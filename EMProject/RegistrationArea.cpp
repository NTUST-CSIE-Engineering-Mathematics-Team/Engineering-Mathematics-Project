#include "RegistrationArea.h"

using namespace em::intrprt;
void RegistrationArea::registerHere() {
	CommandFactory::addCommand<PrintCommand^>();
	CommandFactory::addCommand<CreateMatrixCommand^>();
	CommandFactory::addCommand<CreateVectorCommand^>();
	CommandFactory::addCommand<CreateScalarCommand^>();
	CommandFactory::addCommand<SettingsCommand^>();
	CommandFactory::addCommand<DeleteCommand^>();
	CommandFactory::addCommand<ShowStorageCommand^>();
	//CommandFactory::addCommand<JudgeCommand^>();

	OperatorFactory::addOperation<AdditionOperator>("+");
	OperatorFactory::addOperation<SubtractionOperator>("-");
	OperatorFactory::addOperation<MultiplicationOperator>("*");
	OperatorFactory::addOperation<DivisionOperator>("/");
	OperatorFactory::addOperation<CrossProductOperator>("x");

	FunctionFactory::addFunction<MagFunction>("mag");
	FunctionFactory::addFunction<ProjFunction>("proj");
}