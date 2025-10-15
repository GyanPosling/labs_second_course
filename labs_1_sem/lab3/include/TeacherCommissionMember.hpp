#ifndef TEACHER_COMMISSION_MEMBER_H
#define TEACHER_COMMISSION_MEMBER_H

#include "../include/Teacher.hpp"
#include "../include/CommissionMember.hpp"

#define COMMISSION_WORKS_SIZE 5

class TeacherCommissionMember : public UniversityTeacher, public CommissionMember {
private:
    std::string commissionWorks[COMMISSION_WORKS_SIZE];
    int commissionWorksCount;
public:
    TeacherCommissionMember();
    TeacherCommissionMember(const std::string& first, const std::string& last, const std::string& middle, int year,
                           const std::string& pos, const std::string& degree, const std::string& spec,
                           const std::string& commission, int appYear, const std::string& cert);
    ~TeacherCommissionMember();
    
    TeacherCommissionMember& operator=(const TeacherCommissionMember& other);
    friend std::ostream& operator<<(std::ostream& os, const TeacherCommissionMember& tcm);
    friend std::istream& operator>>(std::istream& is, TeacherCommissionMember& tcm);
    
    std::string getCommissionWork(int index) const;
    int getCommissionWorksCount() const;
    int getCommissionWorksSize() const;
    void setCommissionWork(int index, const std::string& work);
    void addCommissionWork(const std::string& work);
    
    void printHeader() const override;
};

#endif