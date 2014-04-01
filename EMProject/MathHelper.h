#pragma once
#include "All_Math.h"
#include <limits>

namespace em {
	namespace math {

		using System::Math;
		interface class MathHelper{
			static double EPSILON = std::numeric_limits<float>::epsilon();

			static double degreeToRadian(Scalar^ d);
			static Scalar^ radianToDegree(double r);
		};

	}
}
