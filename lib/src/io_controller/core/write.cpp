#include <cstddef>  // Copyright 2025 wiserin
#include <string>
#include <unistd.h>
#include <fcntl.h>

#include <logging/logger.hpp>

#include "wise-io/core.hpp"


namespace wiseio::core {

bool AWrite(
        int fd, const uint8_t* buffer, size_t buffer_size,
        const logging::Logger& logger) {
    size_t written = 0;

    while (written < buffer_size) {
        ssize_t res = write(fd, buffer + written, buffer_size - written);

        if (res < 0) {
            if (errno == EINTR) {
                continue;
            }
            logger.Error("Ошибка записи в файл. Errno: " + std::to_string(errno));
            return false;
        }
        written += res;
    }

    return true;
}


bool CWrite(
        int fd, const uint8_t* buffer, size_t buffer_size,
        size_t& cursor, const logging::Logger& logger) {
    size_t written = 0;

    while (written < buffer_size) {
        ssize_t res = pwrite(fd, buffer + written, buffer_size - written, cursor + written);

        if (res < 0) {
            if (errno == EINTR) {
                continue;
            }
            logger.Error("Ошибка записи в файл. Errno: " + std::to_string(errno));
            return false;
        }
        written += res;
    }

    cursor += written;

    return true;
}


bool CustomWrite(
        int fd, const uint8_t* buffer, size_t offset, size_t buffer_size,
        const logging::Logger& logger) {
    size_t written = 0;

    while (written < buffer_size) {
        ssize_t res = pwrite(fd, buffer + written, buffer_size - written, offset + written);

        if (res < 0) {
            if (errno == EINTR) {
                continue;
            }
            logger.Error("Ошибка записи в файл. Errno: " + std::to_string(errno));
            return false;
        }
        written += res;
    }

    return true;
}

} // namespace wiseio
