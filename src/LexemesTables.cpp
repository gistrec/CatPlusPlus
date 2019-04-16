#include "LexemesTables.hpp"

LexemesTables::LexemesTables() {
	// ��������� �������� �����
	keywords = {
		{Lexeme(LexemeType::Keyword, KeywordType::If,    "if"   )},
		{Lexeme(LexemeType::Keyword, KeywordType::Else,  "else" )},
		{Lexeme(LexemeType::Keyword, KeywordType::For,   "for"  )},
		{Lexeme(LexemeType::Keyword, KeywordType::While, "while")},
	};

	// ��������� �����
	signs = {
		{Lexeme(LexemeType::Sign, SignType::Add,     "+" )},
		{Lexeme(LexemeType::Sign, SignType::Sub,     "-" )},
		{Lexeme(LexemeType::Sign, SignType::Mul,     "*" )},
		{Lexeme(LexemeType::Sign, SignType::Div,     "/" )},
		{Lexeme(LexemeType::Sign, SignType::isEqual, "==")},
		{Lexeme(LexemeType::Sign, SignType::Equal,   "=" )},
	};

	// ��������� �����������
	delimiters = {
		{Lexeme(LexemeType::Delimiter, DelimiterType::OpenBracket,  "(")},
		{Lexeme(LexemeType::Delimiter, DelimiterType::CloseBracket, ")")},
		{Lexeme(LexemeType::Delimiter, DelimiterType::Space,        " ")},
		{Lexeme(LexemeType::Delimiter, DelimiterType::Semicolon,    ";")},
	};
}

Lexeme* LexemesTables::getLexeme(const string& name) {
	for (auto& keyword : keywords) {
		if (keyword.getName() == name) return &keyword;
	}
	for (auto& sign : signs) {
		if (sign.getName() == name) return &sign;
	}
	for (auto& delimiter : delimiters) {
		if (delimiter.getName() == name) return &delimiter;
	}

	return nullptr;
}
Lexeme* LexemesTables::getLexeme(int type, int subtype) {
	switch (type) {
		case LexemeType::Keyword:   return &keywords.at(subtype);
		case LexemeType::Delimiter: return &delimiters.at(subtype);
		case LexemeType::Sign:      return &signs.at(subtype);
	}
	return nullptr;
}


int LexemesTables::addVariable(Variable &variable) {
	// TODO: ������ ��������� ������������ ����������
	variable.subtype = variables.size(); // ������������� ������� � �������
	variables.push_back(variable);
	return variables.size() - 1;
}

Variable* LexemesTables::getVariable(int position) {
	if (variables.size() < position) return nullptr;

	return &(variables[position]);
}
Variable* LexemesTables::getVariable(string name)  {
	for (auto &variable : variables) {
		if (variable.getName() == name) return &variable;
	}
	return nullptr;
};

int LexemesTables::addConstant(Constant &constant) {
	// TODO: ������ ��������� ������������ ����������
	constant.subtype = constants.size(); // ������������� ������� � �������
	constants.push_back(constant);
	return constants.size() - 1;
}

Constant* LexemesTables::getConstant(int position)  {
	if (constants.size() < position) return nullptr;

	return &constants[position];
}
Constant* LexemesTables::getConstant(string name) {
	for (auto &constant : constants) {
		if (constant.getName() == name) return &constant;
	}
	return nullptr;
}