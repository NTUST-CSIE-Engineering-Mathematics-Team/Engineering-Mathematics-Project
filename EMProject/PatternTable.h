#pragma once
#include "ConstantTable.h"
#include "PatternAnalyzer.h"
#include "CommandPatternAnalyzer.h"

namespace em {
	namespace intrprt {
		namespace pattern {
			using System::String;
			using System::Text::RegularExpressions::Regex;
			using System::Collections::Generic::KeyValuePair;

			ref class PatternTable : public ConstantTable<Regex^, PatternAnalyzer^> {

			public:
				PatternTable(array<PatternAnalyzer^>^ analyzers);
				virtual ~PatternTable();

				virtual PatternAnalyzer^ matchPattern(String^ line, Match^% result);

			private:
				static array<Regex^>^ PatternTable::createKeys(array<PatternAnalyzer^>^ analyzers);

			};
		}
	}
}