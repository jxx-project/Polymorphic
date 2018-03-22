//
// Copyright (C) 2018 Dr. Michael Steffens
//
// SPDX-License-Identifier:		BSL-1.0
//


#ifndef TestCase_INCLUDED
#define TestCase_INCLUDED

#include <functional>
#include <stdexcept>

namespace Testee {

class TestCase
{
public:
	TestCase(const std::string& name, const std::function<void(void)>& runner) : name(name), runner(runner)
	{
	}

	void run()
	{
		try {
			runner();
		} catch (std::runtime_error& e) {
			std::string comment(e.what());
			throw std::runtime_error("Test case \"" + name + "\" failed." + (comment.empty() ?	"" : " // " + comment));
		}
	}

	static void assert(bool succeeded, const char* comment = "")
	{
		if (!succeeded) {
			throw std::runtime_error(comment);
		}
	}

private:
	std::string name;
	std::function<void(void)> runner;
};

} // namespace Testee

#endif // TestCase_INCLUDED
