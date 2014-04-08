#pragma once
#include "All_Math.h"
#include <limits>

namespace em {
	namespace math {

		using System::Math;
		using System::Type;
		interface class MathHelper {
		public:
			static double EPSILON = Math::Pow(10, 4 + Math::Floor(Math::Log10(std::numeric_limits<double>::epsilon())));

			static bool isZero(double v);
			static Scalar^ adjustCosAndSin(Scalar^ scl);
			static Scalar^ factorial(int n);
			generic<typename M> where M : MathObject
			static String^ getGenericMathID();

			generic<typename M> where M : MathObject
			static String^ getGenericMathType();

			
		};

	}
}
