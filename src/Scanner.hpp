#pragma once
#include "LexemesTables.hpp"
#include <sstream>
#include <iostream>
#include <algorithm> /** all_off */

#define CharTypeSize 6
#define StateSize 8


using std::tuple;
using std::string;
using std::istream;
using std::istringstream;


class Scanner {
private:
    LexemesTables& lexemesTables;

    // Тип сканируемого символа
    enum CharType : int {
        Const,  // Цифра
        Symbol, // Символ
        Delim,  // Разделитель
        Operator,  // Арифметический знак
        Semicolon, // Точка с запятой - комментарий
        LineBreak  // Перенос на следующую строку
    };

    // Состояние конечного автомата
    enum State : int {
        Start,   // Начальное состояние сканера
        ReadSign,    // Считываем арифметический знак
        ReadConst,   // Считываем константу [Ждем только цифры или разделитель]
        ReadSymbol,  // Считываем символы   [Одна из трех таблиц]
        ReadDelim,   // Считываем разделитель
        Comment, // Блок комментария
        End,     // Сканер получил лексему [Находится в str]
        Error,   // Встретился неожиданный символ,
    };

    // Граф переходов
    State transitions[StateSize][CharTypeSize] = {
    /*                 Const    , Symbol    , Delim    , Operator  , Semicolon, LineBreak    */
    /* Start      */ { ReadConst, ReadSymbol, ReadDelim, ReadSign  , Comment  , Start   },
    /* ReadSign   */ { End      , End       , End      , ReadSign  , End      , End     },
    /* ReadConst  */ { ReadConst, Error     , End      , ReadSymbol, End      , End     },
    /* ReadSymbol */ { Error    , ReadSymbol, End      , ReadSymbol, End      , End     },
    /* ReadDelim  */ { End      , End       , End      , End       , End      , End     },
    /* Comment    */ { Comment  , Comment   , Comment  , Comment   , Comment  , End     },
                     { Error    , Error     , Error    , Error     , Error    , Error   },
                     { Error    , Error     , Error    , Error     , Error    , Error   }
    };

    State state;   // Текущее состояние конечного автомата

    char symbol;   // Сканируемый сивол
    CharType type; // Класс сканируемого символа

    string str; // Содержит цепочку литер, составляющих лексему

    /**
     * Выбираем следующую литеру из исходного текста
     * Помещаем её в `symbol` и меняем 'type' на соответствующий тип литеры
     */
    void readChar(istream &stream) {
        stream.read(&symbol, 1);

        // Если закончился текст
        if (stream.eof()) {
            state = State::End;
            return;
        }

        // TODO: Обработка неожиданного символа, например из другой раскладки
        if ((symbol < 0 || symbol > 254) && symbol != ' ') {
            std::cout << "[Error] unexpected symbol: " << symbol << std::endl;
            state = State::Error;
            return;
        }


        static vector<char> Delims = { ' ', '(', ')', '{', '}' };       // Разделители
        static vector<char> op = { '?', '!', '=', '<', '+', '-', '*' }; // Арифметические операторы

        if (isdigit(symbol)) type = CharType::Const;
        else if (isalpha(symbol)) type = CharType::Symbol;
        else if (symbol == ';')   type = CharType::Semicolon;
        else if (symbol == '\n')  type = CharType::LineBreak;

        else if (std::find(Delims.begin(), Delims.end(), symbol) != Delims.end()) type = CharType::Delim;

        else if (std::find(op.begin(), op.end(), symbol) != op.end()) type = CharType::Operator;

        // Если считали неверный символ
        else state = State::Error;
    }

    /**
     * Проверяет содержимое symbol
     * Если там пробел - вызывает readChar, пока в symbol окажется не пробел
     */
    void skipSpace(istream& stream) {
        while (symbol == ' ' && !stream.eof())  readChar(stream);
    }

    void process(istream& stream) {
        // Сначала считываем символ
        switch (state) {
            case State::Start:
                str = "";
                symbol = ' ';
                type = CharType::Delim;

                skipSpace(stream); // Считываем символ
                state = transitions[state][type]; // Переводим в новое состояние
                break;

            case State::ReadDelim:
                str += symbol;     // Добавляем символ к строке
                state = State::End;
                symbol = ' ';
                break;

            case State::ReadSign:
            case State::ReadConst:
            case State::ReadSymbol:
                str += symbol;     // Добавляем символ к строке
                readChar(stream);  // Считываем еще один символ
                state = transitions[state][type]; // Переводим в новое состояние
                break;

            case State::Comment:
                readChar(stream); // Считываем символ
                str = symbol;
                state = transitions[state][type]; // Переводим в новое состояние
                break;

            case State::End:
                break;

            case State::Error:
                std::cout << "Unexpected character '" << symbol << "'" << std::endl;
                std::cout << "Before '" << str << "'" << std::endl;
                break;
        }
    }

    /**
     * Получаем лексему из строки
     */
    tuple<int, int> getLexeme() {
        // Если нет строки
        if (str.size() == 0) return { -1, -1 };

        // Пытаемся получить лексему в таблицах Keywords, Delimiters, Operators
        Lexeme* lexeme = lexemesTables.getLexeme(str);
        if (lexeme) return { lexeme->getType(), lexeme->getSubtype() };

        // Если строка содержит только цифры, то это константа
        if (std::all_of(str.begin(), str.end(), ::isdigit)) {
            Constant* constant = lexemesTables.getConstant(str);
            // Если константа существует
            if (constant) return { constant->getType(), constant->getPosition() };

            // Иначе создаем новую константу
            Constant new_constant(str);
            int position = lexemesTables.addConstant(new_constant);
            return { new_constant.getType(), position };
        }

        // Если строка содержит только буквы, то это переменная
        if (std::all_of(str.begin(), str.end(), ::isalpha)) {
            // Если мы здесь, то строка - переменная
            Variable* var = lexemesTables.getVariable(str);
            // Если переменная существует
            if (var) return { var->getType(), var->getPosition() };

            // Иначе создаем новую переменную
            Variable new_variable(str);
            int position = lexemesTables.addVariable(new_variable);
            return { new_variable.getType(), new_variable.getSubtype() };
        }

        // Лексема не найдена
        std::cout << "Lexemes '" << str << "'not found" << std::endl;
        return { -1, -1 };
    }

public:
    Scanner(LexemesTables &lexemesTables)
        : lexemesTables(lexemesTables), state(State::Start) {}

    /**
     * Передаем в сканнер поток
     * Получаем тип лексемы и подтип (два номера таблицы)
     */
    tuple<int, int> getToken(istream& stream) {
        /// Чтение лексемы завершается при нахождении разделителя (или арифметический знак)
        /// Лексема возвращается, а сам разделитель остается в КА
        /// Поэтому нужно специально проинициализировать состояние хранящимся символом
        if (state == State::Start || state == State::Error || symbol == ' ') {
            state = State::Start; // Простая инициализация
        } else {
            state = transitions[State::Start][type]; // Инициализация хранящимся
            str = "";
        }

        // Пока конечный автомат не в состоянии End или Error
        while (state != State::End && state != State::Error && !stream.eof()) {
            process(stream);
        }

        // Если закончился файл
        if (stream.eof()) return { LexemeType::Delimiter, DelimiterType::LineBreak };

        // Если ошибка
        if (state == State::Error) return { -1 , -1 };

        return getLexeme();
    }
};
