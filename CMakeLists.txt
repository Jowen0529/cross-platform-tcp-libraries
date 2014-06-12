#
cmake_minimum_required (VERSION 2.8)
# Project
project (TCP)


#C++11
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")

#set the default path for built executables to the "bin" directory
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/Linux/bin)
#set the default path for built libraries to the "lib" directory
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/Linux)


# Library
include_directories ("${PROJECT_SOURCE_DIR}/TCPLibrary/Src/")
include_directories ("${PROJECT_SOURCE_DIR}/TCPLibrary/Inc/")
include_directories ("${PROJECT_SOURCE_DIR}/TCPLibrary/")

#add_subdirectory(${PROJECT_SOURCE_DIR}/TCPLibrary)
add_library(TCP STATIC IMPORTED)
set_property(TARGET TCP PROPERTY IMPORTED_LOCATION ${PROJECT_SOURCE_DIR}/Linux/libTCP.a)


# Executable
add_executable (Server Src/ServerMain.cpp)
add_executable (ClientPublisher Src/ClientPublisherMain.cpp)
add_executable (ClientSubscriber Src/ClientSubscriberMain.cpp)

# Link Library
target_link_libraries (Server TCP)
target_link_libraries (ClientPublisher TCP)
target_link_libraries (ClientSubscriber TCP)

# Add Install Targets
install (TARGETS  Server ClientPublisher ClientSubscriber DESTINATION bin)

