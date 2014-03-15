#include "MathObjExp.h"

using namespace em::math::engine;

MathObjExp::MathObjExp(MathObject^ mo) : mo(mo) {
}


MathObjExp::~MathObjExp() {
}

MathObject^ MathObjExp::compute() {
	return this->mo;
}