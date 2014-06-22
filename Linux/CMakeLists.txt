# Created by Zachary Metcalf
# zachmetcalf@gmail.com
#
# CMakeLists.txt
# TCPLibrary
#
# CMake Settings for Linux
#

# CMake Project
cmake_minimum_required (VERSION 2.8)
project (TCPLibrary)


# Compiler Flags for C++11
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x -pthread")


# Build Output Paths
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR})


# TCPLibrary Includes
include_directories ("${PROJECT_SOURCE_DIR}/../TCPLibrary/Inc/")


# TCPLibrary Link
add_library(TCPLibrary STATIC IMPORTED)
set_property(TARGET TCPLibrary PROPERTY IMPORTED_LOCATION ${PROJECT_SOURCE_DIR}/libTCPLibrary.a)


# TCPLibrary Executables and Links
add_executable (Server ../Demos/ServerMain.cpp)
target_link_libraries (Server TCPLibrary)

add_executable(Client ../Demos/ClientMain.cpp)
target_link_libraries (Client TCPLibrary)


# CMake Install
install (TARGETS Server Client DESTINATION bin)

