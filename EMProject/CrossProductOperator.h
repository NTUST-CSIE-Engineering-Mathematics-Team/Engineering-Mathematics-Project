#pragma once
#include "BinaryOperator.h"
#include "All_Math.h"

namespace em {
	namespace math {
		namespace engine {
			namespace expression {
				namespace operators {
					ref class CrossProductOperator : public BinaryOperator {
					public:
						CrossProductOperator(Expression^ a, Expression^ b);
						virtual ~CrossProductOperator();

					private:
						static MathObject^ V_V(Vector^ a, Vector^ b, Message^% msg);
					};
				}
			}
		}
	}
}
