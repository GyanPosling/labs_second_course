#include "Array.h"
using namespace std;

Array::Array() : data(nullptr), size(0) {}

Array::Array(int* array, int arraySize) {
    size = arraySize;
    data = new int[size];
    for (int i = 0; i < size; i++) {
        data[i] = array[i];
    }
}

Array::Array(int size) : size(size) {
    data = new int[size];
    for (int i = 0; i < size; i++) {
        data[i] = 0;
    }
}

Array::Array(const Array& other) {
    size = other.size;
    data = new int[size];
    for (int i = 0; i < size; i++) {
        data[i] = other.data[i];
    }
}

Array& Array::operator=(const Array& other) {
    if (this != &other) {
        delete[] this->data;
        this->size = other.size;
        data = new int[size];
        for (int i = 0; i < this->size; i++) {
            this->data[i] = other.data[i];
        }
    }
    return *this;
}

Array::~Array() {
    delete[] data;
}

const int* Array::getData() const {
    return data;
}

int* Array::getData() {
    return data; 
}

int Array::getSize() const {
    return size;
}

void Array::print() const {
    cout << "[";
    for (int i = 0; i < size; i++) {
        cout << data[i];
        if (i < size - 1) cout << ", ";
    }
    cout << "]" << endl;
}

Array& Array::operator&(const Array& other) {
    Array tempArray((this->getSize() < other.getSize()) ? this->getSize() : other.getSize());

    int resultSize = 0;
    
    for (int i = 0; i < this->getSize(); i++) {
        for (int j = 0; j < other.getSize(); j++) {
            if (this->getData()[i] == other.getData()[j]) {
                bool duplicate = false;
                for (int k = 0; k < resultSize; k++) {
                    if (tempArray.getData()[k] == this->getData()[i]) {
                        duplicate = true;
                        break;
                    }
                }
                if (!duplicate) {
                    tempArray.getData()[resultSize++] = this->getData()[i];
                }
                break;
            }
        }
    }
    
    Array resultArray(resultSize);
    for (int i = 0; i < resultSize; i++) {
        resultArray.getData()[i] = tempArray.getData()[i];
    }

    *this = resultArray;
    return *this;
}