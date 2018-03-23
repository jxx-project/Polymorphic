//
// Copyright (C) 2018 Dr. Michael Steffens
//
// SPDX-License-Identifier:		BSL-1.0
//


#include "Polymorphic/UnorderedMap.h"
#include "Testee/UnorderedMapTestSuite.h"
#include <iostream>

int main(int args, char* argv[])
{
	std::cout << "Testing C++-11 standard unordered_map interface ..." << std::endl;
	return Testee::UnorderedMapTestSuite<Polymorphic::UnorderedMap, int, int>().run() ? 0 : 1;
}