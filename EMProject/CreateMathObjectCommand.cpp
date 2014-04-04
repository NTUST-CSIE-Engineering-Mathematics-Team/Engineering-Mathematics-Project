#include "CreateMathObjectCommand.h"
#include "Interpreter.h"

using namespace em::intrprt::cmd;

CreateFileMathObjectCommand::CreateFileMathObjectCommand(String^ cl, FilePatternAnalyzer^ analyzer) : Command(cl, ' '), analyzer(analyzer) {
}

CreateFileMathObjectCommand::~CreateFileMathObjectCommand() {
}

Message^ CreateFileMathObjectCommand::performCommand(String^ arg, Interpreter^ iptr) {
	this->analyzer->reset(iptr);
	iptr->needNextLine(this->analyzer);
	return Message::PARSING_MSG;
}

CreateFileMathObjectCommand::FilePatternAnalyzer::FilePatternAnalyzer() : PatternAnalyzer() {
	initRegex = this->bindingPattern;
}

CreateFileMathObjectCommand::FilePatternAnalyzer::~FilePatternAnalyzer() {
}


Message^ CreateFileMathObjectCommand::FilePatternAnalyzer::wrongFormatMsg (Interpreter^ iptr) {
	reset(iptr);
	return gcnew Message(Message::State::ERROR, "Wrong data type, please check out your object file");
}

CreateFileMathObjectCommand::FileMatrixConstructionAnalyzer::FileMatrixConstructionAnalyzer() : rowIndex(-1) {

}
CreateFileMathObjectCommand::FileMatrixConstructionAnalyzer::~FileMatrixConstructionAnalyzer() {

}

Message^ CreateFileMathObjectCommand::FileMatrixConstructionAnalyzer::analyze(Match^ result, Interpreter^ iptr) {

	
	if (this->tmpMat == nullptr) {
		int d1, d2;
		if (!isInteger(result->Groups[1]->Captures[0]->Value, d1) || !isInteger(result->Groups[1]->Captures[1]->Value, d2)) {
			return this->wrongFormatMsg(iptr);
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
				return this->wrongFormatMsg(iptr);
			}

			this->tmpMat[this->rowIndex, col++] = s;
		}
	}

	if (this->rowIndex == tmpMat->columnLength - 1) {

		String^ mName = iptr->variableTable->addVariable(this->tmpMat);
		
		reset(iptr);
		return gcnew Message(Message::State::PASS, Message::STORAGE_COLOR, "Loaded matrix \"" + mName + "\" into the static storage");
	}

	return Message::PARSING_MSG;
}

void CreateFileMathObjectCommand::FileMatrixConstructionAnalyzer::reset(Interpreter^ iptr) {
	iptr->releaseNextLine();
	this->rowIndex = -1;
	this->regex = this->initRegex;
	this->tmpMat = nullptr;
}


String^ CreateFileMathObjectCommand::FileMatrixConstructionAnalyzer::buildInitPattern() {
	return PatternAnalyzer::rowValuePattern(2);
}

CreateFileMathObjectCommand::FileVectorConstructionAnalyzer::FileVectorConstructionAnalyzer() {

}

CreateFileMathObjectCommand::FileVectorConstructionAnalyzer::~FileVectorConstructionAnalyzer() {

}

Message^ CreateFileMathObjectCommand::FileVectorConstructionAnalyzer::analyze(Match^ result, Interpreter^ iptr) {

	if (this->tmpVec == nullptr) {
		int r;
		if (!isInteger(result->Groups[1]->Value, r)) {
			return this->wrongFormatMsg(iptr);
		}

		this->tmpVec = gcnew Vector(r);
		this->initRegex = this->regex;
		this->regex = gcnew Regex(PatternAnalyzer::rowValuePattern(tmpVec->dimension));

		return Message::PARSING_MSG;
	}

	double s;
	int i = 0;
	for each(Capture^ cp in result->Groups[1]->Captures) {
		if (!isDouble(cp->Value, s)) {
			return this->wrongFormatMsg(iptr);
		}

		this->tmpVec[i++] = s;
	}
	bool isScl = this->tmpVec->dimension == 1;
	String^ vName = iptr->variableTable->addVariable( isScl ? (MathObject^)gcnew Scalar(this->tmpVec[0]) : this->tmpVec);
	
	reset(iptr);
	return gcnew Message(Message::State::PASS, Message::STORAGE_COLOR, "Loaded " + (isScl ? "scalar" : "vector") + " \"" + vName + "\" into the static storage");

}

void CreateFileMathObjectCommand::FileVectorConstructionAnalyzer::reset(Interpreter^ iptr) {
	iptr->releaseNextLine();
	this->regex = this->initRegex;
	this->tmpVec = nullptr;
}

String^ CreateFileMathObjectCommand::FileVectorConstructionAnalyzer::buildInitPattern() {
	return PatternAnalyzer::rowValuePattern(1);
}