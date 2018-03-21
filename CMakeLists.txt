#
# Copyright (C) 2018 Dr. Michael Steffens
#
# SPDX-License-Identifier:     BSL-1.0
#

project(Polymorphic CXX)
cmake_minimum_required(VERSION 3.0)

set(JXXON_MAJOR_VERSION 0)
set(JXXON_MINOR_VERSION 1)
set(JXXON_PATCH_VERSION 0)
set(JXXON_VERSION ${JXXON_MAJOR_VERSION}.${JXXON_MINOR_VERSION}.${JXXON_PATCH_VERSION})

install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/ DESTINATION include) 

if(CMAKE_COMPILER_IS_GNUCXX)
	set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -std=c++11)
endif()

include_directories(include)

add_subdirectory(test)

enable_testing()
add_test(NAME VectorTest COMMAND vectorTest)
add_test(NAME ListTest COMMAND listTest)
add_test(NAME MapTest COMMAND mapTest)
add_test(NAME MultimapTest COMMAND multimapTest)
add_test(NAME UnorderedMapTest COMMAND unorderedMapTest)
add_test(NAME UnorderedMultimapTest COMMAND unorderedMultimapTest)
