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

