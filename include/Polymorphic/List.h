//
// Copyright (C) 2018 Dr. Michael Steffens
//
// SPDX-License-Identifier:		BSL-1.0
//


#ifndef Polymorphic_List_INCLUDED
#define Polymorphic_List_INCLUDED

#include <list>

namespace Polymorphic {

template<typename T, typename Allocator>
class List;

template<typename T, typename Allocator>
bool operator==(const List<T, Allocator>& lhs, const List<T, Allocator>& rhs);

template<typename T, typename Allocator>
bool operator!=(const List<T, Allocator>& lhs, const List<T, Allocator>& rhs);

template<typename T, typename Allocator>
bool operator<(const List<T, Allocator>& lhs, const List<T, Allocator>& rhs);

template<typename T, typename Allocator>
bool operator<=(const List<T, Allocator>& lhs, const List<T, Allocator>& rhs);

template<typename T, typename Allocator>
bool operator>(const List<T, Allocator>& lhs, const List<T, Allocator>& rhs);

template<typename T, typename Allocator>
bool operator>=(const List<T, Allocator>& lhs, const List<T, Allocator>& rhs);

template<typename T, typename Allocator>
void swap(const List<T, Allocator>& lhs, const List<T, Allocator>& rhs);

/// Polymorphic decorator composing std::list<T> with the sole purpose of adding a virtual destructor..
///
/// Classes derived from Polymorphic::List<T> can be safely used as targets of smart pointers.
/// Note: forwarding member functions are *not* declared virtual! They are not meant to be overriden
/// in subclasses. Add new behavior using new virtual members instead.
template< typename T, typename Allocator = std::allocator<T> >
class List
{
public:
	typedef std::list<T, Allocator> DelegateType;
	typedef T value_type;
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

	/// Forwarded to std::list<T>::list(const allocator_type& allocator = allocator_type()).
	explicit List(const allocator_type& allocator = allocator_type()) : delegate(allocator)
	{
	}

	/// Forwarded to std::list<T>::list(size_type n).
	explicit List(size_type n) : delegate(n)
	{
	}

	/// Forwarded to std::list<T>::list(size_type n, const value_type& value, const allocator_type& allocator = allocator_type()).
	List(size_type n, const value_type& value, const allocator_type& allocator = allocator_type()) : delegate(n, value, allocator)
	{
	}

	/// Forwarded to std::list<T>::list(InputIterator first, InputIterator last, const allocator_type& allocator = allocator_type()).
	template<typename InputIterator>
	List(InputIterator first, InputIterator last, const allocator_type& allocator = allocator_type()) : delegate(first, last, allocator)
	{
	}

	/// Copy constructor.
	List(const List& other) : delegate(other.delegate)
	{
	}

	/// Copy constructor.
	List(const List& other, const allocator_type& allocator) : delegate(other.delegate, allocator)
	{
	}

	/// Move constructor.
	List(List&& other) : delegate(std::move(other.delegate))
	{
	}

	/// Move constructor.
	List(List&& other, const allocator_type& allocator) : delegate(std::move(other.delegate), allocator)
	{
	}

	/// Forwarded to std::list<T>::list(std::initializer_list<value_type> initializerList, const allocator_type& allocator = allocator_type()).
	List(std::initializer_list<value_type> initializerList, const allocator_type& allocator = allocator_type()) : delegate(initializerList, allocator)
	{
	}

	/// Copy construct from std::list<T>.
	List(const DelegateType& other) : delegate(other)
	{
	}

	/// Copy construct from std::list<T> with allocator.
	List(const DelegateType& other, const allocator_type& allocator) : delegate(other, allocator)
	{
	}

	/// Move construct from std::list<T>.
	List(DelegateType&& other) : delegate(std::move(other))
	{
	}

	/// Move construct from std::list<T> with allocator.
	List(DelegateType&& other, const allocator_type& allocator) : delegate(std::move(other), allocator)
	{
	}

	/// Virtual destructor permitting derived classes to be deleted safely via a List pointer.
	virtual ~List()
	{
	}

	/// Copy assignment operator
	List& operator=(const List& other)
	{
		delegate = other.delegate;
		return *this;
	}

	/// Move assignment operator
	List& operator=(List&& other)
	{
		delegate = std::move(other.delegate);
		return *this;
	}

	/// Initializer list assignment operator
	List& operator=(std::initializer_list<value_type> initializerList)
	{
		delegate = initializerList;
		return *this;
	}

	/// Copy assignment from std::list<T>.
	List& operator=(const DelegateType& other)
	{
		delegate = other;
		return *this;
	}

	/// Move assignment from std::list<T>.
	List& operator=(DelegateType&& other)
	{
		delegate = std::move(other);
		return *this;
	}

	/// Implicit type conversion into std::list<T> reference.
	operator DelegateType&()
	{
		return delegate;
	}

	/// Implicit type conversion into const std::list<T> reference.
	operator const DelegateType&() const
	{
		return delegate;
	}

	/// Explicit type conversion into std::list<T> rvalue reference.
	explicit operator DelegateType&&()
	{
		return std::move(delegate);
	}

	/// Forwarded to std::list<T>::begin() noexcept.
	iterator begin() noexcept
	{
		return delegate.begin();
	}

	/// Forwarded to std::list<T>::begin() const noexcept.
	const_iterator begin() const noexcept
	{
		return delegate.begin();
	}

	/// Forwarded to std::list<T>::end() noexcept.
	iterator end() noexcept
	{
		return delegate.end();
	}

	/// Forwarded to std::list<T>::end() const noexcept.
	const_iterator end() const noexcept
	{
		return delegate.end();
	}

	/// Forwarded to std::list<T>::rbegin() noexcept.
	reverse_iterator rbegin() noexcept
	{
		return delegate.rbegin();
	}

	/// Forwarded to std::list<T>::rbegin() const noexcept.
	const_reverse_iterator rbegin() const noexcept
	{
		return delegate.rbegin();
	}

	/// Forwarded to std::list<T>::rend() noexcept.
	reverse_iterator rend() noexcept
	{
		return delegate.rend();
	}

	/// Forwarded to std::list<T>::rend() const noexcept.
	const_reverse_iterator rend() const noexcept
	{
		return delegate.rend();
	}

	/// Forwarded to std::list<T>::cbegin() const noexcept.
	const_iterator cbegin() const noexcept
	{
		return delegate.cbegin();
	}

	/// Forwarded to std::list<T>::cend() const noexcept.
	const_iterator cend() const noexcept
	{
		return delegate.cend();
	}

	/// Forwarded to std::list<T>::crbegin() const noexcept.
	const_reverse_iterator crbegin() const noexcept
	{
		return delegate.crbegin();
	}

	/// Forwarded to std::list<T>::crend() const noexcept.
	const_reverse_iterator crend() const noexcept
	{
		return delegate.crend();
	}

	/// Forwarded to std::list<T>::empty() const noexcept.
	bool empty() const noexcept
	{
		return delegate.empty();
	}

	/// Forwarded to std::list<T>::size() const noexcept.
	size_type size() const noexcept
	{
		return delegate.size();
	}

	/// Forwarded to std::list<T>::max_size() const noexcept.
	size_type max_size() const noexcept
	{
		return delegate.max_size();
	}

	/// Forwarded to std::list<T>::front().
	reference front()
	{
		return delegate.front();
	}

	/// Forwarded to std::list<T>::front(size_type n) const.
	const_reference front() const
	{
		return delegate.front();
	}

	/// Forwarded to std::list<T>::back().
	reference back()
	{
		return delegate.back();
	}

	/// Forwarded to std::list<T>::back(size_type n) const.
	const_reference back() const
	{
		return delegate.back();
	}

	/// Forwarded to std::list<T>::assign(InputIterator first, InputIterator last).
	template<typename InputIterator>
	void assign(InputIterator first, InputIterator last)
	{
		delegate.assign(first, last);
	}

	/// Forwarded to std::list<T>::assign(size_type n, const value_type& value).
	void assign(size_type n, const value_type& value)
	{
		delegate.assign(n, value);
	}

	/// Forwarded to std::list<T>::assign(std::initializer_list<value_type> initializerList).
	void assign(std::initializer_list<value_type> initializerList)
	{
		delegate.assign(initializerList);
	}

	/// Forwarded to std::list<T>::emplace_front(Args&&... args).
	template<class... Args>
	void emplace_front(Args&&... args)
	{
		return delegate.emplace_front(std::forward<Args>(args)...);
	}

	/// Forwarded to std::list<T>::push_front(const value_type& value).
	void push_front(const value_type& value)
	{
		delegate.push_front(value);
	}

	/// Forwarded to std::list<T>::push_front(value_type&& value).
	void push_front(value_type&& value)
	{
		delegate.push_front(std::move(value));
	}

	/// Forwarded to std::list<T>::pop_front().
	void pop_front()
	{
		delegate.pop_front();
	}

	/// Forwarded to std::list<T>::emplace_back(Args&&... args).
	template<class... Args>
	void emplace_back(Args&&... args)
	{
		return delegate.emplace_back(std::forward<Args>(args)...);
	}

	/// Forwarded to std::list<T>::push_back(const value_type& value).
	void push_back(const value_type& value)
	{
		delegate.push_back(value);
	}

	/// Forwarded to std::list<T>::push_back(value_type&& value).
	void push_back(value_type&& value)
	{
		delegate.push_back(std::move(value));
	}

	/// Forwarded to std::list<T>::pop_back().
	void pop_back()
	{
		delegate.pop_back();
	}

	/// Forwarded to std::list<T>::emplace(const_iterator position, Args&&... args).
	template<typename... Args>
	iterator emplace(const_iterator position, Args&&... args)
	{
		return delegate.emplace(position, std::forward<Args>(args)...);
	}

	/// Forwarded to std::list<T>::insert(const_iterator position, const value_type& value).
	iterator insert(const_iterator position, const value_type& value)
	{
		return delegate.insert(position, value);
	}

	/// Forwarded to std::list<T>::insert(const_iterator position, size_type n, const value_type& value).
	iterator insert(const_iterator position, size_type n, const value_type& value)
	{
		return delegate.insert(position, n, value);
	}

	/// Forwarded to std::list<T>::insert(const_iterator position, InputIterator first, InputIterator last).
	template<typename InputIterator>
	iterator insert(const_iterator position, InputIterator first, InputIterator last)
	{
		return delegate.insert(position, first, last);
	}

	/// Forwarded to std::list<T>::insert(const_iterator position, value_type&& value).
	iterator insert(const_iterator position, value_type&& value)
	{
		return delegate.insert(position, std::move(value));
	}

	/// Forwarded to std::list<T>::insert(const_iterator position, std::initializer_list<value_type> initializerList).
	iterator insert(const_iterator position, std::initializer_list<value_type> initializerList)
	{
		return delegate.insert(position, initializerList);
	}

	/// Forwarded to std::list<T>::erase(const_iterator position).
	iterator erase(const_iterator position)
	{
		return delegate.erase(position);
	}

	/// Forwarded to std::list<T>::erase(const_iterator first, const_iterator last).
	iterator erase(const_iterator first, const_iterator last)
	{
		return delegate.erase(first, last);
	}

	/// Forwarded to std::list<T>::swap(std::list<bool>& other).
	void swap(List& other)
	{
		delegate.swap(other.delegate);
	}

	/// Forwarded to std::list<T>::resize(size_type n).
	void resize(size_type n)
	{
		delegate.resize(n);
	}

	/// Forwarded to std::list<T>::resize(size_type n, const value_type& value).
	void resize(size_type n, const value_type& value)
	{
		delegate.resize(n, value);
	}

	/// Forwarded to std::list<T>::clear() noexcept.
	void clear() noexcept
	{
		delegate.clear();
	}

	/// Forwarded to std::list<T>::splice(const_iterator position, list& other).
	void splice(const_iterator position, List& other)
	{
		delegate.splice(position, other.delegate);
	}

	/// Forwarded to std::list<T>::splice(const_iterator position, list&& other).
	void splice(const_iterator position, List&& other)
	{
		delegate.splice(position, std::move(other.delegate));
	}

	/// Forwarded to std::list<T>::splice(const_iterator position, list& other, const_iterator i).
	void splice(const_iterator position, List& other, const_iterator i)
	{
		delegate.splice(position, other.delegate, i);
	}

	/// Forwarded to std::list<T>::splice(const_iterator position, list&& other, const_iterator i).
	void splice(const_iterator position, List&& other, const_iterator i)
	{
		delegate.splice(position, std::move(other.delegate), i);
	}

	/// Forwarded to std::list<T>::splice(const_iterator position, list& other, const_iterator first, const_iterator last).
	void splice(const_iterator position, List& other, const_iterator first, const_iterator last)
	{
		delegate.splice(position, other.delegate, first, last);
	}

	/// Forwarded to std::list<T>::splice(const_iterator position, list&& other, const_iterator first, const_iterator last).
	void splice(const_iterator position, List&& other, const_iterator first, const_iterator last)
	{
		delegate.splice(position, std::move(other.delegate), first, last);
	}

	/// Forwarded to std::list<T>::remove(const value_type& value).
	void remove(const value_type& value)
	{
		delegate.remove(value);
	}

	/// Forwarded to std::list<T>::remove_if(Predicate predicate).
	template<typename Predicate>
	void remove_if(Predicate predicate)
	{
		delegate.remove_if(predicate);
	}

	/// Forwarded to std::list<T>::unique().
	void unique()
	{
		delegate.unique();
	}

	/// Forwarded to std::list<T>::unique(BinaryPredicate predicate).
	template<typename BinaryPredicate>
	void unique(BinaryPredicate predicate)
	{
		delegate.unique(predicate);
	}

	/// Forwarded to std::list<T>::merge(List& other).
	void merge(List& other)
	{
		delegate.merge(other.delegate);
	}

	/// Forwarded to std::list<T>::merge(List&& other).
	void merge(List&& other)
	{
		delegate.merge(std::move(other.delegate));
	}

	/// Forwarded to std::list<T>::merge(List& other, Compare compare).
	template<typename Compare>
	void merge(List& other, Compare compare)
	{
		delegate.merge(other.delegate, compare);
	}

	/// Forwarded to std::list<T>::merge(List&& other, Compare compare).
	template<typename Compare>
	void merge(List&& other, Compare compare)
	{
		delegate.merge(std::move(other.delegate), compare);
	}

	/// Forwarded to std::list<T>::sort().
	void sort()
	{
		delegate.sort();
	}

	/// Forwarded to std::list<T>::sort(Compare compare).
	template<typename Compare>
	void sort(Compare compare)
	{
		delegate.sort(compare);
	}

	/// Forwarded to std::list<T>::reverse() noexcept.
	void reverse() noexcept
	{
		delegate.reverse();
	}

	/// Forwarded to std::list<T>::get_allocator() const noexcept.
	allocator_type get_allocator() const noexcept
	{
		return delegate.get_allocator();
	}

private:
	DelegateType delegate;

	friend bool operator== <T, Allocator> (const List& lhs, const List& rhs);
	friend bool operator!= <T, Allocator> (const List& lhs, const List& rhs);
	friend bool operator<  <T, Allocator> (const List& lhs, const List& rhs);
	friend bool operator<= <T, Allocator> (const List& lhs, const List& rhs);
	friend bool operator>  <T, Allocator> (const List& lhs, const List& rhs);
	friend bool operator>= <T, Allocator> (const List& lhs, const List& rhs);
	friend void Polymorphic::swap<T, Allocator>(const List<T, Allocator>& lhs, const List<T, Allocator>& rhs);
};

/// Forwarded to operator==(const std::list<T, Allocator>& lhs, const std::list<T, Allocator>& rhs).
template<typename T, typename Allocator>
bool operator==(const List<T, Allocator>& lhs, const List<T, Allocator>& rhs)
{
	return lhs.delegate == rhs.delegate;
}

/// Forwarded to operator!=(const std::list<T, Allocator>& lhs, const std::list<T, Allocator>& rhs).
template<typename T, typename Allocator>
bool operator!=(const List<T, Allocator>& lhs, const List<T, Allocator>& rhs)
{
	return lhs.delegate != rhs.delegate;
}

/// Forwarded to operator<(const std::list<T, Allocator>& lhs, const std::list<T, Allocator>& rhs).
template<typename T, typename Allocator>
bool operator<(const List<T, Allocator>& lhs, const List<T, Allocator>& rhs)
{
	return lhs.delegate < rhs.delegate;
}

/// Forwarded to operator<=(const std::list<T, Allocator>& lhs, const std::list<T, Allocator>& rhs).
template<typename T, typename Allocator>
bool operator<=(const List<T, Allocator>& lhs, const List<T, Allocator>& rhs)
{
	return lhs.delegate <= rhs.delegate;
}

/// Forwarded to operator>(const std::list<T, Allocator>& lhs, const std::list<T, Allocator>& rhs).
template<typename T, typename Allocator>
bool operator>(const List<T, Allocator>& lhs, const List<T, Allocator>& rhs)
{
	return lhs.delegate > rhs.delegate;
}

/// Forwarded to operator>=(const std::list<T, Allocator>& lhs, const std::list<T, Allocator>& rhs).
template<typename T, typename Allocator>
bool operator>=(const List<T, Allocator>& lhs, const List<T, Allocator>& rhs)
{
	return lhs.delegate >= rhs.delegate;
}

/// Forwarded to swap(const std::list<T, Allocator>& lhs, const std::list<T, Allocator>& rhs).
template<typename T, typename Allocator>
void swap(const List<T, Allocator>& lhs, const List<T, Allocator>& rhs)
{
	swap(lhs.delegate, rhs.delegate);
}

} // namespace Polymorphic

#endif // Polymorphic_List_INCLUDED
