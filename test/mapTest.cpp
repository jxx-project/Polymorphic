//
// Copyright (C) 2018 Dr. Michael Steffens
//
// SPDX-License-Identifier:		BSL-1.0
//


#include "Polymorphic/Map.h"
#include "Testee/MapTestSuite.h"
#include <iostream>

int main(int args, char* argv[])
{
	std::cout << "Testing C++-11 standard map interface ..." << std::endl;
	return Testee::MapTestSuite<Polymorphic::Map, int, int>().run() ? 0 : 1;
}

namespace Testee {
template const MapTestSuite<Polymorphic::Map, int, int>::InitializerListType MapTestSuite<Polymorphic::Map, int, int>::INITIALIZER_LIST;
template const MapTestSuite<Polymorphic::Map, int, int>::ArrayType MapTestSuite<Polymorphic::Map, int, int>::ARRAY;
} // namespace Testee
