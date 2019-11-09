/*
 * BST.cpp
 * Name: Mike Baldwin
 * Course: EECS 2510 Non-Linear Data Structures - Fall 2019
 * Date: 11/9/2019
 * Description: Implementation of the Binary Search tree
*/

#include <string.h>
#include <iostream>
#include "BST.h"

BST::BST() : root{ nullptr }
{
}

void BST::Insert(const char* cArray)
{
	/*
	 *	Inserts a string into the tree. If the string already exists, then it will increment it's count.
	 *	Parameter:
	 *		<str> This is the string to insert into the tree
	*/

	//If the tree is empty, then we add this node as the root
	if (IsEmpty())
	{
		Node* newNode = new Node(cArray, 1, nullptr, nullptr, nullptr);
		root = newNode;
		std::cout << newNode->name << ' ' << newNode->count << std::endl;
		return;
	}

	//First, we search if the node already exists, if so, we can skip all this and just increment
	Node* current = Find(cArray);
	if (current != nullptr) //A node already exists
	{
		current->count++;
		std::cout << current->name << ' ' << current->count << std::endl;
	}
	else //No node exists yet for this value
	{
		current = root;
		while (current != nullptr)
		{
			if (std::strcmp(cArray, current->name) < 0) //If less than, move to the left subtree
			{
				if (current->left == nullptr) //No node to the left, add a new one
				{
					Node* newNode = new Node(cArray, 1, current, nullptr, nullptr);
					current->left = newNode;
					std::cout << newNode->name << ' ' << newNode->count << std::endl;
					return;
				}
				else //Keep moving through the tree
					current = current->left;
			}
			else if (std::strcmp(cArray, current->name) > 0) //Else If greater than, move to the right subtree
			{
				if (current->right == nullptr) //No node to the right, add a new one
				{
					Node* newNode = new Node(cArray, 1, current, nullptr, nullptr);
					current->right = newNode;
					std::cout << newNode->name << ' ' << newNode->count << std::endl;
					return;
				}
				else //Keep it moving
					current = current->right;
			}
		}
	}
}

void BST::Search(const char* cArray)
{
	/*
	 * Searches in the entire tree for a string and prints to console if found (or if not found)
	 * Parameter<str> The string to search for
	*/

	Node* node = Find(cArray);
	if (node != nullptr)
		std::cout << node->name << ' ' << node->count << std::endl;
	else
		std::cout << cArray << " 0" << std::endl;
}

void BST::GetHeight()
{
	std::cout << ComputeHeight(root) << std::endl;
}


bool BST::IsEmpty()
{
	return root == nullptr;
}

BST::Node* BST::Find(const char* cArray)
{
	/*
	 * Used for searching the tree when you want to get a node pointer back as opposed to just a string.
	 * Parameter<str> The string to search for
	 * Returns the node that contains the supplied string, or NULL if not found
	*/

	Node* current = root;
	while (current != nullptr) //'Current' will be NULL if 'root == NULL', which is intended!
	{
		if (std::strcmp(cArray, current->name) == 0)
			return current;
		if (std::strcmp(cArray, current->name) < 0)
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
		std::cout << node->name << ' ' << node->count << std::endl;
		if (node->right != nullptr)
			Traverse(node->right);
	}
}

int BST::ComputeHeight(Node* node)
{
	/*
	 * Trivial recursive traversal function. It calculates the height.
	*/

	if(node == nullptr)
		return 0;
	else
	{
		int leftHeight = ComputeHeight(node->left);
		int rightHeight = ComputeHeight(node->right);

		if(leftHeight > rightHeight)
			return (leftHeight + 1);
		else
			return rightHeight + 1;
	}
}

BST::Node::Node(const char* name, const int count, Node* parent, Node* left, Node* right)
{
	std::strcpy(this->name, name);
	this->count = count;
	this->parent = parent;
	this->left = left;
	this->right = right;
}

bool BST::Node::IsRoot()
{
	return parent == nullptr;
}

bool BST::Node::IsLeaf()
{
	return left == nullptr && right == nullptr;
}