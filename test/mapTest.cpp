//
// Copyright (C) 2018 Dr. Michael Steffens
//
// SPDX-License-Identifier:		BSL-1.0
//


#include "StdMapTestSuite.h"
#include <iostream>
#include <map>

template const StdMapTestSuite<std::map, int, int>::InitializerListType StdMapTestSuite<std::map, int, int>::INITIALIZER_LIST;
template const StdMapTestSuite<std::map, int, int>::ArrayType StdMapTestSuite<std::map, int, int>::ARRAY;

int main(int args, char* argv[])
{
	std::cout << "Testing C++-11 standard map interface ..." << std::endl;
	return StdMapTestSuite<std::map, int, int>().run() ? 0 : 1;
}
