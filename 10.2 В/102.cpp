#include <iostream>
#include <iomanip>
#include <string>
#include <Windows.h>

using namespace std;

enum Speciality {
    ComputerScience,
    Informatics,
    MathAndEconomics,
    PhysicsAndInformatics,
    LaborEducation
};

struct Grades {
    int physics;
    int math;
    union {
        int programming;
        int numericalMethods;
        int pedagogy;
    };
};

struct Student {
    string lastName;
    int course;
    Speciality speciality;
    Grades grades;
};

string getSpecialityName(Speciality speciality) {
    switch (speciality) {
    case ComputerScience: return "Комп'ютерні науки";
    case Informatics: return "Інформатика";
    case MathAndEconomics: return "Математика та економіка";
    case PhysicsAndInformatics: return "Фізика та інформатика";
    case LaborEducation: return "Трудове навчання";
    default: return "Невідома спеціальність";
    }
}

void inputStudentData(Student* student) {
    cout << "Введіть прізвище: ";
    cin >> ws;
    getline(cin, student->lastName);

    do {
        cout << "Введіть курс (1-5): ";
        cin >> student->course;
        if (student->course < 1 || student->course > 5) {
            cout << "Помилка: курс має бути від 1 до 5.\n";
        }
    } while (student->course < 1 || student->course > 5);

    int speciality;
    do {
        cout << "Виберіть спеціальність (0 - Комп'ютерні науки, 1 - Інформатика, "
            "2 - Математика та економіка, 3 - Фізика та інформатика, 4 - Трудове навчання): ";
        cin >> speciality;
        if (speciality < 0 || speciality > 4) {
            cout << "Помилка: введіть значення від 0 до 4.\n";
        }
    } while (speciality < 0 || speciality > 4);
    student->speciality = static_cast<Speciality>(speciality);

    cout << "Введіть оцінку з фізики: ";
    cin >> student->grades.physics;

    cout << "Введіть оцінку з математики: ";
    cin >> student->grades.math;

    if (student->speciality == ComputerScience) {
        cout << "Введіть оцінку з програмування: ";
        cin >> student->grades.programming;
    }
    else if (student->speciality == Informatics) {
        cout << "Введіть оцінку з чисельних методів: ";
        cin >> student->grades.numericalMethods;
    }
    else {
        cout << "Введіть оцінку з педагогіки: ";
        cin >> student->grades.pedagogy;
    }
    cout << endl;
}

void Print(const Student* students, const int N) {
    cout << "====================================================================================================================================" << endl;
    cout << "| №   | Прізвище          | Курс | Спеціальність            |  Фізика | Математика | Програмування | Чисельні методи  | Педагогіка |" << endl;
    cout << "------------------------------------------------------------------------------------------------------------------------------------" << endl;

    for (int i = 0; i < N; i++) {
        cout << "| " << setw(3) << right << i + 1 << " ";
        cout << "| " << setw(18) << left << students[i].lastName;
        cout << "| " << setw(4) << right << students[i].course << " ";
        cout << "| " << setw(25) << left << getSpecialityName(students[i].speciality);
        cout << "| " << setw(7) << right << students[i].grades.physics << " ";
        cout << "| " << setw(10) << right << students[i].grades.math << " ";

        if (students[i].speciality == ComputerScience) {
            cout << "| " << setw(13) << right << students[i].grades.programming << " ";
            cout << "| " << setw(16) << right << " " << " ";
            cout << "| " << setw(10) << right << " " << " |";
        }
        else if (students[i].speciality == Informatics) {
            cout << "| " << setw(13) << right << " " << " ";
            cout << "| " << setw(16) << right << students[i].grades.numericalMethods << " ";
            cout << "| " << setw(10) << right << " " << " |";
        }
        else {
            cout << "| " << setw(13) << right << " " << " ";
            cout << "| " << setw(16) << right << " " << " ";
            cout << "| " << setw(10) << right << students[i].grades.pedagogy << " |";
        }

        cout << endl;
    }

    cout << "====================================================================================================================================" << endl;
}

void PhysicalSort(Student* students, const int N) {
    for (int i = 0; i < N - 1; i++) {
        for (int j = 0; j < N - i - 1; j++) {
            if (students[j].course > students[j + 1].course ||
                (students[j].course == students[j + 1].course && students[j].grades.math < students[j + 1].grades.math) ||
                (students[j].course == students[j + 1].course && students[j].grades.math == students[j + 1].grades.math && students[j].lastName < students[j + 1].lastName)) {
                swap(students[j], students[j + 1]);
            }
        }
    }
}

void IndexSort(const Student* students, int* indexArray, const int N) {
    for (int i = 0; i < N; i++)
        indexArray[i] = i;

    for (int i = 0; i < N - 1; i++) {
        for (int j = 0; j < N - i - 1; j++) {
            int a = indexArray[j];
            int b = indexArray[j + 1];
            if (students[a].course > students[b].course ||
                (students[a].course == students[b].course && students[a].grades.math < students[b].grades.math) ||
                (students[a].course == students[b].course && students[a].grades.math == students[b].grades.math && students[a].lastName > students[b].lastName)) {
                swap(indexArray[j], indexArray[j + 1]);
            }
        }
    }
}

void PrintIndexSorted(const Student* students, const int* indexArray, const int N) {
    cout << "====================================================================================================================================" << endl;
    cout << "| №   | Прізвище          | Курс | Спеціальність            |  Фізика | Математика | Програмування | Чисельні методи  | Педагогіка |" << endl;
    cout << "------------------------------------------------------------------------------------------------------------------------------------" << endl;

    for (int i = 0; i < N; i++) {
        int idx = indexArray[i];
        cout << "| " << setw(3) << right << i + 1 << " ";
        cout << "| " << setw(18) << left << students[idx].lastName;
        cout << "| " << setw(4) << right << students[idx].course << " ";
        cout << "| " << setw(25) << left << getSpecialityName(students[idx].speciality);
        cout << "| " << setw(7) << right << students[idx].grades.physics << " ";
        cout << "| " << setw(10) << right << students[idx].grades.math << " ";

        if (students[idx].speciality == ComputerScience) {
            cout << "| " << setw(13) << right << students[idx].grades.programming << " ";
            cout << "| " << setw(16) << right << " " << " ";
            cout << "| " << setw(10) << right << " " << " |";
        }
        else if (students[idx].speciality == Informatics) {
            cout << "| " << setw(13) << right << " " << " ";
            cout << "| " << setw(16) << right << students[idx].grades.numericalMethods << " ";
            cout << "| " << setw(10) << right << " " << " |";
        }
        else {
            cout << "| " << setw(13) << right << " " << " ";
            cout << "| " << setw(16) << right << " " << " ";
            cout << "| " << setw(10) << right << students[idx].grades.pedagogy << " |";
        }

        cout << endl;
    }

    cout << "====================================================================================================================================" << endl;
}

int BinarySearch(const Student* students, const int* indexArray, const int N, const string& lastName, int course, int mathGrade) {
    int left = 0, right = N - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        int idx = indexArray[mid];

        if (students[idx].course == course && students[idx].grades.math == mathGrade && students[idx].lastName == lastName)
            return idx;
        else if (students[idx].course < course ||
            (students[idx].course == course && students[idx].grades.math < mathGrade) ||
            (students[idx].course == course && students[idx].grades.math == mathGrade && students[idx].lastName > lastName))
            left = mid + 1;
        else
            right = mid - 1;
    }

    return -1;
}

void displayMenu() {
    cout << "\nМеню:\n";
    cout << "1. Додати студента\n";
    cout << "2. Відсортувати фізично\n";
    cout << "3. Відсортувати за індексом\n";
    cout << "4. Вивести студентів\n";
    cout << "5. Пошук студента\n";
    cout << "6. Вийти\n";
    cout << "Виберіть опцію: ";
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int N;
    cout << "Введіть кількість студентів: ";
    cin >> N;

    Student* students = new Student[N];
    int* indexArray = new int[N];

    int studentCount = 0;
    bool exit = false;

    while (!exit) {
        displayMenu();
        int option;
        cin >> option;

        switch (option) {
        case 1:
            if (studentCount < N) {
                inputStudentData(&students[studentCount]);
                studentCount++;
            }
            else {
                cout << "Досягнуто максимальної кількості студентів.\n";
            }
            break;

        case 2:
            PhysicalSort(students, studentCount);
            cout << "Масив відсортовано фізично.\n";
            break;

        case 3:
            IndexSort(students, indexArray, studentCount);
            cout << "Масив відсортовано за індексом.\n";
            break;

        case 4:
            Print(students, studentCount);
            break;

        case 5: {
            string searchLastName;
            int searchCourse, searchMathGrade;

            cout << "\nВведіть прізвище студента для пошуку: ";
            cin >> ws;
            getline(cin, searchLastName);
            cout << "Введіть курс студента: ";
            cin >> searchCourse;
            cout << "Введіть оцінку з математики: ";
            cin >> searchMathGrade;

            int foundIdx = BinarySearch(students, indexArray, studentCount, searchLastName, searchCourse, searchMathGrade);
            if (foundIdx != -1) {
                cout << "\nСтудента знайдено:\n";
                Print(&students[foundIdx], 1);
            }
            else {
                cout << "Студента не знайдено.\n";
            }
            break;
        }

        case 6:
            exit = true;
            break;

        default:
            cout << "Неправильний вибір. Будь ласка, спробуйте ще раз.\n";
        }
    }

    delete[] students;
    delete[] indexArray;

    return 0;
}