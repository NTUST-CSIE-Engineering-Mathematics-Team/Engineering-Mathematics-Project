#include "MultiplicationOperator.h"

using namespace em::math::engine::expression::operators;

MultiplicationOperator::MultiplicationOperator(Expression^ a, Expression^ b) : CommutativeOperator("*", a, b) {
	this->addOperation<Scalar^, Scalar^>(gcnew Operation<Scalar^, Scalar^>(SS));
	this->addOperation<Vector^, Vector^>(gcnew Operation<Vector^, Vector^>(VV));
	
	this->addOperation<Matrix^, Vector^>(gcnew Operation<Matrix^, Vector^>(MV));
	this->addOperation<Matrix^, Matrix^>(gcnew Operation<Matrix^, Matrix^>(MM));

	this->addCommutativeOperation<Scalar^, Vector^>(gcnew Operation<Scalar^, Vector^>(SV));
	this->addCommutativeOperation<Scalar^, Matrix^>(gcnew Operation<Scalar^, Matrix^>(SM));
}


MultiplicationOperator::~MultiplicationOperator() {
}

MathObject^ MultiplicationOperator::SS(Scalar^ a, Scalar^ b, Message^% msg) {
	return a * b;
}

MathObject^ MultiplicationOperator::VV(Vector^ a, Vector^ b, Message^% msg) {
	return a * b;
}

MathObject^ MultiplicationOperator::MM(Matrix^ a, Matrix^ b, Message^% msg) {
	Matrix^ m = a * b;
	if (m == nullptr) {
		msg = gcnew Message(Message::State::ERROR, "The matrices cannot perform multiplication\ndue to the mismatch of the column size and row size");
	}

	return m;
}

MathObject^ MultiplicationOperator::SV(Scalar^ a, Vector^ b, Message^% msg) {
	return b * a;
}

MathObject^ MultiplicationOperator::SM(Scalar^ a, Matrix^ b, Message^% msg) {
	return b * a;
}

MathObject^ MultiplicationOperator::MV(Matrix^ a, Vector^ b, Message^% msg) {
	Vector^ v = a * b;
	if (v == nullptr) {
		msg = gcnew Message(Message::State::ERROR, "The matrix and vector cannot perform multiplication due to the mismatch of the row size and rank");
	}

	return v;
}