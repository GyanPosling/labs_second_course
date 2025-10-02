#pragma once
#include <iostream>
#include <cstring>

class String {
private:
    char* data;
    int length;

public:
    String() : data(nullptr), length(0) {}              //конструктор по умолчанию

    String(const char* str) {                           //конструктор с параметорм(строка)
        this->length = strlen(str);
        this->data = new char[this->length + 1];
        strcpy(this->data, str);
    }

    explicit String(int size) : length(size) {          //конструктор с параметорм(размер)
        this->data = new char[this->length + 1];
        for (int i = 0; i <= this->length; i++) {
            this->data[i] = '\0';
        }
    }

    String(const String& other) {                      //конструктор копирования
        this->length = other.length;
        this->data = new char[this->length + 1];
        strcpy(this->data, other.data);
    }

    ~String() {                                       //деструктор
        delete[] this->data;
    }

    String& operator=(const String& other);            //переопределения присваивания

    String operator+(const String& other) const;                    // объект + объект
    String operator+(const char* str) const;                        //объект + строка
    friend String operator+(const char* str, const String& obj);    //строка + объект
    String operator-(const String& other) const;                    // объект - объект
    String operator-(const char* string) const;                     // объект - строка
    friend String operator-(const char* string, const String& object);//строка - объект

    String& operator+=(const String& other);                        //Объект += Объект
    String& operator+=(const char *string);                         // объект += строка
    String& operator-=(const String& other);                        // объект -= объект
    String& operator-=(const char* string);                         // объект -= строка

    String operator*(int multiplyDigit) const;                      // объект * число (умножение строки)
    String& operator*=(int multiplyDigit);                          // объект *= число

    char& operator[](int index);                                    // доступ по индексу (неконстантный)
    const char& operator[](int index) const;                        // доступ по индексу (константный)

    String operator()(int start, int end) const;                    // получение подстроки

    bool operator>(const String& other) const;                      // сравнение > (по длине)
    bool operator<(const String& other) const;                      // сравнение < (по длине)
    bool operator==(const String& other) const;                     // сравнение == (по содержимому)
    bool operator!=(const String& other) const;                     // сравнение != (по содержимому)
    bool operator>=(const String& other) const;                     // сравнение >= (по длине)
    bool operator<=(const String& other) const;                     // сравнение <= (по длине)

    String& operator++();                                           // префиксный инкремент
    String operator++(int);                                         // постфиксный инкремент
    String& operator--();                                           // префиксный декремент
    String operator--(int);                                         // постфиксный декремент

    friend std::ostream& operator<<(std::ostream& os, const String& obj);  // вывод в поток
    friend std::istream& operator>>(std::istream& is, String& obj);        // ввод из потока

};