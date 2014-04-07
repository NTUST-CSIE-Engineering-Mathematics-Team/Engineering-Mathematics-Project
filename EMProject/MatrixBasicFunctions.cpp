#include "MatrixBasicFunctions.h"

using namespace em::math::engine::expression::functions;

MathObject^ MatrixBasicFunctions::transpose$M(array<MathObject^>^ mos, Message^% msg) {
	Matrix^ mat;
	Matrix::matrixCast(mos[0], mat);

	return mat->transpose;
}
MathObject^ MatrixBasicFunctions::row_ech$M(array<MathObject^>^ mos, Message^% msg) {
	Matrix^ mat;
	Matrix::matrixCast(mos[0], mat);

	return mat->rowEchelonForm;
}

MathObject^ MatrixBasicFunctions::solve_linear$M_V(array<MathObject^>^ mos, Message^% msg) {
	Matrix^ mat, ^sols;
	Vector^ consts;
	Matrix::matrixCast(mos[0], mat);
	Vector::vectorCast(mos[1], consts);

	dealLinearSystemResult(mat->solveLinearSystem(consts, sols), msg);
	return sols;
		
}

MathObject^ MatrixBasicFunctions::solve_linear$M_M(array<MathObject^>^ mos, Message^% msg) {
	Matrix^ mat, ^ consts, ^ sols;
	Matrix::matrixCast(mos[0], mat);
	Matrix::matrixCast(mos[1], consts);

	dealLinearSystemResult(mat->solveLinearSystem(consts, sols), msg);
	return sols;

}

MathObject^ MatrixBasicFunctions::inverse$M(array<MathObject^>^ mos, Message^% msg) {
	Matrix^ mat;
	Matrix::matrixCast(mos[0], mat);

	Matrix^ inverse = mat->inverse;

	if (inverse == nullptr) {
		msg = gcnew Message(Message::State::ERROR, "This matrix does not have the inverse matrix");
	}

	return inverse;
}

MathObject^ MatrixBasicFunctions::det$M(array<MathObject^>^ mos, Message^% msg) {
	Matrix^ mat;
	Matrix::matrixCast(mos[0], mat);

	Scalar^ det = mat->determinant;

	if (det == nullptr) {
		msg = notSquareErrMsg("det");
	}

	return det;
}

MathObject^ MatrixBasicFunctions::rank$M(array<MathObject^>^ mos, Message^% msg) {
	Matrix^ mat;
	Matrix::matrixCast(mos[0], mat);

	return mat->rank;
}


MathObject^ MatrixBasicFunctions::adj$M(array<MathObject^>^ mos, Message^% msg) {
	Matrix^ mat, ^ adj;
	Matrix::matrixCast(mos[0], mat);
	adj = mat->adjoint;
	if (adj == nullptr) {
		msg = notSquareErrMsg("adj");
	}
	return adj;
}

MathObject^ MatrixBasicFunctions::ul_decom$M(array<MathObject^>^ mos, Message^% msg) {
	Matrix^ mat;
	Matrix::matrixCast(mos[0], mat);
	MathObjGenericSet<Matrix^>^ result = gcnew MathObjGenericSet<Matrix^>();
	
	Matrix^ upper,^ lower;
	mat->ulDecomposition(upper, lower);
	result->add(lower);
	result->add(upper);
	
	return result;
}

MathObject^ MatrixBasicFunctions::pow$M_S(array<MathObject^>^ mos, Message^% msg) {
	Scalar^ scl;
	Scalar::scalarCast(mos[1], scl);
	if (scl->isInteger) {
		msg = gcnew Message(Message::State::ERROR, "A exponent of a matrix cannot be a decimal");
		return nullptr;
	}
	Matrix^ mat;
	Matrix::matrixCast(mos[0], mat);

	mat = mat->pow(scl->toInteger());
	if (mat == nullptr) {
		msg = gcnew Message(Message::State::ERROR, "Connot perform function \"pow\" on a non-square matrix or the matrix that is not invertible");
	}

	return mat;
}

MathObject^ MatrixBasicFunctions::eigen$M(array<MathObject^>^ mos, Message^% msg) {
	Matrix^ mat;
	Matrix::matrixCast(mos[0], mat);
	if (!mat->isSquare) {
		msg = notSquareErrMsg("eigen");
		return nullptr;
	}

	if (mat->columnLength > 3) {
		msg = gcnew Message(Message::State::ERROR, "Sorry,it cannot find eigen values and eigen vectors when matrix size is larger than 3");
		return nullptr;
	}

	Matrix^ eVal = gcnew Matrix(mat->columnLength, mat->columnLength), ^ eVec = gcnew Matrix(mat->columnLength, mat->columnLength);

	if (mat->columnLength == 3) {
		double a = -(mat[0, 0] + mat[1, 1] + mat[2, 2]);
		double b = -(mat[1, 2] * mat[2, 1] + mat[0, 1] * mat[1, 0] + mat[0, 2] * mat[2, 0]
				   - mat[0, 0] * mat[1, 1] - mat[0, 0] * mat[2, 2] - mat[1, 1] * mat[2, 2]);
		double c = -(mat[0, 0] * mat[1, 1] * mat[2, 2] + mat[0, 1] * mat[1, 2] * mat[2, 0] + mat[0, 2] * mat[1, 0] * mat[2, 1]
				   - mat[0, 0] * mat[1, 2] * mat[2, 1] - mat[0, 1] * mat[1, 0] * mat[2, 2] - mat[0, 2] * mat[2, 0] * mat[1, 1]);

		double q = (Math::Pow(a, 2) - 3 * b) / 9;
		double r = (2 * Math::Pow(a, 3) - 9 * a * b  + 27 * c) / 54;
		double q3 = pow(q, 3);
		if (q3 > r * r) {
			a /= 3;
			double theta = Math::Acos(r / Math::Sqrt(q3));
			
			eVal[0, 0] = -2 * Math::Sqrt(q) * Math::Cos(theta / 3) - a;
			eVal[1, 1] = -2 * Math::Sqrt(q) * Math::Cos((theta + Math::PI * 2 )/ 3) - a;
			eVal[2, 2] = -2 * Math::Sqrt(q) * Math::Cos((theta - Math::PI * 2) / 3) - a;

		} else {
			msg = gcnew Message(Message::State::ERROR, "The eigen values are not real numbers, so they can't be solved");
			return nullptr;
		}
	} else if(mat->columnLength == 2) {
		double b = -(mat[0, 0] + mat[1, 1]);
		double c = mat[1, 1] * mat[0, 0] - mat[0, 1] * mat[1, 0];
		double b2 = b * b;
		c *= 4;
		if ( b2 - c >= 0) {
			eVal[0, 0] = (-b - Math::Sqrt(b2 - c)) / 2;
			eVal[1, 1] = (-b + Math::Sqrt(b2 - c)) / 2;
		} else {
			msg = gcnew Message(Message::State::ERROR, "The eigen values are not real numbers, so they can't be solved");
			return nullptr;
		}
	} else {
		eVal[0, 0] = mat[0, 0];
	}

	Matrix^ tmpM;
	Vector^ tmpV;
	int j;
	for (int i = 0; i < mat->columnLength; i++) {
		tmpM = mat->clone;
		tmpV = gcnew Vector(tmpM->columnLength);
		for (j = 0; j < tmpM->columnLength; j++) {
			tmpM[j, j] -= eVal[i, i];
		}
		tmpM = tmpM->reducedRowEchelonForm;
		
		for (j = 0; j < tmpM->columnLength - 1; j++) {
			tmpV[j] = tmpM[j, tmpM->rowLength - 1];
		}
		tmpV[j] = -1;

		eVec[Matrix::VectorOption::COLUMN, i] = tmpV->normalized;

	}

	MathObjGenericSet<Matrix^>^ mset = gcnew MathObjGenericSet<Matrix^>(2);
	mset->add(eVec);
	mset->add(eVal);
	return mset;
}

MathObject^ MatrixBasicFunctions::power_eigen$M(array<MathObject^>^ mos, Message^% msg) {
	Matrix^ mat;
	Matrix::matrixCast(mos[0], mat);
	if (!mat->isSquare) {
		msg = notSquareErrMsg("power_eigen");
		return nullptr;
	}

	Vector^ guess = gcnew Vector(mat->columnLength);
	Vector^ aux;
	for (int i = 0; i < guess->dimension; i++) {
		guess[i] = -1;
	}

	double diff = 1;
	double lastMax = 0;
	Scalar^ max = gcnew Scalar(0);
	for (; !MathHelper::isZero(diff);) {
		aux = Matrix::multiplyToVector(mat, guess);
		max->overrideAssign(getMaxAbsScalar(aux));
		diff = Math::Abs(max - lastMax);
		lastMax = max;
		guess = aux / max;
	}

	Vector^ valVec = gcnew Vector(guess->dimension);
	valVec[0] = Matrix::multiplyToVector(mat, guess) * guess / (guess * guess);
	MathObjGenericSet<Vector^>^ vset = gcnew MathObjGenericSet<Vector^>(2);
	vset->add(guess->normalized);
	vset->add(valVec);

	return vset;
}

MathObject^ MatrixBasicFunctions::least_square$M_M(array<MathObject^>^ mos, Message^% msg) {
	Matrix^ mat, ^ consts, ^ matTrans;
	Matrix::matrixCast(mos[0], mat);
	Matrix::matrixCast(mos[1], consts);

	if (consts->rowLength != 1 || consts->columnLength != mat->columnLength) {
		msg = gcnew Message(Message::State::ERROR, "The constants matrix should only have one row and the same clomn size with the first argument");
		return nullptr;
	}

	matTrans = mat->transpose;
	mat = (matTrans * mat)->inverse;
	if (mat == nullptr) {
		msg = gcnew Message(Message::State::ERROR, "There must be something wrong with your first matrix argument, please check its value");
		return nullptr;
	}
	return mat * matTrans * consts;
}

void MatrixBasicFunctions::dealLinearSystemResult(Matrix::SolutionState ss, Message^% msg) {
	switch (ss) {
	case Matrix::SolutionState::INCONSISTENT:
		msg = gcnew Message(Message::State::ERROR, "There is no solution to this linear system");
		break;
	case Matrix::SolutionState::INFINITE:
		msg = gcnew Message(Message::State::ERROR, "There are infinite solutions to this linear system");
		break;
	case Matrix::SolutionState::BAD_CONSTANTS:
		msg = gcnew Message(Message::State::ERROR, "The size of the matrix of constants is invaild");
		break;
	}
}

Message^ MatrixBasicFunctions::notSquareErrMsg(String^ funName) {
	return gcnew Message(Message::State::ERROR, "Cannot perform  function \"" + funName + "\" on a non-square matrix");
}
					
double MatrixBasicFunctions::getMaxAbsScalar(Vector^ vec) {
	double result = vec[0];
	for (int i = 1; i < vec->dimension; i++) {
		if (Math::Abs(result) < Math::Abs(vec[i])) {
			result = vec[i];
		}
	}

	return result;
}