/*
 * SkipList.cpp
 * Name: Mike Baldwin
 * Course: EECS 2510 Non-Linear Data Structures - Fall 2019
 * Date: 11/9/2019
 * Description: Implementation of the Skip List data structure
*/

#include <cstring>
#include <iostream>
#include <time.h>
#include "SkipList.h"

const char* NEG_INF = "negInf";
const char* POS_INF = "posInf";

SkipList::SkipList()
{
	head = new Node(NEG_INF, 0, nullptr, nullptr, nullptr, nullptr);
	tail = new Node(POS_INF, 0, nullptr, nullptr, nullptr, nullptr);
	head->right = tail;
	tail->left = head;
	std::srand((unsigned int)time(nullptr));
	itemCount = 0;
	height = 1;
}

void SkipList::Insert(const char* cArray)
{
	Node* nodeBefore = Find(cArray);

	// Check to see if the returned node IS our node
	keyComparisonCount++;
	if (std::strcmp(cArray, nodeBefore->name) == 0)
	{
		//We found our node, increment the count and return
		nodeBefore->count++;
		return;
	}

	Node* newNode = new Node(cArray, 1, nullptr, nullptr, nodeBefore, nodeBefore->right);
	nodeBefore->right->left = newNode;
	nodeBefore->right = newNode;
	itemCount++; // Increment the slow lane item count
	pointerChangeCount += 2;

	int randomNumber = rand() % 100; // Get a random number between 0 and 100
	Node* currentNode = newNode;
	while (randomNumber > 50)
	{
		headTossCount++;
		Node* prevTop = FindPrevUp(currentNode);
		keyComparisonCount++;
		if (std::strcmp(currentNode->name, NEG_INF) == 0) // We hit the head
		{
			Node* newHead = new Node(NEG_INF, 0, nullptr, head, nullptr, nullptr);
			Node* newTail = new Node(POS_INF, 0, nullptr, tail, nullptr, nullptr);
			Node* newCurrentNode = new Node(currentNode->name, 0, nullptr, currentNode, newHead, newTail);
			currentNode->up = newCurrentNode;
			newHead->right = newCurrentNode;
			newTail->left = newCurrentNode;
			head->up = newHead;
			tail->up = newTail;
			head = newHead;
			tail = newTail;
			currentNode = newCurrentNode;
			height++; // Increment the height
			pointerChangeCount += 5;
		}
		else // prevTop now equals the prev top node
		{
			Node* newCurrentNode = new Node(currentNode->name, 0, nullptr, currentNode, prevTop, prevTop->right);
			currentNode->up = newCurrentNode;
			prevTop->right->left = newCurrentNode;
			prevTop->right = newCurrentNode;
			currentNode = newCurrentNode;
			pointerChangeCount += 3;
		}

		randomNumber = rand() % 100; // Get a random number between 0 and 100
	}
}

void SkipList::Search(const char* cArray)
{
	/*
	 * Searches in the entire skip list for a string and prints to console if found (or if not found)
	 * Parameter<str> The string to search for
	*/

	Node* node = Find(cArray);
	if (node != nullptr)
		std::cout << node->name << ' ' << node->count << std::endl;
	else
		std::cout << cArray << " 0" << std::endl;
}

int SkipList::GetHeight()
{
	return height;
}

int SkipList::GetApproxWorkDone()
{
	return keyComparisonCount + headTossCount + pointerChangeCount;
}

int SkipList::GetNodeCount()
{
	unsigned int count = 0;
	Node* lastHead = head;
	while (lastHead != nullptr)
	{
		Node* current = lastHead;
		while (current != nullptr)
		{
			count++;
			current = current->right;
		}
		lastHead = lastHead->down;
	}

	return count;
}

SkipList::Node* SkipList::Find(const char* cArray)
{
	/*
	 * Used for searching the skip list when you want to get a node pointer back as opposed to just a string.
	 * Parameter<str> The string to search for
	 * Returns the node that contains the supplied string, or the preceding node if not found
	*/

	Node* current = head;
	while (true)
	{
		keyComparisonCount += 2;
		while (std::strcmp(current->right->name, POS_INF) != 0 && std::strcmp(current->right->name, cArray) <= 0)
			current = current->right;
		if (current->down == nullptr)
			return current;
		current = current->down;
	}
}

SkipList::Node* SkipList::FindPrevUp(Node* node)
{
	Node* current = node;
	while (true)
	{
		if (current->up != nullptr)
			return current->up;
		keyComparisonCount++;
		if (std::strcmp(current->name, NEG_INF) == 0)
			return current;
		current = current->left;
	}
}

SkipList::Node::Node(const char* name, const int count, Node* up, Node* down, Node* left, Node* right)
{
	std::strcpy(this->name, name);
	this->count = count;
	this->up = up;
	this->down = down;
	this->left = left;
	this->right = right;
}
