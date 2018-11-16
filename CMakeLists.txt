cmake_minimum_required(VERSION 3.9.0)
project(wazpo)

add_definitions("-std=c++11")

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_executable(wazpo src/wazpo.cpp)
target_link_libraries(wazpo ${CONAN_LIBS})

