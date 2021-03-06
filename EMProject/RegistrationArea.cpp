#include "RegistrationArea.h"

using namespace em::intrprt;
void RegistrationArea::registerHere() {
	CommandFactory::addCommand<PrintCommand^>();
	CommandFactory::addCommand<OptionCommand^>();
	CommandFactory::addCommand<DeleteCommand^>();
	CommandFactory::addCommand<ShowStorageCommand^>();

	OperatorFactory::addOperation<AdditionOperator>();
	OperatorFactory::addOperation<SubtractionOperator>();
	OperatorFactory::addOperation<MultiplicationOperator>();
	OperatorFactory::addOperation<DivisionOperator>();
	OperatorFactory::addOperation<CrossProductOperator>();

	FunctionFactory::addFunction(gcnew Function::FunctionPerformer(&ScalarBasicFunctions::pow$S_S));
	FunctionFactory::addFunction(gcnew Function::FunctionPerformer(&ScalarBasicFunctions::sqrt$S));

	FunctionFactory::addFunction(gcnew Function::FunctionPerformer(&TrigonometricFunctions::angle$S));
	FunctionFactory::addFunction(gcnew Function::FunctionPerformer(&TrigonometricFunctions::sin$A));
	FunctionFactory::addFunction(gcnew Function::FunctionPerformer(&TrigonometricFunctions::cos$A));
	FunctionFactory::addFunction(gcnew Function::FunctionPerformer(&TrigonometricFunctions::tan$A));
	FunctionFactory::addFunction(gcnew Function::FunctionPerformer(&TrigonometricFunctions::asin$S));
	FunctionFactory::addFunction(gcnew Function::FunctionPerformer(&TrigonometricFunctions::acos$S));
	FunctionFactory::addFunction(gcnew Function::FunctionPerformer(&TrigonometricFunctions::atan$S));

	FunctionFactory::addFunction(gcnew Function::FunctionPerformer(&VectorBasicFunctions::to_vec$M));
	FunctionFactory::addFunction(gcnew Function::FunctionPerformer(&VectorBasicFunctions::mag$V));
	FunctionFactory::addFunction(gcnew Function::FunctionPerformer(&VectorBasicFunctions::proj$V_V));
	FunctionFactory::addFunction(gcnew Function::FunctionPerformer(&VectorBasicFunctions::compnt$V_V));
	FunctionFactory::addFunction(gcnew Function::FunctionPerformer(&VectorBasicFunctions::normlzd$V));
	FunctionFactory::addFunction(gcnew Function::FunctionPerformer(&VectorBasicFunctions::angle$V_V));
	FunctionFactory::addFunction(gcnew Function::FunctionPerformer(&VectorBasicFunctions::tri_area$V_V));
	FunctionFactory::addFunction(gcnew Function::FunctionPerformer(&VectorBasicFunctions::is_pallel$V_V));
	FunctionFactory::addFunction(gcnew Function::FunctionPerformer(&VectorBasicFunctions::is_orth$V_V));
	FunctionFactory::addFunction(gcnew Function::FunctionPerformer(&VectorBasicFunctions::plane_norm$V_V));
	FunctionFactory::addFunction(gcnew Function::FunctionPerformer(&VectorBasicFunctions::is_linear_ind$VC));
	FunctionFactory::addFunction(gcnew Function::FunctionPerformer(&VectorBasicFunctions::gs_orth_process$VC));

	FunctionFactory::addFunction(gcnew Function::FunctionPerformer(&MatrixBasicFunctions::to_mat_v$VC));
	FunctionFactory::addFunction(gcnew Function::FunctionPerformer(&MatrixBasicFunctions::to_mat_h$VC));
	FunctionFactory::addFunction(gcnew Function::FunctionPerformer(&MatrixBasicFunctions::transpose$M));
	FunctionFactory::addFunction(gcnew Function::FunctionPerformer(&MatrixBasicFunctions::row_ech$M));
	FunctionFactory::addFunction(gcnew Function::FunctionPerformer(&MatrixBasicFunctions::solve_linear$M_V));
	FunctionFactory::addFunction(gcnew Function::FunctionPerformer(&MatrixBasicFunctions::solve_linear$M_M));
	FunctionFactory::addFunction(gcnew Function::FunctionPerformer(&MatrixBasicFunctions::inverse$M));
	FunctionFactory::addFunction(gcnew Function::FunctionPerformer(&MatrixBasicFunctions::det$M));
	FunctionFactory::addFunction(gcnew Function::FunctionPerformer(&MatrixBasicFunctions::rank$M));
	FunctionFactory::addFunction(gcnew Function::FunctionPerformer(&MatrixBasicFunctions::adj$M));
	FunctionFactory::addFunction(gcnew Function::FunctionPerformer(&MatrixBasicFunctions::ul_decom$M));
	FunctionFactory::addFunction(gcnew Function::FunctionPerformer(&MatrixBasicFunctions::pow$M_S));
	FunctionFactory::addFunction(gcnew Function::FunctionPerformer(&MatrixBasicFunctions::least_square$M_M));
	FunctionFactory::addFunction(gcnew Function::FunctionPerformer(&MatrixBasicFunctions::eigen$M));
	FunctionFactory::addFunction(gcnew Function::FunctionPerformer(&MatrixBasicFunctions::power_eigen$M));

	FunctionFactory::addFunction(gcnew Function::FunctionPerformer(&GetAccessFunctions::get$V_S));
	FunctionFactory::addFunction(gcnew Function::FunctionPerformer(&GetAccessFunctions::get$M_S_S));
	FunctionFactory::addFunction(gcnew Function::FunctionPerformer(&GetAccessFunctions::get$SC_S));
	FunctionFactory::addFunction(gcnew Function::FunctionPerformer(&GetAccessFunctions::get$AC_S));
	FunctionFactory::addFunction(gcnew Function::FunctionPerformer(&GetAccessFunctions::get$VC_S));
	FunctionFactory::addFunction(gcnew Function::FunctionPerformer(&GetAccessFunctions::get$MC_S));
	FunctionFactory::addFunction(gcnew Function::FunctionPerformer(&GetAccessFunctions::get$CC_S));
	FunctionFactory::addFunction(gcnew Function::FunctionPerformer(&GetAccessFunctions::subset$SC_S_S));
	FunctionFactory::addFunction(gcnew Function::FunctionPerformer(&GetAccessFunctions::subset$AC_S_S));
	FunctionFactory::addFunction(gcnew Function::FunctionPerformer(&GetAccessFunctions::subset$VC_S_S));
	FunctionFactory::addFunction(gcnew Function::FunctionPerformer(&GetAccessFunctions::subset$MC_S_S));
	FunctionFactory::addFunction(gcnew Function::FunctionPerformer(&GetAccessFunctions::subset$CC_S_S));
}