#include "JudgeCommand.h"
#include "KeywordCollection.h"
#include "Interpreter.h"
#include "PrintCommand.h"
#include "MathObjSet.h"
using namespace em::intrprt::cmd;
using em::math::MathObjSet;

JudgeCommand::JudgeCommand() : Command(KeywordCollection::JUDGE_CMD, 'E') {
}


JudgeCommand::~JudgeCommand () {
}

Message^ JudgeCommand::performCommand(String^ arg, Interpreter^ iptr) {
	MathObject^ mo;
	Color color;
	iptr->arithmeticEngine->execute(arg, mo);
	StringBuilder^ result = gcnew StringBuilder("The operation is ");

	if (mo == nullptr) {
		result->Append("NOT PASSED");
		color = Message::JUDGE_NOT_PASS_COLOR;
	} else {
		MathObjSet^ set;
		if (!MathObjSet::setCast(mo, set) || set->size > 0) {
			result->AppendFormat("PASSED, the value is:\n{0}\n{1}\n", PrintCommand::buildHeader(mo), mo->ToString());
			color = Message::JUDGE_PASS_COLOR;
		}
		
	}

	return gcnew Message(Message::State::PASS, color, result->ToString());
}
