#include "MathHelper.h"

using namespace em::math;
using System::Reflection::BindingFlags;

Scalar^ MathHelper::factorial(int n) {
	double f = 1;
	for (; n > 1; n--) {
		f *= n;
	}

	return gcnew Scalar(f);
}

Scalar^  MathHelper::adjustCosAndSin(Scalar^ scl) {
	double val = Math::Abs(scl);
	if ( val > 1) {
		scl->overrideAssign(Math::Sign(scl) * Math::Floor(val));
	}

	return scl;
}

generic<typename M> where M : MathObject
String^ MathHelper::getGenericMathID() {
	return M::typeid->GetField("ID", BindingFlags::Public | BindingFlags::Static)->GetValue(nullptr)->ToString();
}

generic<typename M> where M : MathObject
String^ MathHelper::getGenericMathType() {
	return M::typeid->GetField("TAG", BindingFlags::Public | BindingFlags::Static)->GetValue(nullptr)->ToString();
}


