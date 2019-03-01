cmake_minimum_required(VERSION 3.10)
project(diplomacy VERSION 0.1.0)

message("Build type: ${CMAKE_BUILD_TYPE}")

include(${CMAKE_BINARY_DIR}/conan_paths.cmake OPTIONAL)

include(${CMAKE_CURRENT_LIST_DIR}/cmake/warnings.cmake)
set(optimisation_flags_release -O3 -march=native)
set(optimisation_flags_debug -O0)
set(debug_flags -g)
add_compile_options(
    ${warnings}
    "$<$<CONFIG:Debug>:${optimisation_flags_debug}>"
    "$<$<CONFIG:Debug>:${debug_flags}>"
    "$<$<CONFIG:Release>:${optimisation_flags_release}>")
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

add_subdirectory(src)

#enable_testing()
#add_subdirectory(test)

if(CLANG_TIDY_EXE AND RUN_CLANG_TIDY)
    set_target_properties(
        test-diplomacy
        PROPERTIES
        CXX_CLANG_TIDY "${CLANG_TIDY}")
endif()
