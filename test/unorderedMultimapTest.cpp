//
// Copyright (C) 2018 Dr. Michael Steffens
//
// SPDX-License-Identifier:		BSL-1.0
//


#include "Polymorphic/UnorderedMultimap.h"
#include "Testee/UnorderedMapTestSuite.h"
#include <iostream>

int main(int args, char* argv[])
{
	std::cout << "Testing C++11 standard unordered_multimap interface ..." << std::endl;
	return Testee::UnorderedMapTestSuite<Polymorphic::UnorderedMultimap, int, int, true>().run() ? 0 : 1;
}