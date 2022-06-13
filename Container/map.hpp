#pragma once
#include "../Util/functional.hpp"
#include "../Util/utility.hpp"
// #include "../Util/BSTAlgorithm.hpp"
// #include "../Util/BSTUtils.hpp"
#include "../Iterator/bidirecional_iterator.hpp"
#include "../Iterator/reverse_iterator.hpp"
#include "../Util/BinarySearchTree.hpp"
#include "./vector.hpp"

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
		typedef	ft::reverse_iterator<iterator>				reverse_iterator;
		typedef	const ft::reverse_iterator<const_iterator>	const_reverse_iterator;

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

	map() :  _alloc(), tree(&this->_alloc){
	}

	~map(){
		this->clear();
	}

	map (const map& x) :
		_alloc(x._alloc), tree(&_alloc){
		this->operator=(x);
	}

	map& operator= (const map& x){
		this->clear();
		this->insert(x.begin(), x.end());
		return (*this);
	}
	//Iterators

	iterator begin(){
		if (this->tree.root){
			return iterator(
				ft::BinarySearchTree<Key, T>::getLowerNode(this->tree.root),
				ft::BinarySearchTree<Key, T>::getLowerNode(this->tree.root),
				ft::BinarySearchTree<Key, T>::getHigherNode(this->tree.root),
				this->tree.root ? 0 : 0
			);
		}
		return iterator(
			NULL,
			NULL,
			NULL,
			this->tree.root ? 0 : 0
		);
	}

	iterator end(){
		if (this->tree.root){
			return iterator(
			NULL,
			ft::BinarySearchTree<Key, T>::getLowerNode(this->tree.root),
			ft::BinarySearchTree<Key, T>::getHigherNode(this->tree.root),
			this->tree.root ? 0 : 0, true
			);
		}
		return iterator(
			NULL,
			NULL,
			NULL,
			this->tree.root ? 0 : 0, true
		);
	}

	const iterator begin()const {
		if (this->tree.root){
			return const_iterator(
				ft::BinarySearchTree<Key, T>::getLowerNode(this->tree.root),
				ft::BinarySearchTree<Key, T>::getLowerNode(this->tree.root),
				ft::BinarySearchTree<Key, T>::getHigherNode(this->tree.root),
				this->tree.root ? 0 : 0
			);
		}
		return const_iterator(
			NULL,
			NULL,
			NULL,
			this->tree.root ? 0 : 0
		);
	}

	const_iterator end() const{
		if (this->tree.root){
			return const_iterator(
			NULL,
			ft::BinarySearchTree<Key, T>::getHigherNode(this->tree.root),
			ft::BinarySearchTree<Key, T>::getLowerNode(this->tree.root),
			this->tree.root ? 0 : 0, true
			);
		}
		return const_iterator(
			NULL,
			NULL,
			NULL,
			this->tree.root ? 0 : 0, true
		);
	}

	reverse_iterator rbegin() {
		return reverse_iterator(this->end());
	}

	reverse_iterator rend()   {
		return reverse_iterator(this->begin());
	}

	const_reverse_iterator rbegin() const{
		return const_reverse_iterator(this->end());
	}

	const_reverse_iterator rend() const {
		return const_reverse_iterator((this->begin()));
	}

	//Capacity
	/***
	 * 
	 * @brief Test whether container is empty
	 * @return true if the container size is 0, false otherwise.
	 * 
	**/
	bool empty() const{
		return this->begin() == this->end() ? true : false;
	}

	/***
	 * 
	 * @brief Returns the number of elements in the map container.
	 * @return The number of elements in the container.
	 * 
	**/
	size_type size() const{
		return this->tree.size;
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
		return this->tree.insert(k);
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
		tree.remove(position->first);
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
		int res =  tree.remove(k) ? 1 : 0;
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
			this->tree.remove(holder->first);
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
		ft::Node<Key, T> holder = this->tree.root;
		this->tree.root = x.tree.root;
		x.tree.root = holder;
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
		bool created = this->tree->insert(val);
		ft::Node<Key, T>	*createdNode = this->tree.root->find(val.first);
		return ft::pair<iterator, bool>(iterator(createdNode, this->tree.root->size), created);
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
		this->tree.root->find(position->_first)->insert(val);
		ft::Node<Key, T>	*createdNode = this->tree.root->find(val->first);
		return iterator(createdNode,ft::BinarySearchTree<Key, T>::getHigherNode(this->tree.root),
			ft::BinarySearchTree<Key, T>::getLowerNode(this->tree.root),this->tree.root->size);
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
			this->tree.insert(first->first) = first->second;
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
		return this->tree.root->find(k) ? 1 : 0;
	}

	iterator find (const key_type& k){
		if (this->tree.root == NULL)
			return this->end();
		ft::Node<Key, T>	*found = this->tree.root->find(k);
		if (found == NULL)
			return this->end();
		return iterator(found, this->tree.root->size);
	}
	const_iterator find (const key_type& k) const{
		if (this->tree.root == NULL)
			return this->end();
		ft::Node<Key, T>	*found = this->tree.root->find(k);
		if (found == NULL)
			return this->end();
		return iterator(found, this->tree.root->size);
	}

	iterator upper_bound (const key_type& k){
		iterator begin = this->begin();
		iterator end = this->end();
		for (; begin != end; begin++){
			if ((this->key_comp()(k, begin->first)))
				break;
		}
		return begin;
	}

	const_iterator upper_bound (const key_type& k) const{
		const_iterator begin = this->begin();
		const_iterator end = this->end();
		for (; begin != end; begin++){
			if ((this->key_comp()(k, begin->first)))
				break;
		}
		return begin;
	}

	iterator lower_bound( const Key& k ){
		iterator begin = this->begin();
		iterator end = this->end();
		for (; begin != end; begin++){
			if (!(this->key_comp()(begin->first, k)))
				break;
		}
		return begin;
	}

	const_iterator lower_bound( const Key& k ) const{
		const_iterator begin = this->begin();
		const_iterator end = this->end();
		for (; begin != end; begin++){
			if (!(this->key_comp()(begin->first, k)))
				break;
		}
		return begin;
	}

	pair<iterator,iterator> equal_range (const key_type& k){
		return ft::make_pair(lower_bound(k), upper_bound(k));
	}



	protected:
		// ft::Node<Key, T>								*_node;
		ft::RedBlackTree<Key, T>						tree;
		allocator_type									_alloc;//gerenciador de memoria


};

}