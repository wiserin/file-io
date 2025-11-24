set(WISEIO_STREAM_SRC
    ${CMAKE_CURRENT_SOURCE_DIR}/stream.cpp)


target_sources(WiseIOLib PRIVATE ${WISEIO_STREAM_SRC})

add_subdirectory(private)
add_subdirectory(read)
add_subdirectory(write)