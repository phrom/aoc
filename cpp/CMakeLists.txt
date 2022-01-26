cmake_minimum_required(VERSION 3.20)
project(cpp)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(ENABLE_COMPILER_WARNINGS
     $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>,$<CXX_COMPILER_ID:GNU>>:
          -Wall -Wextra -Weffc++ -Wconversion -Wsign-conversion -pedantic>
     $<$<CXX_COMPILER_ID:MSVC>:
          /W4 /WX>)

find_package(Boost REQUIRED)
add_library(lib
  src/day1.cpp
  src/day2.cpp
  src/day3.cpp
  src/day4.cpp
  src/day5.cpp
  src/day6.cpp
  src/day7.cpp
  src/day8.cpp
  src/day9.cpp
  src/day10.cpp
  src/day11.cpp
  src/day12.cpp
  src/day13.cpp
  src/day14.cpp
  src/day15.cpp
  src/day16.cpp
  src/symbol.cpp
  src/bitstream.cpp)
target_include_directories(lib PRIVATE src/include)
target_include_directories(lib SYSTEM PUBLIC src/include)
target_link_libraries(lib PUBLIC Boost::headers)
target_compile_options(lib PRIVATE ${ENABLE_COMPILER_WARNINGS})

add_executable(main src/main.cpp)
target_link_libraries(main PRIVATE lib)
target_compile_definitions(main PRIVATE INPUT_FOLDER="${CMAKE_SOURCE_DIR}/../input")
target_compile_options(main PRIVATE ${ENABLE_COMPILER_WARNINGS})

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
  test/day8.cpp
  test/day9.cpp
  test/day10.cpp
  test/day11.cpp
  test/day12.cpp
  test/day13.cpp
  test/day14.cpp
  test/day15.cpp
  test/day16.cpp
  test/symbol.cpp
  test/bitstream.cpp)
target_link_libraries(test PRIVATE lib Catch2::Catch2)
target_compile_options(test PRIVATE ${ENABLE_COMPILER_WARNINGS})
