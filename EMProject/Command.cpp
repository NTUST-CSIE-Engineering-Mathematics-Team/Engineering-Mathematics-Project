#include "Command.h"

using namespace em::intrprt::cmd;


Command::Command(String^ cl, wchar_t argT) : cmdLiteral(cl), argT(argT) {
}


Command::~Command() {
	delete this->cmdLiteral;
}
