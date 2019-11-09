/*
 * AVL.cpp
 * Name: Mike Baldwin
 * Course: EECS 2510 Non-Linear Data Structures - Fall 2019
 * Date: 11/9/2019
 * Description: Implementation of the AVL tree
*/

#include <string.h>
#include <iostream>
#include <assert.h>
#include "AVL.h"

AVL::AVL() : root{ nullptr }
{
}

void AVL::Insert(const char* cArray)
{
	/*
	 *	Inserts a string into the tree. If the string already exists, then it will increment it's count.
	 *	Parameter:
	 *		<str> This is the string to insert into the tree
	*/

	/*
	 * LEGEND FROM SLIDES TO BETTER NAMED VARIABLES:
	 *		Y	=	newNode
	 *		A	=	lastNZBFNode
	 *		B	=	lastNZBFNodeChild
	 *		F	=	lastNZBFNodeParent
	 *		P	=	currentNode
	 *		Q	=	currentNodeParent
	 *		C	=
	 *		CL	=
	 *		CR	=
	 *		d	=	displacement
	 */

	Node* newNode; // The new node we insert
	int displacement; // displacement; Used to adjust BFs

	//==============================================================
	// EMPTY TREE INSERT CODE
	//==============================================================

	// If the root is null, then we create a new node and stop the insert here
	if (root == nullptr)
	{
		newNode = new Node(cArray, 0, nullptr, nullptr, 0);
		root = newNode;
		return;
	}

	//==============================================================
	// SEARCH AND INSERT CODE
	//==============================================================

	/*
	 * Locate insertion point for the new node.
	 * The scanner scans through the tree until it falls off bottom
	 * Q is P’s parent (Q lags one step behind P) (y previously)
	 * The new Node Y will be added as either the Left or Right child of Q
	 * A is the last parent above Y with a BF of ±1 (before the insert)
	 * F is A’s parent (F lags one step behind A)
	 */

	Node* lastNZBFNode = root; // The last non-zero balance factor node
	Node* lastNZBFNodeParent = nullptr; // The parent of the last non-zero balance factor node
	Node* currentNode = root; // The current node we are using to scan through the tree
	Node* currentNodeParent = nullptr; // The parent of the current node (lags behind current node)
	while (currentNode != nullptr) // search tree for insertion point. We can't use the search function as we need to track the last non-zero bf node (and it's parent)
	{
		if (strcmp(cArray, currentNode->name) == 0) // Found a node that matches, just increment count and return (no balancing needed)
		{
			currentNode->count++;
			return;
		}
		if (currentNode->balanceFactor != 0) // If the current node has a non-zero balance factor, remember it (and its parent)
		{
			lastNZBFNode = currentNode;
			lastNZBFNodeParent = currentNodeParent;
		}

		// Advance the current node to it's next child (based upon the BT property). Also bring it's parent tracker up to its old spot.
		currentNodeParent = currentNode;
		currentNode = (strcmp(cArray, currentNode->name) < 0) ? currentNode->left : currentNode->right;
	}

	// If we reach here, then current node is NULL. Which is fine, we need to make a new node anyways...

	//==============================================================
	// NEW NODE INSERT CODE (and balancing after)
	//==============================================================

	// Create a new node
	newNode = new Node(cArray, 0, nullptr, nullptr, 0);

	// Based upon currentNodeParent, we will either place this new node as its left or right child
	if (strcmp(cArray, currentNodeParent->name) < 0)
		currentNodeParent->left = newNode;
	else
		currentNodeParent->right = newNode;

	/*
	 * So far, except for keeping track of F and A, we have done exactly
	 * the same “dumb” BST insert we’ve seen before.  Now, it’s time to do
	 * the AVL-specific stuff: detect (and fix, if we have) an imbalance
	 */

	 // "Thar be out o' balance trees beyond this point lad"
	 //===================================================================\\

	 //==============================================================
	 // TREE BALANCING (not unlike balancing a broom on your hand....but with a tree)
	 //==============================================================

	 /*
	  * Adjust BFs from lastNZBFNode to CurrentNodeParent.
	  * lastNZBFNode was the LAST ancestor with a BF of ± 1, (or is still the root, because we never FOUND a BF of ± 1).
	  * So ALL nodes BETWEEN lastNZBFNode and CurrentNodeParent must have a BF of 0, and will, therefore, BECOME ± 1.
	  *
	  * If newNode is inserted in the LEFT subtree of lastNZBFNode, then displacement = +1
	  * If displacement == -1 means we inserted newNode in the RIGHT subtree of lastNZBFNode.
	  */

	Node* lastNZBFNodeChild; // This the child of the last non-zero branch factor node we encountered

	// Which way is the displacement
	if (strcmp(cArray, lastNZBFNode->name) > 0) // Is the new node on the right side of the lastNZBFNode
	{
		lastNZBFNodeChild = lastNZBFNode->right; // Set lastNZBFNodeChild to lastNZBFNodes right child
		currentNode = lastNZBFNode->right; // Set currentNode to lastNZBFNodes right child
		displacement = -1; // Displacement is off by -1 now
	}
	else // Is the new node on the left side of the lastNZBFNode
	{
		lastNZBFNodeChild = lastNZBFNode->left; // Set lastNZBFNodeChild to lastNZBFNodes left child
		currentNode = lastNZBFNode->left; // Set currentNode to lastNZBFNodes left child
		displacement = +1; // Displacement is off by +1 now
	}

	// currentNode is now one node below lastNZBFNode. Adjust from here to the insertion point. Don’t do anything to newNode.
	while (currentNode != newNode /*&& currentNode != nullptr*/)
	{
		assert(currentNode != nullptr);

		// If newNode is on the right side of currentNode (which means the newnode is on the LEFT side of the currentNode)
		if (strcmp(cArray, currentNode->name) > 0)
		{
			// adjust BF and move forward
			currentNode->balanceFactor = -1;
			currentNode = currentNode->right;
		}
		else // If newNode is on the left side of currentNode (which means the newnode is on the RIGHT side of the currentNode)
		{
			// adjust BF and move forward
			currentNode->balanceFactor = +1;
			currentNode = currentNode->left;
		}
	}

	// If the tree was completely balanced then all we do is set the new balance factor and return
	if (lastNZBFNode->balanceFactor == 0)
	{
		lastNZBFNode->balanceFactor = displacement; // Set the balanceFactor to ± 1 (the displacement tells us which direction)
		return;
	}
	// If the tree already had a slight imbalance the OTHER way, then did the insertion throw the tree into complete balance. If so, set the BF to zero and return
	if (lastNZBFNode->balanceFactor == -displacement)
	{
		lastNZBFNode->balanceFactor = 0; // Set balanceFactor to zero and return
		return;
	}

	//If we took neither of the two returns above then the tree was acceptably imbalanced, and is now UNACCEPTABLY IMBALANCED.
	if (displacement == +1)
	{
		assert(lastNZBFNodeChild != nullptr);

		if (lastNZBFNodeChild->balanceFactor == +1) // LL rotation
		{
			// Change the child pointers of lastNZBFNode and lastNZBFNodeChild to reflect the new post-rotation structure
			lastNZBFNode->left = lastNZBFNodeChild->right;
			lastNZBFNodeChild->right = lastNZBFNode;
			lastNZBFNode->balanceFactor = lastNZBFNodeChild->balanceFactor = 0;
		}
		else // LR rotation
		{
			/*
			 * LR rotation (4 LOC)
			 * 3 CASES
			 * Change the child pointers of lastNZBFNode, lastNZBFNodeChild, and lastNZBFNodeGrandChild to reflect the new post-rotation structure
			 */

			Node* c = lastNZBFNodeChild->right;
			Node* cl = c->left;
			Node* cr = c->right;

			/*
			 * Set BF's of A & B, based upon the BF of C
			 * 3 sub-cases
			 * 3 LOC
			 */
			switch (c->balanceFactor)
			{
			case 0: // CASE (a)
				c->right = lastNZBFNode;
				c->left = lastNZBFNodeChild;
				lastNZBFNode->left = lastNZBFNodeChild->right = nullptr;
				break;
			case 1: // CASE (b)
				c->left = lastNZBFNodeChild;
				c->right = lastNZBFNode;
				lastNZBFNodeChild->right = cl;
				lastNZBFNode->left = cr;
				c->balanceFactor = 0;
				lastNZBFNodeChild->balanceFactor = 0;
				lastNZBFNode->balanceFactor = -1;
				break;
			case -1: // CASE (c)
				c->left = lastNZBFNodeChild;
				c->right = lastNZBFNode;
				lastNZBFNodeChild->right = cl;
				lastNZBFNode->left = cr;
				c->balanceFactor = 0;
				lastNZBFNode->balanceFactor = 0;
				lastNZBFNodeChild->balanceFactor = 1;
				break;
			}

			c->balanceFactor = 0;
			lastNZBFNodeChild = c;
		}
	}
	else // displacement = -1
	{
		//Symmetric to above

		assert(lastNZBFNodeChild != nullptr);

		if (lastNZBFNodeChild->balanceFactor == +1) // RR rotation
		{
			lastNZBFNode->right = lastNZBFNodeChild->left;
			lastNZBFNodeChild->left = lastNZBFNode;
			lastNZBFNode->balanceFactor = lastNZBFNodeChild->balanceFactor = 0;
		}
		else
		{
			/*
			 * RL rotation (4 LOC)
			 * 3 CASES
			 * Change the child pointers of lastNZBFNode, lastNZBFNodeChild, and lastNZBFNodeGrandChild to reflect the new post-rotation structure
			 */

			Node* c = lastNZBFNodeChild->left;
			Node* cl = c->left;
			Node* cr = c->right;

			/*
			 * Set BF's of A & B, based upon the BF of C
			 * 3 sub-cases
			 * 3 LOC
			 */
			switch (c->balanceFactor)
			{
			case 0: // CASE (a)
				c->right = lastNZBFNodeChild;
				c->left = lastNZBFNode;
				lastNZBFNode->left = lastNZBFNodeChild->right = nullptr;
				break;
			case 1: // CASE (b)
				c->left = lastNZBFNode;
				c->right = lastNZBFNodeChild;
				lastNZBFNodeChild->left = cr;
				lastNZBFNode->right = cl;
				c->balanceFactor = 0;
				lastNZBFNode->balanceFactor = 0;
				lastNZBFNodeChild->balanceFactor = -1;
				break;
			case -1: // CASE (c)
				c->left = lastNZBFNode;
				c->right = lastNZBFNodeChild;
				lastNZBFNodeChild->left = cr;
				lastNZBFNode->right = cl;
				c->balanceFactor = 0;
				lastNZBFNode->balanceFactor = 1;
				lastNZBFNodeChild->balanceFactor = 0;
				break;
			}

			c->balanceFactor = 0;
			lastNZBFNodeChild = c;
		}
	}

	//==============================================================
	// FINISH UP
	//==============================================================

	/*
	 * Regardless, the subtree rooted at lastNZBFNodeChild has been rebalanced and needs to be the new child of lastNZBFNodeParent
	 * The original subtree of lastNZBFNodeParent had a root of lastNZBFNode
	 */

	 // Did we re-balance the whole tree's root?
	if (lastNZBFNodeParent == nullptr)
	{
		root = lastNZBFNodeChild;
		return;
	}

	/*
	 * The root of what we rebalanced WAS lastNZBFNode, now it’s lastNZBFNodeChild.
	 * If the subtree we rebalanced was LEFT of lastNZBFNodeParent, then lastNZBFNodeChild needs to be left of lastNZBFNodeParent.
	 * If lastNZBFNode was RIGHT of lastNZBFNodeParent, then lastNZBFNodeChild now needs to be right of lastNZBFNodeParent.
	*/

	if (lastNZBFNode == lastNZBFNodeParent->left)
	{
		lastNZBFNodeParent->left = lastNZBFNodeChild;
		return;
	}
	if (lastNZBFNode == lastNZBFNodeParent->right)
	{
		lastNZBFNodeParent->right = lastNZBFNodeChild;
		return;
	}
	std::cout << "We should never be here" << std::endl;
}

void AVL::Search(const char* cArray)
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

void AVL::GetHeight()
{
	std::cout << ComputeHeight(root) << std::endl;
}

AVL::Node* AVL::Find(const char* cArray)
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

void AVL::Traverse(AVL::Node* node)
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

int AVL::ComputeHeight(Node* node)
{
	/*
	 * Trivial recursive traversal function. It calculates the height.
	*/

	if (node == nullptr)
		return 0;
	else
	{
		int leftHeight = ComputeHeight(node->left);
		int rightHeight = ComputeHeight(node->right);

		if (leftHeight > rightHeight)
			return (leftHeight + 1);
		else
			return rightHeight + 1;
	}
}

AVL::Node::Node(const char* name, const int count, Node* left, Node* right, int balanceFactor)
{
	std::strcpy(this->name, name);
	this->count = count;
	this->left = left;
	this->right = right;
	this->balanceFactor = balanceFactor;
}

bool AVL::Node::IsLeaf()
{
	return left == nullptr && right == nullptr;
}