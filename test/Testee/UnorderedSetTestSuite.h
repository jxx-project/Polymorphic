//
// Copyright (C) 2018 Dr. Michael Steffens
//
// SPDX-License-Identifier:	BSL-1.0
//


#ifndef UnorderedSetTestSuite_INCLUDED
#define UnorderedSetTestSuite_INCLUDED

#include "Testee/TestSuite.h"
#include <array>

namespace Testee {

/// Test UnorderedSetType C++11 standard unordered_set or unordered_multiset interface.
template<
	template<typename...> class UnorderedSetType,
	typename Key,
	bool isMultiset = false,
	typename Hash = std::hash<Key>,
	typename Predicate = std::equal_to<Key>,
	typename Allocator = std::allocator<Key>>
class UnorderedSetTestSuite : public TestSuite
{
public:
	typedef std::initializer_list<Key> InitializerListType;
	typedef std::array<Key, 1> ArrayType;
	typedef typename UnorderedSetType<Key, Hash, Predicate, Allocator>::value_type ValueType;

	UnorderedSetTestSuite(const std::string& unorderedMapType) :
		TestSuite(
			unorderedMapType + " C++11 standard interface",
			{

				TestCase(
					"typedefs",
					[] {
						TestCase::assert(
							std::is_same<typename UnorderedSetType<Key, Hash, Predicate, Allocator>::key_type, Key>::value,
							"key_type");
						TestCase::assert(
							std::is_same<typename UnorderedSetType<Key, Hash, Predicate, Allocator>::value_type, Key>::value,
							"value_type");
						TestCase::assert(
							std::is_class<typename UnorderedSetType<Key, Hash, Predicate, Allocator>::hasher>::value, "hasher");
						TestCase::assert(
							std::is_class<typename UnorderedSetType<Key, Hash, Predicate, Allocator>::key_equal>::value,
							"key_equal");
						TestCase::assert(
							std::is_class<typename UnorderedSetType<Key, Hash, Predicate, Allocator>::allocator_type>::value,
							"allocator_type");
						TestCase::assert(
							std::is_same<
								typename UnorderedSetType<Key, Hash, Predicate, Allocator>::reference,
								typename UnorderedSetType<Key, Hash, Predicate, Allocator>::allocator_type::reference>::value,
							"reference");
						TestCase::assert(
							std::is_same<
								typename UnorderedSetType<Key, Hash, Predicate, Allocator>::const_reference,
								typename UnorderedSetType<Key, Hash, Predicate, Allocator>::allocator_type::const_reference>::value,
							"const_reference");
					}),

				TestCase(
					"ctor default",
					[] {
						UnorderedSetType<Key, Hash, Predicate, Allocator> testee;
						TestCase::assert(testee.size() == 0);
					}),

				TestCase(
					"ctor default with allocator",
					[] {
						const Allocator allocator;
						UnorderedSetType<Key, Hash, Predicate, Allocator> testee(allocator);
						TestCase::assert(testee.size() == 0);
					}),

				TestCase(
					"ctor copy",
					[] {
						const UnorderedSetType<Key, Hash, Predicate, Allocator> other(INITIALIZER_LIST);
						UnorderedSetType<Key, Hash, Predicate, Allocator> testee(other);
						TestCase::assert(testee.size() == INITIALIZER_LIST.size());
					}),

				TestCase(
					"ctor copy with allocator",
					[] {
						const UnorderedSetType<Key, Hash, Predicate, Allocator> other(INITIALIZER_LIST);
						const Allocator allocator;
						UnorderedSetType<Key, Hash, Predicate, Allocator> testee(other, allocator);
						TestCase::assert(testee.size() == INITIALIZER_LIST.size());
					}),

				TestCase(
					"ctor move",
					[] {
						UnorderedSetType<Key, Hash, Predicate, Allocator> other(INITIALIZER_LIST);
						UnorderedSetType<Key, Hash, Predicate, Allocator> testee(std::move(other));
						TestCase::assert(other.size() == 0, "other");
						TestCase::assert(testee.size() == INITIALIZER_LIST.size(), "testee");
					}),

				TestCase(
					"ctor move with allocator",
					[] {
						UnorderedSetType<Key, Hash, Predicate, Allocator> other(INITIALIZER_LIST);
						const Allocator allocator;
						UnorderedSetType<Key, Hash, Predicate, Allocator> testee(std::move(other), allocator);
						TestCase::assert(other.size() == 0, "other");
						TestCase::assert(testee.size() == INITIALIZER_LIST.size(), "testee");
					}),

				TestCase(
					"ctor range",
					[] {
						UnorderedSetType<Key, Hash, Predicate, Allocator> testee(ARRAY.begin(), ARRAY.end());
						TestCase::assert(testee.size() == ARRAY.size());
					}),

				TestCase(
					"ctor initializer list",
					[] {
						UnorderedSetType<Key, Hash, Predicate, Allocator> testee(INITIALIZER_LIST);
						TestCase::assert(testee.size() == INITIALIZER_LIST.size());
					}),

				TestCase(
					"operator= copy",
					[] {
						const UnorderedSetType<Key, Hash, Predicate, Allocator> other(INITIALIZER_LIST);
						UnorderedSetType<Key, Hash, Predicate, Allocator> testee;
						auto& result = (testee = other);
						TestCase::assert(
							std::is_same<UnorderedSetType<Key, Hash, Predicate, Allocator>&, decltype(result)>::value, "type");
						TestCase::assert(testee.size() == INITIALIZER_LIST.size(), "result");
					}),

				TestCase(
					"operator= move",
					[] {
						UnorderedSetType<Key, Hash, Predicate, Allocator> other(INITIALIZER_LIST);
						UnorderedSetType<Key, Hash, Predicate, Allocator> testee;
						auto& result = (testee = std::move(other));
						TestCase::assert(
							std::is_same<UnorderedSetType<Key, Hash, Predicate, Allocator>&, decltype(result)>::value, "type");
						TestCase::assert(other.size() == 0, "other");
						TestCase::assert(testee.size() == INITIALIZER_LIST.size(), "testee");
					}),

				TestCase(
					"operator= initializer list",
					[] {
						UnorderedSetType<Key, Hash, Predicate, Allocator> testee;
						auto& result = (testee = INITIALIZER_LIST);
						TestCase::assert(
							std::is_same<UnorderedSetType<Key, Hash, Predicate, Allocator>&, decltype(result)>::value, "type");
						TestCase::assert(testee.size() == INITIALIZER_LIST.size(), "result");
					}),

				TestCase(
					"begin",
					[] {
						UnorderedSetType<Key, Hash, Predicate, Allocator> testee(INITIALIZER_LIST);
						auto result = testee.begin();
						TestCase::assert(
							std::is_same<typename UnorderedSetType<Key, Hash, Predicate, Allocator>::iterator, decltype(result)>::
								value,
							"type");
						TestCase::assert(*result == ValueType(), "result");
					}),

				TestCase(
					"begin const",
					[] {
						const UnorderedSetType<Key, Hash, Predicate, Allocator> testee(INITIALIZER_LIST);
						auto result = testee.begin();
						TestCase::assert(
							std::is_same<
								typename UnorderedSetType<Key, Hash, Predicate, Allocator>::const_iterator,
								decltype(result)>::value,
							"type");
						TestCase::assert(*result == ValueType(), "result");
					}),

				TestCase(
					"end",
					[] {
						UnorderedSetType<Key, Hash, Predicate, Allocator> testee(INITIALIZER_LIST);
						auto result = testee.end();
						TestCase::assert(
							std::is_same<typename UnorderedSetType<Key, Hash, Predicate, Allocator>::iterator, decltype(result)>::
								value);
					}),

				TestCase(
					"end const",
					[] {
						const UnorderedSetType<Key, Hash, Predicate, Allocator> testee(INITIALIZER_LIST);
						auto result = testee.end();
						TestCase::assert(std::is_same<
										 typename UnorderedSetType<Key, Hash, Predicate, Allocator>::const_iterator,
										 decltype(result)>::value);
					}),

				TestCase(
					"cbegin",
					[] {
						UnorderedSetType<Key, Hash, Predicate, Allocator> testee(INITIALIZER_LIST);
						auto result = testee.cbegin();
						TestCase::assert(
							std::is_same<
								typename UnorderedSetType<Key, Hash, Predicate, Allocator>::const_iterator,
								decltype(result)>::value,
							"type");
						TestCase::assert(*result == ValueType(), "result");
					}),

				TestCase(
					"cend",
					[] {
						UnorderedSetType<Key, Hash, Predicate, Allocator> testee(INITIALIZER_LIST);
						auto result = testee.cend();
						TestCase::assert(std::is_same<
										 typename UnorderedSetType<Key, Hash, Predicate, Allocator>::const_iterator,
										 decltype(result)>::value);
					}),

				TestCase(
					"empty",
					[] {
						const UnorderedSetType<Key, Hash, Predicate, Allocator> testee;
						auto result = testee.empty();
						TestCase::assert(std::is_same<bool, decltype(result)>::value, "bool");
						TestCase::assert(result == true, "result");
					}),

				TestCase(
					"size",
					[] {
						const UnorderedSetType<Key, Hash, Predicate, Allocator> testee(INITIALIZER_LIST);
						auto result = testee.size();
						TestCase::assert(
							std::is_same<typename UnorderedSetType<Key, Hash, Predicate, Allocator>::size_type, decltype(result)>::
								value,
							"type");
						TestCase::assert(result == INITIALIZER_LIST.size(), "result");
					}),

				TestCase(
					"max_size",
					[] {
						const UnorderedSetType<Key, Hash, Predicate, Allocator> testee(INITIALIZER_LIST);
						auto result = testee.max_size();
						TestCase::assert(
							std::is_same<typename UnorderedSetType<Key, Hash, Predicate, Allocator>::size_type, decltype(result)>::
								value,
							"type");
						TestCase::assert(result >= INITIALIZER_LIST.size(), "result");
					}),


				TestCase(
					"insert single element",
					[] {
						UnorderedSetType<Key, Hash, Predicate, Allocator> testee;
						auto position = testee.begin();
						auto value = Key();
						auto result = testee.insert(value);
						if (!isMultiset) {
							TestCase::assert(
								std::is_same<
									std::pair<typename UnorderedSetType<Key, Hash, Predicate, Allocator>::iterator, bool>,
									decltype(result)>::value,
								"type");
						} else {
							TestCase::assert(
								std::is_same<
									typename UnorderedSetType<Key, Hash, Predicate, Allocator>::iterator,
									decltype(result)>::value,
								"type");
						}
						TestCase::assert(testee.size() == 1, "result");
					}),

				TestCase(
					"insert move",
					[] {
						UnorderedSetType<Key, Hash, Predicate, Allocator> testee;
						auto position = testee.begin();
						auto value = Key();
						auto result = testee.insert(std::move(value));
						if (!isMultiset) {
							TestCase::assert(
								std::is_same<
									std::pair<typename UnorderedSetType<Key, Hash, Predicate, Allocator>::iterator, bool>,
									decltype(result)>::value,
								"type");
						} else {
							TestCase::assert(
								std::is_same<
									typename UnorderedSetType<Key, Hash, Predicate, Allocator>::iterator,
									decltype(result)>::value,
								"type");
						}
						TestCase::assert(testee.size() == 1, "result");
					}),

				TestCase(
					"insert hint single element",
					[] {
						UnorderedSetType<Key, Hash, Predicate, Allocator> testee;
						auto position = testee.begin();
						auto value = Key();
						auto result = testee.insert(position, value);
						TestCase::assert(
							std::is_same<typename UnorderedSetType<Key, Hash, Predicate, Allocator>::iterator, decltype(result)>::
								value,
							"type");
						TestCase::assert(testee.size() == 1, "result");
					}),

				TestCase(
					"insert hint move",
					[] {
						UnorderedSetType<Key, Hash, Predicate, Allocator> testee;
						auto position = testee.begin();
						auto value = Key();
						auto result = testee.insert(position, std::move(value));
						TestCase::assert(
							std::is_same<typename UnorderedSetType<Key, Hash, Predicate, Allocator>::iterator, decltype(result)>::
								value,
							"type");
						TestCase::assert(testee.size() == 1, "result");
					}),

				TestCase(
					"insert range",
					[] {
						UnorderedSetType<Key, Hash, Predicate, Allocator> testee;
						testee.insert(ARRAY.begin(), ARRAY.end());
						TestCase::assert(testee.size() == ARRAY.size());
					}),

				TestCase(
					"insert initializer list",
					[] {
						UnorderedSetType<Key, Hash, Predicate, Allocator> testee;
						testee.insert(INITIALIZER_LIST);
						TestCase::assert(testee.size() == INITIALIZER_LIST.size());
					}),

				TestCase(
					"erase single element",
					[] {
						UnorderedSetType<Key, Hash, Predicate, Allocator> testee(INITIALIZER_LIST);
						auto position = testee.begin();
						auto result = testee.erase(position);
						TestCase::assert(
							std::is_same<typename UnorderedSetType<Key, Hash, Predicate, Allocator>::iterator, decltype(result)>::
								value,
							"type");
						TestCase::assert(testee.size() == 0, "result");
					}),

				TestCase(
					"erase key",
					[] {
						UnorderedSetType<Key, Hash, Predicate, Allocator> testee(INITIALIZER_LIST);
						auto result = testee.erase(Key());
						TestCase::assert(
							std::is_same<typename UnorderedSetType<Key, Hash, Predicate, Allocator>::size_type, decltype(result)>::
								value,
							"type");
						TestCase::assert(testee.size() == 0, "result");
					}),

				TestCase(
					"erase range",
					[] {
						UnorderedSetType<Key, Hash, Predicate, Allocator> testee(INITIALIZER_LIST);
						auto first = testee.begin();
						auto last = testee.end();
						;
						auto result = testee.erase(first, last);
						TestCase::assert(
							std::is_same<typename UnorderedSetType<Key, Hash, Predicate, Allocator>::iterator, decltype(result)>::
								value,
							"type");
						TestCase::assert(testee.size() == 0, "result");
					}),

				TestCase(
					"swap",
					[] {
						UnorderedSetType<Key, Hash, Predicate, Allocator> other(INITIALIZER_LIST);
						UnorderedSetType<Key, Hash, Predicate, Allocator> testee(INITIALIZER_LIST);
						testee.swap(other);
						TestCase::assert(other.size() == INITIALIZER_LIST.size(), "other");
						TestCase::assert(testee.size() == INITIALIZER_LIST.size(), "testee");
					}),

				TestCase(
					"clear",
					[] {
						UnorderedSetType<Key, Hash, Predicate, Allocator> testee(INITIALIZER_LIST);
						testee.clear();
						TestCase::assert(testee.size() == 0);
					}),

				TestCase(
					"emplace",
					[] {
						UnorderedSetType<Key, Hash, Predicate, Allocator> testee;
						auto result = testee.emplace();
						if (!isMultiset) {
							TestCase::assert(
								std::is_same<
									std::pair<typename UnorderedSetType<Key, Hash, Predicate, Allocator>::iterator, bool>,
									decltype(result)>::value,
								"type");
						} else {
							TestCase::assert(
								std::is_same<
									typename UnorderedSetType<Key, Hash, Predicate, Allocator>::iterator,
									decltype(result)>::value,
								"type");
						}
						TestCase::assert(testee.size() == 1, "result");
					}),

				TestCase(
					"emplace_hint",
					[] {
						UnorderedSetType<Key, Hash, Predicate, Allocator> testee;
						auto position = testee.begin();
						auto result = testee.emplace_hint(position);
						TestCase::assert(
							std::is_same<typename UnorderedSetType<Key, Hash, Predicate, Allocator>::iterator, decltype(result)>::
								value,
							"type");
						TestCase::assert(testee.size() == 1, "result");
					}),

				TestCase(
					"find",
					[] {
						UnorderedSetType<Key, Hash, Predicate, Allocator> testee(INITIALIZER_LIST);
						auto result = testee.find(Key());
						TestCase::assert(
							std::is_same<typename UnorderedSetType<Key, Hash, Predicate, Allocator>::iterator, decltype(result)>::
								value,
							"type");
						TestCase::assert(*result == ValueType(), "result");
					}),

				TestCase(
					"find const",
					[] {
						const UnorderedSetType<Key, Hash, Predicate, Allocator> testee(INITIALIZER_LIST);
						auto result = testee.find(Key());
						TestCase::assert(
							std::is_same<
								typename UnorderedSetType<Key, Hash, Predicate, Allocator>::const_iterator,
								decltype(result)>::value,
							"type");
						TestCase::assert(*result == ValueType(), "result");
					}),

				TestCase(
					"count",
					[] {
						const UnorderedSetType<Key, Hash, Predicate, Allocator> testee(INITIALIZER_LIST);
						auto result = testee.count(Key());
						TestCase::assert(
							std::is_same<typename UnorderedSetType<Key, Hash, Predicate, Allocator>::size_type, decltype(result)>::
								value,
							"type");
						TestCase::assert(result == 1, "result");
					}),

				TestCase(
					"equal_range",
					[] {
						UnorderedSetType<Key, Hash, Predicate, Allocator> testee(INITIALIZER_LIST);
						auto result = testee.equal_range(Key());
						TestCase::assert(std::is_same<
										 std::pair<
											 typename UnorderedSetType<Key, Hash, Predicate, Allocator>::iterator,
											 typename UnorderedSetType<Key, Hash, Predicate, Allocator>::iterator>,
										 decltype(result)>::value);
					}),

				TestCase(
					"equal_range const",
					[] {
						const UnorderedSetType<Key, Hash, Predicate, Allocator> testee(INITIALIZER_LIST);
						auto result = testee.equal_range(Key());
						TestCase::assert(std::is_same<
										 std::pair<
											 typename UnorderedSetType<Key, Hash, Predicate, Allocator>::const_iterator,
											 typename UnorderedSetType<Key, Hash, Predicate, Allocator>::const_iterator>,
										 decltype(result)>::value);
					}),

				TestCase(
					"bucket_count",
					[] {
						const UnorderedSetType<Key, Hash, Predicate, Allocator> testee(INITIALIZER_LIST);
						auto result = testee.bucket_count();
						TestCase::assert(
							std::is_same<typename UnorderedSetType<Key, Hash, Predicate, Allocator>::size_type, decltype(result)>::
								value,
							"type");
						TestCase::assert(result >= 1, "result");
					}),

				TestCase(
					"max_bucket_count",
					[] {
						const UnorderedSetType<Key, Hash, Predicate, Allocator> testee(INITIALIZER_LIST);
						auto result = testee.max_bucket_count();
						TestCase::assert(
							std::is_same<typename UnorderedSetType<Key, Hash, Predicate, Allocator>::size_type, decltype(result)>::
								value,
							"type");
						TestCase::assert(result >= 1, "result");
					}),

				TestCase(
					"bucket_size",
					[] {
						const UnorderedSetType<Key, Hash, Predicate, Allocator> testee(INITIALIZER_LIST);
						auto result = testee.bucket_size(0);
						TestCase::assert(
							std::is_same<typename UnorderedSetType<Key, Hash, Predicate, Allocator>::size_type, decltype(result)>::
								value,
							"type");
						TestCase::assert(result >= 0, "result");
					}),

				TestCase(
					"bucket",
					[] {
						const UnorderedSetType<Key, Hash, Predicate, Allocator> testee(INITIALIZER_LIST);
						auto result = testee.bucket(Key());
						TestCase::assert(
							std::is_same<typename UnorderedSetType<Key, Hash, Predicate, Allocator>::size_type, decltype(result)>::
								value,
							"type");
						TestCase::assert(result >= 0, "result");
					}),

				TestCase(
					"load_factor",
					[] {
						const UnorderedSetType<Key, Hash, Predicate, Allocator> testee(INITIALIZER_LIST);
						auto result = testee.load_factor();
						TestCase::assert(std::is_same<float, decltype(result)>::value, "type");
						TestCase::assert(result >= 0.0F, "result");
					}),

				TestCase(
					"max_load_factor get",
					[] {
						const UnorderedSetType<Key, Hash, Predicate, Allocator> testee(INITIALIZER_LIST);
						auto result = testee.max_load_factor();
						TestCase::assert(std::is_same<float, decltype(result)>::value, "type");
						TestCase::assert(result >= 0.0F, "result");
					}),

				TestCase(
					"max_load_factor set",
					[] {
						UnorderedSetType<Key, Hash, Predicate, Allocator> testee(INITIALIZER_LIST);
						auto oldLoadFactor = testee.max_load_factor();
						testee.max_load_factor(oldLoadFactor + 1.0F);
						auto newLoadFactor = testee.max_load_factor();
						TestCase::assert(newLoadFactor >= oldLoadFactor);
					}),

				TestCase(
					"rehash",
					[] {
						UnorderedSetType<Key, Hash, Predicate, Allocator> testee(INITIALIZER_LIST);
						auto oldCount = testee.bucket_count();
						testee.rehash(oldCount + 1);
						auto newCount = testee.bucket_count();
						TestCase::assert(newCount > oldCount);
					}),

				TestCase(
					"reserve",
					[] {
						UnorderedSetType<Key, Hash, Predicate, Allocator> testee(INITIALIZER_LIST);
						auto oldCount = testee.bucket_count();
						testee.reserve(oldCount + 1);
						auto newCount = testee.bucket_count();
						TestCase::assert(newCount > oldCount);
					}),

				TestCase(
					"hash_function",
					[] {
						const UnorderedSetType<Key, Hash, Predicate, Allocator> testee;
						auto result = testee.hash_function();
						TestCase::assert(
							std::is_same<typename UnorderedSetType<Key, Hash, Predicate, Allocator>::hasher, decltype(result)>::
								value);
					}),

				TestCase(
					"key_eq",
					[] {
						const UnorderedSetType<Key, Hash, Predicate, Allocator> testee;
						auto result = testee.key_eq();
						TestCase::assert(
							std::is_same<typename UnorderedSetType<Key, Hash, Predicate, Allocator>::key_equal, decltype(result)>::
								value);
					}),

				TestCase(
					"get_allocator",
					[] {
						UnorderedSetType<Key, Hash, Predicate, Allocator> testee;
						auto result = testee.get_allocator();
						TestCase::assert(std::is_same<
										 typename UnorderedSetType<Key, Hash, Predicate, Allocator>::allocator_type,
										 decltype(result)>::value);
					}),

				TestCase(
					"operator==",
					[] {
						UnorderedSetType<Key, Hash, Predicate, Allocator> lhs(INITIALIZER_LIST);
						UnorderedSetType<Key, Hash, Predicate, Allocator> rhs(INITIALIZER_LIST);
						auto result = (lhs == rhs);
						TestCase::assert(std::is_same<bool, decltype(result)>::value, "type");
						TestCase::assert(result == true, "result");
					}),

				TestCase(
					"operator!=",
					[] {
						UnorderedSetType<Key, Hash, Predicate, Allocator> lhs;
						UnorderedSetType<Key, Hash, Predicate, Allocator> rhs(INITIALIZER_LIST);
						auto result = (lhs != rhs);
						TestCase::assert(std::is_same<bool, decltype(result)>::value, "type");
						TestCase::assert(result == true, "result");
					}),

				TestCase("swap lhs rhs", [] {
					UnorderedSetType<Key, Hash, Predicate, Allocator> lhs(INITIALIZER_LIST);
					UnorderedSetType<Key, Hash, Predicate, Allocator> rhs;
					swap(lhs, rhs);
					TestCase::assert(lhs.size() == 0, "lhs");
					TestCase::assert(rhs.size() == INITIALIZER_LIST.size(), "rhs");
				})})
	{
	}

	static const InitializerListType INITIALIZER_LIST;
	static const ArrayType ARRAY;
};

template<
	template<typename...> class UnorderedSetType,
	typename Key,
	bool isMultiset,
	typename Hash,
	typename Predicate,
	typename Allocator>
const typename UnorderedSetTestSuite<UnorderedSetType, Key, isMultiset, Hash, Predicate, Allocator>::InitializerListType
	UnorderedSetTestSuite<UnorderedSetType, Key, isMultiset, Hash, Predicate, Allocator>::INITIALIZER_LIST = {Key()};

template<
	template<typename...> class UnorderedSetType,
	typename Key,
	bool isMultiset,
	typename Hash,
	typename Predicate,
	typename Allocator>
const typename UnorderedSetTestSuite<UnorderedSetType, Key, isMultiset, Hash, Predicate, Allocator>::ArrayType
	UnorderedSetTestSuite<UnorderedSetType, Key, isMultiset, Hash, Predicate, Allocator>::ARRAY = {Key()};

} // namespace Testee

#endif // UnorderedSetTestSuite_INCLUDED
