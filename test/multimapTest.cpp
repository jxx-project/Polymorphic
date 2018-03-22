//
// Copyright (C) 2018 Dr. Michael Steffens
//
// SPDX-License-Identifier:		BSL-1.0
//


#include "Polymorphic/Multimap.h"
#include "Testee/MapTestSuite.h"
#include <iostream>

int main(int args, char* argv[])
{
	std::cout << "Testing C++-11 standard multimap interface ..." << std::endl;
	return Testee::MapTestSuite<Polymorphic::Multimap, int, int, true>().run() ? 0 : 1;
}

namespace Testee {
template const MapTestSuite<Polymorphic::Multimap, int, int, true>::InitializerListType MapTestSuite<Polymorphic::Multimap, int, int, true>::INITIALIZER_LIST;
template const MapTestSuite<Polymorphic::Multimap, int, int, true>::ArrayType MapTestSuite<Polymorphic::Multimap, int, int, true>::ARRAY;
} // namespace Testee
