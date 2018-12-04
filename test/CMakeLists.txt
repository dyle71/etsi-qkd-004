# This file is part of etsi-qkd-004.
# See the LICENSE file for the software license.
# (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com

include_directories(${CMAKE_SOURCE_DIR}/include ${CMAKE_BINARY_DIR})

set(TEST_SRC
    test_qkdlkms.cpp
)

add_executable(qkdlkms-test ${TEST_SRC})
target_link_libraries(qkdlkms-test gtest gtest_main pthread qkdlkms ${CMAKE_REQUIRED_LIBRARIES})
gtest_add_tests(TARGET qkdlkms-test  WORKING_DIRECTORY ${CMAKE_BINARY_DIR})

