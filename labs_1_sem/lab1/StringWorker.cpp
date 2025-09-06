#include "StringWorker.h"
#include <iostream>
#include <cstring>
#include <cctype>

using namespace std;

// Конструктор без параметров
StringWorker::StringWorker() : data(nullptr), length(0) {}

// Конструктор с C-строкой
StringWorker::StringWorker(const char* data) {
    if (data) {
        this->length = strlen(data);
        this->data = new char[this->length + 1];
        strcpy(this->data, data);
    } else {
        this->length = 0;
        this->data = nullptr;
    }
}

// Конструктор с данными и длиной
StringWorker::StringWorker(const char* data, int length) {
    if (data && length > 0) {
        this->length = length;
        this->data = new char[this->length + 1];
        strncpy(this->data, data, length);
        this->data[length] = '\0';
    } else {
        this->length = 0;
        this->data = nullptr;
    }
}

// Конструктор копирования
StringWorker::StringWorker(const StringWorker& stringCopy) {
    if (stringCopy.data) {
        this->length = stringCopy.length;
        this->data = new char[this->length + 1];
        strcpy(this->data, stringCopy.data);
    } else {
        this->length = 0;
        this->data = nullptr;
    }
}

// Деструктор
StringWorker::~StringWorker() {
    delete[] data;
}

// Метод ввода данных
void StringWorker::initString() {
    cout << "Введите строку: ";
    
    // Временный буфер для ввода
    const int BUFFER_SIZE = 1000;
    char buffer[BUFFER_SIZE];
    cin.getline(buffer, BUFFER_SIZE);
    
    // Освобождаем старую память
    delete[] data;
    
    // Выделяем новую память
    length = strlen(buffer);
    data = new char[length + 1];
    strcpy(data, buffer);
}

// Получение данных
const char* StringWorker::getData() const {
    return data;
}

// Получение длины
int StringWorker::getLength() const {
    return length;
}

// Вывод строки на экран
void StringWorker::showString() const {
    if (data) {
        cout << data;
    }
    cout << endl;
}

// Функция пересечения строк
StringWorker StringWorker::getIntersection(const StringWorker& string1, const StringWorker& string2) {
    if (!string1.data || !string2.data) {
        return StringWorker();
    }
    
    // Временный буфер для результата
    char result[1000] = {0};
    int resultIndex = 0;
    
    const char* str1 = string1.data;
    const char* str2 = string2.data;
    
    // Проходим по всем символам первой строки
    for (int i = 0; i < string1.length; i++) {
        char currentChar = str1[i];
        
        // Проверяем, есть ли символ во второй строке и еще не добавлен в результат
        bool foundInSecond = false;
        for (int j = 0; j < string2.length; j++) {
            if (str2[j] == currentChar) {
                foundInSecond = true;
                break;
            }
        }
        
        // Проверяем, не добавлен ли уже этот символ в результат
        bool alreadyAdded = false;
        for (int k = 0; k < resultIndex; k++) {
            if (result[k] == currentChar) {
                alreadyAdded = true;
                break;
            }
        }
        
        if (foundInSecond && !alreadyAdded) {
            result[resultIndex++] = currentChar;
        }
    }
    
    result[resultIndex] = '\0';
    
    return StringWorker(result);
}