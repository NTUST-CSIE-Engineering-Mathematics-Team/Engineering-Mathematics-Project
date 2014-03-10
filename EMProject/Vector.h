#pragma once
#include "MathObject.h"

namespace em {
	namespace math {
		using System::String;
		using System::Text::StringBuilder;

		ref class Vector : public MathObject {

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

		private: 
			array<double>^ value;

		public:
			Vector(int dim);
			virtual ~Vector();

			virtual String^ ToString() override;

			Vector^ operator=(Vector^ vec);
		};
	}
	
}

