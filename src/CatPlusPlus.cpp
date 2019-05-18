#include "Scanner.hpp"

#include "../test/Utils.hpp" // Для вывода текста

int main() {
	LexemesTables tables;
	Scanner scanner(tables);

	string text =
		"int value = 10 ; Init var       \n"
		"int result     ; Create var     \n"
		"if (value ?= 5) { ; Check equal \n"
		"	result = 1                   \n"
		"} else {                        \n"
		"	result = 0                   \n"
		"}";
	istringstream stream(text);

	vector<tuple<int, int>> tokens; // Токены, которые получили из сканера

	// Пока не достигнут конец файла
	while (!stream.eof()) {
		tokens.push_back( scanner.getToken(stream) );
	}

	std::wcout << Microsoft::VisualStudio::CppUnitTestFramework::ToString(tokens);

	system("pause");
	return 0;
}