#include "Matrix.h"

using namespace em::math;

Matrix::Matrix(int dim1, int dim2) : MathObject(TAG, ID) {
	this->value = gcnew array<double, 2>(dim1, dim2);
}

Matrix::Matrix(Matrix^ mat) : MathObject(TAG, ID) {
	this->overrideAssign(mat);
}


Matrix::Matrix(VectorOption op, Vector^ vec) : MathObject(TAG, ID) {

	if (op == VectorOption::ROW) {
		this->value = gcnew array<double, 2>(1, vec->rank);
		this[VectorOption::ROW, 0] = vec;
	} else {
		this->value = gcnew array<double, 2>(vec->rank, 1);
		this[VectorOption::COLUMN, 0] = vec;
	}

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

	for (i = 0; i < this->columnLength - 1; i++) {
		for (j = 0; j < this->rowLength; j++) {

			sb->AppendFormat(MathObject::NUMERAL_FORMAT, this[i, j]);
			
		}
		sb->Append("\n");
	}

	for (j = 0; j < this->rowLength; j++) {

		sb->AppendFormat(MathObject::NUMERAL_FORMAT, this[i, j]);
		
	}
	
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

MathObject^ Matrix::overrideAssign(MathObject^ mo) {
	Matrix^ tmp;
	if (!matrixCast(mo, tmp)) {
		return nullptr;
	}

	return this->overrideAssign(tmp);
}

bool Matrix::matrixCast(MathObject^ mo, Matrix^% mat) {
	mat = dynamic_cast<Matrix^>(mo);
	return mat != nullptr;
}

MathObject^ Matrix::operator-() {
	Matrix^ newMat = gcnew Matrix(this->columnLength, this->rowLength);

	for (int i = 0; i < this->columnLength; i++) {
		for (int j = 0; j < this->rowLength; j++) {
			newMat[i, j] = -this[i, j];
		}
	}
	return newMat;
}

Matrix^ Matrix::operator- (Matrix^ m) {
	if (!this->isSameSize(m)) {
		return nullptr;
	}

	Matrix^ newMat = gcnew Matrix(this->columnLength, this->rowLength);

	for (int i = 0; i < this->columnLength; i++) {
		for (int j = 0; j < this->rowLength; j++) {
			newMat[i, j] = this[i, j] - m[i, j];
		}
	}

	return newMat;
}

Matrix^ Matrix::operator+(Matrix^ m) {
	if (!this->isSameSize(m)) {
		return nullptr;
	}

	Matrix^ newMat = gcnew Matrix(this->columnLength, this->rowLength);

	for (int i = 0; i < this->columnLength; i++) {
		for (int j = 0; j < this->rowLength; j++) {
			newMat[i, j] = this[i, j] + m[i, j];
		}
	}

	return newMat;
}

Matrix^ Matrix::operator*(Matrix^ m) {
	if (this->rowLength != m->columnLength) {
		return nullptr;
	}

	Matrix^ newMat = gcnew Matrix(this->columnLength, m->rowLength);

	for (int i = 0; i < newMat->columnLength; i++) {
		for (int j = 0; j < newMat->rowLength; j++) {
			for (int k = 0; k < this->rowLength; k++) {
				newMat[i, j] += this[i, k] * m[k, j];
			}
		}
	}

	return newMat;
}

Vector^ Matrix::operator*(Vector^ v) {
	if (this->rowLength != v->rank) {
		return nullptr;
	}

	Vector^ newVec = gcnew Vector(this->columnLength);

	for (int i = 0; i < this->columnLength; i++) {
		for (int j = 0; j < v->rank; j++) {
			newVec[i] += this[i, j] * v[j];
		}
	}

	return newVec;
}

Matrix^ Matrix::operator*(Scalar^ s) {
	Matrix^ newMat = gcnew Matrix(this->columnLength, this->rowLength);

	for (int i = 0; i < this->columnLength; i++) {
		for (int j = 0; j < this->rowLength; j++) {
			newMat[i, j] = this[i, j] * s;
		}
	}

	return newMat;
}

Matrix^ Matrix::operator/(Scalar^ s) {
	Matrix^ newMat = gcnew Matrix(this->columnLength, this->rowLength);

	for (int i = 0; i < this->columnLength; i++) {
		for (int j = 0; j < this->rowLength; j++) {
			newMat[i, j] = this[i, j] / s;
		}
	}

	return newMat;
}

bool Matrix::isSameSize(Matrix^ m) {
	return this->columnLength == m->columnLength && this->rowLength == m->rowLength;
}

Matrix^ Matrix::getIdentityMatrix(int size) {
	Matrix^ idnty = gcnew Matrix(size, size);

	for (int i = 0; i < size; i++) {
		idnty[i, i] = 1;
	}

	return idnty;
}

Matrix^ Matrix::transpose() {
	Matrix^ newMat = gcnew Matrix(this->rowLength, this->columnLength);
	
	for (int i = 0; i < this->columnLength; i++) {
		for (int j = 0; j < this->rowLength; j++) {
			newMat[j, i] = this[i, j];
		}
	}

	return newMat;
}


Matrix^ Matrix::pow(int exponent) {
	if (!this->square) {
		return nullptr;
	}

	if (exponent == 0) {
		return getIdentityMatrix(this->columnLength);
	}

	Matrix^ m = gcnew Matrix(this);
	// not support inverse of matrix yet
	for (int i = 1; i < exponent; i++) {
		m = m * this;
	}

	return m;
}