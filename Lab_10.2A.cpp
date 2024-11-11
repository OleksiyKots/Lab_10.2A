#include <iostream>
#include <iomanip>
#include <string>
#include <algorithm>
#include <Windows.h>
using namespace std;

// Перерахування, що представляє різні спеціальності
enum Spetsialnist { KOMPYUTERNI_NAUKY, INFORMATYKA, MATEMATYKA_TA_EKONOMIKA, FIZYKA_TA_INFORMATYKA, TRUDOVE_NAVCHANNYA };

// Структура для зберігання інформації про студента
struct Student {
    string prizv = "";                      // Прізвище студента
    int kurs = 0;                           // Номер курсу
    Spetsialnist spetsialnist = KOMPYUTERNI_NAUKY; // Спеціальність
    int ozenka_fizyka = 0;                  // Оцінка з фізики
    int ozenka_matematyka = 0;              // Оцінка з математики
    int ozenka_informatyka = 0;             // Оцінка з інформатики
};

// Прототипи функцій
void Create(Student* s, const int N);       // Функція для введення даних про студентів
void Print(const Student* s, const int N);  // Функція для виведення даних про студентів
void SortStudents(Student* s, const int N); // Функція для сортування студентів за прізвищем
int BinarySearch(Student* s, int N, const string& prizv); // Функція для пошуку студента за прізвищем

int main() {
    SetConsoleCP(1251);      // Встановити кодування для вводу
    SetConsoleOutputCP(1251); // Встановити кодування для виводу

    int N; // Кількість студентів
    cout << "Введіть кількість студентів: ";
    cin >> N;

    Student* students = new Student[N]; // Динамічний масив студентів

    int menuItem;
    // Вивід меню та обробка вибору користувача
    do {
        cout << "\nМеню:\n";
        cout << " [1] - введення даних\n";
        cout << " [2] - виведення даних\n";
        cout << " [3] - сортування студентів\n";
        cout << " [4] - пошук студента за прізвищем (бінарний пошук)\n";
        cout << " [0] - вихід\n";
        cout << "Введіть ваш вибір: ";
        cin >> menuItem;

        switch (menuItem) {
        case 1:
            Create(students, N); // Введення даних студентів
            break;
        case 2:
            Print(students, N);  // Виведення даних студентів
            break;
        case 3:
            SortStudents(students, N); // Сортування студентів за прізвищем
            break;
        case 4: {
            string prizv;
            cout << "Введіть прізвище студента для пошуку: ";
            cin.ignore();
            getline(cin, prizv);
            int index = BinarySearch(students, N, prizv); // Пошук студента за прізвищем
            if (index != -1) {
                cout << "Студент знайдений:\n";
                Print(&students[index], 1); // Виведення знайденого студента
            }
            else {
                cout << "Студента не знайдено.\n"; // Студент не знайдений
            }
            break;
        }
        case 0:
            break; // Вихід з програми
        default:
            cout << "Помилка! Слід вибрати коректний номер.\n";
        }
    } while (menuItem != 0);

    delete[] students;  // Очищення пам'яті, виділеної для студентів
    return 0;
}

// Функція для введення даних про студентів
void Create(Student* s, const int N) {
    for (int i = 0; i < N; i++) {
        cout << "Студент №" << i + 1 << ":\n";
        s[i] = Student();  // Ініціалізація всіх полів значеннями за замовчуванням
        cin.ignore();
        cout << "Прізвище: ";
        getline(cin, s[i].prizv);  // Введення прізвища
        cout << "Курс: ";
        cin >> s[i].kurs;          // Введення курсу
        cout << "Спеціальність (0 - Комп'ютерні науки, 1 - Інформатика, 2 - Математика та економіка, 3 - Фізика та інформатика, 4 - Трудове навчання): ";
        int sp;
        cin >> sp;
        s[i].spetsialnist = static_cast<Spetsialnist>(sp); // Встановлення спеціальності на основі введених даних
        cout << "Оцінка з фізики: ";
        cin >> s[i].ozenka_fizyka;    // Введення оцінки з фізики
        cout << "Оцінка з математики: ";
        cin >> s[i].ozenka_matematyka; // Введення оцінки з математики
        cout << "Оцінка з інформатики: ";
        cin >> s[i].ozenka_informatyka; // Введення оцінки з інформатики
        cout << endl;
    }
}

// Функція для виведення даних про студентів у табличному форматі
void Print(const Student* s, const int N) {
    cout << "=======================================================================================================\n";
    cout << "| №   | Прізвище     | Курс | Спеціальність       | Фізика          | Математика     | Інформатика    |\n";
    cout << "-------------------------------------------------------------------------------------------------------\n";
    for (int i = 0; i < N; i++) {
        cout << left << "| " << setw(3) << i + 1 << " ";
        cout << "| " << setw(13) << left << s[i].prizv;
        cout << "| " << setw(4) << s[i].kurs << " ";
        string spets;
        // Перетворення значення перерахування у рядок для виведення
        switch (s[i].spetsialnist) {
        case KOMPYUTERNI_NAUKY: spets = "Комп'ютерні науки"; break;
        case INFORMATYKA: spets = "Інформатика"; break;
        case MATEMATYKA_TA_EKONOMIKA: spets = "Математика та економіка"; break;
        case FIZYKA_TA_INFORMATYKA: spets = "Фізика та інформатика"; break;
        case TRUDOVE_NAVCHANNYA: spets = "Трудове навчання"; break;
        }
        cout << "| " << setw(20) << left << spets;
        cout << "| " << setw(16) << s[i].ozenka_fizyka;
        cout << "| " << setw(15) << s[i].ozenka_matematyka;
        cout << "| " << setw(14) << s[i].ozenka_informatyka;
        cout << " |\n";
    }
    cout << "=======================================================================================================\n";
}

// Функція для сортування студентів за прізвищем в алфавітному порядку
void SortStudents(Student* s, const int N) {
    sort(s, s + N, [](const Student& a, const Student& b) {
        return a.prizv < b.prizv;
        });
    cout << "Список студентів відсортовано за прізвищем.\n";
}

// Функція для виконання бінарного пошуку студента за прізвищем
int BinarySearch(Student* s, int N, const string& prizv) {
    int left = 0;
    int right = N - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (s[mid].prizv == prizv) {
            return mid; // Повертає індекс, якщо студент знайдений
        }
        if (s[mid].prizv < prizv) {
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }
    return -1;  // Повертає -1, якщо студент не знайдений
}
