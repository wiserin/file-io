add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE logging)
target_link_libraries(${PROJECT_NAME} PRIVATE WiseIOLib)
