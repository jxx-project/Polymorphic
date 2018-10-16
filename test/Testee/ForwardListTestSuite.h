//
// Copyright (C) 2018 Dr. Michael Steffens
//
// SPDX-License-Identifier:	BSL-1.0
//


#ifndef Testee_ForwardListTestSuite_INCLUDED
#define Testee_ForwardListTestSuite_INCLUDED

#include "Testee/TestSuite.h"
#include <array>

namespace Testee {

/// Test ForwardListType C++11 standard list interface.
template<template<typename...> class ForwardListType, typename T, typename Allocator = std::allocator<T>>
class ForwardListTestSuite : public TestSuite
{
public:
	typedef std::initializer_list<T> InitializerListType;
	typedef std::array<T, 1> ArrayType;

	ForwardListTestSuite(const std::string& forwardListType) :
		TestSuite(
			forwardListType + " C++11 standard interface",
			{

				TestCase(
					"typedefs",
					[] {
						TestCase::assert(std::is_same<typename ForwardListType<T, Allocator>::value_type, T>::value, "value_type");
						TestCase::assert(
							std::is_class<typename ForwardListType<T, Allocator>::allocator_type>::value, "allocator_type");
						TestCase::assert(std::is_same<typename ForwardListType<T, Allocator>::reference, T&>::value, "reference");
						TestCase::assert(
							std::is_same<typename ForwardListType<T, Allocator>::const_reference, const T&>::value,
							"const_reference");
					}),

				TestCase(
					"ctor default",
					[] {
						ForwardListType<T, Allocator> testee;
						TestCase::assert(listSize(testee) == 0);
					}),

				TestCase(
					"ctor default with allocator",
					[] {
						const Allocator allocator;
						ForwardListType<T, Allocator> testee(allocator);
						TestCase::assert(listSize(testee) == 0);
					}),

				TestCase(
					"ctor fill",
					[] {
						ForwardListType<T, Allocator> testee(3);
						TestCase::assert(listSize(testee) == 3);
					}),

				TestCase(
					"ctor fill value",
					[] {
						ForwardListType<T, Allocator> testee(3, T(), std::allocator<T>());
						TestCase::assert(listSize(testee) == 3);
					}),

				TestCase(
					"ctor copy",
					[] {
						const ForwardListType<T, Allocator> other(3);
						ForwardListType<T, Allocator> testee(other);
						TestCase::assert(listSize(testee) == 3);
					}),

				TestCase(
					"ctor copy with allocator",
					[] {
						const ForwardListType<T, Allocator> other(3);
						const Allocator allocator;
						ForwardListType<T, Allocator> testee(other, allocator);
						TestCase::assert(listSize(testee) == 3);
					}),

				TestCase(
					"ctor move",
					[] {
						ForwardListType<T, Allocator> other(3);
						ForwardListType<T, Allocator> testee(std::move(other));
						TestCase::assert(listSize(other) == 0, "other");
						TestCase::assert(listSize(testee) == 3, "testee");
					}),

				TestCase(
					"ctor move with allocator",
					[] {
						ForwardListType<T, Allocator> other(3);
						const Allocator allocator;
						ForwardListType<T, Allocator> testee(std::move(other), allocator);
						TestCase::assert(listSize(other) == 0, "other");
						TestCase::assert(listSize(testee) == 3, "testee");
					}),

				TestCase(
					"ctor range",
					[] {
						ForwardListType<T, Allocator> testee(ARRAY.begin(), ARRAY.end());
						TestCase::assert(listSize(testee) == ARRAY.size());
					}),

				TestCase(
					"ctor initializer list",
					[] {
						ForwardListType<T, Allocator> testee(INITIALIZER_LIST);
						TestCase::assert(listSize(testee) == INITIALIZER_LIST.size());
					}),

				TestCase(
					"operator= copy",
					[] {
						const ForwardListType<T, Allocator> other(3);
						ForwardListType<T, Allocator> testee;
						auto& result = (testee = other);
						TestCase::assert(std::is_same<ForwardListType<T, Allocator>&, decltype(result)>::value, "type");
						TestCase::assert(listSize(testee) == 3, "result");
					}),

				TestCase(
					"operator= move",
					[] {
						ForwardListType<T, Allocator> other(3);
						ForwardListType<T, Allocator> testee;
						auto& result = (testee = std::move(other));
						TestCase::assert(std::is_same<ForwardListType<T, Allocator>&, decltype(result)>::value, "type");
						TestCase::assert(listSize(other) == 0, "other");
						TestCase::assert(listSize(testee) == 3, "testee");
					}),

				TestCase(
					"operator= initializer list",
					[] {
						ForwardListType<T, Allocator> testee;
						auto& result = (testee = INITIALIZER_LIST);
						TestCase::assert(std::is_same<ForwardListType<T, Allocator>&, decltype(result)>::value, "type");
						TestCase::assert(listSize(testee) == INITIALIZER_LIST.size(), "result");
					}),

				TestCase(
					"before_begin",
					[] {
						ForwardListType<T, Allocator> testee(1);
						auto result = testee.before_begin();
						TestCase::assert(
							std::is_same<typename ForwardListType<T, Allocator>::iterator, decltype(result)>::value, "type");
						TestCase::assert(*(++result) == T(), "result");
					}),

				TestCase(
					"before_begin const",
					[] {
						const ForwardListType<T, Allocator> testee(1);
						auto result = testee.before_begin();
						TestCase::assert(
							std::is_same<typename ForwardListType<T, Allocator>::const_iterator, decltype(result)>::value, "type");
						TestCase::assert(*(++result) == T(), "result");
					}),

				TestCase(
					"begin",
					[] {
						ForwardListType<T, Allocator> testee(1);
						auto result = testee.begin();
						TestCase::assert(
							std::is_same<typename ForwardListType<T, Allocator>::iterator, decltype(result)>::value, "type");
						TestCase::assert(*result == T(), "result");
					}),

				TestCase(
					"begin const",
					[] {
						const ForwardListType<T, Allocator> testee(1);
						auto result = testee.begin();
						TestCase::assert(
							std::is_same<typename ForwardListType<T, Allocator>::const_iterator, decltype(result)>::value, "type");
						TestCase::assert(*result == T(), "result");
					}),

				TestCase(
					"end",
					[] {
						ForwardListType<T, Allocator> testee(1);
						auto result = testee.end();
						TestCase::assert(
							std::is_same<typename ForwardListType<T, Allocator>::iterator, decltype(result)>::value, "type");
						TestCase::assert(result == (++testee.begin()), "result");
					}),

				TestCase(
					"end const",
					[] {
						const ForwardListType<T, Allocator> testee(1);
						auto result = testee.end();
						TestCase::assert(
							std::is_same<typename ForwardListType<T, Allocator>::const_iterator, decltype(result)>::value, "type");
						TestCase::assert(result == (++testee.begin()), "result");
					}),

				TestCase(
					"cbefore_begin",
					[] {
						ForwardListType<T, Allocator> testee(1);
						auto result = testee.cbefore_begin();
						TestCase::assert(
							std::is_same<typename ForwardListType<T, Allocator>::const_iterator, decltype(result)>::value, "type");
						TestCase::assert(*(++result) == T(), "result");
					}),

				TestCase(
					"cbegin",
					[] {
						ForwardListType<T, Allocator> testee(1);
						auto result = testee.cbegin();
						TestCase::assert(
							std::is_same<typename ForwardListType<T, Allocator>::const_iterator, decltype(result)>::value, "type");
						TestCase::assert(*result == T(), "result");
					}),

				TestCase(
					"cend",
					[] {
						ForwardListType<T, Allocator> testee(1);
						auto result = testee.cend();
						TestCase::assert(
							std::is_same<typename ForwardListType<T, Allocator>::const_iterator, decltype(result)>::value, "type");
						TestCase::assert(result == (++testee.begin()), "result");
					}),

				TestCase(
					"empty",
					[] {
						const ForwardListType<T, Allocator> testee;
						auto result = testee.empty();
						TestCase::assert(std::is_same<bool, decltype(result)>::value, "bool");
						TestCase::assert(result == true, "result");
					}),

				TestCase(
					"max_size",
					[] {
						const ForwardListType<T, Allocator> testee(3);
						auto result = testee.max_size();
						TestCase::assert(
							std::is_same<typename ForwardListType<T, Allocator>::size_type, decltype(result)>::value, "type");
						TestCase::assert(result >= 3, "result");
					}),

				TestCase(
					"front",
					[] {
						ForwardListType<T, Allocator> testee(1);
						auto& result = testee.front();
						TestCase::assert(
							std::is_same<typename ForwardListType<T, Allocator>::reference, decltype(result)>::value, "type");
						TestCase::assert(result == T(), "result");
					}),

				TestCase(
					"front const",
					[] {
						const ForwardListType<T, Allocator> testee(1);
						auto& result = testee.front();
						TestCase::assert(
							std::is_same<typename ForwardListType<T, Allocator>::const_reference, decltype(result)>::value, "type");
						TestCase::assert(result == T(), "result");
					}),

				TestCase(
					"assign range",
					[] {
						ForwardListType<T, Allocator> testee;
						testee.assign(ARRAY.begin(), ARRAY.end());
						TestCase::assert(listSize(testee) == ARRAY.size());
					}),

				TestCase(
					"assign fill value",
					[] {
						ForwardListType<T, Allocator> testee;
						testee.assign(3, T());
						TestCase::assert(listSize(testee) == 3);
					}),

				TestCase(
					"assign initializer list",
					[] {
						ForwardListType<T, Allocator> testee;
						testee.assign(INITIALIZER_LIST);
						TestCase::assert(listSize(testee) == INITIALIZER_LIST.size());
					}),

				TestCase(
					"emplace_front",
					[] {
						ForwardListType<T, Allocator> testee(1);
						testee.emplace_front();
						TestCase::assert(listSize(testee) == 2);
					}),

				TestCase(
					"push_front copy",
					[] {
						ForwardListType<T, Allocator> testee;
						T value = {};
						testee.push_front(value);
						TestCase::assert(listSize(testee) == 1);
					}),

				TestCase(
					"push_front move",
					[] {
						ForwardListType<T, Allocator> testee;
						T value = {};
						testee.push_front(std::move(value));
						TestCase::assert(listSize(testee) == 1);
					}),

				TestCase(
					"pop_front",
					[] {
						ForwardListType<T, Allocator> testee(2);
						testee.pop_front();
						TestCase::assert(listSize(testee) == 1);
					}),

				TestCase(
					"emplace_after",
					[] {
						ForwardListType<T, Allocator> testee(1);
						auto position = testee.begin();
						auto result = testee.emplace_after(position);
						TestCase::assert(
							std::is_same<typename ForwardListType<T, Allocator>::iterator, decltype(result)>::value, "type");
						TestCase::assert(listSize(testee) == 2, "result");
					}),

				TestCase(
					"insert_after single element",
					[] {
						ForwardListType<T, Allocator> testee(1);
						auto position = testee.begin();
						T value = {};
						auto result = testee.insert_after(position, value);
						TestCase::assert(
							std::is_same<typename ForwardListType<T, Allocator>::iterator, decltype(result)>::value, "type");
						TestCase::assert(listSize(testee) == 2, "result");
					}),

				TestCase(
					"insert_after fill",
					[] {
						ForwardListType<T, Allocator> testee(1);
						auto position = testee.begin();
						T value = {};
						auto result = testee.insert_after(position, 2, value);
						TestCase::assert(
							std::is_same<typename ForwardListType<T, Allocator>::iterator, decltype(result)>::value, "type");
						TestCase::assert(listSize(testee) == 3, "result");
					}),

				TestCase(
					"insert_after range",
					[] {
						ForwardListType<T, Allocator> testee(1);
						auto position = testee.begin();
						auto result = testee.insert_after(position, ARRAY.begin(), ARRAY.end());
						TestCase::assert(
							std::is_same<typename ForwardListType<T, Allocator>::iterator, decltype(result)>::value, "type");
						TestCase::assert(listSize(testee) == 1 + ARRAY.size(), "result");
					}),

				TestCase(
					"insert_after move",
					[] {
						ForwardListType<T, Allocator> testee(1);
						auto position = testee.begin();
						T value = {};
						auto result = testee.insert_after(position, std::move(value));
						TestCase::assert(
							std::is_same<typename ForwardListType<T, Allocator>::iterator, decltype(result)>::value, "type");
						TestCase::assert(listSize(testee) == 2, "result");
					}),

				TestCase(
					"insert_after initializer list",
					[] {
						ForwardListType<T, Allocator> testee(1);
						auto position = testee.begin();
						auto result = testee.insert_after(position, INITIALIZER_LIST);
						TestCase::assert(
							std::is_same<typename ForwardListType<T, Allocator>::iterator, decltype(result)>::value, "type");
						TestCase::assert(listSize(testee) == 1 + INITIALIZER_LIST.size(), "result");
					}),

				TestCase(
					"erase_after single element",
					[] {
						ForwardListType<T, Allocator> testee(3);
						auto position = testee.begin();
						auto result = testee.erase_after(position);
						TestCase::assert(
							std::is_same<typename ForwardListType<T, Allocator>::iterator, decltype(result)>::value, "type");
						TestCase::assert(listSize(testee) == 2, "result");
					}),

				TestCase(
					"erase_after range",
					[] {
						ForwardListType<T, Allocator> testee(3);
						auto first = testee.begin();
						auto last = first;
						++last;
						++last;
						auto result = testee.erase_after(first, last);
						TestCase::assert(
							std::is_same<typename ForwardListType<T, Allocator>::iterator, decltype(result)>::value, "type");
						TestCase::assert(listSize(testee) == 2, "result");
					}),

				TestCase(
					"swap",
					[] {
						ForwardListType<T, Allocator> other(3);
						ForwardListType<T, Allocator> testee(1);
						testee.swap(other);
						TestCase::assert(listSize(other) == 1, "other");
						TestCase::assert(listSize(testee) == 3, "testee");
					}),

				TestCase(
					"resize",
					[] {
						ForwardListType<T, Allocator> testee(1);
						testee.resize(3);
						TestCase::assert(listSize(testee) == 3);
					}),

				TestCase(
					"resize value",
					[] {
						ForwardListType<T, Allocator> testee(1);
						testee.resize(3, T());
						TestCase::assert(listSize(testee) == 3);
					}),

				TestCase(
					"clear",
					[] {
						ForwardListType<T, Allocator> testee(1);
						testee.clear();
						TestCase::assert(listSize(testee) == 0);
					}),

				TestCase(
					"splice_after entire list",
					[] {
						ForwardListType<T, Allocator> other(3);
						ForwardListType<T, Allocator> testee(1);
						auto position = testee.begin();
						testee.splice_after(position, other);
						TestCase::assert(listSize(other) == 0, "other");
						TestCase::assert(listSize(testee) == 4, "testee");
					}),

				TestCase(
					"splice_after entire list move",
					[] {
						ForwardListType<T, Allocator> other(3);
						ForwardListType<T, Allocator> testee(1);
						auto position = testee.begin();
						testee.splice_after(position, std::move(other));
						TestCase::assert(listSize(other) == 0, "other");
						TestCase::assert(listSize(testee) == 4, "testee");
					}),

				TestCase(
					"splice_after single element",
					[] {
						ForwardListType<T, Allocator> other(3);
						auto i = other.begin();
						ForwardListType<T, Allocator> testee(1);
						auto position = testee.begin();
						testee.splice_after(position, other, i);
						TestCase::assert(listSize(other) == 2, "other");
						TestCase::assert(listSize(testee) == 2, "testee");
					}),

				TestCase(
					"splice_after single element move",
					[] {
						ForwardListType<T, Allocator> other(3);
						auto i = other.begin();
						ForwardListType<T, Allocator> testee(1);
						auto position = testee.begin();
						testee.splice_after(position, std::move(other), i);
						TestCase::assert(listSize(other) == 2, "other");
						TestCase::assert(listSize(testee) == 2, "testee");
					}),

				TestCase(
					"splice_after range move",
					[] {
						ForwardListType<T, Allocator> other(3);
						auto first = other.begin();
						auto last = first;
						++last;
						++last;
						ForwardListType<T, Allocator> testee(1);
						auto position = testee.begin();
						testee.splice_after(position, std::move(other), first, last);
						TestCase::assert(listSize(other) == 2, "other");
						TestCase::assert(listSize(testee) == 2, "testee");
					}),

				TestCase(
					"splice_after range",
					[] {
						ForwardListType<T, Allocator> other(3);
						auto first = other.begin();
						auto last = first;
						++last;
						++last;
						ForwardListType<T, Allocator> testee(1);
						auto position = testee.begin();
						testee.splice_after(position, other, first, last);
						TestCase::assert(listSize(other) == 2, "other");
						TestCase::assert(listSize(testee) == 2, "testee");
					}),

				TestCase(
					"remove",
					[] {
						ForwardListType<T, Allocator> testee(1);
						testee.remove(T());
						TestCase::assert(listSize(testee) == 0);
					}),

				TestCase(
					"remove_if",
					[] {
						ForwardListType<T, Allocator> testee(1);
						testee.remove_if([](const T&) -> bool { return true; });
						TestCase::assert(listSize(testee) == 0);
					}),

				TestCase(
					"unique",
					[] {
						ForwardListType<T, Allocator> testee(3);
						testee.unique();
						TestCase::assert(listSize(testee) == 1);
					}),

				TestCase(
					"unique with predicate",
					[] {
						ForwardListType<T, Allocator> testee(3);
						testee.unique([](const T& lhs, const T& rhs) -> bool { return lhs == rhs; });
						TestCase::assert(listSize(testee) == 1);
					}),

				TestCase(
					"merge",
					[] {
						ForwardListType<T, Allocator> other(2);
						ForwardListType<T, Allocator> testee(1);
						testee.merge(other);
						TestCase::assert(listSize(testee) == 3);
					}),

				TestCase(
					"merge move",
					[] {
						ForwardListType<T, Allocator> other(2);
						ForwardListType<T, Allocator> testee(1);
						testee.merge(std::move(other));
						TestCase::assert(listSize(testee) == 3);
					}),

				TestCase(
					"merge with predicate",
					[] {
						ForwardListType<T, Allocator> other(2);
						ForwardListType<T, Allocator> testee(1);
						testee.merge(other, [](const T& lhs, const T& rhs) -> bool { return lhs < rhs; });
						TestCase::assert(listSize(testee) == 3);
					}),

				TestCase(
					"merge with predicate move",
					[] {
						ForwardListType<T, Allocator> other(2);
						ForwardListType<T, Allocator> testee(1);
						testee.merge(std::move(other), [](const T& lhs, const T& rhs) -> bool { return lhs < rhs; });
						TestCase::assert(listSize(testee) == 3);
					}),

				TestCase(
					"sort",
					[] {
						ForwardListType<T, Allocator> testee(3);
						testee.sort();
						TestCase::assert(listSize(testee) == 3);
					}),

				TestCase(
					"sort with predicate",
					[] {
						ForwardListType<T, Allocator> testee(3);
						testee.sort([](const T& lhs, const T& rhs) -> bool { return lhs < rhs; });
						TestCase::assert(listSize(testee) == 3);
					}),

				TestCase(
					"reverse",
					[] {
						ForwardListType<T, Allocator> testee(3);
						testee.reverse();
						TestCase::assert(listSize(testee) == 3);
					}),

				TestCase(
					"get_allocator",
					[] {
						ForwardListType<T, Allocator> testee;
						auto result = testee.get_allocator();
						TestCase::assert(
							std::is_same<typename ForwardListType<T, Allocator>::allocator_type, decltype(result)>::value);
					}),

				TestCase(
					"operator==",
					[] {
						ForwardListType<T, Allocator> lhs(3);
						ForwardListType<T, Allocator> rhs(3);
						auto result = (lhs == rhs);
						TestCase::assert(std::is_same<bool, decltype(result)>::value, "type");
						TestCase::assert(result == true, "result");
					}),

				TestCase(
					"operator!=",
					[] {
						ForwardListType<T, Allocator> lhs(2);
						ForwardListType<T, Allocator> rhs(3);
						auto result = (lhs != rhs);
						TestCase::assert(std::is_same<bool, decltype(result)>::value, "type");
						TestCase::assert(result == true, "result");
					}),

				TestCase(
					"operator<",
					[] {
						ForwardListType<T, Allocator> lhs(2);
						ForwardListType<T, Allocator> rhs(3);
						auto result = (lhs < rhs);
						TestCase::assert(std::is_same<bool, decltype(result)>::value, "type");
						TestCase::assert(result == true, "result");
					}),

				TestCase(
					"operator<=",
					[] {
						ForwardListType<T, Allocator> lhs(2);
						ForwardListType<T, Allocator> rhs(3);
						auto result = (lhs <= rhs);
						TestCase::assert(std::is_same<bool, decltype(result)>::value, "type");
						TestCase::assert(result == true, "result");
					}),

				TestCase(
					"operator>",
					[] {
						ForwardListType<T, Allocator> lhs(3);
						ForwardListType<T, Allocator> rhs(2);
						auto result = (lhs > rhs);
						TestCase::assert(std::is_same<bool, decltype(result)>::value, "type");
						TestCase::assert(result == true, "result");
					}),

				TestCase(
					"operator>=",
					[] {
						ForwardListType<T, Allocator> lhs(3);
						ForwardListType<T, Allocator> rhs(2);
						auto result = (lhs >= rhs);
						TestCase::assert(std::is_same<bool, decltype(result)>::value, "type");
						TestCase::assert(result == true, "result");
					}),

				TestCase("swap lhs rhs", [] {
					ForwardListType<T, Allocator> lhs(3);
					ForwardListType<T, Allocator> rhs(2);
					swap(lhs, rhs);
					TestCase::assert(listSize(lhs) == 2, "lhs");
					TestCase::assert(listSize(rhs) == 3, "rhs");
				})})
	{
	}

	static typename ForwardListType<T, Allocator>::size_type listSize(const ForwardListType<T, Allocator>& list)
	{
		typename ForwardListType<T, Allocator>::size_type result = 0;
		for (auto i = list.begin(); i != list.end(); ++i) {
			++result;
		}
		return result;
	}

	static const InitializerListType INITIALIZER_LIST;
	static const ArrayType ARRAY;
};

template<template<typename...> class ForwardListType, typename T, typename Allocator>
const typename ForwardListTestSuite<ForwardListType, T, Allocator>::InitializerListType
	ForwardListTestSuite<ForwardListType, T, Allocator>::INITIALIZER_LIST = {T()};

template<template<typename...> class ForwardListType, typename T, typename Allocator>
const typename ForwardListTestSuite<ForwardListType, T, Allocator>::ArrayType
	ForwardListTestSuite<ForwardListType, T, Allocator>::ARRAY = {T()};

} // namespace Testee

#endif // Testee_ForwardListTestSuite_INCLUDED
