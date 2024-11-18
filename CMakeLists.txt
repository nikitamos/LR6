cmake_minimum_required(VERSION 3.30)
project(LR6 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

option(ENABLE_COLOR "Enable colored output" On)
option(ENABLE_TSAN "Build with thread sanitizer" Off)
option(ENABLE_ASAN "Build with address sanitizer" Off)

if (${ENABLE_COLOR})
  add_compile_definitions(ENABLE_COLOR)
endif()

if (${ENABLE_TSAN}) 
  add_compile_options(-fsanitize=thread)
  add_link_options(-fsanitize=thread)
endif()

if (${ENABLE_ASAN}) 
  add_compile_options(-fsanitize=address)
  add_link_options(-fsanitize=address)
endif()

set(VOWEL_TABLE ${CMAKE_BINARY_DIR}/genrated/Task2_VowelTable.inc)
set(CONSONANT_TABLE ${CMAKE_BINARY_DIR}/genrated/Task2_ConsonantTable.inc)
set(TABLE_GENERATOR ${CMAKE_SOURCE_DIR}/Task_2/generate_table.py)
add_custom_command(
  OUTPUT ${VOWELTABLE_PATH}
  OUTPUT ${CONSONANT_TABLE}
  COMMAND python3 ${TABLE_GENERATOR} ${VOWEL_TABLE} ${CONSONANT_TABLE}
  DEPENDS ${TABLE_GENERATOR}
)

add_library(lr6 STATIC
  Task_1/solution.cc
  Task_2/solution.cc ${VOWEL_TABLE} ${CONSONANT_TABLE}
  Task_3/solution.cpp
  common.cc
)
target_include_directories(lr6 PUBLIC include ${CMAKE_BINARY_DIR}/genrated)
add_executable(lab6 main.cc)
target_link_libraries(lab6 lr6)

add_library(StalinSort SHARED Task_1/StalinSort.cc)
target_link_libraries(StalinSort lr6)