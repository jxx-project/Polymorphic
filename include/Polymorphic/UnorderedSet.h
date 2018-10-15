//
// Copyright (C) 2018 Dr. Michael Steffens
//
// SPDX-License-Identifier:	BSL-1.0
//


#ifndef Polymorphic_UnorderedSet_INCLUDED
#define Polymorphic_UnorderedSet_INCLUDED

#include <unordered_set>

namespace Polymorphic {

template<typename Key, typename Hash, typename Predicate, typename Allocator>
class UnorderedSet;

template<typename Key, typename Hash, typename Predicate, typename Allocator>
bool operator==(
	const UnorderedSet<Key, Hash, Predicate, Allocator>& lhs,
	const UnorderedSet<Key, Hash, Predicate, Allocator>& rhs);

template<typename Key, typename Hash, typename Predicate, typename Allocator>
bool operator!=(
	const UnorderedSet<Key, Hash, Predicate, Allocator>& lhs,
	const UnorderedSet<Key, Hash, Predicate, Allocator>& rhs);

template<typename Key, typename Hash, typename Predicate, typename Allocator>
bool operator<(
	const UnorderedSet<Key, Hash, Predicate, Allocator>& lhs,
	const UnorderedSet<Key, Hash, Predicate, Allocator>& rhs);

template<typename Key, typename Hash, typename Predicate, typename Allocator>
bool operator<=(
	const UnorderedSet<Key, Hash, Predicate, Allocator>& lhs,
	const UnorderedSet<Key, Hash, Predicate, Allocator>& rhs);

template<typename Key, typename Hash, typename Predicate, typename Allocator>
bool operator>(
	const UnorderedSet<Key, Hash, Predicate, Allocator>& lhs,
	const UnorderedSet<Key, Hash, Predicate, Allocator>& rhs);

template<typename Key, typename Hash, typename Predicate, typename Allocator>
bool operator>=(
	const UnorderedSet<Key, Hash, Predicate, Allocator>& lhs,
	const UnorderedSet<Key, Hash, Predicate, Allocator>& rhs);

template<typename Key, typename Hash, typename Predicate, typename Allocator>
void swap(const UnorderedSet<Key, Hash, Predicate, Allocator>& lhs, const UnorderedSet<Key, Hash, Predicate, Allocator>& rhs);

/// Polymorphic decorator composing std::unordered_set<Key> with the sole purpose of adding a virtual destructor..
///
/// Classes derived from Polymorphic::UnorderedSet<Key> can be safely used as targets of smart pointers.
/// Note: forwarding member functions are *not* declared virtual! They are not meant to be overriden
/// in subclasses. Add new behavior using new virtual members instead.
template<
	typename Key,
	typename Hash = std::hash<Key>,
	typename Predicate = std::equal_to<Key>,
	typename Allocator = std::allocator<Key>>
class UnorderedSet
{
public:
	typedef std::unordered_set<Key, Hash, Predicate, Allocator> DelegateType;
	typedef Key key_type;
	typedef Key value_type;
	typedef Hash hasher;
	typedef Predicate key_equal;
	typedef Allocator allocator_type;
	typedef value_type& reference;
	typedef const value_type& const_reference;
	typedef typename DelegateType::pointer pointer;
	typedef typename DelegateType::const_pointer const_pointer;
	typedef typename DelegateType::iterator iterator;
	typedef typename DelegateType::const_iterator const_iterator;
	typedef typename DelegateType::local_iterator local_iterator;
	typedef typename DelegateType::const_local_iterator const_local_iterator;
	typedef typename DelegateType::difference_type difference_type;
	typedef typename DelegateType::size_type size_type;

	/// Forwarded to std::unordered_set<Key>::unordered_set() using default minInitialBuckets.
	UnorderedSet() : delegate()
	{
	}

	/// Forwarded to std::unordered_set<Key>::unordered_set(size_type minInitialBuckets, const hasher& hash = hasher(), const
	/// key_equal& predicate = key_equal(), const allocator_type& allocator = allocator_type()).
	explicit UnorderedSet(
		size_type minInitialBuckets,
		const hasher& hash = hasher(),
		const key_equal& predicate = key_equal(),
		const allocator_type& allocator = allocator_type()) :
		delegate(minInitialBuckets, hash, predicate, allocator)
	{
	}

	/// Forwarded to std::unordered_set<Key>::unordered_set(const allocator_type& alloc).
	explicit UnorderedSet(const allocator_type& allocator) : delegate(allocator)
	{
	}

	/// Forwarded to std::unordered_set<Key>::unordered_set(InputIterator first, InputIterator last) using default
	/// minInitialBuckets.
	template<typename InputIterator>
	UnorderedSet(InputIterator first, InputIterator last) : delegate(first, last)
	{
	}

	/// Forwarded to std::unordered_set<Key>::unordered_set(InputIterator first, InputIterator last, size_type minInitialBuckets,
	/// const hasher& hash = hasher(), const key_equal& predicate = key_equal(), const allocator_type& allocator =
	/// allocator_type()).
	template<typename InputIterator>
	UnorderedSet(
		InputIterator first,
		InputIterator last,
		size_type minInitialBuckets,
		const hasher& hash = hasher(),
		const key_equal& predicate = key_equal(),
		const allocator_type& allocator = allocator_type()) :
		delegate(first, last, minInitialBuckets, hash, predicate, allocator)
	{
	}

	/// Copy constructor.
	UnorderedSet(const UnorderedSet& other) : delegate(other.delegate)
	{
	}

	/// Copy constructor.
	UnorderedSet(const UnorderedSet& other, const allocator_type& allocator) : delegate(other.delegate, allocator)
	{
	}

	/// Move constructor.
	UnorderedSet(UnorderedSet&& other) : delegate(std::move(other.delegate))
	{
	}

	/// Move constructor.
	UnorderedSet(UnorderedSet&& other, const allocator_type& allocator) : delegate(std::move(other.delegate), allocator)
	{
	}

	/// Forwarded to std::unordered_set<Key>::unordered_set(std::initializer_list<value_type> initializerList) using default
	/// minInitialBuckets.
	UnorderedSet(std::initializer_list<value_type> initializerList) : delegate(initializerList)
	{
	}

	/// Forwarded to std::unordered_set<Key>::unordered_set(std::initializer_list<value_type> initializerList, size_type
	/// minInitialBuckets, const hasher& hash = hasher(), const key_equal& predicate = key_equal(), const allocator_type& allocator
	/// = allocator_type()).
	UnorderedSet(
		std::initializer_list<value_type> initializerList,
		size_type minInitialBuckets,
		const hasher& hash = hasher(),
		const key_equal& predicate = key_equal(),
		const allocator_type& allocator = allocator_type()) :
		delegate(initializerList, minInitialBuckets, hash, predicate, allocator)
	{
	}

	/// Copy construct from std::unordered_set<Key>.
	UnorderedSet(const DelegateType& other) : delegate(other)
	{
	}

	/// Copy construct from std::unordered_set<Key> with allocator.
	UnorderedSet(const DelegateType& other, const allocator_type& allocator) : delegate(other, allocator)
	{
	}

	/// Move construct from std::unordered_set<Key>.
	UnorderedSet(DelegateType&& other) : delegate(std::move(other))
	{
	}

	/// Move construct from std::unordered_set<Key> with allocator.
	UnorderedSet(DelegateType&& other, const allocator_type& allocator) : delegate(std::move(other), allocator)
	{
	}

	/// Virtual destructor permitting derived classes to be deleted safely via an UnorderedSet pointer.
	virtual ~UnorderedSet()
	{
	}

	/// Copy assignment operator
	UnorderedSet& operator=(const UnorderedSet& other)
	{
		delegate = other.delegate;
		return *this;
	}

	/// Move assignment operator
	UnorderedSet& operator=(UnorderedSet&& other)
	{
		delegate = std::move(other.delegate);
		return *this;
	}

	/// Initializer list assignment operator
	UnorderedSet& operator=(std::initializer_list<value_type> initializerList)
	{
		delegate = initializerList;
		return *this;
	}

	/// Copy assignment from std::unordered_set<Key>.
	UnorderedSet& operator=(const DelegateType& other)
	{
		delegate = other;
		return *this;
	}

	/// Move assignment from std::unordered_set<Key>.
	UnorderedSet& operator=(DelegateType&& other)
	{
		delegate = std::move(other);
		return *this;
	}

	/// Implicit type conversion into std::unordered_set<Key> reference.
	operator DelegateType&()
	{
		return delegate;
	}

	/// Implicit type conversion into const std::unordered_set<Key> reference.
	operator const DelegateType&() const
	{
		return delegate;
	}

	/// Explicit type conversion into std::unordered_set<Key> rvalue reference.
	explicit operator DelegateType &&()
	{
		return std::move(delegate);
	}

	/// Forwarded to std::unordered_set<Key>::begin() noexcept.
	iterator begin() noexcept
	{
		return delegate.begin();
	}

	/// Forwarded to std::unordered_set<Key>::begin() const noexcept.
	const_iterator begin() const noexcept
	{
		return delegate.begin();
	}

	/// Forwarded to std::unordered_set<Key>::end() noexcept.
	iterator end() noexcept
	{
		return delegate.end();
	}

	/// Forwarded to std::unordered_set<Key>::end() const noexcept.
	const_iterator end() const noexcept
	{
		return delegate.end();
	}

	/// Forwarded to std::unordered_set<Key>::cbegin() const noexcept.
	const_iterator cbegin() const noexcept
	{
		return delegate.cbegin();
	}

	/// Forwarded to std::unordered_set<Key>::cend() const noexcept.
	const_iterator cend() const noexcept
	{
		return delegate.cend();
	}

	/// Forwarded to std::unordered_set<Key>::empty() const noexcept.
	bool empty() const noexcept
	{
		return delegate.empty();
	}

	/// Forwarded to std::unordered_set<Key>::size() const noexcept.
	size_type size() const noexcept
	{
		return delegate.size();
	}

	/// Forwarded to std::unordered_set<Key>::max_size() const noexcept.
	size_type max_size() const noexcept
	{
		return delegate.max_size();
	}

	/// Forwarded to std::unordered_set<Key>::insert(const value_type& value).
	std::pair<iterator, bool> insert(const value_type& value)
	{
		return delegate.insert(value);
	}

	/// Forwarded to std::unordered_set<Key>::insert(value_type&& value).
	std::pair<iterator, bool> insert(value_type&& value)
	{
		return delegate.insert(std::move(value));
	}

	/// Forwarded to std::unordered_set<Key>::insert(const_iterator position, const value_type& value).
	iterator insert(const_iterator position, const value_type& value)
	{
		return delegate.insert(position, value);
	}

	/// Forwarded to std::unordered_set<Key>::insert(const_iterator position, value_type&& value).
	iterator insert(const_iterator position, value_type&& value)
	{
		return delegate.insert(position, std::move(value));
	}

	/// Forwarded to std::unordered_set<Key>::insert(InputIterator first, InputIterator last).
	template<typename InputIterator>
	void insert(InputIterator first, InputIterator last)
	{
		delegate.insert(first, last);
	}

	/// Forwarded to std::unordered_set<Key>::insert(std::initializer_list<value_type> initializerList).
	void insert(std::initializer_list<value_type> initializerList)
	{
		delegate.insert(initializerList);
	}

	/// Forwarded to std::unordered_set<Key>::erase(const_iterator position).
	iterator erase(const_iterator position)
	{
		return delegate.erase(position);
	}

	/// Forwarded to std::unordered_set<Key>::erase(const key_type& key).
	size_type erase(const key_type& key)
	{
		return delegate.erase(key);
	}

	/// Forwarded to std::unordered_set<Key>::erase(const_iterator first, const_iterator last).
	iterator erase(const_iterator first, const_iterator last)
	{
		return delegate.erase(first, last);
	}

	/// Forwarded to std::unordered_set<Key>::swap(std::unordered_set<bool>& other).
	void swap(UnorderedSet& other)
	{
		delegate.swap(other.delegate);
	}

	/// Forwarded to std::unordered_set<Key>::clear() noexcept.
	void clear() noexcept
	{
		delegate.clear();
	}

	/// Forwarded to std::unordered_set<Key>::emplace(const_iterator position, Args&&... args).
	template<typename... Args>
	std::pair<iterator, bool> emplace(Args&&... args)
	{
		return delegate.emplace(std::forward<Args>(args)...);
	}

	/// Forwarded to std::unordered_set<Key>::emplace_hint(const_iterator position, Args&&... args).
	template<typename... Args>
	iterator emplace_hint(const_iterator position, Args&&... args)
	{
		return delegate.emplace_hint(position, std::forward<Args>(args)...);
	}

	/// Forwarded to std::unordered_set<Key>::find(const key_type& key).
	iterator find(const key_type& key)
	{
		return delegate.find(key);
	}

	/// Forwarded to std::unordered_set<Key>::find(const key_type& key) const.
	const_iterator find(const key_type& key) const
	{
		return delegate.find(key);
	}

	/// Forwarded to std::unordered_set<Key>::count(const key_type& key) const.
	size_type count(const key_type& key) const
	{
		return delegate.count(key);
	}

	/// Forwarded to std::unordered_set<Key>::equal_range(const key_type& key).
	std::pair<iterator, iterator> equal_range(const key_type& key)
	{
		return delegate.equal_range(key);
	}

	/// Forwarded to std::unordered_set<Key>::equal_range(const key_type& key) const.
	std::pair<const_iterator, const_iterator> equal_range(const key_type& key) const
	{
		return delegate.equal_range(key);
	}

	/// Forwarded to std::unordered_set<Key>::bucket_count() const noexcept.
	size_type bucket_count() const noexcept
	{
		return delegate.bucket_count();
	}

	/// Forwarded to std::unordered_set<Key>::max_bucket_count() const noexcept.
	size_type max_bucket_count() const noexcept
	{
		return delegate.max_bucket_count();
	}

	/// Forwarded to std::unordered_set<Key>::bucket_size(size_type bucketNumber).
	size_type bucket_size(size_type bucketNumber) const
	{
		return delegate.bucket_size(bucketNumber);
	}

	/// Forwarded to std::unordered_set<Key>::bucket(const key_type& key) const.
	size_type bucket(const key_type& key) const
	{
		return delegate.bucket(key);
	}

	/// Forwarded to std::unordered_set<Key>::load_factor() const noexcept.
	float load_factor() const noexcept
	{
		return delegate.load_factor();
	}

	/// Forwarded to std::unordered_set<Key>::max_load_factor() const noexcept.
	float max_load_factor() const noexcept
	{
		return delegate.max_load_factor();
	}

	/// Forwarded to std::unordered_set<Key>::max_load_factor(float loadFactor).
	void max_load_factor(float loadFactor)
	{
		delegate.max_load_factor(loadFactor);
	}

	/// Forwarded to std::unordered_set<Key>::rehash(size_type n).
	void rehash(size_type n)
	{
		delegate.rehash(n);
	}

	/// Forwarded to std::unordered_set<Key>::reserve(size_type n).
	void reserve(size_type n)
	{
		delegate.reserve(n);
	}

	/// Forwarded to std::unordered_set<Key>::hash_function() const.
	hasher hash_function() const
	{
		return delegate.hash_function();
	}

	/// Forwarded to std::unordered_set<Key>::key_eq() const.
	key_equal key_eq() const
	{
		return delegate.key_eq();
	}

	/// Forwarded to std::unordered_set<Key>::get_allocator() const noexcept.
	allocator_type get_allocator() const noexcept
	{
		return delegate.get_allocator();
	}

private:
	DelegateType delegate;

	// clang-format off
	friend bool operator== <Key, Hash, Predicate, Allocator>(const UnorderedSet& lhs, const UnorderedSet& rhs);
	friend bool operator!= <Key, Hash, Predicate, Allocator>(const UnorderedSet& lhs, const UnorderedSet& rhs);
	friend bool operator< <Key, Hash, Predicate, Allocator>(const UnorderedSet& lhs, const UnorderedSet& rhs);
	friend bool operator<= <Key, Hash, Predicate, Allocator>(const UnorderedSet& lhs, const UnorderedSet& rhs);
	friend bool operator> <Key, Hash, Predicate, Allocator>(const UnorderedSet& lhs, const UnorderedSet& rhs);
	friend bool operator>= <Key, Hash, Predicate, Allocator>(const UnorderedSet& lhs, const UnorderedSet& rhs);
	// clang-format on
	friend void Polymorphic::swap<Key, Hash, Predicate, Allocator>(
		const UnorderedSet<Key, Hash, Predicate, Allocator>& lhs,
		const UnorderedSet<Key, Hash, Predicate, Allocator>& rhs);
};

/// Forwarded to operator==(const std::unordered_set<Key, Hash, Predicate, Allocator>& lhs, const std::unordered_set<Key,
/// Hash, Predicate, Allocator>& rhs).
template<typename Key, typename Hash, typename Predicate, typename Allocator>
bool operator==(
	const UnorderedSet<Key, Hash, Predicate, Allocator>& lhs,
	const UnorderedSet<Key, Hash, Predicate, Allocator>& rhs)
{
	return lhs.delegate == rhs.delegate;
}

/// Forwarded to operator!=(const std::unordered_set<Key, Hash, Predicate, Allocator>& lhs, const std::unordered_set<Key,
/// Hash, Predicate, Allocator>& rhs).
template<typename Key, typename Hash, typename Predicate, typename Allocator>
bool operator!=(
	const UnorderedSet<Key, Hash, Predicate, Allocator>& lhs,
	const UnorderedSet<Key, Hash, Predicate, Allocator>& rhs)
{
	return lhs.delegate != rhs.delegate;
}

/// Forwarded to operator<(const std::unordered_set<Key, Hash, Predicate, Allocator>& lhs, const std::unordered_set<Key, Hash,
/// Predicate, Allocator>& rhs).
template<typename Key, typename Hash, typename Predicate, typename Allocator>
bool operator<(
	const UnorderedSet<Key, Hash, Predicate, Allocator>& lhs,
	const UnorderedSet<Key, Hash, Predicate, Allocator>& rhs)
{
	return lhs.delegate < rhs.delegate;
}

/// Forwarded to operator<=(const std::unordered_set<Key, Hash, Predicate, Allocator>& lhs, const std::unordered_set<Key,
/// Hash, Predicate, Allocator>& rhs).
template<typename Key, typename Hash, typename Predicate, typename Allocator>
bool operator<=(
	const UnorderedSet<Key, Hash, Predicate, Allocator>& lhs,
	const UnorderedSet<Key, Hash, Predicate, Allocator>& rhs)
{
	return lhs.delegate <= rhs.delegate;
}

/// Forwarded to operator>(const std::unordered_set<Key, Hash, Predicate, Allocator>& lhs, const std::unordered_set<Key, Hash,
/// Predicate, Allocator>& rhs).
template<typename Key, typename Hash, typename Predicate, typename Allocator>
bool operator>(
	const UnorderedSet<Key, Hash, Predicate, Allocator>& lhs,
	const UnorderedSet<Key, Hash, Predicate, Allocator>& rhs)
{
	return lhs.delegate > rhs.delegate;
}

/// Forwarded to operator>=(const std::unordered_set<Key, Hash, Predicate, Allocator>& lhs, const std::unordered_set<Key,
/// Hash, Predicate, Allocator>& rhs).
template<typename Key, typename Hash, typename Predicate, typename Allocator>
bool operator>=(
	const UnorderedSet<Key, Hash, Predicate, Allocator>& lhs,
	const UnorderedSet<Key, Hash, Predicate, Allocator>& rhs)
{
	return lhs.delegate >= rhs.delegate;
}

/// Forwarded to swap(const std::unordered_set<Key, Hash, Predicate, Allocator>& lhs, const std::unordered_set<Key, Hash,
/// Predicate, Allocator>& rhs).
template<typename Key, typename Hash, typename Predicate, typename Allocator>
void swap(const UnorderedSet<Key, Hash, Predicate, Allocator>& lhs, const UnorderedSet<Key, Hash, Predicate, Allocator>& rhs)
{
	swap(lhs.delegate, rhs.delegate);
}

} // namespace Polymorphic

#endif // Polymorphic_UnorderedSet_INCLUDED
