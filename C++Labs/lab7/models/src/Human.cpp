#include "../include/Human.hpp"
#include "../../exceptions/include/InputHandler.hpp"
#include "../../exceptions/include/FileException.hpp"
#include <sstream>

using namespace std;

SearchMode Human::currentSearchMode = FULL_MATCH;

Human::Human() : birthday() {}

Human::Human(const string& first, const string& last, const string& middle, const Date& birth)
    : firstName(first), lastName(last), middleName(middle), birthday(birth) {}

Human::~Human() {}

Human::Human(const Human& other)
    : firstName(other.firstName),
      lastName(other.lastName),
      middleName(other.middleName),
      birthday(other.birthday) {}

Human& Human::operator=(const Human& other) {
    if (this != &other) {
        firstName = other.firstName;
        lastName = other.lastName;
        middleName = other.middleName;
        birthday = other.birthday;
    }
    return *this;
}

string Human::getFirstName() const { return firstName; }
string Human::getLastName() const { return lastName; }
string Human::getMiddleName() const { return middleName; }
Date Human::getBirthday() const { return birthday; }

void Human::setFirstName(const string& first) { firstName = first; }
void Human::setLastName(const string& last) { lastName = last; }
void Human::setMiddleName(const string& middle) { middleName = middle; }
void Human::setBirthday(const Date& birth) { birthday = birth; }

void Human::setSearchMode(SearchMode mode) { currentSearchMode = mode; }
SearchMode Human::getSearchMode() { return currentSearchMode; }

bool Human::operator==(const Human& other) const {
    switch (currentSearchMode) {
        case FULL_MATCH:
            return firstName == other.firstName &&
                   lastName == other.lastName &&
                   middleName == other.middleName &&
                   birthday == other.birthday;
        case LAST_NAME:
            return lastName == other.lastName;
        case FIRST_NAME:
            return firstName == other.firstName;
        case MIDDLE_NAME:
            return middleName == other.middleName;
        case BIRTH_YEAR:
            return birthday == other.birthday;
        default:
            return false;
    }
}

bool Human::operator<(const Human& other) const {
    switch (currentSearchMode) {
        case LAST_NAME:
            return lastName < other.lastName;
        case FIRST_NAME:
            return firstName < other.firstName;
        case MIDDLE_NAME:
            return middleName < other.middleName;
        case BIRTH_YEAR:
            return birthday < other.birthday;
        case FULL_MATCH:
        default:
            if (lastName != other.lastName) return lastName < other.lastName;
            if (firstName != other.firstName) return firstName < other.firstName;
            if (middleName != other.middleName) return middleName < other.middleName;
            return birthday < other.birthday;
    }
}

ostream& operator<<(ostream& os, const Human& member) {
    os << member.lastName << " " << member.firstName << " " << member.middleName << " " << member.getBirthday().toString();
    return os;
}

istream& operator>>(istream& is, Human& member) {
    member.firstName = safeGetLine(is, Language::ENGLISH, "Enter first name (English only): ");
    member.lastName = safeGetLine(is, Language::ENGLISH, "Enter last name (English only): ");
    member.middleName = safeGetLine(is, Language::ENGLISH, "Enter middle name (English only): ");
    member.birthday = safeInputDate(is, "DD/MM/YYYY", "Enter birthday (DD/MM/YYYY): ");
    return is;
}

void Human::printHeader() const {}

void Human::printTable() const {}

void Human::updateField(int fieldChoice) {
    string str;
    Date date;
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
        case 4:
            date = safeInputDate(cin, "DD/MM/YYYY", "New birthday (DD/MM/YYYY): ");
            setBirthday(date);
            break;
        default:
            break;
    }
}

void Human::saveTextRecord(ostream& os) const {
    os << "FIRST_NAME|" << firstName << "|\n";
    os << "LAST_NAME|" << lastName << "|\n";
    os << "MIDDLE_NAME|" << middleName << "|\n";
    os << "BIRTHDAY|" << birthday.toString() << "|\n";
}

void Human::saveBinaryRecord(ostream& os) const {
    int len;
    
    len = static_cast<int>(firstName.size());
    os.write(reinterpret_cast<const char*>(&len), sizeof(len));
    if (len > 0) os.write(firstName.data(), len);
    
    len = static_cast<int>(lastName.size());
    os.write(reinterpret_cast<const char*>(&len), sizeof(len));
    if (len > 0) os.write(lastName.data(), len);
    
    len = static_cast<int>(middleName.size());
    os.write(reinterpret_cast<const char*>(&len), sizeof(len));
    if (len > 0) os.write(middleName.data(), len);
    
    string dateStr = birthday.toString();
    len = static_cast<int>(dateStr.size());
    os.write(reinterpret_cast<const char*>(&len), sizeof(len));
    if (len > 0) os.write(dateStr.data(), len);
}

void Human::loadFromText(istream& is) {
    string line;
    getline(is, line);
    firstName = line.substr(line.find('|') + 1, line.rfind('|') - line.find('|') - 1);
    
    getline(is, line);
    lastName = line.substr(line.find('|') + 1, line.rfind('|') - line.find('|') - 1);
    
    getline(is, line);
    middleName = line.substr(line.find('|') + 1, line.rfind('|') - line.find('|') - 1);
    
    getline(is, line);
    string dateStr = line.substr(line.find('|') + 1, line.rfind('|') - line.find('|') - 1);
    istringstream ds(dateStr);
    ds >> birthday;
}

void Human::loadFromBinary(istream& is) {
    int len;
    
    is.read(reinterpret_cast<char*>(&len), sizeof(len));
    if (len > 0) {
        firstName.resize(len);
        is.read(&firstName[0], len);
    }
    
    is.read(reinterpret_cast<char*>(&len), sizeof(len));
    if (len > 0) {
        lastName.resize(len);
        is.read(&lastName[0], len);
    }
    
    is.read(reinterpret_cast<char*>(&len), sizeof(len));
    if (len > 0) {
        middleName.resize(len);
        is.read(&middleName[0], len);
    }
    
    is.read(reinterpret_cast<char*>(&len), sizeof(len));
    if (len > 0) {
        string dateStr;
        dateStr.resize(len);
        is.read(&dateStr[0], len);
        istringstream ds(dateStr);
        ds >> birthday;
    }
}