/*
 * AVL.h
 * Name: Mike Baldwin
 * Course: EECS 2510 Non-Linear Data Structures - Fall 2019
 * Date: 11/9/2019
 * Description: Declaration of the AVL tree
*/

#pragma once

class AVL
{
public:
	AVL();
	void Insert(const char* cArray);
	void Search(const char* cArray);
	void GetHeight();

private:

	struct Node
	{
		char name[50]{};
		int count;
		Node* left;
		Node* right;
		int balanceFactor;
		
		Node(const char* name, const int count, Node* left, Node* right, int balanceFactor);
		bool IsLeaf();
	};

	Node* root;
	Node* Find(const char* cArray);
	void Traverse(Node* node);
	int ComputeHeight(Node* node);
};
#pragma once
