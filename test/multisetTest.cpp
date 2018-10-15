//
// Copyright (C) 2018 Dr. Michael Steffens
//
// SPDX-License-Identifier:	BSL-1.0
//


#include "Polymorphic/Multiset.h"
#include "Testee/SetTestSuite.h"
#include <iostream>

int main(int args, char* argv[])
{
	return Testee::SetTestSuite<Polymorphic::Multiset, int, true>("Polymorphic::Multiset<int>").run() ? 0 : 1;
}
