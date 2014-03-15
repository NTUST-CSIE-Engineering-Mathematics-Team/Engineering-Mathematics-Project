#pragma once
#include "Expression.h"

namespace em {
	namespace math {
		namespace engine {
			ref class BinaryOperator abstract : public Expression {

			public:
				property String^ operatorSymbol {
					String^ get() {
						return this->symbol;
					}
				}

			protected:
				Expression^ opndA;
				Expression^ opndB;
				
			private:
				String^ const symbol;

			public:
				property int priority {
					virtual int get() abstract;
				}

				BinaryOperator(String^ symbol);
				virtual ~BinaryOperator();

				virtual void setOperands(Expression^ opndA, Expression^ opndB);

				virtual MathObject^ compute() override;

			protected:
				virtual MathObject^ calculate(MathObject^ a, MathObject^ b) abstract;
			};

		}
	}
}