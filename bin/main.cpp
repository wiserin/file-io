#include <iostream>
#include <vector>

#include "logging/logger.hpp"
#include "logging/schemas.hpp"
#include "wise-io/stream.hpp"
#include "wise-io/schemas.hpp"


int main() {
    logging::Logger::SetupLogger(logging::LoggerMode::kDebug, logging::LoggerIOMode::kSync, true);

    wiseio::Stream file {"test.txt", wiseio::OpenMode::kRead};

    wiseio::Stream out_file ("out.txt", wiseio::OpenMode::kWrite);

    std::vector<uint8_t> buffer;

    // buffer.reserve(4096);
    buffer.reserve(1);

    int state = file.Read(buffer);

    wiseio::IOBuffer out_buff{};

    out_buff.Add(buffer);

    out_file.CustomWrite(out_buff, 1);
    
    // out_file.Write(buffer);
    // out_file.Write(buffer);


    // std::string text(buffer.begin(), buffer.end());
    // std::cout << text << std::endl;
}