#include "LexemesTables.hpp"

LexemesTables::LexemesTables() {
	// Добавляем ключевые слова
	keywords = {
		{KeywordType::If,    Keyword(KeywordType::If)},
		{KeywordType::Else,  Keyword(KeywordType::Else)},
		{KeywordType::For,   Keyword(KeywordType::For)},
		{KeywordType::While, Keyword(KeywordType::While)},
	};

	// Добавляем знаки
	signs = {
		{SignType::Add, ArithmeticSign(SignType::Add, 2)},         //   +
		{SignType::Sub, ArithmeticSign(SignType::Sub, 2)},         //   -
		{SignType::Mul, ArithmeticSign(SignType::Mul, 3)},         //   *
		{SignType::Div, ArithmeticSign(SignType::Div, 3)},         //   /
		{SignType::isEqual, ArithmeticSign(SignType::isEqual, 1)}, //   ==
		{SignType::Equal,   ArithmeticSign(SignType::Equal, 0)},   //   =
	};

	// Добавляем разделители
	delimiters = {
		{DelimiterType::OpenBracket,  Delimiter(DelimiterType::OpenBracket)},   //   (
		{DelimiterType::CloseBracket, Delimiter(DelimiterType::CloseBracket)},  //   )
		{DelimiterType::Semicolon, Delimiter(DelimiterType::Semicolon)},        //   ;
		{DelimiterType::Space,     Delimiter(DelimiterType::Space)},            //   Пробел
	};
}

Lexeme* LexemesTables::findConstanLexeme(const string& name) {
	if (name == "if") return &(keywords.at(KeywordType::If));
	if (name == " ")  return &(delimiters.at(DelimiterType::Space));
	return nullptr;
}

Lexeme* LexemesTables::getLexeme(LexemeType type, int subtype) {
	switch (type) {
		case LexemeType::Keyword:        return &(keywords.at((KeywordType) subtype));
		case LexemeType::Delimiter:      return &(delimiters.at((DelimiterType) subtype));
		case LexemeType::ArithmeticSign: return &(signs.at((SignType) subtype));
	}
	return nullptr;
}

void LexemesTables::addVariable(const string& name, Variable &variable) {
	variables[name] = variable;
}

Variable* LexemesTables::getVariable(const string& name) const {
	if (variables.find(name) == variables.end()) return nullptr;

	return (Variable *) &variables.at(name);
}

int main() {
	return 0;
}