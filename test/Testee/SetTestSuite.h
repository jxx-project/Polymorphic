//
// Copyright (C) 2018 Dr. Michael Steffens
//
// SPDX-License-Identifier:	BSL-1.0
//


#ifndef SetTestSuite_INCLUDED
#define SetTestSuite_INCLUDED

#include "Testee/TestSuite.h"
#include <array>

namespace Testee {

/// Test SetType C++11 standard set or multiset interface.
template<
	template<typename...> class SetType,
	typename T,
	bool isMultiset = false,
	typename Compare = std::less<T>,
	typename Allocator = std::allocator<T>>
class SetTestSuite : public TestSuite
{
public:
	typedef std::initializer_list<T> InitializerListType;
	typedef std::array<T, 1> ArrayType;
	typedef typename SetType<T, Compare, Allocator>::value_type ValueType;

	SetTestSuite(const std::string& setType) :
		TestSuite(
			setType + " C++11 standard interface",
			{

				TestCase(
					"typedefs",
					[] {
						TestCase::assert(std::is_same<typename SetType<T, Compare, Allocator>::key_type, T>::value, "key_type");
						TestCase::assert(std::is_same<typename SetType<T, Compare, Allocator>::value_type, T>::value, "value_type");
						TestCase::assert(
							std::is_class<typename SetType<T, Compare, Allocator>::allocator_type>::value, "allocator_type");
						TestCase::assert(std::is_same<typename SetType<T, Compare, Allocator>::reference, T&>::value, "reference");
						TestCase::assert(
							std::is_same<typename SetType<T, Compare, Allocator>::const_reference, const T&>::value,
							"const_reference");
					}),

				TestCase(
					"ctor default",
					[] {
						SetType<T, Compare, Allocator> testee;
						TestCase::assert(testee.size() == 0);
					}),

				// TestCase("ctor default with allocator", []
				//		 {
				//			 SetType<T, Compare, Allocator> testee(std::allocator<T>());
				//			 TestCase::assert(testee.size() == 0);
				//		 }),

				TestCase(
					"ctor copy",
					[] {
						const SetType<T, Compare, Allocator> other(INITIALIZER_LIST);
						SetType<T, Compare, Allocator> testee(other);
						TestCase::assert(testee.size() == INITIALIZER_LIST.size());
					}),

				// TestCase("ctor copy with allocator", []
				//		 {
				//			 const SetType<T, Compare, Allocator> other(INITIALIZER_LIST);
				//			 SetType<T, Compare, Allocator> testee(other, std::allocator<T>());
				//			 TestCase::assert(testee.size() == INITIALIZER_LIST.size());
				//		 }),

				TestCase(
					"ctor move",
					[] {
						SetType<T, Compare, Allocator> other(INITIALIZER_LIST);
						SetType<T, Compare, Allocator> testee(std::move(other));
						TestCase::assert(other.size() == 0, "other");
						TestCase::assert(testee.size() == INITIALIZER_LIST.size(), "testee");
					}),

				// TestCase("ctor move with allocator", []
				//		 {
				//			 SetType<T, Compare, Allocator> other(INITIALIZER_LIST);
				//			 SetType<T, Compare, Allocator> testee(std::move(other), std::allocator<T>());
				//			 TestCase::assert(other.size() == 0, "other");
				//			 TestCase::assert(testee.size() == INITIALIZER_LIST.size(), "testee");
				//		 }),

				TestCase(
					"ctor range",
					[] {
						SetType<T, Compare, Allocator> testee(ARRAY.begin(), ARRAY.end());
						TestCase::assert(testee.size() == ARRAY.size());
					}),

				TestCase(
					"ctor initializer list",
					[] {
						SetType<T, Compare, Allocator> testee(INITIALIZER_LIST);
						TestCase::assert(testee.size() == INITIALIZER_LIST.size());
					}),

				TestCase(
					"operator= copy",
					[] {
						const SetType<T, Compare, Allocator> other(INITIALIZER_LIST);
						SetType<T, Compare, Allocator> testee;
						auto& result = (testee = other);
						TestCase::assert(std::is_same<SetType<T, Compare, Allocator>&, decltype(result)>::value, "type");
						TestCase::assert(testee.size() == INITIALIZER_LIST.size(), "result");
					}),

				TestCase(
					"operator= move",
					[] {
						SetType<T, Compare, Allocator> other(INITIALIZER_LIST);
						SetType<T, Compare, Allocator> testee;
						auto& result = (testee = std::move(other));
						TestCase::assert(std::is_same<SetType<T, Compare, Allocator>&, decltype(result)>::value, "type");
						TestCase::assert(other.size() == 0, "other");
						TestCase::assert(testee.size() == INITIALIZER_LIST.size(), "testee");
					}),

				TestCase(
					"operator= initializer list",
					[] {
						SetType<T, Compare, Allocator> testee;
						auto& result = (testee = INITIALIZER_LIST);
						TestCase::assert(std::is_same<SetType<T, Compare, Allocator>&, decltype(result)>::value, "type");
						TestCase::assert(testee.size() == INITIALIZER_LIST.size(), "result");
					}),

				TestCase(
					"begin",
					[] {
						SetType<T, Compare, Allocator> testee(INITIALIZER_LIST);
						auto result = testee.begin();
						TestCase::assert(
							std::is_same<typename SetType<T, Compare, Allocator>::iterator, decltype(result)>::value, "type");
						TestCase::assert(*result == ValueType(), "result");
					}),

				TestCase(
					"begin const",
					[] {
						const SetType<T, Compare, Allocator> testee(INITIALIZER_LIST);
						auto result = testee.begin();
						TestCase::assert(
							std::is_same<typename SetType<T, Compare, Allocator>::const_iterator, decltype(result)>::value, "type");
						TestCase::assert(*result == ValueType(), "result");
					}),

				TestCase(
					"end",
					[] {
						SetType<T, Compare, Allocator> testee(INITIALIZER_LIST);
						auto result = testee.end();
						TestCase::assert(
							std::is_same<typename SetType<T, Compare, Allocator>::iterator, decltype(result)>::value, "type");
						TestCase::assert(*(--result) == ValueType(), "result");
					}),

				TestCase(
					"end const",
					[] {
						const SetType<T, Compare, Allocator> testee(INITIALIZER_LIST);
						auto result = testee.end();
						TestCase::assert(
							std::is_same<typename SetType<T, Compare, Allocator>::const_iterator, decltype(result)>::value, "type");
						TestCase::assert(*(--result) == ValueType(), "result");
					}),

				TestCase(
					"rbegin",
					[] {
						SetType<T, Compare, Allocator> testee(INITIALIZER_LIST);
						auto result = testee.rbegin();
						TestCase::assert(
							std::is_same<typename SetType<T, Compare, Allocator>::reverse_iterator, decltype(result)>::value,
							"type");
						TestCase::assert(*result == ValueType(), "result");
					}),

				TestCase(
					"rbegin const",
					[] {
						const SetType<T, Compare, Allocator> testee(INITIALIZER_LIST);
						auto result = testee.rbegin();
						TestCase::assert(
							std::is_same<typename SetType<T, Compare, Allocator>::const_reverse_iterator, decltype(result)>::value,
							"type");
						TestCase::assert(*result == ValueType(), "result");
					}),

				TestCase(
					"rend",
					[] {
						SetType<T, Compare, Allocator> testee(INITIALIZER_LIST);
						auto result = testee.rend();
						TestCase::assert(
							std::is_same<typename SetType<T, Compare, Allocator>::reverse_iterator, decltype(result)>::value,
							"type");
						TestCase::assert(*(--result) == ValueType(), "result");
					}),

				TestCase(
					"rend const",
					[] {
						const SetType<T, Compare, Allocator> testee(INITIALIZER_LIST);
						auto result = testee.rend();
						TestCase::assert(
							std::is_same<typename SetType<T, Compare, Allocator>::const_reverse_iterator, decltype(result)>::value,
							"type");
						TestCase::assert(*(--result) == ValueType(), "result");
					}),

				TestCase(
					"cbegin",
					[] {
						SetType<T, Compare, Allocator> testee(INITIALIZER_LIST);
						auto result = testee.cbegin();
						TestCase::assert(
							std::is_same<typename SetType<T, Compare, Allocator>::const_iterator, decltype(result)>::value, "type");
						TestCase::assert(*result == ValueType(), "result");
					}),

				TestCase(
					"cend",
					[] {
						SetType<T, Compare, Allocator> testee(INITIALIZER_LIST);
						auto result = testee.cend();
						TestCase::assert(
							std::is_same<typename SetType<T, Compare, Allocator>::const_iterator, decltype(result)>::value, "type");
						TestCase::assert(*(--result) == ValueType(), "result");
					}),

				TestCase(
					"crbegin",
					[] {
						SetType<T, Compare, Allocator> testee(INITIALIZER_LIST);
						auto result = testee.crbegin();
						TestCase::assert(
							std::is_same<typename SetType<T, Compare, Allocator>::const_reverse_iterator, decltype(result)>::value,
							"type");
						TestCase::assert(*result == ValueType(), "result");
					}),

				TestCase(
					"crend",
					[] {
						SetType<T, Compare, Allocator> testee(INITIALIZER_LIST);
						auto result = testee.crend();
						TestCase::assert(
							std::is_same<typename SetType<T, Compare, Allocator>::const_reverse_iterator, decltype(result)>::value,
							"type");
						TestCase::assert(*(--result) == ValueType(), "result");
					}),

				TestCase(
					"empty",
					[] {
						const SetType<T, Compare, Allocator> testee;
						auto result = testee.empty();
						TestCase::assert(std::is_same<bool, decltype(result)>::value, "bool");
						TestCase::assert(result == true, "result");
					}),

				TestCase(
					"size",
					[] {
						const SetType<T, Compare, Allocator> testee(INITIALIZER_LIST);
						auto result = testee.size();
						TestCase::assert(
							std::is_same<typename SetType<T, Compare, Allocator>::size_type, decltype(result)>::value, "type");
						TestCase::assert(result == INITIALIZER_LIST.size(), "result");
					}),

				TestCase(
					"max_size",
					[] {
						const SetType<T, Compare, Allocator> testee(INITIALIZER_LIST);
						auto result = testee.max_size();
						TestCase::assert(
							std::is_same<typename SetType<T, Compare, Allocator>::size_type, decltype(result)>::value, "type");
						TestCase::assert(result >= INITIALIZER_LIST.size(), "result");
					}),


				TestCase(
					"insert single element",
					[] {
						SetType<T, Compare, Allocator> testee;
						auto position = testee.begin();
						auto value = T();
						auto result = testee.insert(value);
						if (!isMultiset) {
							TestCase::assert(
								std::is_same<std::pair<typename SetType<T, Compare, Allocator>::iterator, bool>, decltype(result)>::
									value,
								"type");
						} else {
							TestCase::assert(
								std::is_same<typename SetType<T, Compare, Allocator>::iterator, decltype(result)>::value, "type");
						}
						TestCase::assert(testee.size() == 1, "result");
					}),

				TestCase(
					"insert move",
					[] {
						SetType<T, Compare, Allocator> testee;
						auto position = testee.begin();
						auto value = T();
						auto result = testee.insert(std::move(value));
						if (!isMultiset) {
							TestCase::assert(
								std::is_same<std::pair<typename SetType<T, Compare, Allocator>::iterator, bool>, decltype(result)>::
									value,
								"type");
						} else {
							TestCase::assert(
								std::is_same<typename SetType<T, Compare, Allocator>::iterator, decltype(result)>::value, "type");
						}
						TestCase::assert(testee.size() == 1, "result");
					}),

				TestCase(
					"insert hint single element",
					[] {
						SetType<T, Compare, Allocator> testee;
						auto position = testee.begin();
						auto value = T();
						auto result = testee.insert(position, value);
						TestCase::assert(
							std::is_same<typename SetType<T, Compare, Allocator>::iterator, decltype(result)>::value, "type");
						TestCase::assert(testee.size() == 1, "result");
					}),

				TestCase(
					"insert hint move",
					[] {
						SetType<T, Compare, Allocator> testee;
						auto position = testee.begin();
						auto value = T();
						auto result = testee.insert(position, std::move(value));
						TestCase::assert(
							std::is_same<typename SetType<T, Compare, Allocator>::iterator, decltype(result)>::value, "type");
						TestCase::assert(testee.size() == 1, "result");
					}),

				TestCase(
					"insert range",
					[] {
						SetType<T, Compare, Allocator> testee;
						testee.insert(ARRAY.begin(), ARRAY.end());
						TestCase::assert(testee.size() == ARRAY.size());
					}),

				TestCase(
					"insert initializer list",
					[] {
						SetType<T, Compare, Allocator> testee;
						testee.insert(INITIALIZER_LIST);
						TestCase::assert(testee.size() == INITIALIZER_LIST.size());
					}),

				TestCase(
					"erase single element",
					[] {
						SetType<T, Compare, Allocator> testee(INITIALIZER_LIST);
						auto position = testee.begin();
						auto result = testee.erase(position);
						TestCase::assert(
							std::is_same<typename SetType<T, Compare, Allocator>::iterator, decltype(result)>::value, "type");
						TestCase::assert(testee.size() == 0, "result");
					}),

				TestCase(
					"erase key",
					[] {
						SetType<T, Compare, Allocator> testee(INITIALIZER_LIST);
						auto result = testee.erase(T());
						TestCase::assert(
							std::is_same<typename SetType<T, Compare, Allocator>::size_type, decltype(result)>::value, "type");
						TestCase::assert(testee.size() == 0, "result");
					}),

				TestCase(
					"erase range",
					[] {
						SetType<T, Compare, Allocator> testee(INITIALIZER_LIST);
						auto first = testee.begin();
						auto last = testee.end();
						;
						auto result = testee.erase(first, last);
						TestCase::assert(
							std::is_same<typename SetType<T, Compare, Allocator>::iterator, decltype(result)>::value, "type");
						TestCase::assert(testee.size() == 0, "result");
					}),

				TestCase(
					"swap",
					[] {
						SetType<T, Compare, Allocator> other(INITIALIZER_LIST);
						SetType<T, Compare, Allocator> testee(INITIALIZER_LIST);
						testee.swap(other);
						TestCase::assert(other.size() == INITIALIZER_LIST.size(), "other");
						TestCase::assert(testee.size() == INITIALIZER_LIST.size(), "testee");
					}),

				TestCase(
					"clear",
					[] {
						SetType<T, Compare, Allocator> testee(INITIALIZER_LIST);
						testee.clear();
						TestCase::assert(testee.size() == 0);
					}),

				TestCase(
					"emplace",
					[] {
						SetType<T, Compare, Allocator> testee;
						auto result = testee.emplace();
						if (!isMultiset) {
							TestCase::assert(
								std::is_same<std::pair<typename SetType<T, Compare, Allocator>::iterator, bool>, decltype(result)>::
									value,
								"type");
						} else {
							TestCase::assert(
								std::is_same<typename SetType<T, Compare, Allocator>::iterator, decltype(result)>::value, "type");
						}
						TestCase::assert(testee.size() == 1, "result");
					}),

				TestCase(
					"emplace_hint",
					[] {
						SetType<T, Compare, Allocator> testee;
						auto position = testee.begin();
						auto result = testee.emplace_hint(position);
						TestCase::assert(
							std::is_same<typename SetType<T, Compare, Allocator>::iterator, decltype(result)>::value, "type");
						TestCase::assert(testee.size() == 1, "result");
					}),

				TestCase(
					"key_comp",
					[] {
						const SetType<T, Compare, Allocator> testee;
						auto result = testee.key_comp();
						TestCase::assert(
							std::is_same<typename SetType<T, Compare, Allocator>::key_compare, decltype(result)>::value);
					}),

				TestCase(
					"value_comp",
					[] {
						const SetType<T, Compare, Allocator> testee;
						auto result = testee.value_comp();
						TestCase::assert(
							std::is_same<typename SetType<T, Compare, Allocator>::value_compare, decltype(result)>::value);
					}),

				TestCase(
					"find",
					[] {
						SetType<T, Compare, Allocator> testee(INITIALIZER_LIST);
						auto result = testee.find(T());
						TestCase::assert(
							std::is_same<typename SetType<T, Compare, Allocator>::iterator, decltype(result)>::value, "type");
						TestCase::assert(*result == ValueType(), "result");
					}),

				TestCase(
					"find const",
					[] {
						const SetType<T, Compare, Allocator> testee(INITIALIZER_LIST);
						auto result = testee.find(T());
						TestCase::assert(
							std::is_same<typename SetType<T, Compare, Allocator>::const_iterator, decltype(result)>::value, "type");
						TestCase::assert(*result == ValueType(), "result");
					}),

				TestCase(
					"count",
					[] {
						const SetType<T, Compare, Allocator> testee(INITIALIZER_LIST);
						auto result = testee.count(T());
						TestCase::assert(
							std::is_same<typename SetType<T, Compare, Allocator>::size_type, decltype(result)>::value, "type");
						TestCase::assert(result == 1, "result");
					}),

				TestCase(
					"lower_bound",
					[] {
						SetType<T, Compare, Allocator> testee(INITIALIZER_LIST);
						auto result = testee.lower_bound(T());
						TestCase::assert(
							std::is_same<typename SetType<T, Compare, Allocator>::iterator, decltype(result)>::value, "type");
						TestCase::assert(*result == ValueType(), "result");
					}),

				TestCase(
					"lower_bound const",
					[] {
						const SetType<T, Compare, Allocator> testee(INITIALIZER_LIST);
						auto result = testee.lower_bound(T());
						TestCase::assert(
							std::is_same<typename SetType<T, Compare, Allocator>::const_iterator, decltype(result)>::value, "type");
						TestCase::assert(*result == ValueType(), "result");
					}),

				TestCase(
					"upper_bound",
					[] {
						SetType<T, Compare, Allocator> testee(INITIALIZER_LIST);
						auto result = testee.upper_bound(T());
						TestCase::assert(
							std::is_same<typename SetType<T, Compare, Allocator>::iterator, decltype(result)>::value, "type");
						TestCase::assert(*(--result) == ValueType(), "result");
					}),

				TestCase(
					"upper_bound const",
					[] {
						const SetType<T, Compare, Allocator> testee(INITIALIZER_LIST);
						auto result = testee.upper_bound(T());
						TestCase::assert(
							std::is_same<typename SetType<T, Compare, Allocator>::const_iterator, decltype(result)>::value, "type");
						TestCase::assert(*(--result) == ValueType(), "result");
					}),

				TestCase(
					"equal_range",
					[] {
						SetType<T, Compare, Allocator> testee(INITIALIZER_LIST);
						auto result = testee.equal_range(T());
						TestCase::assert(std::is_same<
										 std::pair<
											 typename SetType<T, Compare, Allocator>::iterator,
											 typename SetType<T, Compare, Allocator>::iterator>,
										 decltype(result)>::value);
					}),

				TestCase(
					"equal_range const",
					[] {
						const SetType<T, Compare, Allocator> testee(INITIALIZER_LIST);
						auto result = testee.equal_range(T());
						TestCase::assert(std::is_same<
										 std::pair<
											 typename SetType<T, Compare, Allocator>::const_iterator,
											 typename SetType<T, Compare, Allocator>::const_iterator>,
										 decltype(result)>::value);
					}),

				TestCase(
					"get_allocator",
					[] {
						SetType<T, Compare, Allocator> testee;
						auto result = testee.get_allocator();
						TestCase::assert(
							std::is_same<typename SetType<T, Compare, Allocator>::allocator_type, decltype(result)>::value);
					}),

				TestCase(
					"operator==",
					[] {
						SetType<T, Compare, Allocator> lhs(INITIALIZER_LIST);
						SetType<T, Compare, Allocator> rhs(INITIALIZER_LIST);
						auto result = (lhs == rhs);
						TestCase::assert(std::is_same<bool, decltype(result)>::value, "type");
						TestCase::assert(result == true, "result");
					}),

				TestCase(
					"operator!=",
					[] {
						SetType<T, Compare, Allocator> lhs;
						SetType<T, Compare, Allocator> rhs(INITIALIZER_LIST);
						auto result = (lhs != rhs);
						TestCase::assert(std::is_same<bool, decltype(result)>::value, "type");
						TestCase::assert(result == true, "result");
					}),

				TestCase(
					"operator<",
					[] {
						SetType<T, Compare, Allocator> lhs;
						SetType<T, Compare, Allocator> rhs(INITIALIZER_LIST);
						auto result = (lhs < rhs);
						TestCase::assert(std::is_same<bool, decltype(result)>::value, "type");
						TestCase::assert(result == true, "result");
					}),

				TestCase(
					"operator<=",
					[] {
						SetType<T, Compare, Allocator> lhs;
						SetType<T, Compare, Allocator> rhs(INITIALIZER_LIST);
						auto result = (lhs <= rhs);
						TestCase::assert(std::is_same<bool, decltype(result)>::value, "type");
						TestCase::assert(result == true, "result");
					}),

				TestCase(
					"operator>",
					[] {
						SetType<T, Compare, Allocator> lhs(INITIALIZER_LIST);
						SetType<T, Compare, Allocator> rhs;
						auto result = (lhs > rhs);
						TestCase::assert(std::is_same<bool, decltype(result)>::value, "type");
						TestCase::assert(result == true, "result");
					}),

				TestCase(
					"operator>=",
					[] {
						SetType<T, Compare, Allocator> lhs(INITIALIZER_LIST);
						SetType<T, Compare, Allocator> rhs;
						auto result = (lhs >= rhs);
						TestCase::assert(std::is_same<bool, decltype(result)>::value, "type");
						TestCase::assert(result == true, "result");
					}),

				TestCase("swap lhs rhs", [] {
					SetType<T, Compare, Allocator> lhs(INITIALIZER_LIST);
					SetType<T, Compare, Allocator> rhs;
					swap(lhs, rhs);
					TestCase::assert(lhs.size() == 0, "lhs");
					TestCase::assert(rhs.size() == INITIALIZER_LIST.size(), "rhs");
				})})
	{
	}

	static const InitializerListType INITIALIZER_LIST;
	static const ArrayType ARRAY;
};

template<template<typename...> class SetType, typename T, bool isMultiset, typename Compare, typename Allocator>
const typename SetTestSuite<SetType, T, isMultiset, Compare, Allocator>::InitializerListType
	SetTestSuite<SetType, T, isMultiset, Compare, Allocator>::INITIALIZER_LIST = {T()};

template<template<typename...> class SetType, typename T, bool isMultiset, typename Compare, typename Allocator>
const typename SetTestSuite<SetType, T, isMultiset, Compare, Allocator>::ArrayType
	SetTestSuite<SetType, T, isMultiset, Compare, Allocator>::ARRAY = {T()};

} // namespace Testee

#endif // SetTestSuite_INCLUDED
