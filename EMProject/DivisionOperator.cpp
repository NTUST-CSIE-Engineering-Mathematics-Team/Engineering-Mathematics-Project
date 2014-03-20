#include "DivisionOperator.h"

using namespace em::math::engine::expression::operators;

DivisionOperator::DivisionOperator(Expression^ a, Expression^ b) : BinaryOperator("/", a, b) {
	this->addOperation<Scalar^, Scalar^>(gcnew Operation<Scalar^, Scalar^>(S_S));
	this->addOperation<Matrix^, Scalar^>(gcnew Operation<Matrix^, Scalar^>(M_S));
	this->addOperation<Vector^, Scalar^>(gcnew Operation<Vector^, Scalar^>(V_S));
}


DivisionOperator::~DivisionOperator() {
}

MathObject^ DivisionOperator::S_S(Scalar^ a, Scalar^ b, Message^% msg) {
	return a / b;
}

MathObject^ DivisionOperator::M_S(Matrix^ a, Scalar^ b, Message^% msg) {
	return a / b;
}

MathObject^ DivisionOperator::V_S(Vector^ a, Scalar^ b, Message^% msg) {
	return a / b;
}