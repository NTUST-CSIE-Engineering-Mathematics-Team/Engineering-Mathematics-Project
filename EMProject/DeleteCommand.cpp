#include "DeleteCommand.h"
#include "KeywordCollection.h"
#include "Interpreter.h"

using namespace em::intrprt::cmd;

DeleteCommand::DeleteCommand() : Command(KeywordCollection::DELETE_CMD, 'N') {
}

DeleteCommand::~DeleteCommand() {
}

Message^ DeleteCommand::performCommand(String^ arg, Interpreter^ iptr) {

	if (!iptr->variableTable->contains(arg)) {
		return Message::varNotFoundMsg(arg);
	} 
	
	iptr->variableTable->deleteVariable(arg);
	return Message::PASS_NO_CONTENT_MSG;
}