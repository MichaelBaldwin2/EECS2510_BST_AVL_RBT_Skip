/*
 * RBT.cpp
 * Name: Mike Baldwin
 * Course: EECS 2510 Non-Linear Data Structures - Fall 2019
 * Date: 11/9/2019
 * Description: Implementation of the Red-Black Tree
*/

#include <string.h>
#include <iostream>
#include <assert.h>
#include "RBT.h"

RBT::RBT()
{
	nil = new Node("", 0, nullptr, nullptr, nullptr, BLACK);
	nil->parent = nil;
	nil->left = nil;
	nil->right = nil;
	root = nil;
}

void RBT::Insert(const char* cArray)
{
	Node* node = new Node(cArray, 1, nullptr, nullptr, nullptr, BLACK);
	Insert(node);
}

void RBT::Search(const char* cArray)
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

void RBT::GetHeight()
{
	std::cout << ComputeHeight(root) << std::endl;
}

void RBT::Insert(Node* z)
{
	Node* y = nil;
	Node* x = root;

	while (x != nil)
	{
		y = x;
		if (std::strcmp(z->name, x->name) < 0)
			x = x->left;
		else
			x = x->right;
	}

	z->parent = y;
	if (y == nil)
		root = z;
	else
	{
		if (std::strcmp(z->name, y->name) < 0)
			y->left = z;
		else
			y->right = z;
	}
	z->left = nil;
	z->right = nil;
	z->color = RED; // Set it to red, We will re-balance the tree below


	// Insert Fix-up
	InsertFixup(z);
}

void RBT::InsertFixup(Node* currentNode)
{
	// currentNode should be RED when entering this function
	assert(currentNode != nullptr);
	assert(currentNode->color == RED);
	
	while (currentNode->parent->color == RED) // While currentNode's parent is RED, we have to fix things
	{
		if (currentNode->parent == currentNode->parent->parent->left) // Is currentNodes parent the left child of it's parent?
		{
			Node* uncle = currentNode->parent->parent->right; // Get currentNode's uncle
			if (uncle->color == RED) // Is currentNode's uncle red? If so, CASE 1
			{
				currentNode->parent->color = BLACK; // currentNodes parent becomes black
				uncle->color = BLACK; // currentNodes uncle becomes black
				currentNode->parent->parent->color = RED; // currentNodes grandparent changes to red
				currentNode = currentNode->parent->parent; // currentNode gets set to currentNode's grandparent (we have to check the tree form there (again))
			}
			else // Case 2 & 3
			{
				if (currentNode == currentNode->parent->right) // Is currentNode the right child of it's parent? If so, CASE 2
				{
					currentNode = currentNode->parent; // Set currentNode to be currentNodes parent
					LeftRotateAround(currentNode); // Perform a left rotation, so that we can change this case 2 into a case 3
				}

				// CASE 3
				currentNode->parent->color = BLACK; // Recolor currentNodes parent to be black 
				currentNode->parent->parent->color = RED; // Recolor currentNodes grandparent to be Red
				RightRotateAround(currentNode->parent->parent); // Right rotate around the link between currentNode's parent and grandparent
			}
		}
		else // Is currentNodes parent the right child of it's parent?
		{
			Node* uncle = currentNode->parent->parent->left; // Get currentNode's uncle
			if (uncle->color == RED) // Is currentNode's uncle red? If so, CASE 1
			{
				currentNode->parent->color = BLACK; // currentNodes parent becomes black
				uncle->color = BLACK; // currentNodes uncle becomes black
				currentNode->parent->parent->color = RED; // currentNodes grandparent changes to red
				currentNode = currentNode->parent->parent; // currentNode gets set to currentNode's grandparent (we have to check the tree form there (again))
			}
			else // Case 2 & 3
			{
				if (currentNode == currentNode->parent->left) // Is currentNode the right child of it's parent? If so, CASE 2
				{
					currentNode = currentNode->parent; // Set currentNode to be currentNodes parent
					RightRotateAround(currentNode); // Perform a right rotation, so that we can change this case 2 into a case 3
				}

				// CASE 3
				currentNode->parent->color = BLACK; // Recolor currentNodes parent to be black 
				currentNode->parent->parent->color = RED; // Recolor currentNodes grandparent to be Red
				LeftRotateAround(currentNode->parent->parent); // Left rotate around the link between currentNode's parent and grandparent
			}
		}
	}
	root->color = BLACK;
}


RBT::Node* RBT::Find(const char* cArray)
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

void RBT::Traverse(Node* node)
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

void RBT::LeftRotateAround(Node* x)
{
	assert(root->parent == nil);
	assert(x->right != nil);

	Node* y = x->right;
	x->right = y->left;

	if (y->left != nil)
		y->left->parent = x;
	y->parent = x->parent;
	if (x->parent == nil)
		root = y;
	else
	{
		if (x == x->parent->left)
			x->parent->left = y;
		else
			x->parent->right = y;
	}
	y->left = x;
	x->parent = y;
}

void RBT::RightRotateAround(Node* x)
{
	assert(root->parent == nil);
	assert(x->left != nil);

	Node* y = x->left;
	x->left = y->right;

	if (y->right != nil)
		y->right->parent = x;
	y->parent = x->parent;
	if (x->parent == nil)
		root = y;
	else
	{
		if (x == x->parent->right)
			x->parent->right = y;
		else
			x->parent->left = y;
	}
	y->right = x;
	x->parent = y;
}

int RBT::ComputeHeight(Node* node)
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

RBT::Node::Node(const char* name, const int count, Node* parent, Node* left, Node* right, Color color)
{
	std::strcpy(this->name, name);
	this->count = count;
	this->parent = parent;
	this->left = left;
	this->right = right;
	this->color = color;
}

bool RBT::Node::IsLeaf()
{
	return left == nullptr && right == nullptr;
}
