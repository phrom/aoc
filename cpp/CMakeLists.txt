cmake_minimum_required(VERSION 3.20)
project(cpp)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(lib
  src/day1.cpp
  src/day2.cpp
  src/day3.cpp
  src/day4.cpp
  src/day5.cpp
  src/day6.cpp
  src/day7.cpp
  src/day8.cpp)
target_include_directories(lib PUBLIC src/include)

add_executable(main src/main.cpp)
target_link_libraries(main PRIVATE lib)

find_package(Catch2 CONFIG REQUIRED)

add_executable(test
  test/main.cpp
  test/day1.cpp
  test/day2.cpp
  test/day3.cpp
  test/day4.cpp
  test/day5.cpp
  test/day6.cpp
  test/day7.cpp
  test/day8.cpp)
target_link_libraries(test PRIVATE lib Catch2::Catch2 Catch2::Catch2WithMain)
