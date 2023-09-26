// SPDX-FileCopyrightText: 2023 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include "daemoncoreplugin.h"
#include "base/baseutils.h"

#include <QDebug>
#include <QUrl>

#include <service/ipc/commonservice.h>
#include <service/ipc/fsservice.h>

using namespace daemon_core;

void daemonCorePlugin::initialize()
{
}

bool daemonCorePlugin::start()
{
    CommonService *service = new CommonService(this);
    FSService *fsservice = new FSService(this);
    return true;
}