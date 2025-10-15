#include "../include/TeacherCommissionMember.hpp"
#include <iostream>


TeacherCommissionMember::TeacherCommissionMember() : UniversityTeacher(), CommissionMember(), commissionWorksCount(0) {}

TeacherCommissionMember::TeacherCommissionMember(const std::string& first, const std::string& last, const std::string& middle, int year,
                                                 const std::string& pos, const std::string& degree, const std::string& spec,
                                                 const std::string& commission, int appYear, const std::string& cert)
    : UniversityTeacher(first, last, middle, year, pos, degree, spec),
      CommissionMember(first, last, middle, year, commission, appYear, cert), commissionWorksCount(0) {}

TeacherCommissionMember::~TeacherCommissionMember() {}

TeacherCommissionMember& TeacherCommissionMember::operator=(const TeacherCommissionMember& other) {
    if (this != &other) {
        UniversityTeacher::operator=(other);
        CommissionMember::operator=(other);
        this->commissionWorksCount = other.commissionWorksCount;
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

std::string TeacherCommissionMember::getCommissionWork(int index) const { 
    if (index >= 0 && index < this->commissionWorksCount) return this->commissionWorks[index];
    return "";
}
int TeacherCommissionMember::getCommissionWorksCount() const { return this->commissionWorksCount; }
int TeacherCommissionMember::getCommissionWorksSize() const { return COMMISSION_WORKS_SIZE; }
void TeacherCommissionMember::setCommissionWork(int index, const std::string& work) { 
    if (index >= 0 && index < COMMISSION_WORKS_SIZE) {
        this->commissionWorks[index] = work;
        if (index >= this->commissionWorksCount) {
            this->commissionWorksCount = index + 1;
        }
    }
}
void TeacherCommissionMember::addCommissionWork(const std::string& work) {
    if (this->commissionWorksCount < COMMISSION_WORKS_SIZE) {
        this->commissionWorks[this->commissionWorksCount] = work;
        this->commissionWorksCount++;
    }
}

void TeacherCommissionMember::printHeader() const {
    std::cout << "Teacher Commission Member: " << this->UniversityTeacher::getLastName() << " " << this->UniversityTeacher::getFirstName() << " " << this->UniversityTeacher::getMiddleName() << "\n";
}