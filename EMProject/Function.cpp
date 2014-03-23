#include "Function.h"

using namespace em::math::engine::expression::functions;

Function::Function(bool negative, array<Expression^>^ exps, String^ name, array<String^>^ argTs, FunctionPerformer^ performer)
	: negative(negative), args(exps), name(name), argTs(argTs), performer(performer) {
}


Function::~Function() {
	delete this->args;
	this->args = nullptr;
}

bool Function::isArgsNumCorrect() {
	return this->args->Length == this->argTs->Length;
}

MathObject^ Function::compute(Message^% message) {

	array<MathObject^>^ mos = gcnew array<MathObject^>(this->args->Length);
	int i;
	for (i = 0; i < mos->Length; i++) {
		mos[i] = args[i]->compute(message);
		if (mos[i] == nullptr || !mos[i]->mathID->Equals(argTs[i])) {
			
			if (message == nullptr) {
				message = gcnew Message(Message::State::ERROR, "Incorrect argument types in functoin \"" + this->functionName + "\"");
			}
			return nullptr;
		}
	}
	

	MathObject^ mo = this->performer(mos, message);
	if (mo == nullptr) {
		return nullptr;
	}

	return this->negative? (-mo) : mo;
	
}


