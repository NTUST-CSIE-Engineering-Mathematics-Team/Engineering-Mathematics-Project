#pragma once
#include "MathObject.h"

namespace em {
	namespace math {
		namespace engine {

			using em::math::MathObject;
			interface class Expression {
			public:
				
				virtual MathObject^ compute() abstract;
			};

		}
	}
}