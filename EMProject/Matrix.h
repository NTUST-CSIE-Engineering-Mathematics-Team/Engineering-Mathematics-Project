#pragma once
#include "MathObject.h"
#include "Vector.h"
#include "Scalar.h"

namespace em {
	namespace math {
		using System::String;
		using System::Text::StringBuilder;

		ref class Matrix : public MathObject {

		public:
			enum class VectorOption { ROW, COLUMN };

			static String^ const tag = "Matrix";
			

			property double default[int, int] {
				double get(int i, int j) {
					return this->value[i, j];
				}
				void set(int i, int j, double v) {
					this->value[i, j] = v;
				}
			}

			property Vector^ default[VectorOption, int] {
				Vector^ get(VectorOption vo, int i);
				void set(VectorOption vo, int i, Vector^ vec);
			}

			property int rowLength {
				int get() {
					return this->value->GetLength(1);
				}
			}

			property int columnLength {
				int get() {
					return this->value->GetLength(0);
				}
			}

		private: 
			array<double, 2>^ value;
		
		public:
			Matrix(int dim1, int dim2);
			Matrix(Matrix^ mat);
			virtual ~Matrix();

			virtual String^ ToString() override;
			virtual MathObject^ operator-() override;

			Matrix^ fitAssign(Matrix^ mat);
			virtual Matrix^ overrideAssign(Matrix^ mat);

			Matrix^ operator-(Matrix^ m);
			Matrix^ operator+(Matrix^ m);
			Matrix^ operator*(Matrix^ m);
			Vector^ operator*(Vector^ v);
			Matrix^ operator*(Scalar^ s);
			Matrix^ operator/(Scalar^ s);

			bool isSameSize(Matrix^ m);
			static bool matrixCast(MathObject^ mo, Matrix^% mat);
		};
	}
}

