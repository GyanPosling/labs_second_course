#ifndef HUMAN_H
#define HUMAN_H

#include <iostream>
#include <string>

class Human {
protected:
    std::string firstName;
    std::string lastName;
    std::string middleName;
    int birthYear;
public:
    Human();
    Human(const std::string& first, const std::string& last, const std::string& middle, int year);
    virtual ~Human();
    
    Human& operator=(const Human& other);
    friend std::ostream& operator<<(std::ostream& os, const Human& human);
    friend std::istream& operator>>(std::istream& is, Human& human);
    
    std::string getFirstName() const;
    std::string getLastName() const;
    std::string getMiddleName() const;
    int getBirthYear() const;
    
    void setFirstName(const std::string& first);
    void setLastName(const std::string& last);
    void setMiddleName(const std::string& middle);
    void setBirthYear(int year);
    
    virtual void printHeader() const = 0;
};

#endif