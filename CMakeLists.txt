# This is a boilerplate template for etsi-qkd-004.
# See the LICENSE file for the software license.
# (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com

project(etsi-qkd-004 C CXX)
cmake_minimum_required(VERSION 3.9.1)

cmake_policy(SET CMP0057 NEW)
if (CMAKE_VERSION VERSION_EQUAL "3.12.0" OR CMAKE_VERSION VERSION_GREATER "3.12.0")
    cmake_policy(SET CMP0075 NEW)
endif (CMAKE_VERSION VERSION_EQUAL "3.12.0" OR CMAKE_VERSION VERSION_GREATER "3.12.0")

enable_testing()

include(CheckIncludeFile)
include(CheckIncludeFileCXX)
include(CheckIncludeFiles)
include(CheckLibraryExists)
include(FindPkgConfig)

set(VERSION "0.1")
add_definitions(-DVERSION=\"${VERSION}\")
add_definitions(-D_DEFAULT_SOURCE)

if (CMAKE_BUILD_TYPE STREQUAL "")
    set(CMAKE_BUILD_TYPE "Debug")
endif (CMAKE_BUILD_TYPE STREQUAL "")
message(STATUS "CMake build type: ${CMAKE_BUILD_TYPE}")

set(CMAKE_CXX_STANDARD 17)
if (CMAKE_COMPILER_IS_GNUCC)
    set(GCC_WARNINGS "-Wall -Wextra -pedantic -pedantic-errors")
    if (NOT (CMAKE_BUILD_TYPE STREQUAL "Debug"))
        set(GCC_WARNINGS "-Werror ${GCC_WARNINGS}")
    endif (NOT (CMAKE_BUILD_TYPE STREQUAL "Debug"))
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${GCC_WARNINGS} -rdynamic -fPIC")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_WARNINGS} -rdynamic -fPIC")
endif (CMAKE_COMPILER_IS_GNUCC)

check_include_file(stdio.h HAVE_STDIO_H)
check_include_file(stddef.h HAVE_STDDEF_H)
check_include_file(stdlib.h HAVE_STDLIB_H)
check_include_file(inttypes.h HAVE_INTTYPES_H)
check_include_file(memory.h HAVE_MEMORY_H)
check_include_file(string.h HAVE_STRING_H)
check_include_file(unistd.h HAVE_UNISTD_H)
check_include_file(sys/time.h HAVE_SYS_TIME_H)
check_include_file(time.h HAVE_TIME_H)
check_include_file(math.h HAVE_MATH_H)
check_include_file(stdbool.h HAVE_STDBOOL_H)
check_include_file(endian.h HAVE_ENDIAN_H)
check_include_file(math.h HAVE_MATH_H)
check_include_file(assert.h HAVE_ASSERT_H)
check_include_file(errno.h HAVE_ERRNO_H)
check_include_file(limits.h HAVE_LIMITS_H)

# ------------------------------------------------------------

find_package(Boost 1.65.0 COMPONENTS program_options)
if (Boost_FOUND)
    set(CMAKE_REQUIRED_LIBRARIES "${Boost_LIBRARIES};${CMAKE_REQUIRED_LIBRARIES}")
    include_directories(${Boost_INCLUDE_DIRS})
    set(HAVE_BOOST_LIB 1)
else (Boost_FOUND)
    message(FATAL_ERROR "Boost >= 1.65.0 library not found.")
endif (Boost_FOUND)

# TODO: is there any FindUUID cmake officialy available?
check_include_file(uuid/uuid.h HAVE_UUID_UUID_H)
check_library_exists(uuid uuid_generate "/usr/local/lib;/usr/lib;/lib" HAVE_UUID_LIB)
if (HAVE_UUID_LIB)
    set(CMAKE_REQUIRED_LIBRARIES "uuid;${CMAKE_REQUIRED_LIBRARIES}")
else (HAVE_UUID_LIB)
    message(FATAL_ERROR "Could not find uuid implementation.")
endif (HAVE_UUID_LIB)

# TODO: is there any FindUV cmake officialy available?
check_include_file(uv.h HAVE_UV_H)
check_library_exists(uv uv_version "/usr/local/lib;/usr/lib;/lib" HAVE_UV_LIB)
if (HAVE_UV_LIB)
    set(CMAKE_REQUIRED_LIBRARIES "uv;${CMAKE_REQUIRED_LIBRARIES}")
else (HAVE_UV_LIB)
    message(FATAL_ERROR "Could not find uv implementation.")
endif (HAVE_UV_LIB)

find_package(GTest REQUIRED)


# ------------------------------------------------------------

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/config.h.in ${CMAKE_CURRENT_BINARY_DIR}/config.h)

add_subdirectory(lib)
add_subdirectory(bin)
add_subdirectory(test)

# ------------------------------------------------------------

# set(CPACK_PACKAGE_NAME "etsi-qkd-004")
#
# set(CPACK_PACKAGE_DESCRIPTION "ETSI QKD 004 implementation")
# set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "This is the package is an implementation of the ETSI QKD 004 standard.")
# set(CPACK_PACKAGE_CONTACT "Oliver Maurhart <dyle71@gmail.com>")
# set(CPACK_PACKAGE_VENDOR "Oliver Maurhart")
# set(CPACK_PACKAGE_VERSION_MAJOR "0")
# set(CPACK_PACKAGE_VERSION_MINOR "1")
# set(CPACK_PACKAGE_VERSION_PATCH "0")
# set(CPACK_PROJECT_VERSION_STRING "${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR}.${CPACK_PACKAGE_VERSION_PATCH}" )
#
# set(CPACK_GENERATOR "DEB;RPM;")
# set(CPACK_SOURCE_GENERATOR "TGZ")
#
# set(CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR}-${CMAKE_SYSTEM_PROCESSOR}")
# set(CPACK_SOURCE_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR}")
# set(CPACK_SOURCE_IGNORE_FILES "/build/*;/.git/")
#
# set(CPACK_DEBIAN_PACKAGE_DEPENDS "libc6 (>= 2.13), libgcc1 (>= 1:4.4)")
# set(CPACK_DEBIAN_PACKAGE_CONTROL_EXTRA "${CMAKE_CURRENT_SOURCE_DIR}/cmake/cpack/deb/control/postinst;${CMAKE_CURRENT_SOURCE_DIR}/cmake/cpack/deb/control/postrm;${CMAKE_CURRENT_SOURCE_DIR}/cmake/cpack/deb/control/prerm;")
#
# # debianization
# string(TOLOWER "${CPACK_PACKAGE_NAME}" CPACK_PACKAGE_NAME_LOWERCASE)
# find_program(DPKG_PROGRAM dpkg DOC "dpkg program of Debian-based systems")
# if (DPKG_PROGRAM)
#     # use dpkg to fix the package file setName
#     execute_process(
#         COMMAND ${DPKG_PROGRAM} --print-architecture
#         OUTPUT_VARIABLE CPACK_DEBIAN_PACKAGE_ARCHITECTURE
#         OUTPUT_STRIP_TRAILING_WHITESPACE
#     )
#     set(CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME_LOWERCASE}_${CPACK_PROJECT_VERSION_STRING}_${CPACK_DEBIAN_PACKAGE_ARCHITECTURE}")
# else (DPKG_PROGRAM)
#     set(CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME_LOWERCASE}_${CPACK_PROJECT_VERSION_STRING}_${CMAKE_SYSTEM_NAME}")
# endif (DPKG_PROGRAM)
#
# # package it
# include(CPack)

