#include "Interpreter.h"
#include "RegistrationArea.h"
using namespace em::intrprt;
static Interpreter::Interpreter() {
	RegistrationArea::registerHere();
}
Interpreter::Interpreter(array<PatternAnalyzer^>^ patternList) {

	this->needNext = nullptr;
	this->fullLine = gcnew StringBuilder(50);
	this->pTable = gcnew PatternTable(patternList);
	this->proxyVTable = gcnew VariableTableProxy();
	this->engine = gcnew ArithmeticEngine(this->variableTable);
}

Message^ Interpreter::interpret(String^ line) {
	line = line->Trim();
	Match^ result = this->commentPattern->bindingPattern->Match(line);
	if (result->Success) {
		return this->commentPattern->analyze(result, this);
	}

	if (this->needNext != nullptr) {

		if (this->needNext->bindingPattern->IsMatch(line)) {
			return this->needNext->analyze(this->needNext->bindingPattern->Match(line), this);
		}
	} else {

		if (line->EndsWith("\\")) {
			fullLine->Append(line->Substring(0, line->Length - 1));
			return Message::PASS_NO_CONTENT_MSG;
		} else {
			fullLine->Append(line);
			PatternAnalyzer^ analyzer = this->pTable->matchPattern(fullLine->ToString(), result);
			fullLine->Clear();
			if (analyzer != nullptr) {
				return analyzer->analyze(result, this);
			}
		}
	}

	return Message::SYNTAX_ERROR_MSG;
}

Interpreter::~Interpreter() {

	delete this->needNext;
	delete this->pTable;
	delete this->proxyVTable;
}

void Interpreter::releaseNextLine() {
	//cannot delete it, because "it" invoke this method
	this->needNext = nullptr;
}

void Interpreter::needNextLine(PatternAnalyzer^ tmpAnalyzer) {
	this->needNext = tmpAnalyzer;
}

Interpreter::VariableTableProxy::VariableTableProxy() {
}

Interpreter::VariableTableProxy::~VariableTableProxy() {
}

bool Interpreter::VariableTableProxy::contains(String^ name) {
	return allVTable->contains(name);
}

bool Interpreter::VariableTableProxy::addVariable(String^ name, MathObject^ mo) {

	if (this->allVTable->addVariable(name, mo)) {

		this->VariableTable::addVariable(name, mo);
		return true;
	}

	return false;
}

bool Interpreter::VariableTableProxy::deleteVariable(String^ name) {

	if (this->allVTable->deleteVariable(name)) {

		this->VariableTable::deleteVariable(name);
		return true;
	}

	return false;
}

void Interpreter::VariableTableProxy::load(VariableTable^ vTable) {

	if (vTable == nullptr) {

		this->allVTable->load(this);
	} else {

		this->allVTable->load(vTable);
		this->VariableTable::load(vTable);
	}
	
}

void Interpreter::VariableTableProxy::unload(VariableTable^ vTable) {

	if (vTable == nullptr) {

		this->allVTable->unload(this);
		this->clear();
	} else {

		this->allVTable->unload(vTable);
		this->VariableTable::unload(vTable);
	}
}

bool Interpreter::VariableTableProxy::checkGet(String^ name, MathObject^% mo) {
	return this->allVTable->checkGet(name, mo);
}

Dictionary<String^, MathObject^>::Enumerator Interpreter::VariableTableProxy::getEnumerator() {
	return this->allVTable->getEnumerator();
}