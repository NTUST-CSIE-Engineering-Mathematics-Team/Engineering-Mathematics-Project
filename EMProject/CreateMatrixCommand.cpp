#include "CreateMatrixCommand.h"
#include "KeywordCollection.h"
#include "Interpreter.h"
#include "All_Math.h"

using namespace em::intrprt::cmd;

CreateMatrixCommand::CreateMatrixCommand() : CreateMathObjectCommand(KeywordCollection::CREATE_MATRIX_CMD, "IIn", "IInN", "nN", "nE") {
}

CreateMatrixCommand::~CreateMatrixCommand() {
}

Message^ CreateMatrixCommand::createMathObject(int typeIndex, String^ varName, array<String^>^ rawArgs, Interpreter^ iptr) {
	
	if (typeIndex == 3) {
		MathObject^ mo;
		Message^  msg;
		msg = iptr->arithmeticEngine->execute(rawArgs[1], mo);

		if (mo == nullptr) {
			return msg;
		}

		Matrix^ mat;
		if (Matrix::matrixCast(mo, mat)) {

			iptr->variableTable->addVariable(varName, mat);
			msg = Message::PASS_NO_CONTENT_MSG;
		} else {
			msg = gcnew Message(Message::State::ERROR, "Type error, can not assign a " + mo->mathType->ToLower() + " to a matrix");
		}

		return msg;
	}

	if (typeIndex == 1 || typeIndex == 2) {

		String^ vn = rawArgs[rawArgs->Length - 1];
		MathObject^ mo;
		if (!iptr->variableTable->checkGet(vn, mo)) {
			return Message::varNotFoundMsg(vn);
		}

		Matrix^ mat;
		if (!Matrix::matrixCast(mo, mat)) {
			return gcnew Message(Message::State::ERROR, "Cannot initialize a matrix with a non-matrix variable in the same line");
		}

		Matrix^ newMat;
		if (typeIndex == 2) {
			newMat = gcnew Matrix(mat);
		} else {
			int d1 = System::Convert::ToInt32(rawArgs[0]);
			int d2 = System::Convert::ToInt32(rawArgs[1]);

			if (mat->columnLength > d1 || mat->rowLength > d2) {
				return gcnew Message(Message::State::ERROR, "The dimension of the matrix \"" + vn + "\" exceeds the boundary of matrix");
			}
			newMat = gcnew Matrix(d1, d2);
			newMat->fitAssign(mat);
		}

		iptr->variableTable->addVariable(varName, newMat);
		return Message::PASS_NO_CONTENT_MSG;

	}

	iptr->needNextLine(gcnew MatrixConstructionAnalyzer(gcnew Matrix(System::Convert::ToInt32(rawArgs[0]), System::Convert::ToInt32(rawArgs[1])), varName));
	return Message::PARSING_MSG;
	
}

CreateMatrixCommand::MatrixConstructionAnalyzer::MatrixConstructionAnalyzer(Matrix^ mat, String^ mName) : tmpMat(mat), matName(mName), rowIndex(-1) {
	
}

CreateMatrixCommand::MatrixConstructionAnalyzer::~MatrixConstructionAnalyzer() {
}

Message^ CreateMatrixCommand::MatrixConstructionAnalyzer::analyze(Match^ result, Interpreter^ iptr) {
	
	this->rowIndex++;
	int col = 0;
	for each(Capture^ cp in result->Groups[1]->Captures) {

		double v;
		if (isName(cp->Value)) {
			MathObject^ mo;
			if (!iptr->variableTable->checkGet(cp->Value, mo)) {
				return Message::varNotFoundMsg(cp->Value);
			}

			 Scalar^ scl;
			Vector^ vec;
			
			if (Scalar::scalarCast(mo, scl)) {
				tmpMat[this->rowIndex, col++] = scl;

			} else if (result->Groups[1]->Captures->Count == 1 && Vector::vectorCast(mo, vec)) {
				if (vec->rank > tmpMat->rowLength) {
					return gcnew Message(Message::State::ERROR, "The rank of the vector \"" + cp->Value + "\" exceeds the boundary of the matrix");
				}

				tmpMat[Matrix::VectorOption::ROW, this->rowIndex] = vec;
				
			} else {
				return gcnew Message(Message::State::ERROR, "The \"" + mo->mathType + "\" type of the variable is not acceptable");
			}

		} else if (isDouble(cp->Value, v)) {
			tmpMat[this->rowIndex, col++] = v;
		} else {
			return Message::varNotFoundMsg(cp->Value);
		}
	}
	
	return this->tryFinish(iptr);
	
}

String^ CreateMatrixCommand::MatrixConstructionAnalyzer::buildInitPattern() {
	if (tmpMat == nullptr) {
		return PatternAnalyzer::NAME_PATTERN;
	}
	return  PatternAnalyzer::rowValuePattern(tmpMat->rowLength);
}

Message^ CreateMatrixCommand::MatrixConstructionAnalyzer::tryFinish(Interpreter^ iptr) {
	if (this->rowIndex == tmpMat->columnLength - 1) {
		iptr->variableTable->addVariable(this->matName, this->tmpMat);
		iptr->releaseNextLine();
		return Message::PASS_NO_CONTENT_MSG;
	}

	return Message::PARSING_MSG;
}