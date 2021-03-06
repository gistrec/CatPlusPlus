#pragma once
#include <string>

using std::string;

/**
 * Типы лексем
 * Keyword   - ключевое слово
 * Delimiter - разделитель
 * Sign  - арифметический знак
 * Const - константа
 * Var   - переменная
 */
enum LexemeType : int { Keyword, Sign, Delimiter, Var, Const };
struct Lexeme {
	int type;
	int subtype; // Одно из KeywordType::, SignType::, DelimiterType::

	string name; // Название лексемы

	Lexeme(int type, int subtype, string name) :
		type(type),
		subtype(subtype),
		name(name)
	{};

	int    getType()     { return type;    } // Получить номер таблицы
	int    getSubtype()  { return subtype; } // Получить позицию в таблице
	int    getPosition() { return subtype; }
	string getName()     { return name;    }

	void setPosition(int pos) { subtype = pos; }
};



enum KeywordType   : int { Int, If, Else };
enum SignType      : int { Add, Sub, Mul, isEqual, isNoEqual, isLess, Equal };
enum DelimiterType : int { OpenBracket, CloseBracket, OpenBrace, CloseBrace, Space, LineBreak, Comment };
enum VariableType  : int { Undefined, Integer };



/**
 * Переменная
 * @constructor name - название переменной
 * @constructor vartype - тип значения
 */
struct Variable : public Lexeme {
	VariableType vartype;  // Тип переменной

	bool init;   // Инициализированна ли переменная
	size_t data; // Данные переменной

	Variable(string name, VariableType vartype = VariableType::Undefined) :
		Lexeme(LexemeType::Var, 0, name),
		vartype(vartype),
		init(false),
		data(0)
	{};

	/** Геттеры */
	bool         isInit()     {  return init;     }

	VariableType getVarType() {  return vartype;  }
	string       getName()    {  return name;     }
	size_t       getData()    {  return data;     }

	/** Сеттеры */
	void setVarType(VariableType new_vartype) {
		vartype = new_vartype;
	}

	void setData(size_t new_data) {
		init = true;
		data = new_data;
	}
};

/**
 * Константа
 * @constructor name - название константы
 * @constructor vartype - тип значения
 * @constructor data - данные константы
 */
struct Constant : public Lexeme {
	VariableType vartype;

	size_t data;  // Данные переменной

	Constant(string name, VariableType vartype = VariableType::Undefined, size_t data = 0) :
		Lexeme(LexemeType::Const, 0, name),
		vartype(vartype),
		data(data)
	{};

	/** Геттеры */
	VariableType getVarType() {  return vartype;  }
	string       getName()    {  return name;     }
	size_t       getData()    {  return data;     }

	/** Сеттеры */
};