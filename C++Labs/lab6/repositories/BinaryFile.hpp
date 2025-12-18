#pragma once

#include "File.hpp"
#include <fstream>
#include <string>
#include "../templates/include/Deque.hpp"

using namespace std;

template <typename T>
class BinaryFile : public File
{
public:
    BinaryFile(const string& fname) : File(fname) {}
    ~BinaryFile() = default;

    void saveRecord(const T& object);
    T* readRecord();
    Deque<T*> readAllRecords();
    void clearFile() const;
    void openFile(fstream& file, ios_base::openmode mode) const;
};

#include "BinaryFile.tpp"