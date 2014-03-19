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
	return functionConstructors[name](negative, exps);
}