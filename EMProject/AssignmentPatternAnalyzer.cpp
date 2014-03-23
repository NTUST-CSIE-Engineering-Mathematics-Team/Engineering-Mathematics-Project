#include "AssignmentPatternAnalyzer.h"
#include "All_Math.h"
#include "VariableTable.h"
#include "Interpreter.h"

using namespace em::intrprt::pattern;
using namespace em::intrprt;
using namespace em::math;
using em::math::engine::ArithmeticEngine;
using System::Text::StringBuilder;

AssignmentPatternAnalyzer::AssignmentPatternAnalyzer() {
}


AssignmentPatternAnalyzer::~AssignmentPatternAnalyzer() {
}

Message^ AssignmentPatternAnalyzer::analyze(Match^ result, Interpreter^ iptr) {

	Message^ msg;
	VariableTable^ vTable = iptr->variableTable;
	CaptureCollection^ lObjNames = result->Groups[1]->Captures;
	
	MathObject^ output, ^ var;
	msg = iptr->arithmeticEngine->execute(result->Groups[2]->Value, output);


	if (output != nullptr) {

		String^ lObjName;
		var = output;

		for (int i = lObjNames->Count - 1; i >= 0; i--) {

			lObjName = lObjNames[i]->Value;

			if (isKeyword(lObjName)) {
				return Message::useKeywordAsNameError(lObjName);
			}

			if (!vTable->contains(lObjName)) {
				vTable->addVariable(lObjName, var);
			} else {
				MathObject^ lmo = vTable[lObjName];
				var = lmo->overrideAssign(var);
				if (var == nullptr) {
					StringBuilder^ sb = gcnew StringBuilder();
					sb->AppendFormat("Type error, can not assign a {0} to a {1}", output->mathType->ToLower(), lmo->mathType->ToLower());
					return gcnew Message(Message::State::ERROR, sb->ToString());

				}
			}
		}

	}
	
	return msg;
}


String^ AssignmentPatternAnalyzer::buildInitPattern() {
	StringBuilder^ sb = gcnew StringBuilder();
	
	sb->AppendFormat("^(?:({0})\\s*=\\s*)+({1})$", NAME_PATTERN, ArithmeticEngine::arithmeticContentPattern("p"));
	
	return sb->ToString();
}