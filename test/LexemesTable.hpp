#pragma once
#include "stdafx.hpp"

#include "../src/LexemesTables.cpp"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;


TEST_CLASS(LexemesTablesTest) {
public:

	TEST_METHOD(GetConstantLexemeByName) {
		LexemesTables tables;

		Lexeme* lexeme = tables.findConstanLexeme("NOT FOUND LEXEME");
		Assert::IsNull(lexeme);

		lexeme = tables.findConstanLexeme("if");
		Assert::AreEqual(lexeme->getType(), LexemeType::Keyword);
		Assert::AreEqual(reinterpret_cast<Keyword *>(lexeme)->getKeyword(), KeywordType::If);

		lexeme = tables.findConstanLexeme(" ");
		Assert::AreEqual(lexeme->getType(), LexemeType::Delimiter);
		Assert::AreEqual(reinterpret_cast<Delimiter *>(lexeme)->getDelimeter(), DelimiterType::Space);
	}

	TEST_METHOD(GetConstantLexemeById) {
		LexemesTables tables;

		Lexeme* lexeme = tables.findConstanLexeme("if");
		LexemeType type = lexeme->getType();
		int subtype = (int) reinterpret_cast<Keyword *>(lexeme)->getKeyword();

		Lexeme* result = tables.getLexeme(type, subtype);
		Assert::AreEqual(result->getType(), LexemeType::Keyword);
		Assert::AreEqual(reinterpret_cast<Keyword *>(lexeme)->getKeyword(), KeywordType::If);
	}

	TEST_METHOD(VariableLexemesTablesTest) {
		LexemesTables tables;

		// Переменной не существует
		Variable* var_ptr = tables.getVariable("test");
		Assert::IsNull(var_ptr);

		// Добавили переменную
		Variable var;
		tables.addVariable("test", var);

		// Переменная существует
		var_ptr = tables.getVariable("test");
		Assert::IsNotNull(var_ptr);
	}

};