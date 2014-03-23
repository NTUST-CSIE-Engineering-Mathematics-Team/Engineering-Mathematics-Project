#include "Scalar.h"

using namespace em::math;

Scalar::Scalar(double v) : MathObject(TAG, ID), value(v) {
}

Scalar::Scalar(Scalar^ scl) : MathObject(TAG, ID) {
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

MathObject^ Scalar::overrideAssign(MathObject^ mo) {
	Scalar^ tmp;
	if (!scalarCast(mo, tmp)) {
		return nullptr;
	}

	return this->overrideAssign(tmp);
}


Scalar::operator double() {
	return this->value;
}

bool Scalar::scalarCast(MathObject^ mo, Scalar^% scl) {
	scl = dynamic_cast<Scalar^>(mo);
	return scl != nullptr;
}

MathObject^ Scalar::operator-() {
	return gcnew Scalar(-this->value);
}


Scalar^ Scalar::operator-(Scalar^ s) {
	return gcnew Scalar(this->value - s->value);
}

Scalar^ Scalar::operator+(Scalar^ s) {
	return gcnew Scalar(this->value + s->value);
}

Scalar^ Scalar::operator*(Scalar^ s) {
	return gcnew Scalar(this->value * s->value);
}

Scalar^ Scalar::operator/(Scalar^ s) {
	return gcnew Scalar(this->value / s->value);
}