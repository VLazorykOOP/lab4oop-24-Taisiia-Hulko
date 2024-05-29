#include <iostream>
#include <map>
#include <string>
#include <stdexcept>

void executeVector3FCode();
void executeAssociatedEntitiesCode();

// Код 1
class Vector3F {
private:
    float x, y, z;
    int state; // код помилки

public:
    // Конструктори
    Vector3F() : x(0.0), y(0.0), z(0.0), state(0) {}

    Vector3F(float x_val, float y_val, float z_val) : x(x_val), y(y_val), z(z_val), state(0) {}

    Vector3F(float* arr) : state(0) {
        if (arr == nullptr) {
            state = 1; // Помилка: передано nullptr
        }
        else {
            x = arr[0];
            y = arr[1];
            z = arr[2];
        }
    }

    // Деструктор
    ~Vector3F() {
        std::cout << "Vector destroyed" << std::endl;
    }

    // Перевантаження операторів

    // Унарні префіксні/постфіксні ++ та --
    Vector3F& operator++() {
        ++x;
        ++y;
        ++z;
        return *this;
    }

    Vector3F operator++(int) {
        Vector3F temp(*this);
        ++(*this);
        return temp;
    }

    // Унарні логічні ! та побітові ~
    bool operator!() {
        return !(x == 0.0 && y == 0.0 && z == 0.0);
    }

    Vector3F operator~() {
        return Vector3F(-y, x, z); // просто приклад перпендикулярного вектора
    }

    // Унарний арифметичний -
    Vector3F operator-() {
        return Vector3F(-x, -y, -z);
    }

    // Присвоєння =
    Vector3F& operator=(const Vector3F& other) {
        if (this != &other) {
            x = other.x;
            y = other.y;
            z = other.z;
            state = other.state;
        }
        return *this;
    }

    // Присвоєння з +=
    Vector3F& operator+=(const Vector3F& other) {
        x += other.x;
        y += other.y;
        z += other.z;
        return *this;
    }

    // Присвоєння з *=
    Vector3F& operator*=(float scalar) {
        x *= scalar;
        y *= scalar;
        z *= scalar;
        return *this;
    }

    // Оператори порівняння
    bool operator==(const Vector3F& other) const {
        return x == other.x && y == other.y && z == other.z;
    }

    bool operator!=(const Vector3F& other) const {
        return !(*this == other);
    }

    // Функція-операція порівняння
    bool compareWith(const Vector3F& other) const {
        return x > other.x && y > other.y && z > other.z;
    }

    // Оператор індексації []
    float& operator[](int index) {
        if (index == 0)
            return x;
        else if (index == 1)
            return y;
        else if (index == 2)
            return z;
        else {
            state = 2; // Помилка: невірний індекс
            return z; // Звертаємось до z, але змінюємо код помилки
        }
    }

    // Функція-операція порівняння
    bool operator>(const Vector3F& other) const {
        return (x > other.x && y > other.y && z > other.z);
    }

    bool operator>=(const Vector3F& other) const {
        return (x >= other.x && y >= other.y && z >= other.z);
    }

    bool operator<(const Vector3F& other) const {
        return !(*this >= other);
    }

    bool operator<=(const Vector3F& other) const {
        return !(*this > other);
    }

    // Виклик функції ()
    void operator()() {
        std::cout << "(" << x << ", " << y << ", " << z << ")" << std::endl;
    }

    // Функція для отримання кількості об'єктів
    static int getCount() {
        // Ви можете використовувати якусь глобальну змінну або статичну в класі
        // для підрахунку кількості створених об'єктів
        // Наприклад:
        // static int count = 0;
        // return count;
        return 0; // поки що повертаємо 0, оскільки логіку лічильника треба додати
    }
};

// Код 2
class AssociatedEntities {
private:
    std::map<std::string, std::string> data;

public:
    // Функція для додавання асоційованих сутностей
    void addEntity(const std::string& key, const std::string& value) {
        data[key] = value;
    }

    // Перевантаження оператора індексації []
    std::string& operator[](const std::string& key) {
        if (data.find(key) != data.end()) {
            return data[key];
        }
        else {
            throw std::out_of_range("Key not found");
        }
    }

    // Перевантаження дружньої операції виведення <<
    friend std::ostream& operator<<(std::ostream& os, const AssociatedEntities& ae) {
        for (const auto& pair : ae.data) {
            os << pair.first << ": " << pair.second << std::endl;
        }
        return os;
    }

    // Перевантаження дружньої операції введення >>
    friend std::istream& operator>>(std::istream& is, AssociatedEntities& ae) {
        std::string key, value;
        is >> key >> value;
        ae.addEntity(key, value);
        return is;
    }
};

void executeVector3FCode() {
    float x, y, z;
    std::cout << "Enter x: ";
    std::cin >> x;
    std::cout << "Enter y: ";
    std::cin >> y;
    std::cout << "Enter z: ";
    std::cin >> z;

    Vector3F vec1(x, y, z);

    // Приклади використання операторів
    ++vec1;
    vec1();

    Vector3F vec2 = ~vec1;
    vec2();
}

void executeAssociatedEntitiesCode() {
    AssociatedEntities entities;

    // Додавання асоційованих сутностей
    entities.addEntity("123456789", "Іванов Іван Іванович");
    entities.addEntity("987654321", "Петров Петро Петрович");

    std::cout << "Асоційовані сутності:" << std::endl;
    std::cout << entities << std::endl;

    // Перевантажений оператор індексації []
    try {
        std::cout << "Пошук за ключем 123456789: " << entities["123456789"] << std::endl;
        std::cout << "Пошук за ключем 555555555: " << entities["555555555"] << std::endl;
    }
    catch (const std::out_of_range& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

int main() {
    setlocale(LC_CTYPE, "ukr");
    int choice;

    std::cout << "Enter 1 to execute code 1 (Vector3F) or 2 to execute code 2 (AssociatedEntities): ";
    std::cin >> choice;

    switch (choice) {
    case 1: {
        executeVector3FCode();
        break;
    }
    case 2: {
        executeAssociatedEntitiesCode();
        break;
    }
    default: {
        std::cerr << "Invalid choice." << std::endl;
        break;
    }
    }

    return 0;
}
