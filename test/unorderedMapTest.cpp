//
// Copyright (C) 2018 Dr. Michael Steffens
//
// SPDX-License-Identifier:	BSL-1.0
//


#include "Polymorphic/UnorderedMap.h"
#include "Testee/UnorderedMapTestSuite.h"
#include <iostream>

int main(int args, char* argv[])
{
	return Testee::UnorderedMapTestSuite<Polymorphic::UnorderedMap, int, int>("Polymorphic::UnorderedMap<int, int>").run() ? 0 : 1;
}
