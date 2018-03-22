//
// Copyright (C) 2018 Dr. Michael Steffens
//
// SPDX-License-Identifier:		BSL-1.0
//


#include "Polymorphic/Multimap.h"
#include "Testee/MapTestSuite.h"
#include <iostream>

#ifndef TESTEE_MULTIMAP_TYPE
#define TESTEE_MULTIMAP_TYPE Polymorphic::Multimap
#endif

int main(int args, char* argv[])
{
	std::cout << "Testing C++-11 standard multimap interface ..." << std::endl;
	return Testee::MapTestSuite<TESTEE_MULTIMAP_TYPE, int, int, true>().run() ? 0 : 1;
}

namespace Testee {
template const MapTestSuite<TESTEE_MULTIMAP_TYPE, int, int, true>::InitializerListType MapTestSuite<TESTEE_MULTIMAP_TYPE, int, int, true>::INITIALIZER_LIST;
template const MapTestSuite<TESTEE_MULTIMAP_TYPE, int, int, true>::ArrayType MapTestSuite<TESTEE_MULTIMAP_TYPE, int, int, true>::ARRAY;
} // namespace Testee
