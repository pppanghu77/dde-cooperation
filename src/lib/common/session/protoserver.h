// SPDX-FileCopyrightText: 2023 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef PROTOSERVER_H
#define PROTOSERVER_H

#include "asioservice.h"
#include "protoendpoint.h"

#include "server/asio/tcp_server.h"

class ProtoServer : public CppServer::Asio::TCPServer, public ProtoEndpoint
{
public:
    using CppServer::Asio::TCPServer::TCPServer;

    bool hasConnected(const std::string &ip) override;

protected:
    std::shared_ptr<CppServer::Asio::TCPSession> CreateSession(const std::shared_ptr<CppServer::Asio::TCPServer> &server) override;

protected:
    void onError(int error, const std::string &category, const std::string &message) override;

    void onConnected(std::shared_ptr<CppServer::Asio::TCPSession>& session) override;

    void onDisconnected(std::shared_ptr<CppServer::Asio::TCPSession>& session) override;

    // Protocol implementation
    size_t onSend(const void *data, size_t size) override;

private:
    // <ip, sessionid>
    std::shared_mutex _sessionids_lock;
    std::map<std::string, CppCommon::UUID> _session_ids;
};

#endif // PROTOSERVER_H
