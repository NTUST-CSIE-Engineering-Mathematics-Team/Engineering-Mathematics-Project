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
						static MathObject^ SS(Scalar^ a, Scalar^ b, Message^% msg);
						static MathObject^ VV(Vector^ a, Vector^ b, Message^% msg);
						static MathObject^ MM(Matrix^ a, Matrix^ b, Message^% msg);
						static MathObject^ SV(Scalar^ a, Vector^ b, Message^% msg);
						static MathObject^ SM(Scalar^ a, Matrix^ b, Message^% msg);
						static MathObject^ MV(Matrix^ a, Vector^ b, Message^% msg);
					};
				}
			}
		}
	}
}