//
// Copyright (C) 2018 Dr. Michael Steffens
//
// SPDX-License-Identifier:	BSL-1.0
//


#include "Polymorphic/Map.h"
#include "Testee/MapTestSuite.h"
#include <iostream>

int main(int args, char* argv[])
{
	return Testee::MapTestSuite<Polymorphic::Map, int, int>("Polymorphic::Map<int, int>").run() ? 0 : 1;
}
