#include "MultiplicationOperator.h"

using namespace em::math::engine::expression::operators;

MultiplicationOperator::MultiplicationOperator(Expression^ a, Expression^ b) : CommutativeOperator("*", a, b) {
	this->addOperation<Scalar^, Scalar^>(gcnew Operation<Scalar^, Scalar^>(S_S));
	this->addOperation<Vector^, Vector^>(gcnew Operation<Vector^, Vector^>(V_V));
	
	this->addOperation<Matrix^, Vector^>(gcnew Operation<Matrix^, Vector^>(M_V));
	this->addOperation<Matrix^, Matrix^>(gcnew Operation<Matrix^, Matrix^>(M_M));

	this->addCommutativeOperation<Scalar^, Vector^>(gcnew Operation<Scalar^, Vector^>(S_V));
	this->addCommutativeOperation<Scalar^, Matrix^>(gcnew Operation<Scalar^, Matrix^>(S_M));
}


MultiplicationOperator::~MultiplicationOperator() {
}

MathObject^ MultiplicationOperator::S_S(Scalar^ a, Scalar^ b, Message^% msg) {
	return a * b;
}

MathObject^ MultiplicationOperator::V_V(Vector^ a, Vector^ b, Message^% msg) {
	Scalar^ s = a * b;
	if (s == nullptr) {
		msg = gcnew Message(Message::State::ERROR, "The Vectors with different ranks cannot perform dot product");
	}

	return s;
}

MathObject^ MultiplicationOperator::M_M(Matrix^ a, Matrix^ b, Message^% msg) {
	Matrix^ m = a * b;
	if (m == nullptr) {
		msg = gcnew Message(Message::State::ERROR, "The matrices cannot perform multiplication\ndue to the mismatch of the column size and row size");
	}

	return m;
}

MathObject^ MultiplicationOperator::S_V(Scalar^ a, Vector^ b, Message^% msg) {
	return b * a;
}

MathObject^ MultiplicationOperator::S_M(Scalar^ a, Matrix^ b, Message^% msg) {
	return b * a;
}

MathObject^ MultiplicationOperator::M_V(Matrix^ a, Vector^ b, Message^% msg) {
	Vector^ v = a * b;
	if (v == nullptr) {
		msg = gcnew Message(Message::State::ERROR, "The matrix and vector cannot perform multiplication due to the mismatch of the row size and rank");
	}

	return v;
}