#pragma once
#include "Function.h"
#include "Vector.h"
#include "Scalar.h"

namespace em {
	namespace math {
		namespace engine {
			namespace expression {
				namespace functions {
					ref class ProjFunction : public Function {
					public:
						ProjFunction(bool negative, array<Expression^>^ exps);
						virtual ~ProjFunction();

						virtual MathObject^ performFunction(array<MathObject^>^ mos) override;
					};
				}
			}
		}
	}
}
