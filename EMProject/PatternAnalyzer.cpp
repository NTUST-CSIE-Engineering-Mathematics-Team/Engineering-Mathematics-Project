#include "PatternAnalyzer.h"
#include "KeywordCollection.h"

using namespace em::intrprt::pattern;
using System::Text::StringBuilder;
using System::Char;

PatternAnalyzer::PatternAnalyzer() {
	this->regex = gcnew Regex(buildInitPattern(), RegexOptions::Compiled);
}

static PatternAnalyzer::PatternAnalyzer() {
	checkTable = gcnew Dictionary<wchar_t, isType^>();
	checkTable->Add(L'N', gcnew isType(isName));
	checkTable->Add(L'I', gcnew isType(isInteger));
	checkTable->Add(L'D', gcnew isType(isDouble));
	checkTable->Add(L'C', gcnew isType(isChar));
	checkTable->Add(L'V', gcnew isType(isNameOrValue));
}

PatternAnalyzer::~PatternAnalyzer() {
	delete this->regex;
}

int PatternAnalyzer::checkVarTypes(array<String^>^ rawArgs, array<String^>^ types) {
	int j;
	for (int i = 0; i < types->Length; i++) {

		if (types[i]->Length != rawArgs->Length) {
			continue;
		}
		
		for (j = 0; j < types[i]->Length; j++) {
			if (!checkTable[Char::ToUpper(types[i][j])](rawArgs[j])) {
				break;
			}
		}

		if (j == rawArgs->Length) {
			return i;
		}
	}

	return -1;
}

bool PatternAnalyzer::isName(String^ arg) {
	return namePattern->IsMatch(arg) && !KeywordCollection::contains(arg);
}

bool PatternAnalyzer::isDouble(String^ arg, double% v) {
	return System::Double::TryParse(arg, v);
}

bool PatternAnalyzer::isDouble(String^ arg) {
	double empty;
	return isDouble(arg, empty);
}

bool PatternAnalyzer::isInteger(String^ arg, int% v) {
	return System::Int32::TryParse(arg, v);
}

bool PatternAnalyzer::isInteger(String^ arg) {
	int empty;
	return isInteger(arg, empty);
}

bool PatternAnalyzer::isChar(String^ arg, wchar_t% v) {
	return System::Char::TryParse(arg, v);
}

bool PatternAnalyzer::isChar(String^ arg) {
	wchar_t empty;
	return isChar(arg, empty);
}

bool PatternAnalyzer::isNameOrValue(String^ arg) {
	return isDouble(arg) || isName(arg);
}

String^ PatternAnalyzer::rowValuePattern(int maxPattern) {

	StringBuilder^ sb = gcnew StringBuilder("^\\s*(?>" + PatternAnalyzer::NAME_OR_VALUE_PATTERN + "\\s*){1,");
	sb->Append(maxPattern);
	sb->Append("}$");
	String^ p = sb->ToString();
	delete sb;
	return  p;
}