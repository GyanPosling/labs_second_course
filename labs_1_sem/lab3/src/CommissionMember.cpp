#include "../include/CommissionMember.hpp"

CommissionMember::CommissionMember() : Human(), appointmentYear(0), autobiographyCount(0) {}

CommissionMember::CommissionMember(const std::string& first, const std::string& last, const std::string& middle, int year,
                                   const std::string& commission, int appYear, const std::string& cert)
    : Human(first, last, middle, year), commissionName(commission), appointmentYear(appYear), certificateNumber(cert), autobiographyCount(0) {}

CommissionMember::~CommissionMember() {}

CommissionMember& CommissionMember::operator=(const CommissionMember& other) {
    if (this != &other) {
        Human::operator=(other);
        this->commissionName = other.commissionName;
        this->appointmentYear = other.appointmentYear;
        this->certificateNumber = other.certificateNumber;
        this->autobiographyCount = other.autobiographyCount;
        for (int i = 0; i < this->autobiographyCount; i++) {
            this->autobiography[i] = other.autobiography[i];
        }
    }
    return *this;
}

std::ostream& operator<<(std::ostream& os, const CommissionMember& member) {
    os << static_cast<const Human&>(member) << " " << member.commissionName << " " << member.appointmentYear << " " << member.certificateNumber;
    for (int i = 0; i < member.autobiographyCount; i++) {
        os << " " << member.autobiography[i];
    }
    return os;
}

std::istream& operator>>(std::istream& is, CommissionMember& member) {
    is >> static_cast<Human&>(member) >> member.commissionName >> member.appointmentYear >> member.certificateNumber;
    return is;
}

std::string CommissionMember::getCommissionName() const { return this->commissionName; }
int CommissionMember::getAppointmentYear() const { return this->appointmentYear; }
std::string CommissionMember::getCertificateNumber() const { return this->certificateNumber; }
std::string CommissionMember::getAutobiography(int index) const { 
    if (index >= 0 && index < this->autobiographyCount) return this->autobiography[index];
    return "";
}
int CommissionMember::getAutobiographyCount() const { return this->autobiographyCount; }
int CommissionMember::getAutobiographySize() const { return AUTOBIOGRAPHY_SIZE; }

void CommissionMember::setCommissionName(const std::string& name) { this->commissionName = name; }
void CommissionMember::setAppointmentYear(int year) { this->appointmentYear = year; }
void CommissionMember::setCertificateNumber(const std::string& number) { this->certificateNumber = number; }
void CommissionMember::setAutobiography(int index, const std::string& bio) { 
    if (index >= 0 && index < AUTOBIOGRAPHY_SIZE) {
        this->autobiography[index] = bio;
        if (index >= this->autobiographyCount) {
            this->autobiographyCount = index + 1;
        }
    }
}
void CommissionMember::addAutobiography(const std::string& bio) {
    if (this->autobiographyCount < AUTOBIOGRAPHY_SIZE) {
        this->autobiography[this->autobiographyCount] = bio;
        this->autobiographyCount++;
    }
}

void CommissionMember::printHeader() const {
    std::cout << "Commission Member: " << this->lastName << " " << this->firstName << " " << this->middleName << "\n";
}