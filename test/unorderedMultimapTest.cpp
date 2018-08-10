//
// Copyright (C) 2018 Dr. Michael Steffens
//
// SPDX-License-Identifier:	BSL-1.0
//


#include "Polymorphic/UnorderedMultimap.h"
#include "Testee/UnorderedMapTestSuite.h"
#include <iostream>

int main(int args, char* argv[])
{
	return Testee::UnorderedMapTestSuite<Polymorphic::UnorderedMultimap, int, int, true>("Polymorphic::UnorderedMultimap<int, int>")
				   .run() ?
			   0 :
			   1;
}
