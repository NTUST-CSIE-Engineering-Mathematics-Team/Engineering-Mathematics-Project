#include "AdditionOperator.h"

#include "OperatorFactory.h"
using namespace em::math::engine::expression::operators;

AdditionOperator::AdditionOperator(Expression^ a, Expression^ b) : CommutativeOperator("+", a, b) {
	this->addOperation<Scalar^, Scalar^>(gcnew Operation<Scalar^, Scalar^>(SS));
	this->addOperation<Vector^, Vector^>(gcnew Operation<Vector^, Vector^>(VV));
	this->addOperation<Matrix^, Matrix^>(gcnew Operation<Matrix^, Matrix^>(MM));
}


AdditionOperator::~AdditionOperator() {
}

MathObject^ AdditionOperator::SS(Scalar^ a, Scalar^ b, Message^% msg) {
	return a + b;
}

MathObject^ AdditionOperator::VV(Vector^ a, Vector^ b, Message^% msg) {
	return a + b;
}

MathObject^ AdditionOperator::MM(Matrix^ a, Matrix^ b, Message^% msg) {

	Matrix^ m = a + b;
	if (m == nullptr) {
		msg = gcnew Message(Message::State::ERROR, "The matrices with different size cannot be added");
	}

	return m;
}
