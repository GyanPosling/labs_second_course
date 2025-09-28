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

String String:: operator+(const String& other){
    String resultString = new String(this->length + other.length); 
    strcpy(resultString.data, this->data);
    strcat(resultString.data, other.data)
    return resultString;
}

String String:: operator+(const char* string){
    String resultString = new String(strlen(string) + this->length);
    strcpy(resultString.data, this->data);
    strcat(resultString.data, string);
    return resultString;
}

String String:: operator+(const char* string, const String& object){
    String resultString = new String(strlen(string) + object.length);
    strcpy(resultString.data, string);
    strcat(resultString.data, object.data);
    return resultString;
}

String String:: operator+(const char* string1, const char& string2){
    String resultString = new String(strlen(string1) + strlen(string2));
    strcpy(resultString.data, string1);
    strcat(resultString.data, string2);
    return resultString;
}