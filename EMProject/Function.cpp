#include "Function.h"

using namespace em::math::engine::expression::functions;

Function::Function(bool negative, array<Expression^>^ exps, String^ name, int argN) : negative(negative), args(exps), name(name), argCount(argN) {
}


Function::~Function() {
	delete this->args;
	this->args = nullptr;
}

bool Function::isArgsNumCorrect() {
	return this->args->Length == this->argCount;
}

MathObject^ Function::compute(Message^% message) {

	if (!isArgsNumCorrect()) {
		return nullptr;
	}

	array<MathObject^>^ mos = gcnew array<MathObject^>(this->args->Length);
	for (int i = 0; i < mos->Length; i++) {
		mos[i] = args[i]->compute(message);
		if (mos[i] == nullptr) {
			return nullptr;
		}
	}

	MathObject^ mo = this->performFunction(mos);
	return this->negative? (-mo) : mo;
	
}