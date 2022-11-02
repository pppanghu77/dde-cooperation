#ifndef UVXX_UVTYPE_H
#define UVXX_UVTYPE_H

#include <memory>

#include <spdlog/spdlog.h>

#include "noncopyable.h"

namespace uvxx {

template <typename U, typename T>
class UvType : public noncopyable {
protected:
    UvType(std::string &&typeName)
        : uv_type_(std::make_shared<U>())
        , typeName_(typeName) {
        get()->data = this;
    }

    template <typename D = T>
    D *get() {
        return reinterpret_cast<D *>(uv_type_.get());
    }

    template <typename D = T>
    const D *get() const {
        return reinterpret_cast<const D *>(uv_type_.get());
    }

    const std::string &getTypeName() const { return typeName_; }

private:
    std::shared_ptr<U> uv_type_;
    const std::string typeName_;
};

} // namespace uvxx

#endif // !UVXX_UVTYPE_H
