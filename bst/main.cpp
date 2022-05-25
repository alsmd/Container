#include <iostream>
#include <sstream>


//Todos a esquerda são menores que o node atual
//Todos a direita são maiores que o node atual

template<typename T>
struct Node{
	T		value;

	struct Node *parent;
	struct Node *left;
	struct Node *right;
};

template<typename T>
class BinarySearchTree{

	public:
		typedef T value_type;
		//Members
		Node<T> *root;



		//Functions
		BinarySearchTree(){
			this->root = NULL;
		}

		~BinarySearchTree(){

		}


		
		void addElement(value_type new_value){
			Node<value_type> *new_node = new Node;
			Node<value_type> *root;
			new_node->value = new_value;
			if (this->root == NULL){
				this->root = new_node;
				return ;
			}else
				root = this->root;
			while (true){
				if (new_value < root->value){//LEFT
					if (root->left == NULL){
						new_node->parent = root;
						root->left = new_node;
						break;
					}else
						root = root->left;
				}else if (new_value > root->value)//RIGHT
				{
					if (root->right == NULL){
						new_node->parent = root;
						root->right = new_node;
						break ;
					}else
						root = root->right;
				}else
					break ;
			}
		}
	

		/***
		 * 
		 * @brief Returns Higher node from binary tree
		 * 
		*/
		Node *getHigherNode(Node<value_type> *node = NULL){
			if (node == NULL)
				node = this->root;
			while (node && node->right){
				node = node->right;
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
		void	swapNode(Node<value_type> *node, Node<value_type> *sub){
			if (sub){
				sub->parent = node->parent;
				sub->left = node->left;
				sub->right = node->right;
				if (node->right)
					node->right->parent = sub;
				if (node->left)
					node->left->parent = sub;
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
		 * @brief Delete node completely and rearrange the binary tree if necessary
		 * 
		*/
		void	deleteNode(Node<value_type> *node){
			if (node->left == NULL && node->right == NULL)// 1º não tem filho nenhum
				this->swapNode(node, NULL);
			else if (node->left && node->right){ // 2º tem 2 filhos
				Node *higher_node = this->getHigherNode(node->left);//maior node da esquerda
				this->swapNode(higher_node, higher_node->left);//ira remover esse node e reconectar a lista
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
		void	removeByValue(value_type value){
			Node<value_type> *node = this->root;
			while (node){
				if (node->value == value){//found
					this->deleteNode(node);
					break ;
				}else if (value < node->value)
					node = node->left;
				else
					node = node->right;
			}
		}


	private:

};



int main(){
	BinarySearchTree	tree;
	std::string	buffer;
	int	value;

	while (1){
		std::cout << "> ";
		std::cin >> buffer;
		if (buffer == "add"){
			std::cout << "new node: ";
			std::cin >> value;
			tree.addElement(value);
		}else if (buffer == "search"){
			Node *begin = tree.root;
			if (begin == NULL){
				std::cout << "is empty!" << std::endl;
				continue ;
			}
			while (true){
				std::cout << begin->value << std::endl;
				std::cout << "search: ";
				std::cin >> buffer;
				if (buffer == "exit")
					break ;
				else if (buffer == "a" && begin->left)
					begin = begin->left;
				else if (buffer == "d" && begin->right)
					begin = begin->right;
				else if (buffer == "w" && begin->parent)
					begin = begin->parent;
			}
		}else if (buffer == "del"){
			std::cout << "delete node: ";
			std::cin >> value;
			tree.removeByValue(value);
		}
	}

	return 0;
}