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
	String^ lObjName = result->Groups[1]->Value;

	

	MathObject^ mo;
	msg = iptr->arithmeticEngine->execute(result->Groups[2]->Value, mo);

	if (mo != nullptr) {

		if (!vTable->contains(lObjName)) {
			vTable->addVariable(lObjName, mo);
		} else {
			MathObject^ v = vTable[lObjName];
			if (mo->mathID->Equals(v->mathID)) {
				Scalar^ scl;
				Vector^ vec;
				if (Scalar::scalarCast(v, scl)) {
					scl->overrideAssign(dynamic_cast<Scalar^>(mo));
				} else if (Vector::vectorCast(v, vec)) {
					vec->overrideAssign(dynamic_cast<Vector^>(mo));
				} else {
					dynamic_cast<Matrix^>(v)->overrideAssign(dynamic_cast<Matrix^>(mo));
				}
			} else {
				StringBuilder^ sb = gcnew StringBuilder();
				sb->AppendFormat("Type error, can not assign a {0} to a {1}", mo->mathType->ToLower(), v->mathType->ToLower());
				return gcnew Message(Message::State::ERROR, sb->ToString());

			}
		}
		 
	}

	return msg;
}


String^ AssignmentPatternAnalyzer::buildInitPattern() {
	StringBuilder^ sb = gcnew StringBuilder();
	
	sb->AppendFormat("^({0})\\s*=\\s*({1})$", NAME_PATTERN, ArithmeticEngine::arithmeticContentPattern("p"));
	
	return sb->ToString();
}