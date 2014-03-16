#pragma once
#include "Expression.h"
#include "Message.h"

namespace em {
	namespace math {
		namespace engine {
			namespace expression {
				namespace functions {
					using em::math::MathObject;
					using em::intrprt::Message;
					using em::math::engine::expression::Expression;
					using System::String;

					ref class Function abstract : public Expression {
					public:
						delegate Function^ FunctionConstructor(array<Expression^>^ exps);

					private:
						const bool negative;
						array<Expression^>^ args;
						String^ const name;
						const int argCount;
						
					public:
						property String^ functionName {
							String^ get() {
								return this->name;
							}
						}

						virtual ~Function();
						
						virtual MathObject^ compute(Message^% message);
						virtual bool isArgsNumCorrect();
					protected:
						Function(bool negative, array<Expression^>^ exps, String^ name, int argN);

						virtual MathObject^ performFunction(array<MathObject^>^ mos) abstract;
					};

				}
			}
		}
	}
}