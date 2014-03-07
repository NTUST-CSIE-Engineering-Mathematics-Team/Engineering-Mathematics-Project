#include "MathObject.h"

using namespace em::math;
MathObject::MathObject(String^ type) : mType(type) {

}
MathObject::~MathObject() {
	delete mType;
}