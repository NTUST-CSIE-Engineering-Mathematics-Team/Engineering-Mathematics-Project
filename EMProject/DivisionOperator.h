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
						static MathObject^ S_S(Scalar^ a, Scalar^ b, Message^% msg);
						static MathObject^ M_S(Matrix^ a, Scalar^ b, Message^% msg);
						static MathObject^ V_S(Vector^ a, Scalar^ b, Message^% msg);
					};
				}
			}
		}
	}
}
