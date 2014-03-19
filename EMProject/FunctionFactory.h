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
						delegate Function^ ConcreteFunction(bool negative, array<Expression^>^ exps);

					private:
						static Dictionary<String^, ConcreteFunction^>^ const functionConstructors = gcnew Dictionary<String^, ConcreteFunction^>();
							
					public:
						template<typename F>
						static void addFunction(String^ name) {
							functionConstructors->Add(name, gcnew ConcreteFunction(concreteFunction<F>));
						}

						static bool hasFunction(String^ name);
						static Function^ createFunctionInstance(String^ name, bool negative, array<Expression^>^ exps);
						~FunctionFactory();
					private:
						FunctionFactory();

						template<typename F>
						static Function^ concreteFunction(bool negative, array<Expression^>^ exps) {
							return gcnew F(negative, exps);
						}
					};
				}
			}
		}
	}
}
