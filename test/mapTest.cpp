//
// Copyright (C) 2018 Dr. Michael Steffens
//
// SPDX-License-Identifier:		BSL-1.0
//


#include "Polymorphic/Map.h"
#include "Testee/MapTestSuite.h"
#include <iostream>

#ifndef TESTEE_MAP_TYPE
#define TESTEE_MAP_TYPE Polymorphic::Map
#endif

int main(int args, char* argv[])
{
	std::cout << "Testing C++-11 standard map interface ..." << std::endl;
	return Testee::MapTestSuite<TESTEE_MAP_TYPE, int, int>().run() ? 0 : 1;
}

namespace Testee {
template const MapTestSuite<TESTEE_MAP_TYPE, int, int>::InitializerListType MapTestSuite<TESTEE_MAP_TYPE, int, int>::INITIALIZER_LIST;
template const MapTestSuite<TESTEE_MAP_TYPE, int, int>::ArrayType MapTestSuite<TESTEE_MAP_TYPE, int, int>::ARRAY;
} // namespace Testee
