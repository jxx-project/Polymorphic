#
# Copyright (C) 2018 Dr. Michael Steffens
#
# SPDX-License-Identifier:	BSL-1.0
#

cmake_minimum_required(VERSION 3.0)
project(Polymorphic VERSION 1.1.0 LANGUAGES CXX)
include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS NO)

add_library(Containers INTERFACE)
add_library(${PROJECT_NAME}::Containers ALIAS Containers)

target_include_directories(Containers INTERFACE
	$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
	$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/test>
	$<INSTALL_INTERFACE:include>)

install(TARGETS Containers EXPORT PolymorphicTargets)
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR} FILES_MATCHING PATTERN "*.h")
install(EXPORT PolymorphicTargets NAMESPACE ${PROJECT_NAME}:: DESTINATION share/Polymorphic/cmake)
configure_file(cmake/PolymorphicConfig.cmake.in PolymorphicConfig.cmake @ONLY)
write_basic_package_version_file(${CMAKE_CURRENT_BINARY_DIR}/PolymorphicConfigVersion.cmake COMPATIBILITY SameMajorVersion)
install(FILES
	${CMAKE_CURRENT_BINARY_DIR}/PolymorphicConfig.cmake
	${CMAKE_CURRENT_BINARY_DIR}/PolymorphicConfigVersion.cmake
	DESTINATION share/Polymorphic/cmake)

enable_testing()

# On demand build of tests. See https://cmake.org/Wiki/CMakeEmulateMakeCheck
if(NOT "${CMAKE_GENERATOR}" MATCHES "Visual Studio")
	add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND} --force-new-ctest-process)
else()
	add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND} --force-new-ctest-process -C $(Configuration))
endif()

add_executable(vectorTest EXCLUDE_FROM_ALL test/vectorTest.cpp)
target_link_libraries(vectorTest ${PROJECT_NAME}::Containers)
add_test(NAME VectorTest COMMAND vectorTest)
add_dependencies(check vectorTest)

add_executable(listTest EXCLUDE_FROM_ALL test/listTest.cpp)
target_link_libraries(listTest ${PROJECT_NAME}::Containers)
add_test(NAME ListTest COMMAND listTest)
add_dependencies(check listTest)

add_executable(mapTest EXCLUDE_FROM_ALL test/mapTest.cpp)
target_link_libraries(mapTest ${PROJECT_NAME}::Containers)
add_test(NAME MapTest COMMAND mapTest)
add_dependencies(check mapTest)

add_executable(multimapTest EXCLUDE_FROM_ALL test/multimapTest.cpp)
target_link_libraries(multimapTest ${PROJECT_NAME}::Containers)
add_test(NAME MultimapTest COMMAND multimapTest)
add_dependencies(check multimapTest)

add_executable(unorderedMapTest EXCLUDE_FROM_ALL test/unorderedMapTest.cpp)
target_link_libraries(unorderedMapTest ${PROJECT_NAME}::Containers)
add_test(NAME UnorderedMapTest COMMAND unorderedMapTest)
add_dependencies(check unorderedMapTest)

add_executable(unorderedMultimapTest EXCLUDE_FROM_ALL test/unorderedMultimapTest.cpp)
target_link_libraries(unorderedMultimapTest ${PROJECT_NAME}::Containers)
add_test(NAME UnorderedMultimapTest COMMAND unorderedMultimapTest)
add_dependencies(check unorderedMultimapTest)

add_executable(setTest EXCLUDE_FROM_ALL test/setTest.cpp)
target_link_libraries(setTest ${PROJECT_NAME}::Containers)
add_test(NAME SetTest COMMAND setTest)
add_dependencies(check setTest)
