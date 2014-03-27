#include "FunctionFactory.h"

using namespace em::math::engine::expression::functions;

FunctionFactory::FunctionFactory() {

}

FunctionFactory::~FunctionFactory() {

}

void FunctionFactory::addFunction(Function::FunctionPerformer^ performer) {
	String^ name = performer->Method->Name;
	array<String^>^ nameAndTypes = name->Split('$');

	if (!hasFunction(nameAndTypes[0])) {
		functionConstructors->Add(nameAndTypes[0], gcnew Dictionary<String^, Function::FunctionPerformer^>());
	}

	functionConstructors[nameAndTypes[0]]->Add(name, performer);

}

bool FunctionFactory::hasFunction(String^ name) {
	return functionConstructors->ContainsKey(name);
}

Function^ FunctionFactory::createFunctionInstance(String^ name, bool negative, array<Expression^>^ exps) {
	return gcnew Function(negative, exps, name, functionConstructors[name]);
}
