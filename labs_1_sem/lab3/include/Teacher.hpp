#ifndef TEACHER_H
#define TEACHER_H

#include "../include/Human.hpp"

class UniversityTeacher : public Human {
private:
    std::string position;
    std::string academicDegree;
    std::string specialty;
    std::string* scientificWorks;
    int worksCount;
public:
    UniversityTeacher();
    UniversityTeacher(const std::string& first, const std::string& last, const std::string& middle, int year,
                     const std::string& pos, const std::string& degree, const std::string& spec);
    ~UniversityTeacher();
    
    UniversityTeacher& operator=(const UniversityTeacher& other);
    friend std::ostream& operator<<(std::ostream& os, const UniversityTeacher& teacher);
    friend std::istream& operator>>(std::istream& is, UniversityTeacher& teacher);
    
    std::string getPosition() const;
    std::string getAcademicDegree() const;
    std::string getSpecialty() const;
    std::string* getScientificWorks() const;
    int getWorksCount() const;
    
    void setPosition(const std::string& pos);
    void setAcademicDegree(const std::string& degree);
    void setSpecialty(const std::string& spec);
    void setScientificWorks(std::string* works, int count);
    
    void printHeader() const override;
};

#endif