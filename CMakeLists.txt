cmake_minimum_required(VERSION 3.10...3.21)

# ---------------------------------------------------------------------------------------
# Start project
# ---------------------------------------------------------------------------------------
# ---------------------------------------------------------------------------------------
# Start project
# ---------------------------------------------------------------------------------------
include(cmake/project_headers.cmake)
include(cmake/project_sources.cmake)
include(cmake/parse_json.cmake)

# 解析 json 中的 version 字段
set(PROJECT_PACKAGE_JSON "${CMAKE_CURRENT_LIST_DIR}/package.json")
parse_json(${PROJECT_PACKAGE_JSON} "version" PACKAGE_VER)

project(xiso_common VERSION ${PACKAGE_VER} LANGUAGES CXX)

# ---------------------------------------------------------------------------------------
# Set default environment variable
# ---------------------------------------------------------------------------------------
include(GNUInstallDirs)

# ---------------------------------------------------------------------------------------
# Set default build to release
# ---------------------------------------------------------------------------------------
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Choose Release or Debug" FORCE)
endif()
message(STATUS "Build ${PROJECT_NAME}: ${PROJECT_VERSION} ${CMAKE_BUILD_TYPE}")

# ---------------------------------------------------------------------------------------
# Compiler config
# ---------------------------------------------------------------------------------------
if(NOT CMAKE_CXX_STANDARD)
    set(CMAKE_CXX_STANDARD 14)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
endif()

set(CMAKE_CXX_EXTENSIONS                                       OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS                              ON)

option(BUILD_SHARED_LIBS             "Build with shared libs"  ON)
option(BUILD_EXAMPLES                "Build with examples"     ON)
option(BUILD_TESTING                 "Build tests"             ON)
option(GENERATOR_DOCS                "Generator api docs"      OFF)
option(BUILD_UNINSTALL_TARGET        "Build uninstall target"  OFF)
option(BUILD_CPPCHECK_TARGET         "Build cppcheck target"   OFF)

# ---------------------------------------------------------------------------------------
# Set output directory
# ---------------------------------------------------------------------------------------
if (NOT DEFINED CMAKE_RUNTIME_OUTPUT_DIRECTORY)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)
endif()
if (NOT DEFINED CMAKE_LIBRARY_OUTPUT_DIRECTORY)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)
endif()
if (NOT DEFINED CMAKE_ARCHIVE_OUTPUT_DIRECTORY)
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)
endif()

# ---------------------------------------------------------------------------------------
# Find packages
# ---------------------------------------------------------------------------------------
find_package(Threads REQUIRED)

# generator version file
configure_file(
    "${CMAKE_CURRENT_LIST_DIR}/version.h.in"
    "${xiso_common_INC_DIR}/xiso/common/version.h")

# ---------------------------------------------------------------------------------------
# Static/Shared library
# ---------------------------------------------------------------------------------------
if(BUILD_SHARED_LIBS)
    add_library(${PROJECT_NAME} SHARED ${xiso_common_SOURCE_FILES} ${xiso_common_HEADER_FILES})
else()
    add_library(${PROJECT_NAME} STATIC ${xiso_common_SOURCE_FILES} ${xiso_common_HEADER_FILES})
endif()

target_include_directories(${PROJECT_NAME} PUBLIC
    $<BUILD_INTERFACE:${xiso_common_INC_DIR}>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)

target_link_libraries(${PROJECT_NAME} PUBLIC Threads::Threads)

set_target_properties(${PROJECT_NAME} PROPERTIES 
    VERSION ${PROJECT_VERSION} 
    SOVERSION ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR})

# ---------------------------------------------------------------------------------------
# Build examples
# ---------------------------------------------------------------------------------------
if(BUILD_EXAMPLES)
    message(STATUS "Generating examples")

    add_subdirectory(examples)
endif()

# ---------------------------------------------------------------------------------------
# Build tests
# ---------------------------------------------------------------------------------------
if(BUILD_TESTING)
    find_package(GTest QUIET)
    if(GTest_FOUND)
        message(STATUS "Generating tests")

        enable_testing()
        add_subdirectory(tests)
    endif()
endif()

# ---------------------------------------------------------------------------------------
# Generator api docs
# ---------------------------------------------------------------------------------------
if(GENERATOR_DOCS)
    message(STATUS "Generating api docs")
    set(DOXYGEN_INPUT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
    set(DOXYGEN_OUTPUT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/api-docs)
    configure_file(
        "${CMAKE_CURRENT_LIST_DIR}/Doxyfile.in"
        "${CMAKE_CURRENT_LIST_DIR}/Doxyfile")
    execute_process(
        COMMAND "doxygen" ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile
        OUTPUT_QUIET ERROR_QUIET)
endif()

# ---------------------------------------------------------------------------------------
# Install
# ---------------------------------------------------------------------------------------
include(CMakePackageConfigHelpers)
install(
    DIRECTORY ${xiso_common_INC_DIR}/xiso
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(
    TARGETS ${PROJECT_NAME}
    EXPORT ${PROJECT_NAME}Targets
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/package_config.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
    PATH_VARS CMAKE_INSTALL_INCLUDEDIR CMAKE_INSTALL_LIBDIR CMAKE_INSTALL_SYSCONFDIR)

write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion)

install(
    FILES ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME})

install(
    EXPORT ${PROJECT_NAME}Targets
    FILE ${PROJECT_NAME}Targets.cmake
    NAMESPACE ${PROJECT_NAME}::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME})

# ---------------------------------------------------------------------------------------
# Configure uninstall target
# ---------------------------------------------------------------------------------------
if(BUILD_UNINSTALL_TARGET)
    configure_file(
        "${CMAKE_CURRENT_SOURCE_DIR}/cmake/cmake_uninstall.cmake.in"
        "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
        IMMEDIATE @ONLY)

    add_custom_target(uninstall
        COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake)
endif()

# ---------------------------------------------------------------------------------------
# Configure cppcheck target
# ---------------------------------------------------------------------------------------
if(BUILD_CPPCHECK_TARGET)
    configure_file(
        "${CMAKE_CURRENT_SOURCE_DIR}/cmake/cmake_cppcheck.cmake.in"
        "${CMAKE_CURRENT_BINARY_DIR}/make_cppcheck.cmake"
        IMMEDIATE @ONLY)

    add_custom_target(cppcheck
        COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/make_cppcheck.cmake)
endif()