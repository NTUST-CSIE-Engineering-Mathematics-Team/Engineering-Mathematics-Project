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

	FunctionFactory::addFunction<MagFunction>();
	FunctionFactory::addFunction<ProjFunction>();
}