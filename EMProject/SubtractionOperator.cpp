#include "SubtractionOperator.h"


using namespace em::math::engine::expression::operators;

SubtractionOperator::SubtractionOperator(Expression^ a, Expression^ b) : BinaryOperator("-", a, b) {
	this->addOperation<Scalar^, Scalar^>(gcnew Operation<Scalar^, Scalar^>(SS));
	this->addOperation<Vector^, Vector^>(gcnew Operation<Vector^, Vector^>(VV));
	this->addOperation<Matrix^, Matrix^>(gcnew Operation<Matrix^, Matrix^>(MM));
}


SubtractionOperator::~SubtractionOperator() {
}

MathObject^ SubtractionOperator::SS(Scalar^ a, Scalar^ b, Message^% msg) {
	return a - b;
}

MathObject^ SubtractionOperator::VV(Vector^ a, Vector^ b, Message^% msg) {
	return a - b;
}

MathObject^ SubtractionOperator::MM(Matrix^ a, Matrix^ b, Message^% msg) {

	Matrix^ m = a - b;
	if (m == nullptr) {
		msg = gcnew Message(Message::State::ERROR, "The Matrices with different size cannot be subtracted");
	}

	return m;
}
