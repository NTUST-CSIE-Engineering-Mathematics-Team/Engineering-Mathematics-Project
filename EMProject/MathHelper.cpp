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
		
generic<typename M> where M : MathObject
String^ MathHelper::getGenericMathID() {
	return M::typeid->GetField("ID", BindingFlags::Public | BindingFlags::Static)->GetValue(nullptr)->ToString();
}

generic<typename M> where M : MathObject
String^ MathHelper::getGenericMathType() {
	return M::typeid->GetField("TAG", BindingFlags::Public | BindingFlags::Static)->GetValue(nullptr)->ToString();
}


