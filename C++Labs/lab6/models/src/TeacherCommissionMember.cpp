#include "../include/TeacherCommissionMember.hpp"
#include "../../exceptions/include/InputHandler.hpp"
#include "../../exceptions/include/FileException.hpp"
#include <sstream>

using namespace std;

TeacherCommissionMember::TeacherCommissionMember()
    : Human(),
      UniversityTeacher(),
      CommissionMember(),
      commissionWorksCount(0) {}

TeacherCommissionMember::TeacherCommissionMember(const string& first, const string& last, const string& middle, const Date& birth,
                                                 const string& pos, const string& degree, const string& spec,
                                                 const string& commission, const Date& appDate, const string& cert)
    : Human(first, last, middle, birth),
      UniversityTeacher(first, last, middle, birth, pos, degree, spec),
      CommissionMember(first, last, middle, birth, commission, appDate, cert),
      commissionWorksCount(0) {}

TeacherCommissionMember::~TeacherCommissionMember() {}

TeacherCommissionMember::TeacherCommissionMember(const TeacherCommissionMember& other)
    : Human(other),
      UniversityTeacher(other),
      CommissionMember(other),
      commissionWorksCount(other.commissionWorksCount) {
    for (int i = 0; i < commissionWorksCount; ++i) {
        commissionWorks[i] = other.commissionWorks[i];
    }
}

TeacherCommissionMember& TeacherCommissionMember::operator=(const TeacherCommissionMember& other) {
    if (this != &other) {
        UniversityTeacher::operator=(other);
        CommissionMember::operator=(other);
        commissionWorksCount = other.commissionWorksCount;
        for (int i = 0; i < commissionWorksCount; ++i) {
            commissionWorks[i] = other.commissionWorks[i];
        }
    }
    return *this;
}

string TeacherCommissionMember::getCommissionWork(int index) const {
    if (index >= 0 && index < commissionWorksCount) {
        return commissionWorks[index];
    }
    return "";
}

int TeacherCommissionMember::getCommissionWorksCount() const { return commissionWorksCount; }
int TeacherCommissionMember::getCommissionWorksSize() const { return COMMISSION_WORKS_SIZE; }

void TeacherCommissionMember::setCommissionWork(int index, const string& work) {
    if (index >= 0 && index < COMMISSION_WORKS_SIZE) {
        if (index >= commissionWorksCount) {
            commissionWorksCount = index + 1;
        }
        commissionWorks[index] = work;
    }
}

void TeacherCommissionMember::addCommissionWork(const string& work) {
    if (commissionWorksCount < COMMISSION_WORKS_SIZE) {
        commissionWorks[commissionWorksCount++] = work;
    }
}

void TeacherCommissionMember::printHeader() const {
    cout << left << setw(15) << "Last Name"
         << left << setw(15) << "First Name"
         << left << setw(15) << "Middle Name"
         << left << setw(12) << "Birthday"
         << left << setw(15) << "Position"
         << left << setw(15) << "Degree"
         << left << setw(15) << "Specialty"
         << left << setw(20) << "Commission"
         << left << setw(12) << "App.Date"
         << left << setw(15) << "Certificate"
         << left << setw(20) << "Scientific Works"
         << "Commission Works" << endl;
}

void TeacherCommissionMember::printTable() const {
    cout << left << setw(15) << lastName
         << left << setw(15) << firstName
         << left << setw(15) << middleName
         << left << setw(12) << birthday.toString()
         << left << setw(15) << position
         << left << setw(15) << academicDegree
         << left << setw(15) << specialty
         << left << setw(20) << commissionName
         << left << setw(12) << appointmentDate.toString()
         << left << setw(15) << certificateNumber;

    if (scientificWorksCount == 0) {
        cout << left << setw(20) << "-";
    } else {
        string allSci;
        for (int i = 0; i < scientificWorksCount; ++i) {
            if (i > 0) allSci += ", ";
            allSci += scientificWorks[i];
        }
        cout << left << setw(20) << allSci;
    }

    if (commissionWorksCount == 0) {
        cout << "-";
    } else {
        for (int i = 0; i < commissionWorksCount; ++i) {
            if (i > 0) cout << ", ";
            cout << commissionWorks[i];
        }
    }

    cout << endl;
}

void TeacherCommissionMember::updateField(int fieldChoice) {
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
            str = safeGetLine(cin, Language::ENGLISH, "New position: ");
            setPosition(str);
            break;
        case 6:
            str = safeGetLine(cin, Language::ENGLISH, "New academic degree: ");
            setAcademicDegree(str);
            break;
        case 7:
            str = safeGetLine(cin, Language::ENGLISH, "New specialty: ");
            setSpecialty(str);
            break;
        case 8:
            str = safeGetLine(cin, Language::ENGLISH, "New scientific work: ");
            addScientificWork(str);
            break;
        case 9:
            if (scientificWorksCount == 0) {
                cout << "No scientific works to replace." << endl;
            } else {
                num = safeInputNumeric<int>(cin, 0, scientificWorksCount - 1,
                                            "Enter index of scientific work to change (0-" + to_string(scientificWorksCount - 1) + "): ");
                str = safeGetLine(cin, Language::ENGLISH, "Enter new scientific work entry: ");
                setScientificWork(num, str);
            }
            break;
        case 10:
            str = safeGetLine(cin, Language::ENGLISH, "New commission name: ");
            setCommissionName(str);
            break;
        case 11: {
            Date d = safeInputDate(cin, "DD/MM/YYYY", "New appointment date (DD/MM/YYYY): ");
            setAppointmentDate(d);
            break;
        }
        case 12:
            str = safeGetLine(cin, Language::ENGLISH, "New certificate number: ");
            setCertificateNumber(str);
            break;
        case 13:
            str = safeGetLine(cin, Language::ENGLISH, "New autobiography entry: ");
            addAutobiography(str);
            break;
        case 14:
            if (autobiographyCount == 0) {
                cout << "No autobiography entries to replace." << endl;
            } else {
                num = safeInputNumeric<int>(cin, 0, autobiographyCount - 1,
                                            "Enter index of autobiography entry to change (0-" + to_string(autobiographyCount - 1) + "): ");
                str = safeGetLine(cin, Language::ENGLISH, "Enter new autobiography entry: ");
                setAutobiography(num, str);
            }
            break;
        case 15:
            str = safeGetLine(cin, Language::ENGLISH, "New commission work: ");
            addCommissionWork(str);
            break;
        case 16:
            if (commissionWorksCount == 0) {
                cout << "No commission works to replace." << endl;
            } else {
                num = safeInputNumeric<int>(cin, 0, commissionWorksCount - 1,
                                            "Enter index of commission work to change (0-" + to_string(commissionWorksCount - 1) + "): ");
                str = safeGetLine(cin, Language::ENGLISH, "Enter new commission work entry: ");
                setCommissionWork(num, str);
            }
            break;
        default:
            break;
    }
}

istream& operator>>(istream& is, TeacherCommissionMember& member) {
    cout << "=== Enter Teacher Data ===" << endl;
    is >> static_cast<UniversityTeacher&>(member);

    cout << "=== Enter Commission Member Data ===" << endl;
    member.commissionName = safeGetLine(is, Language::ENGLISH, "Enter commission name: ");
    member.appointmentDate = safeInputDate(is, "DD/MM/YYYY", "Enter appointment date (DD/MM/YYYY): ");
    member.certificateNumber = safeGetLine(is, Language::ENGLISH, "Enter certificate number: ");

    member.autobiographyCount = safeInputNumeric<int>(is, 0, AUTOBIOGRAPHY_SIZE,
        "Enter number of autobiography entries (0-" + to_string(AUTOBIOGRAPHY_SIZE) + "): ");

    for (int i = 0; i < member.autobiographyCount; ++i) {
        member.autobiography[i] = safeGetLine(is, Language::ENGLISH, "Enter autobiography entry " + to_string(i + 1) + ": ");
    }

    cout << "=== Enter Teacher Commission Member Data ===" << endl;
    member.commissionWorksCount = safeInputNumeric<int>(is, 0, COMMISSION_WORKS_SIZE,
        "Enter number of commission works (0-" + to_string(COMMISSION_WORKS_SIZE) + "): ");

    for (int i = 0; i < member.commissionWorksCount; ++i) {
        member.commissionWorks[i] = safeGetLine(is, Language::ENGLISH, "Enter commission work " + to_string(i + 1) + ": ");
    }

    return is;
}

void TeacherCommissionMember::saveTextRecord(ostream& os) const {
    UniversityTeacher::saveTextRecord(os);
    os << "COMMISSION|" << commissionName << "|\n";
    os << "APPOINTMENT_DATE|" << appointmentDate.toString() << "|\n";
    os << "CERTIFICATE|" << certificateNumber << "|\n";
    os << "AUTOBIOGRAPHY_COUNT|" << autobiographyCount << "|\n";
    for (int i = 0; i < autobiographyCount; ++i) {
        os << "AUTOBIOGRAPHY_" << (i + 1) << "|" << autobiography[i] << "|\n";
    }
    os << "COMMISSION_WORKS_COUNT|" << commissionWorksCount << "|\n";
    for (int i = 0; i < commissionWorksCount; ++i) {
        os << "COMMISSION_WORK_" << (i + 1) << "|" << commissionWorks[i] << "|\n";
    }
}

void TeacherCommissionMember::saveBinaryRecord(ostream& os) const {
    UniversityTeacher::saveBinaryRecord(os);
    
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
    
    os.write(reinterpret_cast<const char*>(&commissionWorksCount), sizeof(commissionWorksCount));
    
    for (int i = 0; i < commissionWorksCount; ++i) {
        len = static_cast<int>(commissionWorks[i].size());
        os.write(reinterpret_cast<const char*>(&len), sizeof(len));
        if (len > 0) os.write(commissionWorks[i].data(), len);
    }
}

void TeacherCommissionMember::loadFromText(istream& is) {
    UniversityTeacher::loadFromText(is);
    
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
    
    getline(is, line);
    countStr = line.substr(line.find('|') + 1, line.rfind('|') - line.find('|') - 1);
    commissionWorksCount = stoi(countStr);
    
    for (int i = 0; i < commissionWorksCount && i < COMMISSION_WORKS_SIZE; ++i) {
        getline(is, line);
        commissionWorks[i] = line.substr(line.find('|') + 1, line.rfind('|') - line.find('|') - 1);
    }
}

void TeacherCommissionMember::loadFromBinary(istream& is) {
    UniversityTeacher::loadFromBinary(is);
    
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
    
    is.read(reinterpret_cast<char*>(&commissionWorksCount), sizeof(commissionWorksCount));
    
    for (int i = 0; i < commissionWorksCount && i < COMMISSION_WORKS_SIZE; ++i) {
        is.read(reinterpret_cast<char*>(&len), sizeof(len));
        if (len > 0) {
            commissionWorks[i].resize(len);
            is.read(&commissionWorks[i][0], len);
        }
    }
}