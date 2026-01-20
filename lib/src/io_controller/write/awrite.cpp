#include <cstdint>  // Copyright 2025 wiserin
#include <vector>
#include <string>

#include "wise-io/core.hpp"
#include "wise-io/stream.hpp"
#include "wise-io/schemas.hpp"
#include "wise-io/buffer.hpp"


using str = std::string;

namespace wiseio {

bool Stream::AWrite(const std::vector<uint8_t>& buffer) {
    if (mode_ != OpenMode::kAppend) {
        logger_.Exception("Для использования этого метода файл должен быть открыт в режиме Append");
        return false;
    }
    bool state = core::AWrite(
        fd_, buffer.data(), buffer.size(),
        logger_);
    return state;
}


bool Stream::AWrite(const IOBuffer& buffer) {
    if (mode_ != OpenMode::kAppend) {
        logger_.Exception("Для использования этого метода файл должен быть открыт в режиме Append");
        return false;
    }
    bool state = core::AWrite(
        fd_, buffer.GetDataPtr(), buffer.GetBufferSize(),
        logger_);
    return state;
}


bool Stream::AWrite(const str& buffer) {
    if (mode_ != OpenMode::kAppend) {
        logger_.Exception("Для использования этого метода файл должен быть открыт в режиме Append");
        return false;
    }
    bool state = core::AWrite(
        fd_, reinterpret_cast<const uint8_t*>(buffer.data()), buffer.size(),
        logger_);
    return state;
}

} // namespace wiseio
