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

/// Polymorphic decorator aggregating std::map<Key, T> with the sole purpose of adding a virtual destructor..
///
/// Classes derived from Polymorphic::Map<Key, T> can be safely used as targets of smart pointers.
/// Note: forwarding member functions are *not* declared virtual! They are not meant to be overriden
/// in subclasses. Add new behavior using new virtual members instead.
template< typename Key, typename T, typename Compare = std::less<Key>, typename Allocator = std::allocator< std::pair<const Key, T> > >
class Map
{
public:
	typedef Key key_type;	
	typedef T mapped_type;	
	typedef std::pair<const key_type, mapped_type> value_type;
	typedef Compare key_compare;
	typedef typename std::map<Key, T, Compare, Allocator>::value_compare value_compare;
	typedef Allocator allocator_type;
	typedef T& reference;	
	typedef const T& const_reference;	
	typedef typename std::map<Key, T, Compare, Allocator>::pointer pointer;
	typedef typename std::map<Key, T, Compare, Allocator>::const_pointer const_pointer ;
	typedef typename std::map<Key, T, Compare, Allocator>::iterator iterator;
	typedef typename std::map<Key, T, Compare, Allocator>::const_iterator const_iterator ;
	typedef typename std::map<Key, T, Compare, Allocator>::reverse_iterator reverse_iterator;
	typedef typename std::map<Key, T, Compare, Allocator>::const_reverse_iterator const_reverse_iterator;
	typedef typename std::map<Key, T, Compare, Allocator>::difference_type difference_type;
	typedef typename std::map<Key, T, Compare, Allocator>::size_type size_type;

	/// Forwarded to std::map<Key, T>::map(const key_compare& compare = key_compare(), const allocator_type& allocator = allocator_type()).
	explicit Map(const key_compare& compare = key_compare(), const allocator_type& allocator = allocator_type()) : delegate(compare, allocator)
	{
	}

	/// Forwarded to std::map<Key, T>::map(const allocator_type& alloc = allocator_type()).
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
	Map(const Map& other, const allocator_type& allocator = allocator_type()) : delegate(other.delegate, allocator)
	{
	}

	/// Move constructor.
	Map(Map&& other) : delegate(std::move(other.delegate))
	{
	}

	/// Move constructor.
	Map(Map&& other, const allocator_type& allocator = allocator_type()) :
			delegate(std::move(other.delegate), allocator)
	{
	}

	/// Forwarded to std::map<Key, T>::map(std::initializer_list<value_type> initializerList, const key_compare& compare = key_compare(), const allocator_type& allocator = allocator_type()).
	Map(std::initializer_list<value_type> initializerList, const key_compare& compare = key_compare(), const allocator_type& allocator = allocator_type()) : delegate(initializerList, compare, allocator)
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
	
	/// Forwarded to std::map<Key, T>::begin().
	iterator begin() noexcept
	{
		return delegate.begin();
	}
	
	/// Forwarded to std::map<Key, T>::begin() const.
	const_iterator begin() const noexcept
	{
		return delegate.begin();
	}

	/// Forwarded to std::map<Key, T>::end().
	iterator end() noexcept
	{
		return delegate.end();
	}
	
	/// Forwarded to std::map<Key, T>::end() const.
	const_iterator end() const noexcept
	{
		return delegate.end();
	}

	/// Forwarded to std::map<Key, T>::rbegin().
	reverse_iterator rbegin() noexcept
	{
		return delegate.rbegin();
	}
	
	/// Forwarded to std::map<Key, T>::rbegin() const.
	const_reverse_iterator rbegin() const noexcept
	{
		return delegate.rbegin();
	}

	/// Forwarded to std::map<Key, T>::rend().
	reverse_iterator rend() noexcept
	{
		return delegate.rend();
	}
	
	/// Forwarded to std::map<Key, T>::rend() const.
	const_reverse_iterator rend() const noexcept
	{
		return delegate.rend();
	}

	/// Forwarded to std::map<Key, T>::cbegin() const.
	const_iterator cbegin() const noexcept
	{
		return delegate.cbegin();
	}

	/// Forwarded to std::map<Key, T>::cend() const.
	const_iterator cend() const noexcept
	{
		return delegate.cend();
	}

	/// Forwarded to std::map<Key, T>::crbegin() const.
	const_reverse_iterator crbegin() const noexcept
	{
		return delegate.crbegin();
	}

	/// Forwarded to std::map<Key, T>::crend() const.
	const_reverse_iterator crend() const noexcept
	{
		return delegate.crend();
	}
	
	/// Forwarded to std::map<Key, T>::empty().
	bool empty() const noexcept
	{
		return delegate.empty();
	}
	
	/// Forwarded to std::map<Key, T>::size().
	size_type size() const noexcept
	{
		return delegate.size();
	}

	/// Forwarded to std::map<Key, T>::max_size().
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
	
	/// Forwarded to std::map<Key, T>::at(key_type&& key).
	const mapped_type& at(key_type&& key) const
	{
		return delegate.at(std::move(key));
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
	void swap(Map& other) {
		delegate.swap(other.map);
	}
	
	/// Forwarded to std::map<Key, T>::clear().
	void clear() noexcept {
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

	/// Forwarded to std::map<Key, T>::key_comp().
	key_compare key_comp() const
	{
		return delegate.key_comp();
	}

	/// Forwarded to std::map<Key, T>::value_comp().
	value_compare value_comp() const
	{
	}

	/// Forwarded to std::map<Key, T>::get_allocator() const noexcept.
	allocator_type get_allocator() const noexcept
	{
		return delegate.get_allocator();
	}
	
private:
	std::map<Key, T, Compare, Allocator> delegate;

	friend bool operator== <Key, T, Compare, Allocator> (const Map& lhs, const Map& rhs);
	friend bool operator!= <Key, T, Compare, Allocator> (const Map& lhs, const Map& rhs);
	friend bool operator<  <Key, T, Compare, Allocator> (const Map& lhs, const Map& rhs);
	friend bool operator<= <Key, T, Compare, Allocator> (const Map& lhs, const Map& rhs);
	friend bool operator>  <Key, T, Compare, Allocator> (const Map& lhs, const Map& rhs);
	friend bool operator>= <Key, T, Compare, Allocator> (const Map& lhs, const Map& rhs);
	friend void Polymorphic::swap<Key, T, Compare, Allocator>(const Map& lhs, const Map& rhs);
};

/// Forwarded to operator==(const std::map<Key, T, Compare, Allocator>& lhs, const std::map<Key, T, Compare, Allocator>& rhs).
template<typename Key, typename T, typename Compare, typename Allocator>
bool operator==(const Map<Key, T, Compare, Allocator>& lhs, const Map<Key, T, Compare, Allocator>& rhs)
{
	return lhs.map == rhs.map;
}

/// Forwarded to operator!=(const std::map<Key, T, Compare, Allocator>& lhs, const std::map<Key, T, Compare, Allocator>& rhs).
template<typename Key, typename T, typename Compare, typename Allocator>
bool operator!=(const Map<Key, T, Compare, Allocator>& lhs, const Map<Key, T, Compare, Allocator>& rhs)
{
	return lhs.map != rhs.map;
}

/// Forwarded to operator<(const std::map<Key, T, Compare, Allocator>& lhs, const std::map<Key, T, Compare, Allocator>& rhs).
template<typename Key, typename T, typename Compare, typename Allocator>
bool operator<(const Map<Key, T, Compare, Allocator>& lhs, const Map<Key, T, Compare, Allocator>& rhs)
{
	return lhs.map < rhs.map;
}

/// Forwarded to operator<=(const std::map<Key, T, Compare, Allocator>& lhs, const std::map<Key, T, Compare, Allocator>& rhs).
template<typename Key, typename T, typename Compare, typename Allocator>
bool operator<=(const Map<Key, T, Compare, Allocator>& lhs, const Map<Key, T, Compare, Allocator>& rhs)
{
	return lhs.map <= rhs.map;
}

/// Forwarded to operator>(const std::map<Key, T, Compare, Allocator>& lhs, const std::map<Key, T, Compare, Allocator>& rhs).
template<typename Key, typename T, typename Compare, typename Allocator>
bool operator>(const Map<Key, T, Compare, Allocator>& lhs, const Map<Key, T, Compare, Allocator>& rhs)
{
	return lhs.map > rhs.map;
}

/// Forwarded to operator>=(const std::map<Key, T, Compare, Allocator>& lhs, const std::map<Key, T, Compare, Allocator>& rhs).
template<typename Key, typename T, typename Compare, typename Allocator>
bool operator>=(const Map<Key, T, Compare, Allocator>& lhs, const Map<Key, T, Compare, Allocator>& rhs)
{
	return lhs.map >= rhs.map;
}

/// Forwarded to swap(const std::map<Key, T, Compare, Allocator>& lhs, const std::map<Key, T, Compare, Allocator>& rhs).
template<typename Key, typename T, typename Compare, typename Allocator>
void swap(const Map<Key, T, Compare, Allocator>& lhs, const Map<Key, T, Compare, Allocator>& rhs)
{
	swap(lhs.map, rhs.map);
}

} // namespace Polymorphic

#endif // Polymorphic_Map_INCLUDED
