//
// Copyright (C) 2018 Dr. Michael Steffens
//
// SPDX-License-Identifier:	BSL-1.0
//


#include "Polymorphic/Multimap.h"
#include "Testee/MapTestSuite.h"
#include <iostream>

int main(int args, char* argv[])
{
	return Testee::MapTestSuite<Polymorphic::Multimap, int, int, true>("Polymorphic::Multimap<int, int>").run() ? 0 : 1;
}
