#include "CommandPatternAnalyzer.h"
#include "Command.h"

using namespace em::intrprt::pattern;
using em::intrprt::cmd::Command;

CommandPatternAnalyzer::CommandPatternAnalyzer(array<Command^>^ commands) {
	this->commandTable = gcnew CommandTable(commands);
}

CommandPatternAnalyzer::~CommandPatternAnalyzer() {
	delete this->commandTable;
}

Message^ CommandPatternAnalyzer::analyze(Match^ result, Interpreter^ iptr) {
	
	String^ cmdL = result->Groups[1]->Value;
	Command^ cmd;
	if (this->commandTable->checkGet(cmdL, cmd)) {

		
		CaptureCollection^ argsCol = result->Groups[2]->Captures;
		array<String^>^ args = gcnew array<String^>(argsCol->Count);

		int i = 0;
		for each(Capture^ capture in argsCol) {
			args[i++] = capture->Value;
		}

		int ti = checkVarTypes(args, cmd->argTypes);
		if (ti < 0) {
			return Message::SYNTAX_ERROR_MSG;
		}

		return cmd->performCommand(args, ti, iptr);
		
	}

	return gcnew Message(Message::State::ERROR, "Cannot find the commmand \"" + cmdL + "\"");
}

String^ CommandPatternAnalyzer::buildInitPattern() {
	return "^\\s*(\\w+)\\s*(?>\\s+" + PatternAnalyzer::NAME_OR_VALUE_PATTERN + ")*$";
}

FileCommandPatternAnalyzer::FileCommandPatternAnalyzer(array<Command^>^ commands) : CommandPatternAnalyzer(commands) {

}
FileCommandPatternAnalyzer::~FileCommandPatternAnalyzer() {
}

Message^ FileCommandPatternAnalyzer::analyze(Match^ result, Interpreter^ iptr) {

	String^ cmdL = result->Groups[1]->Value;

	Command^ cmd;
	if (this->commandTable->checkGet(cmdL, cmd)) {
	
		return cmd->performCommand(nullptr, 0, iptr);
	}

	return gcnew Message(Message::State::ERROR, "Cannot find the commmand \"" + cmdL + "\"");
}

String^ FileCommandPatternAnalyzer::buildInitPattern() {
	return "^\\s*(\\w)\\s*$";
}