#include "MathObjExp.h"

using namespace em::math::engine::expression;

MathObjExp::MathObjExp(MathObject^ mo) : mo(mo) {
}


MathObjExp::~MathObjExp() {
	this->mo = nullptr;
}

MathObject^ MathObjExp::compute(Message^% message) {
	return this->mo;
}