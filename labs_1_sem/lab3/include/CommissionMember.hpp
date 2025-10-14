#ifndef COMMISSION_MEMBER_H
#define COMMISSION_MEMBER_H

#include "../include/Human.hpp"

class CommissionMember : public Human {
private:
    std::string commissionName;
    int appointmentYear;
    std::string certificateNumber;
    std::string* autobiography;
    int autobiographyCount;
public:
    CommissionMember();
    CommissionMember(const std::string& first, const std::string& last, const std::string& middle, int year,
                    const std::string& commission, int appYear, const std::string& cert);
    ~CommissionMember();
    
    CommissionMember& operator=(const CommissionMember& other);
    friend std::ostream& operator<<(std::ostream& os, const CommissionMember& member);
    friend std::istream& operator>>(std::istream& is, CommissionMember& member);
    
    std::string getCommissionName() const;
    int getAppointmentYear() const;
    std::string getCertificateNumber() const;
    std::string* getAutobiography() const;
    int getAutobiographyCount() const;
    
    void setCommissionName(const std::string& name);
    void setAppointmentYear(int year);
    void setCertificateNumber(const std::string& number);
    void setAutobiography(std::string* bio, int count);
    
    void printHeader() const override;
};

#endif