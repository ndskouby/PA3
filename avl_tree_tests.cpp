#include <iostream>
#include "avl_tree.h"

using std::cout, std::endl;

int main() {
	// TODO(student): write tests
	try{
	AVLTree<int> AVL;
	AVL.insert(5);
	AVL.print_tree();
	AVL.insert(3);
	AVL.print_tree();
	AVL.insert(2);
	AVL.print_tree();
	AVL.insert(4);
	AVL.print_tree();
	AVL.insert(7);
	AVL.print_tree();
	AVL.insert(6);
	AVL.print_tree();
	AVL.insert(8);
	AVL.print_tree();
	AVL.insert(10);
	AVL.print_tree();
	AVL.insert(1);
	cout << AVL.contains(0) << "\n";
	AVL.contains(1);
	AVL.print_tree();
	AVL.remove(5);
	AVL.print_tree();
	cout << AVL.contains(3) << "\n";
	AVL.remove(3);
	AVL.print_tree();
	AVL.remove(1);
	AVL.print_tree();
	AVL.remove(1);
	cout << AVL.find_min() << "\n";
	cout << AVL.find_max() << "\n";
	AVL.remove(6);
	AVL.print_tree();
	AVL.remove(7);
	AVL.print_tree();
	AVL.remove(8);
	AVL.print_tree();
	AVL.remove(10);
	AVL.print_tree();
	AVLTree<int> AVL_copy(AVL);
	AVL_copy.insert(10);
	AVL_copy.print_tree();
	AVL.print_tree();
	AVLTree<int> AVL_assign;
	AVL_assign = AVL;
	AVL_assign = AVL_copy;
	AVL_assign.insert(12);
	AVL_assign.print_tree();
	AVL.print_tree();
	AVL.insert(2);
	AVL.remove(2);
	AVL.remove(2);
	AVL.contains(12);
	AVL.contains(13);
	AVLTree<int> AVL_further;
	AVL_further.insert(4);
	AVL_further.insert(5);
	AVL_further.insert(2);
	AVL_further.insert(1);
	AVL_further.remove(2);
	AVL_further.insert(2);
	AVL_further.remove(1);
	AVLTree<int> again;
	again.insert(5);
	again.insert(2);
	again.insert(6);
	again.insert(1);
	again.insert(4);
	again.insert(7);
	again.insert(3);
	again.print_tree();
	again.remove(2);
	again.remove(6);
	again.insert(6);
	again.remove(7);
	again.remove(6);
	again.insert(2);
	again.print_tree();
	again.insert(6);
	again.remove(5);
	again.remove(6);
	again.remove(4);
	again.print_tree();
	again.insert(4);
	again.insert(6);
	again.insert(5);
	AVLNode<int> test_node(5);
	AVLNode<int> assign_node(6);
	assign_node = test_node;
	AVLTree<int> empty_tree;
	empty_tree.print_tree();
	empty_tree.find_min();
	} catch (const std::invalid_argument& ia){
		std::cerr << "Invalid argument: " << ia.what() << "\n";
	}
}
