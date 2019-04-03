#pragma once
#include "stdafx.hpp"

#include "../src/LexemesTables.cpp"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;


TEST_CLASS(LexemesTablesTest) {
public:

	/** ����� � ����������� �������� */
	TEST_METHOD(GetConstantLexemeByName) {
		LexemesTables tables;

		Lexeme* lexeme = tables.getLexeme("NOT FOUND LEXEME");
		Assert::IsNull(lexeme);

		lexeme = tables.getLexeme("if");
		Assert::AreEqual(lexeme->getType(),    (int)LexemeType::Keyword);
		Assert::AreEqual(lexeme->getSubtype(), (int)KeywordType::If);

		lexeme = tables.getLexeme(" ");
		Assert::AreEqual(lexeme->getType(),    (int)LexemeType::Delimiter);
		Assert::AreEqual(lexeme->getSubtype(), (int) DelimiterType::Space);
	}

	/** ����� � ����������� �������� �� id:position */
	TEST_METHOD(GetConstantLexemeById) {
		LexemesTables tables;

		Lexeme* lexeme = tables.getLexeme("if");
		Assert::IsNotNull(lexeme);
		Assert::AreEqual(lexeme->getType(),    (int)LexemeType::Keyword);
		Assert::AreEqual(lexeme->getSubtype(), (int)KeywordType::If);

		Lexeme* second = tables.getLexeme(lexeme->getType(), lexeme->getSubtype());
		Assert::IsNotNull(second);
	}

	/** ����� ���������� */
	TEST_METHOD(VariableLexemesTablesTest) {
		LexemesTables tables;
		string name = "my_variable";

		// ���������� �� ����������
		Variable* var_ptr = tables.getVariable(name);
		Assert::IsNull(var_ptr);

		// �������� ���������� � �������� � ������� � ������� ����������
		Variable var(name);
		int position = tables.addVariable(var);

		// ���������� ����������
		var_ptr = tables.getVariable(name);
		Assert::IsNotNull(var_ptr);
		Assert::AreEqual(var_ptr->getName(), name);

		// �������� ���������� �� � ������� � ������� ����������
		var_ptr = tables.getVariable(position);
		Assert::IsNotNull(var_ptr);
		Assert::AreEqual(var_ptr->getName(), name);
	}
};