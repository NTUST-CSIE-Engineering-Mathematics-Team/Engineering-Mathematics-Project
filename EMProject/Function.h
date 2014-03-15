#pragma once
#include "Expression.h"

namespace em {
	namespace math {
		namespace engine {

			ref class Function abstract : public Expression {
			private:
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
				virtual bool setArgs(array<Expression^>^ exps);
				virtual MathObject^ compute() override;

			protected:
				Function(String^ name, int argN);
				
				virtual MathObject^ performFunction(array<MathObject^>^ mos) abstract;
			};

		}
	}
}