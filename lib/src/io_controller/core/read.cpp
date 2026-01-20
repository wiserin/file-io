#include <cstddef>  // Copyright 2025 wiserin
#include <unistd.h>
#include <fcntl.h>

#include <logging/logger.hpp>

#include "wise-io/stream.hpp"


namespace wiseio::core {


ssize_t CRead(
        int fd, uint8_t* buffer, size_t buffer_size,
        bool& is_eof, size_t& cursor, const logging::Logger& logger) {
    size_t count = 0;

    while (count < buffer_size) {
        ssize_t c_bytes = pread(fd, buffer + count, buffer_size - count, cursor + count);

        if (c_bytes + count >= buffer_size) {
            count += c_bytes;
            break;
        } else if (c_bytes == 0) {
            is_eof = true;
            logger.Debug("Достигнут конец файла");
            break;
        } else if (c_bytes < 0) {
            if (errno == EINTR) {
                continue;
            }
            logger.Error("Ошибка при чтении файла Errno: " + std::to_string(errno));
            return -1;
        } else {
            count += c_bytes;
        }
    }
    cursor += count;

    return count;
}


ssize_t CustomRead(
        int fd, uint8_t* buffer, size_t offset, size_t buffer_size,
        bool& is_eof, const logging::Logger& logger) {
    size_t count = 0;

    while (count < buffer_size) {
        ssize_t c_bytes = pread(fd, buffer + count, buffer_size - count, offset + count);

        if (c_bytes + count >= buffer_size) {
            count += c_bytes;
            break;
        } else if (c_bytes == 0) {
            is_eof = true;
            logger.Debug("Достигнут конец файла");
            break;
        } else if (c_bytes < 0) {
            if (errno == EINTR) {
                continue;
            }
            logger.Error("Ошибка при чтении файла Errno: " + std::to_string(errno));
            return -1;
        } else {
            count += c_bytes;
        }
    }

    return count;
}

} // namespace wiseio
