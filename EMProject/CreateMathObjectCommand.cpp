#include "CreateMathObjectCommand.h"
#include "Interpreter.h"

using namespace em::intrprt::cmd;

CreateMathObjectCommand::CreateMathObjectCommand(String^ cl, array<String^>^ argTs) : Command(cl, argTs) {
	this->nameIndices = gcnew array<int>(argTs->Length);
	int i = 0;
	for each(String^ t in argTs) {
		nameIndices[i++] = t->IndexOf('n');
	}
}

CreateMathObjectCommand::~CreateMathObjectCommand() {
}

Message^ CreateMathObjectCommand::performCommand(array<String^>^ args, int typeIndex, Interpreter^ iptr) {

	
	if (iptr->variableTable->contains(args[this->nameIndices[typeIndex]])) {
		return Message::varAlreadyExistMsg(args[this->nameIndices[typeIndex]]);
	}
	
	return this->createMathObject(typeIndex, args[this->nameIndices[typeIndex]], args, iptr);
}

CreateFileMathObjectCommand::CreateFileMathObjectCommand(String^ cl, PatternAnalyzer^ analyzer) : Command(cl, nullptr), analyzer(analyzer) {
}

CreateFileMathObjectCommand::~CreateFileMathObjectCommand() {
}

Message^ CreateFileMathObjectCommand::performCommand(array<String^>^ args,int typeIndex, Interpreter^ iptr) {
	iptr->needNextLine(this->analyzer);
	return Message::PARSING_MSG;
}

CreateFileMathObjectCommand::FileMatrixConstructionAnalyzer::FileMatrixConstructionAnalyzer() : rowIndex(-1) {

}
CreateFileMathObjectCommand::FileMatrixConstructionAnalyzer::~FileMatrixConstructionAnalyzer() {

}

Message^ CreateFileMathObjectCommand::FileMatrixConstructionAnalyzer::analyze(Match^ result, Interpreter^ iptr) {

	String^ wot = "Wrong data type, please check out your object file";
	if (this->tmpMat == nullptr) {
		int d1, d2;
		if (!isInteger(result->Groups[1]->Captures[0]->Value, d1) || !isInteger(result->Groups[1]->Captures[1]->Value, d2)) {
			return gcnew Message(Message::State::ERROR, wot);
		}

		this->tmpMat = gcnew Matrix(d1, d2);
		this->initRegex = this->regex;
		this->regex = gcnew Regex(PatternAnalyzer::rowValuePattern(tmpMat->rowLength));

	} else {
		this->rowIndex++;
		int col = 0;
		double s;
		for each(Capture^ cp in result->Groups[1]->Captures) {
			if (!isDouble(cp->Value, s)) {
				return gcnew Message(Message::State::ERROR, wot);
			}

			this->tmpMat[this->rowIndex, col++] = s;
		}
	}

	if (this->rowIndex == tmpMat->columnLength - 1) {

		String^ mName = iptr->variableTable->addVariable(this->tmpMat);
		
		iptr->releaseNextLine();
		this->rowIndex = -1;
		this->regex = this->initRegex;
		this->tmpMat = nullptr;
		return gcnew Message(Message::State::PASS, "Loaded matrix \"" + mName + "\" into the static storage", Message::STORAGE_COLOR);
	}

	return Message::PARSING_MSG;
}

String^ CreateFileMathObjectCommand::FileMatrixConstructionAnalyzer::buildInitPattern() {
	return PatternAnalyzer::rowValuePattern(2);
}

CreateFileMathObjectCommand::FileVectorConstructionAnalyzer::FileVectorConstructionAnalyzer() {

}

CreateFileMathObjectCommand::FileVectorConstructionAnalyzer::~FileVectorConstructionAnalyzer() {

}

Message^ CreateFileMathObjectCommand::FileVectorConstructionAnalyzer::analyze(Match^ result, Interpreter^ iptr) {

	String^ wot = "Wrong data type, please check out your object file";
	if (this->tmpVec == nullptr) {
		int r;
		if (!isInteger(result->Groups[1]->Value, r)) {
			return gcnew Message(Message::State::ERROR, wot);
		}
		this->tmpVec = gcnew Vector(r);
		this->initRegex = this->regex;
		this->regex = gcnew Regex(PatternAnalyzer::rowValuePattern(tmpVec->rank));

		return Message::PARSING_MSG;
	}

	double s;
	int i = 0;
	for each(Capture^ cp in result->Groups[1]->Captures) {
		if (!isDouble(cp->Value, s)) {
			return gcnew Message(Message::State::ERROR, wot);
		}

		this->tmpVec[i++] = s;
	}

	String^ vName = iptr->variableTable->addVariable(this->tmpVec);
	this->tmpVec = nullptr;

	iptr->releaseNextLine();
	this->regex = this->initRegex;
	return gcnew Message(Message::State::PASS, "Loaded vector \"" + vName + "\" into the static storage", Message::STORAGE_COLOR);

}

String^ CreateFileMathObjectCommand::FileVectorConstructionAnalyzer::buildInitPattern() {
	return PatternAnalyzer::rowValuePattern(1);
}