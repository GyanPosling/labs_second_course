#include <iostream>
#include "Array.h"

using namespace std;

int* initArray(const char* prompt, int& size) {
    cout << prompt;
    cout << "Enter array size: ";
    cin >> size;
    
    int* result = new int[size];
    cout << "Enter " << size << " elements: ";
    for (int i = 0; i < size; i++) {
        cin >> result[i];
    }
    cin.ignore();
    return result;
}

void performIntersection() {
    int count;
    cout << "Enter number of arrays: ";
    cin >> count;
    cin.ignore();
    
    Array* arrays = new Array[count];
    for (int i = 0; i < count; i++) {
        int size;
        int* input = initArray("Array initialization: \n", size);
        arrays[i] = Array(input, size);
        delete[] input;
    }
    
    Array result = arrays[0];
    for (int i = 1; i < count; i++) {
        result = result & arrays[i];
    }
    
    cout << "Intersection: ";
    result.print();
    
    delete[] arrays;
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
        cin.ignore();
    } while (restart == 1);

    cout << "Exiting...";
    
    return 0;
}