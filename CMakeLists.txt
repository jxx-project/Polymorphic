#
# Copyright (C) 2018 Dr. Michael Steffens
#
# SPDX-License-Identifier:     BSL-1.0
#

cmake_minimum_required(VERSION 3.0)
project(Polymorphic VERSION 0.1.0 LANGUAGES CXX)
include(GNUInstallDirs)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS NO)

add_library(polymorphic INTERFACE)
add_library(Polymorphic::Polymorphic ALIAS polymorphic)

target_include_directories(polymorphic INTERFACE
	$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
	$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/test>
	$<INSTALL_INTERFACE:include>)

install(TARGETS polymorphic EXPORT PolymorphicConfig)
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR} FILES_MATCHING PATTERN "*.h")
install(EXPORT PolymorphicConfig DESTINATION share/Polymorphic/cmake)
export(TARGETS polymorphic FILE PolymorphicConfig.cmake)

enable_testing()

# On demand build of tests. See https://cmake.org/Wiki/CMakeEmulateMakeCheck
if(NOT "${CMAKE_GENERATOR}" MATCHES "Visual Studio")
	add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND} --force-new-ctest-process)
else()
	add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND} --force-new-ctest-process -C $(Configuration))
endif()

add_executable(vectorTest EXCLUDE_FROM_ALL test/vectorTest.cpp)
target_link_libraries(vectorTest polymorphic)
add_test(NAME VectorTest COMMAND vectorTest)
add_dependencies(check vectorTest)

add_executable(listTest EXCLUDE_FROM_ALL test/listTest.cpp)
target_link_libraries(listTest polymorphic)
add_test(NAME ListTest COMMAND listTest)
add_dependencies(check listTest)

add_executable(mapTest EXCLUDE_FROM_ALL test/mapTest.cpp)
target_link_libraries(mapTest polymorphic)
add_test(NAME MapTest COMMAND mapTest)
add_dependencies(check mapTest)

add_executable(multimapTest EXCLUDE_FROM_ALL test/multimapTest.cpp)
target_link_libraries(multimapTest polymorphic)
add_test(NAME MultimapTest COMMAND multimapTest)
add_dependencies(check multimapTest)

add_executable(unorderedMapTest EXCLUDE_FROM_ALL test/unorderedMapTest.cpp)
target_link_libraries(unorderedMapTest polymorphic)
add_test(NAME UnorderedMapTest COMMAND unorderedMapTest)
add_dependencies(check unorderedMapTest)

add_executable(unorderedMultimapTest EXCLUDE_FROM_ALL test/unorderedMultimapTest.cpp)
target_link_libraries(unorderedMultimapTest polymorphic)
add_test(NAME UnorderedMultimapTest COMMAND unorderedMultimapTest)
add_dependencies(check unorderedMultimapTest)
