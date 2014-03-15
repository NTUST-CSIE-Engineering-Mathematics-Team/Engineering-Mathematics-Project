#pragma once
#include "MathObject.h"

namespace em {
	namespace math {
		using System::String;
		using System::Text::StringBuilder;

		ref class Vector : public MathObject {

		public:
			
			static String^ const tag = "Vector";
			
			property double default[int] {
				double get(int i) {
					return this->value[i];
				}
				void set(int i, double v) {
					this->value[i] = v;
				}
			}

			property int rank{
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
			virtual void negate() override;

			Vector^ fitAssign(Vector^ vec);
			Vector^ overrideAssign(Vector^ vec);
			

			static bool vectorCast(MathObject^ mo, Vector^% vec);
		};
	}
	
}

