#include <iostream>
#include "../include/Teacher.hpp"
#include "../include/CommissionMember.hpp"
#include "../include/TeacherCommissionMember.hpp"

void initializeObjects(UniversityTeacher& teacher, CommissionMember& member, TeacherCommissionMember& tcm) {
    teacher = UniversityTeacher("Ivan", "Petrov", "Sidorovich", 1975, "Professor", "PhD", "Computer Science");
    teacher.addScientificWork("AI Research");
    teacher.addScientificWork("Machine Learning Paper");
    teacher.addScientificWork("Neural Networks Study");

    member = CommissionMember("Anna", "Smirnova", "Olegovna", 1980, "Admissions", 2015, "Cert123");
    member.addAutobiography("Moscow State University");
    member.addAutobiography("10 years teaching experience");
    member.addAutobiography("Published 3 books");
    member.addAutobiography("Award winner 2022");

    tcm = TeacherCommissionMember("Sergey", "Ivanov", "Petrovich", 1970, "Docent", "PhD", "Mathematics", "Examination", 2018, "Cert456");
    tcm.addScientificWork("Algebra Research");
    tcm.addScientificWork("Geometry Theorem");
    tcm.addAutobiography("PhD in Mathematics");
    tcm.addAutobiography("15 years at University");
    tcm.addCommissionWork("Exam Committee Report");
    tcm.addCommissionWork("Curriculum Development");
}

void printTeacherInfo(const UniversityTeacher& teacher) {
    teacher.printHeader();
    std::cout << "Position: " << teacher.getPosition() << std::endl;
    std::cout << "Scientific works: " << teacher.getScientificWorksCount() << std::endl;
    for (int i = 0; i < teacher.getScientificWorksCount(); i++) {
        std::cout << "  " << i + 1 << ". " << teacher.getScientificWork(i) << std::endl;
    }
}

void printMemberInfo(const CommissionMember& member) {
    member.printHeader();
    std::cout << "Commission: " << member.getCommissionName() << std::endl;
    std::cout << "Autobiography entries: " << member.getAutobiographyCount() << std::endl;
    for (int i = 0; i < member.getAutobiographyCount(); i++) {
        std::cout << "  " << i + 1 << ". " << member.getAutobiography(i) << std::endl;
    }
}

void printTCMInfo(const TeacherCommissionMember& tcm) {
    tcm.printHeader();
    std::cout << "From Teacher: " << tcm.UniversityTeacher::getPosition() << std::endl;
    std::cout << "From Member: " << tcm.CommissionMember::getCommissionName() << std::endl;
    std::cout << "Commission works: " << tcm.getCommissionWorksCount() << std::endl;
    for (int i = 0; i < tcm.getCommissionWorksCount(); i++) {
        std::cout << "  " << i + 1 << ". " << tcm.getCommissionWork(i) << std::endl;
    }
}

void applySetters(UniversityTeacher& teacher, CommissionMember& member, TeacherCommissionMember& tcm) {
    teacher.setPosition("Senior Professor");
    teacher.setAcademicDegree("Doctor of Sciences");
    teacher.setScientificWork(1, "Updated Machine Learning Research");
    teacher.addScientificWork("New Deep Learning Paper");

    member.setCommissionName("Graduation Commission");
    member.setAppointmentYear(2020);
    member.setCertificateNumber("Cert456-UPD");
    member.setAutobiography(2, "Published 5 books (updated)");
    member.addAutobiography("International Conference Speaker");

    tcm.UniversityTeacher::setPosition("Professor");
    tcm.CommissionMember::setCommissionName("Quality Assurance Commission");
    tcm.setCommissionWork(0, "Updated Exam Committee Report");
    tcm.addCommissionWork("New Accreditation Work");
}

void printInitialState(const UniversityTeacher& teacher, const CommissionMember& member, const TeacherCommissionMember& tcm) {
    std::cout << "=== INITIAL STATE ===\n";
    printTeacherInfo(teacher);
    std::cout << std::endl;
    printMemberInfo(member);
    std::cout << std::endl;
    printTCMInfo(tcm);
}

void printAfterSetters(const UniversityTeacher& teacher, const CommissionMember& member, const TeacherCommissionMember& tcm) {
    std::cout << "\n=== AFTER SETTERS ===\n";
    printTeacherInfo(teacher);
    std::cout << std::endl;
    printMemberInfo(member);
    std::cout << std::endl;
    printTCMInfo(tcm);
}

int main() {
    UniversityTeacher teacher;
    CommissionMember member;
    TeacherCommissionMember tcm;

    initializeObjects(teacher, member, tcm);
    printInitialState(teacher, member, tcm);
    applySetters(teacher, member, tcm);
    printAfterSetters(teacher, member, tcm);

    return 0;
}