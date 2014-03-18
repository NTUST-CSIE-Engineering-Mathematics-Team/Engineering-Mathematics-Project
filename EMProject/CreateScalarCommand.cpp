#include "CreateScalarCommand.h"
#include "KeywordCollection.h"
#include "Interpreter.h"

using namespace em::intrprt::cmd;

CreateScalarCommand::CreateScalarCommand() : CreateMathObjectCommand(KeywordCollection::CREATE_SCALAR_CMD, "nV", "nE") {
}


CreateScalarCommand::~CreateScalarCommand() {
}

Message^ CreateScalarCommand::createMathObject(int typeIndex, String^ varName, array<String^>^ rawArgs, Interpreter^ iptr) {

	if (typeIndex == 1) {
		MathObject^ mo;
		Message^  msg;
		msg = iptr->arithmeticEngine->execute(rawArgs[1], mo);

		if (mo == nullptr) {
			return msg;
		}

		Scalar^ scl;
		if (Scalar::scalarCast(mo, scl)) {

			iptr->variableTable->addVariable(varName, scl);
			msg = Message::PASS_NO_CONTENT_MSG;
		} else {
			msg = gcnew Message(Message::State::ERROR, "Type error, can not assign a " + mo->mathType->ToLower() + " to a scalar");
		}

		return msg;
	}

	double v;
	if (PatternAnalyzer::isDouble(rawArgs[1], v)) {

		iptr->variableTable->addVariable(varName, gcnew Scalar(System::Convert::ToDouble(rawArgs[1])));
	} else {

		String^ vn = rawArgs[1];
		MathObject^ mo;
		if (!iptr->variableTable->checkGet(vn, mo)) {
			return Message::varNotFoundMsg(vn);
		}

		Scalar^ scl;
		if (!Scalar::scalarCast(mo, scl)) {
			return gcnew Message(Message::State::ERROR, "Cannot initialize a scalar with a non-scalar variable");
		}

		iptr->variableTable->addVariable(varName, gcnew Scalar(scl));
	}

	return Message::PASS_NO_CONTENT_MSG;
}
