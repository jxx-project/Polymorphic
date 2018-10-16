//
// Copyright (C) 2018 Dr. Michael Steffens
//
// SPDX-License-Identifier:	BSL-1.0
//


#ifndef Polymorphic_ForwardList_INCLUDED
#define Polymorphic_ForwardList_INCLUDED

#include <forward_list>

namespace Polymorphic {

template<typename T, typename Allocator>
class ForwardList;

template<typename T, typename Allocator>
bool operator==(const ForwardList<T, Allocator>& lhs, const ForwardList<T, Allocator>& rhs);

template<typename T, typename Allocator>
bool operator!=(const ForwardList<T, Allocator>& lhs, const ForwardList<T, Allocator>& rhs);

template<typename T, typename Allocator>
bool operator<(const ForwardList<T, Allocator>& lhs, const ForwardList<T, Allocator>& rhs);

template<typename T, typename Allocator>
bool operator<=(const ForwardList<T, Allocator>& lhs, const ForwardList<T, Allocator>& rhs);

template<typename T, typename Allocator>
bool operator>(const ForwardList<T, Allocator>& lhs, const ForwardList<T, Allocator>& rhs);

template<typename T, typename Allocator>
bool operator>=(const ForwardList<T, Allocator>& lhs, const ForwardList<T, Allocator>& rhs);

template<typename T, typename Allocator>
void swap(const ForwardList<T, Allocator>& lhs, const ForwardList<T, Allocator>& rhs);

/// Polymorphic decorator composing std::forward_list<T> with the sole purpose of adding a virtual destructor..
///
/// Classes derived from Polymorphic::ForwardList<T> can be safely used as targets of smart pointers.
/// Note: forwarding member functions are *not* declared virtual! They are not meant to be overriden
/// in subclasses. Add new behavior using new virtual members instead.
template<typename T, typename Allocator = std::allocator<T>>
class ForwardList
{
public:
	typedef std::forward_list<T, Allocator> DelegateType;
	typedef T value_type;
	typedef Allocator allocator_type;
	typedef value_type& reference;
	typedef const value_type& const_reference;
	typedef typename DelegateType::pointer pointer;
	typedef typename DelegateType::const_pointer const_pointer;
	typedef typename DelegateType::iterator iterator;
	typedef typename DelegateType::const_iterator const_iterator;
	typedef typename DelegateType::difference_type difference_type;
	typedef typename DelegateType::size_type size_type;

	/// Forwarded to std::forward_list<T>::forward_list(const allocator_type& allocator = allocator_type()).
	explicit ForwardList(const allocator_type& allocator = allocator_type()) : delegate(allocator)
	{
	}

	/// Forwarded to std::forward_list<T>::forward_list(size_type n).
	explicit ForwardList(size_type n) : delegate(n)
	{
	}

	/// Forwarded to std::forward_list<T>::forward_list(size_type n, const value_type& value, const allocator_type& allocator =
	/// allocator_type()).
	ForwardList(size_type n, const value_type& value, const allocator_type& allocator = allocator_type()) :
		delegate(n, value, allocator)
	{
	}

	/// Forwarded to std::forward_list<T>::forward_list(InputIterator first, InputIterator last, const allocator_type& allocator =
	/// allocator_type()).
	template<typename InputIterator>
	ForwardList(InputIterator first, InputIterator last, const allocator_type& allocator = allocator_type()) :
		delegate(first, last, allocator)
	{
	}

	/// Copy constructor.
	ForwardList(const ForwardList& other) : delegate(other.delegate)
	{
	}

	/// Copy constructor.
	ForwardList(const ForwardList& other, const allocator_type& allocator) : delegate(other.delegate, allocator)
	{
	}

	/// Move constructor.
	ForwardList(ForwardList&& other) : delegate(std::move(other.delegate))
	{
	}

	/// Move constructor.
	ForwardList(ForwardList&& other, const allocator_type& allocator) : delegate(std::move(other.delegate), allocator)
	{
	}

	/// Forwarded to std::forward_list<T>::forward_list(std::initializer_list<value_type> initializerList, const allocator_type&
	/// allocator = allocator_type()).
	ForwardList(std::initializer_list<value_type> initializerList, const allocator_type& allocator = allocator_type()) :
		delegate(initializerList, allocator)
	{
	}

	/// Copy construct from std::forward_list<T>.
	ForwardList(const DelegateType& other) : delegate(other)
	{
	}

	/// Copy construct from std::forward_list<T> with allocator.
	ForwardList(const DelegateType& other, const allocator_type& allocator) : delegate(other, allocator)
	{
	}

	/// Move construct from std::forward_list<T>.
	ForwardList(DelegateType&& other) : delegate(std::move(other))
	{
	}

	/// Move construct from std::forward_list<T> with allocator.
	ForwardList(DelegateType&& other, const allocator_type& allocator) : delegate(std::move(other), allocator)
	{
	}

	/// Virtual destructor permitting derived classes to be deleted safely via a ForwardList pointer.
	virtual ~ForwardList()
	{
	}

	/// Copy assignment operator
	ForwardList& operator=(const ForwardList& other)
	{
		delegate = other.delegate;
		return *this;
	}

	/// Move assignment operator
	ForwardList& operator=(ForwardList&& other)
	{
		delegate = std::move(other.delegate);
		return *this;
	}

	/// Initializer forward_list assignment operator
	ForwardList& operator=(std::initializer_list<value_type> initializerList)
	{
		delegate = initializerList;
		return *this;
	}

	/// Copy assignment from std::forward_list<T>.
	ForwardList& operator=(const DelegateType& other)
	{
		delegate = other;
		return *this;
	}

	/// Move assignment from std::forward_list<T>.
	ForwardList& operator=(DelegateType&& other)
	{
		delegate = std::move(other);
		return *this;
	}

	/// Implicit type conversion into std::forward_list<T> reference.
	operator DelegateType&()
	{
		return delegate;
	}

	/// Implicit type conversion into const std::forward_list<T> reference.
	operator const DelegateType&() const
	{
		return delegate;
	}

	/// Explicit type conversion into std::forward_list<T> rvalue reference.
	explicit operator DelegateType &&()
	{
		return std::move(delegate);
	}

	/// Forwarded to std::forward_list<T>::before_begin() noexcept.
	iterator before_begin() noexcept
	{
		return delegate.before_begin();
	}

	/// Forwarded to std::forward_list<T>::before_begin() const noexcept.
	const_iterator before_begin() const noexcept
	{
		return delegate.before_begin();
	}

	/// Forwarded to std::forward_list<T>::begin() noexcept.
	iterator begin() noexcept
	{
		return delegate.begin();
	}

	/// Forwarded to std::forward_list<T>::begin() const noexcept.
	const_iterator begin() const noexcept
	{
		return delegate.begin();
	}

	/// Forwarded to std::forward_list<T>::end() noexcept.
	iterator end() noexcept
	{
		return delegate.end();
	}

	/// Forwarded to std::forward_list<T>::end() const noexcept.
	const_iterator end() const noexcept
	{
		return delegate.end();
	}

	/// Forwarded to std::forward_list<T>::cbefore_begin() const noexcept.
	const_iterator cbefore_begin() const noexcept
	{
		return delegate.cbefore_begin();
	}

	/// Forwarded to std::forward_list<T>::cbegin() const noexcept.
	const_iterator cbegin() const noexcept
	{
		return delegate.cbegin();
	}

	/// Forwarded to std::forward_list<T>::cend() const noexcept.
	const_iterator cend() const noexcept
	{
		return delegate.cend();
	}

	/// Forwarded to std::forward_list<T>::empty() const noexcept.
	bool empty() const noexcept
	{
		return delegate.empty();
	}

	/// Forwarded to std::forward_list<T>::max_size() const noexcept.
	size_type max_size() const noexcept
	{
		return delegate.max_size();
	}

	/// Forwarded to std::forward_list<T>::front().
	reference front()
	{
		return delegate.front();
	}

	/// Forwarded to std::forward_list<T>::front(size_type n) const.
	const_reference front() const
	{
		return delegate.front();
	}

	/// Forwarded to std::forward_list<T>::assign(InputIterator first, InputIterator last).
	template<typename InputIterator>
	void assign(InputIterator first, InputIterator last)
	{
		delegate.assign(first, last);
	}

	/// Forwarded to std::forward_list<T>::assign(size_type n, const value_type& value).
	void assign(size_type n, const value_type& value)
	{
		delegate.assign(n, value);
	}

	/// Forwarded to std::forward_list<T>::assign(std::initializer_list<value_type> initializerList).
	void assign(std::initializer_list<value_type> initializerList)
	{
		delegate.assign(initializerList);
	}

	/// Forwarded to std::forward_list<T>::emplace_front(Args&&... args).
	template<class... Args>
	void emplace_front(Args&&... args)
	{
		return delegate.emplace_front(std::forward<Args>(args)...);
	}

	/// Forwarded to std::forward_list<T>::push_front(const value_type& value).
	void push_front(const value_type& value)
	{
		delegate.push_front(value);
	}

	/// Forwarded to std::forward_list<T>::push_front(value_type&& value).
	void push_front(value_type&& value)
	{
		delegate.push_front(std::move(value));
	}

	/// Forwarded to std::forward_list<T>::pop_front().
	void pop_front()
	{
		delegate.pop_front();
	}

	/// Forwarded to std::forward_list<T>::emplace_after(const_iterator position, Args&&... args).
	template<typename... Args>
	iterator emplace_after(const_iterator position, Args&&... args)
	{
		return delegate.emplace_after(position, std::forward<Args>(args)...);
	}

	/// Forwarded to std::forward_list<T>::insert_after(const_iterator position, const value_type& value).
	iterator insert_after(const_iterator position, const value_type& value)
	{
		return delegate.insert_after(position, value);
	}

	/// Forwarded to std::forward_list<T>::insert_after(const_iterator position, size_type n, const value_type& value).
	iterator insert_after(const_iterator position, size_type n, const value_type& value)
	{
		return delegate.insert_after(position, n, value);
	}

	/// Forwarded to std::forward_list<T>::insert_after(const_iterator position, InputIterator first, InputIterator last).
	template<typename InputIterator>
	iterator insert_after(const_iterator position, InputIterator first, InputIterator last)
	{
		return delegate.insert_after(position, first, last);
	}

	/// Forwarded to std::forward_list<T>::insert_after(const_iterator position, value_type&& value).
	iterator insert_after(const_iterator position, value_type&& value)
	{
		return delegate.insert_after(position, std::move(value));
	}

	/// Forwarded to std::forward_list<T>::insert_after(const_iterator position, std::initializer_list<value_type> initializerList).
	iterator insert_after(const_iterator position, std::initializer_list<value_type> initializerList)
	{
		return delegate.insert_after(position, initializerList);
	}

	/// Forwarded to std::forward_list<T>::erase_after(const_iterator position).
	iterator erase_after(const_iterator position)
	{
		return delegate.erase_after(position);
	}

	/// Forwarded to std::forward_list<T>::erase_after(const_iterator first, const_iterator last).
	iterator erase_after(const_iterator first, const_iterator last)
	{
		return delegate.erase_after(first, last);
	}

	/// Forwarded to std::forward_list<T>::swap(std::forward_list<bool>& other).
	void swap(ForwardList& other)
	{
		delegate.swap(other.delegate);
	}

	/// Forwarded to std::forward_list<T>::resize(size_type n).
	void resize(size_type n)
	{
		delegate.resize(n);
	}

	/// Forwarded to std::forward_list<T>::resize(size_type n, const value_type& value).
	void resize(size_type n, const value_type& value)
	{
		delegate.resize(n, value);
	}

	/// Forwarded to std::forward_list<T>::clear() noexcept.
	void clear() noexcept
	{
		delegate.clear();
	}

	/// Forwarded to std::forward_list<T>::splice_after(const_iterator position, forward_list& other).
	void splice_after(const_iterator position, ForwardList& other)
	{
		delegate.splice_after(position, other.delegate);
	}

	/// Forwarded to std::forward_list<T>::splice_after(const_iterator position, forward_list&& other).
	void splice_after(const_iterator position, ForwardList&& other)
	{
		delegate.splice_after(position, std::move(other.delegate));
	}

	/// Forwarded to std::forward_list<T>::splice_after(const_iterator position, forward_list& other, const_iterator i).
	void splice_after(const_iterator position, ForwardList& other, const_iterator i)
	{
		delegate.splice_after(position, other.delegate, i);
	}

	/// Forwarded to std::forward_list<T>::splice_after(const_iterator position, forward_list&& other, const_iterator i).
	void splice_after(const_iterator position, ForwardList&& other, const_iterator i)
	{
		delegate.splice_after(position, std::move(other.delegate), i);
	}

	/// Forwarded to std::forward_list<T>::splice_after(const_iterator position, forward_list& other, const_iterator first,
	/// const_iterator last).
	void splice_after(const_iterator position, ForwardList& other, const_iterator first, const_iterator last)
	{
		delegate.splice_after(position, other.delegate, first, last);
	}

	/// Forwarded to std::forward_list<T>::splice_after(const_iterator position, forward_list&& other, const_iterator first,
	/// const_iterator last).
	void splice_after(const_iterator position, ForwardList&& other, const_iterator first, const_iterator last)
	{
		delegate.splice_after(position, std::move(other.delegate), first, last);
	}

	/// Forwarded to std::forward_list<T>::remove(const value_type& value).
	void remove(const value_type& value)
	{
		delegate.remove(value);
	}

	/// Forwarded to std::forward_list<T>::remove_if(Predicate predicate).
	template<typename Predicate>
	void remove_if(Predicate predicate)
	{
		delegate.remove_if(predicate);
	}

	/// Forwarded to std::forward_list<T>::unique().
	void unique()
	{
		delegate.unique();
	}

	/// Forwarded to std::forward_list<T>::unique(BinaryPredicate predicate).
	template<typename BinaryPredicate>
	void unique(BinaryPredicate predicate)
	{
		delegate.unique(predicate);
	}

	/// Forwarded to std::forward_list<T>::merge(ForwardList& other).
	void merge(ForwardList& other)
	{
		delegate.merge(other.delegate);
	}

	/// Forwarded to std::forward_list<T>::merge(ForwardList&& other).
	void merge(ForwardList&& other)
	{
		delegate.merge(std::move(other.delegate));
	}

	/// Forwarded to std::forward_list<T>::merge(ForwardList& other, Compare compare).
	template<typename Compare>
	void merge(ForwardList& other, Compare compare)
	{
		delegate.merge(other.delegate, compare);
	}

	/// Forwarded to std::forward_list<T>::merge(ForwardList&& other, Compare compare).
	template<typename Compare>
	void merge(ForwardList&& other, Compare compare)
	{
		delegate.merge(std::move(other.delegate), compare);
	}

	/// Forwarded to std::forward_list<T>::sort().
	void sort()
	{
		delegate.sort();
	}

	/// Forwarded to std::forward_list<T>::sort(Compare compare).
	template<typename Compare>
	void sort(Compare compare)
	{
		delegate.sort(compare);
	}

	/// Forwarded to std::forward_list<T>::reverse() noexcept.
	void reverse() noexcept
	{
		delegate.reverse();
	}

	/// Forwarded to std::forward_list<T>::get_allocator() const noexcept.
	allocator_type get_allocator() const noexcept
	{
		return delegate.get_allocator();
	}

private:
	DelegateType delegate;

	// clang-format off
	friend bool operator== <T, Allocator>(const ForwardList& lhs, const ForwardList& rhs);
	friend bool operator!= <T, Allocator>(const ForwardList& lhs, const ForwardList& rhs);
	friend bool operator< <T, Allocator>(const ForwardList& lhs, const ForwardList& rhs);
	friend bool operator<= <T, Allocator>(const ForwardList& lhs, const ForwardList& rhs);
	friend bool operator> <T, Allocator>(const ForwardList& lhs, const ForwardList& rhs);
	friend bool operator>= <T, Allocator>(const ForwardList& lhs, const ForwardList& rhs);
	// clang-format on
	friend void Polymorphic::swap<T, Allocator>(const ForwardList<T, Allocator>& lhs, const ForwardList<T, Allocator>& rhs);
};

/// Forwarded to operator==(const std::forward_list<T, Allocator>& lhs, const std::forward_list<T, Allocator>& rhs).
template<typename T, typename Allocator>
bool operator==(const ForwardList<T, Allocator>& lhs, const ForwardList<T, Allocator>& rhs)
{
	return lhs.delegate == rhs.delegate;
}

/// Forwarded to operator!=(const std::forward_list<T, Allocator>& lhs, const std::forward_list<T, Allocator>& rhs).
template<typename T, typename Allocator>
bool operator!=(const ForwardList<T, Allocator>& lhs, const ForwardList<T, Allocator>& rhs)
{
	return lhs.delegate != rhs.delegate;
}

/// Forwarded to operator<(const std::forward_list<T, Allocator>& lhs, const std::forward_list<T, Allocator>& rhs).
template<typename T, typename Allocator>
bool operator<(const ForwardList<T, Allocator>& lhs, const ForwardList<T, Allocator>& rhs)
{
	return lhs.delegate < rhs.delegate;
}

/// Forwarded to operator<=(const std::forward_list<T, Allocator>& lhs, const std::forward_list<T, Allocator>& rhs).
template<typename T, typename Allocator>
bool operator<=(const ForwardList<T, Allocator>& lhs, const ForwardList<T, Allocator>& rhs)
{
	return lhs.delegate <= rhs.delegate;
}

/// Forwarded to operator>(const std::forward_list<T, Allocator>& lhs, const std::forward_list<T, Allocator>& rhs).
template<typename T, typename Allocator>
bool operator>(const ForwardList<T, Allocator>& lhs, const ForwardList<T, Allocator>& rhs)
{
	return lhs.delegate > rhs.delegate;
}

/// Forwarded to operator>=(const std::forward_list<T, Allocator>& lhs, const std::forward_list<T, Allocator>& rhs).
template<typename T, typename Allocator>
bool operator>=(const ForwardList<T, Allocator>& lhs, const ForwardList<T, Allocator>& rhs)
{
	return lhs.delegate >= rhs.delegate;
}

/// Forwarded to swap(const std::forward_list<T, Allocator>& lhs, const std::forward_list<T, Allocator>& rhs).
template<typename T, typename Allocator>
void swap(const ForwardList<T, Allocator>& lhs, const ForwardList<T, Allocator>& rhs)
{
	swap(lhs.delegate, rhs.delegate);
}

} // namespace Polymorphic

#endif // Polymorphic_ForwardList_INCLUDED
