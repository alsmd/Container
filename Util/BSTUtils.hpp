#pragma once

// #include "../Util/BSTAlgorithm.hpp"

namespace ft{
	template<typename Key, typename T>
	void	deleteNode(BSTNode<Key, T> *node, BSTNode<Key, T> **root){
		if (node->left == NULL && node->right == NULL)// 1º não tem filho nenhum
			swapNode(node, static_cast<BSTNode<Key, T> *>(NULL) , root);
		else if (node->left && node->right){ // 2º tem 2 filhos
			BSTNode<Key, T> *higher_node = getHigherNode(node->left);//maior node da esquerda
			swapNode(higher_node, higher_node->left, root);//ira remover esse node e reconectar a lista
			higher_node->left = NULL;
			higher_node->right = NULL;
			swapNode(node, higher_node, root);
		}else if (node->left || node->right){// tem um filho
			if (node->left) // essse filho é o left
				swapNode(node, node->left, root);
			else// esse filho é o right
				swapNode(node, node->right, root);
		}
		delete node;
	}

	template<typename Key, typename T>
	bool	removeNode(Key key, BSTNode<Key, T> **root){
		BSTNode<Key, T> *node = *root;
		if (node == NULL)
			return false;
		node = node->find(key);
		if (node){
			ft::deleteNode(node, root);
			if (*root)
				(*root)->size -= 1;
			return true;
		}
		return false;
	}


	template<typename Key, typename T>
	int checkHeight(BSTNode<Key, T> *node){
		int size = 0;

		while (node){
			BSTNode<Key, T> *sibling = node->getSibling();
			if (node->left){
				node = node->left;
			}else if (node->right){
				node = node->right;
			}else if (sibling && sibling->left){
				node = sibling->left;
			}else if (sibling && sibling->right){
				node = sibling->right;
			}else{
				node = NULL;
			}
			size++;
		}
		return size;
	}
	template<typename Key, typename T>
	void checkBalance(BSTNode<Key, T> *node, BSTNode<Key, T> *new_node, BSTNode<Key, T> **root){
		if (!node)
			return ;
		int difference = checkHeight(node->left) - checkHeight(node->right);
		if (difference < -1){
			//direita
			// if (checkHeight(node->right->right) > checkHeight(node->right->left)){
			if (new_node->getDirection() == Direction::Right){
				rotate(node->right, root);
				return;
			}else{
				rotate(new_node, root);
				rotate(node->right, root);
				return ;
			}
		}
		if (difference > 1){
			//esquerda
			// if (checkHeight(node->left->left) > checkHeight(node->left->right)){
			if (new_node->getDirection() == Direction::Left){
				rotate(node->left, root);
				return ;
			}else{
				rotate(new_node, root);
				rotate(node->right, root);
				return ;
			}
		}
		checkBalance(node->parent, new_node, root);
	}
	template<typename Key, typename T, typename value_type = ft::pair<const Key, T> >
	bool insertNode(const value_type &value, BSTNode<Key, T> **root, std::allocator<ft::pair<const Key, T> >* alloc){
		BSTNode<Key, T> *node = new BSTNode<Key, T>(value, alloc);
		if (*root == NULL){
			*root = node;
			return true;
		}
		BSTNode<Key, T> *found;
		found = (*root)->findSlot(node);
		if (!node->parent && found != node){
			delete node;
			return false;
		}
		checkBalance(node, node, root);
		return true;
	}
	template<typename Key, typename T>
	T &insertNode(const Key key, BSTNode<Key, T> **root, std::allocator<ft::pair<const Key, T> >* alloc){
		BSTNode<Key, T> *node = new BSTNode<Key, T>(key, alloc);
		if (*root == NULL){
			*root = node;
			return node->data->second;
		}
		BSTNode<Key, T> *found;
		found = (*root)->findSlot(node);
		if (!node->parent && found != node){
			delete node;
		}else
			checkBalance(node, node, root);
		return found->data->second;
	}

	/***
	 * 
	 * @brief Cut this node and conects its parent to the node sub
	 * @param node Node that will be cut
	 * @param sub Node that will substitute the node that was cut
	 * 
	*/
	template<typename Key, typename T>
	void	swapNode(BSTNode<Key, T> *node, BSTNode<Key, T> *sub, BSTNode<Key, T> **root){
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
		}else{
			*root = sub;
		}
	}

	/***
	 * 
	 * @brief Returns Higher node from binary tree
	 * 
	*/
	template<typename Key, typename T>
	BSTNode<Key, T> *getHigherNode(BSTNode<Key, T> *node){
		while (node && node->right){
			node = node->right;
		}
		return node;
	}

	/***
	 * 
	 * @brief Returns Lower node from binary tree
	 * 
	*/
	template<typename Key, typename T>
	BSTNode<Key, T> *getLowerNode(BSTNode<Key, T> *node){
		while (node && node->left){
			node = node->left;
		}
		return node;
	}



	/***
	 * 
	 * @brief	Rotate node in left orientation.
	 * 			The node's parent's parent is gonna be node's parent, and
	 * 			old node's parent is gonna be the node's left child.
	 * 
	*/
	template<typename Key, typename T>
	void leftRotation(BSTNode<Key, T> *node, BSTNode<Key, T> **root){
		BSTNode<Key, T> *old_parent = node->parent;
		old_parent->right = NULL;
		node->parent = old_parent->parent;
		if (old_parent->parent && old_parent->getDirection() == Direction::Left)
			node->parent->left = node;
		else if (old_parent->parent)
			node->parent->right = node;
		old_parent->parent = node;
		BSTNode<Key, T> *sub_tree;
		sub_tree = node->left;
		node->left = old_parent;
		mergeTrees(sub_tree, &node->left);
		if (old_parent == *root)
			*root = node;
	}
	/***
	 * 
	 * @brief	Rotate node in right orientation.
	 * 			The node's parent's parent is gonna be node's parent, and
	 * 			old node's parent is gonna be the node's right child.
	 * 
	*/
	template<typename Key, typename T>
	void rightRotation(BSTNode<Key, T> *node, BSTNode<Key, T> **root){
		BSTNode<Key, T> *old_parent = node->parent;
		old_parent->left = NULL;
		node->parent = old_parent->parent;
		if (old_parent->parent && old_parent->getDirection() == Direction::Left)
			node->parent->left = node;
		else if (old_parent->parent)
			node->parent->right = node;
		old_parent->parent = node;
		BSTNode<Key, T> *sub_tree;
		sub_tree = node->right;
		node->right = old_parent;
		mergeTrees(sub_tree, &node->right);
		if (old_parent == *root)
			*root = node;
		
	}
	template<typename Key, typename T>
	void rotate(BSTNode<Key, T> *node, BSTNode<Key, T> **root){
		if (node->getDirection() == Direction::Right)
			ft::leftRotation(node, root);
		else
			ft::rightRotation(node, root);
	}
	template<typename Key, typename T>
	void mergeTrees(BSTNode<Key, T> *node, BSTNode<Key, T> **root){
		if (!node)
			return ;
		(*root)->findSlot(node);
		mergeTrees(node->left, root);
		mergeTrees(node->right, root);
	}

}