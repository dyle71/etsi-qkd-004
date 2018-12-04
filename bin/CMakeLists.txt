# This file is part of etsi-qkd-004.
# See the LICENSE file for the software license.
# (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com


include_directories(${CMAKE_SOURCE_DIR}/include ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR})

set(QKD_LKMS
    main.cpp
)

add_executable(qkd-lkmsd ${QKD_LKMS})
target_link_libraries(qkd-lkmsd qkdlkms ${CMAKE_REQUIRED_LIBRARIES})
install(TARGETS qkd-lkmsd RUNTIME DESTINATION bin)

