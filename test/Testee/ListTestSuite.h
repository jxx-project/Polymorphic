//
// Copyright (C) 2018 Dr. Michael Steffens
//
// SPDX-License-Identifier:		BSL-1.0
//


#ifndef Testee_ListTestSuite_INCLUDED
#define Testee_ListTestSuite_INCLUDED

#include "Testee/TestSuite.h"

namespace Testee {

/// Test ListType C++-11 standard list interface.
template<template<typename...> class ListType, typename T>
class ListTestSuite : public TestSuite
{
public:
	typedef std::initializer_list<T> InitializerListType;
	typedef std::array<T, 1> ArrayType;

	ListTestSuite() : TestSuite({

			TestCase("typedefs", [this]
					 {
						 TestCase::assert(std::is_same<typename ListType<T>::value_type, T>::value, "value_type");
						 TestCase::assert(std::is_class<typename ListType<T>::allocator_type>::value, "allocator_type");
						 TestCase::assert(std::is_same<typename ListType<T>::reference, T&>::value, "reference");
						 TestCase::assert(std::is_same<typename ListType<T>::const_reference, const T&>::value, "const_reference");
					 }),

			TestCase("ctor default", [this]
					 {
						 ListType<T> testee;
						 TestCase::assert(testee.size() == 0);
					 }),

			TestCase("ctor fill", [this]
					 {
						 ListType<T> testee(3);
						 TestCase::assert(testee.size() == 3);
					 }),

			TestCase("ctor fill value", [this]
					 {
						 ListType<T> testee(3, T(), std::allocator<T>());
						 TestCase::assert(testee.size() == 3);
					 }),

			TestCase("ctor copy", [this]
					 {
						 const ListType<T> other(3);
						 ListType<T> testee(other);
						 TestCase::assert(testee.size() == 3);
					 }),

			// TestCase("ctor copy with allocator", [this]
			//		 {
			//			 const ListType<T> other(3);
			//			 ListType<T> testee(other, std::allocator<T>());
			//			 TestCase::assert(testee.size() == 3);
			//		 }),

			TestCase("ctor move", [this]
					 {
						 ListType<T> other(3);
						 ListType<T> testee(std::move(other));
						 TestCase::assert(other.size() == 0, "other");
						 TestCase::assert(testee.size() == 3, "testee");
					 }),

			// TestCase("ctor move with allocator", [this]
			//		 {
			//			 ListType<T> other(3);
			//			 ListType<T> testee(std::move(other), std::allocator<T>());
			//			 TestCase::assert(other.size() == 0, "other");
			//			 TestCase::assert(testee.size() == 3, "testee");
			//		 }),

			TestCase("ctor range", [this]
					 {
						 ListType<T> testee(ARRAY.begin(), ARRAY.end());
						 TestCase::assert(testee.size() == ARRAY.size());
					 }),

			TestCase("ctor initializer list", [this]
					 {
						 ListType<T> testee(INITIALIZER_LIST);
						 TestCase::assert(testee.size() == INITIALIZER_LIST.size());
					 }),

			TestCase("operator= copy", [this]
					 {
						 const ListType<T> other(3);
						 ListType<T> testee;
						 auto& result = (testee = other);
						 TestCase::assert(std::is_same<ListType<T>&, decltype(result)>::value, "type");
						 TestCase::assert(testee.size() == 3, "result");
					 }),

			TestCase("operator= move", [this]
					 {
						 ListType<T> other(3);
						 ListType<T> testee;
						 auto& result = (testee = std::move(other));
						 TestCase::assert(std::is_same<ListType<T>&, decltype(result)>::value, "type");
						 TestCase::assert(other.size() == 0, "other");
						 TestCase::assert(testee.size() == 3, "testee");
					 }),

			TestCase("operator= initializer list", [this]
					 {
						 ListType<T> testee;
						 auto& result = (testee = INITIALIZER_LIST);
						 TestCase::assert(std::is_same<ListType<T>&, decltype(result)>::value, "type");
						 TestCase::assert(testee.size() == INITIALIZER_LIST.size(), "result");
					 }),

			TestCase("begin", [this]
					 {
						 ListType<T> testee(1);
						 auto result = testee.begin();
						 TestCase::assert(std::is_same<typename ListType<T>::iterator, decltype(result)>::value, "type");
						 TestCase::assert(*result == T(), "result");
					 }),

			TestCase("begin const", [this]
					 {
						 const ListType<T> testee(1);
						 auto result = testee.begin();
						 TestCase::assert(std::is_same<typename ListType<T>::const_iterator, decltype(result)>::value, "type");
						 TestCase::assert(*result == T(), "result");
					 }),

			TestCase("end", [this]
					 {
						 ListType<T> testee(1);
						 auto result = testee.end();
						 TestCase::assert(std::is_same<typename ListType<T>::iterator, decltype(result)>::value, "type");
						 TestCase::assert(*(--result) == T(), "result");
					 }),

			TestCase("end const", [this]
					 {
						 const ListType<T> testee(1);
						 auto result = testee.end();
						 TestCase::assert(std::is_same<typename ListType<T>::const_iterator, decltype(result)>::value, "type");
						 TestCase::assert(*(--result) == T(), "result");
					 }),

			TestCase("rbegin", [this]
					 {
						 ListType<T> testee(1);
						 auto result = testee.rbegin();
						 TestCase::assert(std::is_same<typename ListType<T>::reverse_iterator, decltype(result)>::value, "type");
						 TestCase::assert(*result == T(), "result");
					 }),

			TestCase("rbegin const", [this]
					 {
						 const ListType<T> testee(1);
						 auto result = testee.rbegin();
						 TestCase::assert(std::is_same<typename ListType<T>::const_reverse_iterator, decltype(result)>::value, "type");
						 TestCase::assert(*result == T(), "result");
					 }),

			TestCase("rend", [this]
					 {
						 ListType<T> testee(1);
						 auto result = testee.rend();
						 TestCase::assert(std::is_same<typename ListType<T>::reverse_iterator, decltype(result)>::value, "type");
						 TestCase::assert(*(--result) == T(), "result");
					 }),

			TestCase("rend const", [this]
					 {
						 const ListType<T> testee(1);
						 auto result = testee.rend();
						 TestCase::assert(std::is_same<typename ListType<T>::const_reverse_iterator, decltype(result)>::value, "type");
						 TestCase::assert(*(--result) == T(), "result");
					 }),

			TestCase("cbegin", [this]
					 {
						 ListType<T> testee(1);
						 auto result = testee.cbegin();
						 TestCase::assert(std::is_same<typename ListType<T>::const_iterator, decltype(result)>::value, "type");
						 TestCase::assert(*result == T(), "result");
					 }),

			TestCase("cend", [this]
					 {
						 ListType<T> testee(1);
						 auto result = testee.cend();
						 TestCase::assert(std::is_same<typename ListType<T>::const_iterator, decltype(result)>::value, "type");
						 TestCase::assert(*(--result) == T(), "result");
					 }),

			TestCase("crbegin", [this]
					 {
						 ListType<T> testee(1);
						 auto result = testee.crbegin();
						 TestCase::assert(std::is_same<typename ListType<T>::const_reverse_iterator, decltype(result)>::value, "type");
						 TestCase::assert(*result == T(), "result");
					 }),

			TestCase("crend", [this]
					 {
						 ListType<T> testee(1);
						 auto result = testee.crend();
						 TestCase::assert(std::is_same<typename ListType<T>::const_reverse_iterator, decltype(result)>::value, "type");
						 TestCase::assert(*(--result) == T(), "result");
					 }),

			TestCase("empty", [this]
					 {
						 const ListType<T> testee;
						 auto result = testee.empty();
						 TestCase::assert(std::is_same<bool, decltype(result)>::value, "bool");
						 TestCase::assert(result == true, "result");
					 }),

			TestCase("size", [this]
					 {
						 const ListType<T> testee(3);
						 auto result = testee.size();
						 TestCase::assert(std::is_same<typename ListType<T>::size_type, decltype(result)>::value, "type");
						 TestCase::assert(result == 3, "result");
					 }),

			TestCase("max_size", [this]
					 {
						 const ListType<T> testee(3);
						 auto result = testee.max_size();
						 TestCase::assert(std::is_same<typename ListType<T>::size_type, decltype(result)>::value, "type");
						 TestCase::assert(result >= 3, "result");
					 }),

			TestCase("front", [this]
					 {
						 ListType<T> testee(1);
						 auto& result = testee.front();
						 TestCase::assert(std::is_same<typename ListType<T>::reference, decltype(result)>::value, "type");
						 TestCase::assert(result == T(), "result");
					 }),

			TestCase("front const", [this]
					 {
						 const ListType<T> testee(1);
						 auto& result = testee.front();
						 TestCase::assert(std::is_same<typename ListType<T>::const_reference, decltype(result)>::value, "type");
						 TestCase::assert(result == T(), "result");
					 }),

			TestCase("back", [this]
					 {
						 ListType<T> testee(1);
						 auto& result = testee.back();
						 TestCase::assert(std::is_same<typename ListType<T>::reference, decltype(result)>::value, "type");
						 TestCase::assert(result == T(), "result");
					 }),

			TestCase("back const", [this]
					 {
						 const ListType<T> testee(1);
						 auto& result = testee.back();
						 TestCase::assert(std::is_same<typename ListType<T>::const_reference, decltype(result)>::value, "type");
						 TestCase::assert(result == T(), "result");
					 }),

			TestCase("assign range", [this]
					 {
						 ListType<T> testee;
						 testee.assign(ARRAY.begin(), ARRAY.end());
						 TestCase::assert(testee.size() == ARRAY.size());
					 }),

			TestCase("assign fill value", [this]
					 {
						 ListType<T> testee;
						 testee.assign(3, T());
						 TestCase::assert(testee.size() == 3);
					 }),

			TestCase("assign initializer list", [this]
					 {
						 ListType<T> testee;
						 testee.assign(INITIALIZER_LIST);
						 TestCase::assert(testee.size() == INITIALIZER_LIST.size());
					 }),

			TestCase("emplace_front", [this]
					 {
						 ListType<T> testee(1);
						 testee.emplace_front();
						 TestCase::assert(testee.size() == 2);
					 }),

			TestCase("push_front copy", [this]
					 {
						 ListType<T> testee;
						 T value;
						 testee.push_front(value);
						 TestCase::assert(testee.size() == 1);
					 }),

			TestCase("push_front move", [this]
					 {
						 ListType<T> testee;
						 T value;
						 testee.push_front(std::move(value));
						 TestCase::assert(testee.size() == 1);
					 }),

			TestCase("pop_front", [this]
					 {
						 ListType<T> testee(2);
						 testee.pop_front();
						 TestCase::assert(testee.size() == 1);
					 }),

			TestCase("emplace_back", [this]
					 {
						 ListType<T> testee(1);
						 testee.emplace_back();
						 TestCase::assert(testee.size() == 2);
					 }),

			TestCase("push_back copy", [this]
					 {
						 ListType<T> testee;
						 T value;
						 testee.push_back(value);
						 TestCase::assert(testee.size() == 1);
					 }),

			TestCase("push_back move", [this]
					 {
						 ListType<T> testee;
						 T value;
						 testee.push_back(std::move(value));
						 TestCase::assert(testee.size() == 1);
					 }),

			TestCase("pop_back", [this]
					 {
						 ListType<T> testee(2);
						 testee.pop_back();
						 TestCase::assert(testee.size() == 1);
					 }),

			TestCase("emplace", [this]
					 {
						 ListType<T> testee(1);
						 auto position = testee.begin();
						 auto result = testee.emplace(position);
						 TestCase::assert(std::is_same<typename ListType<T>::iterator, decltype(result)>::value, "type");
						 TestCase::assert(testee.size() == 2, "result");
					 }),

			TestCase("insert single element", [this]
					 {
						 ListType<T> testee(1);
						 auto position = testee.begin();
						 T value;
						 auto result = testee.insert(position, value);
						 TestCase::assert(std::is_same<typename ListType<T>::iterator, decltype(result)>::value, "type");
						 TestCase::assert(testee.size() == 2, "result");
					 }),

			TestCase("insert fill", [this]
					 {
						 ListType<T> testee(1);
						 auto position = testee.begin();
						 T value;
						 auto result = testee.insert(position, 2, value);
						 TestCase::assert(std::is_same<typename ListType<T>::iterator, decltype(result)>::value, "type");
						 TestCase::assert(testee.size() == 3, "result");
					 }),

			TestCase("insert range", [this]
					 {
						 ListType<T> testee(1);
						 auto position = testee.begin();
						 auto result = testee.insert(position, ARRAY.begin(), ARRAY.end());
						 TestCase::assert(std::is_same<typename ListType<T>::iterator, decltype(result)>::value, "type");
						 TestCase::assert(testee.size() == 1 + ARRAY.size(), "result");
					 }),

			TestCase("insert move", [this]
					 {
						 ListType<T> testee(1);
						 auto position = testee.begin();
						 T value;
						 auto result = testee.insert(position, std::move(value));
						 TestCase::assert(std::is_same<typename ListType<T>::iterator, decltype(result)>::value, "type");
						 TestCase::assert(testee.size() == 2, "result");
					 }),

			TestCase("insert initializer list", [this]
					 {
						 ListType<T> testee(1);
						 auto position = testee.begin();
						 auto result = testee.insert(position, INITIALIZER_LIST);
						 TestCase::assert(std::is_same<typename ListType<T>::iterator, decltype(result)>::value, "type");
						 TestCase::assert(testee.size() == 1 + INITIALIZER_LIST.size(), "result");
					 }),

			TestCase("erase single element", [this]
					 {
						 ListType<T> testee(3);
						 auto position = testee.begin();
						 auto result = testee.erase(position);
						 TestCase::assert(std::is_same<typename ListType<T>::iterator, decltype(result)>::value, "type");
						 TestCase::assert(testee.size() == 2, "result");
					 }),

			TestCase("erase range", [this]
					 {
						 ListType<T> testee(3);
						 auto first = testee.begin();
						 auto last = first;
						 ++last;
						 ++last;
						 auto result = testee.erase(first, last);
						 TestCase::assert(std::is_same<typename ListType<T>::iterator, decltype(result)>::value, "type");
						 TestCase::assert(testee.size() == 1, "result");
					 }),

			TestCase("swap", [this]
					 {
						 ListType<T> other(3);
						 ListType<T> testee(1);
						 testee.swap(other);
						 TestCase::assert(other.size() == 1, "other");
						 TestCase::assert(testee.size() == 3, "testee");
					 }),

			TestCase("resize", [this]
					 {
						 ListType<T> testee(1);
						 testee.resize(3);
						 TestCase::assert(testee.size() == 3);
					 }),

			TestCase("resize value", [this]
					 {
						 ListType<T> testee(1);
						 testee.resize(3, T());
						 TestCase::assert(testee.size() == 3);
					 }),

			TestCase("clear", [this]
					 {
						 ListType<T> testee(1);
						 testee.clear();
						 TestCase::assert(testee.size() == 0);
					 }),

			TestCase("splice entire list", [this]
					 {
						 ListType<T> other(3);
						 ListType<T> testee(1);
						 auto position = testee.begin();
						 testee.splice(position, other);
						 TestCase::assert(other.size() == 0, "other");
						 TestCase::assert(testee.size() == 4, "testee");
					 }),

			TestCase("splice entire list move", [this]
					 {
						 ListType<T> other(3);
						 ListType<T> testee(1);
						 auto position = testee.begin();
						 testee.splice(position, std::move(other));
						 TestCase::assert(other.size() == 0, "other");
						 TestCase::assert(testee.size() == 4, "testee");
					 }),

			TestCase("splice single element", [this]
					 {
						 ListType<T> other(3);
						 auto i = other.begin();
						 ListType<T> testee(1);
						 auto position = testee.begin();
						 testee.splice(position, other, i);
						 TestCase::assert(other.size() == 2, "other");
						 TestCase::assert(testee.size() == 2, "testee");
					 }),

			TestCase("splice single element move", [this]
					 {
						 ListType<T> other(3);
						 auto i = other.begin();
						 ListType<T> testee(1);
						 auto position = testee.begin();
						 testee.splice(position, std::move(other), i);
						 TestCase::assert(other.size() == 2, "other");
						 TestCase::assert(testee.size() == 2, "testee");
					 }),

			TestCase("splice range move", [this]
					 {
						 ListType<T> other(3);
						 auto first = other.begin();
						 auto last = first;
						 ++last;
						 ++last;
						 ListType<T> testee(1);
						 auto position = testee.begin();
						 testee.splice(position, std::move(other), first, last);
						 TestCase::assert(other.size() == 1, "other");
						 TestCase::assert(testee.size() == 3, "testee");
					 }),

			TestCase("splice range", [this]
					 {
						 ListType<T> other(3);
						 auto first = other.begin();
						 auto last = first;
						 ++last;
						 ++last;
						 ListType<T> testee(1);
						 auto position = testee.begin();
						 testee.splice(position, other, first, last);
						 TestCase::assert(other.size() == 1, "other");
						 TestCase::assert(testee.size() == 3, "testee");
					 }),

			TestCase("remove", [this]
					 {
						 ListType<T> testee(1);
						 testee.remove(T());
						 TestCase::assert(testee.size() == 0);
					 }),

			TestCase("remove_if", [this]
					 {
						 ListType<T> testee(1);
						 testee.remove_if([](const T&)->bool{return true;});
						 TestCase::assert(testee.size() == 0);
					 }),

			TestCase("unique", [this]
					 {
						 ListType<T> testee(3);
						 testee.unique();
						 TestCase::assert(testee.size() == 1);
					 }),

			TestCase("unique with predicate", [this]
					 {
						 ListType<T> testee(3);
						 testee.unique([](const T&, const T&)->bool{return true;});
						 TestCase::assert(testee.size() == 1);
					 }),

			TestCase("merge", [this]
					 {
						 ListType<T> other(2);
						 ListType<T> testee(1);
						 testee.merge(other);
						 TestCase::assert(testee.size() == 3);
					 }),

			TestCase("merge move", [this]
					 {
						 ListType<T> other(2);
						 ListType<T> testee(1);
						 testee.merge(std::move(other));
						 TestCase::assert(testee.size() == 3);
					 }),

			TestCase("merge with predicate", [this]
					 {
						 ListType<T> other(2);
						 ListType<T> testee(1);
						 testee.merge(other, [](const T&, const T&)->bool{return true;});
						 TestCase::assert(testee.size() == 3);
					 }),

			TestCase("merge with predicate move", [this]
					 {
						 ListType<T> other(2);
						 ListType<T> testee(1);
						 testee.merge(std::move(other), [](const T&, const T&)->bool{return true;});
						 TestCase::assert(testee.size() == 3);
					 }),

			TestCase("sort", [this]
					 {
						 ListType<T> testee(3);
						 testee.sort();
						 TestCase::assert(testee.size() == 3);
					 }),

			TestCase("sort with predicate", [this]
					 {
						 ListType<T> testee(3);
						 testee.sort([](const T&, const T&)->bool{return true;});
						 TestCase::assert(testee.size() == 3);
					 }),

			TestCase("reverse", [this]
					 {
						 ListType<T> testee(3);
						 testee.reverse();
						 TestCase::assert(testee.size() == 3);
					 }),

			TestCase("get_allocator", [this]
					 {
						 ListType<T> testee;
						 auto result = testee.get_allocator();
						 TestCase::assert(std::is_same<typename ListType<T>::allocator_type, decltype(result)>::value);
					 }),

			TestCase("operator==", [this]
					 {
						 ListType<T> lhs(3);
						 ListType<T> rhs(3);
						 auto result = (lhs == rhs);
						 TestCase::assert(std::is_same<bool, decltype(result)>::value, "type");
						 TestCase::assert(result == true, "result");
					 }),

			TestCase("operator!=", [this]
					 {
						 ListType<T> lhs(2);
						 ListType<T> rhs(3);
						 auto result = (lhs != rhs);
						 TestCase::assert(std::is_same<bool, decltype(result)>::value, "type");
						 TestCase::assert(result == true, "result");
					 }),

			TestCase("operator<", [this]
					 {
						 ListType<T> lhs(2);
						 ListType<T> rhs(3);
						 auto result = (lhs < rhs);
						 TestCase::assert(std::is_same<bool, decltype(result)>::value, "type");
						 TestCase::assert(result == true, "result");
					 }),

			TestCase("operator<=", [this]
					 {
						 ListType<T> lhs(2);
						 ListType<T> rhs(3);
						 auto result = (lhs <= rhs);
						 TestCase::assert(std::is_same<bool, decltype(result)>::value, "type");
						 TestCase::assert(result == true, "result");
					 }),

			TestCase("operator>", [this]
					 {
						 ListType<T> lhs(3);
						 ListType<T> rhs(2);
						 auto result = (lhs > rhs);
						 TestCase::assert(std::is_same<bool, decltype(result)>::value, "type");
						 TestCase::assert(result == true, "result");
					 }),

			TestCase("operator>=", [this]
					 {
						 ListType<T> lhs(3);
						 ListType<T> rhs(2);
						 auto result = (lhs >= rhs);
						 TestCase::assert(std::is_same<bool, decltype(result)>::value, "type");
						 TestCase::assert(result == true, "result");
					 }),

			TestCase("swap lhs rhs", [this]
					 {
						 ListType<T> lhs(3);
						 ListType<T> rhs(2);
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
constexpr typename ListTestSuite<ListType, T>::InitializerListType ListTestSuite<ListType, T>::INITIALIZER_LIST;

template<template<typename...> class ListType, typename T>
constexpr typename ListTestSuite<ListType, T>::ArrayType ListTestSuite<ListType, T>::ARRAY;

} // namespace Testee

#endif // Testee_ListTestSuite_INCLUDED
