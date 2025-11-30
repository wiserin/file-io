#include <cstdint>
#include <stdexcept>
#include <unistd.h>

#include "wise-io/stream.hpp"
#include "wise-io/schemas.hpp"
#include "logging/logger.hpp"


namespace wiseio {

Stream::Stream(
        OpenMode io_mode,
        uint64_t buffer_size) 
        : buffer_size_(buffer_size)
        , mode_(io_mode) {}


Stream::~Stream() {
    close(fd_);
}


Stream CreateStream(const char* name, OpenMode mode, uint64_t buffer_size) {
    Stream stream {mode, buffer_size};

    stream.logger_ = logging::Logger {name};
    bool state = stream.Open(name);

    if (!state) {
        throw std::runtime_error("Ошибка при открытии файла");
    }
    return stream;
}


} // namespace wiseio

