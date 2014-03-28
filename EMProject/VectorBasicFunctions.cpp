#include "VectorBasicFunctions.h"

using namespace em::math::engine::expression::functions;


MathObject^ VectorBasicFunctions::mag$V(array<MathObject^>^ mos, Message^% msg) {
	Vector^ v;
	Vector::vectorCast(mos[0], v);
	return gcnew Scalar(v->magnitude);
}

MathObject^ VectorBasicFunctions::normlzd$V(array<MathObject^>^ mos, Message^% msg) {
	Vector^ v;
	Vector::vectorCast(mos[0], v);
	return v->normalized;
}

MathObject^ VectorBasicFunctions::compnt$V_V(array<MathObject^>^ mos, Message^% msg) {
	Vector^ v1, ^ v2;
	Scalar^ compnt;
	Vector::vectorCast(mos[0], v1);
	Vector::vectorCast(mos[1], v2);

	compnt = v1->component(v2);

	return compnt;
}

MathObject^ VectorBasicFunctions::proj$V_V(array<MathObject^>^ mos, Message^% msg) {
	Vector^ v1, ^ v2, ^v3;
	Vector::vectorCast(mos[0], v1);
	Vector::vectorCast(mos[1], v2);

	v3 = v1->projection(v2);

	return v3;
}

MathObject^ VectorBasicFunctions::angle$V_V(array<MathObject^>^ mos, Message^% msg) {
	Vector^ v1, ^ v2;
	Vector::vectorCast(mos[0], v1);
	Vector::vectorCast(mos[1], v2);

	Angle^ angle = gcnew Angle(v1->normalized * v2->normalized);

	return angle;
}
