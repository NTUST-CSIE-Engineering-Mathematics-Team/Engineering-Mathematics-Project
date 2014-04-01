#include "SimpleMathObjExp.h"

using namespace em::math::engine::expression;

SimpleMathObjExp::SimpleMathObjExp(bool negative, MathObject^ mo) : mo(negative ? -mo : mo) {
}


SimpleMathObjExp::~SimpleMathObjExp() {
	this->mo = nullptr;
}

MathObject^ SimpleMathObjExp::compute(Message^% message) {
	return this->mo;
}