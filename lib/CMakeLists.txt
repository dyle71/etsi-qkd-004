# This file is part of etsi-qkd-004.
# See the LICENSE file for the software license.
# (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com

include_directories(${CMAKE_SOURCE_DIR}/include)

set(QKD_LKMS_LIB_SRC
    qkd_lkms.cpp
)

add_library(qkdlkms ${QKD_LKMS_LIB_SRC})
target_link_libraries(qkdlkms ${CMAKE_REQUIRED_LIBRARIES})

