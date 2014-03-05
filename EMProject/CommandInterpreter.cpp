#include "CommandInterpreter.h"

using namespace em;
using namespace em::intrprt;

CommandInterpreter::CommandInterpreter()
{
}

Message^ CommandInterpreter::inetrpret(String^ line) {
	
	return gcnew Message(Message::Type::Error, "God Damn EM");
}

CommandInterpreter::~CommandInterpreter()
{
}
