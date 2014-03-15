#pragma once
#include "MathObject.h"

namespace em {
	namespace math {
		using System::String;
		
		ref class Scalar : public MathObject {
		public:
			
			static String^ const tag = "Scalar";

			property double doubleValue {
				double get() {
					return value;
				}
			}

		private:
			double value;

		public:
			Scalar(double v);
			Scalar(Scalar^ scl);
			virtual ~Scalar();

			virtual String^ ToString() override;
			virtual void negate() override;

			Scalar^ overrideAssign(Scalar^ scl);

			operator double();
			
			static bool scalarCast(MathObject^ mo, Scalar^% scl);
		};
	}
}
