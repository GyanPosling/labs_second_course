#include <iostream>
#include <cstring>

class String {
private:
    char* data;
    int length;

public:
    String(): this->data(nullptr), this->length(0) {}

    String(const char* str){
        this->length = strlen(this->str);
        this->data = new char[this->length + 1];
        strcpy(this->data, this->str);
    }

    explicit String(int size): this->length(size){
        this->data = new char[this->length + 1];
        for (int i = 0; i <= this->length; i++) {
            this->data[i] = '\0';
        }
    }

    String(const String& other){
        this->length = other.length;
        this->data = new char[this.length + 1];
        strcpy(this->data, other.data);
    }

    ~String(){
        delete[] this->data;
    }

    String& operator=(const String& other);

    String operator+(const String& other) const;
    String operator+(const char* string) const;
    friend String operator+(const char* string, const String& object);
    friend String operator+(const char* string1, const char* string2);

    String& operator+=(const String& other);

    char& operator[](int index);
    const char& operator[](int index) const;

    String operator()(int start, int end) const;

    bool operator>(const String& other) const;
    bool operator<(const String& other) const;

    String& operator++();
    String operator++(int);
    String& operator--();
    String operator--(int);

    friend std::ostream& operator<<(std::ostream& os, const String& obj);
    friend std::istream& operator>>(std::istream& is, String& obj);
};