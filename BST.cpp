/*
 * BST.cpp
 * Name: Mike Baldwin
 * Course: EECS 2510 Non-Linear Data Structures - Fall 2019
 * Date: 11/9/2019
 * Description: Binary search tree that auto-balances (so I guess AVL)
*/

#include <iostream>
#include <string>
#include "BST.h"

using namespace std;

BST::BST() : root{ nullptr }
{
}

void BST::Insert(const MyString& str)
{
	/*
	 *	Inserts a string into the BST. If the string already exists, then it will increment it's count.
	 *	Parameter:
	 *		<str> This is the string to insert into the tree
	*/

	//If the tree is empty, then we add this node as the root
	if (IsEmpty())
	{
		const auto newNode = new Node(str, 1, nullptr);
		root = newNode;
		cout << newNode->ToString() << endl;
		return;
	}

	//First, we search if the node already exists, if so, we can skip all this and just increment
	auto current = Find(str);
	if (current != nullptr) //A node already exists
	{
		current->count++;
		cout << current->ToString() << endl;
	}
	else //No node exists yet for this value
	{
		current = root;
		while (current != nullptr)
		{
			if (str < current->name) //If less than, move to the left subtree
			{
				if (current->left == nullptr) //No node to the left, add a new one
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
				if (current->right == nullptr) //No node to the right, add a new one
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

void BST::Search(const MyString& str) const
{
	/*
	 * Searches in the entire tree for a string and prints to console if found (or if not found)
	 * Parameter<str> The string to search for
	*/

	const auto node = Find(str);
	if (node != nullptr)
		cout << node->ToString() << endl;
	else
		cout << str << " 0" << endl;
}

bool BST::IsEmpty() const
{
	return root == nullptr;
}

BST::Node* BST::Find(const MyString& str) const
{
	/*
	 * Used for searching the tree when you want to get a node pointer back as opposed to just a string.
	 * Parameter<str> The string to search for
	 * Returns the node that contains the supplied string, or NULL if not found
	*/

	auto current = root;
	while (current != nullptr) //'Current' will be NULL if 'root == NULL', which is intended!
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

	if (node != nullptr)
	{
		if (node->left != nullptr)
			Traverse(node->left);
		cout << node->ToString() + "\n";
		if (node->right != nullptr)
			Traverse(node->right);
	}
}