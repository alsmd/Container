#pragma once
#include "./utility.hpp"
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


template< typename Key, typename T>
struct Node{
	ft::pair<const Key, T>	*value;
	Node<Key, T>					*parent;
	Node<Key, T>					*left;
	Color					color;
	Node<Key, T>					*right;
};

template< typename Key, typename T, typename Allocator = std::allocator<ft::pair<const Key, T> > >
class BinarySearchTree{

	protected:
		std::allocator<ft::pair<const Key, T> >* _alloc;
	public:
		size_t	size;
		typedef ft::pair<const Key, T> value_type;
		//Members
		Node<Key, T> *root;



		//Functions
		BinarySearchTree(std::allocator<ft::pair<const Key, T> >* alloc) : _alloc(alloc){
			this->root = NULL;
		}

		~BinarySearchTree(){

		}
		/***
		 * 
		 * @brief Returns a new default node
		 * 
		*/
		Node<Key, T>	*newNode(Key key){
			Node<Key, T> *new_node = new Node<Key, T>;
			new_node->left = NULL;
			new_node->right = NULL;
			new_node->parent = NULL;
			new_node->value = this->_alloc->allocate(1);
			this->_alloc->construct(new_node->value, ft::pair<const Key, T>(key, T()));
			new_node->color = Color::Black;
			return (new_node);
		}

		Node<Key, T>	*newNode(value_type value){
			Node<Key, T> *new_node = new Node<Key, T>;
			new_node->left = NULL;
			new_node->right = NULL;
			new_node->parent = NULL;
			new_node->value = this->_alloc->allocate(1);
			this->_alloc->construct(new_node->value, value);
			new_node->color = Color::Black;
			return (new_node);
		}


		/***
		 * 
		 * @brief	Returns Direction::Left node is the left node of its parent, 
		 * 			or returns Direction::Right if node is the right node of its parent
		 * 
		*/
		static Direction getDirection(Node<Key, T> *node){
			if (node->parent->right == node)
				return Direction::Right;
			return Direction::Left;
		}

		/***
		 * 
		 * @brief Searches and put node in a valid slot if node doesn't exists
		 * 
		*/
		Node<Key, T>	*findSlot(Node<Key, T> *node, Node<Key, T> **root = NULL){
			Node<Key, T>	*init;
			if (root == NULL)
				root = &this->root;
			if (*root == NULL){
				*root = node;
				return node;
			}else
				init = *root;
			while (true){
				if (node->value->first == init->value->first)
					return init;
				if (node->value->first < init->value->first){//LEFT
					if (init->left == NULL){
						node->parent = init;
						init->left = node;
						break;
					}else
						init = init->left;
				}else if (node->value->first > init->value->first)//RIGHT
				{
					if (init->right == NULL){
						node->parent = init;
						init->right = node;
						break ;
					}else
						init = init->right;
				}
			}
			return node;
		}

		virtual T &insert(Key key){
			Node<Key, T> *node = this->newNode(key);
			Node<Key, T> *found;
			found = this->findSlot(node);
			if (!node->parent && node != this->root)//alredy exists
				delete node;
			return found->value->second;
		}
	

		/***
		 * 
		 * @brief Returns Higher node from binary tree
		 * 
		*/
		static Node<Key, T> *getHigherNode(Node<Key, T> *node){
			while (node && node->right){
				node = node->right;
			}
			return node;
		}

		static Node<Key, T> *getLowerNode(Node<Key, T> *node){
			while (node && node->left){
				node = node->left;
			}
			return node;
		}



		/***
		 * 
		 * @brief Cut this node and conects its parent to the node sub
		 * @param node Node that will be cut
		 * @param sub Node that will substitute the node that was cut
		 * 
		*/
		void	swapNode(Node<Key, T> *node, Node<Key, T> *sub){
			if (!node)
				return ;
			if (sub){
				sub->color = node->color;
				sub->parent = node->parent;
				if (node->left != sub && node->left){
					sub->left = node->left;
					node->left->parent = sub;
				}
				if (node->right != sub && node->right){
					sub->right = node->right;
					node->right->parent = sub;
				}
			}
			if (node->parent){
				if (node->parent->left == node){
					node->parent->left = sub;
				}else if (node->parent->right == node){
					node->parent->right = sub;
				}
			}else
				this->root = sub;
		}
		/***
		 * 
		 * @brief Search and returns node that has value.
		 * @return Returns that node of value or NULL if no found
		 * 
		*/
		Node<Key, T> *find(Key key, Node<Key, T> *root = NULL){
			if (root == NULL)
				root = this->root;
			Node<Key, T> *node = this->root;
			while (node){
				if (node->value->first == key){//found
					return (node);
				}else if (key < node->value->first)
					node = node->left;
				else
					node = node->right;
			}
			return NULL;
		}

		/***
		 * 
		 * @brief Delete node completely and rearrange the binary tree if necessary
		 * 
		*/
		virtual void	deleteNode(Node<Key, T> *node){
			if (node->left == NULL && node->right == NULL)// 1º não tem filho nenhum
				this->swapNode(node, NULL);
			else if (node->left && node->right){ // 2º tem 2 filhos
				Node<Key, T> *higher_node = this->getHigherNode(node->left);//maior node da esquerda
				this->swapNode(higher_node, higher_node->left);//ira remover esse node e reconectar a lista
				higher_node->left = NULL;
				higher_node->right = NULL;
				this->swapNode(node, higher_node);
			}else if (node->left || node->right){// tem um filho
				if (node->left) // essse filho é o left
					this->swapNode(node, node->left);
				else// esse filho é o right
					this->swapNode(node, node->right);
			}
			delete node;
		}


		/***
		 * 
		 * @brief Remove Node by value
		 * 
		*/
		virtual bool	remove(Key key){
			Node<Key, T> *node = this->find(key);
			if (node){
				this->deleteNode(node);
				return true;
			}
			return false;
		}


	private:

};

template< typename Key, typename T, typename Allocator = std::allocator<ft::pair<const Key, T> > >
class RedBlackTree : public BinarySearchTree<Key, T>{
	public:
	typedef ft::pair<const Key, T> value_type;



	RedBlackTree(std::allocator<ft::pair<const Key, T> >* alloc = new Allocator()) : BinarySearchTree<Key, T>(alloc) {}
	
	~RedBlackTree() {}

	/***
	 * 
	 * @brief	returns the color of the node that is on the same level of node's parents
	 *			If node doesn't have a parent or the parent doesn't have a parent or the parent doesn't have a sibling,
	 			color Black is returned
	 *  
	*/
	Color getParentSiblingColor(Node<Key, T> *node){
		if (!node->parent)
			return (Color::Black);
		if (!node->parent->parent)
			return (Color::Black);
		Node<Key, T> *sibling;
		if (node->parent->parent->left != node->parent)
			sibling = node->parent->parent->left;
		else
			sibling = node->parent->parent->right;
		if (sibling)
			return (sibling->color);
		return (Color::Black);
	}

	/***
	 * 
	 * @brief Returns the node's sibling or NULL if not exists
	 * 
	*/
	Node<Key, T> *getSibling(Node<Key, T> *node){
		if (!node->parent)
			return NULL;
		if (node->parent->left != node)
			return node->parent->left;
		return node->parent->right;
	}


	

	/***
	 * 
	 * @brief	Rotate node in left orientation.
	 * 			The node's parent's parent is gonna be node's parent, and
	 * 			old node's parent is gonna be the node's left child.
	 * 
	*/
	void leftRotation(Node<Key, T> *node){
		Node<Key, T> *old_parent = node->parent;
		old_parent->right = NULL;
		node->parent = old_parent->parent;
		if (old_parent->parent && BinarySearchTree<Key, T>::getDirection(old_parent) == Direction::Left)
			node->parent->left = node;
		else if (old_parent->parent)
			node->parent->right = node;
		old_parent->parent = node;
		Node<Key, T> *sub_tree;
		sub_tree = node->left;
		node->left = old_parent;
		this->mergeTrees(sub_tree, &node->left);
		if (old_parent == this->root)
			this->root = node;
	}
	/***
	 * 
	 * @brief	Rotate node in right orientation.
	 * 			The node's parent's parent is gonna be node's parent, and
	 * 			old node's parent is gonna be the node's right child.
	 * 
	*/
	void rightRotation(Node<Key, T> *node){
		Node<Key, T> *old_parent = node->parent;
		old_parent->left = NULL;
		node->parent = old_parent->parent;
		if (old_parent->parent && BinarySearchTree<Key, T>::getDirection(old_parent) == Direction::Left)
			node->parent->left = node;
		else if (old_parent->parent)
			node->parent->right = node;
		old_parent->parent = node;
		Node<Key, T> *sub_tree;
		sub_tree = node->right;
		node->right = old_parent;
		this->mergeTrees(sub_tree, &node->right);
		if (old_parent == this->root)
			this->root = node;
		
	}
	
	void rotate(Node<Key, T> *node){
		if (BinarySearchTree<Key, T>::getDirection(node) == Direction::Right)
			this->leftRotation(node);
		else
			this->rightRotation(node);
	}

	void reddish(Node<Key, T> *node){
		node->color = Color::Red;
		if (node->parent->color == Color::Black)
			return;
		else if (node->parent->color == Color::Red){
			Color parentSiblingColor = this->getParentSiblingColor(node);
			if (parentSiblingColor == Color::Black){
				//rotation
				if (BinarySearchTree<Key, T>::getDirection(node) == BinarySearchTree<Key, T>::getDirection(node->parent))
				{
					this->rotate(node->parent);
					node->parent->color = Color::Black;
					node->color = Color::Red;
					this->getSibling(node)->color = Color::Red;
				}
				else{
					this->rotate(node);
					this->rotate(node);
					node->color = Color::Black;
					if (node->left)
						node->left->color = Color::Red;
					if (node->right)
						node->right->color = Color::Red;
				}				
				
			}else{
				node->parent->color = Color::Black;
				this->getSibling(node->parent)->color = Color::Black;
				if (node->parent->parent != this->root){
					this->reddish(node->parent->parent);
				}
			}
		}	
	}

	T &insert(const Key key){
		Node<Key, T> *node = this->newNode(key);
		Node<Key, T> *found;
		found = this->findSlot(node);
		if (found->value->first != node->value->first){
			delete node;
			return found->value->second;
		}
		if (!node->parent && node != this->root){//alredy exists
			delete node;
			return found->value->second;
		}else if (node == this->root)//is the root
			return found->value->second;
		this->reddish(node);
		return found->value->second;
	}

	bool insert(value_type &value){
		Node<Key, T> *node = this->newNode(value);
		Node<Key, T> *found;
		found = this->findSlot(node);
		if (found->value->first != node->value->first){
			delete node;
			return false;
		}
		if (!node->parent && node != this->root){//alredy exists
			delete node;
			return false;
		}else if (node == this->root)//is the root
			return true;
		this->reddish(node);
		return true;
	}

	void mergeTrees(Node<Key, T> *node, Node<Key, T> **root){
		if (!node)
			return ;
		this->findSlot(node, root);
		this->mergeTrees(node->left, root);
		this->mergeTrees(node->right, root);
	}

	bool isBlack(Node<Key, T> *node){
		if (!node)
			return true;
		if (node->color == Color::Black)
			return true;
		return false;
	}

	bool isRed(Node<Key, T> *node){
		if (node && node->color == Color::Red)
			return true;
		return false;
	}

	Direction	opositeDirection(Direction dir){
		return dir == Direction::Left ? Direction::Right : Direction::Left;
	}

	Node<Key, T> *getChild(Node<Key, T> *node, Direction dir){
		if (dir == Direction::Left)
			return node->left;
		return node->right;
	}

	void repassBlack(Node<Key, T> *node){
		//Caso 2
		if (node == this->root)
			return ;

		Node<Key, T> *sibling = getSibling(node);
		
		//Caso 3
		if (isBlack(sibling) && isBlack(sibling->left) && isBlack(sibling->right)){
			sibling->color = Color::Red;
			if (node->parent->color == Color::Red){
				node->parent->color == Color::Black;
			}
			else
				repassBlack(node->parent);
		}
		//Caso 4
		else if (isRed(sibling)){
			sibling->color = node->parent->color;
			sibling->parent->color = Color::Red;
			rotate(sibling);
			repassBlack(node);
		}

		//Caso 5
		else if (isBlack(sibling) && isBlack(getChild(sibling, opositeDirection(BinarySearchTree<Key, T>::getDirection(node)))) && isRed(getChild(sibling, BinarySearchTree<Key, T>::getDirection(node)))){
			getChild(sibling, BinarySearchTree<Key, T>::getDirection(node))->color = Color::Black;
			sibling->color = Color::Red;
			rotate(getChild(sibling, BinarySearchTree<Key, T>::getDirection(node)));
			repassBlack(node);
		}
		// Caso 6
		else if (isBlack(sibling) && isRed(getChild(sibling, opositeDirection(BinarySearchTree<Key, T>::getDirection(node))))){
			sibling->color = node->parent->color;
			node->parent->color = Color::Black;
			getChild(sibling, opositeDirection(BinarySearchTree<Key, T>::getDirection(node)))->color = Color::Black;
			rotate(sibling);
		}
		/* else  if (isBlack(sibling)){
			if (getChild(sibling, opositeDirection(getDirection(node)))->color == Color::Black && getChild(sibling, getDirection(node))->color == Color::Red){
				getChild(sibling, getDirection(node))->color = Color::Black;
				sibling->color = Color::Red;
				rotate(getChild(sibling, getDirection(node)));
				repassBlack(node);
			}
		} else if (isBlack(sibling)){
			if (getChild(sibling, getDirection(node))->color == Color::Black && getChild(sibling, opositeDirection(getDirection(node)))->color == Color::Red){
				Color holder = node->parent->color;
				node->parent->color = sibling->color;
				sibling->color = holder;
				getChild(sibling, opositeDirection(getDirection(node)))->color = Color::Black;
				rotate(sibling);
			}
		}else if (isRed(sibling)){
			sibling->color = Color::Black;
			sibling->parent->color = Color::Red;
			rotate(sibling);
			repassBlack(node);
		} */
	}

	/***
	 * 
	 * @brief Delete node completely and rearrange the binary tree if necessary
	 * 
	*/
	void	deleteNode(Node<Key, T> *node){
		if (node->left == NULL && node->right == NULL){
			if (node->color == Color::Black){
				this->repassBlack(node);
			}
			this->swapNode(node, NULL);
			delete node;
		}
		else if (node->left && node->right){
			Node<Key, T> *higher_node = this->getHigherNode(node->left);
			node->value = higher_node->value;
			deleteNode(higher_node);

		}else if (node->left || node->right){// tem um filho
			if (node->left){
				node->value = node->left->value;
				deleteNode(node->left);
			}
			else{
				node->value = node->right->value;
				deleteNode(node->right);
			}
		}
	}
};


}