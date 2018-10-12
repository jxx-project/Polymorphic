//
// Copyright (C) 2018 Dr. Michael Steffens
//
// SPDX-License-Identifier:	BSL-1.0
//


#include "Polymorphic/Set.h"
#include "Testee/SetTestSuite.h"
#include <iostream>

int main(int args, char* argv[])
{
	return Testee::SetTestSuite<Polymorphic::Set, int>("Polymorphic::Set<int>").run() ? 0 : 1;
}
