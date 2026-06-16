// SPDX-FileCopyrightText: 2023 - 2026 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef READYWIDGET_H
#define READYWIDGET_H

#include <QFrame>

class QLineEdit;
class QPushButton;
class QLabel;
class QVBoxLayout;
class ReadyWidget : public QFrame
{
    Q_OBJECT
public:
    ReadyWidget(QWidget *parent = nullptr);
    ~ReadyWidget();
    void clear();

public slots:
    void nextPage();
    void backPage();
    void onLineTextChange();
    void connectFailed();
    void themeChanged(int theme);
private:
    void initUI();
    void initPortInput(QVBoxLayout *mainLayout);
    void tryConnect();
    void setnextButEnable(bool enabel);
    bool checkPortConnectivity(const QString &ip, int port);

    QLineEdit *ipInput{ nullptr };
    QLineEdit *captchaInput{ nullptr };
    QPushButton *nextButton{ nullptr };
    QLabel *tiptextlabel{ nullptr };

    QTimer *timer{ nullptr };

    QLineEdit *portInput{ nullptr };
    QLabel *portError{ nullptr };
    int m_savedPort{ 0 };
};

#endif // READYWIDGET_H
