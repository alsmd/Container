#pragma once
#include <memory>
#include <iostream>
#include <cstddef>
#include <exception>
#include <sstream>
#include <cmath>
#include "../Iterator/random_access_iterator.hpp"
#include "../Iterator/reverse_iterator.hpp"
#include "../Util/type_traits.hpp"

namespace ft{

template<typename T, class Allocator = std::allocator<T> >
class vector
{
public:


	//Member Types
	typedef T											value_type;
	typedef	Allocator									allocator_type;
	typedef	ft::random_access_iterator<value_type>		iterator;
	typedef const iterator								const_iterator;
	typedef	ft::reverse_iterator<iterator>				reverse_iterator;
	typedef	const ft::reverse_iterator<const_iterator>	const_reverse_iterator;
	typedef typename allocator_type::size_type			size_type;
	typedef typename allocator_type::difference_type	difference_type;
	typedef typename allocator_type::reference			reference;
	typedef typename allocator_type::const_reference	const_reference;
	typedef typename allocator_type::pointer			pointer;
	typedef typename allocator_type::const_pointer		const_pointer;

	/***
	 * 
	 * @name	empty container constructor (default constructor)
	 * @brief	Constructs an empty container, with no elements.
	 * @link	https://www.cplusplus.com/reference/vector/vector/vector/
	 *  
	*/
	explicit vector( const Allocator& alloc = allocator_type())
	{
		this->_alloc = alloc;
		this->_finalBlock = NULL;
		this->_index = NULL;
		this->_data = NULL;
	}

	/***
	 * 
	 * @name	fill constructor
	 * @brief	Constructs a container with n elements. Each element is a copy of val.
	 * @link	https://www.cplusplus.com/reference/vector/vector/vector/
	 *  
	*/
	explicit vector( size_type n, const T& value = T(), const Allocator& alloc = Allocator())
	{
		this->_alloc = alloc;
		this->_data = this->_alloc.allocate(n);
		this->_finalBlock = this->_data + n;
		this->_index = this->_data;
		while (n--)
		{
			this->_alloc.construct(this->_index, value);
			this->_index++;
		}
	}

	/***
	 * 
	 * @name	range constructor
	 * @brief	Constructs a container with as many elements as the range [first,last),
	 * 			with each element constructed from its corresponding element in that range, in the same order.
	 * @link	https://www.cplusplus.com/reference/vector/vector/vector/
	 * 
	*/
	template <class InputIterator>
	vector (InputIterator first, typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type last, const allocator_type& alloc = allocator_type()){
		this->_alloc = alloc;
		this->_finalBlock = NULL;
		this->_index = NULL;
		this->_data = NULL;
		this->insert(this->begin(), first, last);
	}


	/***
	 * 
	 * @name	copy constructor
	 * @brief	Constructs a container with a copy of each of the elements in x, in the same order.
	 * @link	https://www.cplusplus.com/reference/vector/vector/vector/
	 * 
	*/
	vector (const vector& x) : _alloc(x.get_allocator()){
		this->_data = this->_alloc.allocate(x.capacity());
		this->_finalBlock = this->_data + x.capacity();
		this->_index = _data;
		for (iterator i = x.begin(); i != x.end(); i++){
			this->_alloc.construct(this->_index, *i);
			this->_index++;
		}
	}


	/***
	 * 
	 * @name	Vector destructor
	 * @brief	This destroys all container elements, and deallocates all the storage capacity allocated by the vector using its allocator.
	 * @link	https://www.cplusplus.com/reference/vector/vector/~vector/
	 * 
	*/
	~vector()
	{
		this->clear();
		if (this->_data)
			this->_alloc.deallocate(this->_data, this->capacity());
	}


	/***
	 * 
	 * @name	Assign Operator
	 * @brief	Copies all the elements from x into the container.
	 * 			The container preserves its current allocator, which is used to allocate storage in case of reallocation.
	 * @link	https://www.cplusplus.com/reference/vector/vector/operator=/
	 * 
	*/
	vector& operator= (const vector& x){
		this->clear();
		this->insert(this->begin(), x.begin(), x.end());
		return (*this);
	}





	/***
	 * 
	 * @brief	Returns an iterator pointing to the first element in the vector.
	 * 			Notice that, unlike member vector::front, which returns a reference to the first element,
	 * 			this function returns a random access iterator pointing to it.
	 * 			If the container is empty, the returned iterator value shall not be dereferenced.

	 * @return	An iterator to the beginning of the sequence container.
	 * @link	https://www.cplusplus.com/reference/vector/vector/begin/
	 * 
	*/
	iterator begin() {
		return iterator(_data);
	}

	/***
	 * 
	 * @brief	Returns an iterator referring to the past-the-end element in the vector container.
	 * 			The past-the-end element is the theoretical element that would follow the last element in the vector.
	 * 			It does not point to any element, and thus shall not be dereferenced.
	 * 			Because the ranges used by functions of the standard library do not include the element pointed by their closing iterator,
	 * 			this function is often used in combination with vector::begin to specify a range including all the elements in the container.
	 * 			If the container is empty, this function returns the same as vector::begin

	 * @return	An iterator to the element past the end of the sequence.
	 * @link	https://www.cplusplus.com/reference/vector/vector/end/
	 * 
	*/
    iterator end()   {
		return iterator(_index);
	}

	/***
	 *
	 * @brief	Returns an iterator pointing to the first element in the vector.
	 * @return	If the vector object is const-qualified, the function returns a const_iterator. Otherwise, it returns an iterator.
	 * 
	*/
	const_iterator begin() const{
		return iterator(_data);
	}
  
	/***
	 *
	 * @brief	Returns an iterator referring to the past-the-end element in the vector container.
	 * @return	If the vector object is const-qualified, the function returns a const_iterator. Otherwise, it returns an iterator.
	 * 
	*/
	const_iterator end() const {
		return iterator(_index);
	}


	/***
	 * 
	 * @brief	Returns a reverse iterator pointing to the last element in the vector (i.e., its reverse beginning).
	 * 			Reverse iterators iterate backwards: increasing them moves them towards the beginning of the container.
	 * 			rbegin points to the element right before the one that would be pointed to by member end.
	 * 			Notice that unlike member vector::back, which returns a reference to this same element,
	 * 			this function returns a reverse random access iterator.
	 * @return	A reverse iterator to the reverse beginning of the sequence container.
	 * @link	https://www.cplusplus.com/reference/vector/vector/rbegin/
	 * 
	*/
	reverse_iterator rbegin() {
		return reverse_iterator(this->_index);
	}

	/***
	 * 
	 * @brief	Returns a reverse iterator pointing to the theoretical element preceding the first element in
	 * 			the vector (which is considered its reverse end).
	 * @return	A reverse iterator to the reverse end of the sequence container.
	 * @link	https://www.cplusplus.com/reference/vector/vector/rend/
	 * 
	*/
    reverse_iterator rend()   {
		return reverse_iterator(this->_data);
	}

	/***
	 * 
	 * @brief	Returns a reverse iterator pointing to the last element in the vector (i.e., its reverse beginning).
	 * @return	If the vector object is const-qualified, the function returns a const_reverse_iterator. Otherwise, it returns a reverse_iterator.
	 * @link	https://www.cplusplus.com/reference/vector/vector/rbegin/
	 * 
	*/
	const_reverse_iterator rbegin() const{
		return const_reverse_iterator(this->_index);
	}

	/***
	 * 
	 * @brief	Returns a reverse iterator pointing to the theoretical element preceding the first element in
	 * 			the vector (which is considered its reverse end).
	 * @return	If the vector object is const-qualified, the function returns a const_reverse_iterator.
	 * @link	https://www.cplusplus.com/reference/vector/vector/rend/
	 * 
	*/
    const_reverse_iterator rend() const{
		return const_reverse_iterator(this->_data);
	}

	
	/***
	 * 
	 * @brief	Returns the number of elements in the vector.
	 * 			This is the number of actual objects held in the vector, which is not necessarily equal to its storage capacity.
	 * @return	The number of elements in the container.
	 * @link	https://www.cplusplus.com/reference/vector/vector/size/
	 * 
	*/
	size_type	size() const
	{
		return this->_index - this->_data;
	}

	/***
	 * 
	 * @brief	Returns the maximum number of elements that the vector can hold.
	 * 			This is the maximum potential size the container can reach due to known system or
	 *			library implementation limitations, but the container is by no means guaranteed to be able to
	 			reach that size: it can still fail to allocate storage at any point before that size is reached
	 * @return	The maximum number of elements a vector container can hold as content.
	 * @link	https://www.cplusplus.com/reference/vector/vector/max_size/
	 * 
	*/
	size_type max_size() const
	{
		return (this->_alloc.max_size());
	}

	/***
	 * 
	 * @brief	Resizes the container so that it contains n elements.
	 * 			If n is smaller than the current container size, the content is reduced to its first n elements,
	 * 			removing those beyond (and destroying them).
	 * 			ntent is exIf n is greater than the current container size, the copanded by inserting at the end as many
	 * 			elements as needed to reach a size of n. If val is specified, the new elements are initialized as copies of val, otherwise,
	 * 			they are value-initialized.
	 * 			If n is also greater than the current container capacity, an automatic reallocation of the allocated storage space takes place.
	 * 			Notice that this function changes the actual content of the container by inserting or erasing elements from it.
	 * @return	The maximum number of elements a vector container can hold as content.
	 * @link	https://www.cplusplus.com/reference/vector/vector/max_size/
	 * 
	*/
	void resize(size_type count, T value = T()){
		if (count < this->size()){
			size_type	old_size = this->size();
			for (size_type i = count; i < old_size; i++)
			{
				this->_alloc.destroy(this->_data + i);
				this->_index--;
			}
		}else if (count > this->size()){
			if (count > this->capacity())
				this->reserve(count);
			for (size_type index = this->size(); index < count; index++){
				this->_alloc.construct(this->_index, value);
				this->_index++;
			}
		}
	}



	/***
	 * 
	 * @brief	Returns the size of the storage space currently allocated for the vector, expressed in terms of elements.
	 * @return	The size of the currently allocated storage capacity in the vector, measured in terms of the number elements it can hold.
	 * @link	https://www.cplusplus.com/reference/vector/vector/capacity/
	 * 
	*/
	size_type capacity() const{
		return this->_finalBlock - this->_data;
	}


	/***
	 * 
	 * @brief	Returns whether the vector is empty (i.e. whether its size is 0).
	 * @return	true if the container size is 0, false otherwise.
	 * @link	https://www.cplusplus.com/reference/vector/vector/empty/
	 * 
	*/
	bool	empty() const
	{
		return (this->begin() == this->end() ? true : false);
	}


	/***
	 * 
	 * @brief	Requests that the vector capacity be at least enough to contain n elements.
	 * @param n Minimum capacity for the vector.
	 * @link 	https://www.cplusplus.com/reference/vector/vector/reserve/
	 * 
	**/
	void reserve(size_type n)
	{
		/* if (n > this->max_size())
			throw length_error */
		if (n > this->capacity())
		{
			size_type	new_size = (this->size() * 2) >= n ? (this->size() * 2) : n;
			pointer		new_data = _alloc.allocate(new_size);
			pointer		new_finalBlock = new_data + n;
			pointer		new_index = new_data;
			size_type	size = this->size();
			for (iterator i = this->begin(); i != this->end(); i++)
			{
				this->_alloc.construct(new_index, *i);
				new_index++;
			}
			this->clear();
			if (this->_data)
				this->_alloc.deallocate(this->_data, this->capacity());
			this->_data = new_data;
			this->_finalBlock = new_finalBlock;
			this->_index = new_index;
		}
	}


	/***
	 * 
	 * @brief		Returns a reference to the element at position n in the vector container.
	 * @param pos	Position of an element in the container.
	 * @return		The element at the specified position in the vector.
	 * @link 		https://www.cplusplus.com/reference/vector/vector/reserve/
	 * 
	**/
	reference operator[]( size_type pos )
	{
		iterator iter = this->begin(); 
		for (size_type i = 0; i < pos; i++)
			iter++;
		return (*iter);
	}

	/***
	 * 
	 * @brief		Returns a reference to the element at position n in the vector container.
	 * @param pos	Position of an element in the container.
	 * @return		The element at the specified position in the vector.
	 * @link 		https://www.cplusplus.com/reference/vector/vector/reserve/
	 * 
	**/
	const_reference operator[]( size_type pos ) const
	{
		iterator iter = this->begin(); 
		for (size_type i = 0; i < pos; i++)
			iter++;
		return (*iter);
	}

	/***
	 * 
	 * @brief		Returns a reference to the element at position n in the vector.
	 * @param n		Position of an element in the container.
	 * @return		The element at the specified position in the container.
	 * @link 		https://www.cplusplus.com/reference/vector/vector/at/
	 * 
	**/
	reference at( size_type pos )
	{
		std::ostringstream	o;
		o << "vector::_M_range_check: __n (which is " << pos << ") >= this->size() (which is " << this->size() << ")";
		if (pos >= this->size()) 
			throw std::out_of_range(o.str());
		return (*this)[pos];
	}

	/***
	 * 
	 * @brief		Returns a reference to the element at position n in the vector.
	 * @param n		Position of an element in the container.
	 * @return		The element at the specified position in the container.
	 * @link 		https://www.cplusplus.com/reference/vector/vector/at/
	 * 
	**/
	const_reference at( size_type pos ) const 
	{
		std::ostringstream	o;
		o << "vector::_M_range_check: __n (which is " << pos << ") >= this->size() (which is " << this->size() << ")";
		if (pos >= this->size()) 
			throw std::out_of_range(o.str());
		return (*this)[pos];
	}

	/***
	 * 
	 * @brief		Returns a reference to the first element in the vector.
	 * @return		A reference to the first element in the vector container.
	 * @link 		https://www.cplusplus.com/reference/vector/vector/front/
	 * 
	**/
	reference front()
	{
		return *(this->begin());
	}
	/***
	 * 
	 * @brief		Returns a reference to the first element in the vector.
	 * @return		A reference to the first element in the vector container.
	 * @link 		https://www.cplusplus.com/reference/vector/vector/front/
	 * 
	**/
	const_reference front() const
	{
		return *(this->begin());
	}

	/***
	 * 
	 * @brief		Returns a reference to the last element in the vector.
	 * @return		A reference to the last element in the vector.
	 * @link 		https://www.cplusplus.com/reference/vector/vector/back/
	 * 
	**/
	reference back()
	{
		iterator i = this->end();
		i--;
		return *(i);
	}

	/***
	 * 
	 * @brief		Returns pointer to the underlying array serving as element storage. The pointer is such that range [data(); data() + size()) is always a valid range, even if the container is empty (data() is not dereferenceable in that case).
	 * @return		Pointer to the underlying element storage. For non-empty containers, the returned pointer compares equal to the address of the first element.
	 * @link 		https://en.cppreference.com/w/cpp/container/vector/data
	 * 
	**/
	T* data(){
		return this->_data;
	}

	const T* data() const{
		return this->_data;
	}
	/***
	 * 
	 * @brief		Returns a reference to the last element in the vector.
	 * @return		A reference to the last element in the vector.
	 * @link 		https://www.cplusplus.com/reference/vector/vector/back/
	 * 
	**/
	const_reference back() const
	{
		iterator i = this->end();
		i--;
		return *(i);
	}


	/***
	 * 
	 * @brief		the new contents are n elements, each initialized to a copy of val.
	 * @param value	Value to fill the container with. Each of the n elements in the container will be initialized to a copy of this value.
	 * @param count	New size for the container.
	 * @link 		https://www.cplusplus.com/reference/vector/vector/assign/
	 * 
	**/
	void assign( size_type count, const T& value )
	{
		this->clear();
		this->insert(this->begin(), count, value);
	}

	/***
	 * 
	 * @brief		the new contents are elements constructed from each of the elements in the range between first and last, in the same order.
	 * @param first Input iterators to the initial and final positions in a sequence. The range used is [first,last), which includes all the elements between first and last,
	 * 				including the element pointed by first but not the element pointed by last.
	 * @param last	
	 * @link 		https://www.cplusplus.com/reference/vector/vector/assign/
	 * 
	**/
	template< class InputIt >
	void assign( InputIt first, typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type
 last )
	{
		this->clear();
		this->insert(this->begin(), first, last);
	}

	/***
	 * 
	 * @brief		Adds a new element at the end of the vector, after its current last element.
	 * 				The content of val is copied (or moved) to the new element.
	 * 				This effectively increases the container size by one, which causes an automatic reallocation
	 * 				of the allocated storage space if -and only if- the new vector size surpasses the current vector capacity.
	 * @param val	Value to be copied (or moved) to the new element.
	 * @link 		https://www.cplusplus.com/reference/vector/vector/push_back/
	 * 
	**/
	void push_back (const value_type& val)
	{
		this->reserve(this->size() + 1);
		this->_alloc.construct(this->_index, val);
		this->_index++;
	}

	/***
	 * 
	 * @brief		Removes the last element in the vector, effectively reducing the container size by one.
	 * @link 		https://www.cplusplus.com/reference/vector/vector/pop_back/
	 * 
	**/
	void pop_back()
	{
		if (this->size() > 0)
		{
			this->_index--;
			this->_alloc.destroy(this->_index);
		}
	}



	/***
	 * 
	 * @brief		The vector is extended by inserting new elements before the element at the specified position,
	 * 				effectively increasing the container size by the number of elements inserted.
	 * @param pos	Position in the vector where the new elements are inserted.
	 * @param value	Value to be copied (or moved) to the inserted elements.
					Member type value_type is the type of the elements in the container,
					defined in deque as an alias of its first template parameter (T).
	 * @link 		https://www.cplusplus.com/reference/vector/vector/insert/
	 * 
	**/
	iterator insert( iterator pos, const T& value ){
		size_type	position = &(*pos) - this->_data; // index of pos inside array container
		this->reserve(this->size() + 1);
		for (size_type s = this->size(); s > position; s--)
			this->_alloc.construct(this->_data + s, *(this->_data + s - 1));
		this->_alloc.construct(this->_data + position, value);
		this->_index++;
		return (this->_data + position);
	}

	/***
	 * 
	 * @brief		The vector is extended by inserting new elements before the element at the specified position,
	 * 				effectively increasing the container size by the number of elements inserted.
	 * @param count	Number of elements to insert. Each element is initialized to a copy of val.
	 * @param pos	Position in the vector where the new elements are inserted.
	 * @param value	Value to be copied (or moved) to the inserted elements.
					Member type value_type is the type of the elements in the container,
					defined in deque as an alias of its first template parameter (T).
	 * @link 		https://www.cplusplus.com/reference/vector/vector/insert/
	 * 
	**/
	void insert( iterator pos, size_type count, const T& value )
	{
		size_type	position = &(*pos) - this->_data; // index of pos inside array container

		this->reserve(this->size() + count);
		for (size_type i = 0; i < count; i++)
		{
			for (size_type s = this->size(); s > position; s--)
				this->_alloc.construct(this->_data + s, *(this->_data + s - 1));
			this->_index++;
			this->_alloc.construct(this->_data + position, value);
		}
	}


	/***
	 * 
	 * @brief		The vector is extended by inserting new elements before the element at the specified position,
	 * 				effectively increasing the container size by the number of elements inserted.
	 * @param pos	Position in the vector where the new elements are inserted.
	 * @param first	Iterators specifying a range of elements. Copies of the elements in the range [first,last)
	 * 				are inserted at position (in the same order).
	 * 				Notice that the range includes all the elements between first and last,
	 * 				including the element pointed by first but not the one pointed by last.
	 * @param last	
	 * @link 		https://www.cplusplus.com/reference/vector/vector/insert/
	 * 
	**/
	template< class InputIt>
	void insert( iterator pos, InputIt first,typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type last )
	{
		size_type numberOfNewElements = std::abs(&(*last) - &(*first));
		size_type	insertPosition = &(*pos) - this->_data; // index of pos inside array container
		this->reserve(this->size() + numberOfNewElements);
		for (size_type i = 0; i < numberOfNewElements; i++)
		{
			for (size_type s = this->size(); s > insertPosition + i; s--)
				this->_alloc.construct(this->_data + s, *(this->_data + s - 1));
			this->_index++;
			this->_alloc.construct(this->_data + insertPosition + i, *first);
			first++;
		}
	}


	/***
	 * 
	 * @brief		Removes from the vector either a single element (position) or a range of elements ([first,last)).
	 * @param pos	Iterator pointing to a single element to be removed from the vector.
	 * 				Member types iterator and const_iterator are random access iterator types that point to elements
	 * @return		An iterator pointing to the new location of the element that followed the last element erased by the function call.
	 * 				This is the container end if the operation erased the last element in the sequence.
	 * @link 		https://www.cplusplus.com/reference/vector/vector/erase/
	 * 
	**/
	iterator erase( iterator pos )
	{
		iterator next = pos + 1;
		size_type index = &(*pos) - this->_data;
		this->_alloc.destroy(this->_data + index);
		for (; index < this->size() - 1; index++)
		{
			this->_alloc.construct(this->_data + index, *(this->_data + index + 1));
		}
		this->_index--;
		return (next);
	}

	/***
	 * 
	 * @brief		Removes from the vector either a single element (position) or a range of elements ([first,last)).
	 * @param first	Iterators specifying a range within the vector] to be removed: [first,last). i.e., the range includes
	 * 				all the elements between first and last, including the element pointed by first but not the one pointed by last.
	 * @return		An iterator pointing to the new location of the element that followed the last element erased by the function call.
	 * 				This is the container end if the operation erased the last element in the sequence.
	 * @link 		https://www.cplusplus.com/reference/vector/vector/erase/
	 * 
	**/
	iterator erase( iterator first, iterator last )
	{
		size_type index = &(*first) - this->_data;
		size_type end = &(*last) - this->_data + 1;
		while (end < this->size() - 1)
		{
			this->_alloc.construct(this->_data + index, *(this->_data + end));
			index++;
			end++;
		}
		for (; first != last; first++)
		{
			this->_alloc.destroy(&(*first));
			this->_index--;
		}
		this->_alloc.destroy(&(*first));
		return (iterator(this->_index - 1));
	}


	/***
	 * 
	 * @brief		Exchanges the content of the container by the content of x, which is another vector object of the same type. Sizes may differ.
	 * 				After the call to this member function, the elements in this container are those which were in x before the call,
	 * 				and the elements of x are
	 * 				those which were in this. All iterators, references and pointers remain valid for the swapped objects.
	 * @param x		Another vector container of the same type (i.e., instantiated with the same template parameters, T and Alloc)
	 * 				whose content is swapped with that of this container.
	 * @link 		https://www.cplusplus.com/reference/vector/vector/swap/
	 * 
	**/
	void swap (vector& x){
		allocator_type	tmp_alloc = x._alloc;
		pointer			tmp_data = x._data;
		pointer			tmp_finalBlock = x._finalBlock;
		pointer			tmp_index = x._index;

		x._alloc = this->_alloc;
		x._data = this->_data;
		x._finalBlock = this->_finalBlock;
		x._index = this->_index;

		this->_alloc = tmp_alloc;
		this->_data = tmp_data;
		this->_finalBlock = tmp_finalBlock;
		this->_index = tmp_index;
	}


	/***
	 * 
	 * @brief		Removes all elements from the vector (which are destroyed), leaving the container with a size of 0.
	 * @link 		https://www.cplusplus.com/reference/vector/vector/clear/
	 * 
	**/
	void clear()
	{
		for (size_type i = 0; i < this->size(); i++)
			_alloc.destroy(_data + i);
		this->_index = this->_data;
	}

	
	/***
	 * 
	 * @brief		Returns a copy of the allocator object associated with the vector.
	 * @return		The allocator.
	 * @link 		https://www.cplusplus.com/reference/vector/vector/get_allocator/
	 * 
	**/
	allocator_type get_allocator() const
	{
		return this->_alloc;
	}


	/* T* data()
	{
		return (this->_data);
	}

	const T* data() const
	{
		return (this->_data);
	} */

private:
	/* data */
	allocator_type	_alloc;//gerenciador de memoria
	pointer			_data;//começo
	pointer			_finalBlock;//final de todo bloco
	pointer			_index;//depois ultimo elemento

	
	
protected:


};

template <class T, class Alloc>
bool operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs){
	if (lhs.size() != rhs.size())
		return false;
	for (int index = 0; index < lhs.size(); index++){
		if (lhs[index] != rhs[index])
			return false;
	}
	return true;
}

template <class T, class Alloc>
bool operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs){
	return (!(lhs == rhs));
}

template <class T, class Alloc>
bool operator<  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs){
	for (int index = 0; index < lhs.size() && index < rhs.size(); index++){
		if (lhs[index] > rhs[index])
			return false;
	}
	if (lhs.size() >= rhs.size())
		return false;
	return true;
}

template <class T, class Alloc>
bool operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs){
	for (int index = 0; index < lhs.size() && index < rhs.size(); index++){
		if (lhs[index] > rhs[index])
			return false;
	}
	if (lhs.size() > rhs.size())
		return false;
	return true;
}

template <class T, class Alloc>
bool operator>  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs){
	for (int index = 0; index < lhs.size() && index < rhs.size(); index++){
		if (lhs[index] < rhs[index])
			return false;
	}
	if (lhs.size() <= rhs.size())
		return false;
	return true;
}

template <class T, class Alloc>
bool operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs){
	for (int index = 0; index < lhs.size() && index < rhs.size(); index++){
		if (lhs[index] < rhs[index])
			return false;
	}
	if (lhs.size() < rhs.size())
		return false;
	return true;
}


template <class T, class Alloc>
void swap (vector<T,Alloc>& x, vector<T,Alloc>& y){
	x.swap(y);
}
}