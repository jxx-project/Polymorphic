//
// Copyright (C) 2018 Dr. Michael Steffens
//
// SPDX-License-Identifier:		BSL-1.0
//


#include "StdUnorderedMapTestSuite.h"
#include <iostream>
#include <unordered_map>

template const StdUnorderedMapTestSuite<std::unordered_multimap, int, int, true>::InitializerListType StdUnorderedMapTestSuite<std::unordered_multimap, int, int, true>::INITIALIZER_LIST;
template const StdUnorderedMapTestSuite<std::unordered_multimap, int, int, true>::ArrayType StdUnorderedMapTestSuite<std::unordered_multimap, int, int, true>::ARRAY;

int main(int args, char* argv[])
{
	std::cout << "Testing C++-11 standard unordered_multimap interface ..." << std::endl;
	return StdUnorderedMapTestSuite<std::unordered_multimap, int, int, true>().run() ? 0 : 1;
}
