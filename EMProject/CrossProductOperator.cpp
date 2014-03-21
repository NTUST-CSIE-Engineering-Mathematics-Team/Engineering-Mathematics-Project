#include "CrossProductOperator.h"

using namespace em::math::engine::expression::operators;

CrossProductOperator::CrossProductOperator(Expression^ a, Expression^ b) : BinaryOperator("x", a, b) {
	this->addOperation<Vector^, Vector^>(gcnew Operation<Vector^, Vector^>(V_V));
}


CrossProductOperator::~CrossProductOperator() {
}

MathObject^ CrossProductOperator::V_V(Vector^ a, Vector^ b, Message^% msg) {
	Vector^ v = a->cross(b);
	if (v == nullptr) {
		msg = gcnew Message(Message::State::ERROR, "The ranks of vectors is invaild, it cannot be more than 3 or they have different ranks");
	}

	return v;
}


