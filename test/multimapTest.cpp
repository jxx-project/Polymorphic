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
	std::cout << "Testing C++11 standard multimap interface ..." << std::endl;
	return Testee::MapTestSuite<Polymorphic::Multimap, int, int, true>().run() ? 0 : 1;
}