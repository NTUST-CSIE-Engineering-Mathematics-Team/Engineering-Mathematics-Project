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
