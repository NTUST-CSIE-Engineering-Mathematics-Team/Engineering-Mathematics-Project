#include "CommandTable.h"

using namespace em::intrprt::cmd;


CommandTable::CommandTable(array<Command^>^ commands) : ConstantTable(createKeys(commands), commands) {
}


CommandTable::~CommandTable() {
}

array<String^>^ CommandTable::createKeys(array<Command^>^ commands) {

	array<String^>^ keys = gcnew array<String^>(commands->Length);
	for (int i = 0; i < commands->Length; i++) {
		keys[i] = commands[i]->commandLiteral;
	}

	return keys;
}