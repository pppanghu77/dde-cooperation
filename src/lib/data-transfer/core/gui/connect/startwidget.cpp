// SPDX-FileCopyrightText: 2023 - 2026 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include "startwidget.h"
#include "../type_defines.h"
#include "common/log.h"
#include "common/debugdialog.h"
#include <net/helper/transferhepler.h>

#include <QHBoxLayout>
#include <QLabel>
#include <QDebug>
#include <QToolButton>
#include <QStackedWidget>
#include <QCheckBox>
#include <QTextBrowser>
#include <QMouseEvent>
#include <QTimer>

StartWidget::StartWidget(QWidget *parent)
    : QFrame(parent)
{
    DLOG << "Widget constructor called";
    clickTimer = new QTimer(this);
    clickTimer->setSingleShot(true);
    clickTimer->setInterval(3000); // 1 second timeout
    connect(clickTimer, &QTimer::timeout, this, &StartWidget::resetClickCount);

    initUI();
}

StartWidget::~StartWidget()
{
    DLOG << "Widget destructor called";
}

void StartWidget::initUI()
{
    DLOG << "StartWidget initUI";
    setStyleSheet(".StartWidget{background-color: white; border-radius: 10px;}");

    QVBoxLayout *mainLayout = new QVBoxLayout();
    setLayout(mainLayout);
    mainLayout->setSpacing(0);

    QLabel *iconLabel = new QLabel(this);
    iconLabel->setPixmap(QIcon(":/icon/picture-home.png").pixmap(200, 160));
    iconLabel->setAlignment(Qt::AlignBottom | Qt::AlignHCenter);

    titleLabel = new QLabel(tr("UOS data transfer"), this);
    StyleHelper::setAutoFont(titleLabel, 24, QFont::DemiBold);
    titleLabel->setAlignment(Qt::AlignCenter);

    // Install event filter for detecting clicks on title
    titleLabel->installEventFilter(this);

    QLabel *titileLabel = titleLabel;

    QLabel *textLabel2 = new QLabel(tr("UOS transfer tool enables one click migration of your files, personal data, and applications to\nUOS, helping you seamlessly replace your system."), this);
    textLabel2->setAlignment(Qt::AlignTop | Qt::AlignCenter);
    StyleHelper::setAutoFont(textLabel2, 14, QFont::Normal);

    ButtonLayout *buttonLayout = new ButtonLayout();
    buttonLayout->setCount(1);
    QPushButton *nextButton = buttonLayout->getButton1();
    nextButton->setText(tr("Next"));
    connect(nextButton, &QPushButton::clicked, this, &StartWidget::nextPage);

    mainLayout->addSpacing(50);
    mainLayout->addWidget(iconLabel);
    mainLayout->addWidget(titileLabel);
    mainLayout->addWidget(textLabel2);
    mainLayout->addSpacing(60);
    mainLayout->addLayout(buttonLayout);
    DLOG << "StartWidget initUI finished";
}

void StartWidget::nextPage()
{
    DLOG << "Navigating to choose widget";
    emit TransferHelper::instance()->changeWidget(PageName::choosewidget);
}

void StartWidget::themeChanged(int theme)
{
    DLOG << "Theme changed to:" << (theme == 1 ? "light" : "dark");

    //light
    if (theme == 1) {
        DLOG << "Theme is light, setting stylesheet";
        setStyleSheet(".StartWidget{background-color: white; border-radius: 10px;}");
    } else {
        //dark
        DLOG << "Theme is dark, setting stylesheet";
        setStyleSheet(".StartWidget{background-color: rgb(37, 37, 37); border-radius: 10px;}");
    }
}

bool StartWidget::eventFilter(QObject *obj, QEvent *event)
{
    if (obj == titleLabel && event->type() == QEvent::MouseButtonRelease) {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
        if (mouseEvent->button() == Qt::LeftButton) {
            clickCount++;

            if (clickCount >= CLICK_THRESHOLD) {
                showDebugDialog();
                resetClickCount();
            } else {
                // Restart the timer on each click
                clickTimer->start();
            }

            return true;
        }
    }

    return QFrame::eventFilter(obj, event);
}

void StartWidget::resetClickCount()
{
    clickCount = 0;
}

void StartWidget::showDebugDialog()
{
    DLOG << "Opening debug dialog";
    DebugDialog dialog(this);
    dialog.exec();
}
