#pragma once
#include <iostream>
#include <cstring>

class StringWorker {
private:
    char* data1;
    char* data2;

public:
    StringWorker(); //контруктор по умолчанию
    StringWorker(const char* data1, const char* data2);// конструктор с двумя параметрами
    StringWorker(const StringWorker& other);// конструктор копирования
    StringWorker& operator=(const StringWorker& other);// переопределение оператора = 
    ~StringWorker(); // деструктор

    //геттеры
    const char* getFirstData() const;
    const char* getSecondData() const;
    int getFirstLength() const;
    int getSecondLength() const;

    //сеттеры
    void setFirstString(const char* data);
    void setSecondString(const char* data);

    short isEmpty() const;
    void printStrings() const;
    void clearStrings();

    //функция пересечния строк
    char* getIntersection() const;
};
