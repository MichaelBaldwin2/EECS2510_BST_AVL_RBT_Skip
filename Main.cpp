/*
 * Name: Mike Baldwin
 * Course: EECS 2510 Non-Linear Data Structures
 * Date: 9/29/2019
*/

#include <string.h>
#include <iostream>
#include "BST.h"

using namespace std;

int main() noexcept
{
	auto bst = BST();

	while (true)
	{
		char str1[50];
		cin >> str1;

		if (std::strlen(str1) > 0)
		{
			if (std::strcmp(str1, "insert") == 0)
			{
				char str2[50];
				cin >> str2;
				bst.Insert(str2);
			}
			else if (std::strcmp(str1, "search") == 0)
			{
				char str2[50];
				cin >> str2;
				bst.Search(str2);
			}
			else if (std::strcmp(str1, "exit") == 0)
			{
				return 0;
			}
		}
	}
}