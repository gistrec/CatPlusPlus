#pragma once
#include "LexicalAnalyzer.hpp"

LexicalAnalyzer::LexicalAnalyzer() {
    
}

LexicalAnalyzer::~LexicalAnalyzer() {
    for (auto &lexemTable : lexemesTables) {
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
            for (auto delimeter : lexemesTables["Delimeters"]) {
                /// Разделитель - один символ (нулевой), представленный в виде строки
                if (((Delimiter*) delimeter)->identifier[0] == symbol) return true;
            }
            return false;
        });

        string lexem(begin, finish); // Лексема. Может быть пустой, если находится между двумя разделителями
        parseToken(lexem); // Добавляем лексему

        // Если не достигнут конец файла
        if (finish != file.end()) {
            string delimetr(finish, finish + 1);
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
    if (str.empty() || str == " " || str == "\n") return;

    for (auto &keyword : lexemesTables["Keywords"]) {
        if (((Keyword*) keyword)->identifier == str) {
            tokens.push_back(Token("Keywords", str));
            return;
        }
    }
    for (auto &delimeter : lexemesTables["Delimeters"]) {
        if (((Delimiter*) delimeter)->identifier == str) {
            tokens.push_back(Token("Delimeters", str));
            return;
        }
    }
    for (auto &sign : lexemesTables["ArithmeticSigns"]) {
        if (((ArithmeticSign*) sign)->identifier == str) {
            tokens.push_back(Token("ArithmeticSigns", str));
            return;
        }
    }

    // на данном этапе лексема может быть либо числом (константой), либо переменной
    // Проверка на то, что строка состоит только из чисел
    if (std::all_of(str.begin(), str.end(), ::isdigit)) {
        if (!getConstant(str)) addConstant(str);
        tokens.push_back(Token("Constants", str));
    } else {
        if (!getVariable(str)) addVariable(str);
        tokens.push_back(Token("Variables", str));
    }
}

Variable* LexicalAnalyzer::getVariable(string name) {
    auto& vars = lexemesTables["Variables"];
    auto result = std::find_if(vars.begin(), vars.end(), [&] (Lexeme* &lexeme) {
        // Если имена переменных совпадают - то переменная найдена
        if (((Variable *) lexeme)->name == name) return true;
        else return false;
    });
    if (result == vars.end()) return 0;
    else return (Variable*) *result;
}

void LexicalAnalyzer::addVariable(string name) {
    assert(getVariable(name) == 0 && "Переменная уже добавлена в таблицу");
    lexemesTables["Variables"].push_back(new Variable(name));
}

Constant* LexicalAnalyzer::getConstant(string value) {
    auto& consts = lexemesTables["Constants"];
    auto result = std::find_if(consts.begin(), consts.end(), [&](Lexeme* &lexeme) {
        // Если имена переменных совпадают - то переменная найдена
        if (((Constant *)lexeme)->value == value) return true;
        else return false;
    });
    if (result == consts.end()) return 0;
    else return (Constant*) *result;
}

void LexicalAnalyzer::addConstant(string value) {
    assert(getConstant(value) == 0 && "Константа уже добавлена в таблицу");
    lexemesTables["Constants"].push_back(new Constant(value));
}