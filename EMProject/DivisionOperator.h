#pragma once
#include "BinaryOperator.h"
#include "All_Math.h"

namespace em {
	namespace math {
		namespace engine {
			namespace expression {
				namespace operators {
					ref class DivisionOperator : public BinaryOperator {
					public:
						DivisionOperator(Expression^ a, Expression^ b);
						virtual ~DivisionOperator();

					private:
						static MathObject^ SS(Scalar^ a, Scalar^ b, Message^% msg);
						static MathObject^ MS(Matrix^ a, Scalar^ b, Message^% msg);
						static MathObject^ VS(Vector^ a, Scalar^ b, Message^% msg);
					};
				}
			}
		}
	}
}
