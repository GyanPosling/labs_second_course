#pragma once

#include "BinaryFile.hpp"
#include <fstream>
#include <string>
#include "../templates/include/Deque.hpp"

using namespace std;

template <typename T>
void BinaryFile<T>::saveRecord(const T& object) {
    fstream file;
    openFile(file, ios::out | ios::app | ios::binary);
    if (file.is_open()) {
        object.saveBinaryRecord(file);
    }
}

template <typename T>
T* BinaryFile<T>::readRecord() {
    fstream file;
    openFile(file, ios::in | ios::binary);
    if (!file.is_open()) {
        return nullptr;
    }
    
    if (file.peek() == EOF) {
        return nullptr;
    }
    
    T* object = new T();
    object->loadFromBinary(file);
    return object;
}

template <typename T>
Deque<T*> BinaryFile<T>::readAllRecords() {
    Deque<T*> deque;
    fstream file;
    openFile(file, ios::in | ios::binary);
    
    if (!file.is_open()) {
        return deque;
    }
    
    while (file.peek() != EOF) {
        T* object = new T();
        try {
            object->loadFromBinary(file);
            deque.pushBack(object);
        } catch (...) {
            delete object;
            break;
        }
    }
    
    return deque;
}

template <typename T>
void BinaryFile<T>::clearFile() const {
    ofstream file(filename, ios::out | ios::trunc | ios::binary);
}

template <typename T>
void BinaryFile<T>::openFile(fstream& file, ios_base::openmode mode) const {
    file.open(filename, mode);
    if (!file.is_open()) {
        throw FileException(60, "Failed to open file: " + filename);
    }
}