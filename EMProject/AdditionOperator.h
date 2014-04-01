#pragma once
#include "CommutativeOperator.h"
#include "All_Math.h"

namespace em {
	namespace math {
		namespace engine {
			namespace expression {
				namespace operators {
					
					ref class AdditionOperator : public CommutativeOperator {
					public:
						AdditionOperator(Expression^ a, Expression^ b);
						virtual ~AdditionOperator();
						
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
