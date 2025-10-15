#ifndef TEACHER_HPP
#define TEACHER_HPP

#include "../include/Human.hpp"

#define SCIENTIFIC_WORKS_SIZE 5

class UniversityTeacher : public Human {
private:
    std::string position;
    std::string academicDegree;
    std::string specialty;
    std::string scientificWorks[SCIENTIFIC_WORKS_SIZE];
    int scientificWorksCount;
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
    std::string getScientificWork(int index) const;
    int getScientificWorksCount() const;
    int getScientificWorksSize() const;
    
    void setPosition(const std::string& pos);
    void setAcademicDegree(const std::string& degree);
    void setSpecialty(const std::string& spec);
    void setScientificWork(int index, const std::string& work);
    void addScientificWork(const std::string& work);
    
    void printHeader() const override;
};

#endif