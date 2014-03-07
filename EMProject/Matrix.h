#pragma once
#include "MathObject.h"
#include "Vector.h"

namespace em {
	namespace math {

		using System::String;
		using System::Text::StringBuilder;

		ref class Matrix : public MathObject {

		private: array<double, 2>^ value;

		public:
			enum class VectorOption {ROW, COLUMN};

			property double default[int, int] {
				double get(int i, int j) {
					return this->value[i, j];
				}
				void set(int i, int j, double v) {
					this->value[i, j] = v;
				}
			}

			/*property Vector^ default[VectorOption, int] {
				Vector^ get(VectorOption vo, int i) {

					gcnew Vector();
					return
				}
				void set(VectorOption vo, int i, Vector^ v) {
					this->value[i, j] = v;
				}
			}*/

			Matrix(int dim1, int dim2);
			virtual ~Matrix();
			virtual String^ toString() override;
		};
	}
}

