#include "CommandPatternAnalyzer.h"
#include "Command.h"
#include "ArithmeticEngine.h"

using namespace em::intrprt::pattern;
using em::intrprt::cmd::Command;
using System::Text::StringBuilder;
using em::math::engine::ArithmeticEngine;

CommandPatternAnalyzer::CommandPatternAnalyzer(array<Command^>^ commands) {
	this->commandTable = gcnew CommandTable(commands);
}

CommandPatternAnalyzer::~CommandPatternAnalyzer() {
	delete this->commandTable;
}

Message^ CommandPatternAnalyzer::analyze(Match^ result, Interpreter^ iptr) {
	if (result->Groups["i"]->Success) {
		return gcnew Message(Message::State::ERROR, "The parenthese is not balanced");
	}

	String^ cmdL = result->Groups[1]->Value;
	Command^ cmd;
	if (this->commandTable->checkGet(cmdL, cmd)) {
		if (!checkVarType(result->Groups[2]->Value, cmd->argType)) {
			return Message::SYNTAX_ERROR_MSG;
		}

		return cmd->performCommand(result->Groups[2]->Value, iptr);
		
	}

	return gcnew Message(Message::State::ERROR, "Cannot find the commmand \"" + cmdL + "\"");
}

String^ CommandPatternAnalyzer::buildInitPattern() {
	StringBuilder^ sb = gcnew StringBuilder();

	sb->AppendFormat("^\\s*(\\w+)\\s+({0})$", ArithmeticEngine::arithmeticContentPattern("i")); 

	return sb->ToString();
}

FileCommandPatternAnalyzer::FileCommandPatternAnalyzer(array<Command^>^ commands) : CommandPatternAnalyzer(commands) {

}
FileCommandPatternAnalyzer::~FileCommandPatternAnalyzer() {
}

Message^ FileCommandPatternAnalyzer::analyze(Match^ result, Interpreter^ iptr) {

	String^ cmdL = result->Groups[1]->Value;

	Command^ cmd;
	if (this->commandTable->checkGet(cmdL, cmd)) {
	
		return cmd->performCommand(nullptr, iptr);
	}

	return gcnew Message(Message::State::ERROR, "Cannot find the commmand \"" + cmdL + "\"");
}

String^ FileCommandPatternAnalyzer::buildInitPattern() {
	return "^\\s*(\\w)\\s*$";
}