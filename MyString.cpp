#include "MyString.h"
#include <string> // <=== Need this include for the strcmp(). Could I implement it myself? Yes. --- Do I really want to? Not at all :)

using namespace std;

MyString::MyString() : data{ new char[0] }, size{ 0 }
{
}

MyString::MyString(const MyString& other) : data{ new char[other.size] }, size{ other.size }
{
	std::copy(other.data, other.data + other.size, data);
}

MyString::MyString(MyString&& other) noexcept : MyString()
{
	swap(*this, other);
}

MyString::MyString(const char* s) : MyString()
{
	auto c = const_cast<char*>(s);
	auto count = 0;
	while (*c != 0) //Loop until we hit a null terminator
	{
		count++;
		c++;
	}

	if (count > 0)
	{
		delete[] data;
		data = new char[count];
		size = count;
	}
}

MyString::~MyString()
{
	delete[]data;
	data = nullptr;
	size = 0;
}

MyString& MyString::operator=(MyString other)
{
	swap(*this, other);
	return *this;
}

bool MyString::operator==(const MyString& rhs) const
{
	return strcmp(this->data, rhs.data) == 0;
}

bool MyString::operator!=(const MyString& rhs) const
{
	return !(*this == rhs);
}

bool MyString::operator<(const MyString& rhs) const
{
	return strcmp(this->data, rhs.data) < 0;
}

bool MyString::operator>(const MyString& rhs) const
{
	return rhs < *this;
}

bool MyString::operator<=(const MyString& rhs) const
{
	return !(*this > rhs);
}

bool MyString::operator>=(const MyString& rhs) const
{
	return !(*this < rhs);
}

void swap(MyString& lhs, MyString& rhs) noexcept
{
	using std::swap;
	swap(lhs.size, rhs.size);
	swap(lhs.data, rhs.data);
}

std::ostream& operator<<(std::ostream& os, const MyString& obj)
{
	os.write(obj.data, obj.size);
	return os;
}

MyString operator+(const MyString& lhs, const MyString& rhs)
{
	MyString resultString;
	const auto size = lhs.size + rhs.size;
	delete[] resultString.data;
	resultString.data = nullptr;
	resultString.data = new char[size];
	resultString.size = size;
	std::copy(lhs.data, lhs.data + lhs.size, resultString.data);
	std::copy(rhs.data, rhs.data + rhs.size, resultString.data + lhs.size);
	return resultString;
}

MyString operator+(const MyString& lhs, const char rhs)
{
	const MyString rhsString(&rhs);
	return lhs + rhsString;
}

MyString operator+(const MyString& lhs, const char* rhs)
{
	const MyString rhsString(rhs);
	return lhs + rhsString;
}