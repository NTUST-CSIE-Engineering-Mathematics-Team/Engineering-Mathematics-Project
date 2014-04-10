#include "PatternAnalyzer.h"
#include "KeywordCollection.h"

using namespace em::intrprt::pattern;
using System::Text::StringBuilder;
using System::Char;

PatternAnalyzer::PatternAnalyzer() {
	
	this->regex = gcnew Regex(buildInitPattern(), RegexOptions::Compiled);
}

static PatternAnalyzer::PatternAnalyzer() {
	checkTable->Add(L'N', gcnew IsType(isName));
	checkTable->Add(L'V', gcnew IsType(isVarName));
	checkTable->Add(L'I', gcnew IsType(isInteger));
	checkTable->Add(L'D', gcnew IsType(isDouble));
	checkTable->Add(L'C', gcnew IsType(isChar));
	checkTable->Add(L'E', gcnew IsType(isExpression));
	checkTable->Add(L'K', gcnew IsType(isKeyword));
	checkTable->Add(L'P', gcnew IsType(isPair));
}

PatternAnalyzer::~PatternAnalyzer() {
	delete this->regex;
}

bool PatternAnalyzer::checkVarType(String^ rawArg, wchar_t type) {
	return checkTable[Char::ToUpper(type)](rawArg);
}
bool PatternAnalyzer::isPair(String^ arg) {
	String^ emptyS;
	int emptyI;
	return isPair(arg, emptyS, emptyI);
}

bool PatternAnalyzer::isPair(String^ arg, String^% key, int% value) {
	Match^ m = pairPattern->Match(arg);
	if (!m->Success) {
		return false;
	}

	key = m->Groups[1]->Value;
	isInteger(m->Groups[2]->Value, value);

	return true;
}

bool PatternAnalyzer::isVarName(String^ arg) {
	return isName(arg) && !isKeyword(arg);
}

bool PatternAnalyzer::isName(String^ arg) {
	return namePattern->IsMatch(arg);
}

bool PatternAnalyzer::isKeyword(String^ arg) {
	return KeywordCollection::contains(arg);
}

bool PatternAnalyzer::isExpression(String^ arg, String^% v) {

	if (isDouble(arg) || isVarName(arg)) {
		return true;
	}

	Match^ m = expressionPattern->Match(arg);
	if (!m->Success || m->Groups["i"]->Success) {
		return false;
	}

	v = m->Groups[1]->Value;
	return true;
}

bool PatternAnalyzer::isExpression(String^ arg) {
	String^ empty;
	return isExpression(arg, empty);
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

String^ PatternAnalyzer::rowValuePattern(int maxPattern) {

	StringBuilder^ sb = gcnew StringBuilder("^\\s*(?>(" + PatternAnalyzer::NAME_OR_VALUE_PATTERN + ")\\s*){1,");
	sb->Append(maxPattern);
	sb->Append("}$");
	String^ p = sb->ToString();
	delete sb;
	return  p;
}