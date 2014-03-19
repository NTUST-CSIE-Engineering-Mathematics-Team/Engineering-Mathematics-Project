#include "MathObject.h"

using namespace em::math;
MathObject::MathObject(String^ type, wchar_t mID) : mType(type), mID(mID) {
}

MathObject::~MathObject() {
	delete mType;
}


