/*
 * Name: Mike Baldwin
 * Course: EECS 2510 Non-Linear Data Structures
 * Date: 11/9/2019
*/

#pragma once

/*
 * A couple things:
 * This is my dynamic array class. I got very, very, very tired of juggling node pointers so I just threw this together to do it for me.
 * The instructions on the PDF say we can't use any STL components. Thankfully, this isn't STL!   :)
 *
 * Also, becuase this is using generics I HAVE to define the functions within this header file.
 * I understand that there are "workarounds" to define it in a cpp file, but I don't like hacky code.
 */
template <class T>
class DynamicArray
{
public:
	DynamicArray();
	~DynamicArray();
	T Get(int index);
	int Size();
	void Add(T item);
	void Remove(int index);
	void Remove(T item);

private:
	T* ptr;
	int size;
	int allocated;
	void Grow();
};

template <class T>
DynamicArray<T>::DynamicArray()
{
	ptr = new T[1];
	size = 0;
	allocated = 1;
}

template <class T>
DynamicArray<T>::~DynamicArray()
{
	delete[] ptr;
	size = 0;
	allocated = 0;
}

template <class T>
T DynamicArray<T>::Get(int index)
{
	if (index < 0 || index >= size)
		throw "Index out of bounds exception";
	return ptr[index];
}

template <class T>
int DynamicArray<T>::Size()
{
	return size;
}

template <class T>
void DynamicArray<T>::Add(T item)
{
	if (size == allocated)
	{
		Grow();
	}

	ptr[size] = item;
	size++;
}

template <class T>
void DynamicArray<T>::Remove(int index)
{
	if (index < 0 || index >= size)
		throw "Index out of bounds exception";

	for (int i = index; i < size - 1; i++)
	{
		ptr[i] = ptr[i + 1];
	}
	size--;
}

template <class T>
void DynamicArray<T>::Remove(T item)
{
	for (int i = 0; i < size; i++)
	{
		if (ptr[i] == item)
		{
			Remove(i);
			break;
		}
	}
}

template <class T>
void DynamicArray<T>::Grow()
{
	size_t newSize = allocated * 2;
	T* newPtr = new T[newSize];
	memcpy(newPtr, ptr, allocated * sizeof(T));
	allocated = newSize;
	delete[] ptr;
	ptr = newPtr;
}