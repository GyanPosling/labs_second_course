#pragma once

#include "TextFile.hpp"
#include <fstream>
#include <string>
#include "../templates/include/Deque.hpp"

using namespace std;

template <typename T>
void TextFile<T>::saveRecord(const T& object) {
    fstream file;
    openFile(file, ios::out | ios::app);
    if (file.is_open()) {
        object.saveTextRecord(file);
        file << "\n";
    }
}

template <typename T>
T* TextFile<T>::readRecord() {
    fstream file;
    openFile(file, ios::in);
    if (!file.is_open()) {
        return nullptr;
    }
    
    if (file.peek() == EOF) {
        return nullptr;
    }
    
    T* object = new T();
    object->loadFromText(file);
    
    string dummy;
    getline(file, dummy);
    
    return object;
}

template <typename T>
Deque<T*> TextFile<T>::readAllRecords() {
    Deque<T*> deque;
    fstream file;
    openFile(file, ios::in);
    
    if (!file.is_open()) {
        return deque;
    }
    
    while (file.peek() != EOF) {
        T* object = new T();
        object->loadFromText(file);
        deque.pushBack(object);
        
        string dummy;
        getline(file, dummy);
    }
    
    return deque;
}

template <typename T>
void TextFile<T>::clearFile() const {
    ofstream file(filename, ios::out | ios::trunc);
}

template <typename T>
void TextFile<T>::openFile(fstream& file, ios_base::openmode mode) const {
    file.open(filename, mode);
    if (!file.is_open()) {
        throw FileException(50, "Failed to open file: " + filename);
    }
}