#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include <windows.h>
using namespace std;

// Класс "Студент", описывающий базовые свойства и поведение студента
class Student {
private:
    std::string name;        // Имя студента
    int age;                 // Возраст студента
    double averageGrade;     // Средний балл студента

public:
    // Конструктор с параметрами, сразу вызывает сеттеры с валидацией
    Student(const std::string& name, int age, double averageGrade) {
        setName(name);
        setAge(age);
        setAverageGrade(averageGrade);
    }

    // Геттер для имени
    std::string getName() const { return name; }

    // Геттер для возраста
    int getAge() const { return age; }

    // Геттер для среднего балла
    double getAverageGrade() const { return averageGrade; }

    // Сеттер для имени с проверкой, что имя не пустое
    void setName(const std::string& newName) {
        if (newName.empty())
            throw std::invalid_argument("Имя не может быть пустым.");
        name = newName;
    }

    // Сеттер для возраста с проверкой, что он положительный
    void setAge(int newAge) {
        if (newAge <= 0)
            throw std::invalid_argument("Возраст должен быть положительным.");
        age = newAge;
    }

    // Сеттер для среднего балла с проверкой диапазона от 0 до 10
    void setAverageGrade(double newGrade) {
        if (newGrade < 0.0 || newGrade > 10.0)
            throw std::invalid_argument("Средний балл должен быть от 0 до 10.");
        averageGrade = newGrade;
    }

    // Метод для вывода информации о студенте в консоль
    void printInfo() const {
        std::cout << "Имя: " << name
            << ", Возраст: " << age
            << ", Средний балл: " << averageGrade << std::endl;
    }

    // Метод, возвращающий текстовую оценку успеваемости по среднему баллу
    std::string evaluatePerformance() const {
        if (averageGrade > 8.0)
            return "Отлично";
        else if (averageGrade >= 6.0)
            return "Хорошо";
        else if (averageGrade >= 4.0)
            return "Удовлетворительно";
        else
            return "Неудовлетворительно";
    }

    // Метод, проверяющий, является ли студент совершеннолетним (18+)
    bool isAdult() const {
        return age >= 18;
    }
};

// ===== Функции интерфейса пользователя (меню) =====

// Добавление нового студента через ввод с клавиатуры
void addStudent(std::vector<Student>& students) {
    std::string name;
    int age;
    double grade;

    std::cout << "Введите имя: ";
    std::getline(std::cin >> std::ws, name); // Ввод имени (возможно с пробелами)


    std::cout << "Введите возраст: ";
    std::cin >> age;

    std::cout << "Введите средний балл: ";
    std::cin >> grade;
    std::cin.ignore(); // Очистка ввода после чисел

    try {
        // Попытка создать объект студента с валидацией
        Student newStudent(name, age, grade);
        students.push_back(newStudent); // Добавление в список
        std::cout << "Студент добавлен успешно.\n";
    }
    catch (const std::exception& ex) {
        // Обработка ошибок при неправильных данных
        std::cerr << "Ошибка: " << ex.what() << std::endl;
    }
}

// Вывод всех студентов из списка
void showStudents(const std::vector<Student>& students) {
    if (students.empty()) {
        std::cout << "Список студентов пуст.\n";
        return;
    }

    // Цикл по всем студентам
    for (const Student& student : students) {
        student.printInfo(); // Печать информации
        std::cout << "Оценка: " << student.evaluatePerformance() << std::endl;
        std::cout << "Совершеннолетний: " << (student.isAdult() ? "Да" : "Нет") << "\n" << std::endl;
    }
}

// Основное текстовое меню программы
void menu() {
    std::vector<Student> students;

    // Заранее созданные студенты (демонстрация использования)
    try {
        students.push_back(Student("Иван", 20, 9.1));
        students.push_back(Student("Мария", 17, 7.5));
        students.push_back(Student("Алексей", 18, 5.2));
    }
    catch (const std::exception& ex) {
        std::cerr << "Ошибка при создании студента: " << ex.what() << std::endl;
    }

    int choice;
    do {
        // Отображение пунктов меню
        std::cout << "\n--- МЕНЮ ---\n";
        std::cout << "1. Добавить студента\n";
        std::cout << "2. Показать всех студентов\n";
        std::cout << "3. Выход\n";
        std::cout << "Выберите действие: ";
        std::cin >> choice;
        std::cin.ignore(); // Очистка буфера ввода после чисел

        // Обработка выбора пользователя
        switch (choice) {
        case 1:
            addStudent(students); // Добавление нового студента
            break;
        case 2:
            showStudents(students); // Вывод всех студентов
            break;
        case 3:
            std::cout << "Выход из программы.\n";
            break;
        default:
            std::cout << "Неверный выбор. Повторите попытку.\n";
            break;
        }

    } while (choice != 3); // Повторять до выхода
}

// Точка входа в программу
int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    menu(); // Запуск меню
    cin.get();
    return 0;
}
