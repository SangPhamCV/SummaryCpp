#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <limits>

struct DisplayFormat {
    size_t widthIndex{ 6 }, widthFullname{ 32 }, widthAge{ 8 }, widthScore{ 12 };

    void printHeader() const {
        std::cout << std::left;
        std::cout << "|" << std::setw(widthIndex - 1) << "STT" << "|" <<
            std::setw(widthFullname - 1) << "Ho va ten" << "|" <<
            std::setw(widthAge - 1) << "Tuoi" << "|" <<
            std::setw(widthScore - 1) << "Diem so" << "|" << std::endl;
    }

    void printSeparator() const {
        for (size_t i{ 0 }; i < widthIndex + widthFullname + widthAge + widthScore + 1; i++) {
            if (i == 0 ||
                i == widthIndex ||
                i == widthIndex + widthFullname ||
                i == widthIndex + widthFullname + widthAge ||
                i == widthIndex + widthFullname + widthAge + widthScore) {
                std::cout << "+";
            }
            else {
                std::cout << "-";
            }
        }
        std::cout << std::endl;
    }
};

enum class SortCriteria {
    NAME,
    AGE,
    SCORE
};

struct Person {
    std::string fullname;
    int age;
    double score;
    size_t index;
    Person* next;

    Person(const std::string& fn, const int& a, const double& sc) : fullname(fn), age(a), score(sc), next(NULL) {}
};

struct PersonList {
    DisplayFormat displayFormat;
    Person* head = NULL;

    ~PersonList() {
        while (head) {
            Person* temp = head;
            head = head->next;
            delete temp;
        }
    }

    bool checkEmptyList() {
        if (head == NULL) {
            std::cout << "Danh sach trong!" << std::endl;
            return true;
        }
        return false;
    }

    size_t index() const {
        size_t index{ 0 };
        for (Person* p = head; p != NULL; p = p->next) {
            index = p->index;
        }
        return index;
    }

    void append(Person* person) {
        if (head == NULL) {
            head = person;
            head->index = 1;
        }
        else {
            Person* current = head;
            while (current->next != NULL) {
                current = current->next;
            }
            current->next = person;
            current->next->index = current->index + 1;
        }
    }

    void print(const Person* p) const {
        std::cout << "|" << std::setw(displayFormat.widthIndex - 1) << p->index << "|" <<
            std::setw(displayFormat.widthFullname - 1) << p->fullname << "|" <<
            std::setw(displayFormat.widthAge - 1) << p->age << "|" <<
            std::setw(displayFormat.widthScore - 1) << p->score << "|" << std::endl;
    }

    void edit(size_t index, const std::string& field, const std::string& newValue) {
        Person* current = head;
        while (current != NULL) {
            if (current->index == index) {
                if (field == "fullname") {
                    current->fullname = newValue;
                }
                else if (field == "age") {
                    current->age = std::stoi(newValue);
                }
                else if (field == "score") {
                    current->score = std::stod(newValue);
                }
                return;
            }
            current = current->next;
        }
    }

    void remove(size_t index) {
        if (index == 1) {
            Person* temp = head;
            head = head->next;
            delete temp;

            Person* current = head;
            while (current != NULL) {
                current->index = current->index - 1;
                current = current->next;
            }
            return;
        }

        Person* current = head;
        while (current != NULL) {
            if (current->index == index - 1) {
                Person* temp = current->next;
                current->next = temp->next;
                delete temp;

                Person* changeIndex = current->next;
                while (changeIndex != NULL) {
                    changeIndex->index = changeIndex->index - 1;
                    changeIndex = changeIndex->next;
                }
                break;
            }
            current = current->next;
        }
    }

    void findByName(const std::string& ch) {

        Person* current = head;
        size_t found;
        bool foundChar{ false };
        bool boolDisplayFormat{ false };

        while (current != NULL) {
            found = current->fullname.find(ch);
            if (found != std::string::npos) {
                if (boolDisplayFormat == false) {
                    displayFormat.printSeparator();
                    displayFormat.printHeader();
                    displayFormat.printSeparator();
                    boolDisplayFormat = true;
                }
                foundChar = true;
                print(current);
            }
            current = current->next;
        }

        if (foundChar == false) {
            std::cout << "\tKhong tim thay sinh vien co ky tu " << ch << std::endl;
        }
        else {
            displayFormat.printSeparator();
        }
    }

    void sort(SortCriteria criteria) {

        bool swapped;
        Person* lastSorted = NULL;
        do {
            swapped = false;
            Person* current = head;
            Person* prev = NULL;

            while (current->next) {
                Person* next = current->next;
                if (compare(current, next, criteria)) {
                    if (prev) {
                        prev->next = next;
                    }
                    else {
                        head = next;
                    }
                    current->next = next->next;
                    next->next = current;
                    prev = next;

                    swapped = true;
                }
                else {
                    prev = current;
                    current = next;
                }
            }
            lastSorted = current;
        } while (swapped);
    }

    bool compare(Person* a, Person* b, SortCriteria criteria) {
        switch (criteria) {
        case SortCriteria::NAME:
            return a->fullname > b->fullname;
        case SortCriteria::AGE:
            return a->age > b->age;
        case SortCriteria::SCORE:
            return a->score > b->score;
        }
        return false;
    }
};

void loadPerson(const std::string& filename, PersonList* list);
void printList(PersonList* list);
void addPerson(PersonList* list);
void editPerson(PersonList* list);
void removePerson(PersonList* list);
void findPerson(PersonList* list);
void statisticPerson(PersonList* list);
void sortPerson(PersonList* list);
void updateData(std::string filename, PersonList* list);

void printListMenu();
void waitForKeyPress();

int main() {
    const std::string filename = "Data.txt";
    PersonList* list = new PersonList();
    loadPerson(filename, list);

    int command;
    do {
        printListMenu();
        std::cout << std::endl;
        std::cout << "Nhap lenh: ";
        std::cin >> command;

        if (command < 1 || command > 9) {
            std::cout << "Lenh khong hop le, nhap lai! " << std::endl;
            continue;
        }

        switch (command) {
        case 1: printList(list); break;
        case 2: addPerson(list); break;
        case 3: editPerson(list); break;
        case 4: removePerson(list); break;
        case 5: findPerson(list); break;
        case 6: sortPerson(list); break;
        case 7: statisticPerson(list); break;
        case 8: updateData(filename, list); break;
        case 9: std::cout << "[9] Thoat chuong trinh" << std::endl; break;
        }

        if (command != 9) {
            waitForKeyPress();
        }
    } while (command != 9);
    delete list;
    return 0;
}

void loadPerson(const std::string& filename, PersonList* list) {
    std::ifstream input(filename);
    std::string line;

    while (getline(input, line)) {
        std::string delimiter{ ";" };
        size_t pos{ 0 };
        size_t fieldIndex{ 0 };

        std::string fullname;
        int age;
        double score;

        while ((pos = line.find(delimiter)) != std::string::npos) {
            std::string token = line.substr(0, pos);
            if (fieldIndex == 0) {
                fullname = token;
            }
            else if (fieldIndex == 1) {
                age = std::stoi(token);
            }
            line.erase(0, pos + delimiter.length());
            fieldIndex++;
        }
        score = std::stod(line);
        list->append(new Person(fullname, age, score));
    }
}

void printList(PersonList* list) {

    DisplayFormat displayFormat;
    std::cout << "[1] Danh sach sinh vien: " << std::endl;

    if (list->checkEmptyList()) return;


    displayFormat.printSeparator();
    displayFormat.printHeader();
    displayFormat.printSeparator();

    Person* current = list->head;
    while (current != NULL) {
        list->print(current);
        current = current->next;
    }
    displayFormat.printSeparator();
}

void addPerson(PersonList* list) {
    if (list->checkEmptyList()) return;

    std::string fullname;
    int age;
    double score;

    std::cout << "[2] Them sinh vien" << std::endl;;
    std::cout << "\t(?) Nhap ten: ";
    std::cin >> fullname;
    std::cout << "\t(?) Nhap tuoi: ";
    std::cin >> age;
    std::cout << "\t(?) Nhap diem: ";
    std::cin >> score;

    std::cout << "\t(!) Da them sinh vien co ten:  " << fullname <<
        ", tuoi: " << age << ", diem so: " << score << std::endl;

    list->append(new Person(fullname, age, score));
}

void editPerson(PersonList* list) {
    if (list->checkEmptyList()) return;

    std::string fullname, newValue;
    int age, choosen;
    double score;
    size_t index;

    std::cout << "[3] Sua thong tin sinh vien" << std::endl;;
    std::cout << "\t(?) Nhap STT cua sinh vien can sua: ";
    std::cin >> index;
    std::cout << "\t(!) Ban muon sua gi: " << std::endl;
    std::cout << "\t\t1 - Ten" << std::endl;
    std::cout << "\t\t2 - Tuoi" << std::endl;
    std::cout << "\t\t3 - Diem" << std::endl;
    std::cout << "\t\t(?) - Chon: ";
    std::cin >> choosen;

    if (choosen == 1) {
        std::cout << "Nhap ten: ";
        std::cin.ignore();
        std::getline(std::cin, fullname);
        std::cout << "Da sua ten sinh vien co so thu tu: " << index << std::endl;
        list->edit(index, "fullname", fullname);
    }
    else if (choosen == 2) {
        std::cout << "Nhap tuoi: ";
        std::cin >> age;
        newValue = std::to_string(age);
        std::cout << "Da sua tuoi sinh vien co so thu tu: " << index << std::endl;
        list->edit(index, "age", newValue);
    }
    else if (choosen == 3) {
        std::cout << "Nhap diem: ";
        std::cin >> score;
        newValue = std::to_string(score);
        std::cout << "Da sua tuoi sinh vien co so thu tu: " << index << std::endl;
        list->edit(index, "score", newValue);
    }
}

void removePerson(PersonList* list) {
    if (list->checkEmptyList()) return;

    size_t index;

    std::cout << "[4] Xoa sinh vien" << std::endl;;
    std::cout << "\t(?) Nhap STT cua sinh vien muon xoa: ";
    std::cin >> index;
    std::cout << "\t(!) Da xoa sinh vien co STT: " << index << std::endl;
    list->remove(index);
}

void findPerson(PersonList* list) {
    if (list->checkEmptyList()) return;

    std::string ch;
    std::cout << "[5] Tim kiem" << std::endl;;
    std::cout << "\t(?) Nhap ki tu: ";
    std::cin >> ch;
    list->findByName(ch);
}

void sortPerson(PersonList* list) {
    if (list->checkEmptyList()) return;

    size_t choosen;

    std::cout << "[6] Sap xep" << std::endl;;
    std::cout << "\t(!) Sap xep the nao: " << std::endl;
    std::cout << "\t\t1 - Sap xep theo ten ABC" << std::endl;
    std::cout << "\t\t2 - Sap xep theo tuoi tang dan" << std::endl;
    std::cout << "\t\t3 - Sap xep theo diem tang dan" << std::endl;
    std::cout << "\t(?) - Chon: ";
    std::cin >> choosen;

    if (choosen == 1) {
        list->sort(SortCriteria::NAME);
    }
    else if (choosen == 2) {
        list->sort(SortCriteria::AGE);
    }
    else if (choosen == 3) {
        list->sort(SortCriteria::SCORE);
    }
    printList(list);
}

void statisticPerson(PersonList* list) {
    if (list->checkEmptyList()) return;

    Person* current = list->head;
    int countTotal{ 0 }, countVeryGood{ 0 }, countGood{ 0 }, countBad{ 0 };
    double sumScore{ 0 }, greatScore{ 0 };

    while (current != NULL) {
        sumScore += current->score;
        countTotal++;

        if (current->score >= 8) {
            countVeryGood++;
        }
        else if (current->score > 5) {
            countGood++;
        }
        else {
            countBad++;
        }
        if (greatScore <= current->score) {
            greatScore = current->score;
        }
        current = current->next;
    }

    double avg = sumScore / countTotal;
    double percentVeryGoodStudent = (static_cast<double>(countVeryGood) / countTotal) * 100;
    double percentGoodStudent = (static_cast<double>(countGood) / countTotal) * 100;
    double percentBadStudent = (static_cast<double>(countBad) / countTotal) * 100;

    std::cout << "[7] Thong ke" << std::endl;;
    std::cout << "\t(!) Diem trung binh ca lop: " << avg << std::endl;
    std::cout << "\t(!) Ti le sinh vien gioi: " << percentVeryGoodStudent << "%" << std::endl;
    std::cout << "\t(!) Ti le sinh vien kha: " << percentGoodStudent << "%" << std::endl;
    std::cout << "\t(!) Ti le sinh vien kem: " << percentBadStudent << "%" << std::endl;
    std::cout << "\t(!) Sinh vien dat diem cao nhat (" << greatScore << ") la: " << std::endl;

    current = list->head;
    while (current != NULL) {
        if (current->score == greatScore) {
            std::cout << "\t\t" << current->fullname << std::endl;
        }
        current = current->next;
    }
}

void updateData(std::string filename, PersonList* list) {
    std::ofstream output(filename);

    Person* current = list->head;
    while (current != NULL) {
        output << current->fullname << ";" << current->age << ";" << current->score << std::endl;
        current = current->next;
    }
    output.close();

    std::cout << "[7] Luu thong tin" << std::endl;;
    std::cout << "\t(!) Da luu du lieu thanh cong: " << std::endl;
}

void printListMenu() {
    std::cout << "Danh sach thao tac: " << std::endl;
    std::cout << "1 - In danh sach SV " << std::endl;
    std::cout << "2 - Them " << std::endl;
    std::cout << "3 - Sua " << std::endl;
    std::cout << "4 - Xoa " << std::endl;
    std::cout << "5 - Tim kiem " << std::endl;
    std::cout << "6 - Sap xep " << std::endl;
    std::cout << "7 - Thong ke " << std::endl;
    std::cout << "8 - Sao luu " << std::endl;
    std::cout << "9 - Thoat " << std::endl;
}

void waitForKeyPress() {
    std::cout << "Press any key to continue...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
    std::cout << std::endl;
}
