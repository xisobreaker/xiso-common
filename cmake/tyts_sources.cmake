# ---------------------------------------------------------------------------------------
# Set sources
# ---------------------------------------------------------------------------------------
set(TYTS_SOURCE_DIRS "${CMAKE_CURRENT_LIST_DIR}/../src")

file(GLOB TYTS_TOP_SOURCES ${TYTS_SOURCE_DIRS}/*.cpp)

set(TYTS_SOURCE_FILES
    ${TYTS_TOP_SOURCES})