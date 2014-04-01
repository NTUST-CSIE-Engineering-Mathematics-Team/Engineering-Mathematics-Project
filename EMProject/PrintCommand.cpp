#include "PrintCommand.h"
#include "KeywordCollection.h"
#include "Interpreter.h"


using namespace em::intrprt::cmd;

static PrintCommand::PrintCommand() {

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

	sb->AppendFormat(" =\n{0}\n", mo->ToString());
	String^ result = sb->ToString();
	delete sb;
	return gcnew Message(Message::State::PASS, Message::MATH_OBJECT_COLOR, result);
}

