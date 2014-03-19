#include "JudgeCommand.h"
#include "KeywordCollection.h"
#include "Interpreter.h"
#include "PrintCommand.h"

using namespace em::intrprt::cmd;

JudgeCommand::JudgeCommand() : Command(KeywordCollection::JUDGE_CMD, "E") {
}


JudgeCommand::~JudgeCommand () {
}

Message^ JudgeCommand::performCommand(array<String^>^ args, int typeIndex, Interpreter^ iptr) {
	MathObject^ mo;
	Color color;
	iptr->arithmeticEngine->execute(args[0], mo);
	StringBuilder^ result = gcnew StringBuilder("The operation is ");

	if (mo == nullptr) {
		result->Append("NOT PASSED");
		color = Message::JUDGE_NOT_PASS_COLOR;
	} else {
		result->AppendFormat("PASSED, the value is:\n{0}\n{1}\n", PrintCommand::buildHeader(mo), mo->ToString());
		color = Message::JUDGE_PASS_COLOR;
	}

	return gcnew Message(Message::State::PASS, color, result->ToString());
}
