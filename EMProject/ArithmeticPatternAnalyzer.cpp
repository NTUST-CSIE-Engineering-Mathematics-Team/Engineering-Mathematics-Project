#include "ArithmeticPatternAnalyzer.h"
#include "All_Math.h"
#include "VariableTable.h"
#include "Interpreter.h"

using namespace em::intrprt::pattern;
using namespace em::intrprt;
using namespace em::math;
using em::math::engine::ArithmeticEngine;
using System::Text::StringBuilder;

ArithmeticPatternAnalyzer::ArithmeticPatternAnalyzer() {
}


ArithmeticPatternAnalyzer::~ArithmeticPatternAnalyzer() {
}

Message^ ArithmeticPatternAnalyzer::analyze(Match^ result, Interpreter^ iptr) {

	Message^ msg;
	VariableTable^ vTable = iptr->variableTable;
	String^ lObjName = result->Groups[1]->Value;

	if (!vTable->contains(lObjName)) {
		return Message::varNotFoundMsg(lObjName);
	}

	MathObject^ mo;
	msg = iptr->arithmeticEngine->execute(result->Groups[2]->Value, mo);

	if (mo != nullptr) {
		MathObject^ v = vTable[lObjName];
		if (mo->mathType->Equals(v->mathType)) {
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

	return msg;
}


String^ ArithmeticPatternAnalyzer::buildInitPattern() {
	StringBuilder^ sb = gcnew StringBuilder();
	
	sb->AppendFormat("^({0})\\s*=\\s*({1})$", NAME_PATTERN, ArithmeticEngine::arithmeticContentPattern("p"));
	
	return sb->ToString();
}