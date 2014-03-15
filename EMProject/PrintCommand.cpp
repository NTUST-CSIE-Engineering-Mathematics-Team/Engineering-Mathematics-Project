#include "PrintCommand.h"
#include "KeywordCollection.h"
#include "Interpreter.h"


using namespace em::intrprt::cmd;
using namespace em::math;


PrintCommand::PrintCommand() : Command(KeywordCollection::PRINT_CMD, "V") {
}

PrintCommand::~PrintCommand() {
}

Message^ PrintCommand::performCommand(array<String^>^ args, int typeIndex, Interpreter^ iptr) {

	StringBuilder^ sb;
	MathObject^ mo;
	if (PatternAnalyzer::isDouble(args[0])) {
		sb = gcnew StringBuilder(Scalar::tag);
		sb->Append(" ");
		sb->Append(args[0]);

	} else if (iptr->variableTable->checkGet(args[0], mo)) {

		sb = buildHeader(mo, args[0]);
		sb->AppendFormat("\n{0}\n", mo->ToString());

	} else {
		return Message::varNotFoundMsg(args[0]);
	}

	String^ result = sb->ToString();
	delete sb;
	return gcnew Message(Message::State::PASS, result, Message::MATH_OBJECT_COLOR);
}

StringBuilder^ PrintCommand::buildHeader(MathObject^ mo, String^ vName) {
	StringBuilder^ sb = gcnew StringBuilder(mo->mathType);
	Matrix^ mat;
	Vector^ vec;
	if (Matrix::martixCast(mo, mat)) {
		sb->AppendFormat(" ({0} x {1})", mat->columnLength, mat->rowLength);

	} else if (Vector::vectorCast(mo, vec)) {
		sb->AppendFormat(" {0}", vec->rank);
	}

	sb->AppendFormat(" {0}", vName);
	return sb;
}