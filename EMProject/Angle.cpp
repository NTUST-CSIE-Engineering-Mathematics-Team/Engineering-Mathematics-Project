#include "Angle.h"

using namespace em::math;
using System::Text::StringBuilder;
Angle::Angle(double radian) : MathObject(TAG, ID), rAngle(radian) {

}

Angle::Angle(Angle^ degree) : MathObject(TAG, ID) {
	overrideAssign(degree);
}

Angle::Angle(Scalar^ radian) : MathObject(TAG, ID) {
	overrideAssign(radian);
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

Angle^ Angle::overrideAssign(Scalar^ angle) {
	this->rAngle = angle->doubleValue * Math::PI / 180;
	return this;
}

Angle^ Angle::overrideAssign(double val) {
	this->rAngle = val;
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
	return this->rAngle;
}

bool Angle::angleCast(MathObject^ mo, Angle^% angle) {
	angle = dynamic_cast<Angle^>(mo);
	return angle != nullptr;
}

MathObject^ Angle::operator-() {
	return gcnew Angle(-this->rAngle);
}
