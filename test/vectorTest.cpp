//
// Copyright (C) 2018 Dr. Michael Steffens
//
// SPDX-License-Identifier:		BSL-1.0
//


#include "Polymorphic/Vector.h"
#include "Testee/VectorTestSuite.h"
#include <iostream>

int main(int args, char* argv[])
{
	std::cout << "Testing C++-11 standard vector interface ..." << std::endl;
	auto vectorPassed = Testee::VectorTestSuite<Polymorphic::Vector, int>().run();
	std::cout << "Testing C++-11 standard vector<bool> interface ..." << std::endl;
	auto vectorBoolPassed = Testee::VectorTestSuite<Polymorphic::Vector, bool>().run();
	return vectorPassed && vectorBoolPassed ? 0 : 1;
}
