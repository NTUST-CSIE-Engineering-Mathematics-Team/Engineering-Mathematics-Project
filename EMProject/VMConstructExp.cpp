#include "VMConstructExp.h"

using namespace em::math::engine::expression;
using System::Collections::Generic::LinkedList;
VMConstructExp::VMConstructExp(bool negative, array<array<Expression^>^>^ content) : negative(negative), content(content) {
}


VMConstructExp::~VMConstructExp() {
	this->content = nullptr;
}

MathObject^ VMConstructExp::compute(Message^% message) {
	Scalar^ scl;
	if (content->Length == 1) {
		Vector^ v = gcnew Vector(content[0]->Length);
		
		for (int i = 0; i < v->dimension; i++) {
			
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
		Vector^ vec;
		MathObject^ mo;
		LinkedList<double>^ initList = gcnew LinkedList<double>();
		for (int i = 0; i < content[0]->Length; i++) {

			mo = content[0][i]->compute(message);

			if (Scalar::scalarCast(mo, scl)) {
				initList->AddLast(scl);
			} else if (Vector::vectorCast(mo, vec)) {
				for (int j = 0; j < vec->dimension; j++) {
					initList->AddLast(vec[j]);
				}
			} else {
				if (message == nullptr) {
					message = INIT_MAT_ERR_MSG;
				}

				return nullptr;
			}
		}

		Matrix^ m = gcnew Matrix(content->Length, initList->Count);
		int i = 0;
		for each(double scl in initList) {
			m[0, i++] = this->negative ? -scl : scl;
		}

		delete initList;
			
		int rowI;
		for (i = 1; i < content->Length; i++) {
			rowI = 0;
			for (int j = 0; j < content[i]->Length; j++) {
				
				mo = content[i][j]->compute(message);

				if (Scalar::scalarCast(mo, scl)) {
					if (rowI >= m->rowLength) {
						message = OUT_OF_BOUNDS_MSG;
						return nullptr;
					}

					m[i, rowI] = this->negative ? -(double)scl : scl;
					rowI++;

				} else if (Vector::vectorCast(mo, vec)) {
					if ((rowI + vec->dimension) > m->rowLength) {
						message = OUT_OF_BOUNDS_MSG;
						return nullptr;
					}

					for (int k = 0; k < vec->dimension; k++, rowI++) {
						m[i, rowI] = this->negative ? -vec[k] : vec[k];
					}

				} else {
					if (message == nullptr) {
						message = INIT_MAT_ERR_MSG;
					}

					return nullptr;
				}

			}
		}

		return m;
	}

}