// SPDX-FileCopyrightText: 2023 - 2026 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef PORTMANAGER_H
#define PORTMANAGER_H

#include <QObject>

#ifdef __linux__
namespace Dtk {
namespace Core {
class DConfig;
}
}
#endif

class PortManager : public QObject
{
    Q_OBJECT
public:
    static PortManager *instance();

    int getPort() const;
    void setPort(int port);

    // 校验
    bool isPortInRange(int port) const;
    bool isPortAvailable(int port) const;

    // DConfig 与 UI 双向同步：任一侧端口变更都会同步写入另一侧
    void setDConfigPort(int port);

    QString validatePort(int port) const;

Q_SIGNALS:
    void portChanged(int newPort);

private:
    explicit PortManager(QObject *parent = nullptr);
    ~PortManager() override = default;

    void loadFromSettings();

    static constexpr int kDefaultPort = 51596;
    static constexpr int kMinPort = 13628;
    static constexpr int kMaxPort = 23628;

    int m_port = kDefaultPort;
#ifdef __linux__
    Dtk::Core::DConfig *m_dconfig { nullptr };
#endif
};

#endif // PORTMANAGER_H
