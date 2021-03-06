#pragma once
#include "Message.h"
#include "ArithmeticEngine.h"
namespace em {
	namespace intrprt {
		ref class Interpreter;

		namespace pattern {
			using namespace em::intrprt;
			using namespace System::Text::RegularExpressions;
			using System::Collections::Generic::Dictionary;
			using em::math::engine::ArithmeticEngine;

			ref class PatternAnalyzer abstract {

			public:
				static String^ const NAME_PATTERN = "(?:[A-Za-z_]\\w*)";
				static String^ const DOUBLE_PATTERN = "(?:-?\\d+(?:\\.\\d+)?)";
				static String^ const INTEGER_PATTERN = "(?:-?\\d+)";
				static String^ const NAME_OR_VALUE_PATTERN = "(?:" + NAME_PATTERN + "|" + DOUBLE_PATTERN + ")";
				

				property Regex^ bindingPattern {
					Regex^ get() {
						return regex;
					}
				}

			protected:
				Regex^ regex;

			private:
				delegate bool IsType(String^ var);

				static Regex^ const namePattern = gcnew Regex("^" + NAME_PATTERN + "$", RegexOptions::Compiled);
				static Regex^ const expressionPattern = gcnew Regex("^(" + ArithmeticEngine::arithmeticContentPattern("i") + ")$", RegexOptions::Compiled);
				static Regex^ const pairPattern = gcnew Regex("^(" + NAME_PATTERN + ")\\s+(" + INTEGER_PATTERN + ")$", RegexOptions::Compiled);
				static Dictionary<wchar_t, IsType^>^ const checkTable = gcnew Dictionary<wchar_t, IsType^>(8);

			public:
				virtual ~PatternAnalyzer();

				virtual Message^ analyze(Match^ result, Interpreter^ iptr) abstract;

				static bool isPair(String^ arg);
				static bool isPair(String^ arg, String^% key, int% value);
				static bool isVarName(String^ arg);
				static bool isName(String^ arg);
				static bool PatternAnalyzer::isKeyword(String^ arg);

				static bool isExpression(String^ arg);
				static bool isExpression(String^ arg, String^% v);

				static bool isDouble(String^ arg, double% v);
				static bool isDouble(String^ arg);

				static bool isInteger(String^ arg, int% v);
				static bool isInteger(String^ arg);

				static bool isChar(String^ arg, wchar_t% v);
				static bool isChar(String^ arg);

				static String^ rowValuePattern(int maxArgs);
				static bool checkVarType(String^ rawArg, wchar_t type);

			protected:
				PatternAnalyzer();

				virtual String^ buildInitPattern() abstract;

			private:
				static PatternAnalyzer();
			};
		}
	}
}