//
// Copyright (C) 2018 Dr. Michael Steffens
//
// SPDX-License-Identifier:		BSL-1.0
//


#include "StdMapTestSuite.h"
#include <iostream>
#include <map>

template const StdMapTestSuite<std::multimap, int, int, true>::InitializerListType StdMapTestSuite<std::multimap, int, int, true>::INITIALIZER_LIST;
template const StdMapTestSuite<std::multimap, int, int, true>::ArrayType StdMapTestSuite<std::multimap, int, int, true>::ARRAY;

int main(int args, char* argv[])
{
	std::cout << "Testing C++-11 standard multimap interface ..." << std::endl;
	return StdMapTestSuite<std::multimap, int, int, true>().run() ? 0 : 1;
}
