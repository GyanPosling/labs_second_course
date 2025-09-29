#include "String.h"

String& String::operator=(const String& other) {
    if (this != &other) {
        delete[] this->data;
        this->length = other.length;
        this->data = new char[this->length + 1];
        strcpy(this->data, other.data);
    }
    return *this;
}

String String::operator+(const String& other) {
    String resultString(this->length + other.length);
    strcpy(resultString.data, this->data);
    strcat(resultString.data, other.data);
    return resultString;
}

String String::operator+(const char* string) {
    String resultString(strlen(string) + this->length);
    strcpy(resultString.data, this->data);
    strcat(resultString.data, string);
    return resultString;
}

String operator+(const char* string, const String& object) {
    String resultString(strlen(string) + object.length);
    strcpy(resultString.data, string);
    strcat(resultString.data, object.data);
    return resultString;
}

String& String::operator+=(const String& other) {
    char* temp = new char[this->length + other.length + 1];
    strcpy(temp, this->data);
    strcat(temp, other.data);
    delete[] this->data;
    this->data = temp;
    this->length += other.length;
    return *this;
}

char& String::operator[](int index) {
    return this->data[index];
}

const char& String::operator[](int index) const {
    return this->data[index];
}

String String::operator()(int start, int end) const {
    String result(end - start + 1);
    for (int i = 0; i < end - start; i++) {
        result.data[i] = this->data[start + i];
    }
    return result;
}

bool String::operator>(const String& other) const {
    return this->length > other.length;
}

bool String::operator<(const String& other) const {
    return this->length < other.length;
}

String& String::operator++() {
    for (int i = 0; i < this->length; i++) {
        if (this->data[i] != '\0') {
            this->data[i] = this->data[i] + 1;
        }
    }
    return *this;
}

String String::operator++(int) {
    String temp(*this);
    ++(*this);
    return temp;
}

String& String::operator--() {
    for (int i = 0; i < this->length; i++) {
        if (this->data[i] != '\0') {
            this->data[i] = this->data[i] - 1;
        }
    }
    return *this;
}

String String::operator--(int) {
    String temp(*this);
    --(*this);
    return temp;
}

std::ostream& operator<<(std::ostream& os, const String& string) {
    if (string.data != nullptr) {
        os << "'" << string.data << "'";
    }
    return os;
}

std::istream& operator>>(std::istream& is, String& string) {
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
    
    delete[] string.data;
    string.length = size;
    string.data = new char[string.length + 1];
    strcpy(string.data, buffer);
    
    delete[] buffer;
    return is;
}

String& String::operator=(const String& other) {
    if (this != &other) {
        delete[] this->data;
        this->length = other.length;
        this->data = new char[this->length + 1];
        strcpy(this->data, other.data);
    }
    return *this;
}