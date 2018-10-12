//
// Copyright (C) 2018 Dr. Michael Steffens
//
// SPDX-License-Identifier:	BSL-1.0
//


#ifndef Polymorphic_Set_INCLUDED
#define Polymorphic_Set_INCLUDED

#include <set>

namespace Polymorphic {

template<typename T, typename Compare, typename Allocator>
class Set;

template<typename T, typename Compare, typename Allocator>
bool operator==(const Set<T, Compare, Allocator>& lhs, const Set<T, Compare, Allocator>& rhs);

template<typename T, typename Compare, typename Allocator>
bool operator!=(const Set<T, Compare, Allocator>& lhs, const Set<T, Compare, Allocator>& rhs);

template<typename T, typename Compare, typename Allocator>
bool operator<(const Set<T, Compare, Allocator>& lhs, const Set<T, Compare, Allocator>& rhs);

template<typename T, typename Compare, typename Allocator>
bool operator<=(const Set<T, Compare, Allocator>& lhs, const Set<T, Compare, Allocator>& rhs);

template<typename T, typename Compare, typename Allocator>
bool operator>(const Set<T, Compare, Allocator>& lhs, const Set<T, Compare, Allocator>& rhs);

template<typename T, typename Compare, typename Allocator>
bool operator>=(const Set<T, Compare, Allocator>& lhs, const Set<T, Compare, Allocator>& rhs);

template<typename T, typename Compare, typename Allocator>
void swap(const Set<T, Compare, Allocator>& lhs, const Set<T, Compare, Allocator>& rhs);

/// Polymorphic decorator composing std::set<T> with the sole purpose of adding a virtual destructor..
///
/// Classes derived from Polymorphic::Set<T> can be safely used as targets of smart pointers.
/// Note: forwarding member functions are *not* declared virtual! They are not meant to be overriden
/// in subclasses. Add new behavior using new virtual members instead.
template<typename T, typename Compare = std::less<T>, typename Allocator = std::allocator<T>>
class Set
{
public:
	typedef std::set<T, Compare, Allocator> DelegateType;
	typedef T key_type;
	typedef T value_type;
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

	/// Forwarded to std::set<T>::set(const key_compare& compare = key_compare(), const allocator_type& allocator =
	/// allocator_type()).
	explicit Set(const key_compare& compare = key_compare(), const allocator_type& allocator = allocator_type()) :
		delegate(compare, allocator)
	{
	}

	/// Forwarded to std::set<T>::set(const allocator_type& alloc).
	explicit Set(const allocator_type& allocator) : delegate(allocator)
	{
	}

	/// Forwarded to std::set<T>::set(InputIterator first, InputIterator last, const key_compare& compare = key_compare(),
	/// const allocator_type& allocator = allocator_type()).
	template<typename InputIterator>
	Set(InputIterator first,
		InputIterator last,
		const key_compare& compare = key_compare(),
		const allocator_type& allocator = allocator_type()) :
		delegate(first, last, compare, allocator)
	{
	}

	/// Copy constructor.
	Set(const Set& other) : delegate(other.delegate)
	{
	}

	/// Copy constructor.
	Set(const Set& other, const allocator_type& allocator) : delegate(other.delegate, allocator)
	{
	}

	/// Move constructor.
	Set(Set&& other) : delegate(std::move(other.delegate))
	{
	}

	/// Move constructor.
	Set(Set&& other, const allocator_type& allocator) : delegate(std::move(other.delegate), allocator)
	{
	}

	/// Forwarded to std::set<T>::set(std::initializer_list<value_type> initializerList, const key_compare& compare =
	/// key_compare(), const allocator_type& allocator = allocator_type()).
	Set(std::initializer_list<value_type> initializerList,
		const key_compare& compare = key_compare(),
		const allocator_type& allocator = allocator_type()) :
		delegate(initializerList, compare, allocator)
	{
	}

	/// Copy construct from std::set<T>.
	Set(const DelegateType& other) : delegate(other)
	{
	}

	/// Copy construct from std::set<T> with allocator.
	Set(const DelegateType& other, const allocator_type& allocator) : delegate(other, allocator)
	{
	}

	/// Move construct from std::set<T>.
	Set(DelegateType&& other) : delegate(std::move(other))
	{
	}

	/// Move construct from std::set<T> with allocator.
	Set(DelegateType&& other, const allocator_type& allocator) : delegate(std::move(other), allocator)
	{
	}

	/// Virtual destructor permitting derived classes to be deleted safely via a Set pointer.
	virtual ~Set()
	{
	}

	/// Copy assignment operator
	Set& operator=(const Set& other)
	{
		delegate = other.delegate;
		return *this;
	}

	/// Move assignment operator
	Set& operator=(Set&& other)
	{
		delegate = std::move(other.delegate);
		return *this;
	}

	/// Initializer list assignment operator
	Set& operator=(std::initializer_list<value_type> initializerList)
	{
		delegate = initializerList;
		return *this;
	}

	/// Copy assignment from std::set<T>.
	Set& operator=(const DelegateType& other)
	{
		delegate = other;
		return *this;
	}

	/// Move assignment from std::set<T>.
	Set& operator=(DelegateType&& other)
	{
		delegate = std::move(other);
		return *this;
	}

	/// Implicit type conversion into std::set<T> reference.
	operator DelegateType&()
	{
		return delegate;
	}

	/// Implicit type conversion into const std::set<T> reference.
	operator const DelegateType&() const
	{
		return delegate;
	}

	/// Explicit type conversion into std::set<T> rvalue reference.
	explicit operator DelegateType &&()
	{
		return std::move(delegate);
	}

	/// Forwarded to std::set<T>::begin() noexcept.
	iterator begin() noexcept
	{
		return delegate.begin();
	}

	/// Forwarded to std::set<T>::begin() const noexcept.
	const_iterator begin() const noexcept
	{
		return delegate.begin();
	}

	/// Forwarded to std::set<T>::end() noexcept.
	iterator end() noexcept
	{
		return delegate.end();
	}

	/// Forwarded to std::set<T>::end() const noexcept.
	const_iterator end() const noexcept
	{
		return delegate.end();
	}

	/// Forwarded to std::set<T>::rbegin() noexcept.
	reverse_iterator rbegin() noexcept
	{
		return delegate.rbegin();
	}

	/// Forwarded to std::set<T>::rbegin() const noexcept.
	const_reverse_iterator rbegin() const noexcept
	{
		return delegate.rbegin();
	}

	/// Forwarded to std::set<T>::rend() noexcept.
	reverse_iterator rend() noexcept
	{
		return delegate.rend();
	}

	/// Forwarded to std::set<T>::rend() const noexcept.
	const_reverse_iterator rend() const noexcept
	{
		return delegate.rend();
	}

	/// Forwarded to std::set<T>::cbegin() const noexcept.
	const_iterator cbegin() const noexcept
	{
		return delegate.cbegin();
	}

	/// Forwarded to std::set<T>::cend() const noexcept.
	const_iterator cend() const noexcept
	{
		return delegate.cend();
	}

	/// Forwarded to std::set<T>::crbegin() const noexcept.
	const_reverse_iterator crbegin() const noexcept
	{
		return delegate.crbegin();
	}

	/// Forwarded to std::set<T>::crend() const noexcept.
	const_reverse_iterator crend() const noexcept
	{
		return delegate.crend();
	}

	/// Forwarded to std::set<T>::empty() const noexcept.
	bool empty() const noexcept
	{
		return delegate.empty();
	}

	/// Forwarded to std::set<T>::size() const noexcept.
	size_type size() const noexcept
	{
		return delegate.size();
	}

	/// Forwarded to std::set<T>::max_size() const noexcept.
	size_type max_size() const noexcept
	{
		return delegate.max_size();
	}

	/// Forwarded to std::set<T>::insert(const value_type& value).
	std::pair<iterator, bool> insert(const value_type& value)
	{
		return delegate.insert(value);
	}

	/// Forwarded to std::set<T>::insert(value_type&& value).
	std::pair<iterator, bool> insert(value_type&& value)
	{
		return delegate.insert(std::move(value));
	}

	/// Forwarded to std::set<T>::insert(const_iterator position, const value_type& value).
	iterator insert(const_iterator position, const value_type& value)
	{
		return delegate.insert(position, value);
	}

	/// Forwarded to std::set<T>::insert(const_iterator position, value_type&& value).
	iterator insert(const_iterator position, value_type&& value)
	{
		return delegate.insert(position, std::move(value));
	}

	/// Forwarded to std::set<T>::insert(InputIterator first, InputIterator last).
	template<typename InputIterator>
	void insert(InputIterator first, InputIterator last)
	{
		delegate.insert(first, last);
	}

	/// Forwarded to std::set<T>::insert(std::initializer_list<value_type> initializerList).
	void insert(std::initializer_list<value_type> initializerList)
	{
		delegate.insert(initializerList);
	}

	/// Forwarded to std::set<T>::erase(const_iterator position).
	iterator erase(const_iterator position)
	{
		return delegate.erase(position);
	}

	/// Forwarded to std::set<T>::erase(const value_type& value).
	size_type erase(const value_type& value)
	{
		return delegate.erase(value);
	}

	/// Forwarded to std::set<T>::erase(const_iterator first, const_iterator last).
	iterator erase(const_iterator first, const_iterator last)
	{
		return delegate.erase(first, last);
	}

	/// Forwarded to std::set<T>::swap(std::set<bool>& other).
	void swap(Set& other)
	{
		delegate.swap(other.delegate);
	}

	/// Forwarded to std::set<T>::clear() noexcept.
	void clear() noexcept
	{
		delegate.clear();
	}

	/// Forwarded to std::set<T>::emplace(const_iterator position, Args&&... args).
	template<typename... Args>
	std::pair<iterator, bool> emplace(Args&&... args)
	{
		return delegate.emplace(std::forward<Args>(args)...);
	}

	/// Forwarded to std::set<T>::emplace_hint(const_iterator position, Args&&... args).
	template<typename... Args>
	iterator emplace_hint(const_iterator position, Args&&... args)
	{
		return delegate.emplace_hint(position, std::forward<Args>(args)...);
	}

	/// Forwarded to std::set<T>::find(const value_type& value).
	iterator find(const value_type& value)
	{
		return delegate.find(value);
	}

	/// Forwarded to std::set<T>::find(const value_type& value) const.
	const_iterator find(const value_type& value) const
	{
		return delegate.find(value);
	}

	/// Forwarded to std::set<T>::count(const value_type& value) const.
	size_type count(const value_type& value) const
	{
		return delegate.count(value);
	}

	/// Forwarded to std::set<T>::lower_bound(const value_type& value).
	iterator lower_bound(const value_type& value)
	{
		return delegate.lower_bound(value);
	}

	/// Forwarded to std::set<T>::lower_bound(const value_type& value) const.
	const_iterator lower_bound(const value_type& value) const
	{
		return delegate.lower_bound(value);
	}

	/// Forwarded to std::set<T>::upper_bound(const value_type& value).
	iterator upper_bound(const value_type& value)
	{
		return delegate.upper_bound(value);
	}

	/// Forwarded to std::set<T>::upper_bound(const value_type& value) const.
	const_iterator upper_bound(const value_type& value) const
	{
		return delegate.upper_bound(value);
	}

	/// Forwarded to std::set<T>::equal_range(const value_type& value).
	std::pair<iterator, iterator> equal_range(const value_type& value)
	{
		return delegate.equal_range(value);
	}

	/// Forwarded to std::set<T>::equal_range(const value_type& value) const.
	std::pair<const_iterator, const_iterator> equal_range(const value_type& value) const
	{
		return delegate.equal_range(value);
	}

	/// Forwarded to std::set<T>::key_comp() const.
	key_compare key_comp() const
	{
		return delegate.key_comp();
	}

	/// Forwarded to std::set<T>::value_comp() const.
	value_compare value_comp() const
	{
		return delegate.value_comp();
	}

	/// Forwarded to std::set<T>::get_allocator() const noexcept.
	allocator_type get_allocator() const noexcept
	{
		return delegate.get_allocator();
	}

private:
	DelegateType delegate;

	// clang-format off
	friend bool operator== <T, Compare, Allocator>(const Set& lhs, const Set& rhs);
	friend bool operator!= <T, Compare, Allocator>(const Set& lhs, const Set& rhs);
	friend bool operator< <T, Compare, Allocator>(const Set& lhs, const Set& rhs);
	friend bool operator<= <T, Compare, Allocator>(const Set& lhs, const Set& rhs);
	friend bool operator> <T, Compare, Allocator>(const Set& lhs, const Set& rhs);
	friend bool operator>= <T, Compare, Allocator>(const Set& lhs, const Set& rhs);
	// clang-format on
	friend void Polymorphic::swap<T, Compare, Allocator>(
		const Set<T, Compare, Allocator>& lhs,
		const Set<T, Compare, Allocator>& rhs);
};

/// Forwarded to operator==(const std::set<T, Compare, Allocator>& lhs, const std::set<T, Compare, Allocator>& rhs).
template<typename T, typename Compare, typename Allocator>
bool operator==(const Set<T, Compare, Allocator>& lhs, const Set<T, Compare, Allocator>& rhs)
{
	return lhs.delegate == rhs.delegate;
}

/// Forwarded to operator!=(const std::set<T, Compare, Allocator>& lhs, const std::set<T, Compare, Allocator>& rhs).
template<typename T, typename Compare, typename Allocator>
bool operator!=(const Set<T, Compare, Allocator>& lhs, const Set<T, Compare, Allocator>& rhs)
{
	return lhs.delegate != rhs.delegate;
}

/// Forwarded to operator<(const std::set<T, Compare, Allocator>& lhs, const std::set<T, Compare, Allocator>& rhs).
template<typename T, typename Compare, typename Allocator>
bool operator<(const Set<T, Compare, Allocator>& lhs, const Set<T, Compare, Allocator>& rhs)
{
	return lhs.delegate < rhs.delegate;
}

/// Forwarded to operator<=(const std::set<T, Compare, Allocator>& lhs, const std::set<T, Compare, Allocator>& rhs).
template<typename T, typename Compare, typename Allocator>
bool operator<=(const Set<T, Compare, Allocator>& lhs, const Set<T, Compare, Allocator>& rhs)
{
	return lhs.delegate <= rhs.delegate;
}

/// Forwarded to operator>(const std::set<T, Compare, Allocator>& lhs, const std::set<T, Compare, Allocator>& rhs).
template<typename T, typename Compare, typename Allocator>
bool operator>(const Set<T, Compare, Allocator>& lhs, const Set<T, Compare, Allocator>& rhs)
{
	return lhs.delegate > rhs.delegate;
}

/// Forwarded to operator>=(const std::set<T, Compare, Allocator>& lhs, const std::set<T, Compare, Allocator>& rhs).
template<typename T, typename Compare, typename Allocator>
bool operator>=(const Set<T, Compare, Allocator>& lhs, const Set<T, Compare, Allocator>& rhs)
{
	return lhs.delegate >= rhs.delegate;
}

/// Forwarded to swap(const std::set<T, Compare, Allocator>& lhs, const std::set<T, Compare, Allocator>& rhs).
template<typename T, typename Compare, typename Allocator>
void swap(const Set<T, Compare, Allocator>& lhs, const Set<T, Compare, Allocator>& rhs)
{
	swap(lhs.delegate, rhs.delegate);
}

} // namespace Polymorphic

#endif // Polymorphic_Set_INCLUDED
