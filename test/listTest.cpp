//
// Copyright (C) 2018 Dr. Michael Steffens
//
// SPDX-License-Identifier:		BSL-1.0
//


#include "StdListTestSuite.h"
#include <iostream>
#include <list>

int main(int args, char* argv[])
{
	std::cout << "Testing C++-11 standard list interface ..." << std::endl;
	return StdListTestSuite<std::list, int>().run() ? 0 : 1;
}
