#include "../include/TeacherCommissionMember.hpp"
#include <iostream>

TeacherCommissionMember::TeacherCommissionMember() : UniversityTeacher(), CommissionMember(), commissionWorks(nullptr), commissionWorksCount(0) {}

TeacherCommissionMember::TeacherCommissionMember(const std::string& first, const std::string& last, const std::string& middle, int year,
                                                 const std::string& pos, const std::string& degree, const std::string& spec,
                                                 const std::string& commission, int appYear, const std::string& cert)
    : UniversityTeacher(first, last, middle, year, pos, degree, spec),
      CommissionMember(first, last, middle, year, commission, appYear, cert), commissionWorks(nullptr), commissionWorksCount(0) {}

TeacherCommissionMember::~TeacherCommissionMember() {
    delete[] this->commissionWorks;
}

TeacherCommissionMember& TeacherCommissionMember::operator=(const TeacherCommissionMember& other) {
    if (this != &other) {
        UniversityTeacher::operator=(other);
        CommissionMember::operator=(other);
        
        delete[] this->commissionWorks;
        this->commissionWorksCount = other.commissionWorksCount;
        this->commissionWorks = new std::string[this->commissionWorksCount];
        for (int i = 0; i < this->commissionWorksCount; i++) {
            this->commissionWorks[i] = other.commissionWorks[i];
        }
    }
    return *this;
}

std::ostream& operator<<(std::ostream& os, const TeacherCommissionMember& tcm) {
    os << static_cast<const UniversityTeacher&>(tcm) << " " << static_cast<const CommissionMember&>(tcm);
    for (int i = 0; i < tcm.commissionWorksCount; i++) {
        os << " " << tcm.commissionWorks[i];
    }
    return os;
}

std::istream& operator>>(std::istream& is, TeacherCommissionMember& tcm) {
    is >> static_cast<UniversityTeacher&>(tcm) >> static_cast<CommissionMember&>(tcm);
    return is;
}

std::string* TeacherCommissionMember::getCommissionWorks() const { return this->commissionWorks; }
int TeacherCommissionMember::getCommissionWorksCount() const { return this->commissionWorksCount; }
void TeacherCommissionMember::setCommissionWorks(std::string* works, int count) {
    delete[] this->commissionWorks;
    this->commissionWorksCount = count;
    this->commissionWorks = new std::string[this->commissionWorksCount];
    for (int i = 0; i < this->commissionWorksCount; i++) {
        this->commissionWorks[i] = works[i];
    }
}

void TeacherCommissionMember::printHeader() const {
    std::cout << "Teacher Commission Member: " << UniversityTeacher::getLastName() << " " << UniversityTeacher::getFirstName() << " " << UniversityTeacher::getMiddleName() << "\n";
}