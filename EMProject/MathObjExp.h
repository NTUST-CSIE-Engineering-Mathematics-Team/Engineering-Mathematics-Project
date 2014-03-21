#pragma once
#include "Expression.h"
#include "Message.h"

namespace em {
	namespace math {
		namespace engine {
			namespace expression {
				using em::math::MathObject;
				using em::intrprt::Message;

				ref class MathObjExp : public Expression {
				private:
					MathObject^ mo;

				public:
					MathObjExp(bool negative, MathObject^ mo);
					virtual ~MathObjExp();

					virtual MathObject^ compute(Message^% message);
				};

			}
		}
	}
}