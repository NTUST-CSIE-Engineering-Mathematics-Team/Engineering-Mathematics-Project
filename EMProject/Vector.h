#pragma once
#include "MathObject.h"
#include "Scalar.h"

namespace em {
	namespace math {
		using System::String;
		using System::Text::StringBuilder;

		ref class Vector : public MathObject {

		public:
			
			static String^ const TAG = "Vector";
			static String^  const ID = "V";

			property MathObject^ clone{
				virtual MathObject^ get() override {
					return gcnew Vector(this);
				}
			}

			property double default[int] {
				double get(int i) {
					return this->value[i];
				}
				void set(int i, double v) {
					this->value[i] = v;
				}
			}

			property Vector^ normalized{
				Vector^ get() {
					return this / gcnew Scalar(this->magnitude);
				}
			}

			property double magnitude {
				double get() {
					double s = 0;
					for (int i = 0; i < this->rank; i++) {
						s += this[i] * this[i];
					}
					return System::Math::Sqrt(s);
				}
			}

			property int rank {
				int get() {
					return this->value->Length;
				}
			}

		private:
			
			array<double>^ value;

		public:
			Vector(int dim);
			Vector(Vector^ vec);
			virtual ~Vector();

			virtual String^ ToString() override;
			virtual MathObject^ operator-() override;

			Vector^ fitAssign(Vector^ vec);

			virtual MathObject^ overrideAssign(MathObject^ mo) override;
			Vector^ overrideAssign(Vector^ vec);
			
			virtual Vector^ operator-(Vector^ v);
			virtual Vector^ operator+(Vector^ v);
			virtual Vector^ operator*(Scalar^ s);
			virtual Scalar^ operator*(Vector^ v);
			virtual Vector^ operator/(Scalar^ s);
			virtual Vector^ cross(Vector^ v);
			virtual Scalar^ component(Vector^ v);
			virtual Vector^ projection(Vector^ v);
			
			static bool isSameRank(Vector^ a, Vector^ b);
			static bool vectorCast(MathObject^ mo, Vector^% vec);
			static int getWiderRank(Vector^ a, Vector^ b);
			static void widerConvert(Vector^% a, Vector^% b);
			
		};
	}
	
}

