#include "Vector.h"

using namespace em::math;

Vector::Vector(int dim) : MathObject(tag) {
	this->value = gcnew array<double>(dim);
}

Vector::~Vector() {
	delete this->value;
	
}

Vector^ Vector::operator=(Vector^ vec) {

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