#include "MathObjExp.h"

using namespace em::math::engine::expression;

MathObjExp::MathObjExp(bool negative, MathObject^ mo) : mo(negative ? -mo : mo) {
}


MathObjExp::~MathObjExp() {
	this->mo = nullptr;
}

MathObject^ MathObjExp::compute(Message^% message) {
	return this->mo;
}