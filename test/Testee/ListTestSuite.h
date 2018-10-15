//
// Copyright (C) 2018 Dr. Michael Steffens
//
// SPDX-License-Identifier:	BSL-1.0
//


#ifndef Testee_ListTestSuite_INCLUDED
#define Testee_ListTestSuite_INCLUDED

#include "Testee/TestSuite.h"
#include <array>

namespace Testee {

/// Test ListType C++11 standard list interface.
template<template<typename...> class ListType, typename T, typename Allocator = std::allocator<T>>
class ListTestSuite : public TestSuite
{
public:
	typedef std::initializer_list<T> InitializerListType;
	typedef std::array<T, 1> ArrayType;

	ListTestSuite(const std::string& listType) :
		TestSuite(
			listType + " C++11 standard interface",
			{

				TestCase(
					"typedefs",
					[] {
						TestCase::assert(std::is_same<typename ListType<T, Allocator>::value_type, T>::value, "value_type");
						TestCase::assert(std::is_class<typename ListType<T, Allocator>::allocator_type>::value, "allocator_type");
						TestCase::assert(std::is_same<typename ListType<T, Allocator>::reference, T&>::value, "reference");
						TestCase::assert(
							std::is_same<typename ListType<T, Allocator>::const_reference, const T&>::value, "const_reference");
					}),

				TestCase(
					"ctor default",
					[] {
						ListType<T, Allocator> testee;
						TestCase::assert(testee.size() == 0);
					}),

				TestCase(
					"ctor default with allocator",
					[] {
						const Allocator allocator;
						ListType<T, Allocator> testee(allocator);
						TestCase::assert(testee.size() == 0);
					}),

				TestCase(
					"ctor fill",
					[] {
						ListType<T, Allocator> testee(3);
						TestCase::assert(testee.size() == 3);
					}),

				TestCase(
					"ctor fill value",
					[] {
						ListType<T, Allocator> testee(3, T(), std::allocator<T>());
						TestCase::assert(testee.size() == 3);
					}),

				TestCase(
					"ctor copy",
					[] {
						const ListType<T, Allocator> other(3);
						ListType<T, Allocator> testee(other);
						TestCase::assert(testee.size() == 3);
					}),

				TestCase(
					"ctor copy with allocator",
					[] {
						const ListType<T, Allocator> other(3);
						const Allocator allocator;
						ListType<T, Allocator> testee(other, allocator);
						TestCase::assert(testee.size() == 3);
					}),

				TestCase(
					"ctor move",
					[] {
						ListType<T, Allocator> other(3);
						ListType<T, Allocator> testee(std::move(other));
						TestCase::assert(other.size() == 0, "other");
						TestCase::assert(testee.size() == 3, "testee");
					}),

				TestCase(
					"ctor move with allocator",
					[] {
						ListType<T, Allocator> other(3);
						const Allocator allocator;
						ListType<T, Allocator> testee(std::move(other), allocator);
						TestCase::assert(other.size() == 0, "other");
						TestCase::assert(testee.size() == 3, "testee");
					}),

				TestCase(
					"ctor range",
					[] {
						ListType<T, Allocator> testee(ARRAY.begin(), ARRAY.end());
						TestCase::assert(testee.size() == ARRAY.size());
					}),

				TestCase(
					"ctor initializer list",
					[] {
						ListType<T, Allocator> testee(INITIALIZER_LIST);
						TestCase::assert(testee.size() == INITIALIZER_LIST.size());
					}),

				TestCase(
					"operator= copy",
					[] {
						const ListType<T, Allocator> other(3);
						ListType<T, Allocator> testee;
						auto& result = (testee = other);
						TestCase::assert(std::is_same<ListType<T, Allocator>&, decltype(result)>::value, "type");
						TestCase::assert(testee.size() == 3, "result");
					}),

				TestCase(
					"operator= move",
					[] {
						ListType<T, Allocator> other(3);
						ListType<T, Allocator> testee;
						auto& result = (testee = std::move(other));
						TestCase::assert(std::is_same<ListType<T, Allocator>&, decltype(result)>::value, "type");
						TestCase::assert(other.size() == 0, "other");
						TestCase::assert(testee.size() == 3, "testee");
					}),

				TestCase(
					"operator= initializer list",
					[] {
						ListType<T, Allocator> testee;
						auto& result = (testee = INITIALIZER_LIST);
						TestCase::assert(std::is_same<ListType<T, Allocator>&, decltype(result)>::value, "type");
						TestCase::assert(testee.size() == INITIALIZER_LIST.size(), "result");
					}),

				TestCase(
					"begin",
					[] {
						ListType<T, Allocator> testee(1);
						auto result = testee.begin();
						TestCase::assert(std::is_same<typename ListType<T, Allocator>::iterator, decltype(result)>::value, "type");
						TestCase::assert(*result == T(), "result");
					}),

				TestCase(
					"begin const",
					[] {
						const ListType<T, Allocator> testee(1);
						auto result = testee.begin();
						TestCase::assert(
							std::is_same<typename ListType<T, Allocator>::const_iterator, decltype(result)>::value, "type");
						TestCase::assert(*result == T(), "result");
					}),

				TestCase(
					"end",
					[] {
						ListType<T, Allocator> testee(1);
						auto result = testee.end();
						TestCase::assert(std::is_same<typename ListType<T, Allocator>::iterator, decltype(result)>::value, "type");
						TestCase::assert(*(--result) == T(), "result");
					}),

				TestCase(
					"end const",
					[] {
						const ListType<T, Allocator> testee(1);
						auto result = testee.end();
						TestCase::assert(
							std::is_same<typename ListType<T, Allocator>::const_iterator, decltype(result)>::value, "type");
						TestCase::assert(*(--result) == T(), "result");
					}),

				TestCase(
					"rbegin",
					[] {
						ListType<T, Allocator> testee(1);
						auto result = testee.rbegin();
						TestCase::assert(
							std::is_same<typename ListType<T, Allocator>::reverse_iterator, decltype(result)>::value, "type");
						TestCase::assert(*result == T(), "result");
					}),

				TestCase(
					"rbegin const",
					[] {
						const ListType<T, Allocator> testee(1);
						auto result = testee.rbegin();
						TestCase::assert(
							std::is_same<typename ListType<T, Allocator>::const_reverse_iterator, decltype(result)>::value, "type");
						TestCase::assert(*result == T(), "result");
					}),

				TestCase(
					"rend",
					[] {
						ListType<T, Allocator> testee(1);
						auto result = testee.rend();
						TestCase::assert(
							std::is_same<typename ListType<T, Allocator>::reverse_iterator, decltype(result)>::value, "type");
						TestCase::assert(*(--result) == T(), "result");
					}),

				TestCase(
					"rend const",
					[] {
						const ListType<T, Allocator> testee(1);
						auto result = testee.rend();
						TestCase::assert(
							std::is_same<typename ListType<T, Allocator>::const_reverse_iterator, decltype(result)>::value, "type");
						TestCase::assert(*(--result) == T(), "result");
					}),

				TestCase(
					"cbegin",
					[] {
						ListType<T, Allocator> testee(1);
						auto result = testee.cbegin();
						TestCase::assert(
							std::is_same<typename ListType<T, Allocator>::const_iterator, decltype(result)>::value, "type");
						TestCase::assert(*result == T(), "result");
					}),

				TestCase(
					"cend",
					[] {
						ListType<T, Allocator> testee(1);
						auto result = testee.cend();
						TestCase::assert(
							std::is_same<typename ListType<T, Allocator>::const_iterator, decltype(result)>::value, "type");
						TestCase::assert(*(--result) == T(), "result");
					}),

				TestCase(
					"crbegin",
					[] {
						ListType<T, Allocator> testee(1);
						auto result = testee.crbegin();
						TestCase::assert(
							std::is_same<typename ListType<T, Allocator>::const_reverse_iterator, decltype(result)>::value, "type");
						TestCase::assert(*result == T(), "result");
					}),

				TestCase(
					"crend",
					[] {
						ListType<T, Allocator> testee(1);
						auto result = testee.crend();
						TestCase::assert(
							std::is_same<typename ListType<T, Allocator>::const_reverse_iterator, decltype(result)>::value, "type");
						TestCase::assert(*(--result) == T(), "result");
					}),

				TestCase(
					"empty",
					[] {
						const ListType<T, Allocator> testee;
						auto result = testee.empty();
						TestCase::assert(std::is_same<bool, decltype(result)>::value, "bool");
						TestCase::assert(result == true, "result");
					}),

				TestCase(
					"size",
					[] {
						const ListType<T, Allocator> testee(3);
						auto result = testee.size();
						TestCase::assert(std::is_same<typename ListType<T, Allocator>::size_type, decltype(result)>::value, "type");
						TestCase::assert(result == 3, "result");
					}),

				TestCase(
					"max_size",
					[] {
						const ListType<T, Allocator> testee(3);
						auto result = testee.max_size();
						TestCase::assert(std::is_same<typename ListType<T, Allocator>::size_type, decltype(result)>::value, "type");
						TestCase::assert(result >= 3, "result");
					}),

				TestCase(
					"front",
					[] {
						ListType<T, Allocator> testee(1);
						auto& result = testee.front();
						TestCase::assert(std::is_same<typename ListType<T, Allocator>::reference, decltype(result)>::value, "type");
						TestCase::assert(result == T(), "result");
					}),

				TestCase(
					"front const",
					[] {
						const ListType<T, Allocator> testee(1);
						auto& result = testee.front();
						TestCase::assert(
							std::is_same<typename ListType<T, Allocator>::const_reference, decltype(result)>::value, "type");
						TestCase::assert(result == T(), "result");
					}),

				TestCase(
					"back",
					[] {
						ListType<T, Allocator> testee(1);
						auto& result = testee.back();
						TestCase::assert(std::is_same<typename ListType<T, Allocator>::reference, decltype(result)>::value, "type");
						TestCase::assert(result == T(), "result");
					}),

				TestCase(
					"back const",
					[] {
						const ListType<T, Allocator> testee(1);
						auto& result = testee.back();
						TestCase::assert(
							std::is_same<typename ListType<T, Allocator>::const_reference, decltype(result)>::value, "type");
						TestCase::assert(result == T(), "result");
					}),

				TestCase(
					"assign range",
					[] {
						ListType<T, Allocator> testee;
						testee.assign(ARRAY.begin(), ARRAY.end());
						TestCase::assert(testee.size() == ARRAY.size());
					}),

				TestCase(
					"assign fill value",
					[] {
						ListType<T, Allocator> testee;
						testee.assign(3, T());
						TestCase::assert(testee.size() == 3);
					}),

				TestCase(
					"assign initializer list",
					[] {
						ListType<T, Allocator> testee;
						testee.assign(INITIALIZER_LIST);
						TestCase::assert(testee.size() == INITIALIZER_LIST.size());
					}),

				TestCase(
					"emplace_front",
					[] {
						ListType<T, Allocator> testee(1);
						testee.emplace_front();
						TestCase::assert(testee.size() == 2);
					}),

				TestCase(
					"push_front copy",
					[] {
						ListType<T, Allocator> testee;
						T value = {};
						testee.push_front(value);
						TestCase::assert(testee.size() == 1);
					}),

				TestCase(
					"push_front move",
					[] {
						ListType<T, Allocator> testee;
						T value = {};
						testee.push_front(std::move(value));
						TestCase::assert(testee.size() == 1);
					}),

				TestCase(
					"pop_front",
					[] {
						ListType<T, Allocator> testee(2);
						testee.pop_front();
						TestCase::assert(testee.size() == 1);
					}),

				TestCase(
					"emplace_back",
					[] {
						ListType<T, Allocator> testee(1);
						testee.emplace_back();
						TestCase::assert(testee.size() == 2);
					}),

				TestCase(
					"push_back copy",
					[] {
						ListType<T, Allocator> testee;
						T value = {};
						testee.push_back(value);
						TestCase::assert(testee.size() == 1);
					}),

				TestCase(
					"push_back move",
					[] {
						ListType<T, Allocator> testee;
						T value = {};
						testee.push_back(std::move(value));
						TestCase::assert(testee.size() == 1);
					}),

				TestCase(
					"pop_back",
					[] {
						ListType<T, Allocator> testee(2);
						testee.pop_back();
						TestCase::assert(testee.size() == 1);
					}),

				TestCase(
					"emplace",
					[] {
						ListType<T, Allocator> testee(1);
						auto position = testee.begin();
						auto result = testee.emplace(position);
						TestCase::assert(std::is_same<typename ListType<T, Allocator>::iterator, decltype(result)>::value, "type");
						TestCase::assert(testee.size() == 2, "result");
					}),

				TestCase(
					"insert single element",
					[] {
						ListType<T, Allocator> testee(1);
						auto position = testee.begin();
						T value = {};
						auto result = testee.insert(position, value);
						TestCase::assert(std::is_same<typename ListType<T, Allocator>::iterator, decltype(result)>::value, "type");
						TestCase::assert(testee.size() == 2, "result");
					}),

				TestCase(
					"insert fill",
					[] {
						ListType<T, Allocator> testee(1);
						auto position = testee.begin();
						T value = {};
						auto result = testee.insert(position, 2, value);
						TestCase::assert(std::is_same<typename ListType<T, Allocator>::iterator, decltype(result)>::value, "type");
						TestCase::assert(testee.size() == 3, "result");
					}),

				TestCase(
					"insert range",
					[] {
						ListType<T, Allocator> testee(1);
						auto position = testee.begin();
						auto result = testee.insert(position, ARRAY.begin(), ARRAY.end());
						TestCase::assert(std::is_same<typename ListType<T, Allocator>::iterator, decltype(result)>::value, "type");
						TestCase::assert(testee.size() == 1 + ARRAY.size(), "result");
					}),

				TestCase(
					"insert move",
					[] {
						ListType<T, Allocator> testee(1);
						auto position = testee.begin();
						T value = {};
						auto result = testee.insert(position, std::move(value));
						TestCase::assert(std::is_same<typename ListType<T, Allocator>::iterator, decltype(result)>::value, "type");
						TestCase::assert(testee.size() == 2, "result");
					}),

				TestCase(
					"insert initializer list",
					[] {
						ListType<T, Allocator> testee(1);
						auto position = testee.begin();
						auto result = testee.insert(position, INITIALIZER_LIST);
						TestCase::assert(std::is_same<typename ListType<T, Allocator>::iterator, decltype(result)>::value, "type");
						TestCase::assert(testee.size() == 1 + INITIALIZER_LIST.size(), "result");
					}),

				TestCase(
					"erase single element",
					[] {
						ListType<T, Allocator> testee(3);
						auto position = testee.begin();
						auto result = testee.erase(position);
						TestCase::assert(std::is_same<typename ListType<T, Allocator>::iterator, decltype(result)>::value, "type");
						TestCase::assert(testee.size() == 2, "result");
					}),

				TestCase(
					"erase range",
					[] {
						ListType<T, Allocator> testee(3);
						auto first = testee.begin();
						auto last = first;
						++last;
						++last;
						auto result = testee.erase(first, last);
						TestCase::assert(std::is_same<typename ListType<T, Allocator>::iterator, decltype(result)>::value, "type");
						TestCase::assert(testee.size() == 1, "result");
					}),

				TestCase(
					"swap",
					[] {
						ListType<T, Allocator> other(3);
						ListType<T, Allocator> testee(1);
						testee.swap(other);
						TestCase::assert(other.size() == 1, "other");
						TestCase::assert(testee.size() == 3, "testee");
					}),

				TestCase(
					"resize",
					[] {
						ListType<T, Allocator> testee(1);
						testee.resize(3);
						TestCase::assert(testee.size() == 3);
					}),

				TestCase(
					"resize value",
					[] {
						ListType<T, Allocator> testee(1);
						testee.resize(3, T());
						TestCase::assert(testee.size() == 3);
					}),

				TestCase(
					"clear",
					[] {
						ListType<T, Allocator> testee(1);
						testee.clear();
						TestCase::assert(testee.size() == 0);
					}),

				TestCase(
					"splice entire list",
					[] {
						ListType<T, Allocator> other(3);
						ListType<T, Allocator> testee(1);
						auto position = testee.begin();
						testee.splice(position, other);
						TestCase::assert(other.size() == 0, "other");
						TestCase::assert(testee.size() == 4, "testee");
					}),

				TestCase(
					"splice entire list move",
					[] {
						ListType<T, Allocator> other(3);
						ListType<T, Allocator> testee(1);
						auto position = testee.begin();
						testee.splice(position, std::move(other));
						TestCase::assert(other.size() == 0, "other");
						TestCase::assert(testee.size() == 4, "testee");
					}),

				TestCase(
					"splice single element",
					[] {
						ListType<T, Allocator> other(3);
						auto i = other.begin();
						ListType<T, Allocator> testee(1);
						auto position = testee.begin();
						testee.splice(position, other, i);
						TestCase::assert(other.size() == 2, "other");
						TestCase::assert(testee.size() == 2, "testee");
					}),

				TestCase(
					"splice single element move",
					[] {
						ListType<T, Allocator> other(3);
						auto i = other.begin();
						ListType<T, Allocator> testee(1);
						auto position = testee.begin();
						testee.splice(position, std::move(other), i);
						TestCase::assert(other.size() == 2, "other");
						TestCase::assert(testee.size() == 2, "testee");
					}),

				TestCase(
					"splice range move",
					[] {
						ListType<T, Allocator> other(3);
						auto first = other.begin();
						auto last = first;
						++last;
						++last;
						ListType<T, Allocator> testee(1);
						auto position = testee.begin();
						testee.splice(position, std::move(other), first, last);
						TestCase::assert(other.size() == 1, "other");
						TestCase::assert(testee.size() == 3, "testee");
					}),

				TestCase(
					"splice range",
					[] {
						ListType<T, Allocator> other(3);
						auto first = other.begin();
						auto last = first;
						++last;
						++last;
						ListType<T, Allocator> testee(1);
						auto position = testee.begin();
						testee.splice(position, other, first, last);
						TestCase::assert(other.size() == 1, "other");
						TestCase::assert(testee.size() == 3, "testee");
					}),

				TestCase(
					"remove",
					[] {
						ListType<T, Allocator> testee(1);
						testee.remove(T());
						TestCase::assert(testee.size() == 0);
					}),

				TestCase(
					"remove_if",
					[] {
						ListType<T, Allocator> testee(1);
						testee.remove_if([](const T&) -> bool { return true; });
						TestCase::assert(testee.size() == 0);
					}),

				TestCase(
					"unique",
					[] {
						ListType<T, Allocator> testee(3);
						testee.unique();
						TestCase::assert(testee.size() == 1);
					}),

				TestCase(
					"unique with predicate",
					[] {
						ListType<T, Allocator> testee(3);
						testee.unique([](const T& lhs, const T& rhs) -> bool { return lhs == rhs; });
						TestCase::assert(testee.size() == 1);
					}),

				TestCase(
					"merge",
					[] {
						ListType<T, Allocator> other(2);
						ListType<T, Allocator> testee(1);
						testee.merge(other);
						TestCase::assert(testee.size() == 3);
					}),

				TestCase(
					"merge move",
					[] {
						ListType<T, Allocator> other(2);
						ListType<T, Allocator> testee(1);
						testee.merge(std::move(other));
						TestCase::assert(testee.size() == 3);
					}),

				TestCase(
					"merge with predicate",
					[] {
						ListType<T, Allocator> other(2);
						ListType<T, Allocator> testee(1);
						testee.merge(other, [](const T& lhs, const T& rhs) -> bool { return lhs < rhs; });
						TestCase::assert(testee.size() == 3);
					}),

				TestCase(
					"merge with predicate move",
					[] {
						ListType<T, Allocator> other(2);
						ListType<T, Allocator> testee(1);
						testee.merge(std::move(other), [](const T& lhs, const T& rhs) -> bool { return lhs < rhs; });
						TestCase::assert(testee.size() == 3);
					}),

				TestCase(
					"sort",
					[] {
						ListType<T, Allocator> testee(3);
						testee.sort();
						TestCase::assert(testee.size() == 3);
					}),

				TestCase(
					"sort with predicate",
					[] {
						ListType<T, Allocator> testee(3);
						testee.sort([](const T& lhs, const T& rhs) -> bool { return lhs < rhs; });
						TestCase::assert(testee.size() == 3);
					}),

				TestCase(
					"reverse",
					[] {
						ListType<T, Allocator> testee(3);
						testee.reverse();
						TestCase::assert(testee.size() == 3);
					}),

				TestCase(
					"get_allocator",
					[] {
						ListType<T, Allocator> testee;
						auto result = testee.get_allocator();
						TestCase::assert(std::is_same<typename ListType<T, Allocator>::allocator_type, decltype(result)>::value);
					}),

				TestCase(
					"operator==",
					[] {
						ListType<T, Allocator> lhs(3);
						ListType<T, Allocator> rhs(3);
						auto result = (lhs == rhs);
						TestCase::assert(std::is_same<bool, decltype(result)>::value, "type");
						TestCase::assert(result == true, "result");
					}),

				TestCase(
					"operator!=",
					[] {
						ListType<T, Allocator> lhs(2);
						ListType<T, Allocator> rhs(3);
						auto result = (lhs != rhs);
						TestCase::assert(std::is_same<bool, decltype(result)>::value, "type");
						TestCase::assert(result == true, "result");
					}),

				TestCase(
					"operator<",
					[] {
						ListType<T, Allocator> lhs(2);
						ListType<T, Allocator> rhs(3);
						auto result = (lhs < rhs);
						TestCase::assert(std::is_same<bool, decltype(result)>::value, "type");
						TestCase::assert(result == true, "result");
					}),

				TestCase(
					"operator<=",
					[] {
						ListType<T, Allocator> lhs(2);
						ListType<T, Allocator> rhs(3);
						auto result = (lhs <= rhs);
						TestCase::assert(std::is_same<bool, decltype(result)>::value, "type");
						TestCase::assert(result == true, "result");
					}),

				TestCase(
					"operator>",
					[] {
						ListType<T, Allocator> lhs(3);
						ListType<T, Allocator> rhs(2);
						auto result = (lhs > rhs);
						TestCase::assert(std::is_same<bool, decltype(result)>::value, "type");
						TestCase::assert(result == true, "result");
					}),

				TestCase(
					"operator>=",
					[] {
						ListType<T, Allocator> lhs(3);
						ListType<T, Allocator> rhs(2);
						auto result = (lhs >= rhs);
						TestCase::assert(std::is_same<bool, decltype(result)>::value, "type");
						TestCase::assert(result == true, "result");
					}),

				TestCase("swap lhs rhs", [] {
					ListType<T, Allocator> lhs(3);
					ListType<T, Allocator> rhs(2);
					swap(lhs, rhs);
					TestCase::assert(lhs.size() == 2, "lhs");
					TestCase::assert(rhs.size() == 3, "rhs");
				})})
	{
	}

	static const InitializerListType INITIALIZER_LIST;
	static const ArrayType ARRAY;
};

template<template<typename...> class ListType, typename T, typename Allocator>
const typename ListTestSuite<ListType, T, Allocator>::InitializerListType ListTestSuite<ListType, T, Allocator>::INITIALIZER_LIST =
	{T()};

template<template<typename...> class ListType, typename T, typename Allocator>
const typename ListTestSuite<ListType, T, Allocator>::ArrayType ListTestSuite<ListType, T, Allocator>::ARRAY = {T()};

} // namespace Testee

#endif // Testee_ListTestSuite_INCLUDED
