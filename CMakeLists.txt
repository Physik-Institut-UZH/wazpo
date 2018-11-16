cmake_minimum_required(VERSION 3.9.0)
project(wazpo)

add_definitions("-std=c++11")


################ ROOT setup #####################
list(APPEND CMAKE_PREFIX_PATH $ENV{ROOTSYS})
find_package(ROOT REQUIRED)
include(${ROOT_USE_FILE})
################################################

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

include_directories(src)

#Get all source file and saves it in a list called SOURCES
file(GLOB SOURCES "src/branchHolder/*.C")

# Producing a shared library with branchHolder
add_library(branches SHARED ${SOURCES})
target_link_libraries( branches ${ROOT_LIBRARIES}) # link the branch holder to ROOT


add_executable(wazpo src/wazpo.cpp)
target_link_libraries(wazpo ${CONAN_LIBS} branches)
target_include_directories(wazpo PUBLIC src/branchHolder)

