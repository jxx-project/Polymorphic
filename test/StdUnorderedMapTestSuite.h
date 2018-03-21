//
// Copyright (C) 2018 Dr. Michael Steffens
//
// SPDX-License-Identifier:		BSL-1.0
//


#ifndef StdUnorderedMapTestSuite_INCLUDED
#define StdUnorderedMapTestSuite_INCLUDED

#include "TestSuite.h"

// Conditionally enabled test executors handling map vs multimap.

template<template<typename...> class UnorderedMapType, typename Key, typename T, bool isMultimap, typename Enable = void>
class TestSubscriptOperator;

template<template<typename...> class UnorderedMapType, typename Key, typename T, bool isMultimap, typename Enable = void>
class TestSubscriptOperatorMove;

template<template<typename...> class UnorderedMapType, typename Key, typename T, bool isMultimap, typename Enable = void>
class TestAt;

template<template<typename...> class UnorderedMapType, typename Key, typename T, bool isMultimap, typename Enable = void>
class TestAtConst;


/// Test UnorderedMapType C++-11 standard map or multimap interface.
template<template<typename...> class UnorderedMapType, typename Key, typename T, bool isMultimap = false>
class StdUnorderedMapTestSuite : public TestSuite
{
public:
	typedef std::initializer_list< std::pair<const Key, T> > InitializerListType;
	typedef std::array<std::pair<const Key, T>, 1> ArrayType;

	StdUnorderedMapTestSuite() : TestSuite({

			TestCase("typedefs", [this]
					 {
						 TestCase::assert(std::is_same<typename UnorderedMapType<Key, T>::key_type, Key>::value, "key_type");
						 TestCase::assert(std::is_same<typename UnorderedMapType<Key, T>::mapped_type, T>::value, "mapped_type");
						 TestCase::assert(std::is_same<typename UnorderedMapType<Key, T>::value_type, std::pair<const Key, T> >::value, "value_type");
						 TestCase::assert(std::is_class<typename UnorderedMapType<Key, T>::hasher>::value, "hasher");
						 TestCase::assert(std::is_class<typename UnorderedMapType<Key, T>::key_equal>::value, "key_equal");
						 TestCase::assert(std::is_class<typename UnorderedMapType<Key, T>::allocator_type>::value, "allocator_type");
						 TestCase::assert(std::is_same<typename UnorderedMapType<Key, T>::reference, typename UnorderedMapType<Key, T>::allocator_type::reference>::value, "reference");
						 TestCase::assert(std::is_same<typename UnorderedMapType<Key, T>::const_reference, typename UnorderedMapType<Key, T>::allocator_type::const_reference>::value, "const_reference");
					 }),

			TestCase("ctor default", [this]
					 {
						 UnorderedMapType<Key, T> testee;
						 TestCase::assert(testee.size() == 0);
					 }),

			// TestCase("ctor default with allocator", [this]
			//		 {
			//			 UnorderedMapType<Key, T> testee(std::allocator<T>());
			//			 TestCase::assert(testee.size() == 0);
			//		 }),

			TestCase("ctor copy", [this]
					 {
						 const UnorderedMapType<Key, T> other(INITIALIZER_LIST);
						 UnorderedMapType<Key, T> testee(other);
						 TestCase::assert(testee.size() == INITIALIZER_LIST.size());
					 }),

			// TestCase("ctor copy with allocator", [this]
			//		 {
			//			 const UnorderedMapType<Key, T> other(INITIALIZER_LIST);
			//			 UnorderedMapType<Key, T> testee(other, std::allocator<T>());
			//			 TestCase::assert(testee.size() == INITIALIZER_LIST.size());
			//		 }),

			TestCase("ctor move", [this]
					 {
						 UnorderedMapType<Key, T> other(INITIALIZER_LIST);
						 UnorderedMapType<Key, T> testee(std::move(other));
						 TestCase::assert(other.size() == 0, "other");
						 TestCase::assert(testee.size() == INITIALIZER_LIST.size(), "testee");
					 }),

			// TestCase("ctor move with allocator", [this]
			//		 {
			//			 UnorderedMapType<Key, T> other(INITIALIZER_LIST);
			//			 UnorderedMapType<Key, T> testee(std::move(other), std::allocator<T>());
			//			 TestCase::assert(other.size() == 0, "other");
			//			 TestCase::assert(testee.size() == INITIALIZER_LIST.size(), "testee");
			//		 }),

			TestCase("ctor range", [this]
					 {
						 UnorderedMapType<Key, T> testee(ARRAY.begin(), ARRAY.end());
						 TestCase::assert(testee.size() == ARRAY.size());
					 }),

			TestCase("ctor initializer list", [this]
					 {
						 UnorderedMapType<Key, T> testee(INITIALIZER_LIST);
						 TestCase::assert(testee.size() == INITIALIZER_LIST.size());
					 }),

			TestCase("operator= copy", [this]
					 {
						 const UnorderedMapType<Key, T> other(INITIALIZER_LIST);
						 UnorderedMapType<Key, T> testee;
						 auto& result = (testee = other);
						 TestCase::assert(std::is_same<UnorderedMapType<Key, T>&, decltype(result)>::value, "type");
						 TestCase::assert(testee.size() == INITIALIZER_LIST.size(), "result");
					 }),

			TestCase("operator= move", [this]
					 {
						 UnorderedMapType<Key, T> other(INITIALIZER_LIST);
						 UnorderedMapType<Key, T> testee;
						 auto& result = (testee = std::move(other));
						 TestCase::assert(std::is_same<UnorderedMapType<Key, T>&, decltype(result)>::value, "type");
						 TestCase::assert(other.size() == 0, "other");
						 TestCase::assert(testee.size() == INITIALIZER_LIST.size(), "testee");
					 }),

			TestCase("operator= initializer list", [this]
					 {
						 UnorderedMapType<Key, T> testee;
						 auto& result = (testee = INITIALIZER_LIST);
						 TestCase::assert(std::is_same<UnorderedMapType<Key, T>&, decltype(result)>::value, "type");
						 TestCase::assert(testee.size() == INITIALIZER_LIST.size(), "result");
					 }),

			TestCase("begin", [this]
					 {
						 UnorderedMapType<Key, T> testee(INITIALIZER_LIST);
						 auto i = testee.begin();
						 TestCase::assert(std::is_same<typename UnorderedMapType<Key, T>::iterator, decltype(i)>::value, "type");
						 TestCase::assert(*i == typename UnorderedMapType<Key, T>::value_type(), "result");
					 }),

			TestCase("begin const", [this]
					 {
						 const UnorderedMapType<Key, T> testee(INITIALIZER_LIST);
						 auto i = testee.begin();
						 TestCase::assert(std::is_same<typename UnorderedMapType<Key, T>::const_iterator, decltype(i)>::value, "type");
						 TestCase::assert(*i == typename UnorderedMapType<Key, T>::value_type(), "result");
					 }),

			TestCase("end", [this]
					 {
						 UnorderedMapType<Key, T> testee(INITIALIZER_LIST);
						 auto i = testee.end();
						 TestCase::assert(std::is_same<typename UnorderedMapType<Key, T>::iterator, decltype(i)>::value);
					 }),

			TestCase("end const", [this]
					 {
						 const UnorderedMapType<Key, T> testee(INITIALIZER_LIST);
						 auto i = testee.end();
						 TestCase::assert(std::is_same<typename UnorderedMapType<Key, T>::const_iterator, decltype(i)>::value);
					 }),

			TestCase("cbegin", [this]
					 {
						 UnorderedMapType<Key, T> testee(INITIALIZER_LIST);
						 auto i = testee.cbegin();
						 TestCase::assert(std::is_same<typename UnorderedMapType<Key, T>::const_iterator, decltype(i)>::value, "type");
						 TestCase::assert(*i == typename UnorderedMapType<Key, T>::value_type(), "result");
					 }),

			TestCase("cend", [this]
					 {
						 UnorderedMapType<Key, T> testee(INITIALIZER_LIST);
						 auto i = testee.cend();
						 TestCase::assert(std::is_same<typename UnorderedMapType<Key, T>::const_iterator, decltype(i)>::value);
					 }),

			TestCase("empty", [this]
					 {
						 const UnorderedMapType<Key, T> testee;
						 auto result = testee.empty();
						 TestCase::assert(std::is_same<bool, decltype(result)>::value, "bool");
						 TestCase::assert(result == true, "result");
					 }),

			TestCase("size", [this]
					 {
						 const UnorderedMapType<Key, T> testee(INITIALIZER_LIST);
						 auto result = testee.size();
						 TestCase::assert(std::is_same<typename UnorderedMapType<Key, T>::size_type, decltype(result)>::value, "type");
						 TestCase::assert(result == INITIALIZER_LIST.size(), "result");
					 }),

			TestCase("max_size", [this]
					 {
						 const UnorderedMapType<Key, T> testee(INITIALIZER_LIST);
						 auto result = testee.max_size();
						 TestCase::assert(std::is_same<typename UnorderedMapType<Key, T>::size_type, decltype(result)>::value, "type");
						 TestCase::assert(result >= INITIALIZER_LIST.size(), "result");
					 }),


			TestCase("operator[]", TestSubscriptOperator<UnorderedMapType, Key, T, isMultimap>()),

			TestCase("operator[] move", TestSubscriptOperatorMove<UnorderedMapType, Key, T, isMultimap>()),

			TestCase("at", TestAt<UnorderedMapType, Key, T, isMultimap>()),

			TestCase("at const", TestAtConst<UnorderedMapType, Key, T, isMultimap>()),

			TestCase("insert single element", [this]
					 {
						 UnorderedMapType<Key, T> testee;
						 auto position = testee.begin();
						 auto value = std::make_pair(Key(), T());
						 auto result = testee.insert(value);
						 if (!isMultimap) {
							 TestCase::assert(std::is_same<std::pair<typename UnorderedMapType<Key, T>::iterator, bool>, decltype(result)>::value, "type");
						 } else {
							 TestCase::assert(std::is_same<typename UnorderedMapType<Key, T>::iterator, decltype(result)>::value, "type");
						 }
						 TestCase::assert(testee.size() == 1, "result");
					 }),

			TestCase("insert move", [this]
					 {
						 UnorderedMapType<Key, T> testee;
						 auto position = testee.begin();
						 auto value = std::make_pair(Key(), T());
						 auto result = testee.insert(std::move(value));
						 if (!isMultimap) {
							 TestCase::assert(std::is_same<std::pair<typename UnorderedMapType<Key, T>::iterator, bool>, decltype(result)>::value, "type");
						 } else {
							 TestCase::assert(std::is_same<typename UnorderedMapType<Key, T>::iterator, decltype(result)>::value, "type");
						 }
						 TestCase::assert(testee.size() == 1, "result");
					 }),

			TestCase("insert hint single element", [this]
					 {
						 UnorderedMapType<Key, T> testee;
						 auto position = testee.begin();
						 auto value = std::make_pair(Key(), T());
						 auto result = testee.insert(position, value);
						 TestCase::assert(std::is_same<typename UnorderedMapType<Key, T>::iterator, decltype(result)>::value, "type");
						 TestCase::assert(testee.size() == 1, "result");
					 }),

			TestCase("insert hint move", [this]
					 {
						 UnorderedMapType<Key, T> testee;
						 auto position = testee.begin();
						 auto value = std::make_pair(Key(), T());
						 auto result = testee.insert(position, std::move(value));
						 TestCase::assert(std::is_same<typename UnorderedMapType<Key, T>::iterator, decltype(result)>::value, "type");
						 TestCase::assert(testee.size() == 1, "result");
					 }),

			TestCase("insert range", [this]
					 {
						 UnorderedMapType<Key, T> testee;
						 testee.insert(ARRAY.begin(), ARRAY.end());
						 TestCase::assert(testee.size() == ARRAY.size());
					 }),

			TestCase("insert initializer list", [this]
					 {
						 UnorderedMapType<Key, T> testee;
						 testee.insert(INITIALIZER_LIST);
						 TestCase::assert(testee.size() == INITIALIZER_LIST.size());
					 }),

			TestCase("erase single element", [this]
					 {
						 UnorderedMapType<Key, T> testee(INITIALIZER_LIST);
						 auto position = testee.begin();
						 auto result = testee.erase(position);
						 TestCase::assert(std::is_same<typename UnorderedMapType<Key, T>::iterator, decltype(result)>::value, "type");
						 TestCase::assert(testee.size() == 0, "result");
					 }),

			TestCase("erase key", [this]
					 {
						 UnorderedMapType<Key, T> testee(INITIALIZER_LIST);
						 auto result = testee.erase(Key());
						 TestCase::assert(std::is_same<typename UnorderedMapType<Key, T>::size_type, decltype(result)>::value, "type");
						 TestCase::assert(testee.size() == 0, "result");
					 }),

			TestCase("erase range", [this]
					 {
						 UnorderedMapType<Key, T> testee(INITIALIZER_LIST);
						 auto first = testee.begin();
						 auto last = testee.end();;
						 auto result = testee.erase(first, last);
						 TestCase::assert(std::is_same<typename UnorderedMapType<Key, T>::iterator, decltype(result)>::value, "type");
						 TestCase::assert(testee.size() == 0, "result");
					 }),

			TestCase("swap", [this]
					 {
						 UnorderedMapType<Key, T> other(INITIALIZER_LIST);
						 UnorderedMapType<Key, T> testee(INITIALIZER_LIST);
						 testee.swap(other);
						 TestCase::assert(other.size() == INITIALIZER_LIST.size(), "other");
						 TestCase::assert(testee.size() == INITIALIZER_LIST.size(), "testee");
					 }),

			TestCase("clear", [this]
					 {
						 UnorderedMapType<Key, T> testee(INITIALIZER_LIST);
						 testee.clear();
						 TestCase::assert(testee.size() == 0);
					 }),

			TestCase("emplace", [this]
					 {
						 UnorderedMapType<Key, T> testee;
						 auto result = testee.emplace();
						 if (!isMultimap) {
							 TestCase::assert(std::is_same<std::pair<typename UnorderedMapType<Key, T>::iterator, bool>, decltype(result)>::value, "type");
						 } else {
							 TestCase::assert(std::is_same<typename UnorderedMapType<Key, T>::iterator, decltype(result)>::value, "type");
						 }
						 TestCase::assert(testee.size() == 1, "result");
					 }),

			TestCase("emplace_hint", [this]
					 {
						 UnorderedMapType<Key, T> testee;
						 auto position = testee.begin();
						 auto result = testee.emplace_hint(position);
						 TestCase::assert(std::is_same<typename UnorderedMapType<Key, T>::iterator, decltype(result)>::value, "type");
						 TestCase::assert(testee.size() == 1, "result");
					 }),

			TestCase("find", [this]
					 {
						 UnorderedMapType<Key, T> testee(INITIALIZER_LIST);
						 auto result = testee.find(Key());
						 TestCase::assert(std::is_same<typename UnorderedMapType<Key, T>::iterator, decltype(result)>::value, "type");
						 TestCase::assert(*result == typename UnorderedMapType<Key, T>::value_type(), "result");
					 }),

			TestCase("find const", [this]
					 {
						 const UnorderedMapType<Key, T> testee(INITIALIZER_LIST);
						 auto result = testee.find(Key());
						 TestCase::assert(std::is_same<typename UnorderedMapType<Key, T>::const_iterator, decltype(result)>::value, "type");
						 TestCase::assert(*result == typename UnorderedMapType<Key, T>::value_type(), "result");
					 }),

			TestCase("count", [this]
					 {
						 const UnorderedMapType<Key, T> testee(INITIALIZER_LIST);
						 auto result = testee.count(Key());
						 TestCase::assert(std::is_same<typename UnorderedMapType<Key, T>::size_type, decltype(result)>::value, "type");
						 TestCase::assert(result == 1, "result");
					 }),

			TestCase("equal_range", [this]
					 {
						 UnorderedMapType<Key, T> testee(INITIALIZER_LIST);
						 auto result = testee.equal_range(Key());
						 TestCase::assert(std::is_same<std::pair<typename UnorderedMapType<Key, T>::iterator, typename UnorderedMapType<Key, T>::iterator>, decltype(result)>::value);
					 }),

			TestCase("equal_range const", [this]
					 {
						 const UnorderedMapType<Key, T> testee(INITIALIZER_LIST);
						 auto result = testee.equal_range(Key());
						 TestCase::assert(std::is_same<std::pair<typename UnorderedMapType<Key, T>::const_iterator, typename UnorderedMapType<Key, T>::const_iterator>, decltype(result)>::value);
					 }),

			TestCase("bucket_count", [this]
					 {
						 const UnorderedMapType<Key, T> testee(INITIALIZER_LIST);
						 auto result = testee.bucket_count();
						 TestCase::assert(std::is_same<typename UnorderedMapType<Key, T>::size_type, decltype(result)>::value, "type");
						 TestCase::assert(result >= 1, "result");
					 }),

			TestCase("max_bucket_count", [this]
					 {
						 const UnorderedMapType<Key, T> testee(INITIALIZER_LIST);
						 auto result = testee.max_bucket_count();
						 TestCase::assert(std::is_same<typename UnorderedMapType<Key, T>::size_type, decltype(result)>::value, "type");
						 TestCase::assert(result >= 1, "result");
					 }),

			TestCase("bucket_size", [this]
					 {
						 const UnorderedMapType<Key, T> testee(INITIALIZER_LIST);
						 auto result = testee.bucket_size(0);
						 TestCase::assert(std::is_same<typename UnorderedMapType<Key, T>::size_type, decltype(result)>::value, "type");
						 TestCase::assert(result >= 0, "result");
					 }),

			TestCase("bucket", [this]
					 {
						 const UnorderedMapType<Key, T> testee(INITIALIZER_LIST);
						 auto result = testee.bucket(Key());
						 TestCase::assert(std::is_same<typename UnorderedMapType<Key, T>::size_type, decltype(result)>::value, "type");
						 TestCase::assert(result >= 0, "result");
					 }),

			TestCase("load_factor", [this]
					 {
						 const UnorderedMapType<Key, T> testee(INITIALIZER_LIST);
						 auto result = testee.load_factor();
						 TestCase::assert(std::is_same<float, decltype(result)>::value, "type");
						 TestCase::assert(result >= 0.0F, "result");
					 }),

			TestCase("max_load_factor get", [this]
					 {
						 const UnorderedMapType<Key, T> testee(INITIALIZER_LIST);
						 auto result = testee.max_load_factor();
						 TestCase::assert(std::is_same<float, decltype(result)>::value, "type");
						 TestCase::assert(result >= 0.0F, "result");
					 }),

			TestCase("max_load_factor set", [this]
					 {
						 UnorderedMapType<Key, T> testee(INITIALIZER_LIST);
						 auto oldLoadFactor = testee.max_load_factor();
						 testee.max_load_factor(oldLoadFactor + 1.0F);
						 auto newLoadFactor = testee.max_load_factor();
						 TestCase::assert(newLoadFactor >= oldLoadFactor);
					 }),

			TestCase("rehash", [this]
					 {
						 UnorderedMapType<Key, T> testee(INITIALIZER_LIST);
						 auto oldCount = testee.bucket_count();
						 testee.rehash(oldCount + 1);
						 auto newCount = testee.bucket_count();
						 TestCase::assert(newCount > oldCount);
					 }),

			TestCase("reserve", [this]
					 {
						 UnorderedMapType<Key, T> testee(INITIALIZER_LIST);
						 auto oldCount = testee.bucket_count();
						 testee.reserve(oldCount + 1);
						 auto newCount = testee.bucket_count();
						 TestCase::assert(newCount > oldCount);
					 }),

			TestCase("hash_function", [this]
					 {
						 const UnorderedMapType<Key, T> testee;
						 auto result = testee.hash_function();
						 TestCase::assert(std::is_same<typename UnorderedMapType<Key, T>::hasher, decltype(result)>::value);
					 }),

			TestCase("key_eq", [this]
					 {
						 const UnorderedMapType<Key, T> testee;
						 auto result = testee.key_eq();
						 TestCase::assert(std::is_same<typename UnorderedMapType<Key, T>::key_equal, decltype(result)>::value);
					 }),

			TestCase("get_allocator", [this]
					 {
						 UnorderedMapType<Key, T> testee;
						 auto result = testee.get_allocator();
						 TestCase::assert(std::is_same<typename UnorderedMapType<Key, T>::allocator_type, decltype(result)>::value);
					 }),

			TestCase("operator==", [this]
					 {
						 UnorderedMapType<Key, T> lhs(INITIALIZER_LIST);
						 UnorderedMapType<Key, T> rhs(INITIALIZER_LIST);
						 auto result = (lhs == rhs);
						 TestCase::assert(std::is_same<bool, decltype(result)>::value, "type");
						 TestCase::assert(result == true, "result");
					 }),

			TestCase("operator!=", [this]
					 {
						 UnorderedMapType<Key, T> lhs;
						 UnorderedMapType<Key, T> rhs(INITIALIZER_LIST);
						 auto result = (lhs != rhs);
						 TestCase::assert(std::is_same<bool, decltype(result)>::value, "type");
						 TestCase::assert(result == true, "result");
					 }),

			TestCase("swap lhs rhs", [this]
					 {
						 UnorderedMapType<Key, T> lhs(INITIALIZER_LIST);
						 UnorderedMapType<Key, T> rhs;
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

template<template<typename...> class UnorderedMapType, typename Key, typename T, bool isMultimap>
constexpr typename StdUnorderedMapTestSuite<UnorderedMapType, Key, T, isMultimap>::InitializerListType StdUnorderedMapTestSuite<UnorderedMapType, Key, T, isMultimap>::INITIALIZER_LIST;

template<template<typename...> class UnorderedMapType, typename Key, typename T, bool isMultimap>
constexpr typename StdUnorderedMapTestSuite<UnorderedMapType, Key, T, isMultimap>::ArrayType StdUnorderedMapTestSuite<UnorderedMapType, Key, T, isMultimap>::ARRAY;


// Conditionally enabled test executors handling map vs multimap.

template<template<typename...> class UnorderedMapType, typename Key, typename T, bool isMultimap>
class TestSubscriptOperator<UnorderedMapType, Key, T, isMultimap, typename std::enable_if<!isMultimap>::type>
{
public:
	void operator()()
	{
		UnorderedMapType<Key, T> testee({std::make_pair(Key(), T())});
		auto& result = testee[Key()];
		TestCase::assert(std::is_same<typename UnorderedMapType<Key, T>::mapped_type&, decltype(result)>::value, "type");
		TestCase::assert(result == T(), "result");
	}
};

template<template<typename...> class UnorderedMapType, typename Key, typename T, bool isMultimap>
class TestSubscriptOperator<UnorderedMapType, Key, T, isMultimap, typename std::enable_if<isMultimap>::type>
{
public:
	void operator()()
	{
	}
};

template<template<typename...> class UnorderedMapType, typename Key, typename T, bool isMultimap>
class TestSubscriptOperatorMove<UnorderedMapType, Key, T, isMultimap, typename std::enable_if<!isMultimap>::type>
{
public:
	void operator()() const
	{
		UnorderedMapType<Key, T> testee({std::make_pair(Key(), T())});
		auto& result = testee[std::move(Key())];
		TestCase::assert(std::is_same<typename UnorderedMapType<Key, T>::mapped_type&, decltype(result)>::value, "type");
		TestCase::assert(result == T(), "result");
	}
};

template<template<typename...> class UnorderedMapType, typename Key, typename T, bool isMultimap>
class TestSubscriptOperatorMove<UnorderedMapType, Key, T, isMultimap, typename std::enable_if<isMultimap>::type>
{
public:
	void operator()()
	{
	}
};

template<template<typename...> class UnorderedMapType, typename Key, typename T, bool isMultimap>
class TestAt<UnorderedMapType, Key, T, isMultimap, typename std::enable_if<!isMultimap>::type>
{
public:
	void operator()()
	{
		UnorderedMapType<Key, T> testee({std::make_pair(Key(), T())});
		auto& result = testee.at(Key());
		TestCase::assert(std::is_same<typename UnorderedMapType<Key, T>::mapped_type&, decltype(result)>::value, "type");
		TestCase::assert(result == T(), "result");
	}
};

template<template<typename...> class UnorderedMapType, typename Key, typename T, bool isMultimap>
class TestAt<UnorderedMapType, Key, T, isMultimap, typename std::enable_if<isMultimap>::type>
{
public:
	void operator()()
	{
	}
};

template<template<typename...> class UnorderedMapType, typename Key, typename T, bool isMultimap>
class TestAtConst<UnorderedMapType, Key, T, isMultimap, typename std::enable_if<!isMultimap>::type>
{
public:
	void operator()()
	{
		const UnorderedMapType<Key, T> testee({std::make_pair(Key(), T())});
		auto& result = testee.at(Key());
		TestCase::assert(std::is_same<const typename UnorderedMapType<Key, T>::mapped_type&, decltype(result)>::value, "type");
		TestCase::assert(result == T(), "result");
	}
};

template<template<typename...> class UnorderedMapType, typename Key, typename T, bool isMultimap>
class TestAtConst<UnorderedMapType, Key, T, isMultimap, typename std::enable_if<isMultimap>::type>
{
public:
	void operator()()
	{
	}
};


#endif // StdUnorderedMapTestSuite_INCLUDED
