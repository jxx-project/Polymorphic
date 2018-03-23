//
// Copyright (C) 2018 Dr. Michael Steffens
//
// SPDX-License-Identifier:		BSL-1.0
//


#include "Polymorphic/List.h"
#include "Testee/ListTestSuite.h"
#include <iostream>

int main(int args, char* argv[])
{
	std::cout << "Testing C++-11 standard list interface ..." << std::endl;
	return Testee::ListTestSuite<Polymorphic::List, int>().run() ? 0 : 1;
}
