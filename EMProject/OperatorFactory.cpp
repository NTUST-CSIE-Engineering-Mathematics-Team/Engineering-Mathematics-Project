#include "OperatorFactory.h"

using namespace em::math::engine::expression::operators;


OperatorFactory::OperatorFactory() {
}

OperatorFactory::~OperatorFactory() {
}

BinaryOperator^ OperatorFactory::createOperatorInstance(String^ type, Expression^ a, Expression^ b) {
	return operatorConstructors[type](a, b);
}