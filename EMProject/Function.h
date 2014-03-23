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

					ref class Function : public Expression {
					public:
						delegate MathObject^ FunctionPerformer(array<MathObject^>^ mos, Message^% msg);

						property String^ functionName {
							String^ get() {
								return this->name;
							}
						}

						property array<String^>^ argType {
							array<String^>^ get() {
								return this->argT;
							}
						}
					private:
						const bool negative;
						array<Expression^>^ args;
						String^ const name;
						array<String^>^ const  argT;
						FunctionPerformer^ performer;

					public:
						Function(bool negative, array<Expression^>^ exps, String^ name, String^ argT, FunctionPerformer^ performer);

						virtual ~Function();
						
						virtual MathObject^ compute(Message^% message);
						virtual bool isArgsNumCorrect();
						
					};

				}
			}
		}
	}
}