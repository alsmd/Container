#pragma once
#include "../Util/functional.hpp"
#include "../Util/utility.hpp"
#include <memory>

namespace ft{


	enum Color{
		Black = 0,
		Red = 1
	};

	enum Direction{
		Left,
		Right,
		Parent,
		None
	};

	template< typename Key, typename T, typename Compare = ft::less<Key>, typename Allocator = std::allocator<ft::pair<const Key, T> > >
	class BSTNode{
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

			pointer				data;
			int					color;
			int					size;
			BSTNode<Key, T>		*right;
			BSTNode<Key, T>		*left;
			BSTNode<Key, T>		*parent;

			BSTNode(std::allocator<ft::pair<const Key, T> >* alloc) : _alloc(alloc) {
				this->left = NULL;
				this->right = NULL;
				this->parent = NULL;
				this->data = NULL;
				this->size = 0;
				this->color = Color::Black;
			}

			BSTNode(const Key key,std::allocator<ft::pair<const Key, T> > *alloc) : _alloc(alloc){
				this->left = NULL;
				this->right = NULL;
				this->parent = NULL;
				this->data = this->_alloc->allocate(1);
				this->size = 1;
				this->_alloc->construct(this->data, ft::pair<const Key, T>(key, T()));
				this->color = Color::Black;
			}

			BSTNode(const value_type &value,std::allocator<ft::pair<const Key, T> > *alloc) : _alloc(alloc){
				this->left = NULL;
				this->right = NULL;
				this->parent = NULL;
				this->data = this->_alloc->allocate(1);
				this->size = 1;
				this->_alloc->construct(this->data, value);
				this->color = Color::Black;
			}


			~BSTNode(){
				if (this->data){
					this->_alloc->destroy(this->data);
					this->_alloc->deallocate(this->data, 1);
				}
			}

			/***
			 * 
			 * @brief Searches and put node in a valid slot if node doesn't exists
			 * 
			*/
			BSTNode<Key, T>	*findSlot(BSTNode<Key, T> *node){
				BSTNode<Key, T>	*init = this;
				while (true){
					//Check if node is on wrong side of the tree
					if (init->getDirection() == ft::Direction::Right){
						if (node->data->first < init->parent->data->first){
							init = init->parent;
							continue;
						}else if (node->data->first == init->parent->data->first)
							return init->parent;
					}else if (init->getDirection() == ft::Direction::Left) {
						if (node->data->first > init->parent->data->first){
							init = init->parent;
							continue;
						}else if (node->data->first == init->parent->data->first)
							return init->parent;
					}

					if (node->data->first < init->data->first){
						if (init->left == NULL){
							node->parent = init;
							init->left = node;
							break;
						}else
							init = init->left;
					}else if (node->data->first > init->data->first)
					{
						if (init->right == NULL){
							node->parent = init;
							init->right = node;
							break ;
						}else
							init = init->right;
					}else
						return init;
				}
				this->size += 1;
				return node;
			}

			/***
			 * 
			 * @brief Search and returns node that has value.
			 * @return Returns that node of value or NULL if no found
			 * 
			*/
			BSTNode<Key, T> *find(const Key key){
				BSTNode<Key, T> *node = this;
				while (node){
					if (node->data->first == key){//found
						return (node);
					}else if (key < node->data->first)
						node = node->left;
					else
						node = node->right;
				}
				return NULL;
			}


			Direction getDirection(){
				if (this->parent == NULL)
					return Direction::None;
				if (this->parent->right == this)
					return Direction::Right;
				return Direction::Left;
			}
			std::allocator<ft::pair<const Key, T> >	*_alloc;

	};

	
}