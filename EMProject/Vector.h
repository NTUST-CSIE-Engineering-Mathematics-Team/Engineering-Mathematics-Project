#pragma once
#include "MathObject.h"

namespace em {
	namespace math {

		using System::String;
		using System::Text::StringBuilder;

		ref class Vector : public MathObject {
		private: array<double>^ value;

		public:
			static property String^ tag {
				String^ get() {
					return "Vector";
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

			property int rank{
				int get() {
					return this->value->Length;
				}
			}
			Vector(int dim);
			virtual ~Vector();

			Vector^ operator=(Vector^ vec);

			virtual String^ toString() override;
		};
	}
	
}

