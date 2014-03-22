#include "FunctionFactory.h"

using namespace em::math::engine::expression::functions;

FunctionFactory::FunctionFactory() {

}

FunctionFactory::~FunctionFactory() {

}

bool FunctionFactory::hasFunction(String^ name) {
	return functionConstructors->ContainsKey(name);
}

Function^ FunctionFactory::createFunctionInstance(String^ name, bool negative, array<Expression^>^ exps) {
	FunctionData^ data = functionConstructors[name];
	return gcnew Function(negative, exps, data->name, data->argT, data->performer);
}

FunctionFactory::FunctionData::FunctionData(String^ name, String^ argT, Function::FunctionPerformer^ performer)
	: name(name), argT(argT), performer(performer) {
}

FunctionFactory::FunctionData::~FunctionData() {
	delete name;
	delete argT;
	delete performer;
}