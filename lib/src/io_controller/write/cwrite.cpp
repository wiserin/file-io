#include <cstdint>  // Copyright 2025 wiserin
#include <vector>
#include <string>

#include "wise-io/core.hpp"
#include "wise-io/stream.hpp"
#include "wise-io/schemas.hpp"
#include "wise-io/buffer.hpp"

using str = std::string;

namespace wiseio {

bool Stream::CWrite(const std::vector<uint8_t>& buffer) {
    if (mode_ != OpenMode::kWrite && mode_ != OpenMode::kReadAndWrite) {
        logger_.Exception("Для использования этого метода файл должен быть открыт в режиме Write");
        return false;
    }
    bool state = core::CWrite(
        fd_, buffer.data(), buffer.size(),
        cursor_, logger_);
    return state;
}


bool Stream::CWrite(const IOBuffer& buffer) {
    if (mode_ != OpenMode::kWrite && mode_ != OpenMode::kReadAndWrite) {
        logger_.Exception("Для использования этого метода файл должен быть открыт в режиме Write");
        return false;
    }
    bool state = core::CWrite(
        fd_, buffer.GetDataPtr(), buffer.GetBufferSize(),
        cursor_, logger_);
    return state;
}

bool Stream::CWrite(const str& buffer) {
    if (mode_ != OpenMode::kWrite && mode_ != OpenMode::kReadAndWrite) {
        logger_.Exception("Для использования этого метода файл должен быть открыт в режиме Write");
        return false;
    }
    bool state = core::CWrite(
        fd_, reinterpret_cast<const uint8_t*>(buffer.data()), buffer.size(),
        cursor_, logger_);
    return state;
}


} // namespace wiseio
