#include "MyString.h"
#include <cstring>
using namespace std;

MyString::MyString() : data(nullptr), length(0) {}

MyString::MyString(const char* str) {
    length = strlen(str);
    data = new char[length + 1];
    strcpy(data, str);
}

MyString::MyString(int size) : length(size) {
    data = new char[length + 1];
    for (int i = 0; i <= length; i++) {
        data[i] = '\0';
    }
}

MyString::MyString(const MyString& other) {
    length = other.length;
    data = new char[length + 1];
    strcpy(data, other.data);
}


MyString& MyString::operator=(const MyString& other) {
    if (this != &other) {
        delete[] data;
        length = other.length;
        data = new char[length + 1];
        strcpy(data, other.data);
    }

    return *this;
}

MyString::~MyString() {
    delete[] data;
}


MyString& MyString::intersectWith(const MyString& other) {

    MyString resultString((this->length < other.length) ? this->length : other.length);
    
    int resultLength = 0;
    
    for (int i = 0; i < this->length; i++) {
        for (int j = 0; j < other.length; j++) {
            if (this->data[i] == other.data[j]) {
                short duplicate = 0;
                for (int k = 0; k < resultLength; k++) {
                    if (resultString.data[k] == this->data[i]) {
                        duplicate = 1;
                        break;
                    }
                }
                if (!duplicate) {
                    resultString.data[resultLength] = this->data[i];
                    resultLength++;
                }
                break;
            }
        }
    }
    
    resultString.data[resultLength] = '\0';

    *this = resultString;
    return *this;

}

std::ostream& operator<<(std::ostream& os, const MyString& str) {
    if (str.data != nullptr) {
        os <<"'"<< str.data<< "'";
    }
    return os;
}

std::istream& operator>>(std::istream& is, MyString& str) {
    char ch;
    int capacity = 10;
    int size = 0;
    char* buffer = new char[capacity];
    
    while (is.get(ch) && ch != '\n') {
        if (size >= capacity - 1) {
            capacity *= 2;
            char* newBuffer = new char[capacity];
            strcpy(newBuffer, buffer);
            delete[] buffer;
            buffer = newBuffer;
        }
        buffer[size++] = ch;
    }
    buffer[size] = '\0';
    
    delete[] str.data;
    str.length = size;
    str.data = new char[str.length + 1];
    strcpy(str.data, buffer);
    
    delete[] buffer;
    return is;
}

