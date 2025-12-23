#include "../include/CommissionMember.hpp"
#include "../../exceptions/include/InputHandler.hpp"
#include "../../exceptions/include/FileException.hpp"
#include <sstream>

using namespace std;

CommissionMember::CommissionMember() : Human(), appointmentDate(), autobiographyCount(0) {}

CommissionMember::CommissionMember(const string& first, const string& last, const string& middle, const Date& birth,
                                   const string& commission, const Date& appDate, const string& cert)
    : Human(first, last, middle, birth),
      commissionName(commission),
      appointmentDate(appDate),
      certificateNumber(cert),
      autobiographyCount(0) {}

CommissionMember::~CommissionMember() {}

CommissionMember::CommissionMember(const CommissionMember& other)
    : Human(other),
      commissionName(other.commissionName),
      appointmentDate(other.appointmentDate),
      certificateNumber(other.certificateNumber),
      autobiographyCount(other.autobiographyCount) {
    for (int i = 0; i < autobiographyCount; ++i) {
        autobiography[i] = other.autobiography[i];
    }
}

CommissionMember& CommissionMember::operator=(const CommissionMember& other) {
    if (this != &other) {
        Human::operator=(other);
        commissionName = other.commissionName;
        appointmentDate = other.appointmentDate;
        certificateNumber = other.certificateNumber;
        autobiographyCount = other.autobiographyCount;
        for (int i = 0; i < autobiographyCount; ++i) {
            autobiography[i] = other.autobiography[i];
        }
    }
    return *this;
}

string CommissionMember::getCommissionName() const { return commissionName; }
Date CommissionMember::getAppointmentDate() const { return appointmentDate; }
string CommissionMember::getCertificateNumber() const { return certificateNumber; }

string CommissionMember::getAutobiography(int index) const {
    if (index >= 0 && index < autobiographyCount) {
        return autobiography[index];
    }
    return "";
}

int CommissionMember::getAutobiographyCount() const { return autobiographyCount; }
int CommissionMember::getAutobiographySize() const { return AUTOBIOGRAPHY_SIZE; }

void CommissionMember::setCommissionName(const string& name) { commissionName = name; }
void CommissionMember::setAppointmentDate(const Date& date) { appointmentDate = date; }
void CommissionMember::setCertificateNumber(const string& number) { certificateNumber = number; }

void CommissionMember::setAutobiography(int index, const string& bio) {
    if (index >= 0 && index < AUTOBIOGRAPHY_SIZE) {
        if (index >= autobiographyCount) {
            autobiographyCount = index + 1;
        }
        autobiography[index] = bio;
    }
}

void CommissionMember::addAutobiography(const string& bio) {
    if (autobiographyCount < AUTOBIOGRAPHY_SIZE) {
        autobiography[autobiographyCount++] = bio;
    }
}

void CommissionMember::printHeader() const {
    cout << left << setw(15) << "Last Name"
         << left << setw(15) << "First Name"
         << left << setw(15) << "Middle Name"
         << left << setw(12) << "Birthday"
         << left << setw(20) << "Commission"
         << left << setw(12) << "App.Date"
         << left << setw(15) << "Certificate"
         << "Autobiography" << endl;
}

void CommissionMember::printTable() const {
    cout << left << setw(15) << lastName
         << left << setw(15) << firstName
         << left << setw(15) << middleName
         << left << setw(12) << birthday.toString()
         << left << setw(20) << commissionName
         << left << setw(12) << appointmentDate.toString()
         << left << setw(15) << certificateNumber;

    if (autobiographyCount == 0) {
        cout << "-";
    } else {
        for (int i = 0; i < autobiographyCount; ++i) {
            if (i > 0) cout << ", ";
            cout << autobiography[i];
        }
    }
    cout << endl;
}

void CommissionMember::updateField(int fieldChoice) {
    string str;
    int num;
    switch (fieldChoice) {
        case 1:
            str = safeGetLine(cin, Language::ENGLISH, "New first name (English only): ");
            setFirstName(str);
            break;
        case 2:
            str = safeGetLine(cin, Language::ENGLISH, "New last name (English only): ");
            setLastName(str);
            break;
        case 3:
            str = safeGetLine(cin, Language::ENGLISH, "New middle name (English only): ");
            setMiddleName(str);
            break;
        case 4: {
            Date d = safeInputDate(cin, "DD/MM/YYYY", "New birthday (DD/MM/YYYY): ");
            setBirthday(d);
            break;
        }
        case 5:
            str = safeGetLine(cin, Language::ENGLISH, "New commission name: ");
            setCommissionName(str);
            break;
        case 6: {
            Date d = safeInputDate(cin, "DD/MM/YYYY", "New appointment date (DD/MM/YYYY): ");
            setAppointmentDate(d);
            break;
        }
        case 7:
            str = safeGetLine(cin, Language::ENGLISH, "New certificate number: ");
            setCertificateNumber(str);
            break;
        case 8:
            str = safeGetLine(cin, Language::ENGLISH, "New autobiography entry: ");
            addAutobiography(str);
            break;
        case 9:
            if (autobiographyCount == 0) {
                cout << "No autobiography entries to replace." << endl;
            } else {
                num = safeInputNumeric<int>(cin, 0, autobiographyCount - 1,
                                            "Enter index of autobiography entry to change (0-" + to_string(autobiographyCount - 1) + "): ");
                str = safeGetLine(cin, Language::ENGLISH, "Enter new autobiography entry: ");
                setAutobiography(num, str);
            }
            break;
        default:
            break;
    }
}

istream& operator>>(istream& is, CommissionMember& member) {
    cout << "=== Enter Human Data ===" << endl;
    is >> static_cast<Human&>(member);

    member.commissionName = safeGetLine(is, Language::ENGLISH, "Enter commission name: ");
    member.appointmentDate = safeInputDate(is, "DD/MM/YYYY", "Enter appointment date (DD/MM/YYYY): ");
    member.certificateNumber = safeGetLine(is, Language::ENGLISH, "Enter certificate number: ");

    member.autobiographyCount = safeInputNumeric<int>(is, 0, AUTOBIOGRAPHY_SIZE,
        "Enter number of autobiography entries (0-" + to_string(AUTOBIOGRAPHY_SIZE) + "): ");

    for (int i = 0; i < member.autobiographyCount; ++i) {
        member.autobiography[i] = safeGetLine(is, Language::ENGLISH, "Enter autobiography entry " + to_string(i + 1) + ": ");
    }

    return is;
}

void CommissionMember::saveTextRecord(ostream& os) const {
    Human::saveTextRecord(os);
    os << "COMMISSION|" << commissionName << "|\n";
    os << "APPOINTMENT_DATE|" << appointmentDate.toString() << "|\n";
    os << "CERTIFICATE|" << certificateNumber << "|\n";
    os << "AUTOBIOGRAPHY_COUNT|" << autobiographyCount << "|\n";
    for (int i = 0; i < autobiographyCount; ++i) {
        os << "AUTOBIOGRAPHY_" << (i + 1) << "|" << autobiography[i] << "|\n";
    }
}

void CommissionMember::saveBinaryRecord(ostream& os) const {
    Human::saveBinaryRecord(os);
    
    int len = static_cast<int>(commissionName.size());
    os.write(reinterpret_cast<const char*>(&len), sizeof(len));
    if (len > 0) os.write(commissionName.data(), len);
    
    string appDateStr = appointmentDate.toString();
    len = static_cast<int>(appDateStr.size());
    os.write(reinterpret_cast<const char*>(&len), sizeof(len));
    if (len > 0) os.write(appDateStr.data(), len);
    
    len = static_cast<int>(certificateNumber.size());
    os.write(reinterpret_cast<const char*>(&len), sizeof(len));
    if (len > 0) os.write(certificateNumber.data(), len);
    
    os.write(reinterpret_cast<const char*>(&autobiographyCount), sizeof(autobiographyCount));
    
    for (int i = 0; i < autobiographyCount; ++i) {
        len = static_cast<int>(autobiography[i].size());
        os.write(reinterpret_cast<const char*>(&len), sizeof(len));
        if (len > 0) os.write(autobiography[i].data(), len);
    }
}

void CommissionMember::loadFromText(istream& is) {
    Human::loadFromText(is);
    
    string line;
    getline(is, line);
    commissionName = line.substr(line.find('|') + 1, line.rfind('|') - line.find('|') - 1);
    
    getline(is, line);
    string appDateStr = line.substr(line.find('|') + 1, line.rfind('|') - line.find('|') - 1);
    istringstream ds(appDateStr);
    ds >> appointmentDate;
    
    getline(is, line);
    certificateNumber = line.substr(line.find('|') + 1, line.rfind('|') - line.find('|') - 1);
    
    getline(is, line);
    string countStr = line.substr(line.find('|') + 1, line.rfind('|') - line.find('|') - 1);
    autobiographyCount = stoi(countStr);
    
    for (int i = 0; i < autobiographyCount && i < AUTOBIOGRAPHY_SIZE; ++i) {
        getline(is, line);
        autobiography[i] = line.substr(line.find('|') + 1, line.rfind('|') - line.find('|') - 1);
    }
}

void CommissionMember::loadFromBinary(istream& is) {
    Human::loadFromBinary(is);
    
    int len;
    
    is.read(reinterpret_cast<char*>(&len), sizeof(len));
    if (len > 0) {
        commissionName.resize(len);
        is.read(&commissionName[0], len);
    }
    
    is.read(reinterpret_cast<char*>(&len), sizeof(len));
    if (len > 0) {
        string appDateStr;
        appDateStr.resize(len);
        is.read(&appDateStr[0], len);
        istringstream ds(appDateStr);
        ds >> appointmentDate;
    }
    
    is.read(reinterpret_cast<char*>(&len), sizeof(len));
    if (len > 0) {
        certificateNumber.resize(len);
        is.read(&certificateNumber[0], len);
    }
    
    is.read(reinterpret_cast<char*>(&autobiographyCount), sizeof(autobiographyCount));
    
    for (int i = 0; i < autobiographyCount && i < AUTOBIOGRAPHY_SIZE; ++i) {
        is.read(reinterpret_cast<char*>(&len), sizeof(len));
        if (len > 0) {
            autobiography[i].resize(len);
            is.read(&autobiography[i][0], len);
        }
    }
}