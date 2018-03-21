//
// Copyright (C) 2018 Dr. Michael Steffens
//
// SPDX-License-Identifier:		BSL-1.0
//


#include "Polymorphic/Map.h"
#include "StdMapTestSuite.h"
#include <iostream>

template const StdMapTestSuite<Polymorphic::Map, int, int>::InitializerListType StdMapTestSuite<Polymorphic::Map, int, int>::INITIALIZER_LIST;
template const StdMapTestSuite<Polymorphic::Map, int, int>::ArrayType StdMapTestSuite<Polymorphic::Map, int, int>::ARRAY;

int main(int args, char* argv[])
{
	std::cout << "Testing C++-11 standard map interface ..." << std::endl;
	return StdMapTestSuite<Polymorphic::Map, int, int>().run() ? 0 : 1;
}
