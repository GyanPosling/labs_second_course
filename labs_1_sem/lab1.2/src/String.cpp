#include "../include/String.hpp"

String& String::operator=(const String& other) {
    if (this != &other) {
        delete[] this->data;
        this->length = other.length;
        this->data = new char[this->length + 1];
        strcpy(this->data, other.data);
    }
    return *this;
}

String String::operator+(const String& other) const{
    String resultString(this->length + other.length);
    strcpy(resultString.data, this->data);
    strcat(resultString.data, other.data);
    return resultString;
}

String String::operator+(const char* string) const{
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
    String tempString(this->length + other.length);

    strcpy(tempString.data, this->data);
    strcat(tempString.data, other.data);

    delete[] this->data;
    
    this->data = tempString.data;
    this->length += other.length;

    tempString.data = nullptr;
    tempString.length = 0;

    return *this;
}

String& String::operator+=(const char* string){
    String tempString(this->length + strlen(string));

    strcpy(tempString.data, this->data);
    strcat(tempString.data, string);

    delete[] this->data;

    this->data = tempString.data;
    this->length += strlen(string);

    tempString.data = nullptr;
    tempString.length = 0;

    return *this;
}

char& String::operator[](int index) {
    char nullChar = '\0';
    return (index >= 0 && index < this->length) ? this->data[index] : nullChar;
}

String String::operator()(int start, int end) const {
    if (start < 0 || end >= this->length || start > end) {
        return String();
    }
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
bool String::operator==(const String& other) const {
    return strcmp(this->data, other.data) == 0;
}

bool String::operator!=(const String& other) const {
    return !(*this == other);
}

bool String::operator>=(const String& other) const {
    return this->length >= other.length;
}

bool String::operator<=(const String& other) const {
    return this->length <= other.length;
}

String& String::operator++() {
    for (int i = 0; i < this->length; i++) {
        if (this->data[i] != '\0') {
            this->data[i] = this->data[i] + 1;
        }
    }
    return *this;
}

String& String::operator--() {
    for (int i = 0; i < this->length; i++) {
        if (this->data[i] != '\0') {
            this->data[i] = this->data[i] - 1;
        }
    }
    return *this;
}

std::ostream& operator<<(std::ostream& os, const String& string) {
    if (string.data != nullptr) {
        os << "'" << string.data << "'";
    }
    return os;
}

std::istream& operator>>(std::istream& is, String& string) {
    char buffer[1000];
    
    std::cout << "Enter string: ";
    rewind(stdin);
    is.getline(buffer, 1000);
    
    delete[] string.data;
    string.length = strlen(buffer);
    string.data = new char[string.length + 1];
    strcpy(string.data, buffer);
    
    return is;
}

