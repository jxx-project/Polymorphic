//
// Copyright (C) 2018 Dr. Michael Steffens
//
// SPDX-License-Identifier:		BSL-1.0
//


#ifndef Polymorphic_UnorderedMultimap_INCLUDED
#define Polymorphic_UnorderedMultimap_INCLUDED

#include <unordered_map>

namespace Polymorphic {

template<typename Key, typename T, typename Hash, typename Predicate, typename Allocator>
class UnorderedMultimap;

template<typename Key, typename T, typename Hash, typename Predicate, typename Allocator>
bool operator==(const UnorderedMultimap<Key, T, Hash, Predicate, Allocator>& lhs, const UnorderedMultimap<Key, T, Hash, Predicate, Allocator>& rhs);

template<typename Key, typename T, typename Hash, typename Predicate, typename Allocator>
bool operator!=(const UnorderedMultimap<Key, T, Hash, Predicate, Allocator>& lhs, const UnorderedMultimap<Key, T, Hash, Predicate, Allocator>& rhs);

template<typename Key, typename T, typename Hash, typename Predicate, typename Allocator>
bool operator<(const UnorderedMultimap<Key, T, Hash, Predicate, Allocator>& lhs, const UnorderedMultimap<Key, T, Hash, Predicate, Allocator>& rhs);

template<typename Key, typename T, typename Hash, typename Predicate, typename Allocator>
bool operator<=(const UnorderedMultimap<Key, T, Hash, Predicate, Allocator>& lhs, const UnorderedMultimap<Key, T, Hash, Predicate, Allocator>& rhs);

template<typename Key, typename T, typename Hash, typename Predicate, typename Allocator>
bool operator>(const UnorderedMultimap<Key, T, Hash, Predicate, Allocator>& lhs, const UnorderedMultimap<Key, T, Hash, Predicate, Allocator>& rhs);

template<typename Key, typename T, typename Hash, typename Predicate, typename Allocator>
bool operator>=(const UnorderedMultimap<Key, T, Hash, Predicate, Allocator>& lhs, const UnorderedMultimap<Key, T, Hash, Predicate, Allocator>& rhs);

template<typename Key, typename T, typename Hash, typename Predicate, typename Allocator>
void swap(const UnorderedMultimap<Key, T, Hash, Predicate, Allocator>& lhs, const UnorderedMultimap<Key, T, Hash, Predicate, Allocator>& rhs);

/// Polymorphic decorator composing std::unordered_multimap<Key, T> with the sole purpose of adding a virtual destructor..
///
/// Classes derived from Polymorphic::UnorderedMultimap<Key, T> can be safely used as targets of smart pointers.
/// Note: forwarding member functions are *not* declared virtual! They are not meant to be overriden
/// in subclasses. Add new behavior using new virtual members instead.
template< typename Key, typename T, typename Hash = std::hash<Key>, typename Predicate = std::equal_to<Key>, typename Allocator = std::allocator< std::pair<const Key, T> > >
class UnorderedMultimap
{
public:
	typedef std::unordered_multimap<Key, T, Hash, Predicate, Allocator> DelegateType;
	typedef Key key_type;
	typedef T mapped_type;
	typedef std::pair<const key_type, mapped_type> value_type;
	typedef Hash hasher;
	typedef Predicate key_equal;
	typedef Allocator allocator_type;
	typedef value_type& reference;
	typedef const value_type& const_reference;
	typedef typename DelegateType::pointer pointer;
	typedef typename DelegateType::const_pointer const_pointer ;
	typedef typename DelegateType::iterator iterator;
	typedef typename DelegateType::const_iterator const_iterator ;
	typedef typename DelegateType::local_iterator local_iterator;
	typedef typename DelegateType::const_local_iterator const_local_iterator;
	typedef typename DelegateType::difference_type difference_type;
	typedef typename DelegateType::size_type size_type;

	/// Forwarded to std::unordered_multimap<Key, T>::unordered_multimap() using default minInitialBuckets.
	UnorderedMultimap() : delegate()
	{
	}

	/// Forwarded to std::unordered_multimap<Key, T>::unordered_multimap(size_type minInitialBuckets, const hasher& hash = hasher(), const key_equal& predicate = key_equal(), const allocator_type& allocator = allocator_type()).
	explicit UnorderedMultimap(size_type minInitialBuckets, const hasher& hash = hasher(), const key_equal& predicate = key_equal(), const allocator_type& allocator = allocator_type()) : delegate(minInitialBuckets, hash, predicate, allocator)
	{
	}

	/// Forwarded to std::unordered_multimap<Key, T>::unordered_multimap(const allocator_type& alloc).
	explicit UnorderedMultimap(const allocator_type& allocator) : delegate(allocator)
	{
	}

	/// Forwarded to std::unordered_multimap<Key, T>::unordered_multimap(InputIterator first, InputIterator last) using default minInitialBuckets.
	template<typename InputIterator>
	UnorderedMultimap(InputIterator first, InputIterator last) : delegate(first, last)
	{
	}

	/// Forwarded to std::unordered_multimap<Key, T>::unordered_multimap(InputIterator first, InputIterator last, size_type minInitialBuckets, const hasher& hash = hasher(), const key_equal& predicate = key_equal(), const allocator_type& allocator = allocator_type()).
	template<typename InputIterator>
	UnorderedMultimap(InputIterator first, InputIterator last, size_type minInitialBuckets, const hasher& hash = hasher(), const key_equal& predicate = key_equal(), const allocator_type& allocator = allocator_type()) : delegate(first, last, minInitialBuckets, hash, predicate, allocator)
	{
	}

	/// Copy constructor.
	UnorderedMultimap(const UnorderedMultimap& other) : delegate(other.delegate)
	{
	}

	/// Copy constructor.
	UnorderedMultimap(const UnorderedMultimap& other, const allocator_type& allocator) : delegate(other.delegate, allocator)
	{
	}

	/// Move constructor.
	UnorderedMultimap(UnorderedMultimap&& other) : delegate(std::move(other.delegate))
	{
	}

	/// Move constructor.
	UnorderedMultimap(UnorderedMultimap&& other, const allocator_type& allocator) : delegate(std::move(other.delegate), allocator)
	{
	}

	/// Forwarded to std::unordered_multimap<Key, T>::unordered_multimap(std::initializer_list<value_type> initializerList) using default minInitialBuckets.
	UnorderedMultimap(std::initializer_list<value_type> initializerList) : delegate(initializerList)
	{
	}

	/// Forwarded to std::unordered_multimap<Key, T>::unordered_multimap(std::initializer_list<value_type> initializerList, size_type minInitialBuckets, const hasher& hash = hasher(), const key_equal& predicate = key_equal(), const allocator_type& allocator = allocator_type()).
	UnorderedMultimap(std::initializer_list<value_type> initializerList, size_type minInitialBuckets, const hasher& hash = hasher(), const key_equal& predicate = key_equal(), const allocator_type& allocator = allocator_type()) : delegate(initializerList, minInitialBuckets, hash, predicate, allocator)
	{
	}

	/// Copy construct from std::unordered_multimap<T>.
	UnorderedMultimap(const DelegateType& other) : delegate(other)
	{
	}

	/// Copy construct from std::unordered_multimap<T> with allocator.
	UnorderedMultimap(const DelegateType& other, const allocator_type& allocator) : delegate(other, allocator)
	{
	}

	/// Move construct from std::unordered_multimap<T>.
	UnorderedMultimap(DelegateType&& other) : delegate(std::move(other))
	{
	}

	/// Move construct from std::unordered_multimap<T> with allocator.
	UnorderedMultimap(DelegateType&& other, const allocator_type& allocator) : delegate(std::move(other), allocator)
	{
	}

	/// Virtual destructor permitting derived classes to be deleted safely via an UnorderedMultimap pointer.
	virtual ~UnorderedMultimap()
	{
	}

	/// Copy assignment operator
	UnorderedMultimap& operator=(const UnorderedMultimap& other)
	{
		delegate = other.delegate;
		return *this;
	}

	/// Move assignment operator
	UnorderedMultimap& operator=(UnorderedMultimap&& other)
	{
		delegate = std::move(other.delegate);
		return *this;
	}

	/// Initializer list assignment operator
	UnorderedMultimap& operator=(std::initializer_list<value_type> initializerList)
	{
		delegate = initializerList;
		return *this;
	}

	/// Copy assignment from std::unordered_multimap<T>.
	UnorderedMultimap& operator=(const DelegateType& other)
	{
		delegate = other;
		return *this;
	}

	/// Move assignment from std::unordered_multimap<T>.
	UnorderedMultimap& operator=(DelegateType&& other)
	{
		delegate = std::move(other);
		return *this;
	}

	/// Implicit type conversion into std::unordered_multimap<T> reference.
	operator DelegateType&()
	{
		return delegate;
	}

	/// Implicit type conversion into const std::unordered_multimap<T> reference.
	operator const DelegateType&() const
	{
		return delegate;
	}

	/// Implicit type conversion into std::unordered_multimap<T> rvalue reference.
	operator DelegateType&&()
	{
		return std::move(delegate);
	}

	/// Forwarded to std::unordered_multimap<Key, T>::begin().
	iterator begin() noexcept
	{
		return delegate.begin();
	}

	/// Forwarded to std::unordered_multimap<Key, T>::begin() const.
	const_iterator begin() const noexcept
	{
		return delegate.begin();
	}

	/// Forwarded to std::unordered_multimap<Key, T>::end().
	iterator end() noexcept
	{
		return delegate.end();
	}

	/// Forwarded to std::unordered_multimap<Key, T>::end() const.
	const_iterator end() const noexcept
	{
		return delegate.end();
	}

	/// Forwarded to std::unordered_multimap<Key, T>::cbegin() const.
	const_iterator cbegin() const noexcept
	{
		return delegate.cbegin();
	}

	/// Forwarded to std::unordered_multimap<Key, T>::cend() const.
	const_iterator cend() const noexcept
	{
		return delegate.cend();
	}

	/// Forwarded to std::unordered_multimap<Key, T>::empty().
	bool empty() const noexcept
	{
		return delegate.empty();
	}

	/// Forwarded to std::unordered_multimap<Key, T>::size().
	size_type size() const noexcept
	{
		return delegate.size();
	}

	/// Forwarded to std::unordered_multimap<Key, T>::max_size().
	size_type max_size() const noexcept
	{
		return delegate.max_size();
	}

	/// Forwarded to std::unordered_multimap<Key, T>::insert(const value_type& value).
	std::pair<iterator, bool> insert(const value_type& value)
	{
		return delegate.insert(value);
	}

	/// Forwarded to std::unordered_multimap<Key, T>::insert(Pair&& value).
	template<typename Pair>
	iterator insert(Pair&& value)
	{
		return delegate.insert(std::move(value));
	}

	/// Forwarded to std::unordered_multimap<Key, T>::insert(const_iterator position, const value_type& value).
	iterator insert(const_iterator position, const value_type& value)
	{
		return delegate.insert(position, value);
	}

	/// Forwarded to std::unordered_multimap<Key, T>::insert(const_iterator position, Pair&& value).
	template<typename Pair>
	iterator insert(const_iterator position, Pair&& value)
	{
		return delegate.insert(position, std::move(value));
	}

	/// Forwarded to std::unordered_multimap<Key, T>::insert(InputIterator first, InputIterator last).
	template<typename InputIterator>
	void insert(InputIterator first, InputIterator last)
	{
		delegate.insert(first, last);
	}

	/// Forwarded to std::unordered_multimap<Key, T>::insert(std::initializer_list<value_type> initializerList).
	void insert(std::initializer_list<value_type> initializerList)
	{
		delegate.insert(initializerList);
	}

	/// Forwarded to std::unordered_multimap<Key, T>::erase(const_iterator position).
	iterator erase(const_iterator position)
	{
		return delegate.erase(position);
	}

	/// Forwarded to std::unordered_multimap<Key, T>::erase(const key_type& key).
	size_type erase(const key_type& key)
	{
		return delegate.erase(key);
	}

	/// Forwarded to std::unordered_multimap<Key, T>::erase(const_iterator first, const_iterator last).
	iterator erase(const_iterator first, const_iterator last)
	{
		return delegate.erase(first, last);
	}

	/// Forwarded to std::unordered_multimap<Key, T>::swap(std::unordered_multimap<bool>& other).
	void swap(UnorderedMultimap& other) {
		delegate.swap(other.delegate);
	}

	/// Forwarded to std::unordered_multimap<Key, T>::clear().
	void clear() noexcept {
		delegate.clear();
	}

	/// Forwarded to std::unordered_multimap<Key, T>::emplace(const_iterator position, Args&&... args).
	template<typename... Args>
	iterator emplace(Args&&... args)
	{
		return delegate.emplace(std::forward<Args>(args)...);
	}

	/// Forwarded to std::unordered_multimap<Key, T>::emplace_hint(const_iterator position, Args&&... args).
	template<typename... Args>
	iterator emplace_hint(const_iterator position, Args&&... args)
	{
		return delegate.emplace_hint(position, std::forward<Args>(args)...);
	}

	/// Forwarded to std::unordered_multimap<Key, T>::find(const key_type& key).
	iterator find(const key_type& key)
	{
		return delegate.find(key);
	}

	/// Forwarded to std::unordered_multimap<Key, T>::find(const key_type& key) const.
	const_iterator find(const key_type& key) const
	{
		return delegate.find(key);
	}

	/// Forwarded to std::unordered_multimap<Key, T>::count(const key_type& key) const.
	size_type count(const key_type& key) const
	{
		return delegate.count(key);
	}

	/// Forwarded to std::unordered_multimap<Key, T>::equal_range(const key_type& key).
	std::pair<iterator, iterator> equal_range(const key_type& key)
	{
		return delegate.equal_range(key);
	}

	/// Forwarded to std::unordered_multimap<Key, T>::equal_range(const key_type& key) const.
	std::pair<const_iterator, const_iterator> equal_range(const key_type& key) const
	{
		return delegate.equal_range(key);
	}

	/// Forwarded to std::unordered_multimap<Key, T>::bucket_count().
	size_type bucket_count() const noexcept
	{
		return delegate.bucket_count();
	}

	/// Forwarded to std::unordered_multimap<Key, T>::max_bucket_count().
	size_type max_bucket_count() const noexcept
	{
		return delegate.max_bucket_count();
	}

	/// Forwarded to std::unordered_multimap<Key, T>::bucket_size(size_type bucketNumber).
	size_type bucket_size(size_type bucketNumber) const
	{
		return delegate.bucket_size(bucketNumber);
	}

	/// Forwarded to std::unordered_multimap<Key, T>::bucket(const key_type& key) const.
	size_type bucket(const key_type& key) const
	{
		return delegate.bucket(key);
	}

	/// Forwarded to std::unordered_multimap<Key, T>::load_factor().
	float load_factor() const noexcept
	{
		return delegate.load_factor();
	}

	/// Forwarded to std::unordered_multimap<Key, T>::max_load_factor().
	float max_load_factor() const noexcept
	{
		return delegate.max_load_factor();
	}

	/// Forwarded to std::unordered_multimap<Key, T>::max_load_factor(float loadFactor).
	void max_load_factor(float loadFactor)
	{
		delegate.max_load_factor(loadFactor);
	}

	/// Forwarded to std::unordered_multimap<Key, T>::rehash(size_type n).
	void rehash(size_type n)
	{
		delegate.rehash(n);
	}

	/// Forwarded to std::unordered_multimap<Key, T>::reserve(size_type n).
	void reserve(size_type n)
	{
		delegate.reserve(n);
	}

	/// Forwarded to std::unordered_multimap<Key, T>::hash_function().
	hasher hash_function() const
	{
		return delegate.hash_function();
	}

	/// Forwarded to std::unordered_multimap<Key, T>::key_eq().
	key_equal key_eq() const
	{
		return delegate.key_eq();
	}

	/// Forwarded to std::unordered_multimap<Key, T>::get_allocator() const noexcept.
	allocator_type get_allocator() const noexcept
	{
		return delegate.get_allocator();
	}

private:
	DelegateType delegate;

	friend bool operator== <Key, T, Hash, Predicate, Allocator> (const UnorderedMultimap& lhs, const UnorderedMultimap& rhs);
	friend bool operator!= <Key, T, Hash, Predicate, Allocator> (const UnorderedMultimap& lhs, const UnorderedMultimap& rhs);
	friend bool operator<  <Key, T, Hash, Predicate, Allocator> (const UnorderedMultimap& lhs, const UnorderedMultimap& rhs);
	friend bool operator<= <Key, T, Hash, Predicate, Allocator> (const UnorderedMultimap& lhs, const UnorderedMultimap& rhs);
	friend bool operator>  <Key, T, Hash, Predicate, Allocator> (const UnorderedMultimap& lhs, const UnorderedMultimap& rhs);
	friend bool operator>= <Key, T, Hash, Predicate, Allocator> (const UnorderedMultimap& lhs, const UnorderedMultimap& rhs);
	friend void Polymorphic::swap<Key, T, Hash, Predicate, Allocator>(const UnorderedMultimap& lhs, const UnorderedMultimap& rhs);
};

/// Forwarded to operator==(const std::unordered_multimap<Key, T, Hash, Predicate, Allocator>& lhs, const std::unordered_multimap<Key, T, Hash, Predicate, Allocator>& rhs).
template<typename Key, typename T, typename Hash, typename Predicate, typename Allocator>
bool operator==(const UnorderedMultimap<Key, T, Hash, Predicate, Allocator>& lhs, const UnorderedMultimap<Key, T, Hash, Predicate, Allocator>& rhs)
{
	return lhs.delegate == rhs.delegate;
}

/// Forwarded to operator!=(const std::unordered_multimap<Key, T, Hash, Predicate, Allocator>& lhs, const std::unordered_multimap<Key, T, Hash, Predicate, Allocator>& rhs).
template<typename Key, typename T, typename Hash, typename Predicate, typename Allocator>
bool operator!=(const UnorderedMultimap<Key, T, Hash, Predicate, Allocator>& lhs, const UnorderedMultimap<Key, T, Hash, Predicate, Allocator>& rhs)
{
	return lhs.delegate != rhs.delegate;
}

/// Forwarded to operator<(const std::unordered_multimap<Key, T, Hash, Predicate, Allocator>& lhs, const std::unordered_multimap<Key, T, Hash, Predicate, Allocator>& rhs).
template<typename Key, typename T, typename Hash, typename Predicate, typename Allocator>
bool operator<(const UnorderedMultimap<Key, T, Hash, Predicate, Allocator>& lhs, const UnorderedMultimap<Key, T, Hash, Predicate, Allocator>& rhs)
{
	return lhs.delegate < rhs.delegate;
}

/// Forwarded to operator<=(const std::unordered_multimap<Key, T, Hash, Predicate, Allocator>& lhs, const std::unordered_multimap<Key, T, Hash, Predicate, Allocator>& rhs).
template<typename Key, typename T, typename Hash, typename Predicate, typename Allocator>
bool operator<=(const UnorderedMultimap<Key, T, Hash, Predicate, Allocator>& lhs, const UnorderedMultimap<Key, T, Hash, Predicate, Allocator>& rhs)
{
	return lhs.delegate <= rhs.delegate;
}

/// Forwarded to operator>(const std::unordered_multimap<Key, T, Hash, Predicate, Allocator>& lhs, const std::unordered_multimap<Key, T, Hash, Predicate, Allocator>& rhs).
template<typename Key, typename T, typename Hash, typename Predicate, typename Allocator>
bool operator>(const UnorderedMultimap<Key, T, Hash, Predicate, Allocator>& lhs, const UnorderedMultimap<Key, T, Hash, Predicate, Allocator>& rhs)
{
	return lhs.delegate > rhs.delegate;
}

/// Forwarded to operator>=(const std::unordered_multimap<Key, T, Hash, Predicate, Allocator>& lhs, const std::unordered_multimap<Key, T, Hash, Predicate, Allocator>& rhs).
template<typename Key, typename T, typename Hash, typename Predicate, typename Allocator>
bool operator>=(const UnorderedMultimap<Key, T, Hash, Predicate, Allocator>& lhs, const UnorderedMultimap<Key, T, Hash, Predicate, Allocator>& rhs)
{
	return lhs.delegate >= rhs.delegate;
}

/// Forwarded to swap(const std::unordered_multimap<Key, T, Hash, Predicate, Allocator>& lhs, const std::unordered_multimap<Key, T, Hash, Predicate, Allocator>& rhs).
template<typename Key, typename T, typename Hash, typename Predicate, typename Allocator>
void swap(const UnorderedMultimap<Key, T, Hash, Predicate, Allocator>& lhs, const UnorderedMultimap<Key, T, Hash, Predicate, Allocator>& rhs)
{
	swap(lhs.delegate, rhs.delegate);
}

} // namespace Polymorphic

#endif // Polymorphic_UnorderedMultimap_INCLUDED
