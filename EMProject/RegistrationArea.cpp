#include "RegistrationArea.h"

using namespace em::intrprt;
void RegistrationArea::registerHere() {
	CommandFactory::addCommand<PrintCommand^>();
	CommandFactory::addCommand<SettingsCommand^>();
	CommandFactory::addCommand<DeleteCommand^>();
	CommandFactory::addCommand<ShowStorageCommand^>();
	CommandFactory::addCommand<JudgeCommand^>();

	OperatorFactory::addOperation<AdditionOperator>();
	OperatorFactory::addOperation<SubtractionOperator>();
	OperatorFactory::addOperation<MultiplicationOperator>();
	OperatorFactory::addOperation<DivisionOperator>();
	OperatorFactory::addOperation<CrossProductOperator>();

	FunctionFactory::addFunction(gcnew Function::FunctionPerformer(&ScalarBasicFunctions::pow$S_S));
	FunctionFactory::addFunction(gcnew Function::FunctionPerformer(&ScalarBasicFunctions::sqrt$S));
	FunctionFactory::addFunction(gcnew Function::FunctionPerformer(&ScalarBasicFunctions::test));

	FunctionFactory::addFunction(gcnew Function::FunctionPerformer(&TrigonometricFunctions::angle$S));
	FunctionFactory::addFunction(gcnew Function::FunctionPerformer(&TrigonometricFunctions::sin$A));
	FunctionFactory::addFunction(gcnew Function::FunctionPerformer(&TrigonometricFunctions::cos$A));
	FunctionFactory::addFunction(gcnew Function::FunctionPerformer(&TrigonometricFunctions::tan$A));
	FunctionFactory::addFunction(gcnew Function::FunctionPerformer(&TrigonometricFunctions::asin$S));
	FunctionFactory::addFunction(gcnew Function::FunctionPerformer(&TrigonometricFunctions::acos$S));
	FunctionFactory::addFunction(gcnew Function::FunctionPerformer(&TrigonometricFunctions::atan$S));

	FunctionFactory::addFunction(gcnew Function::FunctionPerformer(&VectorBasicFunctions::mag$V));
	FunctionFactory::addFunction(gcnew Function::FunctionPerformer(&VectorBasicFunctions::proj$V_V));
	FunctionFactory::addFunction(gcnew Function::FunctionPerformer(&VectorBasicFunctions::compnt$V_V));
	FunctionFactory::addFunction(gcnew Function::FunctionPerformer(&VectorBasicFunctions::normlzd$V));
	FunctionFactory::addFunction(gcnew Function::FunctionPerformer(&VectorBasicFunctions::angle$V_V));

	FunctionFactory::addFunction(gcnew Function::FunctionPerformer(&MatrixBasicFunctions::transpose$M));
	FunctionFactory::addFunction(gcnew Function::FunctionPerformer(&MatrixBasicFunctions::pow$M_S));
}