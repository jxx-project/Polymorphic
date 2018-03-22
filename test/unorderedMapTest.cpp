//
// Copyright (C) 2018 Dr. Michael Steffens
//
// SPDX-License-Identifier:		BSL-1.0
//


#include "Polymorphic/UnorderedMap.h"
#include "Testee/UnorderedMapTestSuite.h"
#include <iostream>

#ifndef TESTEE_UNORDERED_MAP_TYPE
#define TESTEE_UNORDERED_MAP_TYPE Polymorphic::UnorderedMap
#endif

int main(int args, char* argv[])
{
	std::cout << "Testing C++-11 standard unordered_map interface ..." << std::endl;
	return Testee::UnorderedMapTestSuite<TESTEE_UNORDERED_MAP_TYPE, int, int>().run() ? 0 : 1;
}

namespace Testee {
template const UnorderedMapTestSuite<TESTEE_UNORDERED_MAP_TYPE, int, int>::InitializerListType UnorderedMapTestSuite<TESTEE_UNORDERED_MAP_TYPE, int, int>::INITIALIZER_LIST;
template const UnorderedMapTestSuite<TESTEE_UNORDERED_MAP_TYPE, int, int>::ArrayType UnorderedMapTestSuite<TESTEE_UNORDERED_MAP_TYPE, int, int>::ARRAY;
} // namespace Testee
