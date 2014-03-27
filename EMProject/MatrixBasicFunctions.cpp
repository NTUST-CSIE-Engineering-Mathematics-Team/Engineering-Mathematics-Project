#include "MatrixBasicFunctions.h"

using namespace em::math::engine::expression::functions;

MathObject^ MatrixBasicFunctions::transpose$M(array<MathObject^>^ mos, Message^% msg) {
	Matrix^ mat;
	Matrix::matrixCast(mos[0], mat);

	return mat->transpose();
}