# ---------------------------------------------------------------------------------------
# Set headers
# ---------------------------------------------------------------------------------------
set(xiso_common_INC_DIR ${CMAKE_CURRENT_LIST_DIR}/../include)
file(GLOB_RECURSE xiso_common_HEADER_FILES RELATIVE ${CMAKE_CURRENT_LIST_DIR}/.. "*.h")

message(STATUS "xiso_common_INC_DIR: ${xiso_common_INC_DIR}")
message(STATUS "xiso_common_INC_FILES: ${xiso_common_HEADER_FILES}")