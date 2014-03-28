#include "BinaryOperator.h"


using namespace em::math::engine::expression::operators;

BinaryOperator::BinaryOperator(String^ symbol, Expression^ opndA, Expression^ opndB) : symbol(symbol), opndA(opndA), opndB(opndB) {
	this->operationMap = gcnew Dictionary<String^, CasterInterface^>(12);
}

BinaryOperator::~BinaryOperator() {
	delete this->opndA;
	delete this->opndB;
	
}

MathObject^ BinaryOperator::compute(Message^% message) {
	MathObject^ moA = this->opndA->compute(message),^ moB = this->opndB->compute(message);
	
	if (moA == nullptr || moB == nullptr) {
		return nullptr;
	}

	String^ types = String::Concat(moA->mathID, "_", moB->mathID);

	if (!this->operationMap->ContainsKey(types)) {
		message = gcnew Message(Message::State::ERROR, "Wrong arithmetic operation, the operands do not match to this \"" + this->symbol + "\" operator");
		return nullptr;
	}
	
	return this->castInvoke(types, moA, moB, message);
}

MathObject^ BinaryOperator::castInvoke(String^ types, MathObject^ a, MathObject^ b, Message^% message) {
	return this->operationMap[types]->castInvoke(a, b, message);
}

generic<typename A, typename B> where A : MathObject where B : MathObject
void BinaryOperator::addOperation(String^ types, Operation<A, B>^ operation) {
	this->operationMap->Add(types, gcnew Caster<A, B>(operation));
}

generic<typename A, typename B> where A : MathObject where B : MathObject
void BinaryOperator::addOperation(Operation<A, B>^ operation) {
	this->addOperation(operation->Method->Name, operation);
}

generic<typename A, typename B> where A : MathObject where B : MathObject
BinaryOperator::Caster<A, B>::Caster(Operation<A, B>^ op) : operation(op) {
	
}

generic<typename A, typename B> where A : MathObject where B : MathObject
BinaryOperator::Caster<A, B>::~Caster() {
	delete this->operation;
}

generic<typename A, typename B> where A : MathObject where B : MathObject
MathObject^ BinaryOperator::Caster<A, B>::castInvoke(MathObject^ a, MathObject^ b, Message^% message) {
	return this->operation(safe_cast<A>(a), safe_cast<B>(b), message);
}