#pragma once
#include "Function.h"
#include "all_Math.h"

namespace em {
	namespace math {
		namespace engine {
			namespace expression {
				namespace functions {
					ref class NormalizationFunction : public Function {
					public:
						NormalizationFunction(bool negative, array<Expression^>^ exps);
						virtual ~NormalizationFunction();

						virtual MathObject^ performFunction(array<MathObject^>^ mos) override;
					};
				}
			}
		}
	}
}
