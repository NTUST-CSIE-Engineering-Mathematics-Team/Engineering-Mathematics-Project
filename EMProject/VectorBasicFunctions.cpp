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

	if (compnt == nullptr) {
		msg = differentRankErrMsg();
	}

	return compnt;
}

MathObject^ VectorBasicFunctions::proj$V_V(array<MathObject^>^ mos, Message^% msg) {
	Vector^ v1, ^ v2, ^v3;
	Vector::vectorCast(mos[0], v1);
	Vector::vectorCast(mos[1], v2);

	v3 = v1->projection(v2);

	if (v3 == nullptr) {
		msg = differentRankErrMsg();
	}

	return v3;
}

MathObject^ VectorBasicFunctions::angle$V_V(array<MathObject^>^ mos, Message^% msg) {
	Vector^ v1, ^ v2;
	Vector::vectorCast(mos[0], v1);
	Vector::vectorCast(mos[1], v2);

	Scalar^ cos = v1->normalized * v2->normalized;

	if (cos == nullptr) {
		msg = differentRankErrMsg();
		return nullptr;
	}


	return gcnew Angle(Math::Acos(cos));
}

MathObject^ VectorBasicFunctions::tri_area$V_V(array<MathObject^>^ mos, Message^% msg) {
	Vector^ v1, ^ v2;
	Vector::vectorCast(mos[0], v1);
	Vector::vectorCast(mos[1], v2);

	Scalar^ cos = v1->normalized * v2->normalized;

	if (cos == nullptr) {
		msg = differentRankErrMsg();
		return nullptr;
	}
	
	return gcnew Scalar(0.5 * v1->magnitude * v2->magnitude * Math::Sin(Math::Acos(cos)));
}

MathObject^ VectorBasicFunctions::is_pallel$V_V(array<MathObject^>^ mos, Message^% msg) {
	Vector^ v1, ^ v2;
	Vector::vectorCast(mos[0], v1);
	Vector::vectorCast(mos[1], v2);

	Scalar^ cos = v1->normalized * v2->normalized;
	
	if (cos == nullptr) {
		msg = differentRankErrMsg();
		return nullptr;
	}


	return ((1 - Math::Abs(cos)) < MathHelper::EPSILON) ? v2 : nullptr;

}

MathObject^ VectorBasicFunctions::is_orth$V_V(array<MathObject^>^ mos, Message^% msg) {
	Vector^ v1, ^ v2;
	Vector::vectorCast(mos[0], v1);
	Vector::vectorCast(mos[1], v2);

	Scalar^ cos = v1->normalized * v2->normalized;

	if (cos == nullptr) {
		msg = differentRankErrMsg();
		return nullptr;
	}

	return (Math::Abs(cos) < MathHelper::EPSILON) ? v2 : nullptr;

}

Message^ VectorBasicFunctions::differentRankErrMsg() {
	return gcnew Message(Message::State::ERROR, "vectors with different ranks cannot perform vector operation function");
}