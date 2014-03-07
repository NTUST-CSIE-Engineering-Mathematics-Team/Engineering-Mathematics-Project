#include "Matrix.h"

using namespace em::math;

Matrix::Matrix(int dim1, int dim2) {
	
	this->values = gcnew array<double, 2>(dim1, dim2);
}

Matrix::~Matrix() {
	delete this->values;
}