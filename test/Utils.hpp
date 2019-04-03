#pragma once
#include "../src/Lexemes.hpp"
#include <string>

namespace Microsoft {
	namespace VisualStudio {
		namespace CppUnitTestFramework {

			static std::wstring ToString(const enum LexemeType &type) {
				switch (type) {
					case LexemeType::Keyword:   return L"Keyword";
					case LexemeType::Sign:      return L"Sign";
					case LexemeType::Delimiter: return L"Delimiter";
					case LexemeType::Const:     return L"Const";
					case LexemeType::Var:       return L"Var";
					default: return L"No translation";
				}
			}

			static std::wstring ToString(const enum VariableType &type) {
				switch (type) {
					case VariableType::Float:     return L"Float";
					case VariableType::Int:       return L"Int";
					case VariableType::Undefined: return L"Undefined";
					default: return L"No translation";
				}
			}

			static std::wstring ToString(const enum SignType &type) {
				switch (type) {
					case SignType::Add: return L"Add";
					case SignType::Sub: return L"Sub";
					case SignType::Mul: return L"Mul";
					case SignType::Div: return L"Div";
					case SignType::Equal:   return L"Equal";
					case SignType::isEqual: return L"isEqual";
					default: return L"No translation";
				}
			}

			static std::wstring ToString(const enum KeywordType &type) {
				switch (type) {
					case KeywordType::If:    return L"If";
					case KeywordType::Else:  return L"Else";
					case KeywordType::For:   return L"For";
					case KeywordType::While: return L"While";
					default: return L"No translation";
				}
			}

			static std::wstring ToString(const enum DelimiterType &type) {
				switch (type) {
					case DelimiterType::CloseBracket: return L"CloseBracket";
					case DelimiterType::OpenBracket:  return L"OpenBracket";
					case DelimiterType::Semicolon: return L"Semicolon";
					case DelimiterType::Space:     return L"Space";
					default: return L"No translation";
				}
			}
		}
	}
}