#include "CreateScalarCommand.h"
#include "KeywordCollection.h"
#include "Interpreter.h"

using namespace em::intrprt::cmd;

CreateScalarCommand::CreateScalarCommand() : CreateMathObjectCommand(KeywordCollection::CREATE_SCALAR_CMD, "nE") {
}


CreateScalarCommand::~CreateScalarCommand() {
}

Message^ CreateScalarCommand::createMathObject(int typeIndex, String^ varName, array<String^>^ rawArgs, Interpreter^ iptr) {

	MathObject^ mo;
	Message^  msg;
	msg = iptr->arithmeticEngine->execute(rawArgs[1], mo);

	if (mo == nullptr) {
		return msg;
	}

	Scalar^ scl;
	if (!Scalar::scalarCast(mo, scl)) {
		return gcnew Message(Message::State::ERROR, "Cannot initialize a scalar with a non-scalar variable");
	}

	iptr->variableTable->addVariable(varName, gcnew Scalar(scl));
	

	return Message::PASS_NO_CONTENT_MSG;
}
