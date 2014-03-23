#include "MathHelper.h"

using namespace em::math;

double MathHelper::degreeToRadian(Scalar^ d) {
	return d * Math::PI / 180;
}

Scalar^ MathHelper::radianToDegree(double r) {
	return gcnew Scalar(r * 180 / Math::PI);
}

		


