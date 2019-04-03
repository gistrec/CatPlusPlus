#include "LexemesTables.hpp"

LexemesTables::LexemesTables() {
	// Добавляем ключевые слова
	keywords = {
		{KeywordType::If,    Lexeme(KeywordType::If,   0)},
		{KeywordType::Else,  Lexeme(KeywordType::Else, 1)},
		{KeywordType::For,   Lexeme(KeywordType::For,  2)},
		{KeywordType::While, Lexeme(KeywordType::While, 3)},
	};

	// Добавляем знаки
	signs = {
		{SignType::Add,     Lexeme(SignType::Add,     0)}, //   +
		{SignType::Sub,     Lexeme(SignType::Sub,     1)}, //   -
		{SignType::Mul,     Lexeme(SignType::Mul,     2)}, //   *
		{SignType::Div,     Lexeme(SignType::Div,     3)}, //   /
		{SignType::isEqual, Lexeme(SignType::isEqual, 4)}, //   ==
		{SignType::Equal,   Lexeme(SignType::Equal,   5)}, //   =
	};

	// Добавляем разделители
	delimiters = {
		{DelimiterType::OpenBracket,  Lexeme(DelimiterType::OpenBracket,  0)}, //  (
		{DelimiterType::CloseBracket, Lexeme(DelimiterType::CloseBracket, 1)}, //  )
		{DelimiterType::Space,        Lexeme(DelimiterType::Space,        2)}, //  Пробел
		{DelimiterType::Semicolon,    Lexeme(DelimiterType::Semicolon,    3)}, //  ;
	};
}

Lexeme* LexemesTables::getLexeme(const string& name) {
	if (name == "if") return &(keywords.at(KeywordType::If));
	if (name == " ")  return &(delimiters.at(DelimiterType::Space));
	return nullptr;
}
Lexeme* LexemesTables::getLexeme(int type, int subtype) {
	switch (type) {
		case LexemeType::Keyword:   return &(keywords.at((KeywordType) subtype));
		case LexemeType::Delimiter: return &(delimiters.at((DelimiterType) subtype));
		case LexemeType::Sign:      return &(signs.at((SignType) subtype));
	}
	return nullptr;
}


int LexemesTables::addVariable(Variable &variable) {
	// TODO: нельзя добавлять существующую переменную
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




int main() {
	return 0;
}