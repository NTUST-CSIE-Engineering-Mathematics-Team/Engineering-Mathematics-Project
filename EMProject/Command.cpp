#include "Command.h"

using namespace em::intrprt::cmd;


Command::Command(String^ cl, ...array<String^>^ argTs) : cmdLiteral(cl) {
	this->argTs = argTs;
}


Command::~Command() {
	delete this->cmdLiteral;
}
