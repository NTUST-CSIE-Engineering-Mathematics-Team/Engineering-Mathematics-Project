#pragma once
#include "MathObject.h"
namespace em {
	namespace math {
		ref class Matrix : public MathObject {
		private: array<double, 2>^ values;
		public:
			Matrix(int dim1, int dim2);
			virtual ~Matrix();
		};
	}
}

