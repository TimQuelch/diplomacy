cmake_minimum_required(VERSION 3.10)

include(${CMAKE_BINARY_DIR}/conan_paths.cmake OPTIONAL)

find_package(fmt REQUIRED)
find_package(nlohmann_json REQUIRED)

# Build
add_library(diplomacy map.cpp utils.cpp game.cpp)
add_library(diplomacy::diplomacy ALIAS diplomacy)
target_include_directories(
    diplomacy
    PUBLIC
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include/>
    $<INSTALL_INTERFACE:include/>)
target_compile_features(diplomacy PUBLIC cxx_std_17)
target_link_libraries(diplomacy PUBLIC stdc++fs nlohmann_json::nlohmann_json fmt::fmt)

add_executable(diplomacy-app main.cpp)
add_executable(diplomacy::diplomacy-app ALIAS diplomacy-app)
target_link_libraries(diplomacy-app PRIVATE diplomacy)

configure_file(${PROJECT_SOURCE_DIR}/data/map.json ${CMAKE_CURRENT_BINARY_DIR}/data/map.json COPYONLY)

# Install
include(GNUInstallDirs)
set(INSTALL_CONFIGDIR ${CMAKE_INSTALL_LIBDIR}/cmake/diplomacy)

install(
    TARGETS diplomacy-app
    EXPORT diplomacy-targets
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR})

install(
    EXPORT diplomacy-targets
    FILE diplomacyTargets.cmake
    NAMESPACE diplomacy::
    DESTINATION ${INSTALL_CONFIGDIR})

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/diplomacyConfigVersion.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY AnyNewerVersion)

configure_package_config_file(
    ${PROJECT_SOURCE_DIR}/cmake/diplomacyConfig.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/diplomacyConfig.cmake
    INSTALL_DESTINATION ${INSTALL_CONFIGDIR})

install(
    FILES
    ${CMAKE_CURRENT_BINARY_DIR}/diplomacyConfig.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/diplomacyConfigVersion.cmake
    DESTINATION ${INSTALL_CONFIGDIR})

export(
    EXPORT diplomacy-targets
    FILE ${CMAKE_CURRENT_BINARY_DIR}/diplomacyTargets.cmake
    NAMESPACE diplomacy::)

export(PACKAGE diplomacy)
