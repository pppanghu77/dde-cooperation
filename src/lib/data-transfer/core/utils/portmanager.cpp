// SPDX-FileCopyrightText: 2023 - 2026 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include "portmanager.h"

#include "common/log.h"
#include "common/commonutils.h"

#include <QSettings>
#ifdef __linux__
#include <DConfig>
DCORE_USE_NAMESPACE
#endif

PortManager::PortManager(QObject *parent)
    : QObject(parent)
{
    DLOG << "PortManager initializing";
    loadFromSettings();
#ifdef __linux__
    m_dconfig = DConfig::create("org.deepin.dde.cooperation.transfer", "org.deepin.dde.cooperation.transfer", "", this);
    if (m_dconfig && m_dconfig->isValid()) {
        int dconfigPort = m_dconfig->value("cooperation.transfer.port", 0).toInt();
        if (dconfigPort > 0) {
            setDConfigPort(dconfigPort);
            DLOG << "DConfig port override:" << dconfigPort;
        }
        connect(m_dconfig, &DConfig::valueChanged, this, [this](const QString &key) {
            if (key != QLatin1String("cooperation.transfer.port"))
                return;
            int port = m_dconfig->value(key, 0).toInt();
            if (port > 0 && port != m_port) {
                setDConfigPort(port);
                DLOG << "DConfig port updated:" << port;
            }
        });
    }
#endif
    DLOG << "PortManager initialized, port:" << m_port;
}

PortManager *PortManager::instance()
{
    static PortManager ins;
    return &ins;
}

void PortManager::loadFromSettings()
{
    QSettings settings;
    int userPort = settings.value("transfer/port", 0).toInt();
    if (userPort > 0) {
        m_port = userPort;
    } else {
        m_port = kDefaultPort;
    }
}

void PortManager::setDConfigPort(int port)
{
    DLOG << "DConfig port received:" << port << "(current port:" << m_port << ")";
    if (port > 0 && port != m_port) {
        DLOG << "Applying DConfig port:" << port << "(bypasses range/availability validation, "
             << "if listening fails please check whether this port is occupied or privileged)";
        m_port = port;
        emit portChanged(port);
    }
}

int PortManager::getPort() const
{
    return m_port;
}

void PortManager::setPort(int port)
{
    if (port == m_port)
        return;

    m_port = port;
    QSettings settings;
    settings.setValue("transfer/port", port);
    settings.sync();

#ifdef __linux__
    if (m_dconfig && m_dconfig->isValid()) {
        m_dconfig->setValue("cooperation.transfer.port", port);
    }
#endif

    emit portChanged(port);
    DLOG << "Port updated to:" << port;
}

bool PortManager::isPortInRange(int port) const
{
    return port >= kMinPort && port <= kMaxPort;
}

bool PortManager::isPortAvailable(int port) const
{
    return !deepin_cross::CommonUitls::isPortInUse(port);
}
QString PortManager::validatePort(int port) const
{
    if (!isPortInRange(port)) {
        return QObject::tr("Port number must be between %1 and %2").arg(kMinPort).arg(kMaxPort);
    }

    if (!isPortAvailable(port)) {
        return QObject::tr("Port is already in use, please change");
    }
    return QString();
}
