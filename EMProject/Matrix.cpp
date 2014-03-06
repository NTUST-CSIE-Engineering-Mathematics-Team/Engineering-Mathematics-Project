#include "Matrix.h"

using em::math::Matrix;

Matrix::Matrix(int dim1, int dim2) {
	
	this->values = gcnew array<double, 2>(dim1, dim2);
}

Matrix::~Matrix() {
	delete this->values;
}