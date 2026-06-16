// SPDX-FileCopyrightText: 2023 - 2026 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include "readywidget.h"
#include "common/log.h"

#include <QHBoxLayout>
#include <QLabel>
#include <QDebug>
#include <QToolButton>
#include <QStackedWidget>
#include <QCheckBox>
#include <QTextBrowser>
#include <QLineEdit>
#include <QRegularExpressionValidator>
#include <QTimer>
#include <QTcpSocket>

#include <net/helper/transferhepler.h>
#include <utils/portmanager.h>

ReadyWidget::ReadyWidget(QWidget *parent)
    : QFrame(parent)
{
    DLOG << "Widget constructor called";
    initUI();
}

ReadyWidget::~ReadyWidget()
{
    DLOG << "Widget destructor called";
}

void ReadyWidget::clear()
{
    DLOG << "ReadyWidget clear";
    ipInput->clear();
    captchaInput->clear();
    portInput->clear();
    portError->setVisible(false);
    tiptextlabel->setVisible(false);
    setnextButEnable(false);
    tiptextlabel->setStyleSheet(StyleHelper::textStyle(StyleHelper::normal));
    tiptextlabel->setText(tr("connect..."));
    DLOG << "ReadyWidget clear finished";
}

void ReadyWidget::initPortInput(QVBoxLayout *mainLayout)
{
    m_savedPort = PortManager::instance()->getPort();

    QLabel *portTitle = new QLabel(tr("Port"), this);
    QHBoxLayout *portTitleLayout = new QHBoxLayout(this);
    portTitleLayout->setContentsMargins(0, 0, 0, 0);
    portTitleLayout->addSpacing(190);
    portTitleLayout->addWidget(portTitle);
    portTitleLayout->setAlignment(Qt::AlignBottom);

    portInput = new QLineEdit(this);
    portInput->setPlaceholderText(QString::number(m_savedPort));
    portInput->setStyleSheet("border-radius: 8px;"
                             "opacity: 1;"
                             "padding-left: 10px;"
                             "background-color: rgba(0,0,0, 0.08);");
    portInput->setFixedSize(340, 36);
    portInput->setValidator(new QIntValidator(1, 65535, this));
    connect(portInput, &QLineEdit::editingFinished, this, [this]() {
        if (portInput->text().isEmpty())
            portInput->setText(QString::number(m_savedPort));
    });

    QHBoxLayout *portInputLayout = new QHBoxLayout(this);
    portInputLayout->setContentsMargins(0, 0, 0, 0);
    portInputLayout->setAlignment(Qt::AlignCenter);
    portInputLayout->addWidget(portInput);

    portError = new QLabel(this);
    portError->setStyleSheet(StyleHelper::textStyle(StyleHelper::error));
    portError->setVisible(false);
    portError->setAlignment(Qt::AlignCenter);

    connect(portInput, &QLineEdit::textChanged, this, [this]() {
        portError->setVisible(false);
    });

    mainLayout->addLayout(portTitleLayout);
    mainLayout->addLayout(portInputLayout);
    mainLayout->addWidget(portError);
}

bool ReadyWidget::checkPortConnectivity(const QString &ip, int port)
{
    QTcpSocket socket;
    socket.connectToHost(ip, port);
    if (!socket.waitForConnected(3000)) {
        return false;
    }
    socket.disconnectFromHost();
    return true;
}

void ReadyWidget::initUI()
{
    DLOG << "ReadyWidget initUI";
    setStyleSheet(".ReadyWidget{background-color: white; border-radius: 10px;}");

    // init timer
    timer = new QTimer(this);
    timer->setSingleShot(true);
    timer->setInterval(3000);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(0);
    setLayout(mainLayout);

    QLabel *titileLabel = new QLabel(tr("Ready to connect"), this);
    StyleHelper::setAutoFont(titileLabel, 24, QFont::DemiBold);
    titileLabel->setAlignment(Qt::AlignTop | Qt::AlignCenter);

    QLabel *ipLabel = new QLabel(tr("IP"), this);
    QHBoxLayout *ipLayout = new QHBoxLayout(this);
    ipLayout->setContentsMargins(0, 0, 0, 0);
    ipLayout->addSpacing(190);
    ipLayout->addWidget(ipLabel);
    ipLayout->setAlignment(Qt::AlignBottom);

    ipInput = new QLineEdit(this);
    ipInput->setPlaceholderText(tr("Please input the IP of UOS"));
    ipInput->setStyleSheet("border-radius: 8px;"
                           "opacity: 1;"
                           "padding-left: 10px;"
                           "background-color: rgba(0,0,0, 0.08);");
    ipInput->setFixedSize(340, 36);

    QRegularExpressionValidator *ipValidator = new QRegularExpressionValidator(QRegularExpression(
            "^((\\d{1,2}|1\\d{2}|2[0-4]\\d|25[0-5])\\.){3}(\\d{1,2}|1\\d{2}|2[0-4]\\d|25[0-5])$"));

    ipInput->setValidator(ipValidator);

    QObject::connect(ipInput, &QLineEdit::textChanged, [=]() {
        bool isEmpty = ipInput->text().isEmpty();
        ipInput->setClearButtonEnabled(!isEmpty);
        DLOG << "IP input text changed, clear button enabled:" << !isEmpty;
    });
    QHBoxLayout *editLayout1 = new QHBoxLayout(this);
    editLayout1->setContentsMargins(0, 0, 0, 0);
    editLayout1->setAlignment(Qt::AlignCenter);
    editLayout1->addWidget(ipInput);


    QLabel *Captcha = new QLabel(tr("Connect code"), this);
    QHBoxLayout *captchaLayout = new QHBoxLayout(this);
    captchaLayout->setContentsMargins(0, 0, 0, 0);
    captchaLayout->addSpacing(190);
    captchaLayout->addWidget(Captcha);
    captchaLayout->setAlignment(Qt::AlignBottom);

    captchaInput = new QLineEdit(this);
    QRegularExpressionValidator *captchaValidator =
            new QRegularExpressionValidator(QRegularExpression("^\\d{6}$"));
    captchaInput->setValidator(captchaValidator);
    captchaInput->setPlaceholderText(tr("Please input the connect code on UOS"));
    captchaInput->setStyleSheet("border-radius: 8px;"
                                "opacity: 1;"
                                "padding-left: 10px;"
                                "background-color: rgba(0,0,0, 0.08);");
    captchaInput->setFixedSize(340, 36);
    QObject::connect(captchaInput, &QLineEdit::textChanged, [=]() {
        bool isEmpty = captchaInput->text().isEmpty();
        captchaInput->setClearButtonEnabled(!isEmpty);
        DLOG << "Captcha input text changed, clear button enabled:" << !isEmpty;
    });

    QHBoxLayout *editLayout2 = new QHBoxLayout(this);
    editLayout2->setContentsMargins(0, 0, 0, 0);
    editLayout2->setAlignment(Qt::AlignCenter);
    editLayout2->addWidget(captchaInput);

    tiptextlabel = new QLabel(this);
    tiptextlabel->setStyleSheet(StyleHelper::textStyle(StyleHelper::normal));
    tiptextlabel->setText(tr("connect..."));
    tiptextlabel->setVisible(false);
    tiptextlabel->setAlignment(Qt::AlignBottom|Qt::AlignHCenter);

    ButtonLayout *buttonLayout = new ButtonLayout();
    QPushButton *backButton = buttonLayout->getButton1();
    backButton->setText(tr("Back"));
    nextButton = buttonLayout->getButton2();
    nextButton->setText(tr("Connect"));
    nextButton->setEnabled(false);
    setnextButEnable(false);

    connect(nextButton, &QToolButton::clicked, this, &ReadyWidget::tryConnect);
    connect(backButton, &QToolButton::clicked, this, &ReadyWidget::backPage);

    IndexLabel *indelabel = new IndexLabel(1, this);
    indelabel->setAlignment(Qt::AlignCenter);
    QHBoxLayout *indexLayout = new QHBoxLayout(this);
    indexLayout->setContentsMargins(0, 0, 0, 0);
    indexLayout->addWidget(indelabel, Qt::AlignCenter);

    mainLayout->addSpacing(40);
    mainLayout->addWidget(titileLabel);
    mainLayout->addLayout(ipLayout);
    mainLayout->addLayout(editLayout1);
    mainLayout->addLayout(captchaLayout);
    mainLayout->addLayout(editLayout2);
    // 端口输入
    initPortInput(mainLayout);
    mainLayout->addSpacing(80);
    mainLayout->addWidget(tiptextlabel);
    mainLayout->addLayout(buttonLayout);
    mainLayout->addSpacing(4);
    mainLayout->addLayout(indexLayout);

    QObject::connect(ipInput, &QLineEdit::textChanged, this, &ReadyWidget::onLineTextChange);
    QObject::connect(captchaInput, &QLineEdit::textChanged, this, &ReadyWidget::onLineTextChange);
    QObject::connect(TransferHelper::instance(), &TransferHelper::connectSucceed, this,
                     &ReadyWidget::nextPage);
    QObject::connect(TransferHelper::instance(), &TransferHelper::connectFailed, this,
                     &ReadyWidget::connectFailed);

    // Connect the timer's timeout signal to hiding the label
    QObject::connect(timer, &QTimer::timeout, [this]() {
        connectFailed();
    });
    DLOG << "ReadyWidget initUI finished";
}

void ReadyWidget::tryConnect()
{
    DLOG << "ReadyWidget tryConnect";

    int port = portInput->text().isEmpty() ? m_savedPort : portInput->text().toInt();

    QString err = PortManager::instance()->validatePort(port);
    if (!err.isEmpty()) {
        portError->setText(err);
        portError->setVisible(true);
        return;
    }

    if (!checkPortConnectivity(ipInput->text(), port)) {
        tiptextlabel->setStyleSheet(StyleHelper::textStyle(StyleHelper::error));
        tiptextlabel->setText(tr("Port is unreachable, please change the port on both devices and retry"));
        tiptextlabel->setVisible(true);
        return;
    }

    PortManager::instance()->setPort(port);

    tiptextlabel->setText(
            QString("<font size='3' color='#000000'>%1</font>").arg(tr("connect...")));
    tiptextlabel->setVisible(true);
    setnextButEnable(false);

    TransferHelper::instance()->tryConnect(ipInput->text(), captchaInput->text(), port);
    timer->start();
    DLOG << "ReadyWidget tryConnect finished";
}

void ReadyWidget::setnextButEnable(bool enabel)
{
    if (enabel) {
        DLOG << "Enabling next button";
        nextButton->setEnabled(true);
        nextButton->setStyleSheet(".QPushButton{border-radius: 8px;"
                                  "opacity: 1;"
                                  "background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 "
                                  "rgba(37, 183, 255, 1), stop:1 rgba(0, 152, 255, 1));"
                                  "font-family: \"SourceHanSansSC-Medium\";"
                                  "font-size: 14px;"
                                  "font-weight: 500;"
                                  "color: rgba(255,255,255,1);"
                                  "font-style: normal;"
                                  "text-align: center;"
                                  "}");
    } else {
        DLOG << "Disabling next button";
        nextButton->setEnabled(false);
        nextButton->setStyleSheet(".QPushButton{border-radius: 8px;"
                                  "opacity: 1;"
                                  "background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 "
                                  "rgba(37, 183, 255, 0.6), stop:1 rgba(0, 152, 255, 0.6));"
                                  "font-family: \"SourceHanSansSC-Medium\";"
                                  "font-size: 14px;"
                                  "font-weight: 500;"
                                  "color: rgba(255,255,255,0.6);"
                                  "font-style: normal;"
                                  "text-align: center;"
                                  "}");
    }
}

void ReadyWidget::nextPage()
{
    DLOG << "ReadyWidget nextPage";
    QStackedWidget *stackedWidget = qobject_cast<QStackedWidget *>(this->parent());
    if (stackedWidget) {
        DLOG << "Jump to next page";
        stackedWidget->setCurrentIndex(stackedWidget->currentIndex() + 1);
    } else {
        WLOG << "Jump to next page failed, qobject_cast<QStackedWidget *>(this->parent()) = "
                "nullptr";
    }

    clear();
    DLOG << "ReadyWidget nextPage finished";
}

void ReadyWidget::backPage()
{
    DLOG << "ReadyWidget backPage";
    QStackedWidget *stackedWidget = qobject_cast<QStackedWidget *>(this->parent());
    if (stackedWidget) {
        stackedWidget->setCurrentIndex(stackedWidget->currentIndex() - 1);
    } else {
        WLOG << "Jump to next page failed, qobject_cast<QStackedWidget *>(this->parent()) = "
                "nullptr";
    }

    clear();
    DLOG << "ReadyWidget backPage finished";
}

void ReadyWidget::onLineTextChange()
{
    DLOG << "ReadyWidget onLineTextChange";
    QRegularExpression ipRegex(
            "^((\\d{1,2}|1\\d{2}|2[0-4]\\d|25[0-5])\\.){3}(\\d{1,2}|1\\d{2}|2[0-4]\\d|25[0-5])$");
    QRegularExpressionMatch ipMatch = ipRegex.match(ipInput->text());

    if (!ipMatch.hasMatch()) {
        DLOG << "IP input does not match regex, disabling next button";
        setnextButEnable(false);
        return;
    }

    QRegularExpression captchaRegex("^\\d{6}$");
    QRegularExpressionMatch captchaMatch = captchaRegex.match(captchaInput->text());

    if (!captchaMatch.hasMatch()) {
        DLOG << "Captcha input does not match regex, disabling next button";
        setnextButEnable(false);
        return;
    }

    DLOG << "Input validation passed, enabling connect button";
    setnextButEnable(true);
    DLOG << "ReadyWidget onLineTextChange finished";
}

void ReadyWidget::connectFailed()
{
    DLOG << "ReadyWidget connectFailed";
    tiptextlabel->setStyleSheet(StyleHelper::textStyle(StyleHelper::error));
    tiptextlabel->setText(tr("Failed to connect, please check your input"));
}

void ReadyWidget::themeChanged(int theme)
{
    // TODO: 适配暗色主题
    DLOG << "themeChanged:" << theme;
}
