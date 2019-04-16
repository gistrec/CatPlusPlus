#pragma once
#include "stdafx.hpp"

#include "../src/LexemesTables.hpp"


TEST_CLASS(LexemesTest) {
public:
	/** Проверка функций, которые возвращают table_id и position*/
	TEST_METHOD(SimpleLexemeTest) {
		string word = "if";
		Lexeme lexeme(LexemeType::Keyword, KeywordType::If, word);

		Assert::AreEqual(lexeme.getType(),    (int)LexemeType::Keyword);
		Assert::AreEqual(lexeme.getSubtype(), (int)KeywordType::If);
		Assert::AreEqual(lexeme.getName(),    word);
	}
	
	TEST_METHOD(LexemeTest) {
		string word;
		Lexeme sign_lexeme(LexemeType::Sign, SignType::Add, word);

		Assert::AreEqual(sign_lexeme.getType(),    (int)LexemeType::Sign);
		Assert::AreEqual(sign_lexeme.getSubtype(), (int)SignType::Add);

		word = " ";
		Lexeme delim_lexeme(LexemeType::Delimiter, DelimiterType::Space, word);
		Assert::AreEqual(delim_lexeme.getType(),    (int)LexemeType::Delimiter);
		Assert::AreEqual(delim_lexeme.getSubtype(), (int)DelimiterType::Space);
	}

	TEST_METHOD(VariableLexemeTest) {
		string name = "my_variable";
		Variable var(name);

		Assert::AreEqual(var.getName(),    name);
		Assert::AreEqual(var.getType(),    (int)LexemeType::Var);
		Assert::AreEqual(var.getVarType(), VariableType::Undefined);
		Assert::AreEqual(var.isInit(),     false);
		Assert::AreEqual(var.getData(),    (size_t) 0);
		
		var.setVarType(VariableType::Int);
		var.setData(12);

		Assert::AreEqual(var.getVarType(), VariableType::Int);
		Assert::AreEqual(var.getData(),    (size_t) 12);
	}

	TEST_METHOD(ConstantLexemeTest) {
		string name = "my_constant";
		Constant constant(name, VariableType::Int, 5);

		Assert::AreEqual(constant.getName(),    name);
		Assert::AreEqual(constant.getType(),    (int)LexemeType::Const);
		Assert::AreEqual(constant.getVarType(), VariableType::Int);
		Assert::AreEqual(constant.getData(),    (size_t) 5);
	}
};