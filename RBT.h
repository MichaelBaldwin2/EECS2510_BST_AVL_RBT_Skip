/*
 * RBT.h
 * Name: Mike Baldwin
 * Course: EECS 2510 Non-Linear Data Structures - Fall 2019
 * Date: 11/9/2019
 * Description: Declaration of the Red-Black Tree
*/

#pragma once

class RBT
{
public:
	RBT();
	void Insert(const char* cArray);
	void Search(const char* cArray);
	void GetHeight();

private:
	enum Color { RED, BLACK };

	struct Node
	{
		char name[50]{};
		int count;
		Node* parent;
		Node* left;
		Node* right;
		Color color = BLACK;

		Node(const char* name, const int count, Node* parent, Node* left, Node* right, Color color);
		bool IsLeaf();
	};

	Node* root;
	Node* nil;
	void Insert(Node* z);
	void InsertFixup(Node* currentNode);
	void LeftRotateAround(Node* x);
	void RightRotateAround(Node* x);
	Node* Find(const char* cArray);
	void Traverse(Node* node);
	int ComputeHeight(Node* node);
};