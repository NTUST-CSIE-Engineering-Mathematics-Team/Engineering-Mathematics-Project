#include "ArithmeticPatternAnalyzer.h"
#include "MathObject.h"
#include "VariableTable.h"
#include "Interpreter.h"

using namespace em::intrprt::pattern;
using namespace em::intrprt;
using em::math::MathObject;
using em::math::engine::ArithmeticEngine;
using System::Text::StringBuilder;

ArithmeticPatternAnalyzer::ArithmeticPatternAnalyzer() {
	this->engine = gcnew ArithmeticEngine();
}


ArithmeticPatternAnalyzer::~ArithmeticPatternAnalyzer() {
}

Message^ ArithmeticPatternAnalyzer::analyze(Match^ result, Interpreter^ iptr) {

	Message^ msg;
	VariableTable^ vTable = iptr->variableTable;
	String^ lObjName = result->Groups[1]->Value;

	if (!vTable->contains(lObjName)) {
		msg = Message::varNotFoundMsg(lObjName);
		return nullptr;
	}

	if (!this->engine->analyze(result->Groups[2]->Value, iptr->variableTable, msg)) {
		return msg;
	}

	MathObject^ mo
	if (!this->engine->compute(mo)) {

	}
	vTable[lObjName] = mo;

}


String^ ArithmeticPatternAnalyzer::buildInitPattern() {
	StringBuilder^ sb = gcnew StringBuilder();
	sb->AppendFormat("^({0})\\s*=\\s*({1})$", NAME_PATTERN, ArithmeticEngine::arithmeticContentPattern("p"));
	
	return sb->ToString();
}