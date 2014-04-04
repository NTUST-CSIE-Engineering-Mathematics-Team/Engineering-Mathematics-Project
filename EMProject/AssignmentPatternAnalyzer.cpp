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
	this->parseAssignment = gcnew Regex("^(?:(" + NAME_PATTERN + ")\\s*=\\s*)+(" + ArithmeticEngine::arithmeticContentPattern("p") + ")$", RegexOptions::Compiled);
}


AssignmentPatternAnalyzer::~AssignmentPatternAnalyzer() {
}

Message^ AssignmentPatternAnalyzer::analyze(Match^ result, Interpreter^ iptr) {

	Message^ msg;
	VariableTable^ vTable = iptr->variableTable;

	CaptureCollection^ lObjNames, ^ equations = result->Groups[ArithmeticEngine::operandTag]->Captures;
	String^ lObjName;
	Match^ match;
	MathObject^ output, ^ var, ^lmo;
	for each(Capture^ cp in equations) {
		match = parseAssignment->Match(cp->Value);
		lObjNames = match->Groups[1]->Captures;
		msg = iptr->arithmeticEngine->execute(match->Groups[2]->Value, output);

		if (output != nullptr) {
			
			var = output;

			for (int i = lObjNames->Count - 1; i >= 0; i--) {

				lObjName = lObjNames[i]->Value;

				if (isKeyword(lObjName)) {
					return Message::useKeywordAsNameError(lObjName);
				}

				if (!vTable->checkGet(lObjName, lmo)) {
					vTable->addVariable(lObjName, var);
				} else {
					
					var = lmo->overrideAssign(var);
					if (var == nullptr) {
						StringBuilder^ sb = gcnew StringBuilder();
						sb->AppendFormat("Type error, can not assign a {0} to a {1}", output->mathType->ToLower(), lmo->mathType->ToLower());
						return gcnew Message(Message::State::ERROR, sb->ToString());

					}
				}
			}

		}
	}

	return msg;
}


String^ AssignmentPatternAnalyzer::buildInitPattern() {
	StringBuilder^ d = gcnew StringBuilder();
	StringBuilder^ full = gcnew StringBuilder();
	d->AppendFormat("(?<{0}>(?:{1}\\s*=\\s*)+{2})", ArithmeticEngine::operandTag, NAME_PATTERN, ArithmeticEngine::arithmeticContentPattern("p"));
	full->AppendFormat("^{0}(?:,\\s*{1})*$", d, d);
	
	return full->ToString();
}