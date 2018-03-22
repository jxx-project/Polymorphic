//
// Copyright (C) 2018 Dr. Michael Steffens
//
// SPDX-License-Identifier:		BSL-1.0
//


#ifndef Testee_VectorTestSuite_INCLUDED
#define Testee_VectorTestSuite_INCLUDED

#include "Testee/TestSuite.h"

namespace Testee {

// Conditionally enabled test executors handling the std::vector<bool> specialization.

template<template<typename...> class VectorType, typename T, typename Enable = void>
class TestSubscriptOperator;

template<template<typename...> class VectorType, typename T, typename Enable = void>
class TestSubscriptOperatorConst;

template<template<typename...> class VectorType, typename T, typename Enable = void>
class TestAt;

template<template<typename...> class VectorType, typename T, typename Enable = void>
class TestAtConst;

template<template<typename...> class VectorType, typename T, typename Enable = void>
class TestFront;

template<template<typename...> class VectorType, typename T, typename Enable = void>
class TestFrontConst;

template<template<typename...> class VectorType, typename T, typename Enable = void>
class TestBack;

template<template<typename...> class VectorType, typename T, typename Enable = void>
class TestBackConst;

template<template<typename...> class VectorType, typename T, typename Enable = void>
class TestData;

template<template<typename...> class VectorType, typename T, typename Enable = void>
class TestDataConst;

template<template<typename...> class VectorType, typename T, typename Enable = void>
class TestFlip;

template<template<typename...> class VectorType, typename T, typename Enable = void>
class TestSwapElements;


/// Test VectorType C++-11 standard vector interface.
template< template<typename...> class VectorType, typename T>
class VectorTestSuite : public TestSuite
{
public:
	typedef std::initializer_list<T> InitializerListType;
	typedef std::array<T, 1> ArrayType;

	VectorTestSuite() : TestSuite({

			TestCase("typedefs", [this]
					 {
						 TestCase::assert(std::is_same<typename VectorType<T>::value_type, T>::value, "value_type");
						 TestCase::assert(std::is_class<typename VectorType<T>::allocator_type>::value, "allocator_type");
						 if (!std::is_same<bool, T>::value) {
							 TestCase::assert(std::is_same<typename VectorType<T>::reference, T&>::value, "reference");
							 TestCase::assert(std::is_same<typename VectorType<T>::const_reference, const T&>::value, "const_reference");
						 } else {
							 TestCase::assert(std::is_class<typename VectorType<T>::reference>::value, "reference");
							 TestCase::assert(std::is_same<typename VectorType<T>::const_reference, T>::value, "const_reference");
						 }
					 }),

			TestCase("ctor default", [this]
					 {
						 VectorType<T> testee;
						 TestCase::assert(testee.size() == 0);
					 }),

			TestCase("ctor fill", [this]
					 {
						 VectorType<T> testee(3);
						 TestCase::assert(testee.size() == 3);
					 }),

			TestCase("ctor fill value", [this]
					 {
						 VectorType<T> testee(3, T());
						 TestCase::assert(testee.size() == 3);
					 }),

			TestCase("ctor copy", [this]
					 {
						 const VectorType<T> other(3);
						 VectorType<T> testee(other);
						 TestCase::assert(testee.size() == 3);
					 }),

			TestCase("ctor copy with allocator", [this]
					 {
						 const VectorType<T> other(3);
						 VectorType<T> testee(other, std::allocator<T>());
						 TestCase::assert(testee.size() == 3);
					 }),

			TestCase("ctor move", [this]
					 {
						 VectorType<T> other(3);
						 VectorType<T> testee(std::move(other));
						 TestCase::assert(other.size() == 0, "other");
						 TestCase::assert(testee.size() == 3, "testee");
					 }),

			TestCase("ctor move with allocator", [this]
					 {
						 VectorType<T> other(3);
						 VectorType<T> testee(std::move(other), std::allocator<T>());
						 TestCase::assert(other.size() == 0, "other");
						 TestCase::assert(testee.size() == 3, "testee");
					 }),

			TestCase("ctor range", [this]
					 {
						 VectorType<T> testee(ARRAY.begin(), ARRAY.end());
						 TestCase::assert(testee.size() == ARRAY.size());
					 }),

			TestCase("ctor initializer list", [this]
					 {
						 VectorType<T> testee(INITIALIZER_LIST);
						 TestCase::assert(testee.size() == INITIALIZER_LIST.size());
					 }),

			TestCase("operator= copy", [this]
					 {
						 const VectorType<T> other(3);
						 VectorType<T> testee;
						 auto& result = (testee = other);
						 TestCase::assert(std::is_same<VectorType<T>&, decltype(result)>::value, "type");
						 TestCase::assert(testee.size() == 3, "result");
					 }),

			TestCase("operator= move", [this]
					 {
						 VectorType<T> other(3);
						 VectorType<T> testee;
						 auto& result = (testee = std::move(other));
						 TestCase::assert(std::is_same<VectorType<T>&, decltype(result)>::value, "type");
						 TestCase::assert(other.size() == 0, "other");
						 TestCase::assert(testee.size() == 3, "testee");
					 }),

			TestCase("operator= initializer list", [this]
					 {
						 VectorType<T> testee;
						 auto& result = (testee = INITIALIZER_LIST);
						 TestCase::assert(std::is_same<VectorType<T>&, decltype(result)>::value, "type");
						 TestCase::assert(testee.size() == INITIALIZER_LIST.size(), "result");
					 }),

			TestCase("begin", [this]
					 {
						 VectorType<T> testee(1);
						 auto result = testee.begin();
						 TestCase::assert(std::is_same<typename VectorType<T>::iterator, decltype(result)>::value, "type");
						 TestCase::assert(*result == T(), "result");
					 }),

			TestCase("begin const", [this]
					 {
						 const VectorType<T> testee(1);
						 auto result = testee.begin();
						 TestCase::assert(std::is_same<typename VectorType<T>::const_iterator, decltype(result)>::value, "type");
						 TestCase::assert(*result == T(), "result");
					 }),

			TestCase("end", [this]
					 {
						 VectorType<T> testee(1);
						 auto result = testee.end();
						 TestCase::assert(std::is_same<typename VectorType<T>::iterator, decltype(result)>::value, "type");
						 TestCase::assert(*(--result) == T(), "result");
					 }),

			TestCase("end const", [this]
					 {
						 const VectorType<T> testee(1);
						 auto result = testee.end();
						 TestCase::assert(std::is_same<typename VectorType<T>::const_iterator, decltype(result)>::value, "type");
						 TestCase::assert(*(--result) == T(), "result");
					 }),

			TestCase("rbegin", [this]
					 {
						 VectorType<T> testee(1);
						 auto result = testee.rbegin();
						 TestCase::assert(std::is_same<typename VectorType<T>::reverse_iterator, decltype(result)>::value, "type");
						 TestCase::assert(*result == T(), "result");
					 }),

			TestCase("rbegin const", [this]
					 {
						 const VectorType<T> testee(1);
						 auto result = testee.rbegin();
						 TestCase::assert(std::is_same<typename VectorType<T>::const_reverse_iterator, decltype(result)>::value, "type");
						 TestCase::assert(*result == T(), "result");
					 }),

			TestCase("rend", [this]
					 {
						 VectorType<T> testee(1);
						 auto result = testee.rend();
						 TestCase::assert(std::is_same<typename VectorType<T>::reverse_iterator, decltype(result)>::value, "type");
						 TestCase::assert(*(--result) == T(), "result");
					 }),

			TestCase("rend const", [this]
					 {
						 const VectorType<T> testee(1);
						 auto result = testee.rend();
						 TestCase::assert(std::is_same<typename VectorType<T>::const_reverse_iterator, decltype(result)>::value, "type");
						 TestCase::assert(*(--result) == T(), "result");
					 }),

			TestCase("cbegin", [this]
					 {
						 VectorType<T> testee(1);
						 auto result = testee.cbegin();
						 TestCase::assert(std::is_same<typename VectorType<T>::const_iterator, decltype(result)>::value, "type");
						 TestCase::assert(*result == T(), "result");
					 }),

			TestCase("cend", [this]
					 {
						 VectorType<T> testee(1);
						 auto result = testee.cend();
						 TestCase::assert(std::is_same<typename VectorType<T>::const_iterator, decltype(result)>::value, "type");
						 TestCase::assert(*(--result) == T(), "result");
					 }),

			TestCase("crbegin", [this]
					 {
						 VectorType<T> testee(1);
						 auto result = testee.crbegin();
						 TestCase::assert(std::is_same<typename VectorType<T>::const_reverse_iterator, decltype(result)>::value, "type");
						 TestCase::assert(*result == T(), "result");
					 }),

			TestCase("crend", [this]
					 {
						 VectorType<T> testee(1);
						 auto result = testee.crend();
						 TestCase::assert(std::is_same<typename VectorType<T>::const_reverse_iterator, decltype(result)>::value, "type");
						 TestCase::assert(*(--result) == T(), "result");
					 }),

			TestCase("empty", [this]
					 {
						 const VectorType<T> testee;
						 auto result = testee.empty();
						 TestCase::assert(std::is_same<bool, decltype(result)>::value, "bool");
						 TestCase::assert(result == true, "result");
					 }),

			TestCase("size", [this]
					 {
						 const VectorType<T> testee(3);
						 auto result = testee.size();
						 TestCase::assert(std::is_same<typename VectorType<T>::size_type, decltype(result)>::value, "type");
						 TestCase::assert(result == 3, "result");
					 }),

			TestCase("max_size", [this]
					 {
						 const VectorType<T> testee(3);
						 auto result = testee.max_size();
						 TestCase::assert(std::is_same<typename VectorType<T>::size_type, decltype(result)>::value, "type");
						 TestCase::assert(result >= 3, "result");
					 }),

			TestCase("resize", [this]
					 {
						 VectorType<T> testee(1);
						 testee.resize(3);
						 TestCase::assert(testee.size() == 3);
					 }),

			TestCase("resize value", [this]
					 {
						 VectorType<T> testee(1);
						 testee.resize(3, T());
						 TestCase::assert(testee.size() == 3);
					 }),

			TestCase("capacity", [this]
					 {
						 const VectorType<T> testee(3);
						 auto result = testee.capacity();
						 TestCase::assert(std::is_same<typename VectorType<T>::size_type, decltype(result)>::value, "type");
						 TestCase::assert(result >= 3, "result");
					 }),

			TestCase("reserve", [this]
					 {
						 VectorType<T> testee(1);
						 testee.reserve(3);
						 TestCase::assert(testee.capacity() >= 3);
					 }),

			TestCase("shrink_to_fit", [this]
					 {
						 VectorType<T> testee(1);
						 testee.reserve(3);
						 testee.shrink_to_fit();
						 if (!std::is_same<bool, T>::value) {
							 TestCase::assert(testee.capacity() == testee.size());
						 }
					 }),

			TestCase("operator[]", TestSubscriptOperator<VectorType, T>()),

			TestCase("operator[]", TestSubscriptOperatorConst<VectorType, T>()),

			TestCase("at", TestAt<VectorType, T>()),

			TestCase("at const", TestAtConst<VectorType, T>()),

			TestCase("front", TestFront<VectorType, T>()),

			TestCase("front const", TestFrontConst<VectorType, T>()),

			TestCase("back", TestBack<VectorType, T>()),

			TestCase("back const", TestBackConst<VectorType, T>()),

			TestCase("data", TestData<VectorType, T>()),

			TestCase("data const", TestDataConst<VectorType, T>()),

			TestCase("assign range", [this]
					 {
						 VectorType<T> testee;
						 testee.assign(ARRAY.begin(), ARRAY.end());
						 TestCase::assert(testee.size() == ARRAY.size());
					 }),

			TestCase("assign fill value", [this]
					 {
						 VectorType<T> testee;
						 testee.assign(3, T());
						 TestCase::assert(testee.size() == 3);
					 }),

			TestCase("assign initializer list", [this]
					 {
						 VectorType<T> testee;
						 testee.assign(INITIALIZER_LIST);
						 TestCase::assert(testee.size() == INITIALIZER_LIST.size());
					 }),

			TestCase("push_back copy", [this]
					 {
						 VectorType<T> testee;
						 T value;
						 testee.push_back(value);
						 TestCase::assert(testee.size() == 1);
					 }),

			TestCase("push_back move", [this]
					 {
						 VectorType<T> testee;
						 T value;
						 testee.push_back(std::move(value));
						 TestCase::assert(testee.size() == 1);
					 }),

			TestCase("pop_back", [this]
					 {
						 VectorType<T> testee(2);
						 testee.pop_back();
						 TestCase::assert(testee.size() == 1);
					 }),

			TestCase("insert single element", [this]
					 {
						 VectorType<T> testee(1);
						 auto position = testee.begin();
						 T value;
						 auto result = testee.insert(position, value);
						 TestCase::assert(std::is_same<typename VectorType<T>::iterator, decltype(result)>::value, "type");
						 TestCase::assert(testee.size() == 2, "result");
					 }),

			TestCase("insert fill", [this]
					 {
						 VectorType<T> testee(1);
						 auto position = testee.begin();
						 T value;
						 auto result = testee.insert(position, 2, value);
						 TestCase::assert(std::is_same<typename VectorType<T>::iterator, decltype(result)>::value, "type");
						 TestCase::assert(testee.size() == 3, "result");
					 }),

			TestCase("insert range", [this]
					 {
						 VectorType<T> testee(1);
						 auto position = testee.begin();
						 auto result = testee.insert(position, ARRAY.begin(), ARRAY.end());
						 TestCase::assert(std::is_same<typename VectorType<T>::iterator, decltype(result)>::value, "type");
						 TestCase::assert(testee.size() == 1 + ARRAY.size(), "result");
					 }),

			TestCase("insert move", [this]
					 {
						 VectorType<T> testee(1);
						 auto position = testee.begin();
						 T value;
						 auto result = testee.insert(position, std::move(value));
						 TestCase::assert(std::is_same<typename VectorType<T>::iterator, decltype(result)>::value, "type");
						 TestCase::assert(testee.size() == 2, "result");
					 }),

			TestCase("insert initializer list", [this]
					 {
						 VectorType<T> testee(1);
						 auto position = testee.begin();
						 auto result = testee.insert(position, INITIALIZER_LIST);
						 TestCase::assert(std::is_same<typename VectorType<T>::iterator, decltype(result)>::value, "type");
						 TestCase::assert(testee.size() == 1 + INITIALIZER_LIST.size(), "result");
					 }),

			TestCase("erase single element", [this]
					 {
						 VectorType<T> testee(3);
						 auto position = testee.begin();
						 auto result = testee.erase(position);
						 TestCase::assert(std::is_same<typename VectorType<T>::iterator, decltype(result)>::value, "type");
						 TestCase::assert(testee.size() == 2, "result");
					 }),

			TestCase("erase range", [this]
					 {
						 VectorType<T> testee(3);
						 auto first = testee.begin();
						 auto last = first + 2;
						 auto result = testee.erase(first, last);
						 TestCase::assert(std::is_same<typename VectorType<T>::iterator, decltype(result)>::value, "type");
						 TestCase::assert(testee.size() == 1, "result");
					 }),

			TestCase("flip", TestFlip<VectorType, T>()),

			TestCase("swap", [this]
					 {
						 VectorType<T> other(3);
						 VectorType<T> testee(1);
						 testee.swap(other);
						 TestCase::assert(other.size() == 1, "other");
						 TestCase::assert(testee.size() == 3, "testee");
					 }),

			TestCase("swap elements", TestSwapElements<VectorType, T>()),

			TestCase("clear", [this]
					 {
						 VectorType<T> testee(1);
						 testee.clear();
						 TestCase::assert(testee.size() == 0);
					 }),

			TestCase("emplace", [this]
					 {
						 VectorType<T> testee(1);
						 auto position = testee.begin();
						 auto result = testee.emplace(position);
						 TestCase::assert(std::is_same<typename VectorType<T>::iterator, decltype(result)>::value, "type");
						 TestCase::assert(testee.size() == 2, "result");
					 }),

			TestCase("emplace_back", [this]
					 {
						 VectorType<T> testee(1);
						 testee.emplace_back();
						 TestCase::assert(testee.size() == 2);
					 }),

			TestCase("get_allocator", [this]
					 {
						 VectorType<T> testee;
						 auto result = testee.get_allocator();
						 TestCase::assert(std::is_same<typename VectorType<T>::allocator_type, decltype(result)>::value);
					 }),

			TestCase("operator==", [this]
					 {
						 VectorType<T> lhs(3);
						 VectorType<T> rhs(3);
						 auto result = (lhs == rhs);
						 TestCase::assert(std::is_same<bool, decltype(result)>::value, "type");
						 TestCase::assert(result == true, "result");
					 }),

			TestCase("operator!=", [this]
					 {
						 VectorType<T> lhs(2);
						 VectorType<T> rhs(3);
						 auto result = (lhs != rhs);
						 TestCase::assert(std::is_same<bool, decltype(result)>::value, "type");
						 TestCase::assert(result == true, "result");
					 }),

			TestCase("operator<", [this]
					 {
						 VectorType<T> lhs(2);
						 VectorType<T> rhs(3);
						 auto result = (lhs < rhs);
						 TestCase::assert(std::is_same<bool, decltype(result)>::value, "type");
						 TestCase::assert(result == true, "result");
					 }),

			TestCase("operator<=", [this]
					 {
						 VectorType<T> lhs(2);
						 VectorType<T> rhs(3);
						 auto result = (lhs <= rhs);
						 TestCase::assert(std::is_same<bool, decltype(result)>::value, "type");
						 TestCase::assert(result == true, "result");
					 }),

			TestCase("operator>", [this]
					 {
						 VectorType<T> lhs(3);
						 VectorType<T> rhs(2);
						 auto result = (lhs > rhs);
						 TestCase::assert(std::is_same<bool, decltype(result)>::value, "type");
						 TestCase::assert(result == true, "result");
					 }),

			TestCase("operator>=", [this]
					 {
						 VectorType<T> lhs(3);
						 VectorType<T> rhs(2);
						 auto result = (lhs >= rhs);
						 TestCase::assert(std::is_same<bool, decltype(result)>::value, "type");
						 TestCase::assert(result == true, "result");
					 }),

			TestCase("swap lhs rhs", [this]
					 {
						 VectorType<T> lhs(3);
						 VectorType<T> rhs(2);
						 swap(lhs, rhs);
						 TestCase::assert(lhs.size() == 2, "lhs");
						 TestCase::assert(rhs.size() == 3, "rhs");
					 })
		})
	{
	}

	static constexpr InitializerListType INITIALIZER_LIST = {T()};
	static constexpr ArrayType ARRAY = {T()};
};

template<template<typename...> class ListType, typename T>
constexpr typename VectorTestSuite<ListType, T>::InitializerListType VectorTestSuite<ListType, T>::INITIALIZER_LIST;

template<template<typename...> class ListType, typename T>
constexpr typename VectorTestSuite<ListType, T>::ArrayType VectorTestSuite<ListType, T>::ARRAY;


// Conditionally enabled test executors handling the std::vector<bool> specialization.

template<template<typename...> class VectorType, typename T>
class TestSubscriptOperator<VectorType, T, typename std::enable_if<!std::is_same<bool, T>::value>::type>
{
public:
	void operator()()
	{
		VectorType<T> testee(1);
		auto& result = testee[0];
		TestCase::assert(std::is_same<typename VectorType<T>::reference, decltype(result)>::value, "type");
		TestCase::assert(result == T(), "result");
	}
};

template<template<typename...> class VectorType, typename T>
class TestSubscriptOperator<VectorType, T, typename std::enable_if<std::is_same<bool, T>::value>::type>
{
public:
	void operator()()
	{
		VectorType<T> testee(1);
		auto result = testee[0];
		TestCase::assert(std::is_same<typename VectorType<T>::reference, decltype(result)>::value, "type");
		TestCase::assert(result == T(), "result");
	}
};

template<template<typename...> class VectorType, typename T>
class TestSubscriptOperatorConst<VectorType, T, typename std::enable_if<!std::is_same<bool, T>::value>::type>
{
public:
	void operator()()
	{
		const VectorType<T> testee(1);
		auto& result = testee[0];
		TestCase::assert(std::is_same<typename VectorType<T>::const_reference, decltype(result)>::value, "type");
		TestCase::assert(result == T(), "result");
	}
};

template<template<typename...> class VectorType, typename T>
class TestSubscriptOperatorConst<VectorType, T, typename std::enable_if<std::is_same<bool, T>::value>::type>
{
public:
	void operator()()
	{
		const VectorType<T> testee(1);
		auto result = testee[0];
		TestCase::assert(std::is_same<typename VectorType<T>::const_reference, decltype(result)>::value, "type");
		TestCase::assert(result == T(), "result");
	}
};

template<template<typename...> class VectorType, typename T>
class TestAt<VectorType, T, typename std::enable_if<!std::is_same<bool, T>::value>::type>
{
public:
	void operator()()
	{
		VectorType<T> testee(1);
		auto& result = testee.at(0);
		TestCase::assert(std::is_same<typename VectorType<T>::reference, decltype(result)>::value, "type");
		TestCase::assert(result == T(), "result");
	}
};

template<template<typename...> class VectorType, typename T>
class TestAt<VectorType, T, typename std::enable_if<std::is_same<bool, T>::value>::type>
{
public:
	void operator()()
	{
		VectorType<T> testee(1);
		auto result = testee.at(0);
		TestCase::assert(std::is_same<typename VectorType<T>::reference, decltype(result)>::value, "type");
		TestCase::assert(result == T(), "result");
	}
};

template<template<typename...> class VectorType, typename T>
class TestAtConst<VectorType, T, typename std::enable_if<!std::is_same<bool, T>::value>::type>
{
public:
	void operator()()
	{
		const VectorType<T> testee(1);
		auto& result = testee.at(0);
		TestCase::assert(std::is_same<typename VectorType<T>::const_reference, decltype(result)>::value, "type");
		TestCase::assert(result == T(), "result");
	}
};

template<template<typename...> class VectorType, typename T>
class TestAtConst<VectorType, T, typename std::enable_if<std::is_same<bool, T>::value>::type>
{
public:
	void operator()()
	{
		const VectorType<T> testee(1);
		auto result = testee.at(0);
		TestCase::assert(std::is_same<typename VectorType<T>::const_reference, decltype(result)>::value, "type");
		TestCase::assert(result == T(), "result");
	}
};

template<template<typename...> class VectorType, typename T>
class TestFront<VectorType, T, typename std::enable_if<!std::is_same<bool, T>::value>::type>
{
public:
	void operator()()
	{
		VectorType<T> testee(1);
		auto& result = testee.front();
		TestCase::assert(std::is_same<typename VectorType<T>::reference, decltype(result)>::value, "type");
		TestCase::assert(result == T(), "result");
	}
};

template<template<typename...> class VectorType, typename T>
class TestFront<VectorType, T, typename std::enable_if<std::is_same<bool, T>::value>::type>
{
public:
	void operator()()
	{
		VectorType<T> testee(1);
		auto result = testee.front();
		TestCase::assert(std::is_same<typename VectorType<T>::reference, decltype(result)>::value, "type");
		TestCase::assert(result == T(), "result");
	}
};

template<template<typename...> class VectorType, typename T>
class TestFrontConst<VectorType, T, typename std::enable_if<!std::is_same<bool, T>::value>::type>
{
public:
	void operator()()
	{
		const VectorType<T> testee(1);
		auto& result = testee.front();
		TestCase::assert(std::is_same<typename VectorType<T>::const_reference, decltype(result)>::value, "type");
		TestCase::assert(result == T(), "result");
	}
};

template<template<typename...> class VectorType, typename T>
class TestFrontConst<VectorType, T, typename std::enable_if<std::is_same<bool, T>::value>::type>
{
public:
	void operator()()
	{
		const VectorType<T> testee(1);
		auto result = testee.front();
		TestCase::assert(std::is_same<typename VectorType<T>::const_reference, decltype(result)>::value, "type");
		TestCase::assert(result == T(), "result");
	}
};

template<template<typename...> class VectorType, typename T>
class TestBack<VectorType, T, typename std::enable_if<!std::is_same<bool, T>::value>::type>
{
public:
	void operator()()
	{
		VectorType<T> testee(1);
		auto& result = testee.back();
		TestCase::assert(std::is_same<typename VectorType<T>::reference, decltype(result)>::value, "type");
		TestCase::assert(result == T(), "result");
	}
};

template<template<typename...> class VectorType, typename T>
class TestBack<VectorType, T, typename std::enable_if<std::is_same<bool, T>::value>::type>
{
public:
	void operator()()
	{
		VectorType<T> testee(1);
		auto result = testee.back();
		TestCase::assert(std::is_same<typename VectorType<T>::reference, decltype(result)>::value, "type");
		TestCase::assert(result == T(), "result");
	}
};

template<template<typename...> class VectorType, typename T>
class TestBackConst<VectorType, T, typename std::enable_if<!std::is_same<bool, T>::value>::type>
{
public:
	void operator()()
	{
		const VectorType<T> testee(1);
		auto& result = testee.back();
		TestCase::assert(std::is_same<typename VectorType<T>::const_reference, decltype(result)>::value, "type");
		TestCase::assert(result == T(), "result");
	}
};

template<template<typename...> class VectorType, typename T>
class TestBackConst<VectorType, T, typename std::enable_if<std::is_same<bool, T>::value>::type>
{
public:
	void operator()()
	{
		const VectorType<T> testee(1);
		auto result = testee.back();
		TestCase::assert(std::is_same<typename VectorType<T>::const_reference, decltype(result)>::value, "type");
		TestCase::assert(result == T(), "result");
	}
};

template<template<typename...> class VectorType, typename T>
class TestData<VectorType, T, typename std::enable_if<!std::is_same<bool, T>::value>::type>
{
public:
	void operator()()
	{
		VectorType<T> testee(1);
		auto result = testee.data();
		TestCase::assert(std::is_same<typename VectorType<T>::pointer, decltype(result)>::value, "pointer");
		TestCase::assert(*result == T(), "result");
	}
};

template<template<typename...> class VectorType, typename T>
class TestData<VectorType, T, typename std::enable_if<std::is_same<bool, T>::value>::type>
{
public:
	void operator()()
	{
	}
};

template<template<typename...> class VectorType, typename T>
class TestDataConst<VectorType, T, typename std::enable_if<!std::is_same<bool, T>::value>::type>
{
public:
	void operator()()
	{
		const VectorType<T> testee(1);
		auto result = testee.data();
		TestCase::assert(std::is_same<typename VectorType<T>::const_pointer, decltype(result)>::value, "const_pointer");
		TestCase::assert(*result == T(), "result");
	}
};

template<template<typename...> class VectorType, typename T>
class TestDataConst<VectorType, T, typename std::enable_if<std::is_same<bool, T>::value>::type>
{
public:
	void operator()()
	{
	}
};




template<template<typename...> class VectorType, typename T>
class TestFlip<VectorType, T, typename std::enable_if<!std::is_same<bool, T>::value>::type>
{
public:
	void operator()()
	{
	}
};

template<template<typename...> class VectorType, typename T>
class TestFlip<VectorType, T, typename std::enable_if<std::is_same<bool, T>::value>::type>
{
public:
	void operator()()
	{
		VectorType<bool> testee({true, false});
		testee.flip();
		TestCase::assert(testee.front() == false && testee.back() == true);
	}
};

template<template<typename...> class VectorType, typename T>
class TestSwapElements<VectorType, T, typename std::enable_if<!std::is_same<bool, T>::value>::type>
{
public:
	void operator()()
	{
	}
};

template<template<typename...> class VectorType, typename T>
class TestSwapElements<VectorType, T, typename std::enable_if<std::is_same<bool, T>::value>::type>
{
public:
	void operator()()
	{
		VectorType<bool> testee({true, false});
		VectorType<T>::swap(testee.front(), testee.back());
		TestCase::assert(testee.front() == false && testee.back() == true);
	}
};

} // namespace Testee

#endif // Testee_VectorTestSuite_INCLUDED
