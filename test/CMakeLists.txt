#
# Copyright (C) 2018 Dr. Michael Steffens
#
# SPDX-License-Identifier:	BSL-1.0
#

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_executable (vectorTest vectorTest.cpp)
add_executable (listTest listTest.cpp)
add_executable (mapTest mapTest.cpp)
add_executable (multimapTest multimapTest.cpp)
add_executable (unorderedMapTest unorderedMapTest.cpp)
add_executable (unorderedMultimapTest unorderedMultimapTest.cpp)
add_executable (setTest setTest.cpp)
