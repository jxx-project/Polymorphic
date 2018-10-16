//
// Copyright (C) 2018 Dr. Michael Steffens
//
// SPDX-License-Identifier:	BSL-1.0
//


#ifndef Testee_DequeTestSuite_INCLUDED
#define Testee_DequeTestSuite_INCLUDED

#include "Testee/TestSuite.h"
#include <array>

namespace Testee {

/// Test DequeType C++11 standard deque interface.
template<template<typename...> class DequeType, typename T, typename Allocator = std::allocator<T>>
class DequeTestSuite : public TestSuite
{
public:
	typedef std::initializer_list<T> InitializerListType;
	typedef std::array<T, 1> ArrayType;

	DequeTestSuite(const std::string& vectorType) :
		TestSuite(
			vectorType + " C++11 standard interface",
			{

				TestCase(
					"typedefs",
					[] {
						TestCase::assert(std::is_same<typename DequeType<T, Allocator>::value_type, T>::value, "value_type");
						TestCase::assert(std::is_class<typename DequeType<T, Allocator>::allocator_type>::value, "allocator_type");
						if (!std::is_same<bool, T>::value) {
							TestCase::assert(std::is_same<typename DequeType<T, Allocator>::reference, T&>::value, "reference");
							TestCase::assert(
								std::is_same<typename DequeType<T, Allocator>::const_reference, const T&>::value,
								"const_reference");
						} else {
							TestCase::assert(std::is_class<typename DequeType<T, Allocator>::reference>::value, "reference");
							TestCase::assert(
								std::is_same<typename DequeType<T, Allocator>::const_reference, T>::value, "const_reference");
						}
					}),

				TestCase(
					"ctor default",
					[] {
						DequeType<T, Allocator> testee;
						TestCase::assert(testee.size() == 0);
					}),

				TestCase(
					"ctor default with allocator",
					[] {
						const Allocator allocator;
						DequeType<T, Allocator> testee(allocator);
						TestCase::assert(testee.size() == 0);
					}),

				TestCase(
					"ctor fill",
					[] {
						DequeType<T, Allocator> testee(3);
						TestCase::assert(testee.size() == 3);
					}),

				TestCase(
					"ctor fill value",
					[] {
						DequeType<T, Allocator> testee(3, T());
						TestCase::assert(testee.size() == 3);
					}),

				TestCase(
					"ctor copy",
					[] {
						const DequeType<T, Allocator> other(3);
						DequeType<T, Allocator> testee(other);
						TestCase::assert(testee.size() == 3);
					}),

				TestCase(
					"ctor copy with allocator",
					[] {
						const DequeType<T, Allocator> other(3);
						const Allocator allocator;
						DequeType<T, Allocator> testee(other, allocator);
						TestCase::assert(testee.size() == 3);
					}),

				TestCase(
					"ctor move",
					[] {
						DequeType<T, Allocator> other(3);
						DequeType<T, Allocator> testee(std::move(other));
						TestCase::assert(other.size() == 0, "other");
						TestCase::assert(testee.size() == 3, "testee");
					}),

				TestCase(
					"ctor move with allocator",
					[] {
						DequeType<T, Allocator> other(3);
						const Allocator allocator;
						DequeType<T, Allocator> testee(std::move(other), allocator);
						TestCase::assert(other.size() == 0, "other");
						TestCase::assert(testee.size() == 3, "testee");
					}),

				TestCase(
					"ctor range",
					[] {
						DequeType<T, Allocator> testee(ARRAY.begin(), ARRAY.end());
						TestCase::assert(testee.size() == ARRAY.size());
					}),

				TestCase(
					"ctor initializer list",
					[] {
						DequeType<T, Allocator> testee(INITIALIZER_LIST);
						TestCase::assert(testee.size() == INITIALIZER_LIST.size());
					}),

				TestCase(
					"operator= copy",
					[] {
						const DequeType<T, Allocator> other(3);
						DequeType<T, Allocator> testee;
						auto& result = (testee = other);
						TestCase::assert(std::is_same<DequeType<T, Allocator>&, decltype(result)>::value, "type");
						TestCase::assert(testee.size() == 3, "result");
					}),

				TestCase(
					"operator= move",
					[] {
						DequeType<T, Allocator> other(3);
						DequeType<T, Allocator> testee;
						auto& result = (testee = std::move(other));
						TestCase::assert(std::is_same<DequeType<T, Allocator>&, decltype(result)>::value, "type");
						TestCase::assert(other.size() == 0, "other");
						TestCase::assert(testee.size() == 3, "testee");
					}),

				TestCase(
					"operator= initializer list",
					[] {
						DequeType<T, Allocator> testee;
						auto& result = (testee = INITIALIZER_LIST);
						TestCase::assert(std::is_same<DequeType<T, Allocator>&, decltype(result)>::value, "type");
						TestCase::assert(testee.size() == INITIALIZER_LIST.size(), "result");
					}),

				TestCase(
					"begin",
					[] {
						DequeType<T, Allocator> testee(1);
						auto result = testee.begin();
						TestCase::assert(std::is_same<typename DequeType<T, Allocator>::iterator, decltype(result)>::value, "type");
						TestCase::assert(*result == T(), "result");
					}),

				TestCase(
					"begin const",
					[] {
						const DequeType<T, Allocator> testee(1);
						auto result = testee.begin();
						TestCase::assert(
							std::is_same<typename DequeType<T, Allocator>::const_iterator, decltype(result)>::value, "type");
						TestCase::assert(*result == T(), "result");
					}),

				TestCase(
					"end",
					[] {
						DequeType<T, Allocator> testee(1);
						auto result = testee.end();
						TestCase::assert(std::is_same<typename DequeType<T, Allocator>::iterator, decltype(result)>::value, "type");
						TestCase::assert(*(--result) == T(), "result");
					}),

				TestCase(
					"end const",
					[] {
						const DequeType<T, Allocator> testee(1);
						auto result = testee.end();
						TestCase::assert(
							std::is_same<typename DequeType<T, Allocator>::const_iterator, decltype(result)>::value, "type");
						TestCase::assert(*(--result) == T(), "result");
					}),

				TestCase(
					"rbegin",
					[] {
						DequeType<T, Allocator> testee(1);
						auto result = testee.rbegin();
						TestCase::assert(
							std::is_same<typename DequeType<T, Allocator>::reverse_iterator, decltype(result)>::value, "type");
						TestCase::assert(*result == T(), "result");
					}),

				TestCase(
					"rbegin const",
					[] {
						const DequeType<T, Allocator> testee(1);
						auto result = testee.rbegin();
						TestCase::assert(
							std::is_same<typename DequeType<T, Allocator>::const_reverse_iterator, decltype(result)>::value,
							"type");
						TestCase::assert(*result == T(), "result");
					}),

				TestCase(
					"rend",
					[] {
						DequeType<T, Allocator> testee(1);
						auto result = testee.rend();
						TestCase::assert(
							std::is_same<typename DequeType<T, Allocator>::reverse_iterator, decltype(result)>::value, "type");
						TestCase::assert(*(--result) == T(), "result");
					}),

				TestCase(
					"rend const",
					[] {
						const DequeType<T, Allocator> testee(1);
						auto result = testee.rend();
						TestCase::assert(
							std::is_same<typename DequeType<T, Allocator>::const_reverse_iterator, decltype(result)>::value,
							"type");
						TestCase::assert(*(--result) == T(), "result");
					}),

				TestCase(
					"cbegin",
					[] {
						DequeType<T, Allocator> testee(1);
						auto result = testee.cbegin();
						TestCase::assert(
							std::is_same<typename DequeType<T, Allocator>::const_iterator, decltype(result)>::value, "type");
						TestCase::assert(*result == T(), "result");
					}),

				TestCase(
					"cend",
					[] {
						DequeType<T, Allocator> testee(1);
						auto result = testee.cend();
						TestCase::assert(
							std::is_same<typename DequeType<T, Allocator>::const_iterator, decltype(result)>::value, "type");
						TestCase::assert(*(--result) == T(), "result");
					}),

				TestCase(
					"crbegin",
					[] {
						DequeType<T, Allocator> testee(1);
						auto result = testee.crbegin();
						TestCase::assert(
							std::is_same<typename DequeType<T, Allocator>::const_reverse_iterator, decltype(result)>::value,
							"type");
						TestCase::assert(*result == T(), "result");
					}),

				TestCase(
					"crend",
					[] {
						DequeType<T, Allocator> testee(1);
						auto result = testee.crend();
						TestCase::assert(
							std::is_same<typename DequeType<T, Allocator>::const_reverse_iterator, decltype(result)>::value,
							"type");
						TestCase::assert(*(--result) == T(), "result");
					}),

				TestCase(
					"empty",
					[] {
						const DequeType<T, Allocator> testee;
						auto result = testee.empty();
						TestCase::assert(std::is_same<bool, decltype(result)>::value, "bool");
						TestCase::assert(result == true, "result");
					}),

				TestCase(
					"size",
					[] {
						const DequeType<T, Allocator> testee(3);
						auto result = testee.size();
						TestCase::assert(
							std::is_same<typename DequeType<T, Allocator>::size_type, decltype(result)>::value, "type");
						TestCase::assert(result == 3, "result");
					}),

				TestCase(
					"max_size",
					[] {
						const DequeType<T, Allocator> testee(3);
						auto result = testee.max_size();
						TestCase::assert(
							std::is_same<typename DequeType<T, Allocator>::size_type, decltype(result)>::value, "type");
						TestCase::assert(result >= 3, "result");
					}),

				TestCase(
					"resize",
					[] {
						DequeType<T, Allocator> testee(1);
						testee.resize(3);
						TestCase::assert(testee.size() == 3);
					}),

				TestCase(
					"resize value",
					[] {
						DequeType<T, Allocator> testee(1);
						testee.resize(3, T());
						TestCase::assert(testee.size() == 3);
					}),

				TestCase(
					"shrink_to_fit",
					[] {
						DequeType<T, Allocator> testee(1);
						testee.shrink_to_fit();
					}),

				TestCase(
					"operator[]",
					[] {
						DequeType<T, Allocator> testee(1);
						auto& result = testee[0];
						TestCase::assert(
							std::is_same<typename DequeType<T, Allocator>::reference, decltype(result)>::value, "type");
						TestCase::assert(result == T(), "result");
					}),

				TestCase(
					"operator[] const", []
					{
						const DequeType<T, Allocator> testee(1);
						auto& result = testee[0];
						TestCase::assert(
							std::is_same<typename DequeType<T, Allocator>::const_reference, decltype(result)>::value, "type");
						TestCase::assert(result == T(), "result");
					}),

				TestCase(
					"at",
					[] {
						DequeType<T, Allocator> testee(1);
						auto& result = testee.at(0);
						TestCase::assert(
							std::is_same<typename DequeType<T, Allocator>::reference, decltype(result)>::value, "type");
						TestCase::assert(result == T(), "result");
					}),

				TestCase(
					"at const",
					[] {
						const DequeType<T, Allocator> testee(1);
						auto& result = testee.at(0);
						TestCase::assert(
							std::is_same<typename DequeType<T, Allocator>::const_reference, decltype(result)>::value, "type");
						TestCase::assert(result == T(), "result");
					}),

				TestCase(
					"front",
					[] {
						DequeType<T, Allocator> testee(1);
						auto& result = testee.front();
						TestCase::assert(
							std::is_same<typename DequeType<T, Allocator>::reference, decltype(result)>::value, "type");
						TestCase::assert(result == T(), "result");
					}),

				TestCase(
					"front const",
					[] {
						const DequeType<T, Allocator> testee(1);
						auto& result = testee.front();
						TestCase::assert(
							std::is_same<typename DequeType<T, Allocator>::const_reference, decltype(result)>::value, "type");
						TestCase::assert(result == T(), "result");
					}),

				TestCase(
					"back",
					[] {
						DequeType<T, Allocator> testee(1);
						auto& result = testee.back();
						TestCase::assert(
							std::is_same<typename DequeType<T, Allocator>::reference, decltype(result)>::value, "type");
						TestCase::assert(result == T(), "result");
					}),

				TestCase(
					"back const",
					[] {
						const DequeType<T, Allocator> testee(1);
						auto& result = testee.back();
						TestCase::assert(
							std::is_same<typename DequeType<T, Allocator>::const_reference, decltype(result)>::value, "type");
						TestCase::assert(result == T(), "result");
					}),

				TestCase(
					"assign range",
					[] {
						DequeType<T, Allocator> testee;
						testee.assign(ARRAY.begin(), ARRAY.end());
						TestCase::assert(testee.size() == ARRAY.size());
					}),

				TestCase(
					"assign fill value",
					[] {
						DequeType<T, Allocator> testee;
						testee.assign(3, T());
						TestCase::assert(testee.size() == 3);
					}),

				TestCase(
					"assign initializer list",
					[] {
						DequeType<T, Allocator> testee;
						testee.assign(INITIALIZER_LIST);
						TestCase::assert(testee.size() == INITIALIZER_LIST.size());
					}),

				TestCase(
					"push_back copy",
					[] {
						DequeType<T, Allocator> testee;
						T value = {};
						testee.push_back(value);
						TestCase::assert(testee.size() == 1);
					}),

				TestCase(
					"push_back move",
					[] {
						DequeType<T, Allocator> testee;
						T value = {};
						testee.push_back(std::move(value));
						TestCase::assert(testee.size() == 1);
					}),

				TestCase(
					"push_front copy",
					[] {
						DequeType<T, Allocator> testee;
						T value = {};
						testee.push_front(value);
						TestCase::assert(testee.size() == 1);
					}),

				TestCase(
					"push_front move",
					[] {
						DequeType<T, Allocator> testee;
						T value = {};
						testee.push_front(std::move(value));
						TestCase::assert(testee.size() == 1);
					}),

				TestCase(
					"pop_back",
					[] {
						DequeType<T, Allocator> testee(2);
						testee.pop_back();
						TestCase::assert(testee.size() == 1);
					}),

				TestCase(
					"pop_front",
					[] {
						DequeType<T, Allocator> testee(2);
						testee.pop_front();
						TestCase::assert(testee.size() == 1);
					}),

				TestCase(
					"insert single element",
					[] {
						DequeType<T, Allocator> testee(1);
						auto position = testee.begin();
						T value = {};
						auto result = testee.insert(position, value);
						TestCase::assert(std::is_same<typename DequeType<T, Allocator>::iterator, decltype(result)>::value, "type");
						TestCase::assert(testee.size() == 2, "result");
					}),

				TestCase(
					"insert fill",
					[] {
						DequeType<T, Allocator> testee(1);
						auto position = testee.begin();
						T value = {};
						auto result = testee.insert(position, 2, value);
						TestCase::assert(std::is_same<typename DequeType<T, Allocator>::iterator, decltype(result)>::value, "type");
						TestCase::assert(testee.size() == 3, "result");
					}),

				TestCase(
					"insert range",
					[] {
						DequeType<T, Allocator> testee(1);
						auto position = testee.begin();
						auto result = testee.insert(position, ARRAY.begin(), ARRAY.end());
						TestCase::assert(std::is_same<typename DequeType<T, Allocator>::iterator, decltype(result)>::value, "type");
						TestCase::assert(testee.size() == 1 + ARRAY.size(), "result");
					}),

				TestCase(
					"insert move",
					[] {
						DequeType<T, Allocator> testee(1);
						auto position = testee.begin();
						T value = {};
						auto result = testee.insert(position, std::move(value));
						TestCase::assert(std::is_same<typename DequeType<T, Allocator>::iterator, decltype(result)>::value, "type");
						TestCase::assert(testee.size() == 2, "result");
					}),

				TestCase(
					"insert initializer list",
					[] {
						DequeType<T, Allocator> testee(1);
						auto position = testee.begin();
						auto result = testee.insert(position, INITIALIZER_LIST);
						TestCase::assert(std::is_same<typename DequeType<T, Allocator>::iterator, decltype(result)>::value, "type");
						TestCase::assert(testee.size() == 1 + INITIALIZER_LIST.size(), "result");
					}),

				TestCase(
					"erase single element",
					[] {
						DequeType<T, Allocator> testee(3);
						auto position = testee.begin();
						auto result = testee.erase(position);
						TestCase::assert(std::is_same<typename DequeType<T, Allocator>::iterator, decltype(result)>::value, "type");
						TestCase::assert(testee.size() == 2, "result");
					}),

				TestCase(
					"erase range",
					[] {
						DequeType<T, Allocator> testee(3);
						auto first = testee.begin();
						auto last = first + 2;
						auto result = testee.erase(first, last);
						TestCase::assert(std::is_same<typename DequeType<T, Allocator>::iterator, decltype(result)>::value, "type");
						TestCase::assert(testee.size() == 1, "result");
					}),

				TestCase(
					"swap",
					[] {
						DequeType<T, Allocator> other(3);
						DequeType<T, Allocator> testee(1);
						testee.swap(other);
						TestCase::assert(other.size() == 1, "other");
						TestCase::assert(testee.size() == 3, "testee");
					}),

				TestCase(
					"clear",
					[] {
						DequeType<T, Allocator> testee(1);
						testee.clear();
						TestCase::assert(testee.size() == 0);
					}),

				TestCase(
					"emplace",
					[] {
						DequeType<T, Allocator> testee(1);
						auto position = testee.begin();
						auto result = testee.emplace(position);
						TestCase::assert(std::is_same<typename DequeType<T, Allocator>::iterator, decltype(result)>::value, "type");
						TestCase::assert(testee.size() == 2, "result");
					}),

				TestCase(
					"emplace_back",
					[] {
						DequeType<T, Allocator> testee(1);
						testee.emplace_back();
						TestCase::assert(testee.size() == 2);
					}),

				TestCase(
					"emplace_front",
					[] {
						DequeType<T, Allocator> testee(1);
						testee.emplace_front();
						TestCase::assert(testee.size() == 2);
					}),

				TestCase(
					"get_allocator",
					[] {
						DequeType<T, Allocator> testee;
						auto result = testee.get_allocator();
						TestCase::assert(std::is_same<typename DequeType<T, Allocator>::allocator_type, decltype(result)>::value);
					}),

				TestCase(
					"operator==",
					[] {
						DequeType<T, Allocator> lhs(3);
						DequeType<T, Allocator> rhs(3);
						auto result = (lhs == rhs);
						TestCase::assert(std::is_same<bool, decltype(result)>::value, "type");
						TestCase::assert(result == true, "result");
					}),

				TestCase(
					"operator!=",
					[] {
						DequeType<T, Allocator> lhs(2);
						DequeType<T, Allocator> rhs(3);
						auto result = (lhs != rhs);
						TestCase::assert(std::is_same<bool, decltype(result)>::value, "type");
						TestCase::assert(result == true, "result");
					}),

				TestCase(
					"operator<",
					[] {
						DequeType<T, Allocator> lhs(2);
						DequeType<T, Allocator> rhs(3);
						auto result = (lhs < rhs);
						TestCase::assert(std::is_same<bool, decltype(result)>::value, "type");
						TestCase::assert(result == true, "result");
					}),

				TestCase(
					"operator<=",
					[] {
						DequeType<T, Allocator> lhs(2);
						DequeType<T, Allocator> rhs(3);
						auto result = (lhs <= rhs);
						TestCase::assert(std::is_same<bool, decltype(result)>::value, "type");
						TestCase::assert(result == true, "result");
					}),

				TestCase(
					"operator>",
					[] {
						DequeType<T, Allocator> lhs(3);
						DequeType<T, Allocator> rhs(2);
						auto result = (lhs > rhs);
						TestCase::assert(std::is_same<bool, decltype(result)>::value, "type");
						TestCase::assert(result == true, "result");
					}),

				TestCase(
					"operator>=",
					[] {
						DequeType<T, Allocator> lhs(3);
						DequeType<T, Allocator> rhs(2);
						auto result = (lhs >= rhs);
						TestCase::assert(std::is_same<bool, decltype(result)>::value, "type");
						TestCase::assert(result == true, "result");
					}),

				TestCase("swap lhs rhs", [] {
					DequeType<T, Allocator> lhs(3);
					DequeType<T, Allocator> rhs(2);
					swap(lhs, rhs);
					TestCase::assert(lhs.size() == 2, "lhs");
					TestCase::assert(rhs.size() == 3, "rhs");
				})})
	{
	}

	static const InitializerListType INITIALIZER_LIST;
	static const ArrayType ARRAY;
};

template<template<typename...> class DequeType, typename T, typename Allocator>
const typename DequeTestSuite<DequeType, T, Allocator>::InitializerListType
	DequeTestSuite<DequeType, T, Allocator>::INITIALIZER_LIST = {T()};

template<template<typename...> class DequeType, typename T, typename Allocator>
const typename DequeTestSuite<DequeType, T, Allocator>::ArrayType DequeTestSuite<DequeType, T, Allocator>::ARRAY = {T()};

} // namespace Testee

#endif // Testee_DequeTestSuite_INCLUDED
