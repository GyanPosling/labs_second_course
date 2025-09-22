#include <iostream>
#include "MyString.h"
#include <string.h>
using namespace std;

char* initString(const char* prompt) {
    cout << prompt;
    char buffer[1024];
    if (!cin.getline(buffer, sizeof(buffer))) return nullptr;
    char* result = new char[strlen(buffer) + 1];
    strcpy(result, buffer);
    return result;
}

void demonstrateIntersection() {
    MyString str1("hello");
    MyString str2("world");
    MyString str3("loop");
    
    cout << "String 1: "; str1.print();
    cout << "String 2: "; str2.print();
    cout << "String 3: "; str3.print();
    
    MyString result = str1;
    result.intersectWith(str2).intersectWith(str3);
    
    cout << "Intersection: ";
    result.print();
}

void interactiveMode() {
    int count;
    cout << "Enter number of strings: ";
    cin >> count;
    cin.ignore();
    
    MyString* strings = new MyString[count];
    for (int i = 0; i < count; i++) {
        char* input = initString("Enter string: ");
        strings[i] = MyString(input);
        delete[] input;
    }
    
    MyString result = strings[0];
    for (int i = 1; i < count; i++) {
        result.intersectWith(strings[i]);
    }
    
    cout << "Intersection: ";
    result.print();
    
    delete[] strings;
}

void printMenu() {
    cout << "+----------------------------+\n";
    cout << "|          M E N U           |\n";
    cout << "+----------------------------+\n";
    cout << "| 1. Demonstration           |\n";
    cout << "| 2. Interactive Mode        |\n";
    cout << "| 0. Exit                    |\n";
    cout << "+----------------------------+\n";
    cout << "Choice: ";
}

void printRestartBox() {
    cout << "+------------------------------+\n";
    cout << "|   Restart? (1 = Yes, 0 = No) |\n";
    cout << "+------------------------------+\n";
    cout << "Answer: ";
}

void run() {
    int restart;
    
    do {
        char choice;
        printMenu();
        cin >> choice;
        cin.ignore();
        
        if (choice == '1') demonstrateIntersection();
        else if (choice == '2') interactiveMode();
        
        if (choice != '0') {
            printRestartBox();
            cin >> restart;
            cin.ignore();
        } else {
            restart = 0;
        }
    } while (restart == 1);

    cout<<"Exiting...";
}

int main() {
    run();
    return 0;
}
