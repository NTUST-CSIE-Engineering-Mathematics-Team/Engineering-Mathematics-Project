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

MathObject^ VectorBasicFunctions::proj$V_V(array<MathObject^>^ mos, Message^% msg) {
	Vector^ v1, ^ v2;
	Vector::vectorCast(mos[0], v1);
	Vector::vectorCast(mos[1], v2);
	return v1->projection(v2);
}

