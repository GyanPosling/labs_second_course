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

// const char* MyString::getData() const {
//     return data;
// }

char* MyString::getData() { return data; }


int MyString::getLength() const {
    return length;
}

bool MyString::isEmpty() const {
    return length == 0;
}

void MyString::print() const {
    cout << data << endl;
}

MyString& MyString::intersectWith(const MyString& other) {
    MyString currentString = *this;
    MyString otherString = other;
    MyString resultString((currentString.getLength() < otherString.getLength()) ? currentString.getLength() : otherString.getLength());
    
    int resultLength = 0;
    
    for (int i = 0; i < currentString.getLength(); i++) {
        for (int j = 0; j < otherString.getLength(); j++) {
            if (currentString.getData()[i] == otherString.getData()[j]) {
                bool duplicate = false;
                for (int k = 0; k < resultLength; k++) {
                    if (resultString.getData()[k] == currentString.getData()[i]) {
                        duplicate = true;
                        break;
                    }
                }
                if (!duplicate) {
                    resultString.getData()[resultLength] = currentString.getData()[i];
                    resultLength++;
                }
                break;
            }
        }
    }
    
    resultString.getData()[resultLength] = '\0';
    
    *this = resultString;
    return *this;
}