#pragma once
#include "LexicalAnalyzer.hpp"

LexicalAnalyzer::LexicalAnalyzer() {
    /// Добавляем ключевые слова
    auto keywords = { "if", "else", "for", "while", "int32", "int64", "float32", "double64" };
    for (auto &keyword : keywords) {
        lexemsTable["Keywords"].push_back(new Keyword(keyword));
    }

    auto delimiters = { "\n", " ", "{", "}", ";" };
    for (auto &delimiter : delimiters) {
        lexemsTable["Delimeters"].push_back(new Delimiter(delimiter));
    }

    /// Добавляем арифметические знаки
    lexemsTable["ArithmeticSigns"] = {
        new ArithmeticSign("+", 0),
        new ArithmeticSign("-", 0),
        new ArithmeticSign("*", 1),
        new ArithmeticSign("/", 1),
        new ArithmeticSign("==", 2),
        new ArithmeticSign("=",  3)
    };
}

LexicalAnalyzer::~LexicalAnalyzer() {
    for (auto &lexemTable : lexemsTable) {
        for (auto &lexem : lexemTable.second) {
            delete lexem;
        }
    }
}

/**
 * Пробегаем по всему файлу и выдергиваем лексему между разделителями
 * Итераторы на разделители хранятся в begin и finish
 */
void LexicalAnalyzer::parseString(string file) {
    std::string::iterator begin  = file.begin(); // Указатель на начало токена
    std::string::iterator finish = file.begin(); // Указатель на разделитель

    while (finish != file.end()) {
        // Получаем итератор на разделитель
        finish = std::find_if(begin, file.end(), [&](char symbol) {
            for (auto delimeter : lexemsTable["Delimeters"]) {
                /// Разделитель - один символ (нулевой), представленный в виде строки
                if (((Delimiter*) delimeter)->identifier[0] == symbol) return true;
            }
            return false;
        });

        string lexem(begin, finish); // Лексема. Может быть пустой, если находится между двумя разделителями
        parseToken(lexem); // Добавляем лексему

        // Если не достигнут конец файла
        if (finish != file.end()) {
            parseToken(string(finish, finish + 1)); // Добавляем разделитель
            begin = finish + 1;
        }
    }
}

/**
 * Пробегаем по трем постоянным таблицам в поисках лексем
 * Если не нашлось - то пытаемся получить число (константу)
 * Иначе это новая переменная
 */
void LexicalAnalyzer::parseToken(string str) {
    for (auto &keyword : lexemsTable["Keywords"]) {
        if (((Keyword*)keyword)->identifier == str) {
            tokens.push_back(Token("Keywords", str));
            return;
        }
    }
    for (auto &keyword : lexemsTable["Delimeters"]) {
        if (((Keyword*)keyword)->identifier == str) {
            tokens.push_back(Token("Delimeters", str));
            return;
        }
    }
    for (auto &keyword : lexemsTable["ArithmeticSigns"]) {
        if (((Keyword*)keyword)->identifier == str) {
            tokens.push_back(Token("ArithmeticSigns", str));
            return;
        }
    }

    // на данном этапе лексема может быть либо числом (константой), либо переменной
    // Проверка на то, что строка состоит только из чисел
    if (std::all_of(str.begin(), str.end(), ::isdigit)) {
        // int number = std::stoll(str);
        // TODO: добавить константу
    } else {
        // TODO: добавить переменную
    }

}

#include <fstream>
int main() {
    std::ifstream input("input.catpp");
    LexicalAnalyzer analyzer;
    input >> analyzer;
    system("pause");
    return 0;
}