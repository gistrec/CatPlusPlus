#pragma once
#include <cassert>
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
	map<KeywordType,   Lexeme> keywords;   // �������� �����
	map<DelimiterType, Lexeme> delimiters; // �����������
	map<SignType,      Lexeme> signs;      // �������������� �����

	vector<Variable> variables; // ����������
	vector<Constant> constants; // ���������

	LexemesTables();

	/**
	 * ����� ������� ����� ����������� ������
	 * �� ������ ��� ������ ������� � ������� � �������
	 */
	Lexeme* getLexeme(const string& name);
	Lexeme* getLexeme(int type, int subtype);

	/**
	 * ���������/�������� ���������� � ������� ����������
	 * int - ������� � �������
	 */
	int addVariable(Variable &variable);
	Variable* getVariable(int position);
	Variable* getVariable(string name);

	int addConstant(Constant &constant);
	Constant* getConstant(int position);
	Constant* getConstant(string name);
};