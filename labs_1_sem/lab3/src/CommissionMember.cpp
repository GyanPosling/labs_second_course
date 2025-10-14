#include "../include/CommissionMember.hpp"

CommissionMember::CommissionMember() : Human(), autobiography(nullptr), autobiographyCount(0) {}

CommissionMember::CommissionMember(const std::string& first, const std::string& last, const std::string& middle, int year,
                                   const std::string& commission, int appYear, const std::string& cert)
    : Human(first, last, middle, year), commissionName(commission), appointmentYear(appYear), certificateNumber(cert), autobiography(nullptr), autobiographyCount(0) {}

CommissionMember::~CommissionMember() {
    delete[] this->autobiography;
}

CommissionMember& CommissionMember::operator=(const CommissionMember& other) {
    if (this != &other) {
        Human::operator=(other);
        this->commissionName = other.commissionName;
        this->appointmentYear = other.appointmentYear;
        this->certificateNumber = other.certificateNumber;
        
        delete[] this->autobiography;
        this->autobiographyCount = other.autobiographyCount;
        this->autobiography = new std::string[this->autobiographyCount];
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
std::string* CommissionMember::getAutobiography() const { return this->autobiography; }
int CommissionMember::getAutobiographyCount() const { return this->autobiographyCount; }

void CommissionMember::setCommissionName(const std::string& name) { this->commissionName = name; }
void CommissionMember::setAppointmentYear(int year) { this->appointmentYear = year; }
void CommissionMember::setCertificateNumber(const std::string& number) { this->certificateNumber = number; }
void CommissionMember::setAutobiography(std::string* bio, int count) {
    delete[] this->autobiography;
    this->autobiographyCount = count;
    this->autobiography = new std::string[this->autobiographyCount];
    for (int i = 0; i < this->autobiographyCount; i++) {
        this->autobiography[i] = bio[i];
    }
}

void CommissionMember::printHeader() const {
    std::cout << "Commission Member: " << this->lastName << " " << this->firstName << " " << this->middleName << "\n";
}