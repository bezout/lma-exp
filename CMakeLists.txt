cmake_minimum_required(VERSION 2.8)

enable_testing()

set(CMAKE_CXX_COMPILER /usr/bin/g++-5)

find_package(Eigen3 REQUIRED)
find_package(Boost REQUIRED system chrono)

set(CMAKE_CXX_FLAGS "-std=c++1y -isystem/usr/include/eigen3")

include_directories("include")
include_directories(${EIGEN3_INCLUDE_DIR})
include_directories(${Boost_INCLUDE_DIR})

set(test_files tests/simple.cpp)

add_executable(lma_test ${test_files})

target_link_libraries(lma_test ${Boost_LIBRARIES})

add_test(lma lma_test)
