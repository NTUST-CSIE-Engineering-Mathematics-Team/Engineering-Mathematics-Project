#include "PrintCommand.h"
#include "KeywordCollection.h"
#include "Interpreter.h"


using namespace em::intrprt::cmd;

static PrintCommand::PrintCommand() {

	idToNameMap->Add(Scalar::ID, Scalar::TAG->ToLower());
	idToNameMap->Add(Vector::ID, Vector::TAG->ToLower());
	idToNameMap->Add(Matrix::ID, Matrix::TAG->ToLower());
	idToNameMap->Add(MathObjSet::ID, MathObjSet::TAG->ToLower());
}

PrintCommand::PrintCommand() : Command(KeywordCollection::PRINT_CMD, 'E') {
}

PrintCommand::~PrintCommand() {
}

Message^ PrintCommand::performCommand(String^ arg, Interpreter^ iptr) {
	String^ header = nullptr;
	StringBuilder^ sb = gcnew StringBuilder(arg);
	MathObject^ mo;

		Message^ msg = iptr->arithmeticEngine->execute(arg, mo);
		if (mo == nullptr) {
			return msg;
		}

		if (iptr->variableTable->contains(arg)) {
			header = arg;
		}

		sb->AppendFormat(" =\n{0}", buildHeader(mo, header));
	sb->AppendFormat("\n{0}\n", mo->ToString());
	String^ result = sb->ToString();
	delete sb;
	return gcnew Message(Message::State::PASS, Message::MATH_OBJECT_COLOR, result);
}

StringBuilder^ PrintCommand::buildHeader(MathObject^ mo, String^ vName) {
	StringBuilder^ sb = gcnew StringBuilder(mo->mathType);

	if (vName != nullptr) {
		sb->AppendFormat(" \"{0}\"", vName);
	}
	
	Matrix^ mat;
	Vector^ vec;
	MathObjSet^ set;
	if (Matrix::matrixCast(mo, mat)) {
		sb->AppendFormat(" size = ({0} x {1})", mat->columnLength, mat->rowLength);
	} else if (Vector::vectorCast(mo, vec)) {
		sb->AppendFormat(" rank = {0}", vec->rank);
	} else if (MathObjSet::setCast(mo, set)) {
		sb->Insert(MathObjSet::TAG->Length, " of " + idToNameMap[set->contentID] + "s");
		sb->AppendFormat(" size = {0}", set->size);
	}

	return sb;
}

StringBuilder^ PrintCommand::buildHeader(MathObject^ mo) {
	return buildHeader(mo, nullptr);
}