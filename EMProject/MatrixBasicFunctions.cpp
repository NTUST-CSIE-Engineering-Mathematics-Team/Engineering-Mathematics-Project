#include "MatrixBasicFunctions.h"

using namespace em::math::engine::expression::functions;

MathObject^ MatrixBasicFunctions::transpose$M(array<MathObject^>^ mos, Message^% msg) {
	Matrix^ mat;
	Matrix::matrixCast(mos[0], mat);

	return mat->transpose();
}
MathObject^ MatrixBasicFunctions::row_ech$M(array<MathObject^>^ mos, Message^% msg) {
	Matrix^ mat;
	Matrix::matrixCast(mos[0], mat);

	return mat->rowEchelonForm;
}

MathObject^ MatrixBasicFunctions::solve_linear$M_V(array<MathObject^>^ mos, Message^% msg) {
	Matrix^ mat, ^sols;
	Vector^ consts;
	Matrix::matrixCast(mos[0], mat);
	Vector::vectorCast(mos[1], consts);

	dealLinearSystemResult(mat->solveLinearSystem(consts, sols), msg);
	return sols;
		
}

MathObject^ MatrixBasicFunctions::solve_linear$M_M(array<MathObject^>^ mos, Message^% msg) {
	Matrix^ mat, ^ consts, ^ sols;
	Matrix::matrixCast(mos[0], mat);
	Matrix::matrixCast(mos[1], consts);

	dealLinearSystemResult(mat->solveLinearSystem(consts, sols), msg);
	return sols;

}

MathObject^ MatrixBasicFunctions::inverse$M(array<MathObject^>^ mos, Message^% msg) {
	Matrix^ mat;
	Matrix::matrixCast(mos[0], mat);

	Matrix^ inverse = mat->inverse;

	if (inverse == nullptr) {
		msg = gcnew Message(Message::State::ERROR, "This matrix does not have the inverse matrix");
	}

	return inverse;
}

MathObject^ MatrixBasicFunctions::det$M(array<MathObject^>^ mos, Message^% msg) {
	Matrix^ mat;
	Matrix::matrixCast(mos[0], mat);

	Scalar^ det = mat->determinant;

	if (det == nullptr) {
		msg = notSquareErrMsg("det");
	}

	return det;
}

MathObject^ MatrixBasicFunctions::rank$M(array<MathObject^>^ mos, Message^% msg) {
	Matrix^ mat;
	Matrix::matrixCast(mos[0], mat);

	return mat->rank;
}

MathObject^ MatrixBasicFunctions::ul_decom$M(array<MathObject^>^ mos, Message^% msg) {
	Matrix^ mat;
	Matrix::matrixCast(mos[0], mat);
	MathObjGenericSet<Matrix^>^ result = gcnew MathObjGenericSet<Matrix^>();
	
	Matrix^ upper,^ lower;
	mat->ulDecomposition(upper, lower);
	result->add(lower);
	result->add(upper);
	
	return result;
}

MathObject^ MatrixBasicFunctions::pow$M_S(array<MathObject^>^ mos, Message^% msg) {
	Scalar^ scl;
	Scalar::scalarCast(mos[1], scl);
	if (scl->isInteger) {
		msg = gcnew Message(Message::State::ERROR, "A exponent of a matrix cannot be a decimal");
		return nullptr;
	}
	Matrix^ mat;
	Matrix::matrixCast(mos[0], mat);

	mat = mat->pow(scl->toInteger());
	if (mat == nullptr) {
		msg = gcnew Message(Message::State::ERROR, "Connot perform function \"pow\" on a non-square matrix or the matrix that is not invertible");
	}

	return mat;
}

void MatrixBasicFunctions::dealLinearSystemResult(Matrix::SolutionState ss, Message^% msg) {
	switch (ss) {
	case Matrix::SolutionState::INCONSISTENT:
		msg = gcnew Message(Message::State::ERROR, "There is no solution to this linear system");
		break;
	case Matrix::SolutionState::INFINITE:
		msg = gcnew Message(Message::State::ERROR, "There are infinite solutions to this linear system");
		break;
	case Matrix::SolutionState::BAD_CONSTANTS:
		msg = gcnew Message(Message::State::ERROR, "The size of the matrix of constants is invaild");
		break;
	}
}

Message^ MatrixBasicFunctions::notSquareErrMsg(String^ funName) {
	return gcnew Message(Message::State::ERROR, "Cannot perform  function \"" + funName + "\" on a non-square matrix");
}
						