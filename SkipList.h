/*
 * SkipList.h
 * Name: Mike Baldwin
 * Course: EECS 2510 Non-Linear Data Structures - Fall 2019
 * Date: 11/9/2019
 * Description: Declaration of the Skip List data structure
*/

#pragma once

class SkipList
{
public:
	SkipList();
	void Insert(const char* cArray);
	void Search(const char* cArray);
	int GetHeight();
	int GetApproxWorkDone();
	int GetNodeCount();

private:
	struct Node
	{
		char name[50]{};
		int count;
		Node* up;
		Node* down;
		Node* left;
		Node* right;
		
		Node(const char* name, const int count, Node* up, Node* down, Node* left, Node* right);
	};
	
	Node* head;
	Node* tail;
	int height;
	int itemCount;
	unsigned int keyComparisonCount;
	unsigned int headTossCount;
	unsigned int pointerChangeCount;
	Node* Find(const char* cArray);
	Node* FindPrevUp(Node* node);
};

