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

		reverse_iterator(reverse_iterator &cpy) : _current(cpy._current){}
		explicit reverse_iterator(iterator_type current) : _current(current) {}

		template< class U > reverse_iterator( const reverse_iterator<U>& other ) : _current(other._current){}
		//Operators

		template< class U > reverse_iterator& operator=( const reverse_iterator<U>& other );
		

		iterator_type base() const{
			return this->_current;
		}

		/* operator[]( difference_type n ) const; */


		reference operator *(){
			iterator_type cpy = _current;
			return *(--cpy);
		}

		pointer operator ->(){
			return &(operator*());
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


		reference operator[](difference_type n ) const {
			return (this->base()[-n - 1]);
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


template< class Iterator1, class Iterator2 >
bool operator<( const ft::reverse_iterator<Iterator1>& lhs, const ft::reverse_iterator<Iterator2>& rhs ){
	return (lhs.base() < rhs.base());
}

template< class Iterator1, class Iterator2 >
bool operator<=( const ft::reverse_iterator<Iterator1>& lhs, const ft::reverse_iterator<Iterator2>& rhs ){
	return (lhs.base() <= rhs.base());
}

template< class Iterator1, class Iterator2 >
bool operator>( const ft::reverse_iterator<Iterator1>& lhs, const ft::reverse_iterator<Iterator2>& rhs ){
	return (lhs.base() > rhs.base());
}

template< class Iterator1, class Iterator2 >
bool operator>=( const ft::reverse_iterator<Iterator1>& lhs, const ft::reverse_iterator<Iterator2>& rhs ){
	return (lhs.base() >= rhs.base());
}
	

template< class Iterator >
typename reverse_iterator<Iterator>::difference_type
operator-( const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs ){
	return (lhs.base() - rhs.base());
}

template< class Iter >
reverse_iterator<Iter>
operator+( typename reverse_iterator<Iter>::difference_type n, const reverse_iterator<Iter>& it ){
	return reverse_iterator<Iter>(it.base() - n);
}

} 