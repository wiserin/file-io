add_library(WiseIOLib STATIC)

target_include_directories(WiseIOLib PUBLIC include/)

add_subdirectory(src)

target_link_libraries(WiseIOLib PRIVATE logging)

