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
					using System::Collections::Generic::Dictionary;

					ref class Function : public Expression {
					public:
						delegate MathObject^ FunctionPerformer(array<MathObject^>^ mos, Message^% msg);

						property String^ functionName {
							String^ get() {
								return this->name;
							}
						}

						
					private:
						const bool negative;
						array<Expression^>^ args;
						String^ const name;
						Dictionary<String^, FunctionPerformer^>^ overloadsMap;

					public:
						Function(bool negative, array<Expression^>^ exps, String^ name, Dictionary<String^, FunctionPerformer^>^ performers);

						virtual ~Function();
						
						virtual MathObject^ compute(Message^% message);
					
					};

				}
			}
		}
	}
}