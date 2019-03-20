#pragma once
#include <functional>
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
	map<KeywordType, Keyword> keywords;
	map<DelimiterType, Delimiter> delimiters;
	map<SignType, ArithmeticSign> signs;

	map<string, Variable> variables;
	map<string, Constant> constants;

	LexemesTables();

	/**
	 * Поиск лексемы среди константных таблиц по строке
	 * @param name - строка, например 'if' или 'int'
	 */
	/// TODO TODO TODO TODO TODOD
	Lexeme* findConstanLexeme(const string& name);
	
	/**
	 * Поиск лексемы по типу и подтипу
	 * @param type - тип лексемы
	 * @param subtype - подтип (например, Keyword::If или Delimiter::Space)
	 */
	Lexeme* getLexeme(LexemeType type, int subtype);

	void addVariable(const string& name, Variable &constant);
	Variable* getVariable(const string& name) const;
};