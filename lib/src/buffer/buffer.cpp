#include <cstdint>
#include <utility>

#include "wise-io/stream.hpp"


namespace wiseio {


IOBuffer::IOBuffer(size_t buffer_size)
        : buffer_size_(buffer_size) {}


IOBuffer::IOBuffer(IOBuffer&& buffer) {
    data_ = std::move(buffer.data_);
    buffer_size_ = buffer.buffer_size_;
    len_ = buffer.len_;
    cursor_ = buffer.cursor_;
}


size_t IOBuffer::ReadFromBuffer() {
    return 1;
}


size_t IOBuffer::GetBufferLen() {
    return len_;
}


size_t IOBuffer::GetBufferSize() {
    return buffer_size_;
}


uint8_t* IOBuffer::GetDataPtr() {
    return data_.get();
}


bool IOBuffer::SetLen(size_t len) {
    if (len <= buffer_size_) {
        len_ = len;
        return true;
    } else {
        return false;
    }
}


bool IOBuffer::SetCursor(size_t position) {
    if (position < buffer_size_) {
        cursor_ = position;
        return true;
    } else {
        return false;
    }
}



} // namespase wiseio
