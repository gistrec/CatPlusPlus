#pragma once

/**
 * Типы лексем
 * Keyword - ключевое слово 
 * ArithmeticSign - арифметический знак
 * Delimiter - разделитель
 * Variable  - переменная
 * Constant  - константа
 */
enum class LexemeType { Keyword, ArithmeticSign, Delimiter, Variable, Constant };
struct Lexeme {
	LexemeType type;

	Lexeme(LexemeType type) : type(type) {};

	LexemeType getType() {
		return type;
	}
};


/**
 * Ключевые/зарезервированные слова
 */
enum class KeywordType : char { If, Else, For, While };
struct Keyword : Lexeme {
	KeywordType keyword;

    Keyword(KeywordType keyword) :
		Lexeme(LexemeType::Keyword),
		keyword(keyword)
	{};

	KeywordType getKeyword() {
		return keyword;
	}
};

/**
 * Арифметические знаки
 * Например: +, -, *, /
 */
enum class SignType : char { Add, Sub, Mul, Div, Equal, isEqual };
struct ArithmeticSign : public Lexeme {
	SignType sign;
	int priority;

	ArithmeticSign(SignType sign, int priority) :
		Lexeme(LexemeType::ArithmeticSign),
		priority(priority),
        sign(sign)
	{};

	int getPriority() {
		return priority;
	}
};

/**
 * Разделители
 * Например: ], }, ;
 * @param identifier - идентефикатор лексемы
 */
enum class DelimiterType : char { OpenBracket, CloseBracket, Space, Semicolon };
struct Delimiter : public Lexeme {
	DelimiterType delimeter;

    Delimiter(DelimiterType delimeter) :
		Lexeme(LexemeType::Delimiter),
		delimeter(delimeter)
	{};

	DelimiterType getDelimeter() {
		return delimeter;
	}
};


/**
 * Переменная
 */
enum class VariableType { Undefined, Int, Float };
struct Variable : Lexeme {
	VariableType vartype;  // Тип переменной

    bool init;   // Инициализированна ли переменная
	size_t data; // Данные переменной

	Variable(VariableType vartype = VariableType::Undefined) :
		Lexeme(LexemeType::Variable),
		vartype(vartype),
		init(false),
		data(0)
	{};

	bool isInit() {
		return init;
	}

	VariableType getVarType() {
		return vartype;
	}

	void setVarType(VariableType new_vartype) {
		vartype = new_vartype;
	}

	size_t getData() {
		return data;
	}

	void setData(size_t new_data) {
		init = true;
		data = new_data;
	}
};

/**
 * Константа
 * @param value - значение константы
 * @param type  - тип значения
 */
struct Constant : Lexeme {
    VariableType vartype;

	size_t data; // Данные переменной

	Constant(VariableType vartype, size_t data) :
		Lexeme(LexemeType::Constant),
		vartype(vartype),
		data(data)
	{};

	VariableType getVarType() {
		return vartype;
	}

	size_t getData() {
		return data;
	}
};