#pragma once
#include "Expression.h"
#include "Message.h"
#include "All_Math.h"

namespace em {
	namespace math {
		namespace engine {
			namespace expression {
				namespace operators {
					using namespace em::math;
					using em::intrprt::Message;
					using em::math::engine::expression::Expression;
					using System::String;
					using System::Collections::Generic::Dictionary;

					ref class BinaryOperator abstract : public Expression {
					protected:
						generic<typename A, typename B> where A : MathObject where B : MathObject
						delegate MathObject^ Operation(A opndA, B opndB, Message^% msg);

					private:
						interface class CasterInterface {
						public:
							virtual MathObject^ castInvoke(MathObject^ a, MathObject^ b, Message^% message) abstract;
						};

						generic<typename A, typename B> where A : MathObject where B : MathObject
						ref class Caster : public CasterInterface {

						private:
							Operation<A, B>^ operation;

						public:
							Caster(Operation<A, B>^ op);
							~Caster();

							virtual MathObject^ castInvoke(MathObject^ a, MathObject^ b, Message^% message);
						};

					public:
						property String^ operatorSymbol {
							String^ get() {
								return this->symbol;
							}
						}

					private:
						String^ const symbol;
						Expression^ opndA;
						Expression^ opndB;

						Dictionary<String^, CasterInterface^>^ overloadsMap;

					public:
						BinaryOperator(String^ symbol, Expression^ opndA, Expression^ opndB);
						virtual ~BinaryOperator();

						generic<typename A, typename B> where A : MathObject where B : MathObject
						virtual void addOperation(String^ types, Operation<A, B>^ caster);
						generic<typename A, typename B> where A : MathObject where B : MathObject
						virtual void addOperation(Operation<A, B>^ caster);

						virtual MathObject^ compute(Message^% message);

					protected:
						MathObject^ castInvoke(String^ types, MathObject^ a, MathObject^ b, Message^% message);
					
					};

				}
			}
		}
	}
}