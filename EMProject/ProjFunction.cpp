#include "ProjFunction.h"

using namespace em::math::engine::expression::functions;
ProjFunction::ProjFunction(bool negative, array<Expression^>^ exps) : Function(negative, exps, "proj", "VV") {
}


ProjFunction::~ProjFunction() {
}

MathObject^ ProjFunction::performFunction(array<MathObject^>^ mos) {
	Vector^ v1,^ v2;
	Vector::vectorCast(mos[0], v1);
	Vector::vectorCast(mos[1], v2);
	return v1->projection(v2);
}