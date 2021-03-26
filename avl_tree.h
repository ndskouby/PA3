#include<stdexcept>
#include<sstream>
#include<cstddef>
#include<iostream>
#ifndef AVL_TREE_H
#define AVL_TREE_H

template <typename Comparable>
struct AVLNode{
	AVLNode(Comparable);
	AVLNode(const AVLNode&);
	~AVLNode();
	AVLNode& operator=(const AVLNode&);
	bool _contains(const Comparable&);
	void _insert(const Comparable&);
	void _remove(const Comparable&);
	const Comparable& _find_min() const;
	const Comparable& _find_max() const;
	void _print_helper(std::ostream& out, std::size_t spaces) const;
	void single_left();
	void single_right();
	void double_left();
	void double_right();
	void rebalance();
	int max(int, int);
	//member variables
	AVLNode<Comparable>* left;
	AVLNode<Comparable>* right;
	Comparable data;
	int left_height;
	int right_height;
};

template <typename Comparable>
AVLNode<Comparable>::AVLNode(Comparable value) : left{nullptr}, right{nullptr}, data{value}, left_height{-1}, right_height{-1} {}

template <typename Comparable>
AVLNode<Comparable>::AVLNode(const AVLNode& orig) : left{nullptr}, right{nullptr}, data{orig.data}, left_height{orig.left_height}, right_height{orig.right_height} {
	if (orig.left != nullptr){
		left = new AVLNode<Comparable>(*orig.left);
	}
	if (orig.right != nullptr){
		right = new AVLNode<Comparable>(*orig.right);
	}	
}

template <typename Comparable>
AVLNode<Comparable>::~AVLNode(){
	if (left != nullptr){
		delete left;
	}
	if (right != nullptr){
		delete right;
	}
}

template <typename Comparable>
AVLNode<Comparable>& AVLNode<Comparable>::operator=(const AVLNode<Comparable>& orig){
	if (this != &orig){
		if (left != nullptr){
			delete left;
		}
		if (right != nullptr){
			delete right;
		}
		data = orig.data;
		left_height = orig.left_height;
		right_height = orig.right_height;
		if (orig.left != nullptr){
			left = new AVLNode<Comparable>(*orig.left);
		}
		if (orig.right != nullptr){
			right = new AVLNode<Comparable>(*orig.right);
		}
	}
	return *this;
		
}

template <typename Comparable>
bool AVLNode<Comparable>::_contains(const Comparable& value){
	if (data == value){
		return true;
	} else if (value < data){
		if (left == nullptr){
			return false;
		}
		return left->_contains(value);
	} else if (value > data){
		if (right == nullptr){
			return false;
		}
		return right->_contains(value);
	}
	return false;
}

template <typename Comparable>
void AVLNode<Comparable>::_insert(const Comparable& value){
	if (value > data){
		if (right == nullptr){
			right = new AVLNode<Comparable>(value);
			right_height = 0;
		} else {
			right->_insert(value);
			right_height = max(right->left_height, right->right_height) + 1;
		}
	} else if (value < data){
		if (left == nullptr){
			left = new AVLNode<Comparable>(value);
			left_height = 0;
		} else {
			left->_insert(value);
			left_height = max(left->left_height, left->right_height) + 1;
		}
	} else {
		//duplicate
	}
	rebalance();
}

template <typename Comparable>
void AVLNode<Comparable>::_remove(const Comparable& value){
	if (left != nullptr && left->data == value){
		AVLNode<Comparable>* temp;
		if (left->right == nullptr && left->left == nullptr){
			delete left;
			left = nullptr;
			left_height = -1;
		} else if (left->right == nullptr){
			temp = left;
			left = temp->left;
			temp->left = nullptr;
			delete temp;
			--left_height;
		} else if (left->left == nullptr){
			temp = left;
			left = temp->right;
			temp->right = nullptr;
			delete temp;
			--left_height;
		} else {
			Comparable min = left->right->_find_min();
			if (left->right->left == nullptr){
				temp = left;
				left = temp->right;
				left->left = temp->left;
				left->left_height = temp->left_height;
				temp->right = nullptr;
				temp->left = nullptr;
				delete temp;
			} else {
				left->right->_remove(min);
				left->data = min;
			}
			left_height = max(left->left_height, left->right_height) + 1;
		}
	} else if (right != nullptr && right->data == value){
		AVLNode<Comparable>* temp;
		if (right->right == nullptr && right->left == nullptr){
			delete right;
			right = nullptr;
			right_height = -1;
		} else if (right->right == nullptr){
			temp = right;
			right = temp->left;
			temp->left = nullptr;
			delete temp;
			--right_height;
		} else if (right->left == nullptr){
			temp = right;
			right = temp->right;
			temp->right = nullptr;
			delete temp;
			--right_height;
		} else {
			Comparable min = right->right->_find_min();
			if (right->right->left == nullptr){
				temp = right;
				right = temp->right;
				right->left = temp->left;
				right->left_height = temp->left_height;
				temp->right = nullptr;
				temp->left = nullptr;
				delete temp;
			} else {
				right->right->_remove(min);
				right->data = min;
			}
			right_height = max(right->left_height, right->right_height) + 1;
		}
	} else if (data > value){
		if (left == nullptr){
			//not found
		} else {
			left->_remove(value);
			left_height = max(left->left_height, left->right_height) + 1;
		}
	} else if (data < value){
		if (right == nullptr){
			//not found
		} else {
			right->_remove(value);
			right_height = max(right->left_height, right->right_height) + 1;
		}
	}
	rebalance();
}

template <typename Comparable>
const Comparable& AVLNode<Comparable>::_find_min() const{
	if (left == nullptr){
		return data;
	}
	AVLNode<Comparable>* traverse = left;
	while (traverse->left != nullptr){
		traverse = traverse->left;
	}
	return traverse->data;
}

template <typename Comparable>
const Comparable& AVLNode<Comparable>::_find_max() const{
	if (right == nullptr){
		return data;
	}
	AVLNode<Comparable>* traverse = right;
	while (traverse->right != nullptr){
		traverse = traverse->right;
	}
	return traverse->data;
}

template <typename Comparable>
void AVLNode<Comparable>::_print_helper(std::ostream& out, std::size_t spaces) const{
	spaces += 2;
	if (right != nullptr)
		right->_print_helper(out, spaces);
	for (std::size_t i=2; i < spaces; ++i){
		out << " ";
	}
	out << data << "\n";
	if (left != nullptr)
		left->_print_helper(out, spaces);
}

template <typename Comparable>
void AVLNode<Comparable>::single_left(){
	AVLNode<Comparable>* p;
	AVLNode<Comparable>* c;
	p = new AVLNode<Comparable>(data);
	p->right = right;
	p->right_height = right_height;
	c = left;
	p->left = c->right;
	p->left_height = c->right_height;
	data = c->data;
	left = c->left;
	left_height = c->left_height;
	right = p;
	right_height = max(p->left_height, p->right_height) + 1;
	c->left = nullptr;
	c->right = nullptr;
	delete c;
	
}

template <typename Comparable>
void AVLNode<Comparable>::single_right(){
	AVLNode<Comparable>* p;
	AVLNode<Comparable>* c;
	p = new AVLNode<Comparable>(data);
	p->left = left;
	p->left_height = left_height;
	c = right;
	p->right = c->left;
	p->right_height = c->left_height;
	data = c->data;
	right = c->right;
	right_height = c->right_height;
	left = p;
	left_height = max(p->left_height, p->right_height) + 1;
	c->left = nullptr;
	c->right = nullptr;
	delete c;
}

template <typename Comparable>
void AVLNode<Comparable>::double_left(){
	left->single_right();
	single_left();
}

template <typename Comparable>
void AVLNode<Comparable>::double_right(){
	right->single_left();
	single_right();
}

template <typename Comparable>
void AVLNode<Comparable>::rebalance(){
	if (left_height-right_height > 1){
		if (left->left_height >= left->right_height){
			single_left();
		} else {
			double_left();
		}
	} else if (right_height-left_height > 1){
		if (right->right_height >= right->left_height){
			single_right();
		} else {
			double_right();
		}
	}
	/*if (left != nullptr){
		left->rebalance();
		left_height = max(left->left_height, left->right_height) + 1;
	}
	if (right != nullptr){
		right->rebalance();
		right_height = max(right->left_height, right->right_height) + 1;
	}*/
}

template <typename Comparable>
int AVLNode<Comparable>::max(int x, int y){
	if (x > y){
		return x;
	} else {
		return y;
	}
}


template <typename Comparable>
class AVLTree {
	// TODO(student): implement BinarySearchTree
	public:
		AVLTree(); //constructs empty tree
		//Rule of Three
		AVLTree(const AVLTree&); //copy constructor for deep copy
		~AVLTree(); //destructor
		AVLTree& operator=(const AVLTree&); //copy assignment operator
		bool contains(const Comparable&) const;
		void insert(const Comparable&);
		void remove(const Comparable&); //work on it
		const Comparable& find_min() const;
		const Comparable& find_max() const;
		void print_tree(std::ostream& =std::cout) const;
		//BinarySearchTree(BinarySearchTree&&); //move contructor
		//BinarySearchTree& operator=(BinarySearchTree&&); //move assignment operator
		//bool is_empty() const;
		//void insert(Comparable&&); //move inserts
		//void make_empty()
	private:
		AVLNode<Comparable>* root;
};

template <typename Comparable>
AVLTree<Comparable>::AVLTree() : root{nullptr} {}

template <typename Comparable>
AVLTree<Comparable>::AVLTree(const AVLTree<Comparable>& orig) : root{nullptr} {
	if(orig.root != nullptr){
		root = new AVLNode<Comparable>(*orig.root);
	}
}

template <typename Comparable>
AVLTree<Comparable>::~AVLTree(){
	if (root != nullptr){
		delete root;
	}
}

template <typename Comparable>
AVLTree<Comparable>& AVLTree<Comparable>::operator=(const AVLTree<Comparable>& orig){
	if (this != &orig){
		if (root != nullptr){
			delete root;
		}
		root = new AVLNode<Comparable>(*orig.root);
	}
	return *this;
}

template <typename Comparable>
bool AVLTree<Comparable>::contains(const Comparable& value) const{
	if (root == nullptr){
		return false;
	} else {
		return root->_contains(value);
	}
}

template <typename Comparable>
void AVLTree<Comparable>::insert(const Comparable& value){
	if (root == nullptr){
		root = new AVLNode<Comparable>(value);
	} else {
		root->_insert(value);
	}
	root->rebalance();
}

template <typename Comparable>
void AVLTree<Comparable>::remove(const Comparable& value){
	if (contains(value)){
		if (value == root->data){
			AVLNode<Comparable>* temp;
			if (root->right == nullptr && root->left == nullptr){
				delete root;
				root = nullptr;
			} else if (root->right == nullptr){
				temp = root;
				root = temp->left;
				temp->left = nullptr;
				delete temp;
			} else if (root->left == nullptr){
				temp = root;
				root = temp->right;
				temp->right = nullptr;
				delete temp;
			} else {
				Comparable min = root->right->_find_min();
				if (root->right->left == nullptr){
					temp = root;
					root = temp->right;
					root->left = temp->left;
					temp->right = nullptr;
					temp->left = nullptr;
					delete temp;
				} else {
					root->right->_remove(min);
					root->data = min;
					root->right_height = root->max(root->right->left_height, root->right->right_height) + 1;
				}
			}
		} else {
			root->_remove(value);
		} 
		if (root != nullptr){
			root->rebalance();
		}
	} else {
		//not found
	}
}

template <typename Comparable>
const Comparable& AVLTree<Comparable>::find_min() const{
	if (root == nullptr){
		throw std::invalid_argument("empty tree");
	} else {
		return root->_find_min();
	}
}

template <typename Comparable>
const Comparable& AVLTree<Comparable>::find_max() const{
	if (root == nullptr){
		throw std::invalid_argument("empty tree");
	} else {
		return root->_find_max();
	}
}

template <typename Comparable>
void AVLTree<Comparable>::print_tree(std::ostream& out) const{
	if (root == nullptr){
		out << "<empty>\n";
	} else {
		root->_print_helper(out, 0);
	}
}

#endif
