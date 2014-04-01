#include "CommutativeOperator.h"

using namespace em::math::engine::expression::operators;
CommutativeOperator::CommutativeOperator(wchar_t symbol, Expression^ opndA, Expression^ opndB) : BinaryOperator(symbol, opndA, opndB) {
}


CommutativeOperator::~CommutativeOperator() {
}

generic<typename A, typename B> where A:MathObject where B : MathObject
void CommutativeOperator::addCommutativeOperation(String^ types, Operation<A, B>^ operation) {

	this->addOperation<A, B>(types, operation);
	array<String^>^ typeA = types->Split(L'_');
	if (!typeA[0]->Equals(typeA[1])) {
		this->addOperation<B, A>(String::Concat(typeA[1], "_", typeA[0]), gcnew Operation<B, A>(this, &CommutativeOperator::OperandSwaper<B, A>));
	}
}

generic<typename A, typename B> where A:MathObject where B : MathObject
void CommutativeOperator::addCommutativeOperation(Operation<A, B>^ operation) {
	this->addCommutativeOperation(operation->Method->Name, operation);
}

generic<typename A, typename B> where A : MathObject where B : MathObject
MathObject^ CommutativeOperator::OperandSwaper(A opndA, B opndB, Message^% msg) {
	return this->castInvoke(String::Concat(opndB->mathID, "_", opndA->mathID), opndB, opndA, msg);
}
