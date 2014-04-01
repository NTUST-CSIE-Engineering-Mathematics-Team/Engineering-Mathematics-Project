#include "MatrixBasicFunctions.h"

using namespace em::math::engine::expression::functions;

MathObject^ MatrixBasicFunctions::transpose$M(array<MathObject^>^ mos, Message^% msg) {
	Matrix^ mat;
	Matrix::matrixCast(mos[0], mat);

	return mat->transpose();
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

MathObject^ MatrixBasicFunctions::ul_decom$M(array<MathObject^>^ mos, Message^% msg) {
	Matrix^ mat;
	Matrix::matrixCast(mos[0], mat);
	MathObjGenericSet<Matrix^>^ result = gcnew MathObjGenericSet<Matrix^>();
	
	Matrix^ upper,^ lower;
	mat->ulDecomposition(upper, lower);
	result->add(upper);
	result->add(lower);
	return result;
}

MathObject^ MatrixBasicFunctions::pow$M_S(array<MathObject^>^ mos, Message^% msg) {
	Scalar^ scl;
	Scalar::scalarCast(mos[1], scl);
	if (System::Math::Truncate(scl) != scl) {
		msg = gcnew Message(Message::State::ERROR, "A exponent of a matrix cannot be a decimal");
		return nullptr;
	}
	Matrix^ mat;
	Matrix::matrixCast(mos[0], mat);

	mat = mat->pow((int)scl);
	if (mat == nullptr) {
		msg = gcnew Message(Message::State::ERROR, "Connot perform function \"pow\" on a non-square matrix or the matrix that is not invertible");
	}

	return mat;
}

Message^ MatrixBasicFunctions::notSquareErrMsg(String^ funName) {
	return gcnew Message(Message::State::ERROR, "Cannot perform  function \"" + funName + "\" on a non-square matrix");
}
						