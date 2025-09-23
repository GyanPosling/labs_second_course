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

    //const char* getData() const;
    char* getData();
    int getLength() const;
    bool isEmpty() const;
    void print() const;
    
    MyString& intersectWith(const MyString& other);
};