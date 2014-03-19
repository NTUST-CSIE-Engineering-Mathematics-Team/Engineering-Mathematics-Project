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
						static MathObject^ SS(Scalar^ a, Scalar^ b, Message^% msg);
						static MathObject^ VV(Vector^ a, Vector^ b, Message^% msg);
						static MathObject^ MM(Matrix^ a, Matrix^ b, Message^% msg);
					};
				}
			}
		}
	}
}


