#pragma once  // Copyright 2025 wiserin
#include <cstddef>
#include <cstdint>
#include <vector>
#include <string>

#include <wise-io/schemas.hpp>
#include <wise-io/stream.hpp>


using str = std::string;


namespace wiseio {


class BaseChunk {
 public:
    virtual void load(wiseio::Stream& stream) = 0;
    virtual ~BaseChunk();
};


class NumChunk : public BaseChunk {
    std::vector<uint8_t> data;
    int num_size;
 public:
    void load(wiseio::Stream& stream) override;

};


class ButeChunk : public BaseChunk {
    std::vector<uint8_t> data;
 public:
    void load(wiseio::Stream& stream) override;

};


class ValidateChunk : public BaseChunk {
    std::vector<uint8_t> data;

 public:
    void load(wiseio::Stream& stream) override;

};


} // namespace wiseio
