#include "Vector.h"

using namespace em::math;

Vector::Vector(int dim) : MathObject(TAG, ID) {
	
	this->value = gcnew array<double>(dim);
	this->value[0];
	this[0];
}

Vector::Vector(Vector^ vec) : MathObject(TAG, ID) {
	this->overrideAssign(vec);
}

Vector::~Vector() {
	delete this->value;
	
}

Vector^ Vector::fitAssign(Vector^ vec) {
	if (vec->dimension <= this->dimension) {
		int i;
		for (i = 0; i < vec->dimension; i++) {
			this[i] = vec[i];
		}

		for (; i < this->dimension; i++) {
			this[i] = 0;
		}
	}

	return this;
}


Vector^ Vector::overrideAssign(Vector^ vec) {
	delete this->value;
	this->value = dynamic_cast<array<double>^>(vec->value->Clone());

	return this;
}

MathObject^ Vector::overrideAssign(MathObject^ mo) {
	Vector^ tmp;
	if (!vectorCast(mo, tmp)) {
		return nullptr;
	}

	return this->overrideAssign(tmp);
}

String^ Vector::getHeader() {

	StringBuilder^ sb = gcnew StringBuilder(TAG);
	sb->AppendFormat(" rank = {0}", this->dimension);
	return sb->ToString();
}

String^ Vector::ToString() {

	StringBuilder^ sb = gcnew StringBuilder(getHeader());

	sb->Append("\n< ");
	int i;
	for (i = 0; i < this->value->Length - 1; i++) {
		sb->AppendFormat(NUMERAL_FORMAT, this[i]);
		sb->Append(",");
	}

	sb->AppendFormat(NUMERAL_FORMAT, this[i]);
	sb->Append(" >");

	String^ result = sb->ToString();
	delete sb;
	return result;
}

bool Vector::vectorCast(MathObject^ mo, Vector^% vec) {
	vec = dynamic_cast<Vector^>(mo);
	return vec != nullptr;
}

MathObject^ Vector::operator-() {
	Vector^ vec = gcnew Vector(this->dimension);
	for (int i = 0; i < this->dimension; i++) {
		vec[i] = -this[i];
	}

	return vec;
}

Vector^ Vector::operator-(Vector^ v) {
	
	if (!isSameRank(v, this)) {
		return nullptr;
	}

	Vector^ newVec = gcnew Vector(this->dimension);

	int i;
	for (i = 0; i < newVec->dimension; i++) {
		newVec[i] = this[i] - v[i];
	}

	return newVec;

}

Vector^ Vector::operator+(Vector^ v) {
	if (!isSameRank(v, this)) {
		return nullptr;
	}
	
	Vector^ newVec = gcnew Vector(this->dimension);

	for (int i = 0; i < newVec->dimension; i++) {
		newVec[i] = this[i] + v[i];
	}

	
	return newVec;
}

Vector^ Vector::operator*(Scalar^ s) {
	
	Vector^ newVec = gcnew Vector(this->dimension);

	for (int i = 0; i < this->dimension; i++) {
		newVec[i] = this[i] * s;
	}

	return newVec;
}

Scalar^ Vector::operator*(Vector^ v) {
	if (!isSameRank(v, this)) {
		return nullptr;
	}

	double product = 0;
	Vector^ newVec = gcnew Vector(this->dimension);

	for (int i = 0; i < newVec->dimension; i++) {
		product += this[i] * v[i];
	}

	return gcnew Scalar(product);
}

Vector^ Vector::operator/(Scalar^ s) {
	Vector^ newVec = gcnew Vector(this->dimension);
	
	for (int i = 0; i < this->dimension; i++) {
		newVec[i] = this[i] / s;
	}

	return newVec;
}

Vector^ Vector::cross(Vector^ v) {
	if (!isSameRank(v, this) || this->dimension > 3) {
		return nullptr;
	}

	Vector^ a = this;
	Vector^ b = v;
	Vector^ crs = gcnew Vector(3);

	if (this->dimension < 3) {
		a = gcnew Vector(3);
		a->fitAssign(this);
	}

	if (v->dimension < 3) {
		b = gcnew Vector(3);
		b->fitAssign(v);
	}

	crs[0] = a[1] * b[2] - a[2] * b[1];
	crs[1] = a[2] * b[0] - a[0] * b[2];
	crs[2] = a[0] * b[1] - a[1] * b[0];

	return crs;
}

Scalar^ Vector::component(Vector^ v) {
	return this * v->normalized;
}

Vector^ Vector::projection(Vector^ v) {
	Vector^ n = v->normalized;
	return n * (this * n);
}

bool Vector::isSameRank(Vector^ a, Vector^ b) {
	return a != nullptr && b != nullptr && a->dimension == b->dimension;
}

int Vector::getWiderRank(Vector^ a, Vector^ b) {
	return a->dimension > b->dimension ? a->dimension : b->dimension;
}

bool Vector::isZeroVector(Vector^ vec) {
	for (int i = 0; i < vec->dimension; i++) {
		if (vec[i] != 0) {
			return false;
		}
	}

	return true;
}

void Vector::widerConvert(Vector^% a, Vector^% b) {
	if (isSameRank(a, b)) {
		return;
	}

	int wRank = a->dimension;
	if (b->dimension > wRank) {
		wRank = b->dimension;
		Vector^ c = gcnew Vector(wRank);
		c->fitAssign(a);
		a = c;
	} else {
		Vector^ c = gcnew Vector(wRank);
		c->fitAssign(b);
		b = c;
	}
}