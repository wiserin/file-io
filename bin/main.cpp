#include <compare>
#include <iostream>
#include <sys/types.h>
#include <vector>

#include "logging/logger.hpp"
#include "logging/schemas.hpp"
#include "wise-io/stream.hpp"
#include "wise-io/schemas.hpp"


int main() {
    logging::Logger::SetupLogger(logging::LoggerMode::kDebug, logging::LoggerIOMode::kSync, true);

    wiseio::Stream file = wiseio::CreateStream("test.txt", wiseio::OpenMode::kRead);

    wiseio::Stream out_file = wiseio::CreateStream("out.txt", wiseio::OpenMode::kWrite);

    std::vector<uint8_t> buffer;

    // buffer.reserve(4096);
    buffer.reserve(1);
    std::cerr << "Ok 1" << std::endl;

    int state = file.Read(buffer);

    for(uint8_t el: buffer) {
        std::cerr << el;
    }

    std::cerr << "Ok 2" << std::endl;

    // wiseio::IOBuffer out_buff;

    std::cerr << "Ok 3" << std::endl;
    // out_buff.Add(buffer);

    std::cerr << "Ok 4" << std::endl;

    out_file.CustomWrite(buffer, 1);
    
    // out_file.Write(buffer);
    // out_file.Write(buffer);


    // std::string text(buffer.begin(), buffer.end());
    // std::cout << text << std::endl;
}