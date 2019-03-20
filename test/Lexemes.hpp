#pragma once
#include "stdafx.hpp"

#include "../src/LexemesTables.hpp"


TEST_CLASS(LexemesTest) {
public:

	TEST_METHOD(SimpleLexemeTest) {
		Lexeme lexeme(LexemeType::Keyword);
		Assert::AreEqual(lexeme.getType(), LexemeType::Keyword);
	}
	
	TEST_METHOD(LexemeTest) {
		Keyword k_lexeme(KeywordType::If);
		Assert::AreEqual(k_lexeme.getType(),    LexemeType::Keyword);
		Assert::AreEqual(k_lexeme.getKeyword(), KeywordType::If);

		ArithmeticSign s_lexeme(SignType::Add, 0);
		Assert::AreEqual(s_lexeme.getType(), LexemeType::ArithmeticSign);
		Assert::AreEqual(s_lexeme.sign, SignType::Add);
		Assert::AreEqual(s_lexeme.getPriority(), 0);

		Delimiter d_lexeme(DelimiterType::Space);
		Assert::AreEqual(d_lexeme.getType(),      LexemeType::Delimiter);
		Assert::AreEqual(d_lexeme.getDelimeter(), DelimiterType::Space);
	}

	TEST_METHOD(VariableLexemeTest) {
		Variable var;

		Assert::AreEqual(var.getType(),    LexemeType::Variable);
		Assert::AreEqual(var.getVarType(), VariableType::Undefined);
		Assert::AreEqual(var.isInit(),     false);
		Assert::AreEqual(var.getData(),    (size_t) 0);
		
		var.setVarType(VariableType::Int);
		var.setData(12);

		Assert::AreEqual(var.getVarType(), VariableType::Int);
		Assert::AreEqual(var.getData(), (size_t) 12);
	}

	TEST_METHOD(ConstantLexemeTest) {
		Constant lexeme(VariableType::Int, 5);

		Assert::AreEqual(lexeme.getType(),    LexemeType::Constant);
		Assert::AreEqual(lexeme.getVarType(), VariableType::Int);
		Assert::AreEqual(lexeme.getData(),    (size_t) 5);
	}
	
};