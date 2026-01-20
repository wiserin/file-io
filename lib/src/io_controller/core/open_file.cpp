#include <cstddef>  // Copyright 2025 wiserin
#include <unistd.h>
#include <fcntl.h>

#include "wise-io/core.hpp"

namespace wiseio::core {

int ORead(const char* path) {
    int fd = open(path, O_RDONLY);

    return fd;
}


int OWrite(const char* path) {
    int fd = open(path, O_WRONLY | O_CREAT, 0666);

    return fd;
}


int OAppend(const char* path) {
    int fd = open(path, O_WRONLY | O_APPEND | O_CREAT, 0666);

    return fd;
}


int ReadAndWrite(const char* path) {
    int fd = open(path, O_RDWR | O_CREAT, 0666);

    return fd;
}

} // namespace wiseio
