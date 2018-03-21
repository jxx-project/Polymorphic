//
// Copyright (C) 2018 Dr. Michael Steffens
//
// SPDX-License-Identifier:		BSL-1.0
//


#include "StdUnorderedMapTestSuite.h"
#include <iostream>
#include <unordered_map>

template const StdUnorderedMapTestSuite<std::unordered_map, int, int>::InitializerListType StdUnorderedMapTestSuite<std::unordered_map, int, int>::INITIALIZER_LIST;
template const StdUnorderedMapTestSuite<std::unordered_map, int, int>::ArrayType StdUnorderedMapTestSuite<std::unordered_map, int, int>::ARRAY;

int main(int args, char* argv[])
{
	std::cout << "Testing C++-11 standard unordered_map interface ..." << std::endl;
	return StdUnorderedMapTestSuite<std::unordered_map, int, int>().run() ? 0 : 1;
}
