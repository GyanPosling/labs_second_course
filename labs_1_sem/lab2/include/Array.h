#ifndef MYSTRING_H
#define MYSTRING_H

#pragma once
#include <iostream>

class Array{
private:
    int* data;
    int size;

public:
    Array();
    Array(int* array, int arraySize);
    Array(int size);
    Array(const Array& other);
    Array& operator=(const Array& other);
    ~Array();

    const int* getData() const;
    int* getData();
    int getSize() const;
    void print() const;

    Array& operator&(const Array& other);
};

#endif 