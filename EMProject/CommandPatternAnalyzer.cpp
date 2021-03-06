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
		return Message::PARENTHESE_NOT_BALANCED_MSG;
	}

	String^ cmdL = result->Groups[1]->Value;
	Command^ cmd;
	if (this->commandTable->checkGet(cmdL, cmd)) {

		CaptureCollection^ cc = result->Groups[ArithmeticEngine::operandTag]->Captures;
		
		StringBuilder^ sb = gcnew StringBuilder();
		Message^ tMsg;

		for each(Capture^ cp in cc) {
			if (!checkVarType(cp->Value, cmd->argType)) {
				return Message::SYNTAX_ERROR_MSG;
			}

			tMsg = cmd->performCommand(cp->Value, iptr);

			if (tMsg->msgState == Message::State::ERROR) {
				return tMsg;
			}
			if (!String::IsNullOrEmpty(tMsg)) {
				sb->AppendFormat("{0}\n", tMsg->msgContent);
			}
		}
		if (sb->Length > 0) {
			sb->Remove(sb->Length - 1, 1);
		}
		return gcnew Message(tMsg->msgState, tMsg->msgColor, sb->ToString());
		
	}

	return gcnew Message(Message::State::ERROR, "Cannot find the commmand \"" + cmdL + "\"");
}

String^ CommandPatternAnalyzer::buildInitPattern() {
	StringBuilder^ sb = gcnew StringBuilder();

	sb->AppendFormat("^\\s*(\\w+)\\s+{0}$", ArithmeticEngine::multiArithmeticContentPattern("i")); 

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