#pragma once
#include "Expression.h"
#include "Message.h"

namespace em {
	namespace math {
		namespace engine {
			namespace expression {
				namespace operators {
					using namespace em::math;
					using em::intrprt::Message;
					using em::math::engine::expression::Expression;
					using System::String;
					
					ref class BinaryOperator abstract : public Expression {
					public:
						delegate BinaryOperator^ OperatorConstructor(Expression^ opndA, Expression^ opndB);

					public:
						property String^ operatorSymbol {
							String^ get() {
								return this->symbol;
							}
						}

					private:
						String^ const symbol;
						Expression^ opndA;
						Expression^ opndB;

					public:
						
						BinaryOperator(String^ symbol, Expression^ opndA, Expression^ opndB);
						virtual ~BinaryOperator();

						virtual MathObject^ compute(Message^% message);
						

					protected:
						virtual MathObject^ calculate(MathObject^ a, MathObject^ b, Message^% message) abstract;
					};

				}
			}
		}
	}
}