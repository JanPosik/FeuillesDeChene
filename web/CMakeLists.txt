cmake_minimum_required(VERSION 3.16)

project(feuilles_de_chene)

add_subdirectory(../core ${CMAKE_CURRENT_BINARY_DIR}/include)

add_executable(${PROJECT_NAME} src/wasm_api.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE core)

target_link_options(${PROJECT_NAME} PRIVATE
    "-sEXPORTED_RUNTIME_METHODS=['ccall']"
)
set(CMAKE_EXECUTABLE_SUFFIX ".js")
