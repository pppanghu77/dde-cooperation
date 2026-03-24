// SPDX-FileCopyrightText: 2023 - 2026 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef STARTWIDGET_H
#define STARTWIDGET_H

#include <QFrame>
#include <QLabel>

class QPushButton;
class QTimer;
class DebugDialog;

class StartWidget : public QFrame
{
    Q_OBJECT

public:
    StartWidget(QWidget *parent = nullptr);
    ~StartWidget();

public slots:
    void nextPage();
    void themeChanged(int theme);

protected:
    bool eventFilter(QObject *obj, QEvent *event) override;

private slots:
    void resetClickCount();

private:
    void initUI();
    void showDebugDialog();

    QPushButton *nextButton { nullptr };
    QLabel *titleLabel { nullptr };
    QTimer *clickTimer { nullptr };
    int clickCount { 0 };
    static constexpr int CLICK_THRESHOLD = 10;
};

#endif
