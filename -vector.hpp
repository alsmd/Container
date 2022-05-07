#pragma once
#include <memory>
#include <iostream>
#include <iterator> // For std::forward_iterator_tag
#include <cstddef>  // For std::ptrdiff_t

namespace ft{

template<class T>
struct vectorIterator
{
	typedef typename iterator_category std::random_access_iterator_tag;
    typedef typename difference_type   std::ptrdiff_t;
    typedef typename value_type        T;
    typedef typename pointer           value_type*;  // or also value_type*
    typedef typename reference         value_type&;  // or also value_type&


	vectorIterator(pointer ptr) : _ptr(ptr) {}


	//Operators
	reference operator *(){
		return *_ptr;
	}

	pointer operator ->(){
		return _ptr;
	}

	//prefix increment
	vectorIterator &operator++(){
		_ptr++;
		return (*this);
	}

	//Postfix
	vectorIterator operator++(int) {
		vectorIterator tmp = *this;
		++(*this);
		return tmp;
	}

	friend bool operator== (const vectorIterator& a, const vectorIterator& b) {
		return a._ptr == b._ptr;
	};
    friend bool operator!= (const vectorIterator& a, const vectorIterator& b) {
		return a._ptr != b._ptr;
	};


	private:
		pointer _ptr;
};


template<class T, class Allocator = std::allocator<T>> class vector
{

protected:

	void realloc(int n)
	{

	}

	void checkCapacity(int n = 1)
	{
		if (this->size() + 1 > )
	}
public:

	//Member Types
	typedef T											value_type;
	typedef	Allocator									allocator_type;
	typedef vectorIterator								iterator;
	typedef const iterator								const_iterator;
	typedef typename allocator_type::size_type			size_type;
	typedef typename allocator_type::difference_type	difference_type;
	typedef typename allocator_type::reference			reference;
	typedef typename allocator_type::const_reference	const_reference;
	typedef typename allocator_type::pointer			pointer;
	typedef typename allocator_type::const_pointer		const_pointer;
	
	//Constructors
	//Doc https://en.cppreference.com/w/cpp/container/vector/vector

	//[1] until C++17
	vector(/* args */);

	// [2] until C++17
	explicit vector( const Allocator& alloc = allocator_type()) :
	_alloc(alloc),
	_start(u_nullptr),
	_current(u_nullptr),
	_capacity(u_nullptr)
	{}
	// [3] until C++11
	explicit vector( size_type count, const T& value = T(), const Allocator& alloc = Allocator()) :
		_alloc(alloc),
		_start(u_nullptr),
		_current(u_nullptr),
		_capacity(u_nullptr)
	{
		_start = _alloc.allocate(count)
		_capacity = _start + count;
		_current = _start;
		while (count--)
		{
			__alloc.construct(_current, value);
			_current++;
		}
	}

	template< class InputIt >
	vector( InputIt first, InputIt last, const Allocator& alloc = Allocator() ); // [5] until C++20

	// [6] until C++20
	vector(const vector& other) : 
	_alloc(other._alloc),
	_start(u_nullptr),
	_current(u_nullptr),
	_capacity(u_nullptr)
	{
		this->insert(this->begin(), other.begin(), other.end());
	}


	//Desconstructors
	~vector()
	{
		this->clear();
		_alloc.deallocate(_start, this->capacity());
	}

	//Iterators

	Iterator begin() {
		return Iterator(_start);
	}
    Iterator end()   {
		return Iterator(_capacity);
	}

	const_iterator begin() const{
		return Iterator(_start);
	}
    const_iterator end() const {
		return Iterator(_capacity);
	}




	//Member Functions

	/***
	 * 	@until	C++20
	 *  @doc	https://en.cppreference.com/w/cpp/container/vector/operator%3D
	***/
	vector& operator=( const vector& other ){}

	/***
	 * @until				C++20
	 * @doc					https://en.cppreference.com/w/cpp/container/vector/assign
	 * @brief				Replaces the contents of the container.
	 * 						1 - Replaces the contents with count copies of value value
	 * 						2 -  Replaces the contents with copies of those in the range [first, last). The behavior is undefined if either argument is an iterator into *this.
	 * @param count			the new size of the container
	 * @param value 		the value to initialize elements of the container with
	 * @param firstAndlast	the range to copy the elements from
	***/
	void assign( size_type count, const T& value ){}
	template< class InputIt >
	void assign( InputIt first, InputIt last){}

	/***
	 * @until				C++11
	 * @doc					https://en.cppreference.com/w/cpp/container/vector/get_allocator
	 * @brief				Returns the allocator associated with the container.
	 * @return				The associated allocator.
	***/
	allocator_type get_allocator() const;


	//Element access

	/***
	 * @until				C++20
	 * @doc					https://en.cppreference.com/w/cpp/container/vector/at
	 * @param pos	 		position of the element to return
	 * @brief				Returns a reference to the element at specified location pos, with bounds checking.
	 * 						If pos is not within the range of the container, an exception of type std::out_of_range is thrown.
	 * @exception			std::out_of_range if !(pos < size()).
	 * @return				Reference to the requested element.
	***/
	reference at( size_type pos );
	const_reference at( size_type pos ) const;

	/***
	 * @until				C++20
	 * @doc					https://en.cppreference.com/w/cpp/container/vector/operator_at
	 * @param pos	 		position of the element to return
	 * @brief				Returns a reference to the element at specified location pos. No bounds checking is performed.
	 * @note				Unlike std::map::operator[], this operator never inserts a new element into the container. Accessing a nonexistent element through this operator is undefined behavior.
	 * @return				Reference to the requested element.
	***/
	reference operator[]( size_type pos );
	const_reference operator[]( size_type pos ) const;



	/***
	 * @until				C++20
	 * @doc					https://en.cppreference.com/w/cpp/container/vector/front
	 * @brief				Returns a reference to the first element in the container.
	 * 						Calling front on an empty container is undefined.
	 * @note				For a container c, the expression c.front() is equivalent to *c.begin().
	 * @return				reference to the first element
	***/
	reference front();
	const_reference front() const;


	/***
	 * @until				C++20
	 * @doc					https://en.cppreference.com/w/cpp/container/vector/back
	 * @brief				Returns a reference to the last element in the container.
	 * 						Calling back on an empty container causes undefined behavior.
	 * @note				For a non-empty container c, the expression c.back() is equivalent to *std::prev(c.end())
	 * @return				Reference to the last element.
	***/
	reference back();
	const_reference back() const;


	/***
	 * @until				C++20
	 * @doc					https://en.cppreference.com/w/cpp/container/vector/data
	 * @brief				Returns pointer to the underlying array serving as element storage.
	 * 						The pointer is such that range [data(); data() + size()) is always a valid range, even if the container is empty (data() is not dereferenceable in that case).
	 * @note				If size() is 0, data() may or may not return a null pointer.
	 * @return				Pointer to the underlying element storage. For non-empty containers, the returned pointer compares equal to the address of the first element.
	***/
	T* data();
	const T* data() const;



	//Iterators


	/***
	 * @until				C++11
	 * @doc					https://en.cppreference.com/w/cpp/container/vector/begin
	 * @brief				Returns an iterator to the first element of the vector.
	 * 						If the vector is empty, the returned iterator will be equal to end().
	 * @return				Iterator to the first element.
	***/
	iterator begin();
	const_iterator begin() const;


	/***
	 * @until				C++11
	 * @doc					https://en.cppreference.com/w/cpp/container/vector/end
	 * @brief				Returns an iterator to the element following the last element of the vector.
	 * 						This element acts as a placeholder; attempting to access it results in undefined behavior.
	 * @return				Iterator to the element following the last element.
	***/
	iterator end();
	const_iterator end() const;


	/***
	 * @until				C++11
	 * @doc					https://en.cppreference.com/w/cpp/container/vector/rbegin
	 * @brief				Returns a reverse iterator to the first element of the reversed vector.
	 * 						It corresponds to the last element of the non-reversed vector. If the vector is empty, the returned iterator is equal to rend().
	 * @return				Reverse iterator to the first element.
	***/
	reverse_iterator rbegin();
	const_reverse_iterator rbegin() const;

	/***
	 * @until				C++11
	 * @doc					https://en.cppreference.com/w/cpp/container/vector/rend
	 * @brief				Returns a reverse iterator to the element following the last element of the reversed vector.
	 * 						It corresponds to the element preceding the first element of the non-reversed vector.
	 * 						This element acts as a placeholder, attempting to access it results in undefined behavior.
	 * @return				Reverse iterator to the element following the last element.
	***/
	reverse_iterator rend();
	const_reverse_iterator rend() const;



	//Capacity
	/***
	 * @until				C++11
	 * @doc					https://en.cppreference.com/w/cpp/container/vector/empty
	 * @brief				Checks if the container has no elements, i.e. whether begin() == end().
	 * @return				true if the container is empty, false otherwise
	***/
	bool empty() const;


	/***
	 * @until				C++11
	 * @doc					https://en.cppreference.com/w/cpp/container/vector/size
	 * @brief				Returns the number of elements in the container, i.e. std::distance(begin(), end()).
	 * @return				The number of elements in the container.
	***/
	size_type size() const;


	/***
	 * @until				C++11
	 * @doc					https://en.cppreference.com/w/cpp/container/vector/max_size
	 * @brief				Returns the maximum number of elements the container is able to hold due to system or library implementation limitations, i.e. std::distance(begin(), end()) for the largest container.
	 * @note 				This value typically reflects the theoretical limit on the size of the container, at most std::numeric_limits<difference_type>::max().
	 * 						At runtime, the size of the container may be limited to a value smaller than max_size() by the amount of RAM available.
	 * @return				Maximum number of elements.
	***/
	size_type max_size() const;


	/***
	 * @until				C++11
	 * @doc					https://en.cppreference.com/w/cpp/container/vector/max_size
	 * @brief				increase the capacity of the vector (the total number of elements that the vector can hold without requiring reallocation)
	 * 						to a value that's greater or equal to new_cap. If new_cap is greater than the current capacity(), new storage is allocated, otherwise the function does nothing.
	 * 						reserve() does not change the size of the vector.
	 * 						If new_cap is greater than capacity(), all iterators, including the past-the-end iterator, and all references to the elements are invalidated.
	 * 						Otherwise, no iterators or references are invalidated.
	 * @param new_cap		new capacity of the vector, in number of elements
	 * 
	 * @req					T must meet the requirements of MoveInsertable.
	 * @exception 			std::length_error if new_cap > max_size().
	 * 						any exception thrown by Allocator::allocate() (typically std::bad_alloc)
	***/
	void reserve( size_type new_cap );



	/***
	 * @until				C++11
	 * @doc					https://en.cppreference.com/w/cpp/container/vector/capacity
	 * @brief				Returns the number of elements that the container has currently allocated space for.
	 * @return				Capacity of the currently allocated storage.	
	***/
	size_type capacity() const;


	//Modifiers


	/***
	 * @until				C++11
	 * @doc					https://en.cppreference.com/w/cpp/container/vector/clear
	 * @brief				Erases all elements from the container. After this call, size() returns zero.
	 * 						Invalidates any references, pointers, or iterators referring to contained elements. Any past-the-end iterators are also invalidated.  
	 * 						Leaves the capacity() of the vector unchanged (note: the standard's restriction on the changes to capacity is in the specification of vector::reserve, see [1])
	***/
	void clear();

	/***
	 * @until				C++11
	 * @doc					https://en.cppreference.com/w/cpp/container/vector/insert
	 * @brief				Inserts elements at the specified location in the container.
	 * 						1) inserts value before pos
	 * 						2) inserts count copies of the value before pos
	 * 						3) inserts elements from range [first, last) before pos.
	 * 						This overload has the same effect as overload (3) if InputIt is an integral type.
	 * 						Causes reallocation if the new size() is greater than the old capacity(). If the new size() is greater than capacity(), all iterators and references are invalidated.
	 * 						Otherwise, only the iterators and references before the insertion point remain valid. The past-the-end iterator is also invalidated.
	 * @param pos			iterator before which the content will be inserted. pos may be the end() iterator
	 * @param value			element value to insert
	 * @param count			number of elements to insert
	 * @param firstAndlast	the range of elements to insert, can't be iterators into container for which insert is called
	 * @exception			If an exception is thrown when inserting a single element at the end,
	 * 						and T is CopyInsertable or std::is_nothrow_move_constructible<T>::value is true, there are no effects (strong exception guarantee).
	 * @return				Return value
	 * 						1) Iterator pointing to the inserted value
	 * 						2) Iterator pointing to the first element inserted, or pos if count==0.
	 * 						3) Iterator pointing to the first element inserted, or pos if first==last.
	***/
	iterator insert( iterator pos, const T& value ){
		if (&(*pos) > _capacity)
		{
			int new_size = this->size() * 2;
		}
		else
		{
		}
	}
	void insert( iterator pos, size_type count, const T& value );
	template< class InputIt >
	void insert( iterator pos, InputIt first, InputIt last );


	/***
	 * @until				C++11
	 * @doc					https://en.cppreference.com/w/cpp/container/vector/erase
	 * @brief				Erases the specified elements from the container.
	 * 						1) Removes the element at pos.
	 * 						2) Removes the elements in the range [first, last).
	 * 						Invalidates iterators and references at or after the point of the erase, including the end() iterator.
	 * 						The iterator pos must be valid and dereferenceable. Thus the end() iterator (which is valid, but is not dereferenceable) cannot be used as a value for pos.
	 * 						The iterator first does not need to be dereferenceable if first==last: erasing an empty range is a no-op.
	 * @param pos			iterator to the element to remove
	 * @param firstAndlast	range of elements to remove
	 * @exception			Does not throw unless an exception is thrown by the assignment operator of T.
	 * @return				Iterator following the last removed element.
	 * 						If pos refers to the last element, then the end() iterator is returned.
	 * 						If last==end() prior to removal, then the updated end() iterator is returned.
	 * 						If [first, last) is an empty range, then last is returned.
	***/
	iterator erase( iterator pos );
	iterator erase( iterator first, iterator last );


	/***
	 * @until				C++11
	 * @doc					https://en.cppreference.com/w/cpp/container/vector/push_back
	 * @brief				Appends the given element value to the end of the container.
	 * 						1) The new element is initialized as a copy of value.
	 * 						If the new size() is greater than capacity() then all iterators and references (including the past-the-end iterator) are invalidated.
	 * 						Otherwise only the past-the-end iterator is invalidated.
	 * @param value			the value of the element to append
	 * @exception			If an exception is thrown (which can be due to Allocator::allocate() or element copy/move constructor/assignment), this function has no effect (strong exception guarantee).
	***/
	void push_back( const T& value );


	/***
	 * @until				C++20
	 * @doc					https://en.cppreference.com/w/cpp/container/vector/pop_back
	 * @brief				Removes the last element of the container.
	 * 						Calling pop_back on an empty container results in undefined behavior.
	 * 						Iterators and references to the last element, as well as the end() iterator, are invalidated.
	***/
	void pop_back();



	/***
	 * @until				C++11
	 * @doc					https://en.cppreference.com/w/cpp/container/vector/resize
	 * @brief				Appends the given element value to the end of the container.
	 * 						Resizes the container to contain count elements.
	 * 						If the current size is greater than count, the container is reduced to its first count elements.
	 * 						If the current size is less than count,
	 * 						additional copies of value are appended.
	 * @param count			new size of the container
	 * @param value			the value to initialize the new elements with
	 * @exception			If an exception is thrown, this function has no effect (strong exception guarantee).
	***/

	void resize( size_type count, T value = T() )
	{
		pointer tmp = _alloc.allocate(count);
		if (count < this->size){
			while (this->size())

		}
		else{

		}
		while (count-- && )
		{
			_alloc.construct(tmp, );
		}
	}

	/***
	 * @until				C++17
	 * @doc					https://en.cppreference.com/w/cpp/container/vector/swap
	 * @brief				Exchanges the contents of the container with those of other. Does not invoke any move, copy, or swap operations on individual elements.
	 * 						All iterators and references remain valid. The past-the-end iterator is invalidated.
	 * @param other			container to exchange the contents with
	***/
	void swap( vector& other );




	private:
		allocator_type  _alloc;
		pointer         _start;
		pointer         _current;
		pointer         _capacity;
};

}
