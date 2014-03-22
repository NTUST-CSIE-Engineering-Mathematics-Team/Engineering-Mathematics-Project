#include "TrigonometricFunctions.h"

using namespace em::math::engine::expression::functions;

MathObject^ TrigonometricFunctions::sin$S(array<MathObject^>^ mos, Message^% msg) {
	Scalar^ scl;
	Scalar::scalarCast(mos[0], scl);
	return gcnew Scalar(Math::Sin(scl * Math::PI / 180));
}

MathObject^ TrigonometricFunctions::cos$S(array<MathObject^>^ mos, Message^% msg) {
	Scalar^ scl;
	Scalar::scalarCast(mos[0], scl);
	return gcnew Scalar(Math::Cos(scl * Math::PI / 180));
}

MathObject^ TrigonometricFunctions::tan$S(array<MathObject^>^ mos, Message^% msg) {
	Scalar^ scl;
	Scalar::scalarCast(mos[0], scl);
	return gcnew Scalar(Math::Tan(scl * Math::PI / 180));
}
