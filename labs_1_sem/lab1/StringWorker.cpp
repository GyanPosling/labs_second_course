#include "StringWorker.h"

StringWorker::StringWorker() : data1(nullptr), data2(nullptr) {}

StringWorker::StringWorker(const char* d1, const char* d2) {
    data1 = d1 ? new char[strlen(d1) + 1] : nullptr;
    data2 = d2 ? new char[strlen(d2) + 1] : nullptr;
    if (data1) strcpy(data1, d1);
    if (data2) strcpy(data2, d2);
}

StringWorker::StringWorker(const StringWorker& other) {
    data1 = other.data1 ? new char[strlen(other.data1) + 1] : nullptr;
    data2 = other.data2 ? new char[strlen(other.data2) + 1] : nullptr;
    if (data1) strcpy(data1, other.data1);
    if (data2) strcpy(data2, other.data2);
}

StringWorker& StringWorker::operator=(const StringWorker& other) {
    if (this != &other) {
        clearStrings();
        data1 = other.data1 ? new char[strlen(other.data1) + 1] : nullptr;
        data2 = other.data2 ? new char[strlen(other.data2) + 1] : nullptr;
        if (data1) strcpy(data1, other.data1);
        if (data2) strcpy(data2, other.data2);
    }
    return *this;
}

StringWorker::~StringWorker() {
    clearStrings();
}

const char* StringWorker::getFirstData() const { return data1; }
const char* StringWorker::getSecondData() const { return data2; }
int StringWorker::getFirstLength() const { return data1 ? strlen(data1) : 0; }
int StringWorker::getSecondLength() const { return data2 ? strlen(data2) : 0; }

void StringWorker::setFirstString(const char* d) {
    delete[] data1;
    data1 = d ? new char[strlen(d) + 1] : nullptr;
    if (data1) strcpy(data1, d);
}

void StringWorker::setSecondString(const char* d) {
    delete[] data2;
    data2 = d ? new char[strlen(d) + 1] : nullptr;
    if (data2) strcpy(data2, d);
}

bool StringWorker::isEmpty() const {
    return (!data1 || !*data1) && (!data2 || !*data2);
}

void StringWorker::printStrings() const {
    std::cout << "First: " << (data1 ? data1 : "") << "\n";
    std::cout << "Second: " << (data2 ? data2 : "") << "\n";
}

void StringWorker::clearStrings() {
    delete[] data1;
    delete[] data2;
    data1 = nullptr;
    data2 = nullptr;
}

char* StringWorker::getIntersection() const {
    if (!data1 || !data2) return nullptr;
    char* result = new char[strlen(data1) + 1];
    int k = 0;
    for (int i = 0; data1[i]; i++) {
        for (int j = 0; data2[j]; j++) {
            if (data1[i] == data2[j]) {
                bool exists = false;
                for (int m = 0; m < k; m++) {
                    if (result[m] == data1[i]) {
                        exists = true;
                        break;
                    }
                }
                if (!exists) result[k++] = data1[i];
                break;
            }
        }
    }
    result[k] = '\0';
    return result;
}
