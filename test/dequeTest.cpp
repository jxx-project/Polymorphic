//
// Copyright (C) 2018 Dr. Michael Steffens
//
// SPDX-License-Identifier:	BSL-1.0
//


#include "Polymorphic/Deque.h"
#include "Testee/DequeTestSuite.h"
#include <iostream>

int main(int args, char* argv[])
{
	return Testee::DequeTestSuite<Polymorphic::Deque, int>("Polymorphic::Deque<int>").run() ? 0 : 1;
}
