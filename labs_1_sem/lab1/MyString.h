#pragma once
#include <iostream>

class MyString {
private:
    char* data;
    int length;

public:
    MyString();
    MyString(const char* str);
    MyString(int size);
    MyString(const MyString& other);
    MyString& operator=(const MyString& other);
    ~MyString();

    void print() const;
    
    MyString& intersectWith(const MyString& other);

    friend std::ostream& operator<<(std::ostream& os, const MyString& str);
    friend std::istream& operator>>(std::istream& is, MyString& str);
};