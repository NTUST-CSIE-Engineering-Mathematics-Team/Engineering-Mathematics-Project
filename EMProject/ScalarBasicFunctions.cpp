#include "ScalarBasicFunctions.h"

using namespace em::math::engine::expression::functions;

MathObject^ ScalarBasicFunctions::pow$S_S(array<MathObject^>^ mos, Message^% msg) {
	Scalar^ s1,^ s2;
	Scalar::scalarCast(mos[0], s1);
	Scalar::scalarCast(mos[1], s2);
	return gcnew Scalar(Math::Pow(s1, s2));
}

MathObject^ ScalarBasicFunctions::test(array<MathObject^>^ mos, Message^% msg) {
	
	return gcnew Scalar(MathHelper::EPSILON);
}