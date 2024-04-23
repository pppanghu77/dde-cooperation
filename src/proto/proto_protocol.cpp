//------------------------------------------------------------------------------
// Automatically generated by the Fast Binary Encoding compiler, do not modify!
// https://github.com/chronoxor/FastBinaryEncoding
// Source: message.fbe
// FBE version: 1.14.5.0
//------------------------------------------------------------------------------

#if defined(_MSC_VER)
#pragma warning(push)
#pragma warning(disable:4065) // C4065: switch statement contains 'default' but no 'case' labels
#endif

#include "proto_protocol.h"

namespace FBE {

namespace proto {

size_t Sender::send(const ::proto::OriginMessage& value)
{
    // Serialize the value into the FBE stream
    size_t serialized = OriginMessageModel.serialize(value);
    assert((serialized > 0) && "proto::OriginMessage serialization failed!");
    assert(OriginMessageModel.verify() && "proto::OriginMessage validation failed!");

    // Log the value
    if (this->_logging)
    {
        std::string message = value.string();
        this->onSendLog(message);
    }

    // Send the serialized value
    return this->send_serialized(serialized);
}

size_t Sender::send(const ::proto::MessageReject& value)
{
    // Serialize the value into the FBE stream
    size_t serialized = MessageRejectModel.serialize(value);
    assert((serialized > 0) && "proto::MessageReject serialization failed!");
    assert(MessageRejectModel.verify() && "proto::MessageReject validation failed!");

    // Log the value
    if (this->_logging)
    {
        std::string message = value.string();
        this->onSendLog(message);
    }

    // Send the serialized value
    return this->send_serialized(serialized);
}

size_t Sender::send(const ::proto::MessageNotify& value)
{
    // Serialize the value into the FBE stream
    size_t serialized = MessageNotifyModel.serialize(value);
    assert((serialized > 0) && "proto::MessageNotify serialization failed!");
    assert(MessageNotifyModel.verify() && "proto::MessageNotify validation failed!");

    // Log the value
    if (this->_logging)
    {
        std::string message = value.string();
        this->onSendLog(message);
    }

    // Send the serialized value
    return this->send_serialized(serialized);
}

size_t Sender::send(const ::proto::DisconnectRequest& value)
{
    // Serialize the value into the FBE stream
    size_t serialized = DisconnectRequestModel.serialize(value);
    assert((serialized > 0) && "proto::DisconnectRequest serialization failed!");
    assert(DisconnectRequestModel.verify() && "proto::DisconnectRequest validation failed!");

    // Log the value
    if (this->_logging)
    {
        std::string message = value.string();
        this->onSendLog(message);
    }

    // Send the serialized value
    return this->send_serialized(serialized);
}

bool Receiver::onReceive(size_t type, const void* data, size_t size)
{
    switch (type)
    {
        case FBE::proto::OriginMessageModel::fbe_type():
        {
            // Deserialize the value from the FBE stream
            OriginMessageModel.attach(data, size);
            assert(OriginMessageModel.verify() && "proto::OriginMessage validation failed!");
            [[maybe_unused]] size_t deserialized = OriginMessageModel.deserialize(OriginMessageValue);
            assert((deserialized > 0) && "proto::OriginMessage deserialization failed!");

            // Log the value
            if (this->_logging)
            {
                std::string message = OriginMessageValue.string();
                this->onReceiveLog(message);
            }

            // Call receive handler with deserialized value
            onReceive(OriginMessageValue);
            return true;
        }
        case FBE::proto::MessageRejectModel::fbe_type():
        {
            // Deserialize the value from the FBE stream
            MessageRejectModel.attach(data, size);
            assert(MessageRejectModel.verify() && "proto::MessageReject validation failed!");
            [[maybe_unused]] size_t deserialized = MessageRejectModel.deserialize(MessageRejectValue);
            assert((deserialized > 0) && "proto::MessageReject deserialization failed!");

            // Log the value
            if (this->_logging)
            {
                std::string message = MessageRejectValue.string();
                this->onReceiveLog(message);
            }

            // Call receive handler with deserialized value
            onReceive(MessageRejectValue);
            return true;
        }
        case FBE::proto::MessageNotifyModel::fbe_type():
        {
            // Deserialize the value from the FBE stream
            MessageNotifyModel.attach(data, size);
            assert(MessageNotifyModel.verify() && "proto::MessageNotify validation failed!");
            [[maybe_unused]] size_t deserialized = MessageNotifyModel.deserialize(MessageNotifyValue);
            assert((deserialized > 0) && "proto::MessageNotify deserialization failed!");

            // Log the value
            if (this->_logging)
            {
                std::string message = MessageNotifyValue.string();
                this->onReceiveLog(message);
            }

            // Call receive handler with deserialized value
            onReceive(MessageNotifyValue);
            return true;
        }
        case FBE::proto::DisconnectRequestModel::fbe_type():
        {
            // Deserialize the value from the FBE stream
            DisconnectRequestModel.attach(data, size);
            assert(DisconnectRequestModel.verify() && "proto::DisconnectRequest validation failed!");
            [[maybe_unused]] size_t deserialized = DisconnectRequestModel.deserialize(DisconnectRequestValue);
            assert((deserialized > 0) && "proto::DisconnectRequest deserialization failed!");

            // Log the value
            if (this->_logging)
            {
                std::string message = DisconnectRequestValue.string();
                this->onReceiveLog(message);
            }

            // Call receive handler with deserialized value
            onReceive(DisconnectRequestValue);
            return true;
        }
        default: break;
    }

    return false;
}

bool Proxy::onReceive(size_t type, const void* data, size_t size)
{
    switch (type)
    {
        case FBE::proto::OriginMessageModel::fbe_type():
        {
            // Attach the FBE stream to the proxy model
            OriginMessageModel.attach(data, size);
            assert(OriginMessageModel.verify() && "proto::OriginMessage validation failed!");

            size_t fbe_begin = OriginMessageModel.model.get_begin();
            if (fbe_begin == 0)
                return false;
            // Call proxy handler
            onProxy(OriginMessageModel, type, data, size);
            OriginMessageModel.model.get_end(fbe_begin);
            return true;
        }
        case FBE::proto::MessageRejectModel::fbe_type():
        {
            // Attach the FBE stream to the proxy model
            MessageRejectModel.attach(data, size);
            assert(MessageRejectModel.verify() && "proto::MessageReject validation failed!");

            size_t fbe_begin = MessageRejectModel.model.get_begin();
            if (fbe_begin == 0)
                return false;
            // Call proxy handler
            onProxy(MessageRejectModel, type, data, size);
            MessageRejectModel.model.get_end(fbe_begin);
            return true;
        }
        case FBE::proto::MessageNotifyModel::fbe_type():
        {
            // Attach the FBE stream to the proxy model
            MessageNotifyModel.attach(data, size);
            assert(MessageNotifyModel.verify() && "proto::MessageNotify validation failed!");

            size_t fbe_begin = MessageNotifyModel.model.get_begin();
            if (fbe_begin == 0)
                return false;
            // Call proxy handler
            onProxy(MessageNotifyModel, type, data, size);
            MessageNotifyModel.model.get_end(fbe_begin);
            return true;
        }
        case FBE::proto::DisconnectRequestModel::fbe_type():
        {
            // Attach the FBE stream to the proxy model
            DisconnectRequestModel.attach(data, size);
            assert(DisconnectRequestModel.verify() && "proto::DisconnectRequest validation failed!");

            size_t fbe_begin = DisconnectRequestModel.model.get_begin();
            if (fbe_begin == 0)
                return false;
            // Call proxy handler
            onProxy(DisconnectRequestModel, type, data, size);
            DisconnectRequestModel.model.get_end(fbe_begin);
            return true;
        }
        default: break;
    }

    return false;
}

std::future<::proto::OriginMessage> Client::request(const ::proto::OriginMessage& value, uint64_t timeout)
{
    std::scoped_lock locker(this->_lock);

    std::promise<::proto::OriginMessage> promise;
    std::future<::proto::OriginMessage> future = promise.get_future();

    uint64_t current = utc();

    // Send the request message
    size_t serialized = Sender::send(value);
    if (serialized > 0)
    {
        // Calculate the unique timestamp
        this->_timestamp = (current <= this->_timestamp) ? this->_timestamp + 1 : current;

        // Register the request
        _requests_by_id_OriginMessage.insert(std::make_pair(value.id, std::make_tuple(this->_timestamp, timeout * 1000000, std::move(promise))));
        if (timeout > 0)
            _requests_by_timestamp_OriginMessage.insert(std::make_pair(this->_timestamp, value.id));
    }
    else
        promise.set_exception(std::make_exception_ptr(std::runtime_error("Send request failed!")));

    return future;
}

std::future<void> Client::request(const ::proto::DisconnectRequest& value, uint64_t timeout)
{
    std::promise<void> promise;
    std::future<void> future = promise.get_future();

    // Send the request message
    size_t serialized = Sender::send(value);
    if (serialized > 0)
        promise.set_value();
    else
        promise.set_exception(std::make_exception_ptr(std::runtime_error("Send request failed!")));

    return future;
}

bool Client::onReceiveResponse(const ::proto::OriginMessage& response)
{
    std::scoped_lock locker(this->_lock);

    auto it_OriginMessage = _requests_by_id_OriginMessage.find(response.id);
    if (it_OriginMessage != _requests_by_id_OriginMessage.end())
    {
        auto timestamp = std::get<0>(it_OriginMessage->second);
        [[maybe_unused]] auto timespan = std::get<1>(it_OriginMessage->second);
        auto& promise = std::get<2>(it_OriginMessage->second);
        promise.set_value(response);
        _requests_by_id_OriginMessage.erase(response.id);
        _requests_by_timestamp_OriginMessage.erase(timestamp);
        return true;
    }

    return false;
}

bool Client::onReceiveReject(const ::proto::MessageReject& reject)
{
    std::scoped_lock locker(this->_lock);

    auto it_OriginMessage = _requests_by_id_OriginMessage.find(reject.id);
    if (it_OriginMessage != _requests_by_id_OriginMessage.end())
    {
        auto timestamp = std::get<0>(it_OriginMessage->second);
        [[maybe_unused]] auto timespan = std::get<1>(it_OriginMessage->second);
        auto& promise = std::get<2>(it_OriginMessage->second);
        promise.set_exception(std::make_exception_ptr(std::runtime_error(reject.string())));
        _requests_by_id_OriginMessage.erase(reject.id);
        _requests_by_timestamp_OriginMessage.erase(timestamp);
        return true;
    }

    return false;
}

void Client::reset_requests()
{
    Sender::reset();
    Receiver::reset();

    for (auto& request : _requests_by_id_OriginMessage)
        std::get<2>(request.second).set_exception(std::make_exception_ptr(std::runtime_error("Reset client!")));
    _requests_by_id_OriginMessage.clear();
    _requests_by_timestamp_OriginMessage.clear();
}

void Client::watchdog_requests(uint64_t utc)
{
    auto it_request_by_timestamp_OriginMessage = _requests_by_timestamp_OriginMessage.begin();
    while (it_request_by_timestamp_OriginMessage != _requests_by_timestamp_OriginMessage.end())
    {
        auto& it_request_by_id_OriginMessage = _requests_by_id_OriginMessage[it_request_by_timestamp_OriginMessage->second];
        auto id = it_request_by_timestamp_OriginMessage->second;
        auto timestamp = std::get<0>(it_request_by_id_OriginMessage);
        auto timespan = std::get<1>(it_request_by_id_OriginMessage);
        if ((timestamp + timespan) <= utc)
        {
            auto& promise = std::get<2>(it_request_by_id_OriginMessage);
            promise.set_exception(std::make_exception_ptr(std::runtime_error("Timeout!")));
            _requests_by_id_OriginMessage.erase(id);
            _requests_by_timestamp_OriginMessage.erase(timestamp);
            it_request_by_timestamp_OriginMessage = _requests_by_timestamp_OriginMessage.begin();
            continue;
        }
        else
            break;
    }

}

} // namespace proto

} // namespace FBE

#if defined(_MSC_VER)
#pragma warning(pop)
#endif
