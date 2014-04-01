#pragma once
#include "Expression.h"
#include "Vector.h"
#include "Matrix.h"
#include "Message.h"

namespace em {
	namespace math {
		namespace engine {
			namespace expression {
				using namespace em::math;

				ref class VMConstructExp : public Expression {
				private:
					bool const negative;
					array<array<Expression^>^>^ content;
					property static Message^ OUT_OF_BOUNDS_MSG {
						Message^ get() {
							return gcnew Message(Message::State::ERROR, "Cannot initialize a matrix with the row that is out of bounds which is determinated by the first row");
						}
					}

					property static Message^ INIT_MAT_ERR_MSG {
						Message^ get() {
							return gcnew Message(Message::State::ERROR, "Cannot initialize a matrix without scalars or vectors");
						}
					}
				public:
					VMConstructExp(bool negative, array<array<Expression^>^>^ content);
					virtual ~VMConstructExp();

					virtual MathObject^ compute(Message^% message);
				};

			}
		}
	}
}