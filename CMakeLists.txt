cmake_minimum_required(VERSION 3.15)
project(LR6 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

set(TASK_COUNT 1)
option(ENABLE_COLOR "Disable colored output" On)

if (${ENABLE_COLOR})
  add_compile_definitions(ENABLE_COLOR)
endif()

add_library(lr6 STATIC Task_1/solution.cc common.cc)
target_include_directories(lr6 PUBLIC include)
add_executable(lab6 main.cc)
target_link_libraries(lab6 lr6)
