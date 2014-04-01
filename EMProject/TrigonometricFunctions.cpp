#include "TrigonometricFunctions.h"

using namespace em::math::engine::expression::functions;

MathObject^ TrigonometricFunctions::angle$S(array<MathObject^>^ mos, Message^% msg) {
	Scalar^ scl;
	Scalar::scalarCast(mos[0], scl);
	return gcnew Angle(scl);
}

MathObject^ TrigonometricFunctions::sin$A(array<MathObject^>^ mos, Message^% msg) {
	Angle^ agl;
	Angle::angleCast(mos[0], agl);
	return gcnew Scalar(Math::Sin(agl->radian));
}

MathObject^ TrigonometricFunctions::cos$A(array<MathObject^>^ mos, Message^% msg) {
	Angle^ agl;
	Angle::angleCast(mos[0], agl);
	return gcnew Scalar(Math::Cos(agl->radian));
}

MathObject^ TrigonometricFunctions::tan$A(array<MathObject^>^ mos, Message^% msg) {
	Angle^ agl;
	Angle::angleCast(mos[0], agl);
	return gcnew Scalar(Math::Tan(agl->radian));
}

MathObject^ TrigonometricFunctions::asin$S(array<MathObject^>^ mos, Message^% msg) {
	Scalar^ sin;
	Scalar::scalarCast(mos[0], sin);
	return gcnew Angle(Math::Asin(sin));
}

MathObject^ TrigonometricFunctions::acos$S(array<MathObject^>^ mos, Message^% msg) {
	Scalar^ cos;
	Scalar::scalarCast(mos[0], cos);
	return gcnew Angle(Math::Acos(cos));
}

MathObject^ TrigonometricFunctions::atan$S(array<MathObject^>^ mos, Message^% msg) {
	Scalar^ tan;
	Scalar::scalarCast(mos[0], tan);
	return gcnew Angle(Math::Atan(tan));
}
