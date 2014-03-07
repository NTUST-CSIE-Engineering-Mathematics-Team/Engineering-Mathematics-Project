#include "Vector.h"

using namespace em::math;

Vector::Vector(int dim) : MathObject("Vector") {
	this->value = gcnew array<double>(dim);
}

Vector::~Vector() {
	delete this->value;
	
}

String^ Vector::toString() {
	StringBuilder^ sb = gcnew StringBuilder("< ");

	int i;
	for (i = 0; i < this->value->Length - 1; i++) {
		sb->Append(this[i]);
		sb->Append(", ");
	}
	sb->Append(this[i]);
	sb->Append(" >");

	String^ result = sb->ToString();
	delete sb;
	return result;
}