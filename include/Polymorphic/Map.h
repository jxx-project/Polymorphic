//
// Copyright (C) 2018 Dr. Michael Steffens
//
// SPDX-License-Identifier:		BSL-1.0
//


#ifndef Polymorphic_Map_INCLUDED
#define Polymorphic_Map_INCLUDED

#include <map>

namespace Polymorphic {

template<typename Key, typename T, typename Compare, typename Allocator>
class Map;

template<typename Key, typename T, typename Compare, typename Allocator>
bool operator==(const Map<Key, T, Compare, Allocator>& lhs, const Map<Key, T, Compare, Allocator>& rhs);

template<typename Key, typename T, typename Compare, typename Allocator>
bool operator!=(const Map<Key, T, Compare, Allocator>& lhs, const Map<Key, T, Compare, Allocator>& rhs);

template<typename Key, typename T, typename Compare, typename Allocator>
bool operator<(const Map<Key, T, Compare, Allocator>& lhs, const Map<Key, T, Compare, Allocator>& rhs);

template<typename Key, typename T, typename Compare, typename Allocator>
bool operator<=(const Map<Key, T, Compare, Allocator>& lhs, const Map<Key, T, Compare, Allocator>& rhs);

template<typename Key, typename T, typename Compare, typename Allocator>
bool operator>(const Map<Key, T, Compare, Allocator>& lhs, const Map<Key, T, Compare, Allocator>& rhs);

template<typename Key, typename T, typename Compare, typename Allocator>
bool operator>=(const Map<Key, T, Compare, Allocator>& lhs, const Map<Key, T, Compare, Allocator>& rhs);

template<typename Key, typename T, typename Compare, typename Allocator>
void swap(const Map<Key, T, Compare, Allocator>& lhs, const Map<Key, T, Compare, Allocator>& rhs);

/// Polymorphic decorator composing std::map<Key, T> with the sole purpose of adding a virtual destructor..
///
/// Classes derived from Polymorphic::Map<Key, T> can be safely used as targets of smart pointers.
/// Note: forwarding member functions are *not* declared virtual! They are not meant to be overriden
/// in subclasses. Add new behavior using new virtual members instead.
template< typename Key, typename T, typename Compare = std::less<Key>, typename Allocator = std::allocator< std::pair<const Key, T> > >
class Map
{
public:
	typedef std::map<Key, T, Compare, Allocator> DelegateType;
	typedef Key key_type;
	typedef T mapped_type;
	typedef std::pair<const key_type, mapped_type> value_type;
	typedef Compare key_compare;
	typedef typename DelegateType::value_compare value_compare;
	typedef Allocator allocator_type;
	typedef value_type& reference;
	typedef const value_type& const_reference;
	typedef typename DelegateType::pointer pointer;
	typedef typename DelegateType::const_pointer const_pointer ;
	typedef typename DelegateType::iterator iterator;
	typedef typename DelegateType::const_iterator const_iterator ;
	typedef typename DelegateType::reverse_iterator reverse_iterator;
	typedef typename DelegateType::const_reverse_iterator const_reverse_iterator;
	typedef typename DelegateType::difference_type difference_type;
	typedef typename DelegateType::size_type size_type;

	/// Forwarded to std::map<Key, T>::map(const key_compare& compare = key_compare(), const allocator_type& allocator = allocator_type()).
	explicit Map(const key_compare& compare = key_compare(), const allocator_type& allocator = allocator_type()) : delegate(compare, allocator)
	{
	}

	/// Forwarded to std::map<Key, T>::map(const allocator_type& alloc).
	explicit Map(const allocator_type& allocator) : delegate(allocator)
	{
	}

	/// Forwarded to std::map<Key, T>::map(InputIterator first, InputIterator last, const key_compare& compare = key_compare(), const allocator_type& allocator = allocator_type()).
	template<typename InputIterator>
	Map(InputIterator first, InputIterator last, const key_compare& compare = key_compare(), const allocator_type& allocator = allocator_type()) : delegate(first, last, compare, allocator)
	{
	}

	/// Copy constructor.
	Map(const Map& other) : delegate(other.delegate)
	{
	}

	/// Copy constructor.
	Map(const Map& other, const allocator_type& allocator) : delegate(other.delegate, allocator)
	{
	}

	/// Move constructor.
	Map(Map&& other) : delegate(std::move(other.delegate))
	{
	}

	/// Move constructor.
	Map(Map&& other, const allocator_type& allocator) : delegate(std::move(other.delegate), allocator)
	{
	}

	/// Forwarded to std::map<Key, T>::map(std::initializer_list<value_type> initializerList, const key_compare& compare = key_compare(), const allocator_type& allocator = allocator_type()).
	Map(std::initializer_list<value_type> initializerList, const key_compare& compare = key_compare(), const allocator_type& allocator = allocator_type()) : delegate(initializerList, compare, allocator)
	{
	}

	/// Copy construct from std::map<T>.
	Map(const DelegateType& other) : delegate(other)
	{
	}

	/// Copy construct from std::map<T> with allocator.
	Map(const DelegateType& other, const allocator_type& allocator) : delegate(other, allocator)
	{
	}

	/// Move construct from std::map<T>.
	Map(DelegateType&& other) : delegate(std::move(other))
	{
	}

	/// Move construct from std::map<T> with allocator.
	Map(DelegateType&& other, const allocator_type& allocator) : delegate(std::move(other), allocator)
	{
	}

	/// Virtual destructor permitting derived classes to be deleted safely via a Map pointer.
	virtual ~Map()
	{
	}

	/// Copy assignment operator
	Map& operator=(const Map& other)
	{
		delegate = other.delegate;
		return *this;
	}

	/// Move assignment operator
	Map& operator=(Map&& other)
	{
		delegate = std::move(other.delegate);
		return *this;
	}

	/// Initializer list assignment operator
	Map& operator=(std::initializer_list<value_type> initializerList)
	{
		delegate = initializerList;
		return *this;
	}

	/// Copy assignment from std::map<T>.
	Map& operator=(const DelegateType& other)
	{
		delegate = other;
		return *this;
	}

	/// Move assignment from std::map<T>.
	Map& operator=(DelegateType&& other)
	{
		delegate = std::move(other);
		return *this;
	}

	/// Implicit type conversion into std::map<T> reference.
	operator DelegateType&()
	{
		return delegate;
	}

	/// Implicit type conversion into const std::map<T> reference.
	operator const DelegateType&() const
	{
		return delegate;
	}

	/// Explicit type conversion into std::map<T> rvalue reference.
	explicit operator DelegateType&&()
	{
		return std::move(delegate);
	}

	/// Forwarded to std::map<Key, T>::begin() noexcept.
	iterator begin() noexcept
	{
		return delegate.begin();
	}

	/// Forwarded to std::map<Key, T>::begin() const noexcept.
	const_iterator begin() const noexcept
	{
		return delegate.begin();
	}

	/// Forwarded to std::map<Key, T>::end() noexcept.
	iterator end() noexcept
	{
		return delegate.end();
	}

	/// Forwarded to std::map<Key, T>::end() const noexcept.
	const_iterator end() const noexcept
	{
		return delegate.end();
	}

	/// Forwarded to std::map<Key, T>::rbegin() noexcept.
	reverse_iterator rbegin() noexcept
	{
		return delegate.rbegin();
	}

	/// Forwarded to std::map<Key, T>::rbegin() const noexcept.
	const_reverse_iterator rbegin() const noexcept
	{
		return delegate.rbegin();
	}

	/// Forwarded to std::map<Key, T>::rend() noexcept.
	reverse_iterator rend() noexcept
	{
		return delegate.rend();
	}

	/// Forwarded to std::map<Key, T>::rend() const noexcept.
	const_reverse_iterator rend() const noexcept
	{
		return delegate.rend();
	}

	/// Forwarded to std::map<Key, T>::cbegin() const noexcept.
	const_iterator cbegin() const noexcept
	{
		return delegate.cbegin();
	}

	/// Forwarded to std::map<Key, T>::cend() const noexcept.
	const_iterator cend() const noexcept
	{
		return delegate.cend();
	}

	/// Forwarded to std::map<Key, T>::crbegin() const noexcept.
	const_reverse_iterator crbegin() const noexcept
	{
		return delegate.crbegin();
	}

	/// Forwarded to std::map<Key, T>::crend() const noexcept.
	const_reverse_iterator crend() const noexcept
	{
		return delegate.crend();
	}

	/// Forwarded to std::map<Key, T>::empty() const noexcept.
	bool empty() const noexcept
	{
		return delegate.empty();
	}

	/// Forwarded to std::map<Key, T>::size() const noexcept.
	size_type size() const noexcept
	{
		return delegate.size();
	}

	/// Forwarded to std::map<Key, T>::max_size() const noexcept.
	size_type max_size() const noexcept
	{
		return delegate.max_size();
	}

	/// Forwarded to std::map<Key, T>::operator[](const key_type& key).
	mapped_type& operator[](const key_type& key)
	{
		return delegate[key];
	}

	/// Forwarded to std::map<Key, T>::operator[](key_type&& key).
	mapped_type& operator[](key_type&& key)
	{
		return delegate[std::move(key)];
	}

	/// Forwarded to std::map<Key, T>::at(const key_type& key).
	mapped_type& at(const key_type& key)
	{
		return delegate.at(key);
	}

	/// Forwarded to std::map<Key, T>::at(const key_type& key) const.
	const mapped_type& at(const key_type& key) const
	{
		return delegate.at(key);
	}

	/// Forwarded to std::map<Key, T>::insert(const value_type& value).
	std::pair<iterator, bool> insert(const value_type& value)
	{
		return delegate.insert(value);
	}

	/// Forwarded to std::map<Key, T>::insert(Pair&& value).
	template<typename Pair>
	std::pair<iterator, bool> insert(Pair&& value)
	{
		return delegate.insert(std::move(value));
	}

	/// Forwarded to std::map<Key, T>::insert(const_iterator position, const value_type& value).
	iterator insert(const_iterator position, const value_type& value)
	{
		return delegate.insert(position, value);
	}

	/// Forwarded to std::map<Key, T>::insert(const_iterator position, Pair&& value).
	template<typename Pair>
	iterator insert(const_iterator position, Pair&& value)
	{
		return delegate.insert(position, std::move(value));
	}

	/// Forwarded to std::map<Key, T>::insert(InputIterator first, InputIterator last).
	template<typename InputIterator>
	void insert(InputIterator first, InputIterator last)
	{
		delegate.insert(first, last);
	}

	/// Forwarded to std::map<Key, T>::insert(std::initializer_list<value_type> initializerList).
	void insert(std::initializer_list<value_type> initializerList)
	{
		delegate.insert(initializerList);
	}

	/// Forwarded to std::map<Key, T>::erase(const_iterator position).
	iterator erase(const_iterator position)
	{
		return delegate.erase(position);
	}

	/// Forwarded to std::map<Key, T>::erase(const key_type& key).
	size_type erase(const key_type& key)
	{
		return delegate.erase(key);
	}

	/// Forwarded to std::map<Key, T>::erase(const_iterator first, const_iterator last).
	iterator erase(const_iterator first, const_iterator last)
	{
		return delegate.erase(first, last);
	}

	/// Forwarded to std::map<Key, T>::swap(std::map<bool>& other).
	void swap(Map& other)
	{
		delegate.swap(other.delegate);
	}

	/// Forwarded to std::map<Key, T>::clear() noexcept.
	void clear() noexcept
	{
		delegate.clear();
	}

	/// Forwarded to std::map<Key, T>::emplace(const_iterator position, Args&&... args).
	template<typename... Args>
	std::pair<iterator, bool> emplace(Args&&... args)
	{
		return delegate.emplace(std::forward<Args>(args)...);
	}

	/// Forwarded to std::map<Key, T>::emplace_hint(const_iterator position, Args&&... args).
	template<typename... Args>
	iterator emplace_hint(const_iterator position, Args&&... args)
	{
		return delegate.emplace_hint(position, std::forward<Args>(args)...);
	}

	/// Forwarded to std::map<Key, T>::find(const key_type& key).
	iterator find(const key_type& key)
	{
		return delegate.find(key);
	}

	/// Forwarded to std::map<Key, T>::find(const key_type& key) const.
	const_iterator find(const key_type& key) const
	{
		return delegate.find(key);
	}

	/// Forwarded to std::map<Key, T>::count(const key_type& key) const.
	size_type count(const key_type& key) const
	{
		return delegate.count(key);
	}

	/// Forwarded to std::map<Key, T>::lower_bound(const key_type& key).
	iterator lower_bound(const key_type& key)
	{
		return delegate.lower_bound(key);
	}

	/// Forwarded to std::map<Key, T>::lower_bound(const key_type& key) const.
	const_iterator lower_bound(const key_type& key) const
	{
		return delegate.lower_bound(key);
	}

	/// Forwarded to std::map<Key, T>::upper_bound(const key_type& key).
	iterator upper_bound(const key_type& key)
	{
		return delegate.upper_bound(key);
	}

	/// Forwarded to std::map<Key, T>::upper_bound(const key_type& key) const.
	const_iterator upper_bound(const key_type& key) const
	{
		return delegate.upper_bound(key);
	}

	/// Forwarded to std::map<Key, T>::equal_range(const key_type& key).
	std::pair<iterator, iterator> equal_range(const key_type& key)
	{
		return delegate.equal_range(key);
	}

	/// Forwarded to std::map<Key, T>::equal_range(const key_type& key) const.
	std::pair<const_iterator, const_iterator> equal_range(const key_type& key) const
	{
		return delegate.equal_range(key);
	}

	/// Forwarded to std::map<Key, T>::key_comp() const.
	key_compare key_comp() const
	{
		return delegate.key_comp();
	}

	/// Forwarded to std::map<Key, T>::value_comp() const.
	value_compare value_comp() const
	{
		return delegate.value_comp();
	}

	/// Forwarded to std::map<Key, T>::get_allocator() const noexcept.
	allocator_type get_allocator() const noexcept
	{
		return delegate.get_allocator();
	}

private:
	DelegateType delegate;

	friend bool operator== <Key, T, Compare, Allocator> (const Map& lhs, const Map& rhs);
	friend bool operator!= <Key, T, Compare, Allocator> (const Map& lhs, const Map& rhs);
	friend bool operator<  <Key, T, Compare, Allocator> (const Map& lhs, const Map& rhs);
	friend bool operator<= <Key, T, Compare, Allocator> (const Map& lhs, const Map& rhs);
	friend bool operator>  <Key, T, Compare, Allocator> (const Map& lhs, const Map& rhs);
	friend bool operator>= <Key, T, Compare, Allocator> (const Map& lhs, const Map& rhs);
	friend void Polymorphic::swap<Key, T, Compare, Allocator>(const Map<Key, T, Compare, Allocator>& lhs, const Map<Key, T, Compare, Allocator>& rhs);
};

/// Forwarded to operator==(const std::map<Key, T, Compare, Allocator>& lhs, const std::map<Key, T, Compare, Allocator>& rhs).
template<typename Key, typename T, typename Compare, typename Allocator>
bool operator==(const Map<Key, T, Compare, Allocator>& lhs, const Map<Key, T, Compare, Allocator>& rhs)
{
	return lhs.delegate == rhs.delegate;
}

/// Forwarded to operator!=(const std::map<Key, T, Compare, Allocator>& lhs, const std::map<Key, T, Compare, Allocator>& rhs).
template<typename Key, typename T, typename Compare, typename Allocator>
bool operator!=(const Map<Key, T, Compare, Allocator>& lhs, const Map<Key, T, Compare, Allocator>& rhs)
{
	return lhs.delegate != rhs.delegate;
}

/// Forwarded to operator<(const std::map<Key, T, Compare, Allocator>& lhs, const std::map<Key, T, Compare, Allocator>& rhs).
template<typename Key, typename T, typename Compare, typename Allocator>
bool operator<(const Map<Key, T, Compare, Allocator>& lhs, const Map<Key, T, Compare, Allocator>& rhs)
{
	return lhs.delegate < rhs.delegate;
}

/// Forwarded to operator<=(const std::map<Key, T, Compare, Allocator>& lhs, const std::map<Key, T, Compare, Allocator>& rhs).
template<typename Key, typename T, typename Compare, typename Allocator>
bool operator<=(const Map<Key, T, Compare, Allocator>& lhs, const Map<Key, T, Compare, Allocator>& rhs)
{
	return lhs.delegate <= rhs.delegate;
}

/// Forwarded to operator>(const std::map<Key, T, Compare, Allocator>& lhs, const std::map<Key, T, Compare, Allocator>& rhs).
template<typename Key, typename T, typename Compare, typename Allocator>
bool operator>(const Map<Key, T, Compare, Allocator>& lhs, const Map<Key, T, Compare, Allocator>& rhs)
{
	return lhs.delegate > rhs.delegate;
}

/// Forwarded to operator>=(const std::map<Key, T, Compare, Allocator>& lhs, const std::map<Key, T, Compare, Allocator>& rhs).
template<typename Key, typename T, typename Compare, typename Allocator>
bool operator>=(const Map<Key, T, Compare, Allocator>& lhs, const Map<Key, T, Compare, Allocator>& rhs)
{
	return lhs.delegate >= rhs.delegate;
}

/// Forwarded to swap(const std::map<Key, T, Compare, Allocator>& lhs, const std::map<Key, T, Compare, Allocator>& rhs).
template<typename Key, typename T, typename Compare, typename Allocator>
void swap(const Map<Key, T, Compare, Allocator>& lhs, const Map<Key, T, Compare, Allocator>& rhs)
{
	swap(lhs.delegate, rhs.delegate);
}

} // namespace Polymorphic

#endif // Polymorphic_Map_INCLUDED
