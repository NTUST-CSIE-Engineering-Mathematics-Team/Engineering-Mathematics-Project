#include "Matrix.h"

using namespace em::math;

Matrix::Matrix(int dim1, int dim2) : MathObject(tag) {
	this->value = gcnew array<double, 2>(dim1, dim2);
}

Matrix::Matrix(Matrix^ mat) : MathObject(tag) {
	this->overrideAssign(mat);
}

Matrix::~Matrix() {
	delete this->value;
}

Vector^ Matrix::default::get(VectorOption vo, int i) {
	Vector^ vec;
	if (vo == VectorOption::ROW) {
		vec = gcnew Vector(this->rowLength);
		for (int j = 0; j < vec->rank; j++) {
			vec[j] = this[i, j];
		}
	} else {
		vec = gcnew Vector(this->columnLength);
		for (int j = 0; j < vec->rank; j++) {
			vec[j] = this[j, i];
		}
	}

	return vec;
}
void Matrix::default::set(VectorOption vo, int i, Vector^ vec) {
	int j;
	if (vo == VectorOption::ROW) {
		if (vec->rank <= this->rowLength) {
			for (j = 0; j < vec->rank; j++) {
				this[i, j] = vec[j];
			}

			for (; j < this->rowLength; j++) {
				this[i, j] = 0;
			}
		}
	} else {
		if (vec->rank <= this->columnLength) {
			for (j = 0; j < vec->rank; j++) {
				this[j, i] = vec[j];
			}

			for (; j < this->rowLength; j++) {
				this[j, i] = 0;
			}
		}
	}
}

String^ Matrix::ToString() {
	
	StringBuilder^ sb = gcnew StringBuilder();
	int i,j;

	for (i = value->GetLowerBound(0); i < this->value->GetUpperBound(0); i++) {
		for (j = value->GetLowerBound(1); j < this->value->GetUpperBound(1); j++) {

			sb->AppendFormat(MathObject::NUMERAL_FORMAT, this[i, j]);
			sb->Append("\t");
		}

		sb->AppendFormat(MathObject::NUMERAL_FORMAT, this[i, j]);
		sb->Append("\n");
	}

	for (j = value->GetLowerBound(1); j < this->value->GetUpperBound(1); j++) {

		sb->AppendFormat(MathObject::NUMERAL_FORMAT, this[i, j]);
		sb->Append("\t");
	}

	sb->AppendFormat(MathObject::NUMERAL_FORMAT, this[i, j]);
	
	String^ result = sb->ToString();
	delete sb;
	return result;
}

Matrix^ Matrix::fitAssign(Matrix^ mat) {

	if (mat->columnLength <= this->columnLength && mat->rowLength <= this->rowLength) {
		int i;
		for (i = 0; i < mat->columnLength; i++) {
			this[Matrix::VectorOption::ROW, i] = mat[Matrix::VectorOption::ROW, i];
		}

		Vector^ empty = gcnew Vector(this->rowLength);
		for (; i < this->columnLength; i++) {
			this[Matrix::VectorOption::ROW, i] = empty;
		}
	}

	return this;
}

Matrix^ Matrix::overrideAssign(Matrix^ mat) {
	delete this->value;
	this->value = dynamic_cast<array<double, 2>^>(mat->value->Clone());
	
	return this;
}

bool Matrix::martixCast(MathObject^ mo, Matrix^% mat) {
	mat = dynamic_cast<Matrix^>(mo);
	return mat != nullptr;
}

MathObject^ Matrix::operator-() {	
	for (int i = value->GetLowerBound(0); i <= this->value->GetUpperBound(0); i++) {
		for (int j = value->GetLowerBound(1); j <= this->value->GetUpperBound(1); j++) {
			this[i, j] = -this[i, j];
		}
	}
	return this;
}