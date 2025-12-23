#include "../include/Teacher.hpp"
#include "../../exceptions/include/InputHandler.hpp"
#include "../../exceptions/include/FileException.hpp"
#include <sstream>

using namespace std;

UniversityTeacher::UniversityTeacher() : Human(), scientificWorksCount(0) {}

UniversityTeacher::UniversityTeacher(const string& first, const string& last, const string& middle, const Date& birth,
                                     const string& pos, const string& degree, const string& spec)
    : Human(first, last, middle, birth),
      position(pos),
      academicDegree(degree),
      specialty(spec),
      scientificWorksCount(0) {}

UniversityTeacher::~UniversityTeacher() {}

UniversityTeacher::UniversityTeacher(const UniversityTeacher& other)
    : Human(other),
      position(other.position),
      academicDegree(other.academicDegree),
      specialty(other.specialty),
      scientificWorksCount(other.scientificWorksCount) {
    for (int i = 0; i < scientificWorksCount; ++i) {
        scientificWorks[i] = other.scientificWorks[i];
    }
}

UniversityTeacher& UniversityTeacher::operator=(const UniversityTeacher& other) {
    if (this != &other) {
        Human::operator=(other);
        position = other.position;
        academicDegree = other.academicDegree;
        specialty = other.specialty;
        scientificWorksCount = other.scientificWorksCount;
        for (int i = 0; i < scientificWorksCount; ++i) {
            scientificWorks[i] = other.scientificWorks[i];
        }
    }
    return *this;
}

string UniversityTeacher::getPosition() const { return position; }
string UniversityTeacher::getAcademicDegree() const { return academicDegree; }
string UniversityTeacher::getSpecialty() const { return specialty; }

string UniversityTeacher::getScientificWork(int index) const {
    if (index >= 0 && index < scientificWorksCount) {
        return scientificWorks[index];
    }
    return "";
}

int UniversityTeacher::getScientificWorksCount() const { return scientificWorksCount; }
int UniversityTeacher::getScientificWorksSize() const { return SCIENTIFIC_WORKS_SIZE; }

void UniversityTeacher::setPosition(const string& pos) { position = pos; }
void UniversityTeacher::setAcademicDegree(const string& degree) { academicDegree = degree; }
void UniversityTeacher::setSpecialty(const string& spec) { specialty = spec; }

void UniversityTeacher::setScientificWork(int index, const string& work) {
    if (index >= 0 && index < SCIENTIFIC_WORKS_SIZE) {
        if (index >= scientificWorksCount) {
            scientificWorksCount = index + 1;
        }
        scientificWorks[index] = work;
    }
}

void UniversityTeacher::addScientificWork(const string& work) {
    if (scientificWorksCount < SCIENTIFIC_WORKS_SIZE) {
        scientificWorks[scientificWorksCount++] = work;
    }
}

void UniversityTeacher::printHeader() const {
    cout << left << setw(15) << "Last Name"
         << left << setw(15) << "First Name"
         << left << setw(15) << "Middle Name"
         << left << setw(12) << "Birthday"
         << left << setw(15) << "Position"
         << left << setw(15) << "Degree"
         << left << setw(15) << "Specialty"
         << "Scientific Works" << endl;
}

void UniversityTeacher::printTable() const {
    cout << left << setw(15) << lastName
         << left << setw(15) << firstName
         << left << setw(15) << middleName
         << left << setw(12) << birthday.toString()
         << left << setw(15) << position
         << left << setw(15) << academicDegree
         << left << setw(15) << specialty;

    if (scientificWorksCount == 0) {
        cout << "-";
    } else {
        for (int i = 0; i < scientificWorksCount; ++i) {
            if (i > 0) cout << ", ";
            cout << scientificWorks[i];
        }
    }
    cout << endl;
}

void UniversityTeacher::updateField(int fieldChoice) {
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
        default:
            break;
    }
}

istream& operator>>(istream& is, UniversityTeacher& teacher) {
    cout << "=== Enter Human Data ===" << endl;
    is >> static_cast<Human&>(teacher);

    teacher.position = safeGetLine(is, Language::ENGLISH, "Enter position: ");
    teacher.academicDegree = safeGetLine(is, Language::ENGLISH, "Enter academic degree: ");
    teacher.specialty = safeGetLine(is, Language::ENGLISH, "Enter specialty: ");

    teacher.scientificWorksCount = safeInputNumeric<int>(is, 0, SCIENTIFIC_WORKS_SIZE,
        "Enter number of scientific works (0-" + to_string(SCIENTIFIC_WORKS_SIZE) + "): ");

    for (int i = 0; i < teacher.scientificWorksCount; ++i) {
        teacher.scientificWorks[i] = safeGetLine(is, Language::ENGLISH, "Enter scientific work " + to_string(i + 1) + ": ");
    }

    return is;
}

void UniversityTeacher::saveTextRecord(ostream& os) const {
    Human::saveTextRecord(os);
    os << "POSITION|" << position << "|\n";
    os << "DEGREE|" << academicDegree << "|\n";
    os << "SPECIALTY|" << specialty << "|\n";
    os << "SCI_WORKS_COUNT|" << scientificWorksCount << "|\n";
    for (int i = 0; i < scientificWorksCount; ++i) {
        os << "SCI_WORK_" << (i + 1) << "|" << scientificWorks[i] << "|\n";
    }
}

void UniversityTeacher::saveBinaryRecord(ostream& os) const {
    Human::saveBinaryRecord(os);
    
    int len = static_cast<int>(position.size());
    os.write(reinterpret_cast<const char*>(&len), sizeof(len));
    if (len > 0) os.write(position.data(), len);
    
    len = static_cast<int>(academicDegree.size());
    os.write(reinterpret_cast<const char*>(&len), sizeof(len));
    if (len > 0) os.write(academicDegree.data(), len);
    
    len = static_cast<int>(specialty.size());
    os.write(reinterpret_cast<const char*>(&len), sizeof(len));
    if (len > 0) os.write(specialty.data(), len);
    
    os.write(reinterpret_cast<const char*>(&scientificWorksCount), sizeof(scientificWorksCount));
    
    for (int i = 0; i < scientificWorksCount; ++i) {
        len = static_cast<int>(scientificWorks[i].size());
        os.write(reinterpret_cast<const char*>(&len), sizeof(len));
        if (len > 0) os.write(scientificWorks[i].data(), len);
    }
}

void UniversityTeacher::loadFromText(istream& is) {
    Human::loadFromText(is);
    
    string line;
    getline(is, line);
    position = line.substr(line.find('|') + 1, line.rfind('|') - line.find('|') - 1);
    
    getline(is, line);
    academicDegree = line.substr(line.find('|') + 1, line.rfind('|') - line.find('|') - 1);
    
    getline(is, line);
    specialty = line.substr(line.find('|') + 1, line.rfind('|') - line.find('|') - 1);
    
    getline(is, line);
    string countStr = line.substr(line.find('|') + 1, line.rfind('|') - line.find('|') - 1);
    scientificWorksCount = stoi(countStr);
    
    for (int i = 0; i < scientificWorksCount && i < SCIENTIFIC_WORKS_SIZE; ++i) {
        getline(is, line);
        scientificWorks[i] = line.substr(line.find('|') + 1, line.rfind('|') - line.find('|') - 1);
    }
}

void UniversityTeacher::loadFromBinary(istream& is) {
    Human::loadFromBinary(is);
    
    int len;
    
    is.read(reinterpret_cast<char*>(&len), sizeof(len));
    if (len > 0) {
        position.resize(len);
        is.read(&position[0], len);
    }
    
    is.read(reinterpret_cast<char*>(&len), sizeof(len));
    if (len > 0) {
        academicDegree.resize(len);
        is.read(&academicDegree[0], len);
    }
    
    is.read(reinterpret_cast<char*>(&len), sizeof(len));
    if (len > 0) {
        specialty.resize(len);
        is.read(&specialty[0], len);
    }
    
    is.read(reinterpret_cast<char*>(&scientificWorksCount), sizeof(scientificWorksCount));
    
    for (int i = 0; i < scientificWorksCount && i < SCIENTIFIC_WORKS_SIZE; ++i) {
        is.read(reinterpret_cast<char*>(&len), sizeof(len));
        if (len > 0) {
            scientificWorks[i].resize(len);
            is.read(&scientificWorks[i][0], len);
        }
    }
}