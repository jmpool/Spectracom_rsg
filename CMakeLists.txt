cmake_minimum_required(VERSION 2.8.3)
project(spectracom_rsg)

set(CMAKE_XCODE_ATTRIBUTE_CLANG_CXX_LANGUAGE_STANDARD "c++0x")
set(CMAKE_XCODE_ATTRIBUTE_CLANG_CXX_LIBRARY "libc++")
set(CMAKE_CXX_FLAGS "-std=gnu++11")
SET(CMAKE_EXE_LINKER_FLAGS "-pthread")

## Find catkin and any catkin packages
find_package(catkin REQUIRED COMPONENTS roscpp rospy std_msgs genmsg spectracom)

set(SPECTRACOM_SRCS src/SpectracomGsg6_rsg.cpp)
# Add default header files
set(SPECTRACOM_HEADERS  include/spectracom_rsg/SpectracomGsg6_rsg.hpp)

## Specify additional locations of header files
## Your package locations should be listed before other locations
include_directories(include ${catkin_INCLUDE_DIRS})

## Declare a cpp library
add_library(spectracom_rsg 
            ${SPECTRACOM_SRCS}
            ${SPECTRACOM_HEADERS})

## Generate added messages and services
generate_messages(DEPENDENCIES std_msgs)

## Declare a catkin package
catkin_package()

# add_executable(rsg_talker src/rsg_talker.cpp)
# target_link_libraries(rsg_talker ${catkin_LIBRARIES})

add_executable(rsg_listener src/rsg_listener.cpp)
target_link_libraries(rsg_listener ${catkin_LIBRARIES} spectracom_rsg)
add_dependencies(rsg_listener spectracom_rsg)