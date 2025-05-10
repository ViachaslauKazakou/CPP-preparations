#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>
#include <locale> // добавлено для поддержки локали

class TextFileProcessor {
    std::string filename;
    std::string content;

public:
    TextFileProcessor(const std::string& fname) : filename(fname) {
        // Открываем файл в текстовом режиме с поддержкой UTF-8
        std::ifstream file(filename);
        file.imbue(std::locale("ru_RU.UTF-8")); // Устанавливаем русскую локаль с поддержкой UTF-8
        if (file) {
            std::ostringstream ss;
            ss << file.rdbuf();
            content = ss.str();
        }
    }

    // Поиск слова в тексте, возвращает количество вхождений
    int find_word(const std::string& word) const {
        int count = 0;
        std::istringstream iss(content);
        std::string w;
        while (iss >> w) {
            if (w == word) ++count;
        }
        return count;
    }

    // Подсчет количества слов
    int word_count() const {
        int count = 0;
        std::istringstream iss(content);
        std::string w;
        while (iss >> w) ++count;
        return count;
    }

    // Размер файла (в символах)
    size_t size() const {
        return content.size();
    }

    // Создать новый файл без указанных символов (например, знаков препинания)
    void remove_chars_and_save(const std::string& chars_to_remove, const std::string& new_filename) const {
        std::string new_content = content;
        for (char ch : chars_to_remove) {
            new_content.erase(std::remove(new_content.begin(), new_content.end(), ch), new_content.end());
        }
        std::ofstream out(new_filename);
        out.imbue(std::locale("ru_RU.UTF-8")); // Устанавливаем локаль для вывода
        out << new_content;
    }

    // Создать вектор токенов (слов) из очищенного файла
    std::vector<std::string> get_tokens_from_file(const std::string& cleaned_filename) const {
        std::vector<std::string> tokens;
        std::ifstream file(cleaned_filename);
        file.imbue(std::locale("ru_RU.UTF-8")); // Устанавливаем локаль для чтения
        if (!file) {
            std::cerr << "Не удалось открыть файл: " << cleaned_filename << std::endl;
            return tokens;
        }
        std::string word;
        while (file >> word) {
            tokens.push_back(word);
        }
        return tokens;
    }

    // Сохранить токены в файл
    void save_tokens_to_file(const std::vector<std::string>& tokens, const std::string& filename) const {
        std::ofstream out(filename);
        out.imbue(std::locale("ru_RU.UTF-8")); // Устанавливаем локаль для вывода
        if (!out) {
            std::cerr << "Не удалось открыть файл для записи: " << filename << std::endl;
            return;
        }
        for (const auto& token : tokens) {
            out << token << std::endl;
        }
    }
};

// Пример использования

int main() {
    std::string user_filename;
    std::cout << "Введите имя файла для парсинга (Enter для input.txt): ";
    std::getline(std::cin, user_filename);

    if (user_filename.empty()) {
        user_filename = "input.txt";
    }

    TextFileProcessor tfp(user_filename);
    std::cout << "Слово 'рак' встречается: " << tfp.find_word("рак") << " раз(а)\n";
    std::cout << "Всего слов: " << tfp.word_count() << std::endl;
    std::cout << "Размер файла: " << tfp.size() << " символов\n";
    // tfp.remove_chars_and_save("«»\"'`,.!?;:—()-[]{}<>", "output.txt");
    tfp.remove_chars_and_save(",.!?-()-", "output.txt");

    // Получаем токены из очищенного файла
    std::vector<std::string> tokens = tfp.get_tokens_from_file("output.txt");
    std::cout << "Токены из output.txt:\n";
    for (const auto& token : tokens) {
        std::cout << token << std::endl;
    }

    // Сохраняем токены в файл tokens.txt
    tfp.save_tokens_to_file(tokens, "tokens.txt");

    return 0;
}
