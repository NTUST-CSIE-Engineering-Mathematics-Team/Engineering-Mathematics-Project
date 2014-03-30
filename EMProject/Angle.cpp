#include "Angle.h"

using namespace em::math;
using System::Text::StringBuilder;
Angle::Angle(double radian) : Angle(radian, false) {

}
Angle::Angle(double radian, bool isDegree) : MathObject(TAG, ID), rAngle(isDegree ? radian * RD_RATIO : radian) {

}
Angle::Angle(Angle^ angle) : MathObject(TAG, ID) {
	overrideAssign(angle);
}

Angle::Angle(Scalar^ degree) : MathObject(TAG, ID) {
	overrideAssign(degree);
}

Angle::~Angle() {
	
}

String^ Angle::getHeader() {
	return TAG;
}

String^ Angle::ToString() {
	StringBuilder^ sb = gcnew StringBuilder(getHeader());
	sb->AppendFormat("\n{0}¢X ({1}£k)", System::String::Format(NUMERAL_FORMAT, this->degree),
									System::String::Format("{0:F" + MathObject::numPrecision + "}", this->radian / Math::PI));
	return sb->ToString();
}

Angle^ Angle::overrideAssign(Angle^ angle) {
	return this->overrideAssign(angle->rAngle);
}

Angle^ Angle::overrideAssign(Scalar^ degree) {
	this->rAngle = degree->doubleValue * RD_RATIO;
	return this;
}

Angle^ Angle::overrideAssign(double radian) {
	this->rAngle = radian;
	return this;
}


MathObject^ Angle::overrideAssign(MathObject^ mo) {
	Angle^ tmp;
	if (!angleCast(mo, tmp)) {
		return nullptr;
	}

	return this->overrideAssign(tmp);
}


Angle::operator double() {
	return this->radian;
}

bool Angle::angleCast(MathObject^ mo, Angle^% angle) {
	angle = dynamic_cast<Angle^>(mo);
	return angle != nullptr;
}

MathObject^ Angle::operator-() {
	return gcnew Angle(-this->rAngle);
}

Angle^ Angle::operator-(Angle^ a) {
	return gcnew Angle(this->radian - a->radian);
}

Angle^ Angle::operator+(Angle^ a) {
	return gcnew Angle(this->radian + a->radian);
}

Angle^ Angle::operator*(Scalar^ s) {
	return gcnew Angle(this->radian * s);
}

Angle^ Angle::operator/(Scalar^ s) {
	return gcnew Angle(this->radian / s);
}