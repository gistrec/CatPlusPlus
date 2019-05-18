#pragma once
#include "stdafx.hpp"

#include "../src/Scanner.hpp"


TEST_CLASS(ScannerTest) {
public:

	TEST_METHOD(SimpleScannerTest) {
		LexemesTables tables;
		Scanner scanner(tables);

		string string =
			"int first = 5 ; Comments\n"
			"first = 10                ";
		istringstream stream(string);

		vector<tuple<int , int>> tokens; // Токены, которые получили из сканера

		// Пока не достигнут конец файла
		while (!stream.eof()) {
			tokens.push_back(scanner.getToken(stream) );
		}

		// Из строки удалятся все пробелы
		Assert::AreEqual(tokens, {
			{LexemeType::Keyword, KeywordType::Int}, // int
			{LexemeType::Var,     0               }, // first  - переменная с индексом 0
			{LexemeType::Sign,    SignType::Equal }, // =
			{LexemeType::Const,   0               }, // 5 - константа с индексом 0
			{LexemeType::Delimiter, DelimiterType::LineBreak},  // Перенос строки
			{LexemeType::Var,     0               }, // first - переменная с индексом 0
			{LexemeType::Sign,    SignType::Equal }, // =
			{LexemeType::Const,   1               }, // 10 - константа с индексом 1
			{LexemeType::Delimiter, DelimiterType::LineBreak},  // Перенос строки
		});
	}
};