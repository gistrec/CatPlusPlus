#pragma once
#include <string>

using std::string;


struct Lexeme {};

/**
 * Ключевые/зарезервированные слова
 * Например: if, else, for, while, struct
 * @param identifier - идентефакатор лексемы
 */
struct Keyword : Lexeme {
    string identifier;

    Keyword(string identifier) : identifier(identifier) {};
};

/**
 * Арифметические знаки
 * Например: +, -, *, ==, ++
 * @param identifier - идентефикатор лексемы
 * @param priority   - приоритет операции
 */
struct ArithmeticSign : Lexeme {
    string identifier;
    int priority;

    ArithmeticSign(string identifier, int priority)
        : identifier(identifier), priority(priority) {};
};

/**
 * Разделители
 * Например: ], }, ;
 * @param identifier - идентефикатор лексемы
 */
struct Delimiter : Lexeme {
    string identifier;

    Delimiter(string identifier) : identifier(identifier) {};
};


/// Типы переменных
enum VariableType { int32, int64, float32, double64 };

/**
 * Переменные
 * @param name - название переменной
 * @param init - инициализированна переменная
 * @param type  - тип значения
 * @param value - присвоенное значение
 */
struct Variable : Lexeme {
    string name;
    bool init = false;
    VariableType type;
	string value;

	Variable(string name) : name(name) {};
};

/**
 * Константа
 * @param value - значение константы
 * @param type  - тип значения
 */
struct Constant : Lexeme {
    string value;
    VariableType type;

	Constant(string value) : value(value) {};
};