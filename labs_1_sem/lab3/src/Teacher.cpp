#include "../include/Teacher.hpp"

UniversityTeacher::UniversityTeacher() : Human(), scientificWorks(nullptr), worksCount(0) {}

UniversityTeacher::UniversityTeacher(const std::string& first, const std::string& last, const std::string& middle, int year,
                                     const std::string& pos, const std::string& degree, const std::string& spec)
    : Human(first, last, middle, year), position(pos), academicDegree(degree), specialty(spec), scientificWorks(nullptr), worksCount(0) {}

UniversityTeacher::~UniversityTeacher() {
    delete[] this->scientificWorks;
}

UniversityTeacher& UniversityTeacher::operator=(const UniversityTeacher& other) {
    if (this != &other) {
        Human::operator=(other);
        this->position = other.position;
        this->academicDegree = other.academicDegree;
        this->specialty = other.specialty;
        
        delete[] this->scientificWorks;
        this->worksCount = other.worksCount;
        this->scientificWorks = new std::string[this->worksCount];
        for (int i = 0; i < this->worksCount; i++) {
            this->scientificWorks[i] = other.scientificWorks[i];
        }
    }
    return *this;
}

std::ostream& operator<<(std::ostream& os, const UniversityTeacher& teacher) {
    os << static_cast<const Human&>(teacher) << " " << teacher.position << " " << teacher.academicDegree << " " << teacher.specialty;
    for (int i = 0; i < teacher.worksCount; i++) {
        os << " " << teacher.scientificWorks[i];
    }
    return os;
}

std::istream& operator>>(std::istream& is, UniversityTeacher& teacher) {
    is >> static_cast<Human&>(teacher) >> teacher.position >> teacher.academicDegree >> teacher.specialty;
    return is;
}

std::string UniversityTeacher::getPosition() const { return this->position; }
std::string UniversityTeacher::getAcademicDegree() const { return this->academicDegree; }
std::string UniversityTeacher::getSpecialty() const { return this->specialty; }
std::string* UniversityTeacher::getScientificWorks() const { return this->scientificWorks; }
int UniversityTeacher::getWorksCount() const { return this->worksCount; }

void UniversityTeacher::setPosition(const std::string& pos) { this->position = pos; }
void UniversityTeacher::setAcademicDegree(const std::string& degree) { this->academicDegree = degree; }
void UniversityTeacher::setSpecialty(const std::string& spec) { this->specialty = spec; }
void UniversityTeacher::setScientificWorks(std::string* works, int count) {
    delete[] this->scientificWorks;
    this->worksCount = count;
    this->scientificWorks = new std::string[this->worksCount];
    for (int i = 0; i < this->worksCount; i++) {
        this->scientificWorks[i] = works[i];
    }
}

void UniversityTeacher::printHeader() const {
    std::cout << "University Teacher: " << this->lastName << " " << this->firstName << " " << this->middleName << "\n";
}