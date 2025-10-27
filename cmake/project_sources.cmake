# ---------------------------------------------------------------------------------------
# Set sources
# ---------------------------------------------------------------------------------------
set(xiso_common_SRC_DIR ${CMAKE_CURRENT_LIST_DIR}/../src)
file(GLOB_RECURSE xiso_common_SOURCE_FILES RELATIVE ${CMAKE_CURRENT_LIST_DIR}/.. "src/*.cpp")

message(STATUS "xiso_common_SRC_DIR: ${xiso_common_SRC_DIR}")
message(STATUS "xiso_common_SRC_FILES: ${xiso_common_SOURCE_FILES}")