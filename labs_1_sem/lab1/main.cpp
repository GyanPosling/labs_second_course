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

void performIntersection() {
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


void printRestartBox() {
    cout << "+------------------------------+\n";
    cout << "|   Restart? (1 = Yes, 0 = No) |\n";
    cout << "+------------------------------+\n";
    cout << "Answer: ";
}


int main() {
    int restart = 1;
    
    do {
        performIntersection();
        printRestartBox();
        cin >> restart;
    } while (restart == 1);

    cout<<"Exiting...";
    
    return 0;
}
