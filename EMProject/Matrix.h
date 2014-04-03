#pragma once
#include "Scalar.h"
#include "MathObject.h"

namespace em {
	namespace math {
		using System::String;
		using System::Text::StringBuilder;
		ref class Vector;
		ref class Matrix : public MathObject{

		public:
			enum class VectorOption { ROW, COLUMN };
			enum class SolutionState {UNIQUE, INFINITE, INCONSISTENT, BAD_CONSTANTS};
			static String^ const TAG = "Matrix";
			static String^ const ID = "M";

			property Matrix^ clone{
				Matrix^ get() {
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

			property bool isSquare {
				bool get() {
					return this->rowLength == this->columnLength;
				}
			}

			virtual property Matrix^ rowEchelonForm {
				Matrix^ get();
			}

			virtual property Matrix^ inverse {
				Matrix^ get();
			}

			virtual property Scalar^ determinant {
				Scalar^ get();
			}

			virtual property Scalar^ rank {
				Scalar^ get();
			}
		private: 
			array<double, 2>^ value;
			
		public:
			Matrix(int dim1, int dim2);
			Matrix(Matrix^ mat);
			Matrix(VectorOption op, Vector^ vec);
			virtual ~Matrix();

			virtual String^ getHeader() override;
			virtual String^ ToString() override;
			virtual MathObject^ operator-() override;

			virtual Matrix^ fitAssign(Matrix^ mat);
			virtual MathObject^ overrideAssign(MathObject^ mo) override;
			virtual Matrix^ overrideAssign(Matrix^ mat);

			virtual Matrix^ operator-(Matrix^ m);
			virtual Matrix^ operator+(Matrix^ m);
			virtual Matrix^ operator*(Matrix^ m);
			virtual Matrix^ operator*(Vector^ v);
			virtual Matrix^ operator*(Scalar^ s);
			virtual Matrix^ operator/(Scalar^ s);

			virtual bool isSameSize(Matrix^ m);
			virtual Matrix^ transpose();
			virtual Matrix^ pow(int exponent);

			virtual void ulDecomposition(Matrix^% upper, Matrix^% lower);
			virtual SolutionState solveLinearSystem(Vector^ constSet, Matrix^% solutions);
			virtual SolutionState solveLinearSystem(Matrix^ constSet, Matrix^% solutions);
			
			virtual void multiplyRowOperation(int i, const double scalar);
			virtual void swapRowOperation(int i, int j);
			virtual void addRowOperation(int s, const double scalar, int d);
			
			static bool matrixCast(MathObject^ mo, Matrix^% mat);
			static Matrix^ getIdentityMatrix(int size);
				
		private:
			Matrix^ makeUpperTriangle(Matrix^ syncer);
			void doUpperToIdentity(Matrix^% syncer);
		};
	}
}

