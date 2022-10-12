cmake_minimum_required(VERSION 3.23)
project(convex_hull)

set(CMAKE_CXX_STANDARD 14)

find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )

add_executable(convex_hull main.cpp DivideAndConquer.cpp DivideAndConquer.h Timing.cpp Timing.h Giftwrapping.cpp Giftwrapping.h)
target_link_libraries( convex_hull ${OpenCV_LIBS} )
