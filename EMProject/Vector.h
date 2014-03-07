#pragma once
#include "MathObject.h"

namespace em {
	namespace math {

		using System::String;
		using System::Text::StringBuilder;

		ref class Vector : public MathObject {
		private: array<double>^ value;

		public:
			property double default[int] {
				double get(int i) {
					return this->value[i];
				}
				void set(int i, double v) {
					this->value[i] = v;
				}
			}
			Vector(int dim);
			virtual ~Vector();
			virtual String^ toString() override;
		};
	}
	
}

