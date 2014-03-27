#pragma once
#include "Function.h"

namespace em {
	namespace math {
		namespace engine {
			namespace expression {
				namespace functions {
					using System::Collections::Generic::Dictionary;


					ref class FunctionFactory abstract {
					

					private:
						static Dictionary<String^, Dictionary<String^, Function::FunctionPerformer^>^>^ const functionConstructors = gcnew Dictionary<String^, Dictionary<String^, Function::FunctionPerformer^>^>();
							
					public:
						
						static void addFunction(Function::FunctionPerformer^ performer);

						static bool hasFunction(String^ name);
						static Function^ createFunctionInstance(String^ name, bool negative, array<Expression^>^ exps);
						~FunctionFactory();

					private:
						FunctionFactory();
						
					};
				}
			}
		}
	}
}

