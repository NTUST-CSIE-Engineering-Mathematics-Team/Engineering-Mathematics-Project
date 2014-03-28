#include "TrigonometricFunctions.h"

using namespace em::math::engine::expression::functions;

MathObject^ TrigonometricFunctions::sin$S(array<MathObject^>^ mos, Message^% msg) {
	Scalar^ scl;
	Scalar::scalarCast(mos[0], scl);
	return gcnew Scalar(Math::Sin(MathHelper::degreeToRadian(scl)));
}

MathObject^ TrigonometricFunctions::cos$S(array<MathObject^>^ mos, Message^% msg) {
	Scalar^ scl;
	Scalar::scalarCast(mos[0], scl);
	return gcnew Scalar(Math::Cos(MathHelper::degreeToRadian(scl)));
}

MathObject^ TrigonometricFunctions::tan$S(array<MathObject^>^ mos, Message^% msg) {
	Scalar^ scl;
	Scalar::scalarCast(mos[0], scl);
	return gcnew Scalar(Math::Tan(MathHelper::degreeToRadian(scl)));
}
