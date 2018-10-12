//
// Copyright (C) 2018 Dr. Michael Steffens
//
// SPDX-License-Identifier:	BSL-1.0
//


#ifndef TestSuite_INCLUDED
#define TestSuite_INCLUDED

#include "TestCase.h"
#include <iostream>
#include <list>
#include <string>

namespace Testee {

class TestSuite
{
public:
	TestSuite(const std::string& subject, std::list<TestCase>&& testCases) : subject(subject), testCases(std::move(testCases))
	{
	}

	virtual bool run()
	{
		unsigned int passed = 0;
		unsigned int failed = 0;
		std::cout << "Testing " << subject << " ..." << std::endl;
		for (auto& testCase : testCases) {
			try {
				testCase.run();
				++passed;
			} catch (std::runtime_error& e) {
				std::cerr << e.what() << std::endl;
				++failed;
			}
		}
		std::cout << "... passed: " << passed << ", failed: " << failed << std::endl;
		return failed == 0;
	}

protected:
	std::string subject;
	std::list<TestCase> testCases;
};

} // namespace Testee

#endif // TestSuite_INCLUDED
