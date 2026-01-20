#include <cstddef>  // Copyright 2025 wiserin
#include <unistd.h>

#include "wise-io/core.hpp"

namespace wiseio::core {

void Close(int fd) {
    close(fd);
}

} // namespace wiseio
