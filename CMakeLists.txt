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
file(GLOB SOURCES "src/libs/*.cpp" "src/add_ons/*.cpp")

# Producing a shared library with branchHolder
add_library(wazlibs SHARED ${SOURCES} )
target_link_libraries( wazlibs ${ROOT_LIBRARIES} ${CONAN_LIBS} ) # link the branch holder to ROOT


add_executable(wazpo src/wazpo.cpp)
target_link_libraries(wazpo wazlibs)
target_include_directories(wazpo PUBLIC src/libs)

