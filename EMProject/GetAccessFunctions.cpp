#include "GetAccessFunctions.h"

using namespace em::math::engine::expression::functions;
MathObject^ GetAccessFunctions::get$V_S(array<MathObject^>^ mos, Message^% msg) {
	Vector^ vec;
	Scalar^ index;
	Vector::vectorCast(mos[0], vec);
	Scalar::scalarCast(mos[1], index);

	if (!index->isInteger) {
		msg = indexIntErrMsg;
		return nullptr;
	}

	if (index >= vec->dimension) {
		msg = indexOBErrMsg;
		return nullptr;
	}
	return gcnew Scalar(vec[index->toInteger()]);
}
MathObject^ GetAccessFunctions::get$M_S_S(array<MathObject^>^ mos, Message^% msg){
	Matrix^ mat;
	Scalar^ index1, ^ index2;
	Matrix::matrixCast(mos[0], mat);
	
	Scalar::scalarCast(mos[1], index1);
	Scalar::scalarCast(mos[2], index2);

	if (!index1->isInteger || !index2->isInteger) {
		msg = indexIntErrMsg;
		return nullptr;
	}

	if (index1 >= mat->columnLength || index2 >= mat->rowLength) {
		msg = indexOBErrMsg;
		return nullptr;
	}
	return gcnew Scalar(mat[index1->toInteger(), index2->toInteger()]);
}
MathObject^ GetAccessFunctions::get$SC_S(array<MathObject^>^ mos, Message^% msg){
	return getSetElement(mos[0], mos[1], msg);
}
MathObject^ GetAccessFunctions::get$AC_S(array<MathObject^>^ mos, Message^% msg){
	return getSetElement(mos[0], mos[1], msg);
}
MathObject^ GetAccessFunctions::get$VC_S(array<MathObject^>^ mos, Message^% msg){
	return getSetElement(mos[0], mos[1], msg);
}
MathObject^ GetAccessFunctions::get$MC_S(array<MathObject^>^ mos, Message^% msg){
	return getSetElement(mos[0], mos[1], msg);
}
MathObject^ GetAccessFunctions::get$CC_S(array<MathObject^>^ mos, Message^% msg){
	return getSetElement(mos[0], mos[1], msg);
}
MathObject^ GetAccessFunctions::getSetElement(MathObject^ set, MathObject^ i, Message^% msg) {
	MathObjSet^ mos;
	Scalar^ index;
	MathObjSet::setCast(set, mos);
	Scalar::scalarCast(i, index);
	if (!index->isInteger) {
		msg = indexIntErrMsg;
		return nullptr;
	}

	MathObject^ mo = mos->mathObject[index->toInteger()];
	if (mo == nullptr) {
		msg = indexOBErrMsg;
	}
	return mo;
}

MathObject^ GetAccessFunctions::subset$SC_S_S(array<MathObject^>^ mos, Message^% msg){
	return getsubSet(mos[0], mos[1], mos[2], msg);
}
MathObject^ GetAccessFunctions::subset$AC_S_S(array<MathObject^>^ mos, Message^% msg) {
	return getsubSet(mos[0], mos[1], mos[2], msg);
}
MathObject^ GetAccessFunctions::subset$VC_S_S(array<MathObject^>^ mos, Message^% msg) {
	return getsubSet(mos[0], mos[1], mos[2], msg);
}
MathObject^ GetAccessFunctions::subset$MC_S_S(array<MathObject^>^ mos, Message^% msg) {
	return getsubSet(mos[0], mos[1], mos[2], msg);
}
MathObject^ GetAccessFunctions::subset$CC_S_S(array<MathObject^>^ mos, Message^% msg) {
	return getsubSet(mos[0], mos[1], mos[2], msg);
}
MathObject^ GetAccessFunctions::getsubSet(MathObject^ set, MathObject^ i, MathObject^ j, Message^% msg) {
	MathObjSet^ mos;
	Scalar^ index1, ^ index2;
	MathObjSet::setCast(set, mos);
	Scalar::scalarCast(i, index1);
	Scalar::scalarCast(j, index2);
	if (!index1->isInteger || !index2->isInteger) {
		msg = indexIntErrMsg;
		return nullptr;
	}
	MathObject^ mo = mos->subset[index1->toInteger(), index2->toInteger()];
	if (mo == nullptr) {
		msg = indexOBErrMsg;
	}
	return mo;
}
