#include "SubtractionOperator.h"


using namespace em::math::engine::expression::operators;

SubtractionOperator::SubtractionOperator(Expression^ a, Expression^ b) : BinaryOperator("-", a, b) {
	this->addOperation<Scalar^, Scalar^>(gcnew Operation<Scalar^, Scalar^>(S_S));
	this->addOperation<Vector^, Vector^>(gcnew Operation<Vector^, Vector^>(V_V));
	this->addOperation<Matrix^, Matrix^>(gcnew Operation<Matrix^, Matrix^>(M_M));
}


SubtractionOperator::~SubtractionOperator() {
}

MathObject^ SubtractionOperator::S_S(Scalar^ a, Scalar^ b, Message^% msg) {
	return a - b;
}

MathObject^ SubtractionOperator::V_V(Vector^ a, Vector^ b, Message^% msg) {
	return a - b;
}

MathObject^ SubtractionOperator::M_M(Matrix^ a, Matrix^ b, Message^% msg) {

	Matrix^ m = a - b;
	if (m == nullptr) {
		msg = gcnew Message(Message::State::ERROR, "The Matrices with different size cannot be subtracted");
	}

	return m;
}
