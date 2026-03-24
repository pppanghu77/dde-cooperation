// SPDX-FileCopyrightText: 2023 - 2026 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef DEBUGDIALOG_H
#define DEBUGDIALOG_H

#include <QDialog>
#include <QPushButton>
#include <QComboBox>
#include <QTextEdit>
#include <QLabel>
#include <QTimer>

class DebugDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DebugDialog(QWidget *parent = nullptr);
    ~DebugDialog();

private slots:
    void onLogLevelChanged(int index);
    void onExportLog();
    void onDetectPorts();
    void onRefreshPorts();

private:
    void initUI();
    void loadCurrentLogLevel();
    void saveLogLevel(int level);
    void detectPortsInternal(const QString &targetIP, const QStringList &ports);
    bool copyDirectory(const QString &src, const QString &dest);

    // UI components
    QLabel *m_logLevelLabel;
    QComboBox *m_logLevelCombo;
    QPushButton *m_exportLogBtn;
    QPushButton *m_detectPortsBtn;
    QPushButton *m_refreshBtn;
    QPushButton *m_closeBtn;
    QTextEdit *m_resultText;

    // Port detection timer for timeout handling
    QTimer *m_detectTimer;
};

#endif // DEBUGDIALOG_H
