#include "MatrixBasicFunctions.h"

using namespace em::math::engine::expression::functions;

MathObject^ MatrixBasicFunctions::transpose$M(array<MathObject^>^ mos, Message^% msg) {
	Matrix^ mat;
	Matrix::matrixCast(mos[0], mat);

	return mat->transpose();
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
		msg = gcnew Message(Message::State::ERROR, "cannot perform power function on a non-square matrix");
	}

	return mat;
}