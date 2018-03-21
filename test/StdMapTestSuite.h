//
// Copyright (C) 2018 Dr. Michael Steffens
//
// SPDX-License-Identifier:		BSL-1.0
//


#ifndef StdMapTestSuite_INCLUDED
#define StdMapTestSuite_INCLUDED

#include "TestSuite.h"

// Conditionally enabled test executors handling map vs multimap.

template<template<typename...> class MapType, typename Key, typename T, bool isMultimap, typename Enable = void>
class TestSubscriptOperator;

template<template<typename...> class MapType, typename Key, typename T, bool isMultimap, typename Enable = void>
class TestSubscriptOperatorMove;

template<template<typename...> class MapType, typename Key, typename T, bool isMultimap, typename Enable = void>
class TestAt;

template<template<typename...> class MapType, typename Key, typename T, bool isMultimap, typename Enable = void>
class TestAtConst;


/// Test MapType C++-11 standard map or multimap interface.
template<template<typename...> class MapType, typename Key, typename T, bool isMultimap = false>
class StdMapTestSuite : public TestSuite
{
public:
	typedef std::initializer_list< std::pair<const Key, T> > InitializerListType;
	typedef std::array<std::pair<const Key, T>, 1> ArrayType;

	StdMapTestSuite() : TestSuite({

			TestCase("typedefs", [this]
					 {
						 TestCase::assert(std::is_same<typename MapType<Key, T>::key_type, Key>::value, "key_type");
						 TestCase::assert(std::is_same<typename MapType<Key, T>::mapped_type, T>::value, "mapped_type");
						 TestCase::assert(std::is_same<typename MapType<Key, T>::value_type, std::pair<const Key, T> >::value, "value_type");
						 TestCase::assert(std::is_class<typename MapType<Key, T>::allocator_type>::value, "allocator_type");
						 TestCase::assert(std::is_same<typename MapType<Key, T>::reference, std::pair<const Key, T>&>::value, "reference");
						 TestCase::assert(std::is_same<typename MapType<Key, T>::const_reference, const std::pair<const Key, T>&>::value, "const_reference");
					 }),

			TestCase("ctor default", [this]
					 {
						 MapType<Key, T> testee;
						 TestCase::assert(testee.size() == 0);
					 }),

			// TestCase("ctor default with allocator", [this]
			//		 {
			//			 MapType<Key, T> testee(std::allocator<T>());
			//			 TestCase::assert(testee.size() == 0);
			//		 }),

			TestCase("ctor copy", [this]
					 {
						 const MapType<Key, T> other(INITIALIZER_LIST);
						 MapType<Key, T> testee(other);
						 TestCase::assert(testee.size() == INITIALIZER_LIST.size());
					 }),

			// TestCase("ctor copy with allocator", [this]
			//		 {
			//			 const MapType<Key, T> other(INITIALIZER_LIST);
			//			 MapType<Key, T> testee(other, std::allocator<T>());
			//			 TestCase::assert(testee.size() == INITIALIZER_LIST.size());
			//		 }),

			TestCase("ctor move", [this]
					 {
						 MapType<Key, T> other(INITIALIZER_LIST);
						 MapType<Key, T> testee(std::move(other));
						 TestCase::assert(other.size() == 0, "other");
						 TestCase::assert(testee.size() == INITIALIZER_LIST.size(), "testee");
					 }),

			// TestCase("ctor move with allocator", [this]
			//		 {
			//			 MapType<Key, T> other(INITIALIZER_LIST);
			//			 MapType<Key, T> testee(std::move(other), std::allocator<T>());
			//			 TestCase::assert(other.size() == 0, "other");
			//			 TestCase::assert(testee.size() == INITIALIZER_LIST.size(), "testee");
			//		 }),

			TestCase("ctor range", [this]
					 {
						 MapType<Key, T> testee(ARRAY.begin(), ARRAY.end());
						 TestCase::assert(testee.size() == ARRAY.size());
					 }),

			TestCase("ctor initializer list", [this]
					 {
						 MapType<Key, T> testee(INITIALIZER_LIST);
						 TestCase::assert(testee.size() == INITIALIZER_LIST.size());
					 }),

			TestCase("operator= copy", [this]
					 {
						 const MapType<Key, T> other(INITIALIZER_LIST);
						 MapType<Key, T> testee;
						 auto& result = (testee = other);
						 TestCase::assert(std::is_same<MapType<Key, T>&, decltype(result)>::value, "type");
						 TestCase::assert(testee.size() == INITIALIZER_LIST.size(), "result");
					 }),

			TestCase("operator= move", [this]
					 {
						 MapType<Key, T> other(INITIALIZER_LIST);
						 MapType<Key, T> testee;
						 auto& result = (testee = std::move(other));
						 TestCase::assert(std::is_same<MapType<Key, T>&, decltype(result)>::value, "type");
						 TestCase::assert(other.size() == 0, "other");
						 TestCase::assert(testee.size() == INITIALIZER_LIST.size(), "testee");
					 }),

			TestCase("operator= initializer list", [this]
					 {
						 MapType<Key, T> testee;
						 auto& result = (testee = INITIALIZER_LIST);
						 TestCase::assert(std::is_same<MapType<Key, T>&, decltype(result)>::value, "type");
						 TestCase::assert(testee.size() == INITIALIZER_LIST.size(), "result");
					 }),

			TestCase("begin", [this]
					 {
						 MapType<Key, T> testee(INITIALIZER_LIST);
						 auto i = testee.begin();
						 TestCase::assert(std::is_same<typename MapType<Key, T>::iterator, decltype(i)>::value, "type");
						 TestCase::assert(*i == typename MapType<Key, T>::value_type(), "result");
					 }),

			TestCase("begin const", [this]
					 {
						 const MapType<Key, T> testee(INITIALIZER_LIST);
						 auto i = testee.begin();
						 TestCase::assert(std::is_same<typename MapType<Key, T>::const_iterator, decltype(i)>::value, "type");
						 TestCase::assert(*i == typename MapType<Key, T>::value_type(), "result");
					 }),

			TestCase("end", [this]
					 {
						 MapType<Key, T> testee(INITIALIZER_LIST);
						 auto i = testee.end();
						 TestCase::assert(std::is_same<typename MapType<Key, T>::iterator, decltype(i)>::value, "type");
						 TestCase::assert(*(--i) == typename MapType<Key, T>::value_type(), "result");
					 }),

			TestCase("end const", [this]
					 {
						 const MapType<Key, T> testee(INITIALIZER_LIST);
						 auto i = testee.end();
						 TestCase::assert(std::is_same<typename MapType<Key, T>::const_iterator, decltype(i)>::value, "type");
						 TestCase::assert(*(--i) == typename MapType<Key, T>::value_type(), "result");
					 }),

			TestCase("rbegin", [this]
					 {
						 MapType<Key, T> testee(INITIALIZER_LIST);
						 auto i = testee.rbegin();
						 TestCase::assert(std::is_same<typename MapType<Key, T>::reverse_iterator, decltype(i)>::value, "type");
						 TestCase::assert(*i == typename MapType<Key, T>::value_type(), "result");
					 }),

			TestCase("rbegin const", [this]
					 {
						 const MapType<Key, T> testee(INITIALIZER_LIST);
						 auto i = testee.rbegin();
						 TestCase::assert(std::is_same<typename MapType<Key, T>::const_reverse_iterator, decltype(i)>::value, "type");
						 TestCase::assert(*i == typename MapType<Key, T>::value_type(), "result");
					 }),

			TestCase("rend", [this]
					 {
						 MapType<Key, T> testee(INITIALIZER_LIST);
						 auto i = testee.rend();
						 TestCase::assert(std::is_same<typename MapType<Key, T>::reverse_iterator, decltype(i)>::value, "type");
						 TestCase::assert(*(--i) == typename MapType<Key, T>::value_type(), "result");
					 }),

			TestCase("rend const", [this]
					 {
						 const MapType<Key, T> testee(INITIALIZER_LIST);
						 auto i = testee.rend();
						 TestCase::assert(std::is_same<typename MapType<Key, T>::const_reverse_iterator, decltype(i)>::value, "type");
						 TestCase::assert(*(--i) == typename MapType<Key, T>::value_type(), "result");
					 }),

			TestCase("cbegin", [this]
					 {
						 MapType<Key, T> testee(INITIALIZER_LIST);
						 auto i = testee.cbegin();
						 TestCase::assert(std::is_same<typename MapType<Key, T>::const_iterator, decltype(i)>::value, "type");
						 TestCase::assert(*i == typename MapType<Key, T>::value_type(), "result");
					 }),

			TestCase("cend", [this]
					 {
						 MapType<Key, T> testee(INITIALIZER_LIST);
						 auto i = testee.cend();
						 TestCase::assert(std::is_same<typename MapType<Key, T>::const_iterator, decltype(i)>::value, "type");
						 TestCase::assert(*(--i) == typename MapType<Key, T>::value_type(), "result");
					 }),

			TestCase("crbegin", [this]
					 {
						 MapType<Key, T> testee(INITIALIZER_LIST);
						 auto i = testee.crbegin();
						 TestCase::assert(std::is_same<typename MapType<Key, T>::const_reverse_iterator, decltype(i)>::value, "type");
						 TestCase::assert(*i == typename MapType<Key, T>::value_type(), "result");
					 }),

			TestCase("crend", [this]
					 {
						 MapType<Key, T> testee(INITIALIZER_LIST);
						 auto i = testee.crend();
						 TestCase::assert(std::is_same<typename MapType<Key, T>::const_reverse_iterator, decltype(i)>::value, "type");
						 TestCase::assert(*(--i) == typename MapType<Key, T>::value_type(), "result");
					 }),

			TestCase("empty", [this]
					 {
						 const MapType<Key, T> testee;
						 auto result = testee.empty();
						 TestCase::assert(std::is_same<bool, decltype(result)>::value, "bool");
						 TestCase::assert(result == true, "result");
					 }),

			TestCase("size", [this]
					 {
						 const MapType<Key, T> testee(INITIALIZER_LIST);
						 auto result = testee.size();
						 TestCase::assert(std::is_same<typename MapType<Key, T>::size_type, decltype(result)>::value, "type");
						 TestCase::assert(result == INITIALIZER_LIST.size(), "result");
					 }),

			TestCase("max_size", [this]
					 {
						 const MapType<Key, T> testee(INITIALIZER_LIST);
						 auto result = testee.max_size();
						 TestCase::assert(std::is_same<typename MapType<Key, T>::size_type, decltype(result)>::value, "type");
						 TestCase::assert(result >= INITIALIZER_LIST.size(), "result");
					 }),


			TestCase("operator[]", TestSubscriptOperator<MapType, Key, T, isMultimap>()),

			TestCase("operator[] move", TestSubscriptOperatorMove<MapType, Key, T, isMultimap>()),

			TestCase("at", TestAt<MapType, Key, T, isMultimap>()),

			TestCase("at const", TestAtConst<MapType, Key, T, isMultimap>()),

			TestCase("insert single element", [this]
					 {
						 MapType<Key, T> testee;
						 auto position = testee.begin();
						 auto value = std::make_pair(Key(), T());
						 auto result = testee.insert(value);
						 if (!isMultimap) {
							 TestCase::assert(std::is_same<std::pair<typename MapType<Key, T>::iterator, bool>, decltype(result)>::value, "type");
						 } else {
							 TestCase::assert(std::is_same<typename MapType<Key, T>::iterator, decltype(result)>::value, "type");
						 }
						 TestCase::assert(testee.size() == 1, "result");
					 }),

			TestCase("insert move", [this]
					 {
						 MapType<Key, T> testee;
						 auto position = testee.begin();
						 auto value = std::make_pair(Key(), T());
						 auto result = testee.insert(std::move(value));
						 if (!isMultimap) {
							 TestCase::assert(std::is_same<std::pair<typename MapType<Key, T>::iterator, bool>, decltype(result)>::value, "type");
						 } else {
							 TestCase::assert(std::is_same<typename MapType<Key, T>::iterator, decltype(result)>::value, "type");
						 }
						 TestCase::assert(testee.size() == 1, "result");
					 }),

			TestCase("insert hint single element", [this]
					 {
						 MapType<Key, T> testee;
						 auto position = testee.begin();
						 auto value = std::make_pair(Key(), T());
						 auto result = testee.insert(position, value);
						 TestCase::assert(std::is_same<typename MapType<Key, T>::iterator, decltype(result)>::value, "type");
						 TestCase::assert(testee.size() == 1, "result");
					 }),

			TestCase("insert hint move", [this]
					 {
						 MapType<Key, T> testee;
						 auto position = testee.begin();
						 auto value = std::make_pair(Key(), T());
						 auto result = testee.insert(position, std::move(value));
						 TestCase::assert(std::is_same<typename MapType<Key, T>::iterator, decltype(result)>::value, "type");
						 TestCase::assert(testee.size() == 1, "result");
					 }),

			TestCase("insert range", [this]
					 {
						 MapType<Key, T> testee;
						 testee.insert(ARRAY.begin(), ARRAY.end());
						 TestCase::assert(testee.size() == ARRAY.size());
					 }),

			TestCase("insert initializer list", [this]
					 {
						 MapType<Key, T> testee;
						 testee.insert(INITIALIZER_LIST);
						 TestCase::assert(testee.size() == INITIALIZER_LIST.size());
					 }),

			TestCase("erase single element", [this]
					 {
						 MapType<Key, T> testee(INITIALIZER_LIST);
						 auto position = testee.begin();
						 auto result = testee.erase(position);
						 TestCase::assert(std::is_same<typename MapType<Key, T>::iterator, decltype(result)>::value, "type");
						 TestCase::assert(testee.size() == 0, "result");
					 }),

			TestCase("erase key", [this]
					 {
						 MapType<Key, T> testee(INITIALIZER_LIST);
						 auto result = testee.erase(Key());
						 TestCase::assert(std::is_same<typename MapType<Key, T>::size_type, decltype(result)>::value, "type");
						 TestCase::assert(testee.size() == 0, "result");
					 }),

			TestCase("erase range", [this]
					 {
						 MapType<Key, T> testee(INITIALIZER_LIST);
						 auto first = testee.begin();
						 auto last = testee.end();;
						 auto result = testee.erase(first, last);
						 TestCase::assert(std::is_same<typename MapType<Key, T>::iterator, decltype(result)>::value, "type");
						 TestCase::assert(testee.size() == 0, "result");
					 }),

			TestCase("swap", [this]
					 {
						 MapType<Key, T> other(INITIALIZER_LIST);
						 MapType<Key, T> testee(INITIALIZER_LIST);
						 testee.swap(other);
						 TestCase::assert(other.size() == INITIALIZER_LIST.size(), "other");
						 TestCase::assert(testee.size() == INITIALIZER_LIST.size(), "testee");
					 }),

			TestCase("clear", [this]
					 {
						 MapType<Key, T> testee(INITIALIZER_LIST);
						 testee.clear();
						 TestCase::assert(testee.size() == 0);
					 }),

			TestCase("emplace", [this]
					 {
						 MapType<Key, T> testee;
						 auto result = testee.emplace();
						 if (!isMultimap) {
							 TestCase::assert(std::is_same<std::pair<typename MapType<Key, T>::iterator, bool>, decltype(result)>::value, "type");
						 } else {
							 TestCase::assert(std::is_same<typename MapType<Key, T>::iterator, decltype(result)>::value, "type");
						 }
						 TestCase::assert(testee.size() == 1, "result");
					 }),

			TestCase("emplace_hint", [this]
					 {
						 MapType<Key, T> testee;
						 auto position = testee.begin();
						 auto result = testee.emplace_hint(position);
						 TestCase::assert(std::is_same<typename MapType<Key, T>::iterator, decltype(result)>::value, "type");
						 TestCase::assert(testee.size() == 1, "result");
					 }),

			TestCase("key_comp", [this]
					 {
						 const MapType<Key, T> testee;
						 auto result = testee.key_comp();
						 TestCase::assert(std::is_same<typename MapType<Key, T>::key_compare, decltype(result)>::value);
					 }),

			TestCase("value_comp", [this]
					 {
						 const MapType<Key, T> testee;
						 auto result = testee.value_comp();
						 TestCase::assert(std::is_same<typename MapType<Key, T>::value_compare, decltype(result)>::value);
					 }),

			TestCase("find", [this]
					 {
						 MapType<Key, T> testee(INITIALIZER_LIST);
						 auto result = testee.find(Key());
						 TestCase::assert(std::is_same<typename MapType<Key, T>::iterator, decltype(result)>::value, "type");
						 TestCase::assert(*result == typename MapType<Key, T>::value_type(), "result");
					 }),

			TestCase("find const", [this]
					 {
						 const MapType<Key, T> testee(INITIALIZER_LIST);
						 auto result = testee.find(Key());
						 TestCase::assert(std::is_same<typename MapType<Key, T>::const_iterator, decltype(result)>::value, "type");
						 TestCase::assert(*result == typename MapType<Key, T>::value_type(), "result");
					 }),

			TestCase("count", [this]
					 {
						 const MapType<Key, T> testee(INITIALIZER_LIST);
						 auto result = testee.count(Key());
						 TestCase::assert(std::is_same<typename MapType<Key, T>::size_type, decltype(result)>::value, "type");
						 TestCase::assert(result == 1, "result");
					 }),

			TestCase("lower_bound", [this]
					 {
						 MapType<Key, T> testee(INITIALIZER_LIST);
						 auto result = testee.lower_bound(Key());
						 TestCase::assert(std::is_same<typename MapType<Key, T>::iterator, decltype(result)>::value, "type");
						 TestCase::assert(*result == typename MapType<Key, T>::value_type(), "result");
					 }),

			TestCase("lower_bound const", [this]
					 {
						 const MapType<Key, T> testee(INITIALIZER_LIST);
						 auto result = testee.lower_bound(Key());
						 TestCase::assert(std::is_same<typename MapType<Key, T>::const_iterator, decltype(result)>::value, "type");
						 TestCase::assert(*result == typename MapType<Key, T>::value_type(), "result");
					 }),

			TestCase("upper_bound", [this]
					 {
						 MapType<Key, T> testee(INITIALIZER_LIST);
						 auto result = testee.upper_bound(Key());
						 TestCase::assert(std::is_same<typename MapType<Key, T>::iterator, decltype(result)>::value, "type");
						 TestCase::assert(*(--result) == typename MapType<Key, T>::value_type(), "result");
					 }),

			TestCase("upper_bound const", [this]
					 {
						 const MapType<Key, T> testee(INITIALIZER_LIST);
						 auto result = testee.upper_bound(Key());
						 TestCase::assert(std::is_same<typename MapType<Key, T>::const_iterator, decltype(result)>::value, "type");
						 TestCase::assert(*(--result) == typename MapType<Key, T>::value_type(), "result");
					 }),

			TestCase("equal_range", [this]
					 {
						 MapType<Key, T> testee(INITIALIZER_LIST);
						 auto result = testee.equal_range(Key());
						 TestCase::assert(std::is_same<std::pair<typename MapType<Key, T>::iterator, typename MapType<Key, T>::iterator>, decltype(result)>::value);
					 }),

			TestCase("equal_range const", [this]
					 {
						 const MapType<Key, T> testee(INITIALIZER_LIST);
						 auto result = testee.equal_range(Key());
						 TestCase::assert(std::is_same<std::pair<typename MapType<Key, T>::const_iterator, typename MapType<Key, T>::const_iterator>, decltype(result)>::value);
					 }),

			TestCase("get_allocator", [this]
					 {
						 MapType<Key, T> testee;
						 auto result = testee.get_allocator();
						 TestCase::assert(std::is_same<typename MapType<Key, T>::allocator_type, decltype(result)>::value);
					 }),

			TestCase("operator==", [this]
					 {
						 MapType<Key, T> lhs(INITIALIZER_LIST);
						 MapType<Key, T> rhs(INITIALIZER_LIST);
						 auto result = (lhs == rhs);
						 TestCase::assert(std::is_same<bool, decltype(result)>::value, "type");
						 TestCase::assert(result == true, "result");
					 }),

			TestCase("operator!=", [this]
					 {
						 MapType<Key, T> lhs;
						 MapType<Key, T> rhs(INITIALIZER_LIST);
						 auto result = (lhs != rhs);
						 TestCase::assert(std::is_same<bool, decltype(result)>::value, "type");
						 TestCase::assert(result == true, "result");
					 }),

			TestCase("operator<", [this]
					 {
						 MapType<Key, T> lhs;
						 MapType<Key, T> rhs(INITIALIZER_LIST);
						 auto result = (lhs < rhs);
						 TestCase::assert(std::is_same<bool, decltype(result)>::value, "type");
						 TestCase::assert(result == true, "result");
					 }),

			TestCase("operator<=", [this]
					 {
						 MapType<Key, T> lhs;
						 MapType<Key, T> rhs(INITIALIZER_LIST);
						 auto result = (lhs <= rhs);
						 TestCase::assert(std::is_same<bool, decltype(result)>::value, "type");
						 TestCase::assert(result == true, "result");
					 }),

			TestCase("operator>", [this]
					 {
						 MapType<Key, T> lhs(INITIALIZER_LIST);
						 MapType<Key, T> rhs;
						 auto result = (lhs > rhs);
						 TestCase::assert(std::is_same<bool, decltype(result)>::value, "type");
						 TestCase::assert(result == true, "result");
					 }),

			TestCase("operator>=", [this]
					 {
						 MapType<Key, T> lhs(INITIALIZER_LIST);
						 MapType<Key, T> rhs;
						 auto result = (lhs >= rhs);
						 TestCase::assert(std::is_same<bool, decltype(result)>::value, "type");
						 TestCase::assert(result == true, "result");
					 }),

			TestCase("swap lhs rhs", [this]
					 {
						 MapType<Key, T> lhs(INITIALIZER_LIST);
						 MapType<Key, T> rhs;
						 swap(lhs, rhs);
						 TestCase::assert(lhs.size() == 0, "lhs");
						 TestCase::assert(rhs.size() == INITIALIZER_LIST.size(), "rhs");
					 })
		})
	{
	}

private:
	static constexpr InitializerListType INITIALIZER_LIST = {std::make_pair(Key(), T())};
	static constexpr ArrayType ARRAY = {std::make_pair(Key(), T())};
};

template<template<typename...> class MapType, typename Key, typename T, bool isMultimap>
constexpr typename StdMapTestSuite<MapType, Key, T, isMultimap>::InitializerListType StdMapTestSuite<MapType, Key, T, isMultimap>::INITIALIZER_LIST;

template<template<typename...> class MapType, typename Key, typename T, bool isMultimap>
constexpr typename StdMapTestSuite<MapType, Key, T, isMultimap>::ArrayType StdMapTestSuite<MapType, Key, T, isMultimap>::ARRAY;


// Conditionally enabled test executors handling map vs multimap.

template<template<typename...> class MapType, typename Key, typename T, bool isMultimap>
class TestSubscriptOperator<MapType, Key, T, isMultimap, typename std::enable_if<!isMultimap>::type>
{
public:
	void operator()()
	{
		MapType<Key, T> testee({std::make_pair(Key(), T())});
		auto& result = testee[Key()];
		TestCase::assert(std::is_same<typename MapType<Key, T>::mapped_type&, decltype(result)>::value, "type");
		TestCase::assert(result == T(), "result");
	}
};

template<template<typename...> class MapType, typename Key, typename T, bool isMultimap>
class TestSubscriptOperator<MapType, Key, T, isMultimap, typename std::enable_if<isMultimap>::type>
{
public:
	void operator()()
	{
	}
};

template<template<typename...> class MapType, typename Key, typename T, bool isMultimap>
class TestSubscriptOperatorMove<MapType, Key, T, isMultimap, typename std::enable_if<!isMultimap>::type>
{
public:
	void operator()() const
	{
		MapType<Key, T> testee({std::make_pair(Key(), T())});
		auto& result = testee[std::move(Key())];
		TestCase::assert(std::is_same<typename MapType<Key, T>::mapped_type&, decltype(result)>::value, "type");
		TestCase::assert(result == T(), "result");
	}
};

template<template<typename...> class MapType, typename Key, typename T, bool isMultimap>
class TestSubscriptOperatorMove<MapType, Key, T, isMultimap, typename std::enable_if<isMultimap>::type>
{
public:
	void operator()()
	{
	}
};

template<template<typename...> class MapType, typename Key, typename T, bool isMultimap>
class TestAt<MapType, Key, T, isMultimap, typename std::enable_if<!isMultimap>::type>
{
public:
	void operator()()
	{
		MapType<Key, T> testee({std::make_pair(Key(), T())});
		auto& result = testee.at(Key());
		TestCase::assert(std::is_same<typename MapType<Key, T>::mapped_type&, decltype(result)>::value, "type");
		TestCase::assert(result == T(), "result");
	}
};

template<template<typename...> class MapType, typename Key, typename T, bool isMultimap>
class TestAt<MapType, Key, T, isMultimap, typename std::enable_if<isMultimap>::type>
{
public:
	void operator()()
	{
	}
};

template<template<typename...> class MapType, typename Key, typename T, bool isMultimap>
class TestAtConst<MapType, Key, T, isMultimap, typename std::enable_if<!isMultimap>::type>
{
public:
	void operator()()
	{
		const MapType<Key, T> testee({std::make_pair(Key(), T())});
		auto& result = testee.at(Key());
		TestCase::assert(std::is_same<const typename MapType<Key, T>::mapped_type&, decltype(result)>::value, "type");
		TestCase::assert(result == T(), "result");
	}
};

template<template<typename...> class MapType, typename Key, typename T, bool isMultimap>
class TestAtConst<MapType, Key, T, isMultimap, typename std::enable_if<isMultimap>::type>
{
public:
	void operator()()
	{
	}
};


#endif // StdMapTestSuite_INCLUDED
