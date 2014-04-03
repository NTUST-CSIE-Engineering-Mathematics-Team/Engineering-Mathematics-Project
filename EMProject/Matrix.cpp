#include "Matrix.h"
#include "Vector.h"

using namespace em::math;

Matrix::Matrix(int dim1, int dim2) : MathObject(TAG, ID) {
	this->value = gcnew array<double, 2>(dim1, dim2);
}

Matrix::Matrix(Matrix^ mat) : MathObject(TAG, ID) {
	this->overrideAssign(mat);
}


Matrix::Matrix(VectorOption op, Vector^ vec) : MathObject(TAG, ID) {

	if (op == VectorOption::ROW) {
		this->value = gcnew array<double, 2>(1, vec->dimension);
		this[VectorOption::ROW, 0] = vec;
	} else {
		this->value = gcnew array<double, 2>(vec->dimension, 1);
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
		for (int j = 0; j < vec->dimension; j++) {
			vec[j] = this[i, j];
		}
	} else {
		vec = gcnew Vector(this->columnLength);
		for (int j = 0; j < vec->dimension; j++) {
			vec[j] = this[j, i];
		}
	}

	return vec;
}
void Matrix::default::set(VectorOption vo, int i, Vector^ vec) {
	int j;
	if (vo == VectorOption::ROW) {
		if (vec->dimension <= this->rowLength) {
			for (j = 0; j < vec->dimension; j++) {
				this[i, j] = vec[j];
			}

			for (; j < this->rowLength; j++) {
				this[i, j] = 0;
			}
		}
	} else {
		if (vec->dimension <= this->columnLength) {
			for (j = 0; j < vec->dimension; j++) {
				this[j, i] = vec[j];
			}

			for (; j < this->rowLength; j++) {
				this[j, i] = 0;
			}
		}
	}
}

String^ Matrix::getHeader() {

	StringBuilder^ sb = gcnew StringBuilder(TAG);
	sb->AppendFormat(" size = ({0} x {1})", this->columnLength, this->rowLength);
	return sb->ToString();
}

String^ Matrix::ToString() {
	
	StringBuilder^ sb = gcnew StringBuilder(getHeader());
	sb->Append("\n");
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

Matrix^ Matrix::operator*(Vector^ v) {
	if (this->rowLength != v->dimension) {
		return nullptr;
	}

	Matrix^ newMat = gcnew Matrix(this->columnLength, 1);

	for (int i = 0; i < this->columnLength; i++) {
		for (int j = 0; j < v->dimension; j++) {
			newMat[i, 0] += this[i, j] * v[j];
		}
	}

	return newMat;
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
	if (!this->isSquare) {
		return nullptr;
	}

	if (exponent == 0) {
		return getIdentityMatrix(this->columnLength);
	}
	Matrix^ m,^ o;
	if (exponent < 0) {
		Matrix^ inverse = this->inverse;
		if (inverse == nullptr) {
			return nullptr;
		}
		m = inverse;
		
	} else {
		m = gcnew Matrix(this);
	}
	o = m->clone;

	for (int i = 1; i < exponent; i++) {
		m = m * o;
	}

	return m;
}

Matrix^ Matrix::rowEchelonForm::get() {
	
	Matrix^ upper = this->makeUpperTriangle(nullptr);

	for (int i = 0, j = 0; i < upper->columnLength && j < upper->rowLength; i++, j++) {
		for (; j < upper->rowLength; j++) {
			if (upper[i, j] != 0) {
				upper->multiplyRowOperation(i, 1 / upper[i, j]);
				break;
			}
		}
	}
	
	return upper;
}

Matrix^ Matrix::inverse::get() {
	if (!this->isSquare) {
		return nullptr;
	}
	Matrix^ inverse = getIdentityMatrix(this->columnLength);
	Matrix^ upper = this->makeUpperTriangle(inverse);
	for (int i = 0; i < upper->columnLength; i++) {
		if (upper[i, i] == 0) {
			return nullptr;
		}
	}
	
	upper->doUpperToIdentity(inverse);
	return inverse;
}

Scalar^ Matrix::determinant::get() {
	if (!this->isSquare) {
		return nullptr;
	}

	double det = 1;
	Matrix^ upper = makeUpperTriangle(nullptr);
	for (int i = 0; i < this->columnLength; i++) {
		det *= upper[i, i];
	}

	return gcnew Scalar(det);
}

Scalar^ Matrix::rank::get() {

	Matrix^ upper = this->makeUpperTriangle(nullptr);
	
	int rank = 0;
	for (int i = 0, j = 0; i < upper->columnLength && j < upper->rowLength; i++, j++) {
		for (; j < upper->rowLength; j++) {
			if (upper[i, j] != 0) {
				rank++;
				break;
			}
		}
	}

	return gcnew Scalar(rank);
}

void Matrix::ulDecomposition(Matrix^% upper, Matrix^% lower) {
	lower = getIdentityMatrix(this->columnLength);
	upper = makeUpperTriangle(lower);
	lower = lower->inverse;
}

Matrix::SolutionState Matrix::solveLinearSystem(Vector^ constSet, Matrix^% solutions) {
	return this->solveLinearSystem(gcnew Matrix(VectorOption::COLUMN, constSet), solutions);
}

Matrix::SolutionState Matrix::solveLinearSystem(Matrix^ constSet, Matrix^% solutions) {
	if (constSet->rowLength != 1 || this->columnLength != constSet->columnLength) {
		return SolutionState::BAD_CONSTANTS;
	}

	if (this->rowLength > this->columnLength) {
		return SolutionState::INFINITE;
	}

	solutions = constSet->clone;
	Matrix^ upper = this->makeUpperTriangle(solutions);

	int i = 0;
	for (; i < upper->rowLength; i++) {
		if (upper[i, i] == 0) {
			double sol = solutions[i, 0];
			delete solutions;
			solutions = nullptr;
			
			if ( sol != 0) {
				for (int j = i + 1; j < this->columnLength; j++) {
					if (upper[i, j] != 0) {
						return SolutionState::INFINITE;
					}
				}

				return SolutionState::INCONSISTENT;
			}
			
			return SolutionState::INFINITE;
		}
	}

	for (; i < upper->columnLength; i++) {
		if (solutions[i, 0] != 0) {
			delete solutions;
			solutions = nullptr;
			return SolutionState::INCONSISTENT;
		}
	}

	upper->doUpperToIdentity(solutions);
	
	
	return SolutionState::UNIQUE;

}

Matrix^ Matrix::makeUpperTriangle(Matrix^ syncer) {
	Matrix^ upper = this->clone;
	bool hasSyncer = syncer != nullptr;
	double q;
	for (int i = 0, j = 0; i < upper->columnLength && j < upper->rowLength; i++, j++) {
		for (; upper[i, j] == 0;) {
			int k;
			for (k = i; k < upper->columnLength; k++) {
				if (upper[k, j] != 0) {
					upper->addRowOperation(k, 1, i);
					if (hasSyncer) {
						syncer->addRowOperation(k, 1, i);
					}
					break;
				}
			}
			if (k == upper->columnLength) {
				j++;
				if (j == upper->rowLength) {
					return upper;
				}
			}
		}

		for (int k = i + 1; k < upper->columnLength; k++) {
			q = upper[k, j] / upper[i, j];
			if (q != 0) {
				upper->addRowOperation(i, -q, k);
				if (hasSyncer) {
					syncer->addRowOperation(i, -q, k);
				}
			}
			upper[k, j] = 0;
		}
	}

	return upper;
}

void Matrix::doUpperToIdentity(Matrix^% syncer) {
	int bounds = System::Math::Min(this->columnLength, this->rowLength) - 1;
	for (int i = bounds; i >= 0; i--) {
		for (int j = bounds; j > i; j--) {
			syncer->addRowOperation(j, -this[i, j], i);
			this[i, j] = 0;
			
		}
		syncer->multiplyRowOperation(i, 1 / this[i, i]);
		this[i, i] = 1;
	}
}



void Matrix::multiplyRowOperation(int i, const double scalar) {
	for (int j = 0; j < this->rowLength; j++) {
		this[i, j] *= scalar;
	}
}

void Matrix::swapRowOperation(int i, int j) {
	double tmp;
	for (int k = 0; k < this->rowLength; k++) {
		tmp = this[i, k];
		this[i, k] = this[j, k];
		this[j, k] = tmp;
	}
}

void Matrix::addRowOperation(int s, const double scalar, int d) {
	for (int k = 0; k < this->rowLength; k++) {
		this[d, k] += scalar * this[s, k];
	}
}


