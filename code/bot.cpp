#include <iostream>
#include <string>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <vector>
#include <algorithm>

// Функция для вывода текущего времени и даты
void print_current_time(const std::string& name) {
    auto now = std::chrono::system_clock::now();
    std::time_t now_time = std::chrono::system_clock::to_time_t(now);
    std::cout << "Бот:" << name << ", Сейчас " 
              << std::put_time(std::localtime(&now_time), "%Y-%m-%d %H:%M:%S")
              << std::endl;
}
// Функция для сортировки введенного списка
void sort_list1() {
    std::cout << "Бот: Введи список для сортировки (например, \"321, 654, 987\"): ";
    std::string list;
    std::getline(std::cin, list);
    std::sort(list.begin(), list.end());
    std::cout << "Отсортированный список: " << list << std::endl;
}

// Функция для сортировки введенного списка чисел
void sort_list() {
    std::cout << "Бот: Введи список для сортировки (например, \"321, 654, 987\"): ";
    std::string list;
    std::getline(std::cin, list);

    // Парсим строку в числа
    std::vector<int> numbers;
    std::stringstream ss(list);
    std::string item;
    while (std::getline(ss, item, ',')) {
        // Удаляем пробелы
        item.erase(std::remove_if(item.begin(), item.end(), ::isspace), item.end());
        if (!item.empty()) {
            try {
                numbers.push_back(std::stoi(item));
            } catch (...) {
                std::cout << "Бот: \"" << item << "\" не является числом и будет пропущено.\n";
            }
        }
    }

    // Сортируем числа
    std::sort(numbers.begin(), numbers.end());

    // Выводим результат
    std::cout << "Отсортированный список: ";
    for (size_t i = 0; i < numbers.size(); ++i) {
        std::cout << numbers[i] << "";
        if (i != numbers.size() - 1) std::cout << ", ";
    }
    std::cout << std::endl;
}

// Вынесем логику бота в отдельную функцию
void run_bot() {
    std::string command;

    
    std::cout << "Бот: Как тебя зовут? ";
    std::string name;
    std::getline(std::cin, name);
    std::cout << "Бот: Привет, " << name << "! Я готов помочь." << std::endl;

    while (true) {
        std::cout << "\nБот: Какую команду ты хочешь выполнить? (введите \"помощь\" для списка команд)" << std::endl;
        std::cout << "Бот: Вводи команду (или \"выход\" для завершения): ";
        std::cout << "\nТы: ";
        std::getline(std::cin, command);

        if (command == "привет") {
            std::cout << "Бот: Привет! Рад тебя видеть!";
        } else if (command == "время" || command == "time") {
            print_current_time(name);
        } else if (command == "помощь" || command == "help") {
            std::cout << "Бот: Возможные команды: \"привет\", \"время\", \"помощь\", \"выход\".";
        } else if (command == "сортировать" || command == "sort") {
            sort_list();
        } else if (command == "выход" || command == "exit" || command == "quit" || command == "q") {
            std::cout << "Бот: Пока! 👋" << std::endl;
            break;
        } else {
            std::cout << "Бот: Я не понял команду. Попробуй снова." << std::endl
                      << "Возможные команды:" << std::endl
                      << "  - привет" << std::endl
                      << "  - время" << std::endl
                      << "  - помощь" << std::endl
                      << "  - выход" << std::endl;
        }
    }
}

int main() {
    run_bot();
    return 0;
}
