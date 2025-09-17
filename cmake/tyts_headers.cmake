# ---------------------------------------------------------------------------------------
# Set headers
# ---------------------------------------------------------------------------------------
set(TYTS_INCLUDE_DIRS "${CMAKE_CURRENT_LIST_DIR}/../include")

file(GLOB TYTS_TOP_HEADERS ${TYTS_INCLUDE_DIRS}/tyts/*.h)

set(TYTS_HEADER_FILES
    ${TYTS_TOP_HEADERS})