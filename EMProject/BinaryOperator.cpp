#include "BinaryOperator.h"

using namespace em::math::engine::expression::operators;

BinaryOperator::BinaryOperator(String^ symbol, Expression^ opndA, Expression^ opndB) : symbol(symbol), opndA(opndA), opndB(opndB) {
}


BinaryOperator::~BinaryOperator() {
	delete this->opndA;
	delete this->opndB;
	
}

MathObject^ BinaryOperator::compute(Message^% message) {
	MathObject^ moA = this->opndA->compute(message),^ moB = this->opndB->compute(message);
	
	if (moA == nullptr || moB == nullptr) {
		return nullptr;
	}

	MathObject^ result = this->calculate(moA, moB);
	
	return result;
}