#pragma once

#include "DynamicArray.h"

class MyString
{
public:
	MyString();
	MyString(char *cArr);
	~MyString();

private:
	DynamicArray<char> data;
};