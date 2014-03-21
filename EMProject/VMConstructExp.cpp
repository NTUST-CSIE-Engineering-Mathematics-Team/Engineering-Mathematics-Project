#include "VMConstructExp.h"

using namespace em::math::engine::expression;

VMConstructExp::VMConstructExp(bool negative, array<array<Expression^>^>^ content) : negative(negative), content(content) {
}


VMConstructExp::~VMConstructExp() {
	this->content = nullptr;
}

MathObject^ VMConstructExp::compute(Message^% message) {
	Scalar^ scl;
	if (content->Length == 1) {
		Vector^ v = gcnew Vector(content[0]->Length);
		
		for (int i = 0; i < v->rank; i++) {
			
			if (!Scalar::scalarCast(content[0][i]->compute(message), scl)) {
				if (message == nullptr) {
					message = gcnew Message(Message::State::ERROR, "Cannot initialize a vector with a non-scalar value");
				}

				return nullptr;
			}
			
			v[i] = this->negative ? -(double)scl : (double)scl;
		}

		return v;
	} else {
		Matrix^ m = gcnew Matrix(content->Length, content[0]->Length);
		for (int i = 0; i < m->columnLength; i++) {
			for (int j = 0; j < m->rowLength; j++) {

				if (!Scalar::scalarCast(content[i][j]->compute(message), scl)) {
					if (message == nullptr) {
						message = gcnew Message(Message::State::ERROR, "Cannot initialize a matrix with a non-scalar value");
					}

					return nullptr;
				}

				m[i, j] = this->negative ? -(double)scl : (double)scl;
			}
		}

		return m;
	}

}