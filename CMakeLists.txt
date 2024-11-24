cmake_minimum_required(VERSION 3.25)
project(LR6 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED On)

option(ENABLE_COLOR "Enable colored output" On)
option(ENABLE_TSAN "Build with thread sanitizer" Off)
option(ENABLE_ASAN "Build with address sanitizer" Off)
option(LR6_BUILD_TESTS "Build tests" Off)

set(VOWEL_TABLE ${CMAKE_BINARY_DIR}/genrated/Task2_VowelTable.inc)
set(CONSONANT_TABLE ${CMAKE_BINARY_DIR}/genrated/Task2_ConsonantTable.inc)
set(TABLE_GENERATOR ${CMAKE_SOURCE_DIR}/Task_2/generate_table.py)
add_custom_target(
  tables
  BYPRODUCTS ${VOWELTABLE_PATH} ${CONSONANT_TABLE}
  DEPENDS ${TABLE_GENERATOR}
  COMMAND python3 ${TABLE_GENERATOR} ${VOWEL_TABLE} ${CONSONANT_TABLE}
)

add_library(lr6 STATIC
  Task_1/solution.cc
  Task_2/solution.cc 
  Task_3/solution.cpp
  common.cc
)
add_dependencies(lr6 tables)
target_include_directories(lr6 PUBLIC include ${CMAKE_BINARY_DIR}/genrated)
add_executable(lab6 main.cc)
target_link_libraries(lab6 lr6)

if (${ENABLE_COLOR})
  set_target_properties(lr6 lab6 PROPERTIES COMPILE_DEFINITIONS ENABLE_COLOR)
endif()

# To use Thread Sanitizer everything should be built with it
if (${ENABLE_TSAN}) 
  add_compile_options(-fsanitize=thread)
  add_link_options(-fsanitize=thread)
endif()


if (${ENABLE_ASAN}) 
  set_target_properties(lr6 lab6 PROPERTIES LCOMPILE_OPTIONS -fsanitize=address)
  set_target_properties(lr6 lab6 PROPERTIES LINK_OPTIONS -fsanitize=address)
endif()

if (${LR6_BUILD_TESTS})
  enable_testing()
  add_subdirectory(fuzztest)
  fuzztest_setup_fuzzing_flags()
  add_executable(tests tests/fake-input.cpp tests/task1.cpp tests/task2.cpp)
  link_fuzztest(tests)
  gtest_discover_tests(tests)

  target_link_libraries(tests PRIVATE GTest::gtest_main GTest::gmock lr6)

endif()