#include "MathObjSetExp.h"

using namespace em::math::engine::expression;

MathObjSetExp::MathObjSetExp(bool negative, array<Expression^>^ exps) : negative(negative), exps(exps) {
}


MathObjSetExp::~MathObjSetExp() {
}

MathObject^ MathObjSetExp::compute(Message^% message) {
	int i;
	MathObject^ m0 = this->exps[0]->compute(message);
	if (m0 == nullptr) {
		return nullptr;
	}

	MathObjSet^ ms = MathObjSet::createSpecificSet(m0);
	MathObject^ mObj;

	ms->add(this->negative ? -m0 : m0);
	for (i = 1; i < this->exps->Length; i++) {
		mObj = exps[i]->compute(message);
		if (mObj == nullptr || !ms->add(this->negative ? -mObj : mObj)) {
			if (message == nullptr) {
				message = gcnew Message(Message::State::ERROR, "Cannot construct a set which contain different types");
			}
			delete ms;
			return nullptr;
		}
	}

	return ms;
}


