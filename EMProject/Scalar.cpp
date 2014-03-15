#include "Scalar.h"

using namespace em::math;

Scalar::Scalar(double v) : MathObject(tag), value(v) {
}

Scalar::Scalar(Scalar^ scl) : MathObject(tag) {
	this->overrideAssign(scl);
}

Scalar::~Scalar() {
}

String^ Scalar::ToString() {
	return System::String::Format(NUMERAL_FORMAT, this->value);
}

Scalar^ Scalar::overrideAssign(Scalar^ scl) {
	this->value = scl->value;
	return this;
}

Scalar::operator double() {
	return this->value;
}

bool Scalar::scalarCast(MathObject^ mo, Scalar^% scl) {
	scl = dynamic_cast<Scalar^>(mo);
	return scl != nullptr;


void Scalar::negate() {
	this->value = -this->value;
}