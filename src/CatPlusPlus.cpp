#include "Scanner.hpp"

#include "../test/Utils.hpp" // Для вывода текста

int main() {
	LexemesTables tables;
	Scanner scanner(tables);

	string text = "int value = 10 ; Init var       ";
	istringstream stream(text);

	vector<tuple<int, int>> tokens; // Токены, которые получили из сканера

	// Пока не достигнут конец файла
	while (!stream.eof()) {
		tokens.push_back( scanner.getToken(stream) );
	}                                                                                                                                                                                                                                                tokens.pop_back();

	std::wcout << Microsoft::VisualStudio::CppUnitTestFramework::ToString(tokens);

	system("pause");
	return 0;
}