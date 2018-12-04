cmake_minimum_required(VERSION 3.10)
project(diplomacy)

include(${CMAKE_BINARY_DIR}/conan_paths.cmake OPTIONAL)

include(${CMAKE_CURRENT_LIST_DIR}/warnings.cmake)
add_compile_options(${warnings})

option(RUN_CLANG_TIDY "Run clang tidy on C++ code" FALSE)
find_program(CLANG_TIDY_EXE NAMES "clang-tidy")
if(NOT CLANG_TIDY_EXE)
    message(STATUS "clang-tidy not found.")
else()
    message(STATUS "clang-tidy found.")
    set(
        CLANG_TIDY
        "${CLANG_TIDY_EXE}"
        "-enable-check-profile")
endif()

add_subdirectory(diplomacy)

#enable_testing()
#add_subdirectory(test)

if(CLANG_TIDY_EXE AND RUN_CLANG_TIDY)
    set_target_properties(
        test-diplomacy
        PROPERTIES
        CXX_CLANG_TIDY "${CLANG_TIDY}")
endif()
