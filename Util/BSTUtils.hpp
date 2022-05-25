#pragma once

#include "../Util/BSTAlgorithm.hpp"

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
		}
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

}