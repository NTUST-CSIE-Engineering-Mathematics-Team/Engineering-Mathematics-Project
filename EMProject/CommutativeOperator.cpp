#include "CommutativeOperator.h"

using namespace em::math::engine::expression::operators;
CommutativeOperator::CommutativeOperator(String^ symbol, Expression^ opndA, Expression^ opndB) : BinaryOperator(symbol, opndA, opndB) {
}


CommutativeOperator::~CommutativeOperator() {
}

generic<typename A, typename B> where A:MathObject where B : MathObject
void CommutativeOperator::addCommutativeOperation(String^ types, Operation<A, B>^ operation) {

	this->addOperation<A, B>(types, operation);

	if (types[0] != types[1]) {
		this->addOperation<B, A>(String::Concat(types[1], types[0]), gcnew Operation<B, A>(this, &CommutativeOperator::OperandSwaper<B, A>));
	}
}

generic<typename A, typename B> where A : MathObject where B : MathObject
MathObject^ CommutativeOperator::OperandSwaper(A opndA, B opndB, Message^% msg) {
	return this->castInvoke(String::Concat(opndB->mathType[0], opndA->mathType[0]), opndB, opndA, msg);
}
