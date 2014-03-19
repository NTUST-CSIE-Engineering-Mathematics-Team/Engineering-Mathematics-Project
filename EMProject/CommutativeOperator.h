#pragma once
#include "BinaryOperator.h"

namespace em {
	namespace math {
		namespace engine {
			namespace expression {
				namespace operators {

					ref class CommutativeOperator abstract : public BinaryOperator {
					public:
						CommutativeOperator(String^ symbol, Expression^ opndA, Expression^ opndB);
						virtual ~CommutativeOperator();

						generic<typename A, typename B> where A:MathObject where B : MathObject
						virtual void addCommutativeOperation(String^ types, Operation<A, B>^ operation);
						generic<typename A, typename B> where A:MathObject where B : MathObject
						virtual void addCommutativeOperation(Operation<A, B>^ operation);

					private:
						generic<typename A, typename B> where A : MathObject where B : MathObject
						virtual MathObject^ OperandSwaper(A opndA, B opndB, Message^% msg) sealed;
					};
				}
			}
		}
	}
}
