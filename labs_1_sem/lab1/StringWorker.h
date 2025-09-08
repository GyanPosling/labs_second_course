#pragma once
#include <iostream>
#include <cstring>

class StringWorker {
private:
    char* data1;
    char* data2;

public:
    StringWorker();
    StringWorker(const char* data1, const char* data2);
    StringWorker(const StringWorker& other);
    StringWorker& operator=(const StringWorker& other);
    ~StringWorker();

    const char* getFirstData() const;
    const char* getSecondData() const;
    int getFirstLength() const;
    int getSecondLength() const;

    void setFirstString(const char* data);
    void setSecondString(const char* data);

    bool isEmpty() const;
    void printStrings() const;
    void clearStrings();

    char* getIntersection() const;
};
