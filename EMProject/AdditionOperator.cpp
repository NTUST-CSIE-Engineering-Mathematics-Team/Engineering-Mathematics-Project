#include "AdditionOperator.h"

#include "OperatorFactory.h"
using namespace em::math::engine::expression::operators;

AdditionOperator::AdditionOperator(Expression^ a, Expression^ b) : CommutativeOperator("+", a, b) {
	this->addOperation<Scalar^, Scalar^>(gcnew Operation<Scalar^, Scalar^>(S_S));
	this->addOperation<Vector^, Vector^>(gcnew Operation<Vector^, Vector^>(V_V));
	this->addOperation<Matrix^, Matrix^>(gcnew Operation<Matrix^, Matrix^>(M_M));
}


AdditionOperator::~AdditionOperator() {
}

MathObject^ AdditionOperator::S_S(Scalar^ a, Scalar^ b, Message^% msg) {
	return a + b;
}

MathObject^ AdditionOperator::V_V(Vector^ a, Vector^ b, Message^% msg) {
	return a + b;
}

MathObject^ AdditionOperator::M_M(Matrix^ a, Matrix^ b, Message^% msg) {

	Matrix^ m = a + b;
	if (m == nullptr) {
		msg = gcnew Message(Message::State::ERROR, "The matrices with different size cannot be added");
	}

	return m;
}
