#pragma once
#include "Function.h"
#include "Vector.h"
#include "Scalar.h"

namespace em {
	namespace math {
		namespace engine {
			namespace expression {
				namespace functions {
					ref class MagFunction : public Function {
					public:
						MagFunction(bool negative, array<Expression^>^ exps);
						virtual ~MagFunction();

						virtual MathObject^ performFunction(array<MathObject^>^ mos) override;
					};
				}
			}
		}
	}
}
