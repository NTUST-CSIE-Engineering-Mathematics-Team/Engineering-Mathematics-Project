#include "Function.h"

using namespace em::math::engine::expression::functions;

Function::Function(bool negative, array<Expression^>^ exps, String^ name, String^ argT, FunctionPerformer^ performer)
	: negative(negative), args(exps), name(name), argT(argT->Split(L'_')), performer(performer) {
}


Function::~Function() {
	delete this->args;
	this->args = nullptr;
}

bool Function::isArgsNumCorrect() {
	return this->args->Length == this->argT->Length;
}

MathObject^ Function::compute(Message^% message) {

	array<MathObject^>^ mos = gcnew array<MathObject^>(this->args->Length);
	int i;
	for (i = 0; i < mos->Length; i++) {
		mos[i] = args[i]->compute(message);
		if (mos[i] == nullptr || !mos[i]->mathID->Equals(argT[i])) {
			
			if (message == nullptr) {
				message = gcnew Message(Message::State::ERROR, "Incorrect argument types in functoin \"" + this->functionName + "\"");
			}
			return nullptr;
		}
	}
	if (i != this->argT->Length) {
		message = gcnew Message(Message::State::ERROR, "Incorrect argument numbers in functoin \"" + this->functionName + "\".\nIt should be " + argT->Length);
		return nullptr;
	}

	MathObject^ mo = this->performer(mos, message);
	if (mo == nullptr) {
		return nullptr;
	}

	return this->negative? (-mo) : mo;
	
}