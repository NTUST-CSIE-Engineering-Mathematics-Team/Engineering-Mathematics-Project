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

	return MathHelper::radianToDegree(System::Math::Acos(cos));
}

MathObject^ VectorBasicFunctions::pallel$V_VC(array<MathObject^>^ mos, Message^% msg) {
	Vector^ vec;
	MathObjGenericSet<Vector^>^ set;
	Vector::vectorCast(mos[0], vec);
	MathObjGenericSet<Vector^>::gSetCast(mos[1], set);

	MathObjGenericSet<Vector^>^ result = gcnew MathObjGenericSet<Vector^>(vec->mathID);
	double theta;
	for each(Vector^ op in set) {
		theta = 1- Math::Abs(vec->normalized * op->normalized);

		if (theta < MathHelper::EPSILON) {
			result->add(op);
		}
		
	}

	return result;
}

Message^ VectorBasicFunctions::differentRankErrMsg() {
	return gcnew Message(Message::State::ERROR, "vectors with different ranks cannot perform vector operation function");
}