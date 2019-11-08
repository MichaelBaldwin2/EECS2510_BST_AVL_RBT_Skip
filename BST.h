/*
 * Name: Mike Baldwin
 * Course: EECS 2510 Non-Linear Data Structures
 * Date: 9/29/2019
*/

#pragma once

#include "MyString.h"

using namespace std;

// ReSharper disable once CppInconsistentNaming
class BST
{
public:
	BST();
	void Insert(const MyString& str);
	void Search(const MyString& str) const;

private:

	struct Node
	{
		Node* parent;
		Node* left;
		Node* right;
		MyString name;
		int count;

		Node(MyString name, const int count, Node* parent)
		{
			this->name = name;
			this->count = count;
			this->parent = parent;
			left = nullptr;
			right = nullptr;
		}

		bool IsRoot() const { return parent == nullptr; }
		bool IsLeaf() const { return left == nullptr && right == nullptr; }
		MyString ToString() const { return name + ' ' + count; }
	};

	Node* root;
	bool IsEmpty() const;
	Node* Find(const MyString& str) const;
	static void Traverse(Node* node);
};
