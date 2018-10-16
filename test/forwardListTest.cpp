//
// Copyright (C) 2018 Dr. Michael Steffens
//
// SPDX-License-Identifier:	BSL-1.0
//


#include "Polymorphic/ForwardList.h"
#include "Testee/ForwardListTestSuite.h"
#include <iostream>

int main(int args, char* argv[])
{
	return Testee::ForwardListTestSuite<Polymorphic::ForwardList, int>("Polymorphic::ForwardList<int>").run() ? 0 : 1;
}
