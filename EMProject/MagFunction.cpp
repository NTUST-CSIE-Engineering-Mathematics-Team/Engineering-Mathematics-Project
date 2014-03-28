#include "MagFunction.h"

using namespace em::math::engine::expression::functions;
MagFunction::MagFunction(bool negative, array<Expression^>^ exps) : Function(negative, exps, "mag", "V") {
}


MagFunction::~MagFunction() {
}

MathObject^ MagFunction::performFunction(array<MathObject^>^ mos) {
	Vector^ v;
	Vector::vectorCast(mos[0], v);
	return gcnew Scalar(v->magnitude));
}