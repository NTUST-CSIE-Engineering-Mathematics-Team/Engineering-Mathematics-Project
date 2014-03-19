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

	Vector^ t = this;
	widerConvert(t, v);

	Vector^ newVec = gcnew Vector(t->rank);

	int i;
	for (i = 0; i < newVec->rank; i++) {
		newVec[i] = t[i] - v[i];
	}

	return newVec;

}

Vector^ Vector::operator+(Vector^ v) {
	Vector^ t = this;
	widerConvert(t, v);
	
	Vector^ newVec = gcnew Vector(t->rank);

	for (int i = 0; i < newVec->rank; i++) {
		newVec[i] = t[i] + v[i];
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
	
	Vector^ t = this;
	widerConvert(t, v);

	double product = 0;
	
	for (int i = 0; i < t->rank; i++) {
		product += t[i] * v[i];
	}

	return gcnew Scalar(product);
}

Vector^ Vector::operator/(Scalar^ s) {
	Vector^ newVec = gcnew Vector(this->rank);

	for (int i = 0; i < this->rank; i++) {
		newVec[i] = this[i] / s;
	}

	return newVec;
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

Scalar^ Vector::projection(Vector^ v) {
	
	return this * v->normalized;
}

bool Vector::isSameRank(Vector^ a, Vector^ b) {
	return a->rank == b->rank;
}

int Vector::getWiderRank(Vector^ a, Vector^ b) {
	return a->rank > b->rank ? a->rank : b->rank;
}

void Vector::widerConvert(Vector^% a, Vector^% b) {
	if (isSameRank(a, b)) {
		return;
	}

	int wRank = a->rank;
	if (b->rank > wRank) {
		wRank = b->rank;
		Vector^ c = gcnew Vector(wRank);
		c->fitAssign(a);
		a = c;
	} else {
		Vector^ c = gcnew Vector(wRank);
		c->fitAssign(b);
		b = c;
	}
}