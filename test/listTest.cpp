//
// Copyright (C) 2018 Dr. Michael Steffens
//
// SPDX-License-Identifier:	BSL-1.0
//


#include "Polymorphic/List.h"
#include "Testee/ListTestSuite.h"
#include <iostream>

int main(int args, char* argv[])
{
	return Testee::ListTestSuite<Polymorphic::List, int>("Polymorphic::List<int>").run() ? 0 : 1;
}
