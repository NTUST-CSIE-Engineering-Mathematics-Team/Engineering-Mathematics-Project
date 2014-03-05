#include "CommandInterpreter.h"

using namespace em;

CommandInterpreter::CommandInterpreter()
{
}

Message^ CommandInterpreter::inetrpret(String^ line) {
	
	return gcnew Message(Message::Type::Error, "God Damn EM");
}

CommandInterpreter::~CommandInterpreter()
{
}
