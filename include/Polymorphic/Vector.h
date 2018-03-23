//
// Copyright (C) 2018 Dr. Michael Steffens
//
// SPDX-License-Identifier:		BSL-1.0
//


#ifndef Polymorphic_Vector_INCLUDED
#define Polymorphic_Vector_INCLUDED

#include <vector>

namespace Polymorphic {

template<typename T, typename Allocator>
class Vector;

template<typename T, typename Allocator>
bool operator==(const Vector<T, Allocator>& lhs, const Vector<T, Allocator>& rhs);

template<typename T, typename Allocator>
bool operator!=(const Vector<T, Allocator>& lhs, const Vector<T, Allocator>& rhs);

template<typename T, typename Allocator>
bool operator<(const Vector<T, Allocator>& lhs, const Vector<T, Allocator>& rhs);

template<typename T, typename Allocator>
bool operator<=(const Vector<T, Allocator>& lhs, const Vector<T, Allocator>& rhs);

template<typename T, typename Allocator>
bool operator>(const Vector<T, Allocator>& lhs, const Vector<T, Allocator>& rhs);

template<typename T, typename Allocator>
bool operator>=(const Vector<T, Allocator>& lhs, const Vector<T, Allocator>& rhs);

template<typename T, typename Allocator>
void swap(const Vector<T, Allocator>& lhs, const Vector<T, Allocator>& rhs);

/// Polymorphic decorator composing std::vector<T> with the sole purpose of adding a virtual destructor..
///
/// Classes derived from Polymorphic::Vector<T> can be safely used as targets of smart pointers.
/// Note: forwarding member functions are *not* declared virtual! They are not meant to be overriden
/// in subclasses. Add new behavior using new virtual members instead.
template< typename T, typename Allocator = std::allocator<T> >
class Vector
{
public:
	typedef std::vector<T, Allocator> DelegateType;
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

	/// Forwarded to std::vector<T>::vector(const allocator_type& allocator = allocator_type()).
	explicit Vector(const allocator_type& allocator = allocator_type()) : delegate(allocator)
	{
	}

	/// Forwarded to std::vector<T>::vector(size_type n).
	explicit Vector(size_type n) : delegate(n)
	{
	}

	/// Forwarded to std::vector<T>::vector(size_type n, const value_type& value, const allocator_type& allocator = allocator_type()).
	Vector(size_type n, const value_type& value, const allocator_type& allocator = allocator_type()) : delegate(n, value, allocator)
	{
	}

	/// Forwarded to std::vector<T>::vector(InputIterator first, InputIterator last, const allocator_type& allocator = allocator_type()).
	template<typename InputIterator>
	Vector(InputIterator first, InputIterator last, const allocator_type& allocator = allocator_type()) : delegate(first, last, allocator)
	{
	}

	/// Copy constructor.
	Vector(const Vector& other) : delegate(other.delegate)
	{
	}

	/// Copy constructor.
	Vector(const Vector& other, const allocator_type& allocator) : delegate(other.delegate, allocator)
	{
	}

	/// Move constructor.
	Vector(Vector&& other) : delegate(std::move(other.delegate))
	{
	}

	/// Move constructor.
	Vector(Vector&& other, const allocator_type& allocator) : delegate(std::move(other.delegate), allocator)
	{
	}

	/// Forwarded to std::vector<T>::vector(std::initializer_list<value_type> initializerList, const allocator_type& allocator = allocator_type()).
	Vector(std::initializer_list<value_type> initializerList, const allocator_type& allocator = allocator_type()) : delegate(initializerList, allocator)
	{
	}

	/// Copy construct from std::vector<T>.
	Vector(const DelegateType& other) : delegate(other)
	{
	}

	/// Copy construct from std::vector<T> with allocator.
	Vector(const DelegateType& other, const allocator_type& allocator) : delegate(other, allocator)
	{
	}

	/// Move construct from std::vector<T>.
	Vector(DelegateType&& other) : delegate(std::move(other))
	{
	}

	/// Move construct from std::vector<T> with allocator.
	Vector(DelegateType&& other, const allocator_type& allocator) : delegate(std::move(other), allocator)
	{
	}

	/// Virtual destructor permitting derived classes to be deleted safely via a Vector pointer.
	virtual ~Vector()
	{
	}

	/// Copy assignment operator
	Vector& operator=(const Vector& other)
	{
		delegate = other.delegate;
		return *this;
	}

	/// Move assignment operator
	Vector& operator=(Vector&& other)
	{
		delegate = std::move(other.delegate);
		return *this;
	}

	/// Initializer list assignment operator
	Vector& operator=(std::initializer_list<value_type> initializerList)
	{
		delegate = initializerList;
		return *this;
	}

	/// Copy assignment from std::vector<T>.
	Vector& operator=(const DelegateType& other)
	{
		delegate = other;
		return *this;
	}

	/// Move assignment from std::vector<T>.
	Vector& operator=(DelegateType&& other)
	{
		delegate = std::move(other);
		return *this;
	}

	/// Implicit type conversion into std::vector<T> reference.
	operator DelegateType&()
	{
		return delegate;
	}

	/// Implicit type conversion into const std::vector<T> reference.
	operator const DelegateType&() const
	{
		return delegate;
	}

	/// Implicit type conversion into std::vector<T> rvalue reference.
	operator DelegateType&&()
	{
		return std::move(delegate);
	}

	/// Forwarded to std::vector<T>::begin() noexcept.
	iterator begin() noexcept
	{
		return delegate.begin();
	}

	/// Forwarded to std::vector<T>::begin() const noexcept.
	const_iterator begin() const noexcept
	{
		return delegate.begin();
	}

	/// Forwarded to std::vector<T>::end() noexcept.
	iterator end() noexcept
	{
		return delegate.end();
	}

	/// Forwarded to std::vector<T>::end() const noexcept.
	const_iterator end() const noexcept
	{
		return delegate.end();
	}

	/// Forwarded to std::vector<T>::rbegin() noexcept.
	reverse_iterator rbegin() noexcept
	{
		return delegate.rbegin();
	}

	/// Forwarded to std::vector<T>::rbegin() const noexcept.
	const_reverse_iterator rbegin() const noexcept
	{
		return delegate.rbegin();
	}

	/// Forwarded to std::vector<T>::rend() noexcept.
	reverse_iterator rend() noexcept
	{
		return delegate.rend();
	}

	/// Forwarded to std::vector<T>::rend() const noexcept.
	const_reverse_iterator rend() const noexcept
	{
		return delegate.rend();
	}

	/// Forwarded to std::vector<T>::cbegin() const noexcept.
	const_iterator cbegin() const noexcept
	{
		return delegate.cbegin();
	}

	/// Forwarded to std::vector<T>::cend() const noexcept.
	const_iterator cend() const noexcept
	{
		return delegate.cend();
	}

	/// Forwarded to std::vector<T>::crbegin() const noexcept.
	const_reverse_iterator crbegin() const noexcept
	{
		return delegate.crbegin();
	}

	/// Forwarded to std::vector<T>::crend() const noexcept.
	const_reverse_iterator crend() const noexcept
	{
		return delegate.crend();
	}

	/// Forwarded to std::vector<T>::empty() const noexcept.
	bool empty() const noexcept
	{
		return delegate.empty();
	}

	/// Forwarded to std::vector<T>::size() const noexcept.
	size_type size() const noexcept
	{
		return delegate.size();
	}

	/// Forwarded to std::vector<T>::max_size() const noexcept.
	size_type max_size() const noexcept
	{
		return delegate.max_size();
	}

	/// Forwarded to std::vector<T>::resize(size_type n).
	void resize(size_type n)
	{
		delegate.resize(n);
	}

	/// Forwarded to std::vector<T>::resize(size_type n, const value_type& value).
	void resize(size_type n, const value_type& value)
	{
		delegate.resize(n, value);
	}

	/// Forwarded to std::vector<T>::capacity() noexcept.
	size_type capacity() const noexcept
	{
		return delegate.capacity();
	}

	/// Forwarded to std::vector<T>::reserve(size_type n).
	void reserve(size_type n)
	{
		delegate.reserve(n);
	}

	/// Forwarded to std::vector<T>::shrink_to_fit().
	void shrink_to_fit()
	{
		delegate.shrink_to_fit();
	}

	/// Forwarded to std::vector<T>::operator[](size_type n).
	reference operator[](size_type n)
	{
		return delegate[n];
	}

	/// Forwarded to std::vector<T>::operator[](size_type n) const.
	const_reference operator[](size_type n) const
	{
		return delegate[n];
	}

	/// Forwarded to std::vector<T>::at(size_type n).
	reference at(size_type n)
	{
		return delegate.at(n);
	}

	/// Forwarded to std::vector<T>::at(size_type n) const.
	const_reference at(size_type n) const
	{
		return delegate.at(n);
	}

	/// Forwarded to std::vector<T>::front().
	reference front()
	{
		return delegate.front();
	}

	/// Forwarded to std::vector<T>::front(size_type n) const.
	const_reference front() const
	{
		return delegate.front();
	}

	/// Forwarded to std::vector<T>::back().
	reference back()
	{
		return delegate.back();
	}

	/// Forwarded to std::vector<T>::back(size_type n) const.
	const_reference back() const
	{
		return delegate.back();
	}

	/// Forwarded to std::vector<T>::data().
	value_type* data()
	{
		return delegate.data();
	}

	/// Forwarded to std::vector<T>::data(size_type n) const.
	const value_type* data() const
	{
		return delegate.data();
	}

	/// Forwarded to std::vector<T>::assign(InputIterator first, InputIterator last).
	template<typename InputIterator>
	void assign(InputIterator first, InputIterator last)
	{
		delegate.assign(first, last);
	}

	/// Forwarded to std::vector<T>::assign(size_type n, const value_type& value).
	void assign(size_type n, const value_type& value)
	{
		delegate.assign(n, value);
	}

	/// Forwarded to std::vector<T>::assign(std::initializer_list<value_type> initializerList).
	void assign(std::initializer_list<value_type> initializerList)
	{
		delegate.assign(initializerList);
	}

	/// Forwarded to std::vector<T>::push_back(const value_type& value).
	void push_back(const value_type& value)
	{
		delegate.push_back(value);
	}

	/// Forwarded to std::vector<T>::push_back(value_type&& value).
	void push_back(value_type&& value)
	{
		delegate.push_back(std::move(value));
	}

	/// Forwarded to std::vector<T>::pop_back().
	void pop_back()
	{
		delegate.pop_back();
	}

	/// Forwarded to std::vector<T>::insert(const_iterator position, const value_type& value).
	iterator insert(const_iterator position, const value_type& value)
	{
		return delegate.insert(position, value);
	}

	/// Forwarded to std::vector<T>::insert(const_iterator position, size_type n, const value_type& value).
	iterator insert(const_iterator position, size_type n, const value_type& value)
	{
		return delegate.insert(position, n, value);
	}

	/// Forwarded to std::vector<T>::insert(const_iterator position, InputIterator first, InputIterator last).
	template<typename InputIterator>
	iterator insert(const_iterator position, InputIterator first, InputIterator last)
	{
		return delegate.insert(position, first, last);
	}

	/// Forwarded to std::vector<T>::insert(const_iterator position, value_type&& value).
	iterator insert(const_iterator position, value_type&& value)
	{
		return delegate.insert(position, std::move(value));
	}

	/// Forwarded to std::vector<T>::insert(const_iterator position, std::initializer_list<value_type> initializerList).
	iterator insert(const_iterator position, std::initializer_list<value_type> initializerList)
	{
		return delegate.insert(position, initializerList);
	}

	/// Forwarded to std::vector<T>::erase(const_iterator position).
	iterator erase(const_iterator position)
	{
		return delegate.erase(position);
	}

	/// Forwarded to std::vector<T>::erase(const_iterator first, const_iterator last).
	iterator erase(const_iterator first, const_iterator last)
	{
		return delegate.erase(first, last);
	}

	/// Forwarded to std::vector<T>::swap(std::vector<bool>& other).
	void swap(Vector& other)
	{
		delegate.swap(other.delegate);
	}

	/// Forwarded to std::vector<T>::clear() noexcept.
	void clear() noexcept
	{
		delegate.clear();
	}

	/// Forwarded to std::vector<T>::emplace(const_iterator position, Args&&... args).
	template<typename... Args>
	iterator emplace(const_iterator position, Args&&... args)
	{
		return delegate.emplace(position, std::forward<Args>(args)...);
	}

	/// Forwarded to std::vector<T>::emplace_back(Args&&... args).
	template<class... Args>
	void emplace_back(Args&&... args)
	{
		return delegate.emplace_back(std::forward<Args>(args)...);
	}

	/// Forwarded to std::vector<T>::get_allocator() const noexcept.
	allocator_type get_allocator() const noexcept
	{
		return delegate.get_allocator();
	}

private:
	DelegateType delegate;

	friend bool operator== <T, Allocator> (const Vector& lhs, const Vector& rhs);
	friend bool operator!= <T, Allocator> (const Vector& lhs, const Vector& rhs);
	friend bool operator<  <T, Allocator> (const Vector& lhs, const Vector& rhs);
	friend bool operator<= <T, Allocator> (const Vector& lhs, const Vector& rhs);
	friend bool operator>  <T, Allocator> (const Vector& lhs, const Vector& rhs);
	friend bool operator>= <T, Allocator> (const Vector& lhs, const Vector& rhs);
	friend void Polymorphic::swap<T, Allocator>(const Vector<T, Allocator>& lhs, const Vector<T, Allocator>& rhs);
};

/// Polymorphic decorator composing std::vector<bool> with the sole purpose of adding a virtual destructor..
///
/// Classes derived from Polymorphic::Vector<bool> can be safely used as targets of smart pointers.
/// Note: forwarding member functions are *not* declared virtual! They are not meant to be overriden
/// in subclasses. Add new behavior using new virtual members instead.
///
/// For convenience this wrapper forwards member funtions emplace and emplace_back to insert and
/// push_back, respectively, as emplace and emplace_back are not required to be provided by C++11
/// std::vector<bool> implementations.
template<typename Allocator>
class Vector<bool, Allocator>
{
public:
	typedef std::vector<bool, Allocator> DelegateType;
	typedef bool value_type;
	typedef Allocator allocator_type;
	typedef typename DelegateType::reference reference;
	typedef typename DelegateType::const_reference const_reference;
	typedef typename DelegateType::pointer pointer;
	typedef typename DelegateType::const_pointer const_pointer ;
	typedef typename DelegateType::iterator iterator;
	typedef typename DelegateType::const_iterator const_iterator ;
	typedef typename DelegateType::reverse_iterator reverse_iterator;
	typedef typename DelegateType::const_reverse_iterator const_reverse_iterator;
	typedef typename DelegateType::difference_type difference_type;
	typedef typename DelegateType::size_type size_type;

	/// Forwarded to std::vector<bool>::vector(const allocator_type& allocator = allocator_type()).
	explicit Vector(const allocator_type& allocator = allocator_type()) : delegate(allocator)
	{
	}

	/// Forwarded to std::vector<bool>::vector(size_type n).
	explicit Vector(size_type n) : delegate(n)
	{
	}

	/// Forwarded to std::vector<bool>::vector(size_type n, const value_type& value, const allocator_type& allocator = allocator_type()).
	Vector(size_type n, const value_type& value, const allocator_type& allocator = allocator_type()) : delegate(n, value, allocator)
	{
	}

	/// Forwarded to std::vector<bool>::vector(InputIterator first, InputIterator last, const allocator_type& allocator = allocator_type()).
	template<typename InputIterator>
	Vector(InputIterator first, InputIterator last, const allocator_type& allocator = allocator_type()) : delegate(first, last, allocator)
	{
	}

	/// Copy constructor.
	Vector(const Vector& other) : delegate(other.delegate)
	{
	}

	/// Copy constructor.
	Vector(const Vector& other, const allocator_type& allocator) : delegate(other.delegate, allocator)
	{
	}

	/// Move constructor.
	Vector(Vector&& other) : delegate(std::move(other.delegate))
	{
	}

	/// Move constructor.
	Vector(Vector&& other, const allocator_type& allocator) : delegate(std::move(other.delegate), allocator)
	{
	}

	/// Forwarded to std::vector<bool>::vector(std::initializer_list<value_type> initializerList, const allocator_type& allocator = allocator_type()).
	Vector(std::initializer_list<value_type> initializerList, const allocator_type& allocator = allocator_type()) : delegate(initializerList, allocator)
	{
	}

	/// Copy construct from std::vector<bool>.
	Vector(const DelegateType& other) : delegate(other)
	{
	}

	/// Copy construct from std::vector<bool> with allocator.
	Vector(const DelegateType& other, const allocator_type& allocator) : delegate(other, allocator)
	{
	}

	/// Move construct from std::vector<bool>.
	Vector(DelegateType&& other) : delegate(std::move(other))
	{
	}

	/// Move construct from std::vector<bool> with allocator.
	Vector(DelegateType&& other, const allocator_type& allocator) : delegate(std::move(other), allocator)
	{
	}

	/// Virtual destructor
	virtual ~Vector()
	{
	}

	/// Copy assignment operator
	Vector& operator=(const Vector& other)
	{
		delegate = other.delegate;
		return *this;
	}

	/// Move assignment operator
	Vector& operator=(Vector&& other)
	{
		delegate = std::move(other.delegate);
		return *this;
	}

	/// Initializer list assignment operator
	Vector& operator=(std::initializer_list<value_type> initializerList)
	{
		delegate = initializerList;
		return *this;
	}

	/// Copy assignment from std::vector<bool>.
	Vector& operator=(const DelegateType& other)
	{
		delegate = other;
		return *this;
	}

	/// Move assignment from std::vector<bool>.
	Vector& operator=(DelegateType&& other)
	{
		delegate = std::move(other);
		return *this;
	}

	/// Implicit type conversion into std::vector<bool> reference.
	operator DelegateType&()
	{
		return delegate;
	}

	/// Implicit type conversion into const std::vector<bool> reference.
	operator const DelegateType&() const
	{
		return delegate;
	}

	/// Implicit type conversion into std::vector<bool> rvalue reference.
	operator DelegateType&&()
	{
		return std::move(delegate);
	}

	/// Forwarded to std::vector<bool>::begin() noexcept.
	iterator begin() noexcept
	{
		return delegate.begin();
	}

	/// Forwarded to std::vector<bool>::begin() const noexcept.
	const_iterator begin() const noexcept
	{
		return delegate.begin();
	}

	/// Forwarded to std::vector<bool>::end() noexcept.
	iterator end() noexcept
	{
		return delegate.end();
	}

	/// Forwarded to std::vector<bool>::end() const noexcept.
	const_iterator end() const noexcept
	{
		return delegate.end();
	}

	/// Forwarded to std::vector<bool>::rbegin() noexcept.
	reverse_iterator rbegin() noexcept
	{
		return delegate.rbegin();
	}

	/// Forwarded to std::vector<bool>::rbegin() const noexcept.
	const_reverse_iterator rbegin() const noexcept
	{
		return delegate.rbegin();
	}

	/// Forwarded to std::vector<bool>::rend() noexcept.
	reverse_iterator rend() noexcept
	{
		return delegate.rend();
	}

	/// Forwarded to std::vector<bool>::rend() const noexcept.
	const_reverse_iterator rend() const noexcept
	{
		return delegate.rend();
	}

	/// Forwarded to std::vector<bool>::cbegin() const noexcept.
	const_iterator cbegin() const noexcept
	{
		return delegate.cbegin();
	}

	/// Forwarded to std::vector<bool>::cend() const noexcept.
	const_iterator cend() const noexcept
	{
		return delegate.cend();
	}

	/// Forwarded to std::vector<bool>::crbegin() const noexcept.
	const_reverse_iterator crbegin() const noexcept
	{
		return delegate.crbegin();
	}

	/// Forwarded to std::vector<bool>::crend() const noexcept.
	const_reverse_iterator crend() const noexcept
	{
		return delegate.crend();
	}

	/// Forwarded to std::vector<bool>::empty() const noexcept.
	bool empty() const noexcept
	{
		return delegate.empty();
	}

	/// Forwarded to std::vector<bool>::size() const noexcept.
	size_type size() const noexcept
	{
		return delegate.size();
	}

	/// Forwarded to std::vector<bool>::max_size() const noexcept.
	size_type max_size() const noexcept
	{
		return delegate.max_size();
	}

	/// Forwarded to std::vector<bool>::resize(size_type n).
	void resize(size_type n)
	{
		delegate.resize(n);
	}

	/// Forwarded to std::vector<bool>::resize(size_type n, const value_type& value).
	void resize(size_type n, const value_type& value)
	{
		delegate.resize(n, value);
	}

	/// Forwarded to std::vector<bool>::capacity() const noexcept.
	size_type capacity() const noexcept
	{
		return delegate.capacity();
	}

	/// Forwarded to std::vector<bool>::reserve(size_type n).
	void reserve(size_type n)
	{
		delegate.reserve(n);
	}

	/// Forwarded to std::vector<bool>::shrink_to_fit().
	void shrink_to_fit()
	{
		delegate.shrink_to_fit();
	}

	/// Forwarded to std::vector<bool>::operator[](size_type n).
	reference operator[](size_type n)
	{
		return delegate[n];
	}

	/// Forwarded to std::vector<bool>::operator[](size_type n) const.
	const_reference operator[](size_type n) const
	{
		return delegate[n];
	}

	/// Forwarded to std::vector<bool>::at(size_type n).
	reference at(size_type n)
	{
		return delegate.at(n);
	}

	/// Forwarded to std::vector<bool>::at(size_type n) const.
	const_reference at(size_type n) const
	{
		return delegate.at(n);
	}

	/// Forwarded to std::vector<bool>::front().
	reference front()
	{
		return delegate.front();
	}

	/// Forwarded to std::vector<bool>::front(size_type n) const.
	const_reference front() const
	{
		return delegate.front();
	}

	/// Forwarded to std::vector<bool>::back().
	reference back()
	{
		return delegate.back();
	}

	/// Forwarded to std::vector<bool>::back(size_type n) const.
	const_reference back() const
	{
		return delegate.back();
	}

	/// Forwarded to std::vector<bool>::assign(InputIterator first, InputIterator last).
	template<typename InputIterator>
	void assign(InputIterator first, InputIterator last)
	{
		delegate.assign(first, last);
	}

	/// Forwarded to std::vector<bool>::assign(size_type n, const value_type& value).
	void assign(size_type n, const value_type& value)
	{
		delegate.assign(n, value);
	}

	/// Forwarded to std::vector<bool>::assign(std::initializer_list<value_type> initializerList).
	void assign(std::initializer_list<value_type> initializerList)
	{
		delegate.assign(initializerList);
	}

	/// Forwarded to std::vector<bool>::push_back(const value_type& value).
	void push_back(const value_type& value)
	{
		delegate.push_back(value);
	}

	/// Forwarded to std::vector<bool>::push_back(value_type&& value).
	void push_back(value_type&& value)
	{
		delegate.push_back(std::move(value));
	}

	/// Forwarded to std::vector<bool>::pop_back().
	void pop_back()
	{
		delegate.pop_back();
	}

	/// Forwarded to std::vector<bool>::insert(const_iterator position, const value_type& value).
	iterator insert(const_iterator position, const value_type& value)
	{
		return delegate.insert(position, value);
	}

	/// Forwarded to std::vector<bool>::insert(const_iterator position, size_type n, const value_type& value).
	iterator insert(const_iterator position, size_type n, const value_type& value)
	{
		return delegate.insert(position, n, value);
	}

	/// Forwarded to std::vector<bool>::insert(const_iterator position, InputIterator first, InputIterator last).
	template<typename InputIterator>
	iterator insert(const_iterator position, InputIterator first, InputIterator last)
	{
		return delegate.insert(position, first, last);
	}

	/// Forwarded to std::vector<bool>::insert(const_iterator position, value_type&& value).
	iterator insert(const_iterator position, value_type&& value)
	{
		return delegate.insert(position, std::move(value));
	}

	/// Forwarded to std::vector<bool>::insert(const_iterator position, std::initializer_list<value_type> initializerList).
	iterator insert(const_iterator position, std::initializer_list<value_type> initializerList)
	{
		return delegate.insert(position, initializerList);
	}

	/// Forwarded to std::vector<bool>::erase(const_iterator position).
	iterator erase(const_iterator position)
	{
		return delegate.erase(position);
	}

	/// Forwarded to std::vector<bool>::erase(const_iterator first, const_iterator last).
	iterator erase(const_iterator first, const_iterator last)
	{
		return delegate.erase(first, last);
	}

	/// Forwarded to std::vector<bool>::flip() noexcept.
	void flip() noexcept
	{
		delegate.flip();
	}

	/// Forwarded to std::vector<bool>::swap(std::vector<bool>& other).
	void swap(Vector& other)
	{
		delegate.swap(other.delegate);
	}

	/// Forwarded to std::vector<bool>::swap(reference lhs, reference rhs) noexcept.
	static void swap(reference lhs, reference rhs) noexcept
	{
		DelegateType::swap(lhs, rhs);
	}

	/// Forwarded to std::vector<bool>::clear() noexcept.
	void clear() noexcept
	{
		delegate.clear();
	}

	/// Forwarded to std::vector<bool>::insert(const_iterator position, const bool& arg).
	iterator emplace(const_iterator position, const bool& arg = bool())
	{
		return delegate.insert(position, arg);
	}

	/// Forwarded to std::vector<bool>::push_back(const bool& arg).
	void emplace_back(const bool& arg = bool())
	{
		return delegate.push_back(arg);
	}

	/// Forwarded to std::vector<bool>::get_allocator() const noexcept.
	allocator_type get_allocator() const noexcept
	{
		return delegate.get_allocator();
	}

private:
	DelegateType delegate;

	friend bool operator== <bool, Allocator> (const Vector& lhs, const Vector& rhs);
	friend bool operator!= <bool, Allocator> (const Vector& lhs, const Vector& rhs);
	friend bool operator<  <bool, Allocator> (const Vector& lhs, const Vector& rhs);
	friend bool operator<= <bool, Allocator> (const Vector& lhs, const Vector& rhs);
	friend bool operator>  <bool, Allocator> (const Vector& lhs, const Vector& rhs);
	friend bool operator>= <bool, Allocator> (const Vector& lhs, const Vector& rhs);
	friend void Polymorphic::swap<bool, Allocator>(const Vector<bool, Allocator>& lhs, const Vector<bool, Allocator>& rhs);
};

/// Forwarded to operator==(const std::vector<T, Allocator>& lhs, const std::vector<T, Allocator>& rhs).
template<typename T, typename Allocator>
bool operator==(const Vector<T, Allocator>& lhs, const Vector<T, Allocator>& rhs)
{
	return lhs.delegate == rhs.delegate;
}

/// Forwarded to operator!=(const std::vector<T, Allocator>& lhs, const std::vector<T, Allocator>& rhs).
template<typename T, typename Allocator>
bool operator!=(const Vector<T, Allocator>& lhs, const Vector<T, Allocator>& rhs)
{
	return lhs.delegate != rhs.delegate;
}

/// Forwarded to operator<(const std::vector<T, Allocator>& lhs, const std::vector<T, Allocator>& rhs).
template<typename T, typename Allocator>
bool operator<(const Vector<T, Allocator>& lhs, const Vector<T, Allocator>& rhs)
{
	return lhs.delegate < rhs.delegate;
}

/// Forwarded to operator<=(const std::vector<T, Allocator>& lhs, const std::vector<T, Allocator>& rhs).
template<typename T, typename Allocator>
bool operator<=(const Vector<T, Allocator>& lhs, const Vector<T, Allocator>& rhs)
{
	return lhs.delegate <= rhs.delegate;
}

/// Forwarded to operator>(const std::vector<T, Allocator>& lhs, const std::vector<T, Allocator>& rhs).
template<typename T, typename Allocator>
bool operator>(const Vector<T, Allocator>& lhs, const Vector<T, Allocator>& rhs)
{
	return lhs.delegate > rhs.delegate;
}

/// Forwarded to operator>=(const std::vector<T, Allocator>& lhs, const std::vector<T, Allocator>& rhs).
template<typename T, typename Allocator>
bool operator>=(const Vector<T, Allocator>& lhs, const Vector<T, Allocator>& rhs)
{
	return lhs.delegate >= rhs.delegate;
}

/// Forwarded to swap(const std::vector<T, Allocator>& lhs, const std::vector<T, Allocator>& rhs).
template<typename T, typename Allocator>
void swap(const Vector<T, Allocator>& lhs, const Vector<T, Allocator>& rhs)
{
	swap(lhs.delegate, rhs.delegate);
}

} // namespace Polymorphic

#endif // Polymorphic_Vector_INCLUDED
