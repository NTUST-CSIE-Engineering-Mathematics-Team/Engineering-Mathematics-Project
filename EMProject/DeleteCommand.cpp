#include "DeleteCommand.h"
#include "KeywordCollection.h"
#include "Interpreter.h"

using namespace em::intrprt::cmd;

DeleteCommand::DeleteCommand() : Command(KeywordCollection::DELETE_CMD, "N") {
}

DeleteCommand::~DeleteCommand() {
}

Message^ DeleteCommand::performCommand(array<String^>^ args, int typeIndex, Interpreter^ iptr) {

	if (!iptr->variableTable->contains(args[0])) {
		return Message::varNotFoundMsg(args[0]);
	} 
	
	iptr->variableTable->deleteVariable(args[0]);
	return Message::PASS_NO_CONTENT_MSG;
}