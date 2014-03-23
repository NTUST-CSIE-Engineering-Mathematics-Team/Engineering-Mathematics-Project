#include "FunctionFactory.h"

using namespace em::math::engine::expression::functions;

FunctionFactory::FunctionFactory() {

}

FunctionFactory::~FunctionFactory() {

}

void FunctionFactory::addFunction(Function::FunctionPerformer^ performer) {
	String^ name = performer->Method->Name;
	array<String^>^ nameAndTypes = name->Split('$');
	if (nameAndTypes->Length > 1) {
		functionConstructors->Add(nameAndTypes[0], gcnew FunctionData(nameAndTypes[0], nameAndTypes[1]->Split(L'_'), performer));
	} else {
		functionConstructors->Add(name, gcnew FunctionData(name, gcnew array<String^>(0), performer));
	}
}

bool FunctionFactory::hasFunction(String^ name) {
	return functionConstructors->ContainsKey(name);
}

Function^ FunctionFactory::createFunctionInstance(String^ name, bool negative, array<Expression^>^ exps) {
	FunctionData^ data = functionConstructors[name];
	return gcnew Function(negative, exps, data->name, data->argTs, data->performer);
}

FunctionFactory::FunctionData::FunctionData(String^ name, array<String^>^ argTs, Function::FunctionPerformer^ performer)
	: name(name), argTs(argTs), performer(performer) {
}

FunctionFactory::FunctionData::~FunctionData() {
	delete this->name;
	delete this->argTs;
	delete this->performer;
}