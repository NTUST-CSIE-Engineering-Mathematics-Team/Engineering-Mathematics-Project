#pragma once
#include "MathObject.h"
#include "Message.h"

namespace em {
	namespace math {
		namespace engine {
			namespace expression {
				using em::math::MathObject;
				using em::intrprt::Message;

				interface class Expression {
				public:
					virtual MathObject^ compute(Message^% message) abstract;
				};

			}
		}
	}
}