#pragma once
// #include "iterator_traits.hpp"

namespace ft{
	
template<typename T>
struct random_access_iterator
{
    typedef T									value_type;
	typedef std::random_access_iterator_tag		iterator_category;
    typedef std::ptrdiff_t						difference_type;
    typedef value_type*							pointer;  // or also value_type*
    typedef value_type&							reference;  // or also value_type&


	random_access_iterator(pointer ptr) : _ptr(ptr) {}


	//Operators
	reference operator *(){
		return *_ptr;
	}

	pointer operator ->(){
		return _ptr;
	}

	random_access_iterator operator+(difference_type n) const {
		return random_access_iterator(this->_ptr + n);
	}

	random_access_iterator &operator+=(difference_type n) const {
		this->_ptr += n;
		return (*this);
	}

	random_access_iterator operator-(difference_type n) const {
		return random_access_iterator(this->_ptr - n);
	}

	random_access_iterator &operator-=(difference_type n) const {
		this->_ptr -= n;
		return (*this);
	}

	difference_type operator-(random_access_iterator const &rhs) const {
		return this->_ptr - rhs._ptr;
	}


	//prefix increment
	random_access_iterator &operator++(){
		_ptr++;
		return (*this);
	}

	//Postfix
	random_access_iterator operator++(int) {
		random_access_iterator tmp = *this;
		++(*this);
		return tmp;
	}


	//prefix decrement
	random_access_iterator &operator--(){
		_ptr--;
		return (*this);
	}

	//Postfix
	random_access_iterator operator--(int) {
		random_access_iterator tmp = *this;
		--(*this);
		return tmp;
	}

	friend bool operator== (const random_access_iterator& a, const random_access_iterator& b) {
		return a._ptr == b._ptr;
	};
    friend bool operator!= (const random_access_iterator& a, const random_access_iterator& b) {
		return a._ptr != b._ptr;
	};


	reference operator[](difference_type n ) const {
		return (*(this->_ptr + n));
	}


	private:
		pointer _ptr;
};
}