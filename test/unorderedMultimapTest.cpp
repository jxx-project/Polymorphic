//
// Copyright (C) 2018 Dr. Michael Steffens
//
// SPDX-License-Identifier:		BSL-1.0
//


#include "Polymorphic/UnorderedMultimap.h"
#include "StdUnorderedMapTestSuite.h"
#include <iostream>

template const StdUnorderedMapTestSuite<Polymorphic::UnorderedMultimap, int, int, true>::InitializerListType StdUnorderedMapTestSuite<Polymorphic::UnorderedMultimap, int, int, true>::INITIALIZER_LIST;
template const StdUnorderedMapTestSuite<Polymorphic::UnorderedMultimap, int, int, true>::ArrayType StdUnorderedMapTestSuite<Polymorphic::UnorderedMultimap, int, int, true>::ARRAY;

int main(int args, char* argv[])
{
	std::cout << "Testing C++-11 standard unordered_multimap interface ..." << std::endl;
	return StdUnorderedMapTestSuite<Polymorphic::UnorderedMultimap, int, int, true>().run() ? 0 : 1;
}
