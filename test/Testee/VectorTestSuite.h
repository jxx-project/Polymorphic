//
// Copyright (C) 2018 Dr. Michael Steffens
//
// SPDX-License-Identifier:		BSL-1.0
//


#ifndef Testee_VectorTestSuite_INCLUDED
#define Testee_VectorTestSuite_INCLUDED

#include "Testee/TestSuite.h"
#include <array>

namespace Testee {

template<typename T>
T makeDefault()
{
	return T();
}

// Conditionally enabled test executors handling the std::vector<bool, Allocator> specialization.

template<template<typename...> class VectorType, typename T, typename Allocator, typename Enable = void>
class TestSubscriptOperator;

template<template<typename...> class VectorType, typename T, typename Allocator, typename Enable = void>
class TestSubscriptOperatorConst;

template<template<typename...> class VectorType, typename T, typename Allocator, typename Enable = void>
class TestAt;

template<template<typename...> class VectorType, typename T, typename Allocator, typename Enable = void>
class TestAtConst;

template<template<typename...> class VectorType, typename T, typename Allocator, typename Enable = void>
class TestFront;

template<template<typename...> class VectorType, typename T, typename Allocator, typename Enable = void>
class TestFrontConst;

template<template<typename...> class VectorType, typename T, typename Allocator, typename Enable = void>
class TestBack;

template<template<typename...> class VectorType, typename T, typename Allocator, typename Enable = void>
class TestBackConst;

template<template<typename...> class VectorType, typename T, typename Allocator, typename Enable = void>
class TestData;

template<template<typename...> class VectorType, typename T, typename Allocator, typename Enable = void>
class TestDataConst;

template<template<typename...> class VectorType, typename T, typename Allocator, typename Enable = void>
class TestFlip;

template<template<typename...> class VectorType, typename T, typename Allocator, typename Enable = void>
class TestSwapElements;


/// Test VectorType C++-11 standard vector interface.
template< template<typename...> class VectorType, typename T, typename Allocator = std::allocator<T> >
class VectorTestSuite : public TestSuite
{
public:
	typedef std::initializer_list<T> InitializerListType;
	typedef std::array<T, 1> ArrayType;

	VectorTestSuite() : TestSuite({

			TestCase("typedefs", [this]
					 {
						 TestCase::assert(std::is_same<typename VectorType<T, Allocator>::value_type, T>::value, "value_type");
						 TestCase::assert(std::is_class<typename VectorType<T, Allocator>::allocator_type>::value, "allocator_type");
						 if (!std::is_same<bool, T>::value) {
							 TestCase::assert(std::is_same<typename VectorType<T, Allocator>::reference, T&>::value, "reference");
							 TestCase::assert(std::is_same<typename VectorType<T, Allocator>::const_reference, const T&>::value, "const_reference");
						 } else {
							 TestCase::assert(std::is_class<typename VectorType<T, Allocator>::reference>::value, "reference");
							 TestCase::assert(std::is_same<typename VectorType<T, Allocator>::const_reference, T>::value, "const_reference");
						 }
					 }),

			TestCase("ctor default", [this]
					 {
						 VectorType<T, Allocator> testee;
						 TestCase::assert(testee.size() == 0);
					 }),

			TestCase("ctor fill", [this]
					 {
						 VectorType<T, Allocator> testee(3);
						 TestCase::assert(testee.size() == 3);
					 }),

			TestCase("ctor fill value", [this]
					 {
						 VectorType<T, Allocator> testee(3, T());
						 TestCase::assert(testee.size() == 3);
					 }),

			TestCase("ctor copy", [this]
					 {
						 const VectorType<T, Allocator> other(3);
						 VectorType<T, Allocator> testee(other);
						 TestCase::assert(testee.size() == 3);
					 }),

			TestCase("ctor copy with allocator", [this]
					 {
						 const VectorType<T, Allocator> other(3);
						 VectorType<T, Allocator> testee(other, std::allocator<T>());
						 TestCase::assert(testee.size() == 3);
					 }),

			TestCase("ctor move", [this]
					 {
						 VectorType<T, Allocator> other(3);
						 VectorType<T, Allocator> testee(std::move(other));
						 TestCase::assert(other.size() == 0, "other");
						 TestCase::assert(testee.size() == 3, "testee");
					 }),

			TestCase("ctor move with allocator", [this]
					 {
						 VectorType<T, Allocator> other(3);
						 VectorType<T, Allocator> testee(std::move(other), std::allocator<T>());
						 TestCase::assert(other.size() == 0, "other");
						 TestCase::assert(testee.size() == 3, "testee");
					 }),

			TestCase("ctor range", [this]
					 {
						 VectorType<T, Allocator> testee(ARRAY.begin(), ARRAY.end());
						 TestCase::assert(testee.size() == ARRAY.size());
					 }),

			TestCase("ctor initializer list", [this]
					 {
						 VectorType<T, Allocator> testee(INITIALIZER_LIST);
						 TestCase::assert(testee.size() == INITIALIZER_LIST.size());
					 }),

			TestCase("operator= copy", [this]
					 {
						 const VectorType<T, Allocator> other(3);
						 VectorType<T, Allocator> testee;
						 auto& result = (testee = other);
						 TestCase::assert(std::is_same<VectorType<T, Allocator>&, decltype(result)>::value, "type");
						 TestCase::assert(testee.size() == 3, "result");
					 }),

			TestCase("operator= move", [this]
					 {
						 VectorType<T, Allocator> other(3);
						 VectorType<T, Allocator> testee;
						 auto& result = (testee = std::move(other));
						 TestCase::assert(std::is_same<VectorType<T, Allocator>&, decltype(result)>::value, "type");
						 TestCase::assert(other.size() == 0, "other");
						 TestCase::assert(testee.size() == 3, "testee");
					 }),

			TestCase("operator= initializer list", [this]
					 {
						 VectorType<T, Allocator> testee;
						 auto& result = (testee = INITIALIZER_LIST);
						 TestCase::assert(std::is_same<VectorType<T, Allocator>&, decltype(result)>::value, "type");
						 TestCase::assert(testee.size() == INITIALIZER_LIST.size(), "result");
					 }),

			TestCase("begin", [this]
					 {
						 VectorType<T, Allocator> testee(1);
						 auto result = testee.begin();
						 TestCase::assert(std::is_same<typename VectorType<T, Allocator>::iterator, decltype(result)>::value, "type");
						 TestCase::assert(*result == T(), "result");
					 }),

			TestCase("begin const", [this]
					 {
						 const VectorType<T, Allocator> testee(1);
						 auto result = testee.begin();
						 TestCase::assert(std::is_same<typename VectorType<T, Allocator>::const_iterator, decltype(result)>::value, "type");
						 TestCase::assert(*result == T(), "result");
					 }),

			TestCase("end", [this]
					 {
						 VectorType<T, Allocator> testee(1);
						 auto result = testee.end();
						 TestCase::assert(std::is_same<typename VectorType<T, Allocator>::iterator, decltype(result)>::value, "type");
						 TestCase::assert(*(--result) == T(), "result");
					 }),

			TestCase("end const", [this]
					 {
						 const VectorType<T, Allocator> testee(1);
						 auto result = testee.end();
						 TestCase::assert(std::is_same<typename VectorType<T, Allocator>::const_iterator, decltype(result)>::value, "type");
						 TestCase::assert(*(--result) == T(), "result");
					 }),

			TestCase("rbegin", [this]
					 {
						 VectorType<T, Allocator> testee(1);
						 auto result = testee.rbegin();
						 TestCase::assert(std::is_same<typename VectorType<T, Allocator>::reverse_iterator, decltype(result)>::value, "type");
						 TestCase::assert(*result == T(), "result");
					 }),

			TestCase("rbegin const", [this]
					 {
						 const VectorType<T, Allocator> testee(1);
						 auto result = testee.rbegin();
						 TestCase::assert(std::is_same<typename VectorType<T, Allocator>::const_reverse_iterator, decltype(result)>::value, "type");
						 TestCase::assert(*result == T(), "result");
					 }),

			TestCase("rend", [this]
					 {
						 VectorType<T, Allocator> testee(1);
						 auto result = testee.rend();
						 TestCase::assert(std::is_same<typename VectorType<T, Allocator>::reverse_iterator, decltype(result)>::value, "type");
						 TestCase::assert(*(--result) == T(), "result");
					 }),

			TestCase("rend const", [this]
					 {
						 const VectorType<T, Allocator> testee(1);
						 auto result = testee.rend();
						 TestCase::assert(std::is_same<typename VectorType<T, Allocator>::const_reverse_iterator, decltype(result)>::value, "type");
						 TestCase::assert(*(--result) == T(), "result");
					 }),

			TestCase("cbegin", [this]
					 {
						 VectorType<T, Allocator> testee(1);
						 auto result = testee.cbegin();
						 TestCase::assert(std::is_same<typename VectorType<T, Allocator>::const_iterator, decltype(result)>::value, "type");
						 TestCase::assert(*result == T(), "result");
					 }),

			TestCase("cend", [this]
					 {
						 VectorType<T, Allocator> testee(1);
						 auto result = testee.cend();
						 TestCase::assert(std::is_same<typename VectorType<T, Allocator>::const_iterator, decltype(result)>::value, "type");
						 TestCase::assert(*(--result) == T(), "result");
					 }),

			TestCase("crbegin", [this]
					 {
						 VectorType<T, Allocator> testee(1);
						 auto result = testee.crbegin();
						 TestCase::assert(std::is_same<typename VectorType<T, Allocator>::const_reverse_iterator, decltype(result)>::value, "type");
						 TestCase::assert(*result == T(), "result");
					 }),

			TestCase("crend", [this]
					 {
						 VectorType<T, Allocator> testee(1);
						 auto result = testee.crend();
						 TestCase::assert(std::is_same<typename VectorType<T, Allocator>::const_reverse_iterator, decltype(result)>::value, "type");
						 TestCase::assert(*(--result) == T(), "result");
					 }),

			TestCase("empty", [this]
					 {
						 const VectorType<T, Allocator> testee;
						 auto result = testee.empty();
						 TestCase::assert(std::is_same<bool, decltype(result)>::value, "bool");
						 TestCase::assert(result == true, "result");
					 }),

			TestCase("size", [this]
					 {
						 const VectorType<T, Allocator> testee(3);
						 auto result = testee.size();
						 TestCase::assert(std::is_same<typename VectorType<T, Allocator>::size_type, decltype(result)>::value, "type");
						 TestCase::assert(result == 3, "result");
					 }),

			TestCase("max_size", [this]
					 {
						 const VectorType<T, Allocator> testee(3);
						 auto result = testee.max_size();
						 TestCase::assert(std::is_same<typename VectorType<T, Allocator>::size_type, decltype(result)>::value, "type");
						 TestCase::assert(result >= 3, "result");
					 }),

			TestCase("resize", [this]
					 {
						 VectorType<T, Allocator> testee(1);
						 testee.resize(3);
						 TestCase::assert(testee.size() == 3);
					 }),

			TestCase("resize value", [this]
					 {
						 VectorType<T, Allocator> testee(1);
						 testee.resize(3, T());
						 TestCase::assert(testee.size() == 3);
					 }),

			TestCase("capacity", [this]
					 {
						 const VectorType<T, Allocator> testee(3);
						 auto result = testee.capacity();
						 TestCase::assert(std::is_same<typename VectorType<T, Allocator>::size_type, decltype(result)>::value, "type");
						 TestCase::assert(result >= 3, "result");
					 }),

			TestCase("reserve", [this]
					 {
						 VectorType<T, Allocator> testee(1);
						 testee.reserve(3);
						 TestCase::assert(testee.capacity() >= 3);
					 }),

			TestCase("shrink_to_fit", [this]
					 {
						 VectorType<T, Allocator> testee(1);
						 testee.reserve(3);
						 testee.shrink_to_fit();
						 if (!std::is_same<bool, T>::value) {
							 TestCase::assert(testee.capacity() == testee.size());
						 }
					 }),

			TestCase("operator[]", TestSubscriptOperator<VectorType, T, Allocator>()),

			TestCase("operator[]", TestSubscriptOperatorConst<VectorType, T, Allocator>()),

			TestCase("at", TestAt<VectorType, T, Allocator>()),

			TestCase("at const", TestAtConst<VectorType, T, Allocator>()),

			TestCase("front", TestFront<VectorType, T, Allocator>()),

			TestCase("front const", TestFrontConst<VectorType, T, Allocator>()),

			TestCase("back", TestBack<VectorType, T, Allocator>()),

			TestCase("back const", TestBackConst<VectorType, T, Allocator>()),

			TestCase("data", TestData<VectorType, T, Allocator>()),

			TestCase("data const", TestDataConst<VectorType, T, Allocator>()),

			TestCase("assign range", [this]
					 {
						 VectorType<T, Allocator> testee;
						 testee.assign(ARRAY.begin(), ARRAY.end());
						 TestCase::assert(testee.size() == ARRAY.size());
					 }),

			TestCase("assign fill value", [this]
					 {
						 VectorType<T, Allocator> testee;
						 testee.assign(3, T());
						 TestCase::assert(testee.size() == 3);
					 }),

			TestCase("assign initializer list", [this]
					 {
						 VectorType<T, Allocator> testee;
						 testee.assign(INITIALIZER_LIST);
						 TestCase::assert(testee.size() == INITIALIZER_LIST.size());
					 }),

			TestCase("push_back copy", [this]
					 {
						 VectorType<T, Allocator> testee;
						 T value = {};
						 testee.push_back(value);
						 TestCase::assert(testee.size() == 1);
					 }),

			TestCase("push_back move", [this]
					 {
						 VectorType<T, Allocator> testee;
						 T value = {};
						 testee.push_back(std::move(value));
						 TestCase::assert(testee.size() == 1);
					 }),

			TestCase("pop_back", [this]
					 {
						 VectorType<T, Allocator> testee(2);
						 testee.pop_back();
						 TestCase::assert(testee.size() == 1);
					 }),

			TestCase("insert single element", [this]
					 {
						 VectorType<T, Allocator> testee(1);
						 auto position = testee.begin();
						 T value = {};
						 auto result = testee.insert(position, value);
						 TestCase::assert(std::is_same<typename VectorType<T, Allocator>::iterator, decltype(result)>::value, "type");
						 TestCase::assert(testee.size() == 2, "result");
					 }),

			TestCase("insert fill", [this]
					 {
						 VectorType<T, Allocator> testee(1);
						 auto position = testee.begin();
						 T value = {};
						 auto result = testee.insert(position, 2, value);
						 TestCase::assert(std::is_same<typename VectorType<T, Allocator>::iterator, decltype(result)>::value, "type");
						 TestCase::assert(testee.size() == 3, "result");
					 }),

			TestCase("insert range", [this]
					 {
						 VectorType<T, Allocator> testee(1);
						 auto position = testee.begin();
						 auto result = testee.insert(position, ARRAY.begin(), ARRAY.end());
						 TestCase::assert(std::is_same<typename VectorType<T, Allocator>::iterator, decltype(result)>::value, "type");
						 TestCase::assert(testee.size() == 1 + ARRAY.size(), "result");
					 }),

			TestCase("insert move", [this]
					 {
						 VectorType<T, Allocator> testee(1);
						 auto position = testee.begin();
						 T value = {};
						 auto result = testee.insert(position, std::move(value));
						 TestCase::assert(std::is_same<typename VectorType<T, Allocator>::iterator, decltype(result)>::value, "type");
						 TestCase::assert(testee.size() == 2, "result");
					 }),

			TestCase("insert initializer list", [this]
					 {
						 VectorType<T, Allocator> testee(1);
						 auto position = testee.begin();
						 auto result = testee.insert(position, INITIALIZER_LIST);
						 TestCase::assert(std::is_same<typename VectorType<T, Allocator>::iterator, decltype(result)>::value, "type");
						 TestCase::assert(testee.size() == 1 + INITIALIZER_LIST.size(), "result");
					 }),

			TestCase("erase single element", [this]
					 {
						 VectorType<T, Allocator> testee(3);
						 auto position = testee.begin();
						 auto result = testee.erase(position);
						 TestCase::assert(std::is_same<typename VectorType<T, Allocator>::iterator, decltype(result)>::value, "type");
						 TestCase::assert(testee.size() == 2, "result");
					 }),

			TestCase("erase range", [this]
					 {
						 VectorType<T, Allocator> testee(3);
						 auto first = testee.begin();
						 auto last = first + 2;
						 auto result = testee.erase(first, last);
						 TestCase::assert(std::is_same<typename VectorType<T, Allocator>::iterator, decltype(result)>::value, "type");
						 TestCase::assert(testee.size() == 1, "result");
					 }),

			TestCase("flip", TestFlip<VectorType, T, Allocator>()),

			TestCase("swap", [this]
					 {
						 VectorType<T, Allocator> other(3);
						 VectorType<T, Allocator> testee(1);
						 testee.swap(other);
						 TestCase::assert(other.size() == 1, "other");
						 TestCase::assert(testee.size() == 3, "testee");
					 }),

			TestCase("swap elements", TestSwapElements<VectorType, T, Allocator>()),

			TestCase("clear", [this]
					 {
						 VectorType<T, Allocator> testee(1);
						 testee.clear();
						 TestCase::assert(testee.size() == 0);
					 }),

			TestCase("emplace", [this]
					 {
						 VectorType<T, Allocator> testee(1);
						 auto position = testee.begin();
						 auto result = testee.emplace(position);
						 TestCase::assert(std::is_same<typename VectorType<T, Allocator>::iterator, decltype(result)>::value, "type");
						 TestCase::assert(testee.size() == 2, "result");
					 }),

			TestCase("emplace_back", [this]
					 {
						 VectorType<T, Allocator> testee(1);
						 testee.emplace_back();
						 TestCase::assert(testee.size() == 2);
					 }),

			TestCase("get_allocator", [this]
					 {
						 VectorType<T, Allocator> testee;
						 auto result = testee.get_allocator();
						 TestCase::assert(std::is_same<typename VectorType<T, Allocator>::allocator_type, decltype(result)>::value);
					 }),

			TestCase("operator==", [this]
					 {
						 VectorType<T, Allocator> lhs(3);
						 VectorType<T, Allocator> rhs(3);
						 auto result = (lhs == rhs);
						 TestCase::assert(std::is_same<bool, decltype(result)>::value, "type");
						 TestCase::assert(result == true, "result");
					 }),

			TestCase("operator!=", [this]
					 {
						 VectorType<T, Allocator> lhs(2);
						 VectorType<T, Allocator> rhs(3);
						 auto result = (lhs != rhs);
						 TestCase::assert(std::is_same<bool, decltype(result)>::value, "type");
						 TestCase::assert(result == true, "result");
					 }),

			TestCase("operator<", [this]
					 {
						 VectorType<T, Allocator> lhs(2);
						 VectorType<T, Allocator> rhs(3);
						 auto result = (lhs < rhs);
						 TestCase::assert(std::is_same<bool, decltype(result)>::value, "type");
						 TestCase::assert(result == true, "result");
					 }),

			TestCase("operator<=", [this]
					 {
						 VectorType<T, Allocator> lhs(2);
						 VectorType<T, Allocator> rhs(3);
						 auto result = (lhs <= rhs);
						 TestCase::assert(std::is_same<bool, decltype(result)>::value, "type");
						 TestCase::assert(result == true, "result");
					 }),

			TestCase("operator>", [this]
					 {
						 VectorType<T, Allocator> lhs(3);
						 VectorType<T, Allocator> rhs(2);
						 auto result = (lhs > rhs);
						 TestCase::assert(std::is_same<bool, decltype(result)>::value, "type");
						 TestCase::assert(result == true, "result");
					 }),

			TestCase("operator>=", [this]
					 {
						 VectorType<T, Allocator> lhs(3);
						 VectorType<T, Allocator> rhs(2);
						 auto result = (lhs >= rhs);
						 TestCase::assert(std::is_same<bool, decltype(result)>::value, "type");
						 TestCase::assert(result == true, "result");
					 }),

			TestCase("swap lhs rhs", [this]
					 {
						 VectorType<T, Allocator> lhs(3);
						 VectorType<T, Allocator> rhs(2);
						 swap(lhs, rhs);
						 TestCase::assert(lhs.size() == 2, "lhs");
						 TestCase::assert(rhs.size() == 3, "rhs");
					 })
		})
	{
	}

	static const InitializerListType INITIALIZER_LIST;
	static const ArrayType ARRAY;
};

template<template<typename...> class VectorType, typename T, typename Allocator>
const typename VectorTestSuite<VectorType, T, Allocator>::InitializerListType VectorTestSuite<VectorType, T, Allocator>::INITIALIZER_LIST = {makeDefault<T>()};

template<template<typename...> class VectorType, typename T, typename Allocator>
const typename VectorTestSuite<VectorType, T, Allocator>::ArrayType VectorTestSuite<VectorType, T, Allocator>::ARRAY = {makeDefault<T>()};


// Conditionally enabled test executors handling the std::vector<bool, Allocator> specialization.

template<template<typename...> class VectorType, typename T, typename Allocator>
class TestSubscriptOperator<VectorType, T, Allocator, typename std::enable_if<!std::is_same<bool, T>::value>::type>
{
public:
	void operator()()
	{
		VectorType<T, Allocator> testee(1);
		auto& result = testee[0];
		TestCase::assert(std::is_same<typename VectorType<T, Allocator>::reference, decltype(result)>::value, "type");
		TestCase::assert(result == T(), "result");
	}
};

template<template<typename...> class VectorType, typename T, typename Allocator>
class TestSubscriptOperator<VectorType, T, Allocator, typename std::enable_if<std::is_same<bool, T>::value>::type>
{
public:
	void operator()()
	{
		VectorType<T, Allocator> testee(1);
		auto result = testee[0];
		TestCase::assert(std::is_same<typename VectorType<T, Allocator>::reference, decltype(result)>::value, "type");
		TestCase::assert(result == T(), "result");
	}
};

template<template<typename...> class VectorType, typename T, typename Allocator>
class TestSubscriptOperatorConst<VectorType, T, Allocator, typename std::enable_if<!std::is_same<bool, T>::value>::type>
{
public:
	void operator()()
	{
		const VectorType<T, Allocator> testee(1);
		auto& result = testee[0];
		TestCase::assert(std::is_same<typename VectorType<T, Allocator>::const_reference, decltype(result)>::value, "type");
		TestCase::assert(result == T(), "result");
	}
};

template<template<typename...> class VectorType, typename T, typename Allocator>
class TestSubscriptOperatorConst<VectorType, T, Allocator, typename std::enable_if<std::is_same<bool, T>::value>::type>
{
public:
	void operator()()
	{
		const VectorType<T, Allocator> testee(1);
		auto result = testee[0];
		TestCase::assert(std::is_same<typename VectorType<T, Allocator>::const_reference, decltype(result)>::value, "type");
		TestCase::assert(result == T(), "result");
	}
};

template<template<typename...> class VectorType, typename T, typename Allocator>
class TestAt<VectorType, T, Allocator, typename std::enable_if<!std::is_same<bool, T>::value>::type>
{
public:
	void operator()()
	{
		VectorType<T, Allocator> testee(1);
		auto& result = testee.at(0);
		TestCase::assert(std::is_same<typename VectorType<T, Allocator>::reference, decltype(result)>::value, "type");
		TestCase::assert(result == T(), "result");
	}
};

template<template<typename...> class VectorType, typename T, typename Allocator>
class TestAt<VectorType, T, Allocator, typename std::enable_if<std::is_same<bool, T>::value>::type>
{
public:
	void operator()()
	{
		VectorType<T, Allocator> testee(1);
		auto result = testee.at(0);
		TestCase::assert(std::is_same<typename VectorType<T, Allocator>::reference, decltype(result)>::value, "type");
		TestCase::assert(result == T(), "result");
	}
};

template<template<typename...> class VectorType, typename T, typename Allocator>
class TestAtConst<VectorType, T, Allocator, typename std::enable_if<!std::is_same<bool, T>::value>::type>
{
public:
	void operator()()
	{
		const VectorType<T, Allocator> testee(1);
		auto& result = testee.at(0);
		TestCase::assert(std::is_same<typename VectorType<T, Allocator>::const_reference, decltype(result)>::value, "type");
		TestCase::assert(result == T(), "result");
	}
};

template<template<typename...> class VectorType, typename T, typename Allocator>
class TestAtConst<VectorType, T, Allocator, typename std::enable_if<std::is_same<bool, T>::value>::type>
{
public:
	void operator()()
	{
		const VectorType<T, Allocator> testee(1);
		auto result = testee.at(0);
		TestCase::assert(std::is_same<typename VectorType<T, Allocator>::const_reference, decltype(result)>::value, "type");
		TestCase::assert(result == T(), "result");
	}
};

template<template<typename...> class VectorType, typename T, typename Allocator>
class TestFront<VectorType, T, Allocator, typename std::enable_if<!std::is_same<bool, T>::value>::type>
{
public:
	void operator()()
	{
		VectorType<T, Allocator> testee(1);
		auto& result = testee.front();
		TestCase::assert(std::is_same<typename VectorType<T, Allocator>::reference, decltype(result)>::value, "type");
		TestCase::assert(result == T(), "result");
	}
};

template<template<typename...> class VectorType, typename T, typename Allocator>
class TestFront<VectorType, T, Allocator, typename std::enable_if<std::is_same<bool, T>::value>::type>
{
public:
	void operator()()
	{
		VectorType<T, Allocator> testee(1);
		auto result = testee.front();
		TestCase::assert(std::is_same<typename VectorType<T, Allocator>::reference, decltype(result)>::value, "type");
		TestCase::assert(result == T(), "result");
	}
};

template<template<typename...> class VectorType, typename T, typename Allocator>
class TestFrontConst<VectorType, T, Allocator, typename std::enable_if<!std::is_same<bool, T>::value>::type>
{
public:
	void operator()()
	{
		const VectorType<T, Allocator> testee(1);
		auto& result = testee.front();
		TestCase::assert(std::is_same<typename VectorType<T, Allocator>::const_reference, decltype(result)>::value, "type");
		TestCase::assert(result == T(), "result");
	}
};

template<template<typename...> class VectorType, typename T, typename Allocator>
class TestFrontConst<VectorType, T, Allocator, typename std::enable_if<std::is_same<bool, T>::value>::type>
{
public:
	void operator()()
	{
		const VectorType<T, Allocator> testee(1);
		auto result = testee.front();
		TestCase::assert(std::is_same<typename VectorType<T, Allocator>::const_reference, decltype(result)>::value, "type");
		TestCase::assert(result == T(), "result");
	}
};

template<template<typename...> class VectorType, typename T, typename Allocator>
class TestBack<VectorType, T, Allocator, typename std::enable_if<!std::is_same<bool, T>::value>::type>
{
public:
	void operator()()
	{
		VectorType<T, Allocator> testee(1);
		auto& result = testee.back();
		TestCase::assert(std::is_same<typename VectorType<T, Allocator>::reference, decltype(result)>::value, "type");
		TestCase::assert(result == T(), "result");
	}
};

template<template<typename...> class VectorType, typename T, typename Allocator>
class TestBack<VectorType, T, Allocator, typename std::enable_if<std::is_same<bool, T>::value>::type>
{
public:
	void operator()()
	{
		VectorType<T, Allocator> testee(1);
		auto result = testee.back();
		TestCase::assert(std::is_same<typename VectorType<T, Allocator>::reference, decltype(result)>::value, "type");
		TestCase::assert(result == T(), "result");
	}
};

template<template<typename...> class VectorType, typename T, typename Allocator>
class TestBackConst<VectorType, T, Allocator, typename std::enable_if<!std::is_same<bool, T>::value>::type>
{
public:
	void operator()()
	{
		const VectorType<T, Allocator> testee(1);
		auto& result = testee.back();
		TestCase::assert(std::is_same<typename VectorType<T, Allocator>::const_reference, decltype(result)>::value, "type");
		TestCase::assert(result == T(), "result");
	}
};

template<template<typename...> class VectorType, typename T, typename Allocator>
class TestBackConst<VectorType, T, Allocator, typename std::enable_if<std::is_same<bool, T>::value>::type>
{
public:
	void operator()()
	{
		const VectorType<T, Allocator> testee(1);
		auto result = testee.back();
		TestCase::assert(std::is_same<typename VectorType<T, Allocator>::const_reference, decltype(result)>::value, "type");
		TestCase::assert(result == T(), "result");
	}
};

template<template<typename...> class VectorType, typename T, typename Allocator>
class TestData<VectorType, T, Allocator, typename std::enable_if<!std::is_same<bool, T>::value>::type>
{
public:
	void operator()()
	{
		VectorType<T, Allocator> testee(1);
		auto result = testee.data();
		TestCase::assert(std::is_same<typename VectorType<T, Allocator>::pointer, decltype(result)>::value, "pointer");
		TestCase::assert(*result == T(), "result");
	}
};

template<template<typename...> class VectorType, typename T, typename Allocator>
class TestData<VectorType, T, Allocator, typename std::enable_if<std::is_same<bool, T>::value>::type>
{
public:
	void operator()()
	{
	}
};

template<template<typename...> class VectorType, typename T, typename Allocator>
class TestDataConst<VectorType, T, Allocator, typename std::enable_if<!std::is_same<bool, T>::value>::type>
{
public:
	void operator()()
	{
		const VectorType<T, Allocator> testee(1);
		auto result = testee.data();
		TestCase::assert(std::is_same<typename VectorType<T, Allocator>::const_pointer, decltype(result)>::value, "const_pointer");
		TestCase::assert(*result == T(), "result");
	}
};

template<template<typename...> class VectorType, typename T, typename Allocator>
class TestDataConst<VectorType, T, Allocator, typename std::enable_if<std::is_same<bool, T>::value>::type>
{
public:
	void operator()()
	{
	}
};




template<template<typename...> class VectorType, typename T, typename Allocator>
class TestFlip<VectorType, T, Allocator, typename std::enable_if<!std::is_same<bool, T>::value>::type>
{
public:
	void operator()()
	{
	}
};

template<template<typename...> class VectorType, typename T, typename Allocator>
class TestFlip<VectorType, T, Allocator, typename std::enable_if<std::is_same<bool, T>::value>::type>
{
public:
	void operator()()
	{
		VectorType<bool, Allocator> testee({true, false});
		testee.flip();
		TestCase::assert(testee.front() == false && testee.back() == true);
	}
};

template<template<typename...> class VectorType, typename T, typename Allocator>
class TestSwapElements<VectorType, T, Allocator, typename std::enable_if<!std::is_same<bool, T>::value>::type>
{
public:
	void operator()()
	{
	}
};

template<template<typename...> class VectorType, typename T, typename Allocator>
class TestSwapElements<VectorType, T, Allocator, typename std::enable_if<std::is_same<bool, T>::value>::type>
{
public:
	void operator()()
	{
		VectorType<bool, Allocator> testee({true, false});
		VectorType<T, Allocator>::swap(testee.front(), testee.back());
		TestCase::assert(testee.front() == false && testee.back() == true);
	}
};

} // namespace Testee

#endif // Testee_VectorTestSuite_INCLUDED
