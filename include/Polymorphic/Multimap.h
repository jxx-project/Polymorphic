//
// Copyright (C) 2018 Dr. Michael Steffens
//
// SPDX-License-Identifier:		BSL-1.0
//


#ifndef Polymorphic_Multimap_INCLUDED
#define Polymorphic_Multimap_INCLUDED

#include <map>

namespace Polymorphic {

template<typename Key, typename T, typename Compare, typename Allocator>
class Multimap;

template<typename Key, typename T, typename Compare, typename Allocator>
bool operator==(const Multimap<Key, T, Compare, Allocator>& lhs, const Multimap<Key, T, Compare, Allocator>& rhs);

template<typename Key, typename T, typename Compare, typename Allocator>
bool operator!=(const Multimap<Key, T, Compare, Allocator>& lhs, const Multimap<Key, T, Compare, Allocator>& rhs);

template<typename Key, typename T, typename Compare, typename Allocator>
bool operator<(const Multimap<Key, T, Compare, Allocator>& lhs, const Multimap<Key, T, Compare, Allocator>& rhs);

template<typename Key, typename T, typename Compare, typename Allocator>
bool operator<=(const Multimap<Key, T, Compare, Allocator>& lhs, const Multimap<Key, T, Compare, Allocator>& rhs);

template<typename Key, typename T, typename Compare, typename Allocator>
bool operator>(const Multimap<Key, T, Compare, Allocator>& lhs, const Multimap<Key, T, Compare, Allocator>& rhs);

template<typename Key, typename T, typename Compare, typename Allocator>
bool operator>=(const Multimap<Key, T, Compare, Allocator>& lhs, const Multimap<Key, T, Compare, Allocator>& rhs);

template<typename Key, typename T, typename Compare, typename Allocator>
void swap(const Multimap<Key, T, Compare, Allocator>& lhs, const Multimap<Key, T, Compare, Allocator>& rhs);

/// Polymorphic decorator aggregating std::multimap<Key, T> with the sole purpose of adding a virtual destructor..
///
/// Classes derived from Polymorphic::Multimap<Key, T> can be safely used as targets of smart pointers.
/// Note: forwarding member functions are *not* declared virtual! They are not meant to be overriden
/// in subclasses. Add new behavior using new virtual members instead.
template< typename Key, typename T, typename Compare = std::less<Key>, typename Allocator = std::allocator< std::pair<const Key, T> > >
class Multimap
{
public:
	typedef std::multimap<Key, T, Compare, Allocator> DelegateType;
	typedef Key key_type;	
	typedef T mapped_type;	
	typedef std::pair<const key_type, mapped_type> value_type;
	typedef Compare key_compare;
	typedef typename DelegateType::value_compare value_compare;
	typedef Allocator allocator_type;
	typedef T& reference;	
	typedef const T& const_reference;	
	typedef typename DelegateType::pointer pointer;
	typedef typename DelegateType::const_pointer const_pointer ;
	typedef typename DelegateType::iterator iterator;
	typedef typename DelegateType::const_iterator const_iterator ;
	typedef typename DelegateType::reverse_iterator reverse_iterator;
	typedef typename DelegateType::const_reverse_iterator const_reverse_iterator;
	typedef typename DelegateType::difference_type difference_type;
	typedef typename DelegateType::size_type size_type;

	/// Forwarded to std::multimap<Key, T>::multimap(const key_compare& compare = key_compare(), const allocator_type& allocator = allocator_type()).
	explicit Multimap(const key_compare& compare = key_compare(), const allocator_type& allocator = allocator_type()) : delegate(compare, allocator)
	{
	}

	/// Forwarded to std::multimap<Key, T>::multimap(const allocator_type& alloc).
	explicit Multimap(const allocator_type& allocator) : delegate(allocator)
	{
	}

	/// Forwarded to std::multimap<Key, T>::multimap(InputIterator first, InputIterator last, const key_compare& compare = key_compare(), const allocator_type& allocator = allocator_type()).
	template<typename InputIterator>
	Multimap(InputIterator first, InputIterator last, const key_compare& compare = key_compare(), const allocator_type& allocator = allocator_type()) : delegate(first, last, compare, allocator)
	{
	}

	/// Copy constructor.
	Multimap(const Multimap& other) : delegate(other.delegate)
	{
	}

	/// Copy constructor.
	Multimap(const Multimap& other, const allocator_type& allocator) : delegate(other.delegate, allocator)
	{
	}

	/// Move constructor.
	Multimap(Multimap&& other) : delegate(std::move(other.delegate))
	{
	}

	/// Move constructor.
	Multimap(Multimap&& other, const allocator_type& allocator) :
			delegate(std::move(other.delegate), allocator)
	{
	}

	/// Forwarded to std::multimap<Key, T>::multimap(std::initializer_list<value_type> initializerList, const key_compare& compare = key_compare(), const allocator_type& allocator = allocator_type()).
	Multimap(std::initializer_list<value_type> initializerList, const key_compare& compare = key_compare(), const allocator_type& allocator = allocator_type()) : delegate(initializerList, compare, allocator)
	{
	}

	/// Copy construct from std::multimap<T>.
	Multimap(const DelegateType& other) : delegate(other)
	{
	}

	/// Copy construct from std::multimap<T> with allocator.
	Multimap(const DelegateType& other, const allocator_type& allocator) : delegate(other, allocator)
	{
	}

	/// Move construct from std::multimap<T>.
	Multimap(DelegateType&& other) : delegate(std::move(other))
	{
	}

	/// Move construct from std::multimap<T> with allocator.
	Multimap(DelegateType&& other, const allocator_type& allocator) : delegate(std::move(other), allocator)
	{
	}

	/// Virtual destructor permitting derived classes to be deleted safely via a Multimap pointer.
	virtual ~Multimap()
	{
	}

	/// Copy assignment operator	
	Multimap& operator=(const Multimap& other)
	{
		delegate = other.delegate;
		return *this;
	}

	/// Move assignment operator	
	Multimap& operator=(Multimap&& other)
	{
		delegate = std::move(other.delegate);
		return *this;
	}

	/// Initializer list assignment operator	
	Multimap& operator=(std::initializer_list<value_type> initializerList)
	{
		delegate = initializerList;
		return *this;
	}

	/// Copy assignment from std::multimap<T>.
	Multimap& operator=(const DelegateType& other)
	{
		delegate = other;
		return *this;
	}

	/// Move assignment from std::multimap<T>.
	Multimap& operator=(DelegateType&& other)
	{
		delegate = std::move(other);
		return *this;
	}

	/// Implicit type conversion into std::multimap<T> reference.
	operator DelegateType&()
	{
		return delegate;
	}

	/// Implicit type conversion into const std::multimap<T> reference.
	operator const DelegateType&() const
	{
		return delegate;
	}

	/// Implicit type conversion into std::multimap<T> rvalue reference.
	operator DelegateType&&()
	{
		return std::move(delegate);
	}

	/// Forwarded to std::multimap<Key, T>::begin().
	iterator begin() noexcept
	{
		return delegate.begin();
	}

	/// Forwarded to std::multimap<Key, T>::begin() const.
	const_iterator begin() const noexcept
	{
		return delegate.begin();
	}

	/// Forwarded to std::multimap<Key, T>::end().
	iterator end() noexcept
	{
		return delegate.end();
	}

	/// Forwarded to std::multimap<Key, T>::end() const.
	const_iterator end() const noexcept
	{
		return delegate.end();
	}

	/// Forwarded to std::multimap<Key, T>::rbegin().
	reverse_iterator rbegin() noexcept
	{
		return delegate.rbegin();
	}

	/// Forwarded to std::multimap<Key, T>::rbegin() const.
	const_reverse_iterator rbegin() const noexcept
	{
		return delegate.rbegin();
	}

	/// Forwarded to std::multimap<Key, T>::rend().
	reverse_iterator rend() noexcept
	{
		return delegate.rend();
	}

	/// Forwarded to std::multimap<Key, T>::rend() const.
	const_reverse_iterator rend() const noexcept
	{
		return delegate.rend();
	}

	/// Forwarded to std::multimap<Key, T>::cbegin() const.
	const_iterator cbegin() const noexcept
	{
		return delegate.cbegin();
	}

	/// Forwarded to std::multimap<Key, T>::cend() const.
	const_iterator cend() const noexcept
	{
		return delegate.cend();
	}

	/// Forwarded to std::multimap<Key, T>::crbegin() const.
	const_reverse_iterator crbegin() const noexcept
	{
		return delegate.crbegin();
	}

	/// Forwarded to std::multimap<Key, T>::crend() const.
	const_reverse_iterator crend() const noexcept
	{
		return delegate.crend();
	}

	/// Forwarded to std::multimap<Key, T>::empty().
	bool empty() const noexcept
	{
		return delegate.empty();
	}

	/// Forwarded to std::multimap<Key, T>::size().
	size_type size() const noexcept
	{
		return delegate.size();
	}

	/// Forwarded to std::multimap<Key, T>::max_size().
	size_type max_size() const noexcept
	{
		return delegate.max_size();
	}

	/// Forwarded to std::multimap<Key, T>::insert(const value_type& value).
	std::pair<iterator, bool> insert(const value_type& value)
	{
		return delegate.insert(value);
	}

	/// Forwarded to std::multimap<Key, T>::insert(Pair&& value).
	template<typename Pair>
	std::pair<iterator, bool> insert(Pair&& value)
	{
		return delegate.insert(std::move(value));
	}

	/// Forwarded to std::multimap<Key, T>::insert(const_iterator position, const value_type& value).
	iterator insert(const_iterator position, const value_type& value)
	{
		return delegate.insert(position, value);
	}

	/// Forwarded to std::multimap<Key, T>::insert(const_iterator position, Pair&& value).
	template<typename Pair>
	iterator insert(const_iterator position, Pair&& value)
	{
		return delegate.insert(position, std::move(value));
	}

	/// Forwarded to std::multimap<Key, T>::insert(InputIterator first, InputIterator last).
	template<typename InputIterator>
	void insert(InputIterator first, InputIterator last)
	{
		delegate.insert(first, last);
	}

	/// Forwarded to std::multimap<Key, T>::insert(std::initializer_list<value_type> initializerList).
	void insert(std::initializer_list<value_type> initializerList)
	{
		delegate.insert(initializerList);
	}

	/// Forwarded to std::multimap<Key, T>::erase(const_iterator position).
	iterator erase(const_iterator position)
	{
		return delegate.erase(position);
	}

	/// Forwarded to std::multimap<Key, T>::erase(const key_type& key).
	size_type erase(const key_type& key)
	{
		return delegate.erase(key);
	}

	/// Forwarded to std::multimap<Key, T>::erase(const_iterator first, const_iterator last).
	iterator erase(const_iterator first, const_iterator last)
	{
		return delegate.erase(first, last);
	}

	/// Forwarded to std::multimap<Key, T>::swap(std::multimap<bool>& other).
	void swap(Multimap& other) {
		delegate.swap(other.multimap);
	}

	/// Forwarded to std::multimap<Key, T>::clear().
	void clear() noexcept {
		delegate.clear();
	}

	/// Forwarded to std::multimap<Key, T>::emplace(const_iterator position, Args&&... args).
	template<typename... Args>
	std::pair<iterator, bool> emplace(Args&&... args)
	{
		return delegate.emplace(std::forward<Args>(args)...);
	}

	/// Forwarded to std::multimap<Key, T>::emplace_hint(const_iterator position, Args&&... args).
	template<typename... Args>
	iterator emplace_hint(const_iterator position, Args&&... args)
	{
		return delegate.emplace_hint(position, std::forward<Args>(args)...);
	}

	/// Forwarded to std::multimap<Key, T>::find(const key_type& key).
	iterator find(const key_type& key)
	{
		return delegate.find(key);
	}

	/// Forwarded to std::multimap<Key, T>::find(const key_type& key) const.
	const_iterator find(const key_type& key) const
	{
		return delegate.find(key);
	}

	/// Forwarded to std::multimap<Key, T>::count(const key_type& key) const.
	size_type count(const key_type& key) const
	{
		return delegate.count(key);
	}

	/// Forwarded to std::multimap<Key, T>::lower_bound(const key_type& key).
	iterator lower_bound(const key_type& key)
	{
		return delegate.lower_bound(key);
	}

	/// Forwarded to std::multimap<Key, T>::lower_bound(const key_type& key) const.
	const_iterator lower_bound(const key_type& key) const
	{
		return delegate.lower_bound(key);
	}

	/// Forwarded to std::multimap<Key, T>::upper_bound(const key_type& key).
	iterator upper_bound(const key_type& key)
	{
		return delegate.upper_bound(key);
	}

	/// Forwarded to std::multimap<Key, T>::upper_bound(const key_type& key) const.
	const_iterator upper_bound(const key_type& key) const
	{
		return delegate.upper_bound(key);
	}

	/// Forwarded to std::multimap<Key, T>::equal_range(const key_type& key).
	std::pair<iterator, iterator> equal_range(const key_type& key)
	{
		return delegate.equal_range(key);
	}

	/// Forwarded to std::multimap<Key, T>::equal_range(const key_type& key) const.
	std::pair<const_iterator, const_iterator> equal_range(const key_type& key) const
	{
		return delegate.equal_range(key);
	}

	/// Forwarded to std::multimap<Key, T>::key_comp().
	key_compare key_comp() const
	{
		return delegate.key_comp();
	}

	/// Forwarded to std::multimap<Key, T>::value_comp().
	value_compare value_comp() const
	{
	}

	/// Forwarded to std::multimap<Key, T>::get_allocator() const noexcept.
	allocator_type get_allocator() const noexcept
	{
		return delegate.get_allocator();
	}

private:
	DelegateType delegate;

	friend bool operator== <Key, T, Compare, Allocator> (const Multimap& lhs, const Multimap& rhs);
	friend bool operator!= <Key, T, Compare, Allocator> (const Multimap& lhs, const Multimap& rhs);
	friend bool operator<  <Key, T, Compare, Allocator> (const Multimap& lhs, const Multimap& rhs);
	friend bool operator<= <Key, T, Compare, Allocator> (const Multimap& lhs, const Multimap& rhs);
	friend bool operator>  <Key, T, Compare, Allocator> (const Multimap& lhs, const Multimap& rhs);
	friend bool operator>= <Key, T, Compare, Allocator> (const Multimap& lhs, const Multimap& rhs);
	friend void Polymorphic::swap<Key, T, Compare, Allocator>(const Multimap& lhs, const Multimap& rhs);
};

/// Forwarded to operator==(const std::multimap<Key, T, Compare, Allocator>& lhs, const std::multimap<Key, T, Compare, Allocator>& rhs).
template<typename Key, typename T, typename Compare, typename Allocator>
bool operator==(const Multimap<Key, T, Compare, Allocator>& lhs, const Multimap<Key, T, Compare, Allocator>& rhs)
{
	return lhs.multimap == rhs.multimap;
}

/// Forwarded to operator!=(const std::multimap<Key, T, Compare, Allocator>& lhs, const std::multimap<Key, T, Compare, Allocator>& rhs).
template<typename Key, typename T, typename Compare, typename Allocator>
bool operator!=(const Multimap<Key, T, Compare, Allocator>& lhs, const Multimap<Key, T, Compare, Allocator>& rhs)
{
	return lhs.multimap != rhs.multimap;
}

/// Forwarded to operator<(const std::multimap<Key, T, Compare, Allocator>& lhs, const std::multimap<Key, T, Compare, Allocator>& rhs).
template<typename Key, typename T, typename Compare, typename Allocator>
bool operator<(const Multimap<Key, T, Compare, Allocator>& lhs, const Multimap<Key, T, Compare, Allocator>& rhs)
{
	return lhs.multimap < rhs.multimap;
}

/// Forwarded to operator<=(const std::multimap<Key, T, Compare, Allocator>& lhs, const std::multimap<Key, T, Compare, Allocator>& rhs).
template<typename Key, typename T, typename Compare, typename Allocator>
bool operator<=(const Multimap<Key, T, Compare, Allocator>& lhs, const Multimap<Key, T, Compare, Allocator>& rhs)
{
	return lhs.multimap <= rhs.multimap;
}

/// Forwarded to operator>(const std::multimap<Key, T, Compare, Allocator>& lhs, const std::multimap<Key, T, Compare, Allocator>& rhs).
template<typename Key, typename T, typename Compare, typename Allocator>
bool operator>(const Multimap<Key, T, Compare, Allocator>& lhs, const Multimap<Key, T, Compare, Allocator>& rhs)
{
	return lhs.multimap > rhs.multimap;
}

/// Forwarded to operator>=(const std::multimap<Key, T, Compare, Allocator>& lhs, const std::multimap<Key, T, Compare, Allocator>& rhs).
template<typename Key, typename T, typename Compare, typename Allocator>
bool operator>=(const Multimap<Key, T, Compare, Allocator>& lhs, const Multimap<Key, T, Compare, Allocator>& rhs)
{
	return lhs.multimap >= rhs.multimap;
}

/// Forwarded to swap(const std::multimap<Key, T, Compare, Allocator>& lhs, const std::multimap<Key, T, Compare, Allocator>& rhs).
template<typename Key, typename T, typename Compare, typename Allocator>
void swap(const Multimap<Key, T, Compare, Allocator>& lhs, const Multimap<Key, T, Compare, Allocator>& rhs)
{
	swap(lhs.multimap, rhs.multimap);
}

} // namespace Polymorphic

#endif // Polymorphic_Multimap_INCLUDED
