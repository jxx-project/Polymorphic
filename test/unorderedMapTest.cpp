//
// Copyright (C) 2018 Dr. Michael Steffens
//
// SPDX-License-Identifier:		BSL-1.0
//


#include "Polymorphic/UnorderedMap.h"
#include "StdUnorderedMapTestSuite.h"
#include <iostream>

template const StdUnorderedMapTestSuite<Polymorphic::UnorderedMap, int, int>::InitializerListType StdUnorderedMapTestSuite<Polymorphic::UnorderedMap, int, int>::INITIALIZER_LIST;
template const StdUnorderedMapTestSuite<Polymorphic::UnorderedMap, int, int>::ArrayType StdUnorderedMapTestSuite<Polymorphic::UnorderedMap, int, int>::ARRAY;

int main(int args, char* argv[])
{
	std::cout << "Testing C++-11 standard unordered_map interface ..." << std::endl;
	return StdUnorderedMapTestSuite<Polymorphic::UnorderedMap, int, int>().run() ? 0 : 1;
}
