#pragma once
#include "./utility.hpp"
#include "./functional.hpp"
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

template< typename Key, typename T, typename Allocator = std::allocator<ft::pair<const Key, T> >, typename Compare = ft::less<Key> >
class BinarySearchTree{

	protected:
		std::allocator<ft::pair<const Key, T> >* _alloc;
		Compare _comp;
	public:
		size_t	size;
		typedef ft::pair<const Key, T> value_type;
		//Members
		Node<Key, T> *root;



		//Functions
		BinarySearchTree(std::allocator<ft::pair<const Key, T> >* alloc) : _alloc(alloc){
			this->root = NULL;
			this->size = 0;
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
				this->size += 1;
				*root = node;
				return node;
			}else
				init = *root;
			while (true){
				if (node->value->first == init->value->first)
					return init;
				else if (_comp(node->value->first, init->value->first)){//LEFT
					if (init->left == NULL){
						node->parent = init;
						init->left = node;
						this->size += 1;
						break;
					}else
						init = init->left;
				}else if (!_comp(node->value->first, init->value->first))//RIGHT
				{
					if (init->right == NULL){
						node->parent = init;
						init->right = node;
						this->size += 1;
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


		void	connectFamily(Node<Key, T> *from, Node<Key, T> *to){
			Node<Key, T> *fromParent = from->parent;
			Node<Key, T> *fromLeft = from->left;
			Node<Key, T> *fromRight = from->right;
			if (fromParent){
				if (this->getDirection(from) == Direction::Left)
					fromParent->left = to;
				else
					fromParent->right = to;
			}else
				this->root = to;
			if (fromLeft)
				fromLeft->parent = to;
			if (fromRight)
				fromRight->parent = to;
		}

		void	swapPointers(Node<Key, T> *node1, Node<Key, T> *node2){
			Node<Key, T> *parentHolder = node1->parent;
			Node<Key, T> *leftHolder = node1->left;
			Node<Key, T> *rightHolder = node1->right;
			this->swap(node1->color, node2->color);
			node1->parent = node2->parent == node1 ? NULL : node2->parent;
			node1->left = node2->left == node1 ? NULL : node2->left;
			node1->right = node2->right == node1 ? NULL : node2->right;
			node2->parent = parentHolder == node2 ? NULL : parentHolder;
			node2->left = leftHolder == node2 ? NULL : leftHolder;
			node2->right = rightHolder == node2 ? NULL : rightHolder;
		}

		

		/***
		 * 
		 * @brief Cut this node and conects its parent to the node sub
		 * @param node Node that will be cut
		 * @param sub Node that will substitute the node that was cut
		 * 
		*/
		void	swapNode(Node<Key, T> *node, Node<Key, T> *sub){
			this->connectFamily(node, sub);
			this->connectFamily(sub, node);
			this->swapPointers(node, sub);
		}

		template <typename J>
		void swap(J &n1, J &n2){
			J holder = n1;
			n1 = n2;
			n2 = holder;
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
			this->size -= 1;
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
		size_t i = this->size;
		if (BinarySearchTree<Key, T>::getDirection(node) == Direction::Right)
			this->leftRotation(node);
		else
			this->rightRotation(node);
		this->size = i;
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
		// if DB's sibling is black, and both its children are black
		if (isBlack(sibling) && isBlack(sibling->left) && isBlack(sibling->right)){
			sibling->color = Color::Red;
			if (node->parent->color == Color::Red){
				node->parent->color = Color::Black;
			}
			else
				repassBlack(node->parent);
		}
		//Caso 4
		// Db's sibling is red
		else if (isRed(sibling)){
			ft::Color holder = sibling->color;
			sibling->color = node->parent->color;
			sibling->parent->color = holder;
			rotate(sibling);
			repassBlack(node);
		}

		//Caso 5
		//Db's sibling is black, sibling's child who is far from db is black, but near child to Db is red
		else if (isBlack(sibling) && isBlack(getChild(sibling, opositeDirection(BinarySearchTree<Key, T>::getDirection(node)))) && isRed(getChild(sibling, BinarySearchTree<Key, T>::getDirection(node)))){
			getChild(sibling, BinarySearchTree<Key, T>::getDirection(node))->color = Color::Black;
			sibling->color = Color::Red;
			rotate(getChild(sibling, BinarySearchTree<Key, T>::getDirection(node)));
			repassBlack(node);
		}
		// 6 esta certo
		// Caso 6
		//Db's sibling is black and far child is red
		else if (isBlack(sibling) && isRed(getChild(sibling, opositeDirection(BinarySearchTree<Key, T>::getDirection(node))))){
			sibling->color = node->parent->color;
			node->parent->color = Color::Black;
			getChild(sibling, opositeDirection(BinarySearchTree<Key, T>::getDirection(node)))->color = Color::Black;
			rotate(sibling);
		}
	}

	/***
	 * 
	 * @brief Delete node completely and rearrange the binary tree if necessary
	 * 
	*/
	void	deleteNode(Node<Key, T> *node){
		if (node->left == NULL && node->right == NULL){
			if (node->color == Color::Black)
				this->repassBlack(node);
			if (node->parent){
				if (this->getDirection(node) == Direction::Left)
					node->parent->left = NULL;
				else
					node->parent->right = NULL;
			}
			this->_alloc->destroy(node->value);
			this->_alloc->deallocate(node->value, 1);
			delete node;
			this->size -= 1;
		}
		else if (node->left && node->right){ // 2º tem 2 filhos
			Node<Key, T> *higher_node = this->getHigherNode(node->left);//maior node da esquerda
			this->swapNode(node, higher_node);
			this->deleteNode(node);
		}else if (node->left || node->right){// tem um filho
			if (node->left)
				this->swapNode(node, node->left);
			else
				this->swapNode(node, node->right);
			this->deleteNode(node);
		}
	}
};


}