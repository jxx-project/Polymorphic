//
// Copyright (C) 2018 Dr. Michael Steffens
//
// SPDX-License-Identifier:		BSL-1.0
//


#include "Polymorphic/List.h"
#include "Testee/ListTestSuite.h"
#include <iostream>

#ifndef TESTEE_LIST_TYPE
#define TESTEE_LIST_TYPE Polymorphic::List
#endif

int main(int args, char* argv[])
{
	std::cout << "Testing C++-11 standard list interface ..." << std::endl;
	return Testee::ListTestSuite<TESTEE_LIST_TYPE, int>().run() ? 0 : 1;
}
