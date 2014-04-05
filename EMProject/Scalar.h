#pragma once
#include "MathObject.h"

namespace em {
	namespace math {
		using System::String;
		
		ref class Scalar : public MathObject {
		public:
			
			static String^ const TAG = "Scalar";
			static String^  const ID = "S";

			property double doubleValue {
				double get() {
					return value;
				}
			}

			property bool isInteger {
				bool get() {
					return System::Math::Truncate(this) == this->value;
				}
			}
		private:
			double value;

		public:
			Scalar(double v);
			Scalar(Scalar^ scl);
			virtual ~Scalar();

			virtual String^ getHeader() override;
			virtual String^ ToString() override;
			virtual MathObject^ operator-() override;

			virtual Scalar^ operator-(Scalar^ s);
			virtual Scalar^ operator+(Scalar^ s);
			virtual Scalar^ operator*(Scalar^ s);
			virtual Scalar^ operator/(Scalar^ s);
			
			virtual MathObject^ overrideAssign(MathObject^ mo) override;
			virtual Scalar^ overrideAssign(Scalar^ scl);
			virtual Scalar^ overrideAssign(double val);

			virtual operator double();
			virtual int toInteger();
			Scalar^ clone();

			static bool scalarCast(MathObject^ mo, Scalar^% scl);
			static bool isDoubleInteger(double scl);
		};
	}
}
