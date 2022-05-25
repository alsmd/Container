#pragma once

namespace ft{

template< typename T1, typename T2 > struct pair{
	//Types
	typedef T1 first_type;	
	typedef T2 second_type;
	//Variables
	T1 first;	
	T2 second;
	//Functions
	pair() : first(), second(){}
	pair( const T1& x, const T2& y ) : first(x), second(y){
	}
	template< class U1, class U2 >
	pair( const pair<U1, U2>& p ){
		*this = p;
	}

	pair& operator=( const pair& other ){
		this->first = other.first;
		this->second = other.second;
		return *this;
	}

	

};

template< class T1, class T2 >
ft::pair<T1,T2> make_pair( T1 t, T2 u ){
	return ft::pair<T1, T2>(t, u); 
}

template< class T1, class T2 >
bool operator==( const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs ){
	if (lhs.first == rhs.first && lhs.second == rhs.second)
		return true;
	return false;
}


template< class T1, class T2 >
bool operator!=( const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs ){
	return !(lhs == rhs);
}

template< class T1, class T2 >
bool operator<( const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs ){
	if (lhs.first < rhs.first)
		return true;
	if (lhs.first == rhs.first && lhs.second == rhs.second)
		return true;
	return false;
}

template< class T1, class T2 >
bool operator<=( const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs ){
	return !(rhs < lhs);
}

template< class T1, class T2 >
bool operator>( const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs ){
	return rhs < lhs;
}

template< class T1, class T2 >
bool operator>=( const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs ){
	return !(lhs < rhs);
}



}