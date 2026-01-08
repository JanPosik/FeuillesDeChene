cmake_minimum_required(VERSION 3.31.6)

project(FeuillesDeChene)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

add_executable(${PROJECT_NAME} main.cpp cli.cpp cli_record_manager.cpp)

add_subdirectory(../core ${CMAKE_CURRENT_BINARY_DIR}/core)

target_link_libraries(${PROJECT_NAME} PRIVATE core)
