#include <cerrno>
#include <cstddef>
#include <cstdint>
#include <unistd.h>
#include <fcntl.h>
#include <vector>

#include "wise-io/stream.hpp"
#include "wise-io/schemas.hpp"
#include "logging/logger.hpp"


namespace wiseio {

Stream::Stream(
        const char* file_path,
        OpenMode io_mode,
        uint64_t buffer_size) 
        : buffer_size_(buffer_size){

    logger = logging::Logger {file_path};
    
    Open(file_path, io_mode);

    }


Stream::~Stream() {
    close(fd_);
}


} // namespace wiseio

