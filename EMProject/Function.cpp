#include "Function.h"

using namespace em::math::engine;

Function::Function(String^ name, int argN) : name(name), argCount(argN) {
}


Function::~Function() {
}

bool Function::setArgs(array<Expression^>^ exps) {
	if (this->argCount != exps->Length) {
		return false;
	}
	this->args = exps;
	return true;
}

MathObject^ Function::compute() {
	array<MathObject^>^ mos = gcnew array<MathObject^>(this->args->Length);
	for (int i = 0; i < mos->Length; i++) {
		mos[i] = args[i]->compute();
	}
	
	this->args = nullptr;

	return this->performFunction(mos);

	
}