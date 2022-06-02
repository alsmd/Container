#pragma once
#include "./vector.hpp"

namespace ft{
template <class T, class Container = ft::vector<T> > class stack{
	public:
	typedef T											value_type;
	typedef Container									container_type;
	typedef typename Container::size_type				size_type;
	typedef typename Container::reference				reference;



	explicit stack (const container_type& ctnr = container_type()) : c(ctnr){}

	stack(stack &cpy){
		this->c = cpy.c;
	}

	stack& operator=( const stack& other ){
		this->c = other.c;
	}

	reference top(){
		return this->c.back();
	}

	bool empty() const{
		return this->c.empty();
	}

	size_type size() const{
		return this->c.size();
	}


	void push( const value_type& value ){
		c.push_back(value);
	}

	void pop(){
		c.pop_back();
	}


	protected:
		Container c;
};


template< class T, class Container >
bool operator==( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs ){
	return lhs.c == rhs.c;
}
template< class T, class Container >
bool operator!=( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs ){
	return lhs.c != rhs.c;
}
template< class T, class Container >
bool operator<( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs ){
	return lhs.c < rhs.c;
	
}
template< class T, class Container >
bool operator<=( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs ){
	return lhs.c <= rhs.c;
}
template< class T, class Container >
bool operator>( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs ){
	return lhs.c > rhs.c;
}
template< class T, class Container >
bool operator>=( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs ){
	return lhs.c >= rhs.c;
}

}
