#include <iostream>
#include <cstdlib>
#include <cstring>
#include "performLab.h"
#include "StringWorker.h"


using namespace std;


void printLabHeader() {
    std::cout <<  "\n+---------------------------------------------------------+\n"
                    "|                                                         |\n"
                    "|               Лабораторная работа №1                    |\n"
                    "|                                                         |\n"
                    "|               Тема: Классы и объекты                    |\n"
                    "|                                                         |\n"
                    "|  Задача: Реализовать класс, выполняющий пересчение строк|\n"
                    "|                                                         |\n"
                    "|   Код должен выполнять следующие условия:               |\n"
                    "|     - Деление программы на заголовочные файлы           |\n"
                    "|     - Каждый класс в отдельном .h и .cpp файле          |\n"
                    "|     - Отдельный .cpp файл для main                      |\n"
                    "|                                                         |\n"
                    "|   Автор: Бурш Антон                                     |\n"
                    "|                                                         |\n"
                    "+---------------------------------------------------------+\n";

}

char* initString(const char* prompt) {
    cout << prompt;
    char buffer[1024];
    if (!cin.getline(buffer, sizeof(buffer))) return nullptr;
    char* result = new char[strlen(buffer) + 1];
    strcpy(result, buffer);
    return result;
}

char getValidInput(char min, char max) {
    string input;
    while (true) {
        getline(cin, input);
        
        if (input.length() != 1) {
            cout << "Error! Enter exactly ONE character.\nTry again: ";
            continue;
        }
        
        if (input[0] < min || input[0] > max) {
            cout << "Error! Character must be between '" 
                 << min << "' and '" << max << "'.\nTry again: ";
            continue;
        }
        
        return input[0];
    }
}

void drawMenu() {

    cout << "\n+---------------------------+\n";
    cout << "| 1. Print strings          |\n";
    cout << "| 2. Get intersection       |\n";
    cout << "| 3. Clear and re-enter     |\n";
    cout << "| 0. Exit                   |\n";
    cout << "+---------------------------+\n";
    cout << "Your choice: ";
}

void performTask() {

    printLabHeader();
    char* d1 = initString("Enter first string: ");
    char* d2 = initString("Enter second string: ");
    StringWorker worker(d1, d2);
    delete[] d1;
    delete[] d2;

    char choice;
    do {
        drawMenu();
        choice = getValidInput('0', '3');
        if (choice == '1') {
            worker.printStrings();
        } else if (choice == '2') {
            char* inter = worker.getIntersection();
            if (inter) {
                cout << "Intersection: " << inter << endl;
                delete[] inter;
            } else {
                cout << "No intersection." << endl;
            }
        } else if (choice == '3') {
            worker.clearStrings();
            d1 = initString("Enter first string: ");
            d2 = initString("Enter second string: ");
            worker = StringWorker (d1, d2);
            delete[] d1;
            delete[] d2;
        }
    } while (choice != '0');
}

// ---------------------------------------------------------------------------------------------

//!!!!! ПРИМЕР С ИСПОЛЬЗОВАНИЕМ КОНСТРУКТОРА ПО УМОЛЧАНИЮ

// void performTaskWithDefaultConstructor() {
//     printLabHeader();
//     StringWorker worker;
    
//     char* d1 = initString("Enter first string: ");
//     char* d2 = initString("Enter second string: ");
    
//     worker.setFirstString(d1);
//     worker.setSecondString(d2);
//     delete[] d1;
//     delete[] d2;

//     char choice;
//     do {
//         drawMenu();
//         choice = getValidInput('0', '3');
//         if (choice == '1') {
//             worker.printStrings();
//         } else if (choice == '2') {
//             char* inter = worker.getIntersection();
//             if (inter) {
//                 cout << "Intersection: " << inter << endl;
//                 delete[] inter;
//             } else {
//                 cout << "No intersection." << endl;
//             }
//         } else if (choice == '3') {
//             worker.clearStrings();
//             d1 = initString("Enter first string: ");
//             d2 = initString("Enter second string: ");
//             worker.setFirstString(d1);
//             worker.setSecondString(d2);
//             delete[] d1;
//             delete[] d2;
//         }
//     } while (choice != '0');
// }

// --------------------------------------------------------------------------------------------------------


// !!! ПРИМЕР С ИСПОЛЬЗОВАНИЕМ КОСТРУКТОРА КОПИРОВАНИЯ

// void performTaskWithCopyConstructor() {
//     printLabHeader();
//     char* d1 = initString("Enter first string: ");
//     char* d2 = initString("Enter second string: ");
    
//     StringWorker original(d1, d2);
//     delete[] d1;
//     delete[] d2;

//     StringWorker worker(original);

//     char choice;
//     do {
//         drawMenu();
//         choice = getValidInput('0', '3');
//         if (choice == '1') {
//             worker.printStrings();
//         } else if (choice == '2') {
//             char* inter = worker.getIntersection();
//             if (inter) {
//                 cout << "Intersection: " << inter << endl;
//                 delete[] inter;
//             } else {
//                 cout << "No intersection." << endl;
//             }
//         } else if (choice == '3') {
//             worker.clearStrings();
//             d1 = initString("Enter first string: ");
//             d2 = initString("Enter second string: ");
//             worker.setFirstString(d1);
//             worker.setSecondString(d2);
//             delete[] d1;
//             delete[] d2;
//         }
//     } while (choice != '0');
// }