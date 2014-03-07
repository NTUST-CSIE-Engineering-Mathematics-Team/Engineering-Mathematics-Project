#include "Matrix.h"

using namespace em::math;

Matrix::Matrix(int dim1, int dim2) : MathObject("Matrix") {
	
	this->value = gcnew array<double, 2>(dim1, dim2);
}

Matrix::~Matrix() {
	delete this->value;
}

String^ Matrix::toString() {

	StringBuilder^ sb = gcnew StringBuilder();

	for (int i = value->GetLowerBound(0); i <= this->value->GetUpperBound(0); i++) {

		int j;
		for (j = value->GetLowerBound(1); j < this->value->GetUpperBound(1); j++) {
			sb->Append(this[i, j]);
			sb->Append(" ");
		}
		sb->Append(this[i, j]);
		sb->Append("\n");
	}

	String^ result = sb->ToString();
	delete sb;
	return result;
}