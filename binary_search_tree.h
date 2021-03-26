#include<stdexcept>
#include<cstddef>
#include<sstream>
#include<iostream>
#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

template <typename Comparable>
struct BSTNode{
	BSTNode(Comparable);
	BSTNode(const BSTNode&);
	~BSTNode();
	BSTNode& operator=(const BSTNode&);
	bool _contains(const Comparable&);
	void _insert(const Comparable&);
	void _remove(const Comparable&);
	const Comparable& _find_min() const;
	const Comparable& _find_max() const;
	void _print_helper(std::ostream& out, std::size_t spaces) const;
	BSTNode<Comparable>* left;
	BSTNode<Comparable>* right;
	Comparable data;
};

template <typename Comparable>
BSTNode<Comparable>::BSTNode(Comparable value) : left{nullptr}, right{nullptr}, data{value} {}

template <typename Comparable>
BSTNode<Comparable>::BSTNode(const BSTNode& orig) : left{nullptr}, right{nullptr}, data{orig.data} {
	if (orig.left != nullptr){
		left = new BSTNode<Comparable>(*orig.left);
	}
	if (orig.right != nullptr){
		right = new BSTNode<Comparable>(*orig.right);
	}	
}

template <typename Comparable>
BSTNode<Comparable>::~BSTNode(){
	if (left != nullptr){
		delete left;
	}
	if (right != nullptr){
		delete right;
	}
}

template <typename Comparable>
BSTNode<Comparable>& BSTNode<Comparable>::operator=(const BSTNode<Comparable>& orig){
	if (this != &orig){
		if (left != nullptr){
			delete left;
		}
		if (right != nullptr){
			delete right;
		}
		data = orig.data;
		if (orig.left != nullptr){
			left = new BSTNode<Comparable>(*orig.left);
		}
		if (orig.right != nullptr){
			right = new BSTNode<Comparable>(*orig.right);
		}
	}
	return *this;
		
}

template <typename Comparable>
bool BSTNode<Comparable>::_contains(const Comparable& value){
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
void BSTNode<Comparable>::_insert(const Comparable& value){
	if (value > data){
		if (right == nullptr){
			right = new BSTNode<Comparable>(value);
		} else {
			right->_insert(value);
		}
	} else if (value < data){
		if (left == nullptr){
			left = new BSTNode<Comparable>(value);
		} else {
			left->_insert(value);
		}
	} else {
		//duplicate
	}
}

template <typename Comparable>
void BSTNode<Comparable>::_remove(const Comparable& value){
	if (left != nullptr && left->data == value){
		BSTNode<Comparable>* temp;
		if (left->right == nullptr && left->left == nullptr){
			delete left;
			left = nullptr;
		} else if (left->right == nullptr){
			temp = left;
			left = temp->left;
			temp->left = nullptr;
			delete temp;
		} else if (left->left == nullptr){
			temp = left;
			left = temp->right;
			temp->right = nullptr;
			delete temp;
		} else {
			Comparable min = left->right->_find_min();
			if (left->right->left == nullptr){
				temp = left;
				left = temp->right;
				left->left = temp->left;
				temp->right = nullptr;
				temp->left = nullptr;
				delete temp;
			} else {
				left->right->_remove(min);
				left->data = min;
			}
		}
	} else if (right != nullptr && right->data == value){
		BSTNode<Comparable>* temp;
		if (right->right == nullptr && right->left == nullptr){
			delete right;
			right = nullptr;
		} else if (right->right == nullptr){
			temp = right;
			right = temp->left;
			temp->left = nullptr;
			delete temp;
		} else if (right->left == nullptr){
			temp = right;
			right = temp->right;
			temp->right = nullptr;
			delete temp;
		} else {
			Comparable min = right->right->_find_min();
			if (right->right->left == nullptr){
				temp = right;
				right = temp->right;
				right->left = temp->left;
				temp->right = nullptr;
				temp->left = nullptr;
				delete temp;
			} else {
				right->right->_remove(min);
				right->data = min;
			}
		}
	} else if (data > value){
		if (left == nullptr){
			//not found
		} else {
			left->_remove(value);
		}
	} else if (data < value){
		if (right == nullptr){
			//not found
		} else {
			right->_remove(value);
		}
	}
}

template <typename Comparable>
const Comparable& BSTNode<Comparable>::_find_min() const{
	if (left == nullptr){
		return data;
	}
	BSTNode<Comparable>* traverse = left;
	while (traverse->left != nullptr){
		traverse = traverse->left;
	}
	return traverse->data;
}

template <typename Comparable>
const Comparable& BSTNode<Comparable>::_find_max() const{
	if (right == nullptr){
		return data;
	}
	BSTNode<Comparable>* traverse = right;
	while (traverse->right != nullptr){
		traverse = traverse->right;
	}
	return traverse->data;
}

template <typename Comparable>
void BSTNode<Comparable>::_print_helper(std::ostream& out, std::size_t spaces) const{
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
class BinarySearchTree {
	// TODO(student): implement BinarySearchTree
	public:
		BinarySearchTree(); //constructs empty tree
		//Rule of Three
		BinarySearchTree(const BinarySearchTree&); //copy constructor for deep copy
		~BinarySearchTree(); //destructor
		BinarySearchTree& operator=(const BinarySearchTree&); //copy assignment operator
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
		BSTNode<Comparable>* root;
};

template <typename Comparable>
BinarySearchTree<Comparable>::BinarySearchTree() : root{nullptr} {}

template <typename Comparable>
BinarySearchTree<Comparable>::BinarySearchTree(const BinarySearchTree<Comparable>& orig) : root{nullptr} {
	if(orig.root != nullptr){
		root = new BSTNode<Comparable>(*orig.root);
	}
}

template <typename Comparable>
BinarySearchTree<Comparable>::~BinarySearchTree(){
	if (root != nullptr){
		delete root;
	}
}

template <typename Comparable>
BinarySearchTree<Comparable>& BinarySearchTree<Comparable>::operator=(const BinarySearchTree<Comparable>& orig){
	if (this != &orig){
		if (root != nullptr){
			delete root;
		}
		root = new BSTNode<Comparable>(*orig.root);
	}
	return *this;
}

template <typename Comparable>
bool BinarySearchTree<Comparable>::contains(const Comparable& value) const{
	if (root == nullptr){
		return false;
	} else {
		return root->_contains(value);
	}
}

template <typename Comparable>
void BinarySearchTree<Comparable>::insert(const Comparable& value){
	if (root == nullptr){
		root = new BSTNode<Comparable>(value);
	} else {
		root->_insert(value);
	}
}

template <typename Comparable>
void BinarySearchTree<Comparable>::remove(const Comparable& value){
	if (contains(value)){
		if (value == root->data){
			BSTNode<Comparable>* temp;
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
				}
			}
		} else {
				root->_remove(value);
		}
	} else {
		//not found
	}
}

template <typename Comparable>
const Comparable& BinarySearchTree<Comparable>::find_min() const{
	if (root == nullptr){
		throw std::invalid_argument("empty tree");
	}
	return root->_find_min();
}

template <typename Comparable>
const Comparable& BinarySearchTree<Comparable>::find_max() const{
	if (root == nullptr){
		throw std::invalid_argument("empty tree");
	}
	return root->_find_max();
}

template <typename Comparable>
void BinarySearchTree<Comparable>::print_tree(std::ostream& out) const{
	if (root == nullptr){
		out << "<empty>\n";
	} else {
		root->_print_helper(out, 0);
	}
}

#endif
