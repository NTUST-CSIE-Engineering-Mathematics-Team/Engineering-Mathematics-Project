#pragma once
#include "Expression.h"
#include "Vector.h"
#include "Matrix.h"
#include "Message.h"

namespace em {
	namespace math {
		namespace engine {
			namespace expression {
				using namespace em::math;

				ref class VMConstructExp : public Expression {
				private:
					bool const negative;
					array<array<Expression^>^>^ content;
				public:
					VMConstructExp(bool negative, array<array<Expression^>^>^ content);
					virtual ~VMConstructExp();

					virtual MathObject^ compute(Message^% message);
				};

			}
		}
	}
}