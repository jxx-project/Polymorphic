//
// Copyright (C) 2018 Dr. Michael Steffens
//
// SPDX-License-Identifier:	BSL-1.0
//


#include "Polymorphic/UnorderedSet.h"
#include "Testee/UnorderedSetTestSuite.h"
#include <iostream>

int main(int args, char* argv[])
{
	return Testee::UnorderedSetTestSuite<Polymorphic::UnorderedSet, int>("Polymorphic::UnorderedSet<int>").run() ? 0 : 1;
}
