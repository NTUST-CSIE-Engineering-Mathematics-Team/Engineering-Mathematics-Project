#pragma once
#include "BinaryOperator.h"

namespace em {
	namespace math {
		namespace engine {
			namespace expression {
				namespace operators {
					using System::Collections::Generic::Dictionary;

					ref class OperatorFactory abstract{
					private:
						delegate BinaryOperator^ ConcreteOperator(Expression^ a, Expression^ b);

					private:
						static Dictionary<String^, ConcreteOperator^>^ const operatorConstructors = gcnew Dictionary<String^, ConcreteOperator^>();

					public:
						template<typename O>
						static void addOperation() {
							O^ tmpO = gcnew O(nullptr, nullptr);
							operatorConstructors->Add(tmpO->operatorSymbol, gcnew ConcreteOperator(concreteOperation<O>));
							delete tmpO;
						}

						static BinaryOperator^ createOperatorInstance(String^ symbol, Expression^ a, Expression^ b);
						virtual ~OperatorFactory();

					private:
						OperatorFactory();

						template<typename O>
						static BinaryOperator^ concreteOperation(Expression^ a, Expression^ b) {
							return gcnew O(a, b);
						}
					};
				}
			}
		}
	}
}

