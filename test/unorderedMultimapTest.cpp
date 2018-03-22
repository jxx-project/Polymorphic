//
// Copyright (C) 2018 Dr. Michael Steffens
//
// SPDX-License-Identifier:		BSL-1.0
//


#include "Polymorphic/UnorderedMultimap.h"
#include "Testee/UnorderedMapTestSuite.h"
#include <iostream>

#ifndef TESTEE_UNORDERED_MULTIMAP_TYPE
#define TESTEE_UNORDERED_MULTIMAP_TYPE Polymorphic::UnorderedMultimap
#endif

int main(int args, char* argv[])
{
	std::cout << "Testing C++-11 standard unordered_multimap interface ..." << std::endl;
	return Testee::UnorderedMapTestSuite<TESTEE_UNORDERED_MULTIMAP_TYPE, int, int, true>().run() ? 0 : 1;
}

namespace Testee {
template const UnorderedMapTestSuite<TESTEE_UNORDERED_MULTIMAP_TYPE, int, int, true>::InitializerListType UnorderedMapTestSuite<TESTEE_UNORDERED_MULTIMAP_TYPE, int, int, true>::INITIALIZER_LIST;
template const UnorderedMapTestSuite<TESTEE_UNORDERED_MULTIMAP_TYPE, int, int, true>::ArrayType UnorderedMapTestSuite<TESTEE_UNORDERED_MULTIMAP_TYPE, int, int, true>::ARRAY;
} // namespace Testee
