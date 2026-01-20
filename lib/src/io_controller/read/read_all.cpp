#include <cstddef>  // Copyright 2025 wiserin
#include <cstdint>
#include <vector>
#include <string>

#include "wise-io/schemas.hpp"
#include "wise-io/stream.hpp"
#include "wise-io/buffer.hpp"
#include "wise-io/core.hpp"

using str = std::string;

namespace wiseio {

ssize_t Stream::ReadAll(std::vector<uint8_t>& buffer) {
    FdCheck();
    if (mode_ != OpenMode::kRead && mode_ != OpenMode::kReadAndWrite) {
        logger_.Exception("Для использования этого метода файл должен быть открыт в режиме read");
        return false;
    }
    size_t f_size = GetFileSize();
    buffer.resize(f_size);

    ssize_t len = core::CustomRead(
        fd_, buffer.data(), 0, f_size,
        is_eof_, logger_);
    return len;
}


ssize_t Stream::ReadAll(IOBuffer& buffer) {
    FdCheck();
    if (mode_ != OpenMode::kRead && mode_ != OpenMode::kReadAndWrite) {
        logger_.Exception("Для использования этого метода файл должен быть открыт в режиме read");
        return false;
    }
    size_t f_size = GetFileSize();
    buffer.ResizeBuffer(f_size);

    ssize_t len = core::CustomRead(
        fd_, buffer.GetDataPtr(), 0, f_size,
        is_eof_, logger_);
    return len;
}

ssize_t Stream::ReadAll(str& buffer) {
    FdCheck();
    if (mode_ != OpenMode::kRead && mode_ != OpenMode::kReadAndWrite) {
        logger_.Exception("Для использования этого метода файл должен быть открыт в режиме read");
        return false;
    }

    size_t f_size = GetFileSize();
    buffer.resize(f_size);

    ssize_t len = core::CustomRead(
        fd_, reinterpret_cast<uint8_t*>(buffer.data()), 0, f_size,
        is_eof_, logger_);

    return len;
}

} // namespace wiseio

