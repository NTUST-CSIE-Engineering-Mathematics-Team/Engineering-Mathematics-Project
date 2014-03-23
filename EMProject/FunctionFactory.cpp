#include "FunctionFactory.h"

using namespace em::math::engine::expression::functions;

FunctionFactory::FunctionFactory() {

}

FunctionFactory::~FunctionFactory() {

}

void FunctionFactory::addFunction(Function::FunctionPerformer^ performer) {
	String^ name = performer->Method->Name;
	if (name->Contains("$")) {
		array<String^>^ nameAndTypes = performer->Method->Name->Split('$');
		functionConstructors->Add(nameAndTypes[0], gcnew FunctionData(nameAndTypes[0], nameAndTypes[1], performer));
	} else {
		functionConstructors->Add(name, gcnew FunctionData(name, nullptr, performer));
	}
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