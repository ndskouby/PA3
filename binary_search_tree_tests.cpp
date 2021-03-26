#include <iostream>
#include "binary_search_tree.h"

using std::cout, std::endl;

int main() {
	// TODO(student): write tests
	BinarySearchTree<int> BST;
	BST.insert(5);
	BST.insert(3);
	BST.insert(2);
	BST.insert(4);
	BST.insert(7);
	BST.insert(6);
	BST.insert(8);
	BST.insert(10);
	BST.insert(1);
	cout << BST.contains(0) << "\n";
	BST.contains(1);
	BST.print_tree();
	BST.remove(5);
	BST.print_tree();
	BST.remove(3);
	BST.print_tree();
	BST.remove(1);
	BST.print_tree();
	BST.remove(1);
	cout << BST.find_min() << "\n";
	cout << BST.find_max() << "\n";
	BST.remove(6);
	BST.print_tree();
	BST.remove(7);
	BST.print_tree();
	BST.remove(8);
	BST.print_tree();
	BST.remove(10);
	BST.print_tree();
	BinarySearchTree<int> BST_copy(BST);
	BST_copy.insert(10);
	BST_copy.print_tree();
	BST.print_tree();
	BinarySearchTree<int> BST_assign;
	BST_assign = BST;
	BST_assign.insert(12);
	BST_assign.print_tree();
	BST.print_tree();
	BST.remove(2);
	BST_copy.contains(12);
	BST.contains(13);
	BinarySearchTree<int> tester;
	tester.insert(4);
	tester.insert(2);
	tester.insert(1);
	tester.remove(2);
	tester.insert(2);
	tester.print_tree();
	tester.remove(1);
	tester.remove(2);
	tester.insert(1);
	tester.insert(3);
	tester.insert(2);
	tester.insert(0);
	tester.print_tree();
	tester.remove(1);
	tester.remove(3);
	tester.insert(7);
	tester.insert(6);
	tester.insert(8);
	tester.remove(7);
	tester.remove(8);
	tester.insert(7);
	tester.remove(6);
	tester.insert(9);
	tester.insert(8);
	tester.insert(6);
	tester.print_tree();
	tester.remove(7);
}
