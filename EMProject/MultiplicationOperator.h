#pragma once
#include "CommutativeOperator.h"
#include "All_Math.h"

namespace em {
	namespace math {
		namespace engine {
			namespace expression {
				namespace operators {
					ref class MultiplicationOperator : public CommutativeOperator {
					public:
						MultiplicationOperator(Expression^ a, Expression^ b);
						virtual ~MultiplicationOperator();
						
					private:
						static MathObject^ S_S(Scalar^ a, Scalar^ b, Message^% msg);
						static MathObject^ V_V(Vector^ a, Vector^ b, Message^% msg);
						static MathObject^ M_M(Matrix^ a, Matrix^ b, Message^% msg);
						static MathObject^ S_V(Scalar^ a, Vector^ b, Message^% msg);
						static MathObject^ S_M(Scalar^ a, Matrix^ b, Message^% msg);
						static MathObject^ M_V(Matrix^ a, Vector^ b, Message^% msg);
						static MathObject^ V_M(Vector^ a, Matrix^ b, Message^% msg);
						static MathObject^ S_A(Scalar^ a, Angle^ b, Message^% msg);
					};
				}
			}
		}
	}
}