#pragma once
#include "LexicalAnalyzer.hpp"

typedef std::string LexemesName;
typedef std::string LexemeName;

/**
 * Токен лексемы
 * @param LexemesName - название таблицы, в которой лежит лексема
 * @param identifier - идентефикатор лексемы (название)
 */
struct Token {
    LexemesName name;
    LexemeName identifier;

    Token(LexemesName name, LexemeName identifier) :
        : name(name), identifier(identifier) {};
};