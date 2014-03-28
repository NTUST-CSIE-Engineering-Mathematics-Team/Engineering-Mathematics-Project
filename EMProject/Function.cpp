#include "Function.h"

using namespace em::math::engine::expression::functions;
using System::Text::StringBuilder;
Function::Function(bool negative, array<Expression^>^ exps, String^ name, Dictionary<String^, FunctionPerformer^>^ performers)
	: negative(negative), args(exps), name(name), performers(performers) {
}


Function::~Function() {
	delete this->args;
	this->args = nullptr;
}


MathObject^ Function::compute(Message^% message) {
	StringBuilder^ fullFunctionNameBuilder = gcnew StringBuilder(this->functionName);
	StringBuilder^ argTs = gcnew StringBuilder();

	array<MathObject^>^ mos = gcnew array<MathObject^>(this->args->Length);
	int i;
	for (i = 0; i < mos->Length; i++) {
		mos[i] = args[i]->compute(message);
		if (mos[i] == nullptr) {
			return nullptr;
		}
		argTs->AppendFormat("{0}_", mos[i]->mathID);
	}
	
	if (i > 0) {
		fullFunctionNameBuilder->Append("$");
		fullFunctionNameBuilder->Append(argTs->ToString(), 0, argTs->Length - 1);
	}

	String^ fullFunctionName = fullFunctionNameBuilder->ToString();
	if (!this->performers->ContainsKey(fullFunctionName)) {
		message = gcnew Message(Message::State::ERROR, "Incorrect argument types in functoin \"" + this->functionName + "\"");
		return nullptr;
	}

	MathObject^ mo = this->performers[fullFunctionName](mos, message);
	if (mo == nullptr) {
		return nullptr;
	}

	return this->negative? (-mo) : mo;
	
}


