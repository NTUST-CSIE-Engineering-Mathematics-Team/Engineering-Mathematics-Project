#pragma once
#include "Expression.h"
#include "Message.h"

namespace em {
	namespace math {
		namespace engine {
			namespace expression {
				namespace operators {
					using em::math::MathObject;
					using em::intrprt::Message;

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
						property int priority {
							virtual int get() abstract;
						}

						BinaryOperator(String^ symbol, Expression^ opndA, Expression^ opndB);
						virtual ~BinaryOperator();

						virtual MathObject^ compute(Message^% message) override;
						

					protected:
						virtual MathObject^ calculate(MathObject^ a, MathObject^ b) abstract;
					};

				}
			}
		}
	}
}