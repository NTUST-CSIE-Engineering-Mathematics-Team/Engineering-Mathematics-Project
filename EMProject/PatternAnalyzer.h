#pragma once
#include "Message.h"

namespace em {
	namespace intrprt {
		ref class Interpreter;

		namespace pattern {
			using namespace em::intrprt;
			using namespace System::Text::RegularExpressions;
			using System::Collections::Generic::Dictionary;

			ref class PatternAnalyzer abstract {

			public:
				static String^ const NAME_PATTERN = "(?:[A-Za-z_]\\w*)";
				static String^ const DOUBLE_PATTERN = "(?:-?\\d+(?:\\.\\d+)?)";
				static String^ const NAME_OR_VALUE_PATTERN = "(" + NAME_PATTERN + "|" + DOUBLE_PATTERN + ")";
				

				property Regex^ bindingPattern {
					Regex^ get() {
						return regex;
					}
				}

			protected:
				Regex^ regex;

			private:
				delegate bool isType(String^ var);

				static Regex^ const namePattern = gcnew Regex("^" + NAME_PATTERN + "$", RegexOptions::Compiled);
				static Dictionary<wchar_t, isType^>^ checkTable;

			public:
				virtual ~PatternAnalyzer();

				virtual Message^ analyze(Match^ result, Interpreter^ iptr) abstract;

				static bool isName(String^ arg);

				static bool isDouble(String^ arg, double% v);
				static bool isDouble(String^ arg);

				static bool isInteger(String^ arg, int% v);
				static bool isInteger(String^ arg);

				static bool isChar(String^ arg, wchar_t% v);
				static bool isChar(String^ arg);

				static bool isNameOrValue(String^ arg);

				static String^ rowValuePattern(int maxArgs);
				static int checkVarTypes(array<String^>^ rawArgs, array<String^>^ types);

			protected:
				PatternAnalyzer();

				virtual String^ buildInitPattern() abstract;

			private:
				static PatternAnalyzer();
			};
		}
	}
}