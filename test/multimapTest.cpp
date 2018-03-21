//
// Copyright (C) 2018 Dr. Michael Steffens
//
// SPDX-License-Identifier:		BSL-1.0
//


#include "Polymorphic/Multimap.h"
#include "StdMapTestSuite.h"
#include <iostream>

template const StdMapTestSuite<Polymorphic::Multimap, int, int, true>::InitializerListType StdMapTestSuite<Polymorphic::Multimap, int, int, true>::INITIALIZER_LIST;
template const StdMapTestSuite<Polymorphic::Multimap, int, int, true>::ArrayType StdMapTestSuite<Polymorphic::Multimap, int, int, true>::ARRAY;

int main(int args, char* argv[])
{
	std::cout << "Testing C++-11 standard multimap interface ..." << std::endl;
	return StdMapTestSuite<Polymorphic::Multimap, int, int, true>().run() ? 0 : 1;
}
