#pragma once
#include "Expression.h"
#include"All_Math.h"

namespace em {
	namespace math {
		namespace engine {
			namespace expression {
				using namespace em::math;

				ref class MathObjSetExp : public Expression {
				private:
					const bool negative;
					array<Expression^>^ exps;

				public:
					MathObjSetExp(bool negative, array<Expression^>^ exps);
					virtual ~MathObjSetExp();

					virtual MathObject^ compute(Message^% message);

				};
			}
		}
	}
}

