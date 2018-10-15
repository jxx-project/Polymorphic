//
// Copyright (C) 2018 Dr. Michael Steffens
//
// SPDX-License-Identifier:	BSL-1.0
//


#ifndef Polymorphic_Multiset_INCLUDED
#define Polymorphic_Multiset_INCLUDED

#include <set>

namespace Polymorphic {

template<typename Key, typename Compare, typename Allocator>
class Multiset;

template<typename Key, typename Compare, typename Allocator>
bool operator==(const Multiset<Key, Compare, Allocator>& lhs, const Multiset<Key, Compare, Allocator>& rhs);

template<typename Key, typename Compare, typename Allocator>
bool operator!=(const Multiset<Key, Compare, Allocator>& lhs, const Multiset<Key, Compare, Allocator>& rhs);

template<typename Key, typename Compare, typename Allocator>
bool operator<(const Multiset<Key, Compare, Allocator>& lhs, const Multiset<Key, Compare, Allocator>& rhs);

template<typename Key, typename Compare, typename Allocator>
bool operator<=(const Multiset<Key, Compare, Allocator>& lhs, const Multiset<Key, Compare, Allocator>& rhs);

template<typename Key, typename Compare, typename Allocator>
bool operator>(const Multiset<Key, Compare, Allocator>& lhs, const Multiset<Key, Compare, Allocator>& rhs);

template<typename Key, typename Compare, typename Allocator>
bool operator>=(const Multiset<Key, Compare, Allocator>& lhs, const Multiset<Key, Compare, Allocator>& rhs);

template<typename Key, typename Compare, typename Allocator>
void swap(const Multiset<Key, Compare, Allocator>& lhs, const Multiset<Key, Compare, Allocator>& rhs);

/// Polymorphic decorator composing std::multiset<Key> with the sole purpose of adding a virtual destructor..
///
/// Classes derived from Polymorphic::Multiset<Key> can be safely used as targets of smart pointers.
/// Note: forwarding member functions are *not* declared virtual! They are not meant to be overriden
/// in subclasses. Add new behavior using new virtual members instead.
template<typename Key, typename Compare = std::less<Key>, typename Allocator = std::allocator<Key>>
class Multiset
{
public:
	typedef std::multiset<Key, Compare, Allocator> DelegateType;
	typedef Key key_type;
	typedef Key value_type;
	typedef Compare key_compare;
	typedef Compare value_compare;
	typedef Allocator allocator_type;
	typedef value_type& reference;
	typedef const value_type& const_reference;
	typedef typename DelegateType::pointer pointer;
	typedef typename DelegateType::const_pointer const_pointer;
	typedef typename DelegateType::iterator iterator;
	typedef typename DelegateType::const_iterator const_iterator;
	typedef typename DelegateType::reverse_iterator reverse_iterator;
	typedef typename DelegateType::const_reverse_iterator const_reverse_iterator;
	typedef typename DelegateType::difference_type difference_type;
	typedef typename DelegateType::size_type size_type;

	/// Forwarded to std::multiset<Key>::multiset(const key_compare& compare = key_compare(), const allocator_type& allocator =
	/// allocator_type()).
	explicit Multiset(const key_compare& compare = key_compare(), const allocator_type& allocator = allocator_type()) :
		delegate(compare, allocator)
	{
	}

	/// Forwarded to std::multiset<Key>::multiset(const allocator_type& alloc).
	explicit Multiset(const allocator_type& allocator) : delegate(allocator)
	{
	}

	/// Forwarded to std::multiset<Key>::multiset(InputIterator first, InputIterator last, const key_compare& compare =
	/// key_compare(), const allocator_type& allocator = allocator_type()).
	template<typename InputIterator>
	Multiset(
		InputIterator first,
		InputIterator last,
		const key_compare& compare = key_compare(),
		const allocator_type& allocator = allocator_type()) :
		delegate(first, last, compare, allocator)
	{
	}

	/// Copy constructor.
	Multiset(const Multiset& other) : delegate(other.delegate)
	{
	}

	/// Copy constructor.
	Multiset(const Multiset& other, const allocator_type& allocator) : delegate(other.delegate, allocator)
	{
	}

	/// Move constructor.
	Multiset(Multiset&& other) : delegate(std::move(other.delegate))
	{
	}

	/// Move constructor.
	Multiset(Multiset&& other, const allocator_type& allocator) : delegate(std::move(other.delegate), allocator)
	{
	}

	/// Forwarded to std::multiset<Key>::multiset(std::initializer_list<value_type> initializerList, const key_compare& compare =
	/// key_compare(), const allocator_type& allocator = allocator_type()).
	Multiset(
		std::initializer_list<value_type> initializerList,
		const key_compare& compare = key_compare(),
		const allocator_type& allocator = allocator_type()) :
		delegate(initializerList, compare, allocator)
	{
	}

	/// Copy construct from std::multiset<Key>.
	Multiset(const DelegateType& other) : delegate(other)
	{
	}

	/// Copy construct from std::multiset<Key> with allocator.
	Multiset(const DelegateType& other, const allocator_type& allocator) : delegate(other, allocator)
	{
	}

	/// Move construct from std::multiset<Key>.
	Multiset(DelegateType&& other) : delegate(std::move(other))
	{
	}

	/// Move construct from std::multiset<Key> with allocator.
	Multiset(DelegateType&& other, const allocator_type& allocator) : delegate(std::move(other), allocator)
	{
	}

	/// Virtual destructor permitting derived classes to be deleted safely via a Multiset pointer.
	virtual ~Multiset()
	{
	}

	/// Copy assignment operator
	Multiset& operator=(const Multiset& other)
	{
		delegate = other.delegate;
		return *this;
	}

	/// Move assignment operator
	Multiset& operator=(Multiset&& other)
	{
		delegate = std::move(other.delegate);
		return *this;
	}

	/// Initializer list assignment operator
	Multiset& operator=(std::initializer_list<value_type> initializerList)
	{
		delegate = initializerList;
		return *this;
	}

	/// Copy assignment from std::multiset<Key>.
	Multiset& operator=(const DelegateType& other)
	{
		delegate = other;
		return *this;
	}

	/// Move assignment from std::multiset<Key>.
	Multiset& operator=(DelegateType&& other)
	{
		delegate = std::move(other);
		return *this;
	}

	/// Implicit type conversion into std::multiset<Key> reference.
	operator DelegateType&()
	{
		return delegate;
	}

	/// Implicit type conversion into const std::multiset<Key> reference.
	operator const DelegateType&() const
	{
		return delegate;
	}

	/// Explicit type conversion into std::multiset<Key> rvalue reference.
	explicit operator DelegateType &&()
	{
		return std::move(delegate);
	}

	/// Forwarded to std::multiset<Key>::begin() noexcept.
	iterator begin() noexcept
	{
		return delegate.begin();
	}

	/// Forwarded to std::multiset<Key>::begin() const noexcept.
	const_iterator begin() const noexcept
	{
		return delegate.begin();
	}

	/// Forwarded to std::multiset<Key>::end() noexcept.
	iterator end() noexcept
	{
		return delegate.end();
	}

	/// Forwarded to std::multiset<Key>::end() const noexcept.
	const_iterator end() const noexcept
	{
		return delegate.end();
	}

	/// Forwarded to std::multiset<Key>::rbegin() noexcept.
	reverse_iterator rbegin() noexcept
	{
		return delegate.rbegin();
	}

	/// Forwarded to std::multiset<Key>::rbegin() const noexcept.
	const_reverse_iterator rbegin() const noexcept
	{
		return delegate.rbegin();
	}

	/// Forwarded to std::multiset<Key>::rend() noexcept.
	reverse_iterator rend() noexcept
	{
		return delegate.rend();
	}

	/// Forwarded to std::multiset<Key>::rend() const noexcept.
	const_reverse_iterator rend() const noexcept
	{
		return delegate.rend();
	}

	/// Forwarded to std::multiset<Key>::cbegin() const noexcept.
	const_iterator cbegin() const noexcept
	{
		return delegate.cbegin();
	}

	/// Forwarded to std::multiset<Key>::cend() const noexcept.
	const_iterator cend() const noexcept
	{
		return delegate.cend();
	}

	/// Forwarded to std::multiset<Key>::crbegin() const noexcept.
	const_reverse_iterator crbegin() const noexcept
	{
		return delegate.crbegin();
	}

	/// Forwarded to std::multiset<Key>::crend() const noexcept.
	const_reverse_iterator crend() const noexcept
	{
		return delegate.crend();
	}

	/// Forwarded to std::multiset<Key>::empty() const noexcept.
	bool empty() const noexcept
	{
		return delegate.empty();
	}

	/// Forwarded to std::multiset<Key>::size() const noexcept.
	size_type size() const noexcept
	{
		return delegate.size();
	}

	/// Forwarded to std::multiset<Key>::max_size() const noexcept.
	size_type max_size() const noexcept
	{
		return delegate.max_size();
	}

	/// Forwarded to std::multiset<Key>::insert(const value_type& value).
	iterator insert(const value_type& value)
	{
		return delegate.insert(value);
	}

	/// Forwarded to std::multiset<Key>::insert(value_type&& value).
	iterator insert(value_type&& value)
	{
		return delegate.insert(std::move(value));
	}

	/// Forwarded to std::multiset<Key>::insert(const_iterator position, const value_type& value).
	iterator insert(const_iterator position, const value_type& value)
	{
		return delegate.insert(position, value);
	}

	/// Forwarded to std::multiset<Key>::insert(const_iterator position, value_type&& value).
	iterator insert(const_iterator position, value_type&& value)
	{
		return delegate.insert(position, std::move(value));
	}

	/// Forwarded to std::multiset<Key>::insert(InputIterator first, InputIterator last).
	template<typename InputIterator>
	void insert(InputIterator first, InputIterator last)
	{
		delegate.insert(first, last);
	}

	/// Forwarded to std::multiset<Key>::insert(std::initializer_list<value_type> initializerList).
	void insert(std::initializer_list<value_type> initializerList)
	{
		delegate.insert(initializerList);
	}

	/// Forwarded to std::multiset<Key>::erase(const_iterator position).
	iterator erase(const_iterator position)
	{
		return delegate.erase(position);
	}

	/// Forwarded to std::multiset<Key>::erase(const key_type& key).
	size_type erase(const key_type& key)
	{
		return delegate.erase(key);
	}

	/// Forwarded to std::multiset<Key>::erase(const_iterator first, const_iterator last).
	iterator erase(const_iterator first, const_iterator last)
	{
		return delegate.erase(first, last);
	}

	/// Forwarded to std::multiset<Key>::swap(std::multiset<bool>& other).
	void swap(Multiset& other)
	{
		delegate.swap(other.delegate);
	}

	/// Forwarded to std::multiset<Key>::clear() noexcept.
	void clear() noexcept
	{
		delegate.clear();
	}

	/// Forwarded to std::multiset<Key>::emplace(const_iterator position, Args&&... args).
	template<typename... Args>
	iterator emplace(Args&&... args)
	{
		return delegate.emplace(std::forward<Args>(args)...);
	}

	/// Forwarded to std::multiset<Key>::emplace_hint(const_iterator position, Args&&... args).
	template<typename... Args>
	iterator emplace_hint(const_iterator position, Args&&... args)
	{
		return delegate.emplace_hint(position, std::forward<Args>(args)...);
	}

	/// Forwarded to std::multiset<Key>::find(const key_type& key).
	iterator find(const key_type& key)
	{
		return delegate.find(key);
	}

	/// Forwarded to std::multiset<Key>::find(const key_type& key) const.
	const_iterator find(const key_type& key) const
	{
		return delegate.find(key);
	}

	/// Forwarded to std::multiset<Key>::count(const key_type& key) const.
	size_type count(const key_type& key) const
	{
		return delegate.count(key);
	}

	/// Forwarded to std::multiset<Key>::lower_bound(const key_type& key).
	iterator lower_bound(const key_type& key)
	{
		return delegate.lower_bound(key);
	}

	/// Forwarded to std::multiset<Key>::lower_bound(const key_type& key) const.
	const_iterator lower_bound(const key_type& key) const
	{
		return delegate.lower_bound(key);
	}

	/// Forwarded to std::multiset<Key>::upper_bound(const key_type& key).
	iterator upper_bound(const key_type& key)
	{
		return delegate.upper_bound(key);
	}

	/// Forwarded to std::multiset<Key>::upper_bound(const key_type& key) const.
	const_iterator upper_bound(const key_type& key) const
	{
		return delegate.upper_bound(key);
	}

	/// Forwarded to std::multiset<Key>::equal_range(const key_type& key).
	std::pair<iterator, iterator> equal_range(const key_type& key)
	{
		return delegate.equal_range(key);
	}

	/// Forwarded to std::multiset<Key>::equal_range(const key_type& key) const.
	std::pair<const_iterator, const_iterator> equal_range(const key_type& key) const
	{
		return delegate.equal_range(key);
	}

	/// Forwarded to std::multiset<Key>::key_comp() const.
	key_compare key_comp() const
	{
		return delegate.key_comp();
	}

	/// Forwarded to std::multiset<Key>::value_comp() const.
	value_compare value_comp() const
	{
		return delegate.value_comp();
	}

	/// Forwarded to std::multiset<Key>::get_allocator() const noexcept.
	allocator_type get_allocator() const noexcept
	{
		return delegate.get_allocator();
	}

private:
	DelegateType delegate;

	// clang-format off
	friend bool operator== <Key, Compare, Allocator>(const Multiset& lhs, const Multiset& rhs);
	friend bool operator!= <Key, Compare, Allocator>(const Multiset& lhs, const Multiset& rhs);
	friend bool operator< <Key, Compare, Allocator>(const Multiset& lhs, const Multiset& rhs);
	friend bool operator<= <Key, Compare, Allocator>(const Multiset& lhs, const Multiset& rhs);
	friend bool operator> <Key, Compare, Allocator>(const Multiset& lhs, const Multiset& rhs);
	friend bool operator>= <Key, Compare, Allocator>(const Multiset& lhs, const Multiset& rhs);
	// clang-format on
	friend void Polymorphic::swap<Key, Compare, Allocator>(
		const Multiset<Key, Compare, Allocator>& lhs,
		const Multiset<Key, Compare, Allocator>& rhs);
};

/// Forwarded to operator==(const std::multiset<Key, Compare, Allocator>& lhs, const std::multiset<Key, Compare, Allocator>& rhs).
template<typename Key, typename Compare, typename Allocator>
bool operator==(const Multiset<Key, Compare, Allocator>& lhs, const Multiset<Key, Compare, Allocator>& rhs)
{
	return lhs.delegate == rhs.delegate;
}

/// Forwarded to operator!=(const std::multiset<Key, Compare, Allocator>& lhs, const std::multiset<Key, Compare, Allocator>& rhs).
template<typename Key, typename Compare, typename Allocator>
bool operator!=(const Multiset<Key, Compare, Allocator>& lhs, const Multiset<Key, Compare, Allocator>& rhs)
{
	return lhs.delegate != rhs.delegate;
}

/// Forwarded to operator<(const std::multiset<Key, Compare, Allocator>& lhs, const std::multiset<Key, Compare, Allocator>& rhs).
template<typename Key, typename Compare, typename Allocator>
bool operator<(const Multiset<Key, Compare, Allocator>& lhs, const Multiset<Key, Compare, Allocator>& rhs)
{
	return lhs.delegate < rhs.delegate;
}

/// Forwarded to operator<=(const std::multiset<Key, Compare, Allocator>& lhs, const std::multiset<Key, Compare, Allocator>& rhs).
template<typename Key, typename Compare, typename Allocator>
bool operator<=(const Multiset<Key, Compare, Allocator>& lhs, const Multiset<Key, Compare, Allocator>& rhs)
{
	return lhs.delegate <= rhs.delegate;
}

/// Forwarded to operator>(const std::multiset<Key, Compare, Allocator>& lhs, const std::multiset<Key, Compare, Allocator>& rhs).
template<typename Key, typename Compare, typename Allocator>
bool operator>(const Multiset<Key, Compare, Allocator>& lhs, const Multiset<Key, Compare, Allocator>& rhs)
{
	return lhs.delegate > rhs.delegate;
}

/// Forwarded to operator>=(const std::multiset<Key, Compare, Allocator>& lhs, const std::multiset<Key, Compare, Allocator>& rhs).
template<typename Key, typename Compare, typename Allocator>
bool operator>=(const Multiset<Key, Compare, Allocator>& lhs, const Multiset<Key, Compare, Allocator>& rhs)
{
	return lhs.delegate >= rhs.delegate;
}

/// Forwarded to swap(const std::multiset<Key, Compare, Allocator>& lhs, const std::multiset<Key, Compare, Allocator>& rhs).
template<typename Key, typename Compare, typename Allocator>
void swap(const Multiset<Key, Compare, Allocator>& lhs, const Multiset<Key, Compare, Allocator>& rhs)
{
	swap(lhs.delegate, rhs.delegate);
}

} // namespace Polymorphic

#endif // Polymorphic_Multiset_INCLUDED
