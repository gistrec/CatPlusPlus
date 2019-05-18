#pragma once
#include "../src/Lexemes.hpp"
#include <string>
#include <vector>
#include <tuple>


using std::wstring;
using std::tuple;
using std::get;


namespace Microsoft {
	namespace VisualStudio {
		namespace CppUnitTestFramework {

			static wstring ToString(const enum LexemeType &type) {
				switch (type) {
					case LexemeType::Keyword:   return L"LexemeType::Keyword";
					case LexemeType::Sign:      return L"LexemeType::Sign";
					case LexemeType::Delimiter: return L"LexemeType::Delimiter";
					case LexemeType::Const:     return L"LexemeType::Const";
					case LexemeType::Var:       return L"LexemeType::Var";
					default: return L"No translation";
				}
			}

			static wstring ToString(const enum VariableType &type) {
				switch (type) {
					case VariableType::Integer:       return L"VariableType::Integer";
					case VariableType::Undefined:     return L"VariableType::Undefined";
					default: return L"No translation";
				}
			}

			static std::wstring ToString(const enum SignType &type) {
				switch (type) {
					case SignType::Add:       return L"SignType::Add";
					case SignType::Sub:       return L"SignType::Sub";
					case SignType::Mul:       return L"SignType::Mul";
					case SignType::isEqual:   return L"SignType::isEqual";
					case SignType::isNoEqual: return L"SignType::isNoEqual";
					case SignType::isLess:    return L"SignType::isLess";
					case SignType::Equal:     return L"SignType::Equal";
					default: return L"No translation";
				}
			}

			static wstring ToString(const enum KeywordType &type) {
				switch (type) {
					case KeywordType::Int:   return L"KeywordType::Int";
					case KeywordType::If:    return L"KeywordType::If";
					case KeywordType::Else:  return L"KeywordType::Else";
					default: return L"No translation";
				}
			}

			static wstring ToString(const enum DelimiterType &type) {
				switch (type) {
					case DelimiterType::OpenBracket:  return L"DelimiterType::OpenBracket";
					case DelimiterType::CloseBracket: return L"DelimiterType::CloseBracket";
					case DelimiterType::OpenBrace:    return L"DelimiterType::OpenBrace";
					case DelimiterType::CloseBrace:   return L"DelimiterType::CloseBrace";
					case DelimiterType::Space:        return L"DelimiterType::Space";
					case DelimiterType::LineBreak:    return L"DelimiterType::LineBreak";
					case DelimiterType::Comment:      return L"DelimiterType::Comment";
					default: return L"No translation";
				}
			}

			// TODO: В консоле моноширный шрифт, а в VS обозревателе текстов - нет
			static wstring ToString(const std::vector<tuple<int, int>> &tokens) {
				wstring str = L"{\n";
				for (auto& token : tokens) {
					// Если лексема не найдена
					if (get<0>(token) == -1) {
						str += L"     Lexeme not found\n";
						continue;
					}

					LexemeType type = static_cast<LexemeType>(get<0>(token));
					wstring subtype;

					switch (type) {
					case LexemeType::Keyword:
							subtype = L"  " + ToString(static_cast<KeywordType>(get<1>(token)));
							break;

						case LexemeType::Sign:
							#ifdef TEST_METHOD
								subtype = L"         " + ToString(static_cast<SignType>(get<1>(token)));
							#else
								subtype = L"     " + ToString(static_cast<SignType>(get<1>(token)));
							#endif
							break;

						case LexemeType::Delimiter:
							subtype = L"" + ToString(static_cast<DelimiterType>(get<1>(token)));
							break;

						case LexemeType::Var:
							#ifdef TEST_METHOD
								subtype = L"           index = " + std::to_wstring(get<1>(token));
							#else
								subtype = L"      index = " + std::to_wstring(get<1>(token));
							#endif
							break;

						case LexemeType::Const:
							#ifdef TEST_METHOD
								subtype = L"       index = " + std::to_wstring(get<1>(token));
							#else
								subtype = L"    index = " + std::to_wstring(get<1>(token));
							#endif
							break;

						default:  subtype = L"No translation";
					}

					str += L"     " + ToString(type) + L", " + subtype + L"\n";
				}
				str += L"}";
				return str;
			}
		}
	}
}