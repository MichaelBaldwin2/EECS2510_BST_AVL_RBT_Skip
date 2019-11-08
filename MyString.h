#pragma once

#include <fstream>

class MyString
{
public:
	MyString();
	MyString(const MyString&);
	MyString(MyString&& other) noexcept;
	explicit MyString(const char* s);
	~MyString();

	MyString& operator=(MyString other);
	bool operator==(const MyString& rhs) const;
	bool operator!=(const MyString& rhs) const;
	bool operator<(const MyString& rhs) const;
	bool operator>(const MyString& rhs) const;
	bool operator<=(const MyString& rhs) const;
	bool operator>=(const MyString& rhs) const;
	friend void swap(MyString& lhs, MyString& rhs) noexcept;
	friend std::ostream& operator<<(std::ostream& os, const MyString& obj);
	friend MyString operator+(const MyString& lhs, const MyString& rhs);
	friend MyString operator+(const MyString& lhs, const char rhs);
	friend MyString operator+(const MyString& lhs, const char* rhs);

private:
	char* data;
	unsigned int size;
};