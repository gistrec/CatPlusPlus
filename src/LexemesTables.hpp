#pragma once
#include <cassert>
#include <string>
#include <vector>
#include <map>

#include "Lexemes.hpp"

using std::string;
using std::vector;
using std::pair;
using std::map;
 

class LexemesTables {
public:
	vector<Lexeme> keywords;   // Ключевые слова
	vector<Lexeme> delimiters; // Разделители
	vector<Lexeme> signs;      // Арифметические знаки

	vector<Variable> variables; // Переменные
	vector<Constant> constants; // Константы

	LexemesTables();

	/**
	 * Поиск лексемы среди константных таблиц
	 * По строке или номеру таблицы и позиции в таблице
	 */
	Lexeme* getLexeme(const string& name);
	Lexeme* getLexeme(int type, int subtype);

	/**
	 * Добавляем/получаем переменную в таблице переменных
	 * int - позиция в таблице
	 */
	int addVariable(Variable &variable);
	Variable* getVariable(int position);
	Variable* getVariable(string name);

	int addConstant(Constant &constant);
	Constant* getConstant(int position);
	Constant* getConstant(string name);
};