#include "BinaryOperator.h"

using namespace em::math::engine;

BinaryOperator::BinaryOperator(String^ symbol) : symbol(symbol) {
}


BinaryOperator::~BinaryOperator() {
}

void BinaryOperator::setOperands(Expression^ opndA, Expression^ opndB) {
	this->opndA = opndA;
	this->opndB = opndB;
}

MathObject^ BinaryOperator::compute() {
	MathObject^ result = this->calculate(this->opndA->compute(), this->opndB->compute());
	this->opndA = nullptr;
	this->opndB = nullptr;
	return result;
}