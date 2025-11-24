cmake_minimum_required(VERSION 3.12)


project(
    WiseIO
    VERSION 1.0
    DESCRIPTION "Wise IO controller"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 23)

add_subdirectory(bin)
add_subdirectory(lib)
add_subdirectory(logging)

