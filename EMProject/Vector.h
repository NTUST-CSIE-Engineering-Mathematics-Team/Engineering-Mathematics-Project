#pragma once
#include "MathObject.h"

namespace em {
	namespace math {
		public ref class Vector : public MathObject {
		private: array<double>^ values;

		public:
			Vector(int dim);
			virtual ~Vector();
		};
	}
	
}

