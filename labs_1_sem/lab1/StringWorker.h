#pragma once

class StringWorker {
    
    private:
        char *data;
        int length;

    public:
        StringWorker();
        StringWorker(char *data);
        StringWorker(char *data, int length);
        StringWorker(const StringWorker &stringCopy);

        ~StringWorker();

        char *initString();
        const char *getData(); 
        int getLength();
        void showString(const char *data);

        static StringWorker getIntersection(const StringWorker &string1, const StringWorker &string2);
};