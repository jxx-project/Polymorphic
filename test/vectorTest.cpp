//
// Copyright (C) 2018 Dr. Michael Steffens
//
// SPDX-License-Identifier:		BSL-1.0
//


#include "StdVectorTestSuite.h"
#include <iostream>
#include <vector>

int main(int args, char* argv[])
{
	std::cout << "Testing C++-11 standard vector interface ..." << std::endl;
	auto vectorPassed = StdVectorTestSuite<std::vector, int>().run();
	std::cout << "Testing C++-11 standard vector<bool> interface ..." << std::endl;
	auto vectorBoolPassed = StdVectorTestSuite<std::vector, bool>().run();
	return vectorPassed && vectorBoolPassed ? 0 : 1;
}
