#pragma once
#include "Expression.h"
#include "Message.h"

namespace em {
	namespace math {
		namespace engine {
			namespace expression {
				using em::math::MathObject;
				using em::intrprt::Message;

				ref class SimpleMathObjExp : public Expression {
				private:
					MathObject^ mo;

				public:
					SimpleMathObjExp(bool negative, MathObject^ mo);
					virtual ~SimpleMathObjExp();

					virtual MathObject^ compute(Message^% message);
				};

			}
		}
	}
}