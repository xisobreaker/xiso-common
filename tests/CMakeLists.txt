include_directories(${GTEST_INCLUDE_DIRS})

include_directories(${PROJECT_SOURCE_DIR}/src)

set(TEST_UNITCASE 
    test_byteutils.cpp
    test_configure.cpp
    test_threadpool.cpp
    test_timestamp.cpp
)

set(TEST_SOURCE_FILES   tests.cpp
                        gtest_envir.cpp
                        ${TEST_UNITCASE})

add_executable(xiso_common_tests ${TEST_SOURCE_FILES})
target_link_libraries(xiso_common_tests ${GTEST_LIBRARIES})
target_link_libraries(xiso_common_tests xiso_common)
gtest_discover_tests(xiso_common_tests)
