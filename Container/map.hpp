#pragma once
#include "../Util/functional.hpp"
#include "../Util/utility.hpp"
#include "../Util/BSTAlgorithm.hpp"
#include "../Util/BSTUtils.hpp"
#include "../Iterator/bidirecional_iterator.hpp"

namespace ft {

template< typename Key, typename T, typename Compare = ft::less<Key>, typename Allocator = std::allocator<ft::pair<const Key, T> > > class map{
	public:
		typedef			Key key_type;
		typedef			T mapped_type;
		typedef typename ft::pair<const Key, T> value_type;
		typedef typename std::size_t size_type;
		typedef typename std::ptrdiff_t difference_type;
		typedef 		Compare key_compare;
		typedef 		Allocator allocator_type;
		typedef 		value_type& reference;
		typedef const value_type& const_reference;
		typedef typename Allocator::pointer pointer;
		typedef typename Allocator::const_pointer const_pointer;
		typedef ft::bidirecional_iterator<Key, T>	iterator;
		typedef const iterator						const_iterator;

	class value_compare{
		protected:
			Compare comp;
			value_compare(Compare c) {
				this->comp = c;
			}
		public:
			typedef bool result_type;
			typedef T first_argument_type;
			typedef T second_argument_type;

		bool operator()(const value_type &lhs, const value_type &rhs) const{
			return comp(lhs.first, rhs.first);
		}
	};

	map() :  _alloc(), _node(NULL){
	}

	~map(){
		// this->clear();
	}

	//Iterators

	iterator begin(){
		return iterator(this->_node ? ft::getLowerNode(this->_node) : NULL, this->_node ? this->_node->size: 0);
	}

	iterator end(){
		return iterator(this->_node ? ft::getHigherNode(this->_node) : NULL, this->_node ? this->_node->size: 0, true);
	}



	/* reverse_iterator rbegin();
	const_reverse_iterator rbegin() const;

	reverse_iterator rend();
	const_reverse_iterator rend() const; */


	//Capacity
	/***
	 * 
	 * @brief Test whether container is empty
	 * @return true if the container size is 0, false otherwise.
	 * 
	**/
	bool empty() const{
		return this->_node->size == 0 ? true : false;
	}

	/***
	 * 
	 * @brief Returns the number of elements in the map container.
	 * @return The number of elements in the container.
	 * 
	**/
	size_type size() const{
		return this->_node->size;
	}

	/***
	 * 
	 * @brief Returns the maximum number of elements that the map container can hold.
	 * @return The maximum number of elements a map container can hold as content.
	 * 
	**/
	size_type max_size() const{
		return this->_alloc.max_size();
	}

	
	//Element Access

	/***
	 * 
	 * @brief If k matches the key of an element in the container, the function returns a reference to its mapped value.
	 * 			If k does not match the key of any element in the container, the function inserts a new element with that key
	 *			and returns a reference to its mapped value. Notice that this always increases the container size by one, even if
	 			no mapped value is assigned to the element (the element is constructed using its default constructor).
	 * @return 	A reference to the mapped value of the element with a key value equivalent to k.
	 * 
	**/
	mapped_type& operator[] (const key_type& k){
		return ft::insertNode(k, &this->_node, &this->_alloc);
	}


	//Modifiers

	/***
	 * 
	 * @brief	Removes all elements from the map container (which are destroyed), leaving the container with a size of 0.
	 * 
	**/
	void clear(){
		this->erase(this->begin(), this->end());
	}

	/***
	 * 
	 * @brief 			Removes from the map container either a single element or a range of elements ([first,last)).
	 * @param position	Iterator pointing to a single element to be removed from the map.
	 * 					This shall point to a valid and dereferenceable element.
	 * 
	**/
	void erase (iterator position){
		ft::removeNode(position->first, &this->_node);
	}

	/***
	 * 
	 * @brief Removes from the map container either a single element or a range of elements ([first,last)).
	 * @param k Key of the element to be removed from the map.
	 * 			Member type key_type is the type of the elements in the container, defined in
	 * 			map as an alias of its first template parameter (Key).
	 * @return the function returns the number of elements erased.
	 * 
	**/
	size_type erase (const key_type& k){
		int res =  ft::removeNode(k, &this->_node) ? 1 : 0;
		return res;
	}

	/***
	 * 
	 * @brief 				Removes from the map container either a single element or a range of elements ([first,last)).
	 * @param first, last	Iterators specifying a range within the map container to be removed: [first,last). i.e.,
	 * 						the range includes all the elements between first and last, including the element pointed by first
	 * 						but not the one pointed by last.
	 * 
	**/
	void erase (iterator first, iterator last){
		iterator holder;
		while (first != last){
			holder = first;
			first++;
			ft::removeNode(holder->first, &this->_node);
		}
	}

	
	/***
	 * 
	 * @brief 	Exchanges the content of the container by the content of x, which is another map of the same type. Sizes may differ.
	 * 			After the call to this member function, the elements in this container are those which were in x before the call,
	 * 			and the elements of x are those which were in this. All iterators, references and pointers remain valid for the swapped objects.
	 * 
	**/
	void swap (map& x){
		ft::BSTNode<Key, T> holder = this->_node;
		this->_node = x._node;
		x._node = holder;
	}

	/***
	 * 
	 * @brief 	Extends the container by inserting new elements, effectively increasing the container size by the number of elements inserted.
	 * 			Because element keys in a map are unique, the insertion operation checks whether each inserted element has a key equivalent to
	 * 			the one of an element already in the container, and if so, the element is not inserted, returning an iterator to this existing
	 * 			element (if the function returns a value).
	 * @param val Value to be copied to (or moved as) the inserted element.

	 * 
	**/
	ft::pair<iterator,bool> insert (const value_type& val){
		bool created = this->_node->insert(val);
		ft::BSTNode<Key, T>	*createdNode = this->_node->find(val.first);
		return ft::pair<iterator, bool>(iterator(createdNode, this->_node->size), created);
	}

	/***
	 * 
	 * @brief 	Extends the container by inserting new elements, effectively increasing the container size by the number of elements inserted.
	 * 			Because element keys in a map are unique, the insertion operation checks whether each inserted element has a key equivalent to
	 * 			the one of an element already in the container, and if so, the element is not inserted, returning an iterator to this existing
	 * 			element (if the function returns a value).
	 * @param position Hint for the position where the element can be inserted.
	 * @param val Value to be copied to (or moved as) the inserted element.
	**/
	iterator insert (iterator position, const value_type& val){
		this->_node->find(position->_first)->insert(val);
		ft::BSTNode<Key, T>	*createdNode = this->_node->find(val->first);
		return iterator(createdNode, this->_node->size);
	}


	/***
	 * 
	 * @brief 	Extends the container by inserting new elements, effectively increasing the container size by the number of elements inserted.
	 * 			Because element keys in a map are unique, the insertion operation checks whether each inserted element has a key equivalent to
	 * 			the one of an element already in the container, and if so, the element is not inserted, returning an iterator to this existing
	 * 			element (if the function returns a value).
	 * @param   firstLast	Iterators specifying a range of elements. Copies of the elements in the range [first,last) are inserted in the container.
	 * 			Notice that the range includes all the elements between first and last, including the element pointed by first but not the one pointed
	 * 			 by last.
	**/
	template <class InputIterator>
	void insert (InputIterator first, InputIterator last){
		while (first != last){
			this->_node->insert(first->first) = first->second;
			first++;
		}
	}

	key_compare key_comp() const{
		return key_compare();
	}

	value_compare value_comp() const{
		return value_compare(key_compare());
	}

	allocator_type get_allocator() const{
		return this->_alloc;
	}


	size_type count (const key_type& k) const{
		return this->_node->find(k) ? 1 : 0;
	}

	iterator find (const key_type& k){
		if (this->_node == NULL)
			return this->end();
		ft::BSTNode<Key, T>	*found = this->_node->find(k);
		if (found == NULL)
			return this->end();
		return iterator(found, this->_node->size);
	}
	/* const_iterator find (const key_type& k) const{
		if (this->_node == NULL)
			return this->end();
		ft::BSTNode<Key, T>	*found = this->_node->find(k);
		if (found == NULL)
			return this->end();
		return iterator(found, this->_node->size);
	} */

	/* iterator upper_bound (const key_type& k){
		
	} */


	protected:
		ft::BSTNode<Key, T>								*_node;
		allocator_type									_alloc;//gerenciador de memoria


};

}