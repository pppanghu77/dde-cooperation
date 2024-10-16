//------------------------------------------------------------------------------
// Automatically generated by the Fast Binary Encoding compiler, do not modify!
// https://github.com/chronoxor/FastBinaryEncoding
// Source: message.fbe
// FBE version: 1.14.5.0
//------------------------------------------------------------------------------

#pragma once

#if defined(__clang__)
#pragma clang system_header
#elif defined(__GNUC__)
#pragma GCC system_header
#elif defined(_MSC_VER)
#pragma system_header
#endif

#include "fbe_protocol.h"

#include "proto_final_models.h"

namespace FBE {

namespace proto {

// Fast Binary Encoding proto protocol version
struct ProtocolVersion
{
    // Protocol major version
    static const int major = 1;
    // Protocol minor version
    static const int minor = 0;
};

// Fast Binary Encoding proto final sender
class FinalSender : public virtual FBE::Sender
{
public:
    FinalSender()
        : OriginMessageModel(this->_buffer)
        , MessageRejectModel(this->_buffer)
        , MessageNotifyModel(this->_buffer)
        , DisconnectRequestModel(this->_buffer)
    { this->final(true); }
    FinalSender(const FinalSender&) = delete;
    FinalSender(FinalSender&&) noexcept = delete;
    virtual ~FinalSender() = default;

    FinalSender& operator=(const FinalSender&) = delete;
    FinalSender& operator=(FinalSender&&) noexcept = delete;

    size_t send(const ::proto::OriginMessage& value);
    size_t send(const ::proto::MessageReject& value);
    size_t send(const ::proto::MessageNotify& value);
    size_t send(const ::proto::DisconnectRequest& value);

public:
    // Sender models accessors
    FBE::proto::OriginMessageFinalModel OriginMessageModel;
    FBE::proto::MessageRejectFinalModel MessageRejectModel;
    FBE::proto::MessageNotifyFinalModel MessageNotifyModel;
    FBE::proto::DisconnectRequestFinalModel DisconnectRequestModel;
};

// Fast Binary Encoding proto final receiver
class FinalReceiver : public virtual FBE::Receiver
{
public:
    FinalReceiver() { this->final(true); }
    FinalReceiver(const FinalReceiver&) = delete;
    FinalReceiver(FinalReceiver&&) = delete;
    virtual ~FinalReceiver() = default;

    FinalReceiver& operator=(const FinalReceiver&) = delete;
    FinalReceiver& operator=(FinalReceiver&&) = delete;

protected:
    // Receive handlers
    virtual void onReceive(const ::proto::OriginMessage& value) {}
    virtual void onReceive(const ::proto::MessageReject& value) {}
    virtual void onReceive(const ::proto::MessageNotify& value) {}
    virtual void onReceive(const ::proto::DisconnectRequest& value) {}

    // Receive message handler
    bool onReceive(size_t type, const void* data, size_t size) override;

private:
    // Receiver values accessors
    ::proto::OriginMessage OriginMessageValue;
    ::proto::MessageReject MessageRejectValue;
    ::proto::MessageNotify MessageNotifyValue;
    ::proto::DisconnectRequest DisconnectRequestValue;

    // Receiver models accessors
    FBE::proto::OriginMessageFinalModel OriginMessageModel;
    FBE::proto::MessageRejectFinalModel MessageRejectModel;
    FBE::proto::MessageNotifyFinalModel MessageNotifyModel;
    FBE::proto::DisconnectRequestFinalModel DisconnectRequestModel;
};

// Fast Binary Encoding proto final client
class FinalClient : public virtual FinalSender, protected virtual FinalReceiver
{
public:
    FinalClient() = default;
    FinalClient(const FinalClient&) = delete;
    FinalClient(FinalClient&&) = delete;
    virtual ~FinalClient() = default;

    FinalClient& operator=(const FinalClient&) = delete;
    FinalClient& operator=(FinalClient&&) = delete;

    // Reset client buffers
    void reset() { std::scoped_lock locker(this->_lock); reset_requests(); }

    // Watchdog for timeouts
    void watchdog(uint64_t utc) { std::scoped_lock locker(this->_lock); watchdog_requests(utc); }

    std::future<::proto::OriginMessage> request(const ::proto::OriginMessage& value, uint64_t timeout = 0);
    std::future<void> request(const ::proto::DisconnectRequest& value, uint64_t timeout = 0);

protected:
    std::mutex _lock;
    uint64_t _timestamp{0};

    virtual bool onReceiveResponse(const ::proto::OriginMessage& response);

    virtual bool onReceiveResponse(const ::proto::MessageReject& response) { return false; }
    virtual bool onReceiveResponse(const ::proto::MessageNotify& response) { return false; }
    virtual bool onReceiveResponse(const ::proto::DisconnectRequest& response) { return false; }

    virtual bool onReceiveReject(const ::proto::MessageReject& reject);

    virtual bool onReceiveReject(const ::proto::OriginMessage& reject) { return false; }
    virtual bool onReceiveReject(const ::proto::MessageNotify& reject) { return false; }
    virtual bool onReceiveReject(const ::proto::DisconnectRequest& reject) { return false; }

    virtual void onReceiveNotify(const ::proto::OriginMessage& notify) {}
    virtual void onReceiveNotify(const ::proto::MessageReject& notify) {}
    virtual void onReceiveNotify(const ::proto::MessageNotify& notify) {}
    virtual void onReceiveNotify(const ::proto::DisconnectRequest& notify) {}

    virtual void onReceive(const ::proto::OriginMessage& value) override { if (!onReceiveResponse(value) && !onReceiveReject(value)) onReceiveNotify(value); }
    virtual void onReceive(const ::proto::MessageReject& value) override { if (!onReceiveResponse(value) && !onReceiveReject(value)) onReceiveNotify(value); }
    virtual void onReceive(const ::proto::MessageNotify& value) override { if (!onReceiveResponse(value) && !onReceiveReject(value)) onReceiveNotify(value); }
    virtual void onReceive(const ::proto::DisconnectRequest& value) override { if (!onReceiveResponse(value) && !onReceiveReject(value)) onReceiveNotify(value); }

    // Reset client requests
    virtual void reset_requests();

    // Watchdog client requests for timeouts
    virtual void watchdog_requests(uint64_t utc);

private:
    std::unordered_map<FBE::uuid_t, std::tuple<uint64_t, uint64_t, std::promise<::proto::OriginMessage>>> _requests_by_id_OriginMessage;
    std::map<uint64_t, FBE::uuid_t> _requests_by_timestamp_OriginMessage;
};

} // namespace proto

} // namespace FBE
