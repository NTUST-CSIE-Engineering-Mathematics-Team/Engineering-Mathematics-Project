#pragma once
#include "BinaryOperator.h"
#include "All_Math.h"

namespace em {
	namespace math {
		namespace engine {
			namespace expression {
				namespace operators {
					ref class SubtractionOperator : public BinaryOperator {
					public:
						SubtractionOperator(Expression^ a, Expression^ b);
						virtual ~SubtractionOperator();

					private:
						static MathObject^ S_S(Scalar^ a, Scalar^ b, Message^% msg);
						static MathObject^ V_V(Vector^ a, Vector^ b, Message^% msg);
						static MathObject^ M_M(Matrix^ a, Matrix^ b, Message^% msg);
						static MathObject^ A_A(Angle^ a, Angle^ b, Message^% msg);
					};
				}
			}
		}
	}
}


