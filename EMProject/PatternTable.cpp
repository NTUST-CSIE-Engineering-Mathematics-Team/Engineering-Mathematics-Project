#include "PatternTable.h"

using namespace em::intrprt::pattern;

PatternTable::PatternTable(array<PatternAnalyzer^>^ analyzers) : ConstantTable(createKeys(analyzers), analyzers) {
}


PatternTable::~PatternTable() {
}



PatternAnalyzer^ PatternTable::matchPattern(String^ line, Match^% result) {

	for each(KeyValuePair<Regex^, PatternAnalyzer^> pair in this->table) {
		Match^ tmp = pair.Key->Match(line);
		if (tmp->Success) {
			result = tmp;
			return pair.Value;
		}
	}

	return nullptr;
}

array<Regex^>^ PatternTable::createKeys(array<PatternAnalyzer^>^ analyzers) {

	array<Regex^>^ keys = gcnew array<Regex^>(analyzers->Length);

	for (int i = 0; i < analyzers->Length; i++) {
		keys[i] = analyzers[i]->bindingPattern;
	}

	return keys;
}