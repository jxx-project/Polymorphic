//
// Copyright (C) 2018 Dr. Michael Steffens
//
// SPDX-License-Identifier:		BSL-1.0
//


#ifndef MapTestSuite_INCLUDED
#define MapTestSuite_INCLUDED

#include "Testee/TestSuite.h"
#include <array>

namespace Testee {

// Conditionally enabled test executors handling map vs multimap.

template<template<typename...> class MapType, typename Key, typename T, bool isMultimap, typename Compare, typename Allocator, typename Enable = void>
class TestSubscriptOperator;

template<template<typename...> class MapType, typename Key, typename T, bool isMultimap, typename Compare, typename Allocator, typename Enable = void>
class TestSubscriptOperatorMove;

template<template<typename...> class MapType, typename Key, typename T, bool isMultimap, typename Compare, typename Allocator, typename Enable = void>
class TestAt;

template<template<typename...> class MapType, typename Key, typename T, bool isMultimap, typename Compare, typename Allocator, typename Enable = void>
class TestAtConst;


/// Test MapType C++11 standard map or multimap interface.
template< template<typename...> class MapType, typename Key, typename T, bool isMultimap = false, typename Compare = std::less<Key>, typename Allocator = std::allocator< std::pair<const Key, T> > >
class MapTestSuite : public TestSuite
{
public:
	typedef std::initializer_list< std::pair<const Key, T> > InitializerListType;
	typedef std::array<std::pair<const Key, T>, 1> ArrayType;
	typedef typename MapType<Key, T, Compare, Allocator>::value_type ValueType;

	MapTestSuite(const std::string& mapType) : TestSuite(mapType + " C++11 standard interface", {

			TestCase("typedefs", []
					 {
						 TestCase::assert(std::is_same<typename MapType<Key, T, Compare, Allocator>::key_type, Key>::value, "key_type");
						 TestCase::assert(std::is_same<typename MapType<Key, T, Compare, Allocator>::mapped_type, T>::value, "mapped_type");
						 TestCase::assert(std::is_same<typename MapType<Key, T, Compare, Allocator>::value_type, std::pair<const Key, T> >::value, "value_type");
						 TestCase::assert(std::is_class<typename MapType<Key, T, Compare, Allocator>::allocator_type>::value, "allocator_type");
						 TestCase::assert(std::is_same<typename MapType<Key, T, Compare, Allocator>::reference, std::pair<const Key, T>&>::value, "reference");
						 TestCase::assert(std::is_same<typename MapType<Key, T, Compare, Allocator>::const_reference, const std::pair<const Key, T>&>::value, "const_reference");
					 }),

			TestCase("ctor default", []
					 {
						 MapType<Key, T, Compare, Allocator> testee;
						 TestCase::assert(testee.size() == 0);
					 }),

			// TestCase("ctor default with allocator", []
			//		 {
			//			 MapType<Key, T, Compare, Allocator> testee(std::allocator<T>());
			//			 TestCase::assert(testee.size() == 0);
			//		 }),

			TestCase("ctor copy", []
					 {
						 const MapType<Key, T, Compare, Allocator> other(INITIALIZER_LIST);
						 MapType<Key, T, Compare, Allocator> testee(other);
						 TestCase::assert(testee.size() == INITIALIZER_LIST.size());
					 }),

			// TestCase("ctor copy with allocator", []
			//		 {
			//			 const MapType<Key, T, Compare, Allocator> other(INITIALIZER_LIST);
			//			 MapType<Key, T, Compare, Allocator> testee(other, std::allocator<T>());
			//			 TestCase::assert(testee.size() == INITIALIZER_LIST.size());
			//		 }),

			TestCase("ctor move", []
					 {
						 MapType<Key, T, Compare, Allocator> other(INITIALIZER_LIST);
						 MapType<Key, T, Compare, Allocator> testee(std::move(other));
						 TestCase::assert(other.size() == 0, "other");
						 TestCase::assert(testee.size() == INITIALIZER_LIST.size(), "testee");
					 }),

			// TestCase("ctor move with allocator", []
			//		 {
			//			 MapType<Key, T, Compare, Allocator> other(INITIALIZER_LIST);
			//			 MapType<Key, T, Compare, Allocator> testee(std::move(other), std::allocator<T>());
			//			 TestCase::assert(other.size() == 0, "other");
			//			 TestCase::assert(testee.size() == INITIALIZER_LIST.size(), "testee");
			//		 }),

			TestCase("ctor range", []
					 {
						 MapType<Key, T, Compare, Allocator> testee(ARRAY.begin(), ARRAY.end());
						 TestCase::assert(testee.size() == ARRAY.size());
					 }),

			TestCase("ctor initializer list", []
					 {
						 MapType<Key, T, Compare, Allocator> testee(INITIALIZER_LIST);
						 TestCase::assert(testee.size() == INITIALIZER_LIST.size());
					 }),

			TestCase("operator= copy", []
					 {
						 const MapType<Key, T, Compare, Allocator> other(INITIALIZER_LIST);
						 MapType<Key, T, Compare, Allocator> testee;
						 auto& result = (testee = other);
						 TestCase::assert(std::is_same<MapType<Key, T, Compare, Allocator>&, decltype(result)>::value, "type");
						 TestCase::assert(testee.size() == INITIALIZER_LIST.size(), "result");
					 }),

			TestCase("operator= move", []
					 {
						 MapType<Key, T, Compare, Allocator> other(INITIALIZER_LIST);
						 MapType<Key, T, Compare, Allocator> testee;
						 auto& result = (testee = std::move(other));
						 TestCase::assert(std::is_same<MapType<Key, T, Compare, Allocator>&, decltype(result)>::value, "type");
						 TestCase::assert(other.size() == 0, "other");
						 TestCase::assert(testee.size() == INITIALIZER_LIST.size(), "testee");
					 }),

			TestCase("operator= initializer list", []
					 {
						 MapType<Key, T, Compare, Allocator> testee;
						 auto& result = (testee = INITIALIZER_LIST);
						 TestCase::assert(std::is_same<MapType<Key, T, Compare, Allocator>&, decltype(result)>::value, "type");
						 TestCase::assert(testee.size() == INITIALIZER_LIST.size(), "result");
					 }),

			TestCase("begin", []
					 {
						 MapType<Key, T, Compare, Allocator> testee(INITIALIZER_LIST);
						 auto result = testee.begin();
						 TestCase::assert(std::is_same<typename MapType<Key, T, Compare, Allocator>::iterator, decltype(result)>::value, "type");
						 TestCase::assert(*result == ValueType(), "result");
					 }),

			TestCase("begin const", []
					 {
						 const MapType<Key, T, Compare, Allocator> testee(INITIALIZER_LIST);
						 auto result = testee.begin();
						 TestCase::assert(std::is_same<typename MapType<Key, T, Compare, Allocator>::const_iterator, decltype(result)>::value, "type");
						 TestCase::assert(*result == ValueType(), "result");
					 }),

			TestCase("end", []
					 {
						 MapType<Key, T, Compare, Allocator> testee(INITIALIZER_LIST);
						 auto result = testee.end();
						 TestCase::assert(std::is_same<typename MapType<Key, T, Compare, Allocator>::iterator, decltype(result)>::value, "type");
						 TestCase::assert(*(--result) == ValueType(), "result");
					 }),

			TestCase("end const", []
					 {
						 const MapType<Key, T, Compare, Allocator> testee(INITIALIZER_LIST);
						 auto result = testee.end();
						 TestCase::assert(std::is_same<typename MapType<Key, T, Compare, Allocator>::const_iterator, decltype(result)>::value, "type");
						 TestCase::assert(*(--result) == ValueType(), "result");
					 }),

			TestCase("rbegin", []
					 {
						 MapType<Key, T, Compare, Allocator> testee(INITIALIZER_LIST);
						 auto result = testee.rbegin();
						 TestCase::assert(std::is_same<typename MapType<Key, T, Compare, Allocator>::reverse_iterator, decltype(result)>::value, "type");
						 TestCase::assert(*result == ValueType(), "result");
					 }),

			TestCase("rbegin const", []
					 {
						 const MapType<Key, T, Compare, Allocator> testee(INITIALIZER_LIST);
						 auto result = testee.rbegin();
						 TestCase::assert(std::is_same<typename MapType<Key, T, Compare, Allocator>::const_reverse_iterator, decltype(result)>::value, "type");
						 TestCase::assert(*result == ValueType(), "result");
					 }),

			TestCase("rend", []
					 {
						 MapType<Key, T, Compare, Allocator> testee(INITIALIZER_LIST);
						 auto result = testee.rend();
						 TestCase::assert(std::is_same<typename MapType<Key, T, Compare, Allocator>::reverse_iterator, decltype(result)>::value, "type");
						 TestCase::assert(*(--result) == ValueType(), "result");
					 }),

			TestCase("rend const", []
					 {
						 const MapType<Key, T, Compare, Allocator> testee(INITIALIZER_LIST);
						 auto result = testee.rend();
						 TestCase::assert(std::is_same<typename MapType<Key, T, Compare, Allocator>::const_reverse_iterator, decltype(result)>::value, "type");
						 TestCase::assert(*(--result) == ValueType(), "result");
					 }),

			TestCase("cbegin", []
					 {
						 MapType<Key, T, Compare, Allocator> testee(INITIALIZER_LIST);
						 auto result = testee.cbegin();
						 TestCase::assert(std::is_same<typename MapType<Key, T, Compare, Allocator>::const_iterator, decltype(result)>::value, "type");
						 TestCase::assert(*result == ValueType(), "result");
					 }),

			TestCase("cend", []
					 {
						 MapType<Key, T, Compare, Allocator> testee(INITIALIZER_LIST);
						 auto result = testee.cend();
						 TestCase::assert(std::is_same<typename MapType<Key, T, Compare, Allocator>::const_iterator, decltype(result)>::value, "type");
						 TestCase::assert(*(--result) == ValueType(), "result");
					 }),

			TestCase("crbegin", []
					 {
						 MapType<Key, T, Compare, Allocator> testee(INITIALIZER_LIST);
						 auto result = testee.crbegin();
						 TestCase::assert(std::is_same<typename MapType<Key, T, Compare, Allocator>::const_reverse_iterator, decltype(result)>::value, "type");
						 TestCase::assert(*result == ValueType(), "result");
					 }),

			TestCase("crend", []
					 {
						 MapType<Key, T, Compare, Allocator> testee(INITIALIZER_LIST);
						 auto result = testee.crend();
						 TestCase::assert(std::is_same<typename MapType<Key, T, Compare, Allocator>::const_reverse_iterator, decltype(result)>::value, "type");
						 TestCase::assert(*(--result) == ValueType(), "result");
					 }),

			TestCase("empty", []
					 {
						 const MapType<Key, T, Compare, Allocator> testee;
						 auto result = testee.empty();
						 TestCase::assert(std::is_same<bool, decltype(result)>::value, "bool");
						 TestCase::assert(result == true, "result");
					 }),

			TestCase("size", []
					 {
						 const MapType<Key, T, Compare, Allocator> testee(INITIALIZER_LIST);
						 auto result = testee.size();
						 TestCase::assert(std::is_same<typename MapType<Key, T, Compare, Allocator>::size_type, decltype(result)>::value, "type");
						 TestCase::assert(result == INITIALIZER_LIST.size(), "result");
					 }),

			TestCase("max_size", []
					 {
						 const MapType<Key, T, Compare, Allocator> testee(INITIALIZER_LIST);
						 auto result = testee.max_size();
						 TestCase::assert(std::is_same<typename MapType<Key, T, Compare, Allocator>::size_type, decltype(result)>::value, "type");
						 TestCase::assert(result >= INITIALIZER_LIST.size(), "result");
					 }),


			TestCase("operator[]", TestSubscriptOperator<MapType, Key, T, isMultimap, Compare, Allocator>()),

			TestCase("operator[] move", TestSubscriptOperatorMove<MapType, Key, T, isMultimap, Compare, Allocator>()),

			TestCase("at", TestAt<MapType, Key, T, isMultimap, Compare, Allocator>()),

			TestCase("at const", TestAtConst<MapType, Key, T, isMultimap, Compare, Allocator>()),

			TestCase("insert single element", []
					 {
						 MapType<Key, T, Compare, Allocator> testee;
						 auto position = testee.begin();
						 auto value = std::make_pair(Key(), T());
						 auto result = testee.insert(value);
						 if (!isMultimap) {
							 TestCase::assert(std::is_same<std::pair<typename MapType<Key, T, Compare, Allocator>::iterator, bool>, decltype(result)>::value, "type");
						 } else {
							 TestCase::assert(std::is_same<typename MapType<Key, T, Compare, Allocator>::iterator, decltype(result)>::value, "type");
						 }
						 TestCase::assert(testee.size() == 1, "result");
					 }),

			TestCase("insert move", []
					 {
						 MapType<Key, T, Compare, Allocator> testee;
						 auto position = testee.begin();
						 auto value = std::make_pair(Key(), T());
						 auto result = testee.insert(std::move(value));
						 if (!isMultimap) {
							 TestCase::assert(std::is_same<std::pair<typename MapType<Key, T, Compare, Allocator>::iterator, bool>, decltype(result)>::value, "type");
						 } else {
							 TestCase::assert(std::is_same<typename MapType<Key, T, Compare, Allocator>::iterator, decltype(result)>::value, "type");
						 }
						 TestCase::assert(testee.size() == 1, "result");
					 }),

			TestCase("insert hint single element", []
					 {
						 MapType<Key, T, Compare, Allocator> testee;
						 auto position = testee.begin();
						 auto value = std::make_pair(Key(), T());
						 auto result = testee.insert(position, value);
						 TestCase::assert(std::is_same<typename MapType<Key, T, Compare, Allocator>::iterator, decltype(result)>::value, "type");
						 TestCase::assert(testee.size() == 1, "result");
					 }),

			TestCase("insert hint move", []
					 {
						 MapType<Key, T, Compare, Allocator> testee;
						 auto position = testee.begin();
						 auto value = std::make_pair(Key(), T());
						 auto result = testee.insert(position, std::move(value));
						 TestCase::assert(std::is_same<typename MapType<Key, T, Compare, Allocator>::iterator, decltype(result)>::value, "type");
						 TestCase::assert(testee.size() == 1, "result");
					 }),

			TestCase("insert range", []
					 {
						 MapType<Key, T, Compare, Allocator> testee;
						 testee.insert(ARRAY.begin(), ARRAY.end());
						 TestCase::assert(testee.size() == ARRAY.size());
					 }),

			TestCase("insert initializer list", []
					 {
						 MapType<Key, T, Compare, Allocator> testee;
						 testee.insert(INITIALIZER_LIST);
						 TestCase::assert(testee.size() == INITIALIZER_LIST.size());
					 }),

			TestCase("erase single element", []
					 {
						 MapType<Key, T, Compare, Allocator> testee(INITIALIZER_LIST);
						 auto position = testee.begin();
						 auto result = testee.erase(position);
						 TestCase::assert(std::is_same<typename MapType<Key, T, Compare, Allocator>::iterator, decltype(result)>::value, "type");
						 TestCase::assert(testee.size() == 0, "result");
					 }),

			TestCase("erase key", []
					 {
						 MapType<Key, T, Compare, Allocator> testee(INITIALIZER_LIST);
						 auto result = testee.erase(Key());
						 TestCase::assert(std::is_same<typename MapType<Key, T, Compare, Allocator>::size_type, decltype(result)>::value, "type");
						 TestCase::assert(testee.size() == 0, "result");
					 }),

			TestCase("erase range", []
					 {
						 MapType<Key, T, Compare, Allocator> testee(INITIALIZER_LIST);
						 auto first = testee.begin();
						 auto last = testee.end();;
						 auto result = testee.erase(first, last);
						 TestCase::assert(std::is_same<typename MapType<Key, T, Compare, Allocator>::iterator, decltype(result)>::value, "type");
						 TestCase::assert(testee.size() == 0, "result");
					 }),

			TestCase("swap", []
					 {
						 MapType<Key, T, Compare, Allocator> other(INITIALIZER_LIST);
						 MapType<Key, T, Compare, Allocator> testee(INITIALIZER_LIST);
						 testee.swap(other);
						 TestCase::assert(other.size() == INITIALIZER_LIST.size(), "other");
						 TestCase::assert(testee.size() == INITIALIZER_LIST.size(), "testee");
					 }),

			TestCase("clear", []
					 {
						 MapType<Key, T, Compare, Allocator> testee(INITIALIZER_LIST);
						 testee.clear();
						 TestCase::assert(testee.size() == 0);
					 }),

			TestCase("emplace", []
					 {
						 MapType<Key, T, Compare, Allocator> testee;
						 auto result = testee.emplace();
						 if (!isMultimap) {
							 TestCase::assert(std::is_same<std::pair<typename MapType<Key, T, Compare, Allocator>::iterator, bool>, decltype(result)>::value, "type");
						 } else {
							 TestCase::assert(std::is_same<typename MapType<Key, T, Compare, Allocator>::iterator, decltype(result)>::value, "type");
						 }
						 TestCase::assert(testee.size() == 1, "result");
					 }),

			TestCase("emplace_hint", []
					 {
						 MapType<Key, T, Compare, Allocator> testee;
						 auto position = testee.begin();
						 auto result = testee.emplace_hint(position);
						 TestCase::assert(std::is_same<typename MapType<Key, T, Compare, Allocator>::iterator, decltype(result)>::value, "type");
						 TestCase::assert(testee.size() == 1, "result");
					 }),

			TestCase("key_comp", []
					 {
						 const MapType<Key, T, Compare, Allocator> testee;
						 auto result = testee.key_comp();
						 TestCase::assert(std::is_same<typename MapType<Key, T, Compare, Allocator>::key_compare, decltype(result)>::value);
					 }),

			TestCase("value_comp", []
					 {
						 const MapType<Key, T, Compare, Allocator> testee;
						 auto result = testee.value_comp();
						 TestCase::assert(std::is_same<typename MapType<Key, T, Compare, Allocator>::value_compare, decltype(result)>::value);
					 }),

			TestCase("find", []
					 {
						 MapType<Key, T, Compare, Allocator> testee(INITIALIZER_LIST);
						 auto result = testee.find(Key());
						 TestCase::assert(std::is_same<typename MapType<Key, T, Compare, Allocator>::iterator, decltype(result)>::value, "type");
						 TestCase::assert(*result == ValueType(), "result");
					 }),

			TestCase("find const", []
					 {
						 const MapType<Key, T, Compare, Allocator> testee(INITIALIZER_LIST);
						 auto result = testee.find(Key());
						 TestCase::assert(std::is_same<typename MapType<Key, T, Compare, Allocator>::const_iterator, decltype(result)>::value, "type");
						 TestCase::assert(*result == ValueType(), "result");
					 }),

			TestCase("count", []
					 {
						 const MapType<Key, T, Compare, Allocator> testee(INITIALIZER_LIST);
						 auto result = testee.count(Key());
						 TestCase::assert(std::is_same<typename MapType<Key, T, Compare, Allocator>::size_type, decltype(result)>::value, "type");
						 TestCase::assert(result == 1, "result");
					 }),

			TestCase("lower_bound", []
					 {
						 MapType<Key, T, Compare, Allocator> testee(INITIALIZER_LIST);
						 auto result = testee.lower_bound(Key());
						 TestCase::assert(std::is_same<typename MapType<Key, T, Compare, Allocator>::iterator, decltype(result)>::value, "type");
						 TestCase::assert(*result == ValueType(), "result");
					 }),

			TestCase("lower_bound const", []
					 {
						 const MapType<Key, T, Compare, Allocator> testee(INITIALIZER_LIST);
						 auto result = testee.lower_bound(Key());
						 TestCase::assert(std::is_same<typename MapType<Key, T, Compare, Allocator>::const_iterator, decltype(result)>::value, "type");
						 TestCase::assert(*result == ValueType(), "result");
					 }),

			TestCase("upper_bound", []
					 {
						 MapType<Key, T, Compare, Allocator> testee(INITIALIZER_LIST);
						 auto result = testee.upper_bound(Key());
						 TestCase::assert(std::is_same<typename MapType<Key, T, Compare, Allocator>::iterator, decltype(result)>::value, "type");
						 TestCase::assert(*(--result) == ValueType(), "result");
					 }),

			TestCase("upper_bound const", []
					 {
						 const MapType<Key, T, Compare, Allocator> testee(INITIALIZER_LIST);
						 auto result = testee.upper_bound(Key());
						 TestCase::assert(std::is_same<typename MapType<Key, T, Compare, Allocator>::const_iterator, decltype(result)>::value, "type");
						 TestCase::assert(*(--result) == ValueType(), "result");
					 }),

			TestCase("equal_range", []
					 {
						 MapType<Key, T, Compare, Allocator> testee(INITIALIZER_LIST);
						 auto result = testee.equal_range(Key());
						 TestCase::assert(std::is_same<std::pair<typename MapType<Key, T, Compare, Allocator>::iterator, typename MapType<Key, T, Compare, Allocator>::iterator>, decltype(result)>::value);
					 }),

			TestCase("equal_range const", []
					 {
						 const MapType<Key, T, Compare, Allocator> testee(INITIALIZER_LIST);
						 auto result = testee.equal_range(Key());
						 TestCase::assert(std::is_same<std::pair<typename MapType<Key, T, Compare, Allocator>::const_iterator, typename MapType<Key, T, Compare, Allocator>::const_iterator>, decltype(result)>::value);
					 }),

			TestCase("get_allocator", []
					 {
						 MapType<Key, T, Compare, Allocator> testee;
						 auto result = testee.get_allocator();
						 TestCase::assert(std::is_same<typename MapType<Key, T, Compare, Allocator>::allocator_type, decltype(result)>::value);
					 }),

			TestCase("operator==", []
					 {
						 MapType<Key, T, Compare, Allocator> lhs(INITIALIZER_LIST);
						 MapType<Key, T, Compare, Allocator> rhs(INITIALIZER_LIST);
						 auto result = (lhs == rhs);
						 TestCase::assert(std::is_same<bool, decltype(result)>::value, "type");
						 TestCase::assert(result == true, "result");
					 }),

			TestCase("operator!=", []
					 {
						 MapType<Key, T, Compare, Allocator> lhs;
						 MapType<Key, T, Compare, Allocator> rhs(INITIALIZER_LIST);
						 auto result = (lhs != rhs);
						 TestCase::assert(std::is_same<bool, decltype(result)>::value, "type");
						 TestCase::assert(result == true, "result");
					 }),

			TestCase("operator<", []
					 {
						 MapType<Key, T, Compare, Allocator> lhs;
						 MapType<Key, T, Compare, Allocator> rhs(INITIALIZER_LIST);
						 auto result = (lhs < rhs);
						 TestCase::assert(std::is_same<bool, decltype(result)>::value, "type");
						 TestCase::assert(result == true, "result");
					 }),

			TestCase("operator<=", []
					 {
						 MapType<Key, T, Compare, Allocator> lhs;
						 MapType<Key, T, Compare, Allocator> rhs(INITIALIZER_LIST);
						 auto result = (lhs <= rhs);
						 TestCase::assert(std::is_same<bool, decltype(result)>::value, "type");
						 TestCase::assert(result == true, "result");
					 }),

			TestCase("operator>", []
					 {
						 MapType<Key, T, Compare, Allocator> lhs(INITIALIZER_LIST);
						 MapType<Key, T, Compare, Allocator> rhs;
						 auto result = (lhs > rhs);
						 TestCase::assert(std::is_same<bool, decltype(result)>::value, "type");
						 TestCase::assert(result == true, "result");
					 }),

			TestCase("operator>=", []
					 {
						 MapType<Key, T, Compare, Allocator> lhs(INITIALIZER_LIST);
						 MapType<Key, T, Compare, Allocator> rhs;
						 auto result = (lhs >= rhs);
						 TestCase::assert(std::is_same<bool, decltype(result)>::value, "type");
						 TestCase::assert(result == true, "result");
					 }),

			TestCase("swap lhs rhs", []
					 {
						 MapType<Key, T, Compare, Allocator> lhs(INITIALIZER_LIST);
						 MapType<Key, T, Compare, Allocator> rhs;
						 swap(lhs, rhs);
						 TestCase::assert(lhs.size() == 0, "lhs");
						 TestCase::assert(rhs.size() == INITIALIZER_LIST.size(), "rhs");
					 })
		})
	{
	}

	static const InitializerListType INITIALIZER_LIST;
	static const ArrayType ARRAY;
};

template<template<typename...> class MapType, typename Key, typename T, bool isMultimap, typename Compare, typename Allocator>
const typename MapTestSuite<MapType, Key, T, isMultimap, Compare, Allocator>::InitializerListType MapTestSuite<MapType, Key, T, isMultimap, Compare, Allocator>::INITIALIZER_LIST = {std::make_pair(Key(), T())};

template<template<typename...> class MapType, typename Key, typename T, bool isMultimap, typename Compare, typename Allocator>
const typename MapTestSuite<MapType, Key, T, isMultimap, Compare, Allocator>::ArrayType MapTestSuite<MapType, Key, T, isMultimap, Compare, Allocator>::ARRAY = {std::make_pair(Key(), T())};


// Conditionally enabled test executors handling map vs multimap.

template<template<typename...> class MapType, typename Key, typename T, bool isMultimap, typename Compare, typename Allocator>
class TestSubscriptOperator<MapType, Key, T, isMultimap, Compare, Allocator, typename std::enable_if<!isMultimap>::type>
{
public:
	void operator()()
	{
		MapType<Key, T, Compare, Allocator> testee(MapTestSuite<MapType, Key, T, isMultimap, Compare, Allocator>::INITIALIZER_LIST);
		auto& result = testee[Key()];
		TestCase::assert(std::is_same<typename MapType<Key, T, Compare, Allocator>::mapped_type&, decltype(result)>::value, "type");
		TestCase::assert(result == T(), "result");
	}
};

template<template<typename...> class MapType, typename Key, typename T, bool isMultimap, typename Compare, typename Allocator>
class TestSubscriptOperator<MapType, Key, T, isMultimap, Compare, Allocator, typename std::enable_if<isMultimap>::type>
{
public:
	void operator()()
	{
	}
};

template<template<typename...> class MapType, typename Key, typename T, bool isMultimap, typename Compare, typename Allocator>
class TestSubscriptOperatorMove<MapType, Key, T, isMultimap, Compare, Allocator, typename std::enable_if<!isMultimap>::type>
{
public:
	void operator()() const
	{
		MapType<Key, T, Compare, Allocator> testee(MapTestSuite<MapType, Key, T, isMultimap, Compare, Allocator>::INITIALIZER_LIST);
		auto& result = testee[std::move(Key())];
		TestCase::assert(std::is_same<typename MapType<Key, T, Compare, Allocator>::mapped_type&, decltype(result)>::value, "type");
		TestCase::assert(result == T(), "result");
	}
};

template<template<typename...> class MapType, typename Key, typename T, bool isMultimap, typename Compare, typename Allocator>
class TestSubscriptOperatorMove<MapType, Key, T, isMultimap, Compare, Allocator, typename std::enable_if<isMultimap>::type>
{
public:
	void operator()()
	{
	}
};

template<template<typename...> class MapType, typename Key, typename T, bool isMultimap, typename Compare, typename Allocator>
class TestAt<MapType, Key, T, isMultimap, Compare, Allocator, typename std::enable_if<!isMultimap>::type>
{
public:
	void operator()()
	{
		MapType<Key, T, Compare, Allocator> testee(MapTestSuite<MapType, Key, T, isMultimap, Compare, Allocator>::INITIALIZER_LIST);
		auto& result = testee.at(Key());
		TestCase::assert(std::is_same<typename MapType<Key, T, Compare, Allocator>::mapped_type&, decltype(result)>::value, "type");
		TestCase::assert(result == T(), "result");
	}
};

template<template<typename...> class MapType, typename Key, typename T, bool isMultimap, typename Compare, typename Allocator>
class TestAt<MapType, Key, T, isMultimap, Compare, Allocator, typename std::enable_if<isMultimap>::type>
{
public:
	void operator()()
	{
	}
};

template<template<typename...> class MapType, typename Key, typename T, bool isMultimap, typename Compare, typename Allocator>
class TestAtConst<MapType, Key, T, isMultimap, Compare, Allocator, typename std::enable_if<!isMultimap>::type>
{
public:
	void operator()()
	{
		const MapType<Key, T, Compare, Allocator> testee(MapTestSuite<MapType, Key, T, isMultimap, Compare, Allocator>::INITIALIZER_LIST);
		auto& result = testee.at(Key());
		TestCase::assert(std::is_same<const typename MapType<Key, T, Compare, Allocator>::mapped_type&, decltype(result)>::value, "type");
		TestCase::assert(result == T(), "result");
	}
};

template<template<typename...> class MapType, typename Key, typename T, bool isMultimap, typename Compare, typename Allocator>
class TestAtConst<MapType, Key, T, isMultimap, Compare, Allocator, typename std::enable_if<isMultimap>::type>
{
public:
	void operator()()
	{
	}
};

} // namespace Testee

#endif // MapTestSuite_INCLUDED
