#pragma once
#include "MathObject.h"
#include "Vector.h"
#include "Scalar.h"

namespace em {
	namespace math {
		using System::String;
		using System::Text::StringBuilder;

		ref class Matrix : public MathObject{

		public:
			enum class VectorOption { ROW, COLUMN };

			static String^ const TAG = "Matrix";
			static String^ const ID = "M";

			property MathObject^ clone{
				virtual MathObject^ get() override {
					return gcnew Matrix(this);
				}
			}

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

			property bool square {
				bool get() {
					return this->rowLength == this->columnLength;
				}
			}
		private: 
			array<double, 2>^ value;
		
		public:
			Matrix(int dim1, int dim2);
			Matrix(Matrix^ mat);
			Matrix(VectorOption op, Vector^ vec);
			virtual ~Matrix();

			virtual String^ ToString() override;
			virtual MathObject^ operator-() override;

			virtual Matrix^ fitAssign(Matrix^ mat);
			virtual Matrix^ overrideAssign(Matrix^ mat);

			virtual Matrix^ operator-(Matrix^ m);
			virtual Matrix^ operator+(Matrix^ m);
			virtual Matrix^ operator*(Matrix^ m);
			virtual Vector^ operator*(Vector^ v);
			virtual Matrix^ operator*(Scalar^ s);
			virtual Matrix^ operator/(Scalar^ s);

			virtual bool isSameSize(Matrix^ m) sealed;

			static bool matrixCast(MathObject^ mo, Matrix^% mat);
		};
	}
}

