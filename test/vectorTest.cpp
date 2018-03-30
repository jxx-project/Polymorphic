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
	bool failed = false;
	failed = !Testee::VectorTestSuite<Polymorphic::Vector, int>("Polymorphic::Vector<int>").run() || failed;
	failed = !Testee::VectorTestSuite<Polymorphic::Vector, bool>("Polymorphic::Vector<bool>").run() || failed;
	return failed ? 1 : 0;
}
