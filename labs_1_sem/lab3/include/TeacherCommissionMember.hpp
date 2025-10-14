#ifndef TEACHER_COMMISSION_MEMBER_H
#define TEACHER_COMMISSION_MEMBER_H

#include "../include/Teacher.hpp"
#include "../include/CommissionMember.hpp"

class TeacherCommissionMember : public UniversityTeacher, public CommissionMember {
private:
    std::string* commissionWorks;
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
    
    std::string* getCommissionWorks() const;
    int getCommissionWorksCount() const;
    void setCommissionWorks(std::string* works, int count);
    
    void printHeader() const override;
};

#endif