#include "DivisionOperator.h"

using namespace em::math::engine::expression::operators;

DivisionOperator::DivisionOperator(Expression^ a, Expression^ b) : BinaryOperator("/", a, b) {
	this->addOperation<Scalar^, Scalar^>(gcnew Operation<Scalar^, Scalar^>(SS));
	this->addOperation<Matrix^, Scalar^>(gcnew Operation<Matrix^, Scalar^>(MS));
	this->addOperation<Vector^, Scalar^>(gcnew Operation<Vector^, Scalar^>(VS));
}


DivisionOperator::~DivisionOperator() {
}

MathObject^ DivisionOperator::SS(Scalar^ a, Scalar^ b, Message^% msg) {
	return a / b;
}

MathObject^ DivisionOperator::MS(Matrix^ a, Scalar^ b, Message^% msg) {
	return a / b;
}

MathObject^ DivisionOperator::VS(Vector^ a, Scalar^ b, Message^% msg) {
	return a / b;
}