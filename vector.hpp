#pragma once
#include <memory>
#include <iostream>
#include <cstddef>
#include <exception>
#include <sstream>
#include <cmath>
#include "random_access_iterator.hpp"
#include "reverse_iterator.hpp"

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

	explicit vector( const Allocator& alloc = allocator_type())
	{
		_alloc = alloc;
		_finalBlock = NULL;
		_index = NULL;
		_data = NULL;

	}


	explicit vector( size_type count, const T& value = T(), const Allocator& alloc = Allocator())
	{
		_data = _alloc.allocate(count);
		_finalBlock = _data + count;
		_index = _data;
		while (count--)
		{
			_alloc.construct(_index, value);
			_index++;
		}
	}

	iterator begin() {
		return iterator(_data);
	}
    iterator end()   {
		return iterator(_index);
	}

	const_iterator begin() const{
		return iterator(_data);
	}
    const_iterator end() const {
		return iterator(_index);
	}


	reverse_iterator rbegin() {
		return reverse_iterator(this->_index);
	}
    reverse_iterator rend()   {
		return reverse_iterator(this->_data);
	}

	const_reverse_iterator rbegin() const{
		return const_reverse_iterator(this->_index);
	}
    const_reverse_iterator rend() const{
		return const_reverse_iterator(this->_data);
	}

	~vector()
	{
		this->clear();
		if (_data)
			_alloc.deallocate(_data, this->capacity());
	}


	size_type	size() const
	{
		return this->_index - this->_data;
	}

	size_type capacity() const
	{
		return this->_finalBlock - this->_data;
	}

	/***
	 * 
	 * @brief	Gonna check if there is space to more n elements inside the container.
	 * 			If not realloc container to support more n elements
	 * 
	 * 
	**/
	void reserve(size_type n)
	{
		/* if (n > this->max_size())
			throw length_error */
		if (n > this->capacity())
		{
			pointer		new_data = _alloc.allocate(n);
			pointer		new_finalBlock = new_data + n;
			pointer		new_index = new_data;
			size_type	size = this->size();
			for (iterator i = this->begin(); i != this->end(); i++)
			{
				_alloc.construct(new_index, *i);
				new_index++;
			}
			this->clear();
			if (_data)
				_alloc.deallocate(_data, this->capacity());
			_data = new_data;
			_finalBlock = new_finalBlock;
			_index = new_index;
		}
	}

	bool	empty() const
	{
		return (this->begin() == this->end() ? true : false);
	}

	void clear()
	{
		for (size_type i = 0; i < this->size(); i++)
			_alloc.destroy(_data + i);
		this->_index = this->_data;
	}

	size_type max_size() const
	{
		return (this->_alloc.max_size());
	}

	iterator insert( iterator pos, const T& value ){
		size_type	position = &(*pos) - this->_data; // index of pos inside array container
		if (this->size() + 1 <= this->capacity())//still has empty field
		{
			for (size_type s = this->size(); s > position; s--)
				this->_alloc.construct(this->_data + s, *(this->_data + s - 1));
			this->_index++;
			this->_alloc.construct(this->_data + position, value);
		}
		else//realloc and put the element shifting elements
		{
			pointer	new_data = this->_alloc.allocate(this->size() + 1);
			pointer new_finalBlock = new_data + this->size() + 1;
			pointer new_index = new_data;
			for (size_type i = 0; i < position && i <= this->size(); i++)
			{
				if (i < this->size())
					this->_alloc.construct(new_index, *(this->_data + i));
				else
					this->_alloc.construct(new_index, T());
				new_index++;
			}
			if (position > this->size())
			{
				std::cout << "exception position alem do container\n"; 
			}
			else
			{
				this->_alloc.construct(new_index, value);
				new_index++;
				for (size_type i = position; i < this->size(); i++)
				{
					this->_alloc.construct(new_index, *(this->_data + i));
					new_index++;
				}
			}
			this->clear();
			if (_data)
				_alloc.deallocate(_data, this->capacity());
			_data = new_data;
			_finalBlock = new_finalBlock;
			_index = new_index;
		}
		return (this->_data + position);
	}

	void insert( iterator pos, size_type count, const T& value )
	{
		size_type	position = &(*pos) - this->_data; // index of pos inside array container
		if (this->size() + count <= this->capacity())//still has empty field
		{
			for (size_type i = 0; i < count; i++)
			{
				for (size_type s = this->size(); s > position; s--)
					this->_alloc.construct(this->_data + s, *(this->_data + s - 1));
				this->_index++;
				this->_alloc.construct(this->_data + position, value);
			}
		}
		else//realloc and put the element shifting elements
		{
			pointer	new_data = this->_alloc.allocate(this->size() + count);
			pointer new_finalBlock = new_data + this->size() + count;
			pointer new_index = new_data;
			for (size_type i = 0; i < position && i <= this->size(); i++)
			{
				if (i < this->size())
					this->_alloc.construct(new_index, *(this->_data + i));
				else
					this->_alloc.construct(new_index, T());
				new_index++;
			}
			if (position > this->size())
			{
				std::cout << "exception position alem do container\n"; 
			}
			else
			{
				for (size_type i = 0; i < count; i++)
				{
					this->_alloc.construct(new_index, value);
					new_index++;
				}
				for (size_type i = position; i < this->size(); i++)
				{
					this->_alloc.construct(new_index, *(this->_data + i));
					new_index++;
				}
			}
			this->clear();
			if (_data)
				_alloc.deallocate(_data, this->capacity());
			_data = new_data;
			_finalBlock = new_finalBlock;
			_index = new_index;
		}
	}


	template< class InputIt >
	void insert( iterator pos, InputIt first, InputIt last )
	{
		size_type numberOfNewElements = std::abs(&(*last) - &(*first));
		size_type	insertPosition = &(*pos) - this->_data; // index of pos inside array container

		if (this->size() + numberOfNewElements <= this->capacity())
		{
			for (size_type i = 0; i < numberOfNewElements; i++)
			{
				for (size_type s = this->size(); s > insertPosition; s--)
					this->_alloc.construct(this->_data + s, *(this->_data + s - 1));
				this->_index++;
				this->_alloc.construct(this->_data + insertPosition, *first);
				first++;
			}
		}else
		{
			pointer	new_data = this->_alloc.allocate(this->size() + numberOfNewElements);
			pointer new_finalBlock = new_data + this->size() + numberOfNewElements;
			pointer new_index = new_data;
			for (size_type i = 0; i < insertPosition && i <= this->size(); i++)
			{
				if (i < this->size())
					this->_alloc.construct(new_index, *(this->_data + i));
				else
					this->_alloc.construct(new_index, T());
				new_index++;
			}
			if (insertPosition > this->size())
			{
				std::cout << "exception insertPosition alem do container\n"; 
			}
			else
			{
				for (size_type i = 0; i < numberOfNewElements; i++)
				{
					this->_alloc.construct(new_index, *first);
					first++;
					new_index++;
				}
				for (size_type i = insertPosition; i < this->size(); i++)
				{
					this->_alloc.construct(new_index, *(this->_data + i));
					new_index++;
				}
			}
			this->clear();
			if (_data)
				_alloc.deallocate(_data, this->capacity());
			_data = new_data;
			_finalBlock = new_finalBlock;
			_index = new_index;
		}

	}

	reference front()
	{
		return *(this->begin());
	}

	const_reference front() const
	{
		return *(this->begin());
	}
	reference back()
	{
		iterator i = this->end();
		i--;
		return *(i);
	}
	const_reference back() const
	{
		iterator i = this->end();
		i--;
		return *(i);
	}



	reference operator[]( size_type pos )
	{
		iterator iter = this->begin(); 
		for (size_type i = 0; i < pos; i++)
			iter++;
		return (*iter);
	}



	const_reference operator[]( size_type pos ) const
	{
		iterator iter = this->begin(); 
		for (size_type i = 0; i < pos; i++)
			iter++;
		return (*iter);
	}

	allocator_type get_allocator() const
	{
		return this->_alloc;
	}

	reference at( size_type pos )
	{
		std::ostringstream	o;
		o << "vector::_M_range_check: __n (which is " << pos << ") >= this->size() (which is " << this->size() << ")";
		if (pos >= this->size()) 
			throw std::out_of_range(o.str());
		return (*this)[pos];
	}
	const_reference at( size_type pos ) const 
	{
		std::ostringstream	o;
		o << "vector::_M_range_check: __n (which is " << pos << ") >= this->size() (which is " << this->size() << ")";
		if (pos >= this->size()) 
			throw std::out_of_range(o.str());
		return (*this)[pos];
	}

	T* data()
	{
		return (this->_data);
	}

	const T* data() const
	{
		return (this->_data);
	}

	vector& operator=( const vector& other )
	{
		this->clear();
		this->insert(this->begin(), other.begin(), other.end());
		return (*this);
	}
	
	vector( const vector& other ) :
		_alloc(allocator_type())
	{
		*this = other;
	}

/* 	template< class InputIt >
	vector( InputIt first, InputIt last, const Allocator& alloc = Allocator() )
	{
		this->_alloc = alloc;
		this->insert(this->begin(), first, last);
	}
 */
	void assign( size_type count, const T& value )
	{
		this->clear();
		this->insert(this->begin(), count, value);
	}

	/* template< class InputIt >
	void assign( InputIt first, InputIt last )
	{
		size_type numberOfNewElements = std::abs(&(*last) - &(*first));
		if (numberOfNewElements <= this->capacity())
		{
			this->clear();
			this->insert(this->begin(), first, last);
		}
	} */

	void resize( size_type count, T value = T() ){

	}


	iterator erase( iterator pos )
	{
		iterator next = pos;
		next++;
		size_type index = &(*pos) - this->_data;
		this->_alloc.destroy(this->data + index);
		for (; index < this->size() - 1; index++)
		{
			this->_alloc.construct(this->_data + index, *(this->_data + index + 1));
		}
		this->_index--;
		return (next);
	}

	iterator erase( iterator first, iterator last )
	{
		for (; first != last; first++)
		{
			this->_alloc.destroy(&(*first));
			this->_index--;
		}
		this->_alloc.destroy(&(*first));
		size_type index = &(*first) - this->_data;
		size_type end = &(*last) - this->_data + 1;
		while (end < this->size() - 1)
		{
			this->_alloc.construct(this->_data + index, *(this->_data + end));
			index++;
			end++;
		}
		return (iterator(this->_index - 1));
	}


	void push_back (const value_type& val)
	{
		if (this->_index >= this->_finalBlock)
		{
			pointer	new_data = this->_alloc.allocate(this->size() * 2);
			pointer new_finalBlock = new_data + this->size() * 2;
			pointer new_index = new_data;
			for (iterator i = this->begin(); i != this->end(); i++)
			{
				this->_alloc.construct(new_index, *i);
				new_index++;
			}


			this->clear();
			if (_data)
				_alloc.deallocate(_data, this->capacity());
			_data = new_data;
			_finalBlock = new_finalBlock;
			_index = new_index;
		}
		this->_alloc.construct(this->_index, val);
		this->_index++;
	}

	void pop_back()
	{
		if (this->size() > 0)
		{
			this->_index--;
			this->_alloc.destroy(this->_index);
		}
	}
private:
	/* data */
	allocator_type	_alloc;//gerenciador de memoria
	pointer			_data;//começo
	pointer			_finalBlock;//final de todo bloco
	pointer			_index;//depois ultimo elemento

	
	
protected:
};



}