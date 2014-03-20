#include "MathObject.h"

using namespace em::math;
MathObject::MathObject(String^ type, String^  mID) : mType(type), mID(mID) {
}

MathObject::~MathObject() {
	delete mType;
}


