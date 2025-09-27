#include<iostream>
#include<string.h>

class String{
private:
    char* data;
    int length;
public:
    String() : data(nullptr), length(0) {}

    String(const char* str){
        length = strlen(str);
        data = new char[length + 1];
        strcpy(data, str);
    }

    String(int size) : length(size) {
        data = new char[length + 1];
        for (int i = 0; i <= length; i++) {
            data[i] = '\0';
        }
    }

    String(const String& other) {
        length = other.length;
        data = new char[length + 1];
        strcpy(data, other.data);
    }

    ~String() {
        delete[] data;
    }
};