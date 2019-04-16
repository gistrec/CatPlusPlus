#pragma once
#include <map>
#include <list>
#include <vector>
#include <string>
#include <cassert>
#include <algorithm>

#include "Token.hpp"
#include "Lexemes.hpp"

using std::map;
using std::list;
using std::vector;
using std::string;
using std::istream;
using std::istreambuf_iterator;


typedef string LexemesName;
typedef vector<Lexeme*> LexemesTable;


/**
 * Первая фаза компиляции - лексический анализ
 *
 * Лексический анализатор читает поток символов, составляющих исходную программу,
 * и группирует эти символы в значащие последовательности, называющиеся лексемами.
 *
 * Для каждой лексемы анализатор строит выходной токен (Token) вида <Имя токена, значение атрибута>
 */
class LexicalAnalyzer {
private:
    /// Набор таблиц с лексемами
    map<LexemesName, LexemesTable> lexemesTables;

    /// Список токенов
    list<Token> tokens;

public:
    /// Заполняем постоянные таблицы (ключевые слова, знаки операции и разделители)
    LexicalAnalyzer();
    ~LexicalAnalyzer();

    /// Делим строку разделителями и добавляем токен для каждой лексемы
    void parseString(string);
    /// Получаем токен из строки и добавляем его в список токенов
    void parseToken(string);

    Variable* getVariable(string name); /// Получаем переменную по id
    void addVariable(string name);      /// Добавляем переменную в таблицу переменных

    Constant* getConstant(string value); /// Получаем константу по id
    void addConstant(string value);       /// Добавляем константу  в таблицу констант
};