#include "MathHelper.h"

using namespace em::math;
using System::Reflection::BindingFlags;


		
generic<typename M> where M : MathObject
String^ MathHelper::getGenericMathID() {
	return M::typeid->GetField("ID", BindingFlags::Public | BindingFlags::Static)->GetValue(nullptr)->ToString();
}

generic<typename M> where M : MathObject
String^ MathHelper::getGenericMathType() {
	return M::typeid->GetField("TAG", BindingFlags::Public | BindingFlags::Static)->GetValue(nullptr)->ToString();
}


