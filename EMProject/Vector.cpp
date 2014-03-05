#include "Vector.h"

using em::math::Vector;

Vector::Vector(int dim) {
	this->values = gcnew array<double>(dim);
}

Vector::~Vector() {
	delete this->values;
	
}