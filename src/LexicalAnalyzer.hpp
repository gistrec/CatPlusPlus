#pragma once
#include <map>
#include <list>
#include <vector>
#include <string>
#include <algorithm>

#include "Token.hpp"
#include "LexemeTables.hpp"

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
    map<LexemesName, LexemesTable> lexemsTable;

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
};

/**
 * Считываем весь файл и передаем в функцию parseString
 */
istream& operator >> (istream &in, LexicalAnalyzer &analyzer) {
    string line;

    string file((istreambuf_iterator<char>(in)), istreambuf_iterator<char>());
    analyzer.parseString(file);

    return in;
};