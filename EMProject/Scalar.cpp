#include "Scalar.h"

using namespace em::math;
using System::Text::StringBuilder;
Scalar::Scalar(double v) : MathObject(TAG, ID), value(v) {
}

Scalar::Scalar(Scalar^ scl) : MathObject(TAG, ID) {
	this->overrideAssign(scl);
}

Scalar::~Scalar() {
}

String^ Scalar::getHeader() {
	return TAG;
}

String^ Scalar::ToString() {
	StringBuilder^ sb = gcnew StringBuilder(getHeader());
	sb->AppendFormat("\n{0}", System::String::Format(NUMERAL_FORMAT, this->value));
	
	return sb->ToString();
}

Scalar^ Scalar::overrideAssign(Scalar^ scl) {
	return this->overrideAssign(scl->value);
}

Scalar^ Scalar::overrideAssign(double val) {
	this->value = val;
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

Scalar^ Scalar::clone() {
	return gcnew Scalar(this);
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