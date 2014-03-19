#include "CommandFactory.h"



using namespace em::intrprt::cmd;
CommandFactory::CommandFactory() {
	
}


CommandFactory::~CommandFactory() {
}

generic<typename C> where C : Command
void CommandFactory::addCommand() {
	cmdList->Add(System::Activator::CreateInstance<C>());
}

array<Command^>^ CommandFactory::getCommandArray() {
	return cmdList->ToArray();
}

