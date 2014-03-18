#include "Vector.h"

using namespace em::math;

Vector::Vector(int dim) : MathObject(tag) {
	
	this->value = gcnew array<double>(dim);
}

Vector::Vector(Vector^ vec) : MathObject(tag) {
	this->overrideAssign(vec);
}

Vector::~Vector() {
	delete this->value;
	
}

Vector^ Vector::fitAssign(Vector^ vec) {
	if (vec->rank <= this->rank) {
		int i;
		for (i = 0; i < vec->rank; i++) {
			this[i] = vec[i];
		}

		for (; i < this->rank; i++) {
			this[i] = 0;
		}
	}

	return this;
}


Vector^ Vector::overrideAssign(Vector^ vec) {

	this->value = dynamic_cast<array<double>^>(vec->value->Clone());

	return this;
}

String^ Vector::ToString() {

	StringBuilder^ sb = gcnew StringBuilder("< ");
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
	Vector^ vec = gcnew Vector(this->rank);
	for (int i = 0; i < this->rank; i++) {
		vec[i] = -this[i];
	}

	return vec;
}

Vector^ Vector::operator-(Vector^ v) {

	bool s;
	int wRank, sRank;
	if (this->rank < v->rank) {
		wRank = v->rank;
		sRank = this->rank;
		s = true;
	} else {
		wRank = this->rank;
		sRank = v->rank;
		s = false;
	}

	Vector^ newVec = gcnew Vector(wRank);

	int i;
	for (i = 0; i < sRank; i++) {
		newVec[i] = this[i] - v[i];
	}

	if (s) {
		for (; i < newVec->rank; i++) {
			newVec[i] = -v[i];
		}
	} else {
		for (; i < newVec->rank; i++) {
			newVec[i] = this[i];
		}
	}

	return newVec;

}

Vector^ Vector::operator+(Vector^ v) {
	Vector^ w = this;
	Vector^ s = v;
	int wRank = this->rank;
	if (v->rank > wRank) {
		wRank = v->rank;
		w = v;
		s = w;
	}
	Vector^ newVec = gcnew Vector(wRank);

	int i;
	for (i = 0; i < s->rank; i++) {
		newVec[i] = w[i] + s[i];
	}

	for (; i < newVec->rank; i++) {
		newVec[i] = w[i];
	}

	return newVec;
}

Vector^ Vector::operator*(Scalar^ s) {
	
	Vector^ newVec = gcnew Vector(this->rank);

	for (int i = 0; i < this->rank; i++) {
		newVec[i] = this[i] * s;
	}

	return newVec;
}

Scalar^ Vector::operator*(Vector^ v) {
	if (!isSameRank(this, v)) {
		return nullptr;
	}

	double product = 0;
	
	for (int i = 0; i < this->rank; i++) {
		product += this[i] * v[i];
	}

	return gcnew Scalar(product);
}

Vector^ Vector::cross(Vector^ v) {
	if (this->rank > 3 || v->rank > 3) {
		return nullptr;
	}

	Vector^ a = this;
	Vector^ b = v;
	Vector^ crs = gcnew Vector(3);

	if (this->rank < 3) {
		a = gcnew Vector(3);
		a->fitAssign(this);
	}

	if (v->rank < 3) {
		b = gcnew Vector(3);
		b->fitAssign(v);
	}

	crs[0] = a[1] * b[2] - a[2] * b[1];
	crs[1] = a[2] * b[0] - a[0] * b[2];
	crs[2] = a[0] * b[1] - a[1] * b[0];

	return crs;
}

bool Vector::isSameRank(Vector^ a, Vector^ b) {
	return a->rank == b->rank;
}

int Vector::getWiderRank(Vector^ a, Vector^ b) {
	return a->rank > b->rank ? a->rank : b->rank;
}