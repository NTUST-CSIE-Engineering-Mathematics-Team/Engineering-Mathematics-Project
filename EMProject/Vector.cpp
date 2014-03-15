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
		sb->Append(", ");
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

void Vector::negate() {
	for (int i = 0; i < this->rank; i++) {
		this[i] = -this[i];
	}
}