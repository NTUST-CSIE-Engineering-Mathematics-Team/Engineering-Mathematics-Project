#pragma once
#include "MathObject.h"

namespace em {
	namespace math {
		using System::String;
		
		ref class Scalar : public MathObject {
		public:
			
			static String^ const TAG = "Scalar";
			static String^  const ID = "S";

			property MathObject^ clone{
				virtual MathObject^ get() override {
					return gcnew Scalar(this);
				}
			}

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
			virtual MathObject^ operator-() override;

			virtual Scalar^ operator-(Scalar^ s);
			virtual Scalar^ operator+(Scalar^ s);
			virtual Scalar^ operator*(Scalar^ s);
			virtual Scalar^ operator/(Scalar^ s);
			
			virtual Scalar^ overrideAssign(Scalar^ scl);
			
			virtual operator double();
			
			static bool scalarCast(MathObject^ mo, Scalar^% scl);
		};
	}
}
