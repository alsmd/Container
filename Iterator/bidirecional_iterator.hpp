#pragma once
// #include "iterator_traits.hpp"
#include "../Util/BSTAlgorithm.hpp"
#include "../Util/BSTUtils.hpp"
namespace ft{
	


template< typename Key, typename T >
struct bidirecional_iterator
{
    typedef T									value_type;
	typedef std::bidirectional_iterator_tag		iterator_category;
    typedef std::ptrdiff_t						difference_type;
    typedef value_type*							pointer;  // or also value_type*
    typedef value_type&							reference;  // or also value_type&

	bidirecional_iterator(ft::BSTNode<Key, T> *node, int size, bool end = false)
		: _node(node){
		this->size = size;
		this->end = end;
		this->pair = new ft::pair<const Key, T>(this->size, T());
		if (node){

			while (node->parent)
				node = node->parent;
			this->_first = ft::getLowerNode(node);
			this->_last = ft::getHigherNode(node);
		}
		if (this->end)
			this->_node = NULL;
	}

	bidirecional_iterator()
		: _node(NULL), _first(NULL), _last(NULL), end(false), size(0){
		this->pair = new ft::pair<const Key, T>(this->size, T());
	}

	template< typename k, typename t >
	bidirecional_iterator(bidirecional_iterator<k,t> &cpy)
		: _node(cpy._node), size(cpy.size), _first(cpy._first), _last(cpy._last), end(cpy.end)
	{
		this->pair = new ft::pair<const k, t>(this->size, t());
	}

	template<typename k, typename t>
	bidirecional_iterator<k,t> & operator =(bidirecional_iterator<k,t> &other){
		this->_node = other._node;
		this->_first = other._first;
		this->_last = other._last;
		this->end = other.end;
		this->size = other.size;

		return *this;
	}

	~bidirecional_iterator(){
		delete this->pair;
	}

	//Operators
	ft::pair<const Key, T> *operator *(){
		if (end)
			return this->pair;
		return (this->_node->data);
	}

	ft::pair<const Key, T> *operator ->(){
		if (end)
			return this->pair;
		return (this->_node->data);
	}

	/* bidirecional_iterator operator+(difference_type n) const {
		return bidirecional_iterator(this->_ptr + n);
	}

	bidirecional_iterator &operator+=(difference_type n) const {
		this->_ptr += n;
		return (*this);
	}

	bidirecional_iterator operator-(difference_type n) const {
		return bidirecional_iterator(this->_ptr - n);
	}

	bidirecional_iterator &operator-=(difference_type n) const {
		this->_ptr -= n;
		return (*this);
	}

	difference_type operator-(bidirecional_iterator const &rhs) const {
		return this->_ptr - rhs._ptr;
	} */


	//prefix increment
	bidirecional_iterator &operator++(){
		if (this->end){
			this->end = false;
			this->_node = this->_last;
		}
		else if (this->_node->right){
			this->_node = ft::getLowerNode(this->_node->right);
		}
		else if(this->_node->parent && this->_node != this->_last){
			this->_comingFrom = this->_node->getDirection();
			this->_node = this->_node->parent;
			if (this->_comingFrom == ft::Direction::Right)
				this->_node = this->_node->parent;
		}else{
			this->end = true;
			this->_node = NULL;
		}
		return (*this);
	}

	//Postfix
	bidirecional_iterator operator++(int) {
		bidirecional_iterator it(this->_node, this->size);
		++(*this);
		return (it);
	}


	//prefix decrement
	bidirecional_iterator &operator--(){
		if (this->_node == NULL)
			return *this;
		if (this->end){
			this->end = false;
			this->_node = this->_last;
		}
		else if (this->_node == this->_first)
			this->end = true;
		else if (this->_node->left){
			this->_comingFrom = ft::Direction::Parent;
			this->_node = ft::getHigherNode(this->_node->left);
		}
		else if(this->_node->parent){
			this->_comingFrom = this->_node->getDirection();
			this->_node = this->_node->parent;
			if (this->_comingFrom == ft::Direction::Left){
				while (this->_node->parent)
					this->_node = this->_node->parent;
			}
		}
		return *this;
	}

	//Postfix
	bidirecional_iterator operator--(int) {
		bidirecional_iterator tmp = *this;
		--(*this);
		return tmp;
	}

	
	friend bool operator== (const bidirecional_iterator<Key, T>& a, const bidirecional_iterator<Key, T>& b) {
			return a._node == b._node;
	};
    friend bool operator!= (const bidirecional_iterator<Key, T>& a, const bidirecional_iterator<Key, T>& b) {
		return a._node != b._node; 
	};


/* 	reference operator[](difference_type n ) const {
		return (*(this->_ptr + n));
	}
 */

	private:
		ft::BSTNode<Key, T>	*_node;
		ft::BSTNode<Key, T>	*_first;
		ft::BSTNode<Key, T>	*_last;
		ft::Direction		_comingFrom;
		int					size;
		bool				end;
		ft::pair<const Key, T>  *pair;


};

}