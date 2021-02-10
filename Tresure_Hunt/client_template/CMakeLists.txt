cmake_minimum_required(VERSION 2.8.3)
project(treasure_hunt CXX)

SET(DUELS_ROOT "/home/ecn/duels/opt/duels" CACHE STRING "Path to duels installation folder")

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_BUILD_TYPE Debug)

# find ZeroMQ
find_path ( ZMQ_INCLUDE_DIR zmq.h )
find_library ( ZMQ_LIBRARY NAMES zmq )
include_directories(${DUELS_ROOT}/include ${ZMQ_INCLUDE_DIR})
add_definitions(-DDUELS_ROOT="${DUELS_ROOT}")

# add whatever additional includes / libs needed for your AI

add_executable(treasure_hunt treasure_hunt.cpp)
target_link_libraries(treasure_hunt ${ZMQ_LIBRARY})
