#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include "../models/include/Human.hpp"
#include "../models/include/Teacher.hpp"
#include "../models/include/CommissionMember.hpp"
#include "../models/include/TeacherCommissionMember.hpp"
#include "../templates/include/Deque.hpp"
#include "../exceptions/include/InputHandler.hpp"
#include "../exceptions/include/Date.hpp"
#include "../exceptions/include/InputException.hpp"
#include "../repositories/TextFile.hpp"
#include "../repositories/BinaryFile.hpp"

using namespace std;

Language currentLang = Language::ENGLISH;

void drawMenu(const string& title, const string options[], int numOptions) {
    int max_len = static_cast<int>(title.length());
    for (int i = 0; i < numOptions; i++) {
        if (static_cast<int>(options[i].length()) > max_len) max_len = static_cast<int>(options[i].length());
    }
    max_len += 4;
    cout << "+" << string(max_len, '-') << "+" << endl;
    cout << "| " << title << string(max_len - static_cast<int>(title.length()) - 1, ' ') << "|" << endl;
    cout << "+" << string(max_len, '-') << "+" << endl;
    for (int i = 0; i < numOptions; i++) {
        cout << "| " << options[i] << string(max_len - static_cast<int>(options[i].length()) - 1, ' ') << "|" << endl;
    }
    cout << "+" << string(max_len, '-') << "+" << endl;
}

template <typename T>
void addObject(Deque<T*>& deque) {
    string sideOptions[2] = {"1. Add to Front", "2. Add to Back"};
    drawMenu("Select Side", sideOptions, 2);

    int sideChoice = safeInputNumeric<int>(cin, 1, 2, "Enter choice (1-2): ");

    T* object = new T();
    cin >> *object;

    if (sideChoice == 1) {
        deque.pushFront(object);
    } else {
        deque.pushBack(object);
    }
}

template <typename T>
void removeObject(Deque<T*>& deque) {
    string options[2] = {"1. Remove from Front", "2. Remove from Back"};
    drawMenu("Remove Object", options, 2);

    int choice = safeInputNumeric<int>(cin, 1, 2, "Enter choice (1-2): ");

    if (deque.isEmpty()) {
        cout << "Deque is empty." << endl;
        return;
    }

    if (choice == 1) {
        delete deque.peekFirst();
        deque.popFront();
        cout << "Removed from front." << endl;
    } else {
        delete deque.peekLast();
        deque.popBack();
        cout << "Removed from back." << endl;
    }
}

void modifyObject(Deque<UniversityTeacher*>& deque) {
    string sideOptions[2] = {"1. Modify First", "2. Modify Last"};
    drawMenu("Select Object to Modify", sideOptions, 2);

    int sideChoice = safeInputNumeric<int>(cin, 1, 2, "Enter choice (1-2): ");

    if (deque.isEmpty()) {
        cout << "Deque is empty." << endl;
        return;
    }

    UniversityTeacher* teacher = (sideChoice == 1) ? deque.peekFirst() : deque.peekLast();

    string fieldOptions[9] = {
        "1. First Name", "2. Last Name", "3. Middle Name", "4. Birthday",
        "5. Position", "6. Degree", "7. Specialty", "8. Add Scientific Work",
        "9. Replace Scientific Work"
    };
    drawMenu("Select Field", fieldOptions, 9);

    int fieldChoice = safeInputNumeric<int>(cin, 1, 9, "Enter choice (1-9): ");

    try {
        teacher->updateField(fieldChoice);
        cout << "Field updated successfully." << endl;
    } catch (const InputException& e) {
        cout << "Error updating field: " << e.what() << endl;
    }
}

void modifyObject(Deque<CommissionMember*>& deque) {
    string sideOptions[2] = {"1. Modify First", "2. Modify Last"};
    drawMenu("Select Object to Modify", sideOptions, 2);

    int sideChoice = safeInputNumeric<int>(cin, 1, 2, "Enter choice (1-2): ");

    if (deque.isEmpty()) {
        cout << "Deque is empty." << endl;
        return;
    }

    CommissionMember* member = (sideChoice == 1) ? deque.peekFirst() : deque.peekLast();

    string fieldOptions[9] = {
        "1. First Name", "2. Last Name", "3. Middle Name", "4. Birthday",
        "5. Commission Name", "6. Appointment Date", "7. Certificate Number",
        "8. Add Autobiography", "9. Replace Autobiography"
    };
    drawMenu("Select Field", fieldOptions, 9);

    int fieldChoice = safeInputNumeric<int>(cin, 1, 9, "Enter choice (1-9): ");

    try {
        member->updateField(fieldChoice);
        cout << "Field updated successfully." << endl;
    } catch (const InputException& e) {
        cout << "Error updating field: " << e.what() << endl;
    }
}

void modifyObject(Deque<TeacherCommissionMember*>& deque) {
    string sideOptions[2] = {"1. Modify First", "2. Modify Last"};
    drawMenu("Select Object to Modify", sideOptions, 2);

    int sideChoice = safeInputNumeric<int>(cin, 1, 2, "Enter choice (1-2): ");

    if (deque.isEmpty()) {
        cout << "Deque is empty." << endl;
        return;
    }

    TeacherCommissionMember* tcm = (sideChoice == 1) ? deque.peekFirst() : deque.peekLast();

    string fieldOptions[16] = {
        "1. First Name", "2. Last Name", "3. Middle Name", "4. Birthday",
        "5. Position", "6. Degree", "7. Specialty", "8. Add Scientific Work",
        "9. Replace Scientific Work", "10. Commission Name", "11. Appointment Date",
        "12. Certificate Number", "13. Add Autobiography", "14. Replace Autobiography",
        "15. Add Commission Work", "16. Replace Commission Work"
    };
    drawMenu("Select Field", fieldOptions, 16);

    int fieldChoice = safeInputNumeric<int>(cin, 1, 16, "Enter choice (1-16): ");

    try {
        tcm->updateField(fieldChoice);
        cout << "Field updated successfully." << endl;
    } catch (const InputException& e) {
        cout << "Error updating field: " << e.what() << endl;
    }
}

template <typename T>
void peekObject(Deque<T*>& deque) {
    string options[2] = {"1. Peek First", "2. Peek Last"};
    drawMenu("Peek Object", options, 2);

    int choice = safeInputNumeric<int>(cin, 1, 2, "Enter choice (1-2): ");

    if (deque.isEmpty()) {
        cout << "Deque is empty." << endl;
        return;
    }

    T* obj = (choice == 1) ? deque.peekFirst() : deque.peekLast();
    
    T temp;
    temp.printHeader();
    obj->printTable();
}

template <typename T>
void printDeque(Deque<T*>& deque) {
    if (deque.isEmpty()) {
        cout << "Deque is empty." << endl;
        return;
    }

    T temp;
    temp.printHeader();

    Deque<T*> tmp;
    while (!deque.isEmpty()) {
        T* obj = deque.peekFirst();
        deque.popFront();
        obj->printTable();
        tmp.pushBack(obj);
    }

    while (!tmp.isEmpty()) {
        T* obj = tmp.peekFirst();
        tmp.popFront();
        deque.pushBack(obj);
    }
}

template <typename T>
void searchInDeque(Deque<T*>& deque) {
    if (deque.isEmpty()) {
        cout << "Deque is empty." << endl;
        return;
    }

    string searchOptions[5] = {
        "1. Search by Last Name",
        "2. Search by First Name",
        "3. Search by Middle Name",
        "4. Search by Birthday",
        "5. Search by Full Match (all fields)"
    };
    drawMenu("Search Options", searchOptions, 5);

    int choice = safeInputNumeric<int>(cin, 1, 5, "Enter choice (1-5): ");

    string searchString;
    Date searchDate;

    T* searchObj = new T();

    if (choice == 1) {
        searchString = safeGetLine(cin, currentLang, "Enter last name to search (English only): ");
        searchObj->setLastName(searchString);
        Human::setSearchMode(LAST_NAME);
    } else if (choice == 2) {
        searchString = safeGetLine(cin, currentLang, "Enter first name to search (English only): ");
        searchObj->setFirstName(searchString);
        Human::setSearchMode(FIRST_NAME);
    } else if (choice == 3) {
        searchString = safeGetLine(cin, currentLang, "Enter middle name to search (English only): ");
        searchObj->setMiddleName(searchString);
        Human::setSearchMode(MIDDLE_NAME);
    } else if (choice == 4) {
        searchDate = safeInputDate(cin, "DD/MM/YYYY", "Enter birthday to search: ");
        searchObj->setBirthday(searchDate);
        Human::setSearchMode(BIRTH_YEAR);
    } else {
        cout << "Enter criteria for Full Match:" << endl;

        searchString = safeGetLine(cin, currentLang, "Enter last name (English only): ");
        searchObj->setLastName(searchString);

        searchString = safeGetLine(cin, currentLang, "Enter first name (English only): ");
        searchObj->setFirstName(searchString);

        searchString = safeGetLine(cin, currentLang, "Enter middle name (English only): ");
        searchObj->setMiddleName(searchString);

        searchDate = safeInputDate(cin, "DD/MM/YYYY", "Enter birthday: ");
        searchObj->setBirthday(searchDate);

        Human::setSearchMode(FULL_MATCH);
    }

    Deque<T*> searchResults = deque.find(searchObj);

    Human::setSearchMode(FULL_MATCH);
    delete searchObj;

    if (searchResults.isEmpty()) {
        cout << "No matches found." << endl;
    } else {
        cout << "Search results (" << searchResults.size() << " found):" << endl;
        printDeque(searchResults);
    }
}

template <typename T>
void clearDeque(Deque<T*>& deque) {
    while (!deque.isEmpty()) {
        delete deque.peekFirst();
        deque.popFront();
    }
    cout << "Deque cleared." << endl;
}

template <typename T>
void sortDequeByField(Deque<T*>& deque) {
    if (deque.isEmpty()) {
        cout << "Deque is empty. Nothing to sort." << endl;
        return;
    }
    string sortOptions[4] = {
        "1. Sort by Last Name",
        "2. Sort by First Name",
        "3. Sort by Middle Name",
        "4. Sort by Birth Date"
    };
    drawMenu("Sort Options", sortOptions, 4);

    int choice = safeInputNumeric<int>(cin, 1, 4, "Enter choice (1-4): ");

    if (choice == 1) {
        Human::setSearchMode(LAST_NAME);
        cout << "Sorting by Last Name..." << endl;
    } else if (choice == 2) {
        Human::setSearchMode(FIRST_NAME);
        cout << "Sorting by First Name..." << endl;
    } else if (choice == 3) {
        Human::setSearchMode(MIDDLE_NAME);
        cout << "Sorting by Middle Name..." << endl;
    } else if (choice == 4) {
        Human::setSearchMode(BIRTH_YEAR);
        cout << "Sorting by Birth Date..." << endl;
    } else {
        cout << "Invalid choice. Aborting sort." << endl;
        return;
    }

    deque.sort();

    Human::setSearchMode(LAST_NAME);

    cout << "Deque sorted successfully." << endl;
    printDeque(deque);
}

template <typename T>
void saveToFile(Deque<T*>& deque) {
    if (deque.isEmpty()) {
        cout << "Deque is empty. Nothing to save." << endl;
        return;
    }
    
    string fileTypeOptions[2] = {"1. Text file", "2. Binary file"};
    drawMenu("Select File Type", fileTypeOptions, 2);
    
    int fileTypeChoice = safeInputNumeric<int>(cin, 1, 2, "Enter choice (1-2): ");
    
    string saveTypeOptions[2] = {"1. Save first element", "2. Save all elements"};
    drawMenu("Select Save Type", saveTypeOptions, 2);
    
    int saveTypeChoice = safeInputNumeric<int>(cin, 1, 2, "Enter choice (1-2): ");
    
    string sideOptions[2] = {"1. Save from Front", "2. Save from Back"};
    drawMenu("Select Position to Save", sideOptions, 2);
    
    int sideChoice = safeInputNumeric<int>(cin, 1, 2, "Enter choice (1-2): ");
    
    if (fileTypeChoice == 1) {
        if (saveTypeChoice == 1) {
            T* obj = (sideChoice == 1) ? deque.peekFirst() : deque.peekLast();
            TextFile<T> file("people.txt");
            try {
                file.clearFile();
                file.saveRecord(*obj);
                cout << "Saved " << (sideChoice == 1 ? "first" : "last") << " object to text file: people.txt" << endl;
            } catch (const FileException& e) {
                cout << "File error: " << e.what() << endl;
            }
        } else {
            TextFile<T> file("people.txt");
            try {
                file.clearFile();
                
                if (sideChoice == 1) {
                    Deque<T*> tmp;
                    while (!deque.isEmpty()) {
                        T* obj = deque.peekFirst();
                        deque.popFront();
                        file.saveRecord(*obj);
                        tmp.pushBack(obj);
                    }
                    while (!tmp.isEmpty()) {
                        T* obj = tmp.peekFirst();
                        tmp.popFront();
                        deque.pushBack(obj);
                    }
                } else {
                    Deque<T*> tmp;
                    while (!deque.isEmpty()) {
                        T* obj = deque.peekLast();
                        deque.popBack();
                        file.saveRecord(*obj);
                        tmp.pushFront(obj);
                    }
                    while (!tmp.isEmpty()) {
                        T* obj = tmp.peekFirst();
                        tmp.popFront();
                        deque.pushFront(obj);
                    }
                }
                
                cout << "Saved all objects (starting from " << (sideChoice == 1 ? "front" : "back") << ") to text file: people.txt" << endl;
            } catch (const FileException& e) {
                cout << "File error: " << e.what() << endl;
            }
        }
    } else {
        if (saveTypeChoice == 1) {
            T* obj = (sideChoice == 1) ? deque.peekFirst() : deque.peekLast();
            BinaryFile<T> file("people.bin");
            try {
                file.clearFile();
                file.saveRecord(*obj);
                cout << "Saved " << (sideChoice == 1 ? "first" : "last") << " object to binary file: people.bin" << endl;
            } catch (const FileException& e) {
                cout << "File error: " << e.what() << endl;
            }
        } else {
            BinaryFile<T> file("people.bin");
            try {
                file.clearFile();
                
                if (sideChoice == 1) {
                    Deque<T*> tmp;
                    while (!deque.isEmpty()) {
                        T* obj = deque.peekFirst();
                        deque.popFront();
                        file.saveRecord(*obj);
                        tmp.pushBack(obj);
                    }
                    while (!tmp.isEmpty()) {
                        T* obj = tmp.peekFirst();
                        tmp.popFront();
                        deque.pushBack(obj);
                    }
                } else {
                    Deque<T*> tmp;
                    while (!deque.isEmpty()) {
                        T* obj = deque.peekLast();
                        deque.popBack();
                        file.saveRecord(*obj);
                        tmp.pushFront(obj);
                    }
                    while (!tmp.isEmpty()) {
                        T* obj = tmp.peekFirst();
                        tmp.popFront();
                        deque.pushFront(obj);
                    }
                }
                
                cout << "Saved all objects (starting from " << (sideChoice == 1 ? "front" : "back") << ") to binary file: people.bin" << endl;
            } catch (const FileException& e) {
                cout << "File error: " << e.what() << endl;
            }
        }
    }
}

template <typename T>
void loadFromFile(Deque<T*>& deque) {
    string fileTypeOptions[2] = {"1. Text file", "2. Binary file"};
    drawMenu("Select File Type", fileTypeOptions, 2);
    
    int fileTypeChoice = safeInputNumeric<int>(cin, 1, 2, "Enter choice (1-2): ");
    
    string loadTypeOptions[2] = {"1. Load first element", "2. Load all elements"};
    drawMenu("Select Load Type", loadTypeOptions, 2);
    
    int loadTypeChoice = safeInputNumeric<int>(cin, 1, 2, "Enter choice (1-2): ");
    
    if (fileTypeChoice == 1) {
        if (loadTypeChoice == 1) {
            TextFile<T> file("people.txt");
            try {
                T* obj = file.readRecord();
                if (obj == nullptr) {
                    cout << "File is empty or read error." << endl;
                    return;
                }
                
                string sideOptions[2] = {"1. Insert at Front", "2. Insert at Back"};
                drawMenu("Select Insert Position", sideOptions, 2);
                
                int sideChoice = safeInputNumeric<int>(cin, 1, 2, "Enter choice (1-2): ");
                
                if (sideChoice == 1) {
                    deque.pushFront(obj);
                } else {
                    deque.pushBack(obj);
                }
                
                cout << "Loaded object from text file and inserted at " << (sideChoice == 1 ? "front" : "back") << ": people.txt" << endl;
            } catch (const FileException& e) {
                cout << "File error: " << e.what() << endl;
            }
        } else {
            TextFile<T> file("people.txt");
            try {
                Deque<T*> loadedDeque = file.readAllRecords();
                
                if (loadedDeque.isEmpty()) {
                    cout << "File is empty." << endl;
                    return;
                }
                
                string sideOptions[2] = {"1. Insert at Front", "2. Insert at Back"};
                drawMenu("Select Insert Position", sideOptions, 2);
                
                int sideChoice = safeInputNumeric<int>(cin, 1, 2, "Enter choice (1-2): ");
                
                if (sideChoice == 1) {
                    Deque<T*> tmp;
                    while (!loadedDeque.isEmpty()) {
                        T* obj = loadedDeque.peekFirst();
                        loadedDeque.popFront();
                        tmp.pushFront(obj);
                    }
                    while (!tmp.isEmpty()) {
                        T* obj = tmp.peekFirst();
                        tmp.popFront();
                        deque.pushFront(obj);
                    }
                } else {
                    while (!loadedDeque.isEmpty()) {
                        T* obj = loadedDeque.peekFirst();
                        loadedDeque.popFront();
                        deque.pushBack(obj);
                    }
                }
                
                cout << "Loaded all objects from text file and inserted at " << (sideChoice == 1 ? "front" : "back") << ": people.txt" << endl;
            } catch (const FileException& e) {
                cout << "File error: " << e.what() << endl;
            }
        }
    } else {
        if (loadTypeChoice == 1) {
            BinaryFile<T> file("people.bin");
            try {
                T* obj = file.readRecord();
                if (obj == nullptr) {
                    cout << "File is empty or read error." << endl;
                    return;
                }
                
                string sideOptions[2] = {"1. Insert at Front", "2. Insert at Back"};
                drawMenu("Select Insert Position", sideOptions, 2);
                
                int sideChoice = safeInputNumeric<int>(cin, 1, 2, "Enter choice (1-2): ");
                
                if (sideChoice == 1) {
                    deque.pushFront(obj);
                } else {
                    deque.pushBack(obj);
                }
                
                cout << "Loaded object from binary file and inserted at " << (sideChoice == 1 ? "front" : "back") << ": people.bin" << endl;
            } catch (const FileException& e) {
                cout << "File error: " << e.what() << endl;
            }
        } else {
            BinaryFile<T> file("people.bin");
            try {
                Deque<T*> loadedDeque = file.readAllRecords();
                
                if (loadedDeque.isEmpty()) {
                    cout << "File is empty." << endl;
                    return;
                }
                
                string sideOptions[2] = {"1. Insert at Front", "2. Insert at Back"};
                drawMenu("Select Insert Position", sideOptions, 2);
                
                int sideChoice = safeInputNumeric<int>(cin, 1, 2, "Enter choice (1-2): ");
                
                if (sideChoice == 1) {
                    Deque<T*> tmp;
                    while (!loadedDeque.isEmpty()) {
                        T* obj = loadedDeque.peekFirst();
                        loadedDeque.popFront();
                        tmp.pushFront(obj);
                    }
                    while (!tmp.isEmpty()) {
                        T* obj = tmp.peekFirst();
                        tmp.popFront();
                        deque.pushFront(obj);
                    }
                } else {
                    while (!loadedDeque.isEmpty()) {
                        T* obj = loadedDeque.peekFirst();
                        loadedDeque.popFront();
                        deque.pushBack(obj);
                    }
                }
                
                cout << "Loaded all objects from binary file and inserted at " << (sideChoice == 1 ? "front" : "back") << ": people.bin" << endl;
            } catch (const FileException& e) {
                cout << "File error: " << e.what() << endl;
            }
        }
    }
}

template <typename T>
void runForType(const string& typeName) {
    Deque<T*> myDeque;
    int choice;
    string mainMenuOptions[10] = {
        "1. Add Object",
        "2. Remove Object",
        "3. Modify Object",
        "4. Peek Object",
        "5. Print Deque",
        "6. Search",
        "7. Sort",
        "8. Save to File",
        "9. Load from File",
        "10. Exit"
    };

    do {
        drawMenu("Main Menu - " + typeName, mainMenuOptions, 10);

        choice = safeInputNumeric<int>(cin, 1, 10, "Enter choice (1-10): ");

        switch (choice) {
            case 1: addObject(myDeque); break;
            case 2: removeObject(myDeque); break;
            case 3: modifyObject(myDeque); break;
            case 4: peekObject(myDeque); break;
            case 5: printDeque(myDeque); break;
            case 6: searchInDeque(myDeque); break;
            case 7: sortDequeByField(myDeque); break;
            case 8: saveToFile(myDeque); break;
            case 9: loadFromFile(myDeque); break;
            case 10: clearDeque(myDeque); break;
        }
    } while (choice != 10);
}

void run() {
    string typeOptions[3] = {
        "1. UniversityTeacher",
        "2. CommissionMember",
        "3. TeacherCommissionMember"
    };
    drawMenu("Select type to work with", typeOptions, 3);
    int typeChoice = safeInputNumeric<int>(cin, 1, 3, "Enter choice (1-3): ");

    switch (typeChoice) {
        case 1:
            runForType<UniversityTeacher>("UniversityTeacher");
            break;
        case 2:
            runForType<CommissionMember>("CommissionMember");
            break;
        case 3:
            runForType<TeacherCommissionMember>("TeacherCommissionMember");
            break;
    }
}
