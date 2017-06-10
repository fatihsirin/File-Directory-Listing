cmake_minimum_required(VERSION 3.7)
project(File_Directory_Listing)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp src/listing.cpp src/listing.hpp src/debug.h)
add_executable(File_Directory_Listing ${SOURCE_FILES} src/listing.cpp src/listing.hpp src/debug.h)