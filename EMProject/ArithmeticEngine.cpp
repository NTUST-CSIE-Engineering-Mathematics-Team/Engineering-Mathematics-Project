#include "ArithmeticEngine.h"
#include "All_Math.h"


using namespace em::math::engine;
using namespace System::Text::RegularExpressions;
using em::math::MathObject;

ArithmeticEngine::ArithmeticEngine() {
	root = nullptr;
}


ArithmeticEngine::~ArithmeticEngine() {
}


bool ArithmeticEngine::analyze(String^ expression, VariableTable^ vTable, Message^% msg) {
	this->root = this->anaylzeCompoundExpression(expression, vTable);
	if (this->root == nullptr) {
		msg = gcnew Message(Message::State::ERROR, "The arithmetic expression have some errors, perhaps caused by wrong arithmetic syntax or wrong function call");
		return false;
	}
	return true;
}

Expression^ ArithmeticEngine::anaylzeCompoundExpression(String^ expression, VariableTable^ vTable) {
	 Match^ match = this->COMPOUND_EXP_REGEX->Match(expression);

	 if (!match->Success) {
		 return nullptr;
	 }

	GroupCollection^ groups = match->Groups;
	if (!ArithmeticEngine::isParentheseBalanced(groups)) {
		return nullptr;
	}

	LinkedList<Expression^>^ opnds;
	LinkedList<BinaryOperator^>^ optors;
	if (!loadTokens(groups, vTable, opnds, optors)) {
		return nullptr;
	}

	String^ lowPriorityOptor = "+-";
	LinkedListNode<Expression^>^ rndNode = opnds->First;
	LinkedListNode<Expression^>^ preRndNode;
	LinkedListNode<BinaryOperator^>^ torNode = optors->First;
	LinkedListNode<BinaryOperator^>^ preTorNode;
	
	for (; torNode != nullptr;) {
		if (!lowPriorityOptor->Contains(torNode->Value->operatorSymbol)) {
			this->CombineNodes(opnds, optors, rndNode, torNode, preRndNode, preTorNode);
		} else {
			rndNode = rndNode->Next;
			torNode = torNode->Next;
		}
	}

	for (rndNode = opnds->First, torNode = optors->First; torNode != nullptr;) {
		this->CombineNodes(opnds, optors, rndNode, torNode, preRndNode, preTorNode);
	}

	return opnds->First->Value;
}

void ArithmeticEngine::CombineNodes(LinkedList<Expression^>^% opnds, LinkedList<BinaryOperator^>^% optors,
				  LinkedListNode<Expression^>^% rndNode, LinkedListNode<BinaryOperator^>^% torNode,
				  LinkedListNode<Expression^>^% preRndNode, LinkedListNode<BinaryOperator^>^% preTorNode) {

	torNode->Value->setOperands(rndNode->Value, rndNode->Next->Value);

	preRndNode = rndNode;
	preTorNode = torNode;
	rndNode = rndNode->Next;
	torNode = torNode->Next;
	opnds->Remove(preRndNode);
	optors->Remove(preTorNode);

	rndNode->Value = torNode->Value;

}

bool ArithmeticEngine::loadTokens(GroupCollection^ groups, VariableTable^ vTable, LinkedList<Expression^>^% opnds, LinkedList<BinaryOperator^>^% optors) {
	CaptureCollection^ opndB = groups[4]->Captures;
	CaptureCollection^ optorsC = groups[3]->Captures;

	int opndCount = 1 + opndB->Count;
	int optorsCount = optorsC->Count;
	opnds = gcnew LinkedList<Expression^>();
	optors = gcnew LinkedList<BinaryOperator^>();

	opnds->AddLast(convertToExpression(groups[2]->Value, vTable));
	if (opnds->Last->Value == nullptr) {
		return false;
	}
	for (int i = 1; i < opndCount; i++) {
		opnds->AddLast(convertToExpression(opndB[i - 1]->Value, vTable));
		if (opnds->Last->Value == nullptr) {
			return false;
		}
	}

	for (int i = 0; i < optorsCount; i++) {
		opnds->AddLast(operatorTable[optorsC[i]->Value]);
	}

	return true;
}

Expression^ ArithmeticEngine::convertToExpression(String^ s, VariableTable^ vTable) {
	if (String::IsNullOrWhiteSpace(s)) {
		return nullptr;
	}

	Match^ match;
	for (int i = 0; i < regexList->Length; i++) {
		match = regexList[i]->Match(s);
		if (match->Success) {
			return creatorList[i](match, this, vTable);
		}
	}

	return nullptr;

}

bool ArithmeticEngine::compute(MathObject^% mo) {
	mo = root->compute();
	root = nullptr;
	return mo == nullptr;
}

bool ArithmeticEngine::isParentheseBalanced(GroupCollection^ groups) {
	return !((groups[parentheseTag]->Success) ||
			 (groups[innerParentheseTag]->Success) || 
			 (groups[functionArgParentheseTag]->Success));
}

static ArithmeticEngine::ArithmeticEngine() {

	for each(Function^ function in functions) {
		funcitonTable->Add(function->functionName, function);
	}

	for each(BinaryOperator^ optor in operators) {
		operatorTable->Add(optor->operatorSymbol, optor);
	}
}

Expression^ ArithmeticEngine::ExpressionCreator::createScalarExp(Match^ m, ArithmeticEngine^ engine, VariableTable^ vTable) {
	return gcnew MathObjExp(gcnew Scalar(System::Convert::ToDouble(m->Value)));
}

Expression^ ArithmeticEngine::ExpressionCreator::createMathObjExp(Match^ m, ArithmeticEngine^ engine, VariableTable^ vTable) {
	MathObject^ mo;
	if (!vTable->checkGet(m->Groups[2]->Value, mo)) {
		return nullptr;
	}

	if (m->Groups[1]->Success) {
		mo->negate();
	}

	return gcnew MathObjExp(mo);
}

Expression^ ArithmeticEngine::ExpressionCreator::createFunction(Match^ m, ArithmeticEngine^ engine, VariableTable^ vTable) {

	GroupCollection^ groups = m->Groups;
	String^ funName = groups[1]->Value;
	if (!ArithmeticEngine::funcitonTable->ContainsKey(funName)) {
		return nullptr;
	}

	Function^ function = ArithmeticEngine::funcitonTable[funName];

	CaptureCollection^ argL = groups[3]->Captures;
	array<Expression^>^ args = gcnew array<Expression^>(1 + argL->Count);

	args[0] = engine->convertToExpression(groups[2]->Value, vTable);
	if (args[0] == nullptr) {
		return nullptr;
	}

	for (int i = 1; i < args->Length; i++) {
		args[i] = engine->convertToExpression(argL[i - 1]->Value, vTable);
		if (args[i] == nullptr) {
			return nullptr;
		}
	}

	if (!function->setArgs(args)) {
		return nullptr;
	}

	return function;
}

Expression^ ArithmeticEngine::ExpressionCreator::createCompoundExp(Match^ m, ArithmeticEngine^ engine, VariableTable^ vTable) {
	return engine->anaylzeCompoundExpression(m->Value, vTable);
}