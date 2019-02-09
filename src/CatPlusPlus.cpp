#include <fstream>

#include "LexicalAnalyzer.hpp"

/**
 * Считываем весь файл и передаем в функцию parseString
 */
istream& operator >> (istream &in, LexicalAnalyzer &analyzer) {
    string file((istreambuf_iterator<char>(in)), istreambuf_iterator<char>());
    analyzer.parseString(file);

    return in;
};

int main() {
    std::ifstream input("../examples/input.catpp");
    LexicalAnalyzer analyzer;
    input >> analyzer;
    system("pause");
    return 0;
}