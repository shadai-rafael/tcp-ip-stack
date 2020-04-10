cmake_minimum_required(VERSION 3.10.2)
project(directory_test)
set(CMAKE_BUILD_TYPE Release)

FIND_PACKAGE(PkgConfig)
PKG_CHECK_MODULES(GLIB glib-2.0)

include_directories(${GLIB_INCLUDE_DIRS})
link_directories(${GLIB_LIBRARY_DIRS})
add_definitions(${GLIB_CFLAGS_OTHER})

#Bring the headers, such as Student.h into the project
include_directories(inc)

#However, the file(GLOB...) allows for wildcard additions:
file(GLOB SOURCES "src/*.c")

#Generate the static library from the sources
add_library(graph STATIC ${SOURCES})