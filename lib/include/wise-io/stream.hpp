#pragma once
#include <cstddef>
#include <cstdint>
#include <memory>
#include <vector>

#include "logging/logger.hpp"
#include "wise-io/schemas.hpp"


namespace wiseio {

class IOBuffer {
    std::unique_ptr<uint8_t[]> data_;
    uint64_t buffer_size_;
    size_t len_;
    size_t cursor_;

 public:
    IOBuffer(size_t buffer_size = 4096);

    IOBuffer(IOBuffer&& buffer);

    size_t ReadFromBuffer();

    size_t GetBufferLen();
    size_t GetBufferSize();
    uint8_t* GetDataPtr();
    bool SetLen(size_t len);

    bool SetCursor(size_t position);


    ~IOBuffer() = default;
};


class Stream {
    int fd_;
    uint64_t buffer_size_;
    bool is_eof_ = false;

    size_t cursor_;

    logging::Logger logger;

    bool ORead(const char* path);
    bool OWrite(const char* path);
    bool OAppend(const char* path);

    bool Open(const char* path, OpenMode mode);

    ssize_t Read(uint8_t* buffer, size_t offset);
    ssize_t CRead(uint8_t* buffer);
    ssize_t CustomRead(uint8_t* buffer, size_t offset, size_t buffer_size);

    bool AWrite(uint8_t* buffer, size_t buffer_size);
    bool CustomWrite(uint8_t* buffer, size_t offset, size_t buffer_size);

 public:
    Stream(
        const char* file_path,
        OpenMode mode,
        uint64_t buffer_size = 4096);
    

    ssize_t Read(std::vector<uint8_t>& buffer, size_t offset = 0);
    ssize_t Read(IOBuffer& buffer, size_t offset = 0);
    ssize_t CRead(std::vector<uint8_t>& buffer);
    ssize_t CRead(IOBuffer& buffer);
    ssize_t CustomRead(std::vector<uint8_t>& buffer, size_t offset, size_t buffer_size);
    ssize_t CustomRead(IOBuffer& buffer, size_t offset, size_t buffer_size);
    bool Write(std::vector<uint8_t>& buffer);

    ~Stream();

};


} // namespace wiseio