#pragma once  // Copyright 2025 wiserin
#include <cstddef>
#include <cstdint>
#include <string>
#include <sys/stat.h>

#include <logging/logger.hpp>

using stat_t = struct stat;
using str = std::string;


namespace wiseio::core {

int ORead(const char* path);
int OWrite(const char* path);
int OAppend(const char* path);
int ReadAndWrite(const char* path);

void Close(int fd);

ssize_t CRead(
    int fd, uint8_t* buffer, size_t buffer_size,
    bool& is_eof, size_t& cursor, const logging::Logger& logger);
ssize_t CustomRead(
    int fd, uint8_t* buffer, size_t offset, size_t buffer_size,
    bool& is_eof, const logging::Logger& logger);

bool AWrite(
    int fd, const uint8_t* buffer, size_t buffer_size,
    const logging::Logger& logger);
bool CWrite(
    int fd, const uint8_t* buffer, size_t buffer_size,
    size_t& cursor, const logging::Logger& logger);
bool CustomWrite(
    int fd, const uint8_t* buffer, size_t offset, size_t buffer_size,
    const logging::Logger& logger);

void UpdateStat(stat_t& file_stat);

} // namespace wiseio::core
