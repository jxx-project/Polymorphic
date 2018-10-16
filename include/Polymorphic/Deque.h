//
// Copyright (C) 2018 Dr. Michael Steffens
//
// SPDX-License-Identifier:	BSL-1.0
//


#ifndef Polymorphic_Deque_INCLUDED
#define Polymorphic_Deque_INCLUDED

#include <deque>

namespace Polymorphic {

template<typename T, typename Allocator>
class Deque;

template<typename T, typename Allocator>
bool operator==(const Deque<T, Allocator>& lhs, const Deque<T, Allocator>& rhs);

template<typename T, typename Allocator>
bool operator!=(const Deque<T, Allocator>& lhs, const Deque<T, Allocator>& rhs);

template<typename T, typename Allocator>
bool operator<(const Deque<T, Allocator>& lhs, const Deque<T, Allocator>& rhs);

template<typename T, typename Allocator>
bool operator<=(const Deque<T, Allocator>& lhs, const Deque<T, Allocator>& rhs);

template<typename T, typename Allocator>
bool operator>(const Deque<T, Allocator>& lhs, const Deque<T, Allocator>& rhs);

template<typename T, typename Allocator>
bool operator>=(const Deque<T, Allocator>& lhs, const Deque<T, Allocator>& rhs);

template<typename T, typename Allocator>
void swap(const Deque<T, Allocator>& lhs, const Deque<T, Allocator>& rhs);

/// Polymorphic decorator composing std::deque<T> with the sole purpose of adding a virtual destructor..
///
/// Classes derived from Polymorphic::Deque<T> can be safely used as targets of smart pointers.
/// Note: forwarding member functions are *not* declared virtual! They are not meant to be overriden
/// in subclasses. Add new behavior using new virtual members instead.
template<typename T, typename Allocator = std::allocator<T>>
class Deque
{
public:
	typedef std::deque<T, Allocator> DelegateType;
	typedef T value_type;
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

	/// Forwarded to std::deque<T>::deque(const allocator_type& allocator = allocator_type()).
	explicit Deque(const allocator_type& allocator = allocator_type()) : delegate(allocator)
	{
	}

	/// Forwarded to std::deque<T>::deque(size_type n).
	explicit Deque(size_type n) : delegate(n)
	{
	}

	/// Forwarded to std::deque<T>::deque(size_type n, const value_type& value, const allocator_type& allocator =
	/// allocator_type()).
	Deque(size_type n, const value_type& value, const allocator_type& allocator = allocator_type()) : delegate(n, value, allocator)
	{
	}

	/// Forwarded to std::deque<T>::deque(InputIterator first, InputIterator last, const allocator_type& allocator =
	/// allocator_type()).
	template<typename InputIterator>
	Deque(InputIterator first, InputIterator last, const allocator_type& allocator = allocator_type()) :
		delegate(first, last, allocator)
	{
	}

	/// Copy constructor.
	Deque(const Deque& other) : delegate(other.delegate)
	{
	}

	/// Copy constructor.
	Deque(const Deque& other, const allocator_type& allocator) : delegate(other.delegate, allocator)
	{
	}

	/// Move constructor.
	Deque(Deque&& other) : delegate(std::move(other.delegate))
	{
	}

	/// Move constructor.
	Deque(Deque&& other, const allocator_type& allocator) : delegate(std::move(other.delegate), allocator)
	{
	}

	/// Forwarded to std::deque<T>::deque(std::initializer_list<value_type> initializerList, const allocator_type& allocator =
	/// allocator_type()).
	Deque(std::initializer_list<value_type> initializerList, const allocator_type& allocator = allocator_type()) :
		delegate(initializerList, allocator)
	{
	}

	/// Copy construct from std::deque<T>.
	Deque(const DelegateType& other) : delegate(other)
	{
	}

	/// Copy construct from std::deque<T> with allocator.
	Deque(const DelegateType& other, const allocator_type& allocator) : delegate(other, allocator)
	{
	}

	/// Move construct from std::deque<T>.
	Deque(DelegateType&& other) : delegate(std::move(other))
	{
	}

	/// Move construct from std::deque<T> with allocator.
	Deque(DelegateType&& other, const allocator_type& allocator) : delegate(std::move(other), allocator)
	{
	}

	/// Virtual destructor permitting derived classes to be deleted safely via a Deque pointer.
	virtual ~Deque()
	{
	}

	/// Copy assignment operator
	Deque& operator=(const Deque& other)
	{
		delegate = other.delegate;
		return *this;
	}

	/// Move assignment operator
	Deque& operator=(Deque&& other)
	{
		delegate = std::move(other.delegate);
		return *this;
	}

	/// Initializer list assignment operator
	Deque& operator=(std::initializer_list<value_type> initializerList)
	{
		delegate = initializerList;
		return *this;
	}

	/// Copy assignment from std::deque<T>.
	Deque& operator=(const DelegateType& other)
	{
		delegate = other;
		return *this;
	}

	/// Move assignment from std::deque<T>.
	Deque& operator=(DelegateType&& other)
	{
		delegate = std::move(other);
		return *this;
	}

	/// Implicit type conversion into std::deque<T> reference.
	operator DelegateType&()
	{
		return delegate;
	}

	/// Implicit type conversion into const std::deque<T> reference.
	operator const DelegateType&() const
	{
		return delegate;
	}

	/// Explicit type conversion into std::deque<T> rvalue reference.
	explicit operator DelegateType &&()
	{
		return std::move(delegate);
	}

	/// Forwarded to std::deque<T>::begin() noexcept.
	iterator begin() noexcept
	{
		return delegate.begin();
	}

	/// Forwarded to std::deque<T>::begin() const noexcept.
	const_iterator begin() const noexcept
	{
		return delegate.begin();
	}

	/// Forwarded to std::deque<T>::end() noexcept.
	iterator end() noexcept
	{
		return delegate.end();
	}

	/// Forwarded to std::deque<T>::end() const noexcept.
	const_iterator end() const noexcept
	{
		return delegate.end();
	}

	/// Forwarded to std::deque<T>::rbegin() noexcept.
	reverse_iterator rbegin() noexcept
	{
		return delegate.rbegin();
	}

	/// Forwarded to std::deque<T>::rbegin() const noexcept.
	const_reverse_iterator rbegin() const noexcept
	{
		return delegate.rbegin();
	}

	/// Forwarded to std::deque<T>::rend() noexcept.
	reverse_iterator rend() noexcept
	{
		return delegate.rend();
	}

	/// Forwarded to std::deque<T>::rend() const noexcept.
	const_reverse_iterator rend() const noexcept
	{
		return delegate.rend();
	}

	/// Forwarded to std::deque<T>::cbegin() const noexcept.
	const_iterator cbegin() const noexcept
	{
		return delegate.cbegin();
	}

	/// Forwarded to std::deque<T>::cend() const noexcept.
	const_iterator cend() const noexcept
	{
		return delegate.cend();
	}

	/// Forwarded to std::deque<T>::crbegin() const noexcept.
	const_reverse_iterator crbegin() const noexcept
	{
		return delegate.crbegin();
	}

	/// Forwarded to std::deque<T>::crend() const noexcept.
	const_reverse_iterator crend() const noexcept
	{
		return delegate.crend();
	}

	/// Forwarded to std::deque<T>::empty() const noexcept.
	bool empty() const noexcept
	{
		return delegate.empty();
	}

	/// Forwarded to std::deque<T>::size() const noexcept.
	size_type size() const noexcept
	{
		return delegate.size();
	}

	/// Forwarded to std::deque<T>::max_size() const noexcept.
	size_type max_size() const noexcept
	{
		return delegate.max_size();
	}

	/// Forwarded to std::deque<T>::resize(size_type n).
	void resize(size_type n)
	{
		delegate.resize(n);
	}

	/// Forwarded to std::deque<T>::resize(size_type n, const value_type& value).
	void resize(size_type n, const value_type& value)
	{
		delegate.resize(n, value);
	}

	/// Forwarded to std::deque<T>::shrink_to_fit().
	void shrink_to_fit()
	{
		delegate.shrink_to_fit();
	}

	/// Forwarded to std::deque<T>::operator[](size_type n).
	reference operator[](size_type n)
	{
		return delegate[n];
	}

	/// Forwarded to std::deque<T>::operator[](size_type n) const.
	const_reference operator[](size_type n) const
	{
		return delegate[n];
	}

	/// Forwarded to std::deque<T>::at(size_type n).
	reference at(size_type n)
	{
		return delegate.at(n);
	}

	/// Forwarded to std::deque<T>::at(size_type n) const.
	const_reference at(size_type n) const
	{
		return delegate.at(n);
	}

	/// Forwarded to std::deque<T>::front().
	reference front()
	{
		return delegate.front();
	}

	/// Forwarded to std::deque<T>::front(size_type n) const.
	const_reference front() const
	{
		return delegate.front();
	}

	/// Forwarded to std::deque<T>::back().
	reference back()
	{
		return delegate.back();
	}

	/// Forwarded to std::deque<T>::back(size_type n) const.
	const_reference back() const
	{
		return delegate.back();
	}

	/// Forwarded to std::deque<T>::data().
	value_type* data()
	{
		return delegate.data();
	}

	/// Forwarded to std::deque<T>::data(size_type n) const.
	const value_type* data() const
	{
		return delegate.data();
	}

	/// Forwarded to std::deque<T>::assign(InputIterator first, InputIterator last).
	template<typename InputIterator>
	void assign(InputIterator first, InputIterator last)
	{
		delegate.assign(first, last);
	}

	/// Forwarded to std::deque<T>::assign(size_type n, const value_type& value).
	void assign(size_type n, const value_type& value)
	{
		delegate.assign(n, value);
	}

	/// Forwarded to std::deque<T>::assign(std::initializer_list<value_type> initializerList).
	void assign(std::initializer_list<value_type> initializerList)
	{
		delegate.assign(initializerList);
	}

	/// Forwarded to std::deque<T>::emplace_front(Args&&... args).
	template<class... Args>
	void emplace_front(Args&&... args)
	{
		return delegate.emplace_front(std::forward<Args>(args)...);
	}

	/// Forwarded to std::deque<T>::push_front(const value_type& value).
	void push_front(const value_type& value)
	{
		delegate.push_front(value);
	}

	/// Forwarded to std::deque<T>::push_front(value_type&& value).
	void push_front(value_type&& value)
	{
		delegate.push_front(std::move(value));
	}

	/// Forwarded to std::deque<T>::pop_front().
	void pop_front()
	{
		delegate.pop_front();
	}

	/// Forwarded to std::deque<T>::emplace_back(Args&&... args).
	template<class... Args>
	void emplace_back(Args&&... args)
	{
		return delegate.emplace_back(std::forward<Args>(args)...);
	}

	/// Forwarded to std::deque<T>::push_back(const value_type& value).
	void push_back(const value_type& value)
	{
		delegate.push_back(value);
	}

	/// Forwarded to std::deque<T>::push_back(value_type&& value).
	void push_back(value_type&& value)
	{
		delegate.push_back(std::move(value));
	}

	/// Forwarded to std::deque<T>::pop_back().
	void pop_back()
	{
		delegate.pop_back();
	}

	/// Forwarded to std::deque<T>::emplace(const_iterator position, Args&&... args).
	template<typename... Args>
	iterator emplace(const_iterator position, Args&&... args)
	{
		return delegate.emplace(position, std::forward<Args>(args)...);
	}

	/// Forwarded to std::deque<T>::insert(const_iterator position, const value_type& value).
	iterator insert(const_iterator position, const value_type& value)
	{
		return delegate.insert(position, value);
	}

	/// Forwarded to std::deque<T>::insert(const_iterator position, size_type n, const value_type& value).
	iterator insert(const_iterator position, size_type n, const value_type& value)
	{
		return delegate.insert(position, n, value);
	}

	/// Forwarded to std::deque<T>::insert(const_iterator position, InputIterator first, InputIterator last).
	template<typename InputIterator>
	iterator insert(const_iterator position, InputIterator first, InputIterator last)
	{
		return delegate.insert(position, first, last);
	}

	/// Forwarded to std::deque<T>::insert(const_iterator position, value_type&& value).
	iterator insert(const_iterator position, value_type&& value)
	{
		return delegate.insert(position, std::move(value));
	}

	/// Forwarded to std::deque<T>::insert(const_iterator position, std::initializer_list<value_type> initializerList).
	iterator insert(const_iterator position, std::initializer_list<value_type> initializerList)
	{
		return delegate.insert(position, initializerList);
	}

	/// Forwarded to std::deque<T>::erase(const_iterator position).
	iterator erase(const_iterator position)
	{
		return delegate.erase(position);
	}

	/// Forwarded to std::deque<T>::erase(const_iterator first, const_iterator last).
	iterator erase(const_iterator first, const_iterator last)
	{
		return delegate.erase(first, last);
	}

	/// Forwarded to std::deque<T>::swap(std::deque<bool>& other).
	void swap(Deque& other)
	{
		delegate.swap(other.delegate);
	}

	/// Forwarded to std::deque<T>::clear() noexcept.
	void clear() noexcept
	{
		delegate.clear();
	}

	/// Forwarded to std::deque<T>::get_allocator() const noexcept.
	allocator_type get_allocator() const noexcept
	{
		return delegate.get_allocator();
	}

private:
	DelegateType delegate;

	// clang-format off
	friend bool operator== <T, Allocator>(const Deque& lhs, const Deque& rhs);
	friend bool operator!= <T, Allocator>(const Deque& lhs, const Deque& rhs);
	friend bool operator< <T, Allocator>(const Deque& lhs, const Deque& rhs);
	friend bool operator<= <T, Allocator>(const Deque& lhs, const Deque& rhs);
	friend bool operator> <T, Allocator>(const Deque& lhs, const Deque& rhs);
	friend bool operator>= <T, Allocator>(const Deque& lhs, const Deque& rhs);
	// clang-format on
	friend void Polymorphic::swap<T, Allocator>(const Deque<T, Allocator>& lhs, const Deque<T, Allocator>& rhs);
};

/// Forwarded to operator==(const std::deque<T, Allocator>& lhs, const std::deque<T, Allocator>& rhs).
template<typename T, typename Allocator>
bool operator==(const Deque<T, Allocator>& lhs, const Deque<T, Allocator>& rhs)
{
	return lhs.delegate == rhs.delegate;
}

/// Forwarded to operator!=(const std::deque<T, Allocator>& lhs, const std::deque<T, Allocator>& rhs).
template<typename T, typename Allocator>
bool operator!=(const Deque<T, Allocator>& lhs, const Deque<T, Allocator>& rhs)
{
	return lhs.delegate != rhs.delegate;
}

/// Forwarded to operator<(const std::deque<T, Allocator>& lhs, const std::deque<T, Allocator>& rhs).
template<typename T, typename Allocator>
bool operator<(const Deque<T, Allocator>& lhs, const Deque<T, Allocator>& rhs)
{
	return lhs.delegate < rhs.delegate;
}

/// Forwarded to operator<=(const std::deque<T, Allocator>& lhs, const std::deque<T, Allocator>& rhs).
template<typename T, typename Allocator>
bool operator<=(const Deque<T, Allocator>& lhs, const Deque<T, Allocator>& rhs)
{
	return lhs.delegate <= rhs.delegate;
}

/// Forwarded to operator>(const std::deque<T, Allocator>& lhs, const std::deque<T, Allocator>& rhs).
template<typename T, typename Allocator>
bool operator>(const Deque<T, Allocator>& lhs, const Deque<T, Allocator>& rhs)
{
	return lhs.delegate > rhs.delegate;
}

/// Forwarded to operator>=(const std::deque<T, Allocator>& lhs, const std::deque<T, Allocator>& rhs).
template<typename T, typename Allocator>
bool operator>=(const Deque<T, Allocator>& lhs, const Deque<T, Allocator>& rhs)
{
	return lhs.delegate >= rhs.delegate;
}

/// Forwarded to swap(const std::deque<T, Allocator>& lhs, const std::deque<T, Allocator>& rhs).
template<typename T, typename Allocator>
void swap(const Deque<T, Allocator>& lhs, const Deque<T, Allocator>& rhs)
{
	swap(lhs.delegate, rhs.delegate);
}

} // namespace Polymorphic

#endif // Polymorphic_Deque_INCLUDED
