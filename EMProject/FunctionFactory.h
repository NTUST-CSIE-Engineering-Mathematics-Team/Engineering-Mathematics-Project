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
						ref class FunctionData {
						public:
							String^ const name;
							String^ const argT;
							Function::FunctionPerformer^ const performer;

						public:
							FunctionData(String^ name, String^ argT, Function::FunctionPerformer^ performer);
							~FunctionData();
						};

					private:
						static Dictionary<String^, FunctionData^>^ const functionConstructors = gcnew Dictionary<String^, FunctionData^>();
							
					public:
						
						static void addFunction(Function::FunctionPerformer^ performer) {

							array<String^>^ nameAndTypes = performer->Method->Name->Split('$');
							functionConstructors->Add(nameAndTypes[0], gcnew FunctionData(nameAndTypes[0], nameAndTypes[1], performer));
						}

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

