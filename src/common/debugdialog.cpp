// SPDX-FileCopyrightText: 2023 - 2026 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include "debugdialog.h"
#include "logger.h"
#include "commonutils.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QGroupBox>
#include <QFileDialog>
#include <QMessageBox>
#include <QProcess>
#include <QNetworkInterface>
#include <QTcpSocket>
#include <QApplication>
#include <QDateTime>
#include <QDir>
#include <QInputDialog>
#include <QLineEdit>
#include <QSettings>

DebugDialog::DebugDialog(QWidget *parent)
    : QDialog(parent)
{
    initUI();
    loadCurrentLogLevel();
}

DebugDialog::~DebugDialog()
{
}

void DebugDialog::initUI()
{
    setWindowTitle(tr("Debug Settings"));
    setMinimumWidth(500);
    setMinimumHeight(400);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(10);
    mainLayout->setContentsMargins(20, 20, 20, 20);

    // Log Level Group
    QGroupBox *logGroup = new QGroupBox(tr("Log Settings"), this);
    QFormLayout *logLayout = new QFormLayout(logGroup);

    m_logLevelLabel = new QLabel(tr("Log Level:"), this);
    m_logLevelCombo = new QComboBox(this);
    m_logLevelCombo->addItem(tr("Debug"), 0);
    m_logLevelCombo->addItem(tr("Info"), 1);
    m_logLevelCombo->addItem(tr("Warning"), 2);
    m_logLevelCombo->addItem(tr("Error"), 3);
    m_logLevelCombo->addItem(tr("Fatal"), 4);

    logLayout->addRow(m_logLevelLabel, m_logLevelCombo);

    m_exportLogBtn = new QPushButton(tr("Export Log"), this);
    logLayout->addRow("", m_exportLogBtn);

    // Port Detection Group
    QGroupBox *portGroup = new QGroupBox(tr("Port Detection"), this);
    QVBoxLayout *portLayout = new QVBoxLayout(portGroup);

    m_detectPortsBtn = new QPushButton(tr("Detect Ports"), this);
    m_refreshBtn = new QPushButton(tr("Refresh"), this);
    m_refreshBtn->setEnabled(false);

    QHBoxLayout *btnLayout = new QHBoxLayout();
    btnLayout->addWidget(m_detectPortsBtn);
    btnLayout->addWidget(m_refreshBtn);
    btnLayout->addStretch();

    portLayout->addLayout(btnLayout);

    m_resultText = new QTextEdit(this);
    m_resultText->setReadOnly(true);
    m_resultText->setMaximumHeight(200);
    portLayout->addWidget(m_resultText);

    // Close Button
    m_closeBtn = new QPushButton(tr("Close"), this);

    mainLayout->addWidget(logGroup);
    mainLayout->addWidget(portGroup);
    mainLayout->addStretch();
    mainLayout->addWidget(m_closeBtn);

    // Connections
    connect(m_logLevelCombo, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &DebugDialog::onLogLevelChanged);
    connect(m_exportLogBtn, &QPushButton::clicked,
            this, &DebugDialog::onExportLog);
    connect(m_detectPortsBtn, &QPushButton::clicked,
            this, &DebugDialog::onDetectPorts);
    connect(m_refreshBtn, &QPushButton::clicked,
            this, &DebugDialog::onRefreshPorts);
    connect(m_closeBtn, &QPushButton::clicked,
            this, &QDialog::accept);

    // Setup detection timer
    m_detectTimer = new QTimer(this);
    m_detectTimer->setSingleShot(true);
    m_detectTimer->setInterval(5000); // 5 second timeout
    connect(m_detectTimer, &QTimer::timeout, this, [this]() {
        m_resultText->append(tr("\nPort detection timeout!"));
        m_detectPortsBtn->setEnabled(true);
        m_refreshBtn->setEnabled(false);
    });
}

void DebugDialog::loadCurrentLogLevel()
{
    // Get current log level from global variable
    int currentLevel = static_cast<int>(deepin_cross::g_logLevel);
    m_logLevelCombo->setCurrentIndex(currentLevel);
}

void DebugDialog::onLogLevelChanged(int index)
{
    int level = m_logLevelCombo->itemData(index).toInt();
    deepin_cross::g_logLevel = static_cast<deepin_cross::LogLevel>(level);

    // Save to config file
    saveLogLevel(level);

    m_resultText->append(tr("Log level changed to: ") + m_logLevelCombo->currentText());
    m_resultText->append(tr("Log level will persist after restart."));
}

void DebugDialog::saveLogLevel(int level)
{
    QString configPath = deepin_cross::CommonUitls::getLogDir() + "config.conf";
    QSettings settings(configPath, QSettings::IniFormat);
    settings.setValue("g_minLogLevel", level);
    settings.sync();
}

void DebugDialog::onExportLog()
{
    QString logPath = deepin_cross::CommonUitls::getLogDir();

    // Let user select destination directory
    QString destDir = QFileDialog::getExistingDirectory(this, tr("Select Export Directory"), QDir::homePath());

    if (destDir.isEmpty()) {
        m_resultText->append(tr("Export cancelled."));
        return;
    }

    // Generate folder name with timestamp
    QString timestamp = QDateTime::currentDateTime().toString("yyyyMMdd_hhmmss");
    QString destPath = destDir + "/logs_" + timestamp;

    // Copy directory recursively
    QDir logDir(logPath);
    if (!logDir.exists()) {
        QMessageBox::warning(this, tr("Warning"), tr("Log directory does not exist!"));
        m_resultText->append(tr("Log directory does not exist: ") + logPath);
        return;
    }

    // Copy the directory
    bool success = copyDirectory(logPath, destPath);

    if (success) {
        QMessageBox::information(this, tr("Success"), tr("Logs exported to: ") + destPath);
        m_resultText->append(tr("Export completed successfully!"));
        m_resultText->append(tr("Logs copied to: ") + destPath);
    } else {
        QMessageBox::critical(this, tr("Error"), tr("Failed to export logs"));
        m_resultText->append(tr("Export failed"));
    }
}

bool DebugDialog::copyDirectory(const QString &src, const QString &dest)
{
    QDir srcDir(src);
    QDir destDir(dest);

    if (!destDir.exists()) {
        destDir.mkpath(dest);
    }

    foreach (QFileInfo info, srcDir.entryInfoList(QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot)) {
        if (info.isDir()) {
            if (!copyDirectory(info.absoluteFilePath(), dest + "/" + info.fileName())) {
                return false;
            }
        } else {
            QFile::copy(info.absoluteFilePath(), dest + "/" + info.fileName());
        }
    }

    return true;
}

void DebugDialog::onDetectPorts()
{
    // Get target IP from user
    bool ok;
    QString targetIP = QInputDialog::getText(this, tr("Target IP"),
                                              tr("Please enter target IP address:"),
                                              QLineEdit::Normal, "", &ok);

    if (!ok || targetIP.isEmpty()) {
        m_resultText->append(tr("\nPort detection cancelled."));
        return;
    }

    // Get port list from user
    QString portText = QInputDialog::getText(this, tr("Ports to Detect"),
                                              tr("Please enter ports (comma separated):"),
                                              QLineEdit::Normal, "13628,13629,13630", &ok);

    if (!ok || portText.isEmpty()) {
        m_resultText->append(tr("\nPort detection cancelled."));
        return;
    }

    QStringList ports = portText.split(',', QString::SkipEmptyParts);
    for (QString &port : ports) {
        port = port.trimmed();
    }

    m_detectPortsBtn->setEnabled(false);
    m_refreshBtn->setEnabled(true);
    m_resultText->clear();
    m_resultText->append(tr("Detecting ports..."));

    detectPortsInternal(targetIP, ports);
}

void DebugDialog::onRefreshPorts()
{
    // Reuse the same detection logic
    onDetectPorts();
}

void DebugDialog::detectPortsInternal(const QString &targetIP, const QStringList &ports)
{
    m_resultText->append(tr("\n=== Local Network Interfaces ==="));

    // Get all network interfaces
    QList<QNetworkInterface> interfaces = QNetworkInterface::allInterfaces();

    for (const QNetworkInterface &interface : interfaces) {
        if (interface.flags() & QNetworkInterface::IsRunning) {
            m_resultText->append(tr("\nInterface: ") + interface.humanReadableName());
            m_resultText->append(tr("  MAC: ") + interface.hardwareAddress());

            QList<QNetworkAddressEntry> entries = interface.addressEntries();
            for (const QNetworkAddressEntry &entry : entries) {
                if (entry.ip().protocol() == QAbstractSocket::IPv4Protocol) {
                    m_resultText->append(tr("  IP: ") + entry.ip().toString());
                }
            }
        }
    }

    // Check specified ports
    m_resultText->append(tr("\n=== Target Port Detection ==="));
    m_resultText->append(tr("Target IP: ") + targetIP);
    m_resultText->append(tr("Ports: ") + ports.join(", "));

    for (const QString &portStr : ports) {
        bool portOk;
        int port = portStr.toInt(&portOk);

        if (!portOk || port <= 0 || port > 65535) {
            m_resultText->append(tr("\nPort ") + portStr + tr(": Invalid"));
            continue;
        }

        m_resultText->append(tr("\nChecking port ") + portStr + tr("..."));

        // Use QTcpSocket to check if port is open
        QTcpSocket socket;
        socket.connectToHost(targetIP, port);

        if (socket.waitForConnected(1000)) {
            m_resultText->append(tr("  Port ") + portStr + tr(": OPEN (Connected)"));
            socket.disconnectFromHost();
            socket.waitForDisconnected(500);
        } else {
            m_resultText->append(tr("  Port ") + portStr + tr(": CLOSED (") + socket.errorString() + tr(")"));
        }
    }

    m_resultText->append(tr("\nPort detection completed!"));
    m_detectPortsBtn->setEnabled(true);
}
