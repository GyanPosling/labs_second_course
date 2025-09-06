#include <iostream>
#include "StringWorker.h"

using namespace std;

int main() {
    cout << "=== Лабораторная работа: Класс StringWorker ===" << endl;
    
    // Демонстрация разных конструкторов
    cout << "\n1. Создание объектов:" << endl;
    
    StringWorker str1;                          // конструктор без параметров
    StringWorker str2("Hello, World!");         // конструктор с C-строкой
    StringWorker str3("Test String", 4);        // конструктор с длиной ("Test")
    StringWorker str4(str2);                    // конструктор копирования
    
    cout << "str2: ";
    str2.showString();
    cout << "str3 (первые 4 символа): ";
    str3.showString();
    cout << "str4 (копия str2): ";
    str4.showString();
    
    // Ввод данных
    cout << "\n2. Ввод данных для str1:" << endl;
    str1.initString();
    
    cout << "\n3. Ввод данных для новой строки:" << endl;
    StringWorker str5;
    str5.initString();
    
    // Вывод всех строк
    cout << "\n4. Все строки:" << endl;
    cout << "str1: ";
    str1.showString();
    cout << "str2: ";
    str2.showString();
    cout << "str5: ";
    str5.showString();
    
    // Демонстрация получения длины и данных
    cout << "\n5. Информация о строках:" << endl;
    cout << "Длина str1: " << str1.getLength() << " символов" << endl;
    cout << "Длина str2: " << str2.getLength() << " символов" << endl;
    cout << "Данные str2: " << str2.getData() << endl;
    
    // Пересечение строк
    cout << "\n6. Пересечение символов:" << endl;
    StringWorker intersection1 = StringWorker::getIntersection(str1, str2);
    cout << "Пересечение str1 и str2: ";
    intersection1.showString();
    
    StringWorker intersection2 = StringWorker::getIntersection(str1, str5);
    cout << "Пересечение str1 и str5: ";
    intersection2.showString();
    
    cout << "\n=== Программа завершена ===" << endl;
    
    return 0;
}