#pragma once
#include "MathObject.h"
#include "Scalar.h"

namespace em {
	namespace math {
		using System::String;
		using System::Math;
		ref class Angle : public MathObject {

		public:
			static String^ const TAG = "Angle";
			static String^ const ID = "A";

			property double degree {
				double get() {
					return this->radian * 180 / Math::PI;
				}
			}

			property double radian {
				double get() {
					return this->rAngle;
				}
			}

			property Angle^ clone{
				Angle^ get() {
					return gcnew Angle(this);
				}
			}
		private:
			static const double RD_RATIO = Math::PI / 180;
			double rAngle;

		public:
			Angle(double radian);
			Angle(double radian, bool isDegree);
			Angle(Scalar^ degree);
			Angle(Angle^ angle);

			virtual ~Angle();

			virtual String^ getHeader() override;
			virtual String^ ToString() override;

			virtual MathObject^ operator-() override;
			virtual MathObject^ overrideAssign(MathObject^ mo) override;

			Angle^ overrideAssign(Angle^ angle);
			Angle^ overrideAssign(Scalar^ degree);
			Angle^ overrideAssign(double radian);

			virtual Angle^ operator-(Angle^ a);
			virtual Angle^ operator+(Angle^ a);
			virtual Angle^ operator*(Scalar^ s);
			virtual Angle^ operator/(Scalar^ s);

			operator double();

			static bool angleCast(MathObject^ mo, Angle^% angle);
		};

	}
}

