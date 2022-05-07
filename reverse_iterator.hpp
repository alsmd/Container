#pragma once
#include "iterator_traits.hpp"

namespace ft{
template< class Iter > class reverse_iterator{
	public:
		typedef Iter													iterator_type;
		typedef typename ft::iterator_traits<Iter>::iterator_category	iterator_category;
		typedef typename ft::iterator_traits<Iter>::value_type 			value_type;
		typedef typename ft::iterator_traits<Iter>::difference_type		difference_type;
		typedef typename ft::iterator_traits<Iter>::pointer				pointer;
		typedef typename ft::iterator_traits<Iter>::reference			reference;

		reverse_iterator() : _current(){}

		explicit reverse_iterator(iterator_type current) : _current(current) {}

		template< class U > reverse_iterator( const reverse_iterator<U>& other ) : _current(other.base){}
		//Operators

		template< class U > reverse_iterator& operator=( const reverse_iterator<U>& other );
		

		iterator_type base() const{
			return this->_current;
		}

		/* operator[]( difference_type n ) const; */


		reference operator *(){
			return *_current;
		}

		pointer operator ->(){
			return _current;
		}
		
		reverse_iterator operator+(difference_type n) const {
			return reverse_iterator(this->_ptr - n);
		}

		reverse_iterator &operator+=(difference_type n) const {
			this->_ptr -= n;
			return (*this);
		}

		reverse_iterator operator-(difference_type n) const {
			return reverse_iterator(this->_ptr + n);
		}

		reverse_iterator &operator-=(difference_type n) const {
			this->_ptr += n;
			return (*this);
		}

		//prefix increment
		reverse_iterator &operator++(){
			this->_current--;
			return (*this);
		}

		//Postfix
		reverse_iterator operator++(int) {
			reverse_iterator tmp = *this;
			--(this->_current);
			return tmp;
		}


		//prefix decrement
		reverse_iterator &operator--(){
			this->_current++;
			return (*this);
		}

		//Postfix
		reverse_iterator operator--(int) {
			reverse_iterator tmp = *this;
			this->_current++;
			return tmp;
		}


		
	private:
		iterator_type _current;
	
};

template< class Iterator1, class Iterator2 >
bool operator==( const ft::reverse_iterator<Iterator1>& lhs, const ft::reverse_iterator<Iterator2>& rhs ){
	return (lhs.base() == rhs.base());

}
template< class Iterator1, class Iterator2 >
bool operator!=( const ft::reverse_iterator<Iterator1>& lhs, const ft::reverse_iterator<Iterator2>& rhs ){
	return (lhs.base() != rhs.base());

}


/* template< class Iterator1, class Iterator2 >
bool operator<( const ft::reverse_iterator<Iterator1>& lhs, const ft::reverse_iterator<Iterator2>& rhs );

template< class Iterator1, class Iterator2 >
bool operator<=( const ft::reverse_iterator<Iterator1>& lhs,
                 const ft::reverse_iterator<Iterator2>& rhs );

template< class Iterator1, class Iterator2 >
bool operator>( const ft::reverse_iterator<Iterator1>& lhs,
                const ft::reverse_iterator<Iterator2>& rhs );

template< class Iterator1, class Iterator2 >
bool operator>=( const ft::reverse_iterator<Iterator1>& lhs,
                 const ft::reverse_iterator<Iterator2>& rhs );
	*/
} 