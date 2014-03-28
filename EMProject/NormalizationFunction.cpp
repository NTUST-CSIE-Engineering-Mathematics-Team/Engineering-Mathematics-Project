#include "NormalizationFunction.h"


using namespace em::math::engine::expression::functions;
NormalizationFunction::NormalizationFunction(bool negative, array<Expression^>^ exps) : Function(negative, exps, "normlzd", "V") {
}


NormalizationFunction::~NormalizationFunction() {
}

MathObject^ NormalizationFunction::performFunction(array<MathObject^>^ mos) {
	Vector^ v1;
	
	Vector::vectorCast(mos[0], v1);
	
	return v1->normalized;
}
