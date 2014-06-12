cmake_minimum_required(VERSION 2.4.6)
include($ENV{ROS_ROOT}/core/rosbuild/rosbuild.cmake)

# Set the build type.  Options are:
#  Coverage       : w/ debug symbols, w/o optimization, w/ code-coverage
#  Debug          : w/ debug symbols, w/o optimization
#  Release        : w/o debug symbols, w/ optimization
#  RelWithDebInfo : w/ debug symbols, w/ optimization
#  MinSizeRel     : w/o debug symbols, w/ optimization, stripped binaries
#set(ROS_BUILD_TYPE RelWithDebInfo)

rosbuild_init()


#C++11
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")


#set the default path for built executables to the "bin" directory
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
#set the default path for built libraries to the "lib" directory
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

#uncomment if you have defined messages
#rosbuild_genmsg()
#uncomment if you have defined services
#rosbuild_gensrv()


include_directories ("${PROJECT_SOURCE_DIR}/../TCPLibrary/Src/")
include_directories ("${PROJECT_SOURCE_DIR}/../TCPLibrary/Inc/")
include_directories ("${PROJECT_SOURCE_DIR}/../TCPLibrary/")

add_library(TCP STATIC IMPORTED)
#rosbuild_add_library(TCP STATIC IMPORTED)
set_property(TARGET TCP PROPERTY IMPORTED_LOCATION ${PROJECT_SOURCE_DIR}/libTCP.a)

#common commands for building c++ executables and libraries
#rosbuild_add_library(${PROJECT_NAME} src/example.cpp)
#target_link_libraries(${PROJECT_NAME} another_library)
#rosbuild_add_boost_directories()
#rosbuild_link_boost(${PROJECT_NAME} thread)
#rosbuild_add_executable(example examples/example.cpp)
#target_link_libraries(example ${PROJECT_NAME})

# Executable
#add_executable (Server Src/ServerMain.cpp)
#add_executable (ClientPublisher Src/ClientPublisherMain.cpp)
#add_executable (ClientSubscriber Src/ClientSubscriberMain.cpp)
rosbuild_add_executable (Server Src/ServerMain.cpp)
rosbuild_add_executable (ClientPublisher Src/ClientPublisherMain.cpp)
rosbuild_add_executable (ClientSubscriber Src/ClientSubscriberMain.cpp)
rosbuild_add_executable (ClientSubscriberToROSPublisher Src/ClientSubscriberToROSPublisher.cpp)

# Link Library
target_link_libraries (Server TCP)
target_link_libraries (ClientPublisher TCP)
target_link_libraries (ClientSubscriber TCP)
target_link_libraries (ClientSubscriberToROSPublisher TCP)

# Add Install Targets
install (TARGETS  Server ClientPublisher ClientSubscriber DESTINATION bin)


