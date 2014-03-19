#include "JudgeCommand.h"
#include "KeywordCollection.h"

using namespace em::intrprt::cmd;

JudgeCommand::JudgeCommand() : Command(KeywordCollection::JUDGE_CMD, "NNN", "ENE", "NNE", "ENN") {
}


JudgeCommand::~JudgeCommand () {
}

Message^ JudgeCommand::performCommand(array<String^>^ args, int typeIndex, Interpreter^ iptr) {
	return nullptr;
	
}