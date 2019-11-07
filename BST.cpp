/*
 * BST.cpp
 * Name: Mike Baldwin
 * Course: EECS 2510 Non-Linear Data Structures - Fall 2019
 * Date: 11/9/2019
 * Description: Binary search tree that auto-balances (so I guess AVL)
*/

#include <iostream>
#include "BST.h"

using namespace std;

void BST::Insert(string str)
{
	/*
	 *	Inserts a string into the BST. If the string already exists, then it will icnrement it's count.
	 *	Parameter:
	 *		<str> This is the string to insert into the tree
	*/

	//If the tree is empty, then we add this node as the root
	if (IsEmpty())
	{
		Node* newNode = new Node(str, 1, NULL);
		root = newNode;
		cout << newNode->ToString() << endl;
		return;
	}

	//First, we search if the node already exists, if so, we can skip all this and just increment
	Node* current = Find(str);
	if (current != NULL) //A node already exists
	{
		current->count++;
		cout << current->ToString() << endl;
	}
	else //No node exists yet for this value
	{
		current = root;
		while (current != NULL)
		{
			if (str < current->name) //If less than, move to the left subtree
			{
				if (current->left == NULL) //No node to the left, add a new one
				{
					Node* newNode = new Node(str, 1, current);
					current->left = newNode;
					cout << newNode->ToString() << endl;
					return;
				}
				else //Keep moving through the tree
					current = current->left;
			}
			else if (str > current->name) //Else If greater than, move to the right subtree
			{
				if (current->right == NULL) //No node to the right, add a new one
				{
					Node* newNode = new Node(str, 1, current);
					current->right = newNode;
					cout << newNode->ToString() << endl;
					return;
				}
				else //Keep it moving
					current = current->right;
			}
		}
	}
}

void BST::Search(string str)
{
	/*
	 * Searchs in the entire tree for a string and prints to console if found (or if not found)
	 * Parameter<str> The string to search for
	*/

	Node* node = Find(str);
	if (node != NULL)
		cout << node->ToString() << endl;
	else
		cout << str << " 0" << endl;
}

void BST::Min()
{
	/*
	 * Finds and prints to console the minimum "node" in this tree.
	 * Parameter<str> The string to search for
	*/
	if (IsEmpty())
		cout << endl;
	else
		cout << FindMinimum(root)->name << endl;
}

void BST::Max()
{
	/*
	 * Finds and prints to console the maximum "node" in this tree.
	 * Parameter<str> The string to search for
	*/

	if (IsEmpty())
		cout << endl;
	else
		cout << FindMaximum(root)->name << endl;
}

void BST::Next(string str)
{
	/*
	 * Finds the succesor to the inputed string
	 * Parameter<str> The string that we use to search for it's successor from
	 */

	Node* current = Find(str);
	if (current == NULL)
		cout << endl;
	else if (current != NULL)
	{
		BST::Node* successor = FindSuccessor(current);
		if (successor == NULL)
			cout << endl;
		else
			cout << successor->name << endl;
	}
}

void BST::Prev(string str)
{
	/*
	 * Finds the predecessor to the inputed string.
	 * Parameter<str> The string that we use to search for it's predecessor from.
	 */

	Node* current = Find(str);
	if (current == NULL)
		cout << endl;
	else if (current != NULL)
	{
		BST::Node* predecessor = FindPredecessor(current);
		if (predecessor == NULL)
			cout << endl;
		else
			cout << predecessor->name << endl;
	}
}

void BST::List()
{
	/*
	 * Lists the entire tree in order to the console.
	 */

	if (IsEmpty())
		cout << endl;
	else
		Traverse(root);
}

BST::Node* BST::Find(string str)
{
	/*
	 * Used for searching the tree when you want to get a node pointer back as opposed to just a string.
	 * Parameter<str> The string to search for
	 * Returns the node that contains the supplied string, or NULL if not found
	*/

	Node* current = root;
	while (current != NULL) //'Current' will be NULL if 'root == NULL', which is intended!
	{
		if (current->name == str)
			return current;
		else if (str < current->name)
			current = current->left;
		else
			current = current->right;
	}
	return current;
}

void BST::Traverse(Node* node)
{
	/*
	 * Traverses the tree (or subtree), calls Traversal on it's children, and prints out to console.
	 * Parameter<node> The node to start the traversal from (in this subtree)
	*/

	if (node != NULL)
	{
		if (node->left != NULL)
			Traverse(node->left);
		cout << node->ToString() + "\n";
		if (node->right != NULL)
			Traverse(node->right);
	}
}

BST::Node* BST::FindSuccessor(Node* node)
{
	/*
	 * Finds the successor node to a node in a subtree
	 * Parameter<node> The node to start from (the subtree "root")
	 * Returns the successor node in the subtree, or NULL if the tree is empty
	*/

	Node* current = node;
	if (current != NULL)
	{
		if (current->right != NULL) //First case, get the minimum node starting from this nodes right child.
			return FindMinimum(current->right);
		else //Right child is NULL, we've got to travel back up the tree boys!
		{
			Node* nextNode = current->parent;
			while (nextNode != NULL && current == nextNode->right)
			{
				current = nextNode;
				nextNode = nextNode->parent;
			}
			return nextNode;
		}
	}

	return NULL;
}

BST::Node* BST::FindPredecessor(Node* node)
{
	/*
	 * Finds the predecessor node to a node in a subtree
	 * Parameter<node> The node to start from (the subtree "root")
	 * Returns the predecessor node in the subtree, or NULL if the tree is empty
	*/

	Node* current = node;
	if (current != NULL)
	{
		if (current->left != NULL) //First case, get the maximum node starting from this nodes left child.
			return FindMaximum(current->left);
		else //Left child is NULL, we've got to travel back up the tree boys!
		{
			Node* prevNode = current->parent;
			while (prevNode != NULL && current == prevNode->left)
			{
				current = prevNode;
				prevNode = prevNode->parent;
			}
			return prevNode;
		}
	}

	return NULL;
}

BST::Node* BST::FindMinimum(Node* node)
{
	/*
	 * Finds the maximum node in a subtree
	 * Parameter<node> The node to start from (the subtree "root")
	 * Returns the maximum node in the subtree, or NULL if none exist (node is a leaf)
	*/

	Node* current = node;
	while (current->left != NULL)
		current = current->left;
	return current;
}

BST::Node* BST::FindMaximum(Node* node)
{
	/*
	 * Finds the minimum node in a subtree
	 * Parameter<node> The node to start from (the subtree "root")
	 * Returns the minimum node in the subtree, or NULL if none exist (node is a leaf)
	*/

	Node* current = node;
	while (current->right != NULL)
		current = current->right;
	return current;
}

void BST::Transplant(Node* u, Node* v)
{
	/*
	 * Transplant agorithm presented in class and in the book.
	*/

	if (u->parent == NULL)
		root = v;
	else if (u == u->parent->left)
		u->parent->left = v;
	else
		u->parent->right = v;
	if (v != NULL)
		v->parent = u->parent;
}