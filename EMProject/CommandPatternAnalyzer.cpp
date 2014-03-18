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
	StringBuilder^ sb = gcnew StringBuilder();

	sb->AppendFormat("^\\s*(\\w+)(?:\\s+({0}(?({1}){2}|{3}){4}))*$",
	 				 ArithmeticEngine::OPEN_PARENTHESE_PATTERN,
					 ArithmeticEngine::parentheseTag,
					 ArithmeticEngine::arithmeticContentPattern("i"),
					 NAME_OR_VALUE_PATTERN,
					 ArithmeticEngine::CLOSE_PARENTHESE_PATTERN);

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
	
		return cmd->performCommand(nullptr, 0, iptr);
	}

	return gcnew Message(Message::State::ERROR, "Cannot find the commmand \"" + cmdL + "\"");
}

String^ FileCommandPatternAnalyzer::buildInitPattern() {
	return "^\\s*(\\w)\\s*$";
}