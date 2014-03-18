#include "PrintCommand.h"
#include "KeywordCollection.h"
#include "Interpreter.h"


using namespace em::intrprt::cmd;
using namespace em::math;


PrintCommand::PrintCommand() : Command(KeywordCollection::PRINT_CMD, "V", "E") {
}

PrintCommand::~PrintCommand() {
}

Message^ PrintCommand::performCommand(array<String^>^ args, int typeIndex, Interpreter^ iptr) {
	String^ header = "";
	StringBuilder^ sb;
	MathObject^ mo;

	if (typeIndex == 1) {
		Message^ msg = iptr->arithmeticEngine->execute(args[0], mo);
		if (mo == nullptr) {
			return msg;
		}

	} else {

		double scl;
		if (PatternAnalyzer::isDouble(args[0], scl)) {
			mo = gcnew Scalar(scl);
			
		} else if (iptr->variableTable->checkGet(args[0], mo)) {
			header = args[0];
			
		} else {
			return Message::varNotFoundMsg(args[0]);
		}
	}

	sb = buildHeader(mo, header);
	sb->AppendFormat("\n{0}\n", mo->ToString());
	String^ result = sb->ToString();
	delete sb;
	return gcnew Message(Message::State::PASS, result, Message::MATH_OBJECT_COLOR);
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

	sb->AppendFormat(" {0}", vName);
	return sb;
}