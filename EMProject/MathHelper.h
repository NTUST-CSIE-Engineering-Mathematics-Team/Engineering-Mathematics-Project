#pragma once
#include "All_Math.h"
#include <limits>

namespace em {
	namespace math {

		using System::Math;
		using System::Type;
		interface class MathHelper {
		public:
			static double EPSILON = std::numeric_limits<float>::epsilon();
			
			generic<typename M> where M : MathObject
			static String^ getGenericMathID();

			generic<typename M> where M : MathObject
			static String^ getGenericMathType();
		};

	}
}
