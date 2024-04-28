// SPDX-FileCopyrightText: 2023 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef SESSION_H
#define SESSION_H

#include "proto_protocol.h"
#include <iostream>

enum SessionState {
    RPC_ERROR = -2,
    RPC_DISCONNECTED = -1,
    RPC_DISCONNECTING = 0,
    RPC_CONNECTING = 1,
    RPC_CONNECTED = 2,
};

//using MessageHandler = std::function<bool(const proto::OriginMessage &request, proto::OriginMessage *response)>;
//using StateHandler = std::function<bool(int state, std::string msg)>;

class ServerCallInterface : public std::enable_shared_from_this<ServerCallInterface>
{
public:
    virtual void onReceivedMessage(const proto::OriginMessage &request, proto::OriginMessage *response) = 0;

    virtual void onStateChanged(int state, std::string msg) = 0;
};

#endif // SESSION_H