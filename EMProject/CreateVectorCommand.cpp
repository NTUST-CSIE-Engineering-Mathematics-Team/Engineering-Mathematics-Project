#include "CreateVectorCommand.h"
#include "KeywordCollection.h"
#include "Interpreter.h"

using namespace em::intrprt::cmd;

CreateVectorCommand::CreateVectorCommand() : CreateMathObjectCommand(KeywordCollection::CREATE_VECTOR_CMD, "In", "InN", "nN") {
}


CreateVectorCommand::~CreateVectorCommand() {
}

Message^ CreateVectorCommand::createMathObject(int typeIndex, String^ varName, array<String^>^ rawArgs, Interpreter^ iptr) {

	if (typeIndex == 1 || typeIndex == 2) {

		String^ vn = rawArgs[rawArgs->Length - 1];

		MathObject^ mo;
		if (!iptr->variableTable->checkGet(vn, mo)) {
			return Message::varNotFoundMsg(vn);
		}

		Vector^ vec;
		if (Vector::vectorCast(mo, vec)) {
			return gcnew Message(Message::State::ERROR, "Cannot initialize a vector with a non-vector variable in the same line");
		}

		Vector^ newV;
		if (typeIndex == 2) {
			 newV = gcnew Vector(vec);
		} else {

			int rank = System::Convert::ToInt32(rawArgs[0]);
			if (vec->rank > rank) {
				return gcnew Message(Message::State::ERROR, "The rank of the vector \"" + vn + "\" exceeds the rank of the new vector");
			}
			newV = gcnew Vector(rank);
			newV->fitAssign(vec);
		}

		iptr->variableTable->addVariable(varName, newV);
		return Message::PASS_NO_CONTENT_MSG;

	}

	iptr->needNextLine(gcnew VectorConstructionAnalyzer(gcnew Vector(System::Convert::ToInt32(rawArgs[0])), varName));
	return Message::PARSING_MSG;
}

CreateVectorCommand::VectorConstructionAnalyzer::VectorConstructionAnalyzer(Vector^ vec, String^ vName) : tmpVec(vec), vecName(vName) {
}

CreateVectorCommand::VectorConstructionAnalyzer::~VectorConstructionAnalyzer() {
}

Message^ CreateVectorCommand::VectorConstructionAnalyzer::analyze(Match^ result, Interpreter^ iptr) {

	int col = 0;
	for each(Capture^ cp in result->Groups[1]->Captures) {

		double v;
		if (isName(cp->Value)) {

			MathObject^ mo;
			if (!iptr->variableTable->checkGet(cp->Value, mo)) {
				return Message::varNotFoundMsg(cp->Value);
			}

			Scalar^ scl;
			if (!Scalar::scalarCast(mo, scl)) {
				return gcnew Message(Message::State::ERROR, "The \"" + mo->mathType + "\" type of the variable is not acceptable");
			}

			this->tmpVec[col++] = scl;

		} else if (isDouble(cp->Value, v)) {
			tmpVec[col++] = v;
		} else {
			return Message::SYNTAX_ERROR_MSG;
		}
	}
	
	iptr->variableTable->addVariable(this->vecName, this->tmpVec);
	iptr->releaseNextLine();
	return  Message::PASS_NO_CONTENT_MSG;

}

String^ CreateVectorCommand::VectorConstructionAnalyzer::buildInitPattern() {
	if (tmpVec == nullptr) {
		return PatternAnalyzer::NAME_PATTERN;
	}

	return  PatternAnalyzer::rowValuePattern(this->tmpVec->rank);
}