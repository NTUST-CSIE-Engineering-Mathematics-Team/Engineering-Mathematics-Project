#include "PrintCommand.h"
#include "KeywordCollection.h"
#include "Interpreter.h"


using namespace em::intrprt::cmd;
using namespace em::math;


PrintCommand::PrintCommand() : Command(KeywordCollection::PRINT_CMD, "E") {
}

PrintCommand::~PrintCommand() {
}

Message^ PrintCommand::performCommand(array<String^>^ args, int typeIndex, Interpreter^ iptr) {
	String^ header = "";
	StringBuilder^ sb;
	MathObject^ mo;

		Message^ msg = iptr->arithmeticEngine->execute(args[0], mo);
		if (mo == nullptr) {
			return msg;
		}

	sb = buildHeader(mo, header);
	sb->AppendFormat("\n{0}\n", mo->ToString());
	String^ result = sb->ToString();
	delete sb;
	return gcnew Message(Message::State::PASS, Message::MATH_OBJECT_COLOR, result);
}

StringBuilder^ PrintCommand::buildHeader(MathObject^ mo, String^ vName) {
	StringBuilder^ sb = gcnew StringBuilder(mo->mathType);
	Matrix^ mat;
	Vector^ vec;
	if (Matrix::matrixCast(mo, mat)) {
		sb->AppendFormat(" ({0} x {1})", mat->columnLength, mat->rowLength);

	} else if (Vector::vectorCast(mo, vec)) {
		sb->AppendFormat(" {0}", vec->rank);
	}

	if (vName != nullptr) {
		sb->AppendFormat(" {0}", vName);
	}

	return sb;
}

StringBuilder^ PrintCommand::buildHeader(MathObject^ mo) {
	return buildHeader(mo, nullptr);
}