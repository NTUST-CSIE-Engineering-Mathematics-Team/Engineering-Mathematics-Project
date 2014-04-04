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
		msg = differentDimErrMsg("compnt");
	}

	return compnt;
}

MathObject^ VectorBasicFunctions::proj$V_V(array<MathObject^>^ mos, Message^% msg) {
	Vector^ v1, ^ v2, ^v3;
	Vector::vectorCast(mos[0], v1);
	Vector::vectorCast(mos[1], v2);

	v3 = v1->projection(v2);

	if (v3 == nullptr) {
		msg = differentDimErrMsg("proj");
	}

	return v3;
}

MathObject^ VectorBasicFunctions::angle$V_V(array<MathObject^>^ mos, Message^% msg) {
	Vector^ v1, ^ v2;
	Vector::vectorCast(mos[0], v1);
	Vector::vectorCast(mos[1], v2);

	Scalar^ cos = MathHelper::adjustCosAndSin(v1->normalized * v2->normalized);

	if (cos == nullptr) {
		msg = differentDimErrMsg("angle");
		return nullptr;
	}


	return gcnew Angle(Math::Acos(cos));
}

MathObject^ VectorBasicFunctions::tri_area$V_V(array<MathObject^>^ mos, Message^% msg) {
	Vector^ v1, ^ v2;
	Vector::vectorCast(mos[0], v1);
	Vector::vectorCast(mos[1], v2);

	Scalar^ cos = MathHelper::adjustCosAndSin(v1->normalized * v2->normalized);

	if (cos == nullptr) {
		msg = differentDimErrMsg("tri_area");
		return nullptr;
	}
	System::Diagnostics::Debug::WriteLine(Math::Sin(Math::Acos(cos)));
	return gcnew Scalar(0.5 * v1->magnitude * v2->magnitude * Math::Sin(Math::Acos(cos)));
}

MathObject^ VectorBasicFunctions::is_pallel$V_V(array<MathObject^>^ mos, Message^% msg) {
	Vector^ v1, ^ v2;
	Vector::vectorCast(mos[0], v1);
	Vector::vectorCast(mos[1], v2);

	Scalar^ cos = MathHelper::adjustCosAndSin(v1->normalized * v2->normalized);
	
	if (cos == nullptr) {
		msg = differentDimErrMsg("is_pallel");
		return nullptr;
	}

	if ((1 - Math::Abs(cos)) < MathHelper::EPSILON) {
		msg = gcnew Message(Message::State::PASS, Message::JUDGE_PASS_COLOR, "Two vectors are parallel to each other");
	} else {
		msg = gcnew Message(Message::State::PASS, Message::JUDGE_NOT_PASS_COLOR, "Two vectors are not parallel to each other");
	}
	return  nullptr;

}

MathObject^ VectorBasicFunctions::is_orth$V_V(array<MathObject^>^ mos, Message^% msg) {
	Vector^ v1, ^ v2;
	Vector::vectorCast(mos[0], v1);
	Vector::vectorCast(mos[1], v2);

	Scalar^ cos = MathHelper::adjustCosAndSin(v1->normalized * v2->normalized);

	if (cos == nullptr) {
		msg = differentDimErrMsg("is_orth");
		return nullptr;
	}

	if (Math::Abs(cos) < MathHelper::EPSILON) {
		msg = gcnew Message(Message::State::PASS, Message::JUDGE_PASS_COLOR, "Two vectors are perpendicular to each other");
	} else {
		msg = gcnew Message(Message::State::PASS, Message::JUDGE_NOT_PASS_COLOR, "Two vectors are not perpendicular to each other");
	}

	return nullptr;

}

MathObject^ VectorBasicFunctions::plane_norm$V_V(array<MathObject^>^ mos, Message^% msg) {
	Vector^ v1, ^ v2, ^v3;
	Vector::vectorCast(mos[0], v1);
	Vector::vectorCast(mos[1], v2);

	v3 = v1->cross(v2);

	if (v3 == nullptr) {
		msg = gcnew Message(Message::State::ERROR, "The ranks of vectors is invaild, it cannot be more than 3 or they have different ranks");
		return nullptr;
	}

	return v3;

}
Message^ VectorBasicFunctions::differentDimErrMsg(String^ funName) {
	return gcnew Message(Message::State::ERROR, "Cannot perform function \"" + funName + "\" on vectors with different dimensions");
}
