#include "ArithmeticEngine.h"
#include "All_Math.h"


using namespace em::math::engine;
using namespace System::Text::RegularExpressions;
using em::math::MathObject;

ArithmeticEngine::ArithmeticEngine(VariableTable^ vTable) : vTable(vTable) {
	root = nullptr;
}


ArithmeticEngine::~ArithmeticEngine() {
}

Message^ ArithmeticEngine::execute(String^ expressionString, MathObject^% mo) {
	this->errorMsg = nullptr;
	if (!this->analyze(expressionString)) {
		if (this->errorMsg == nullptr) {
			return gcnew Message(Message::State::ERROR, "There is an unknown arithmetic syntax errors occur");
		}
		return this->errorMsg;
	}
	
	if (!this->compute(mo)) {
		if (this->errorMsg == nullptr) {
			return gcnew Message(Message::State::ERROR, "There is an unknown computing errors occur");
		}
		return this->errorMsg;
	}

	return Message::PASS_NO_CONTENT_MSG;
}

bool ArithmeticEngine::analyze(String^ expression) {
	this->root = this->anaylzeCompoundExpMatch(this->INPUT_COMPOUND_EXP_REGEX->Match(expression));
	if (this->root == nullptr) {
		return false;
	}
	return true;
}

bool ArithmeticEngine::compute(MathObject^% mo) {
	mo = root->compute(this->errorMsg);

	delete root;
	root = nullptr;
	return mo != nullptr;
}

Expression^ ArithmeticEngine::anaylzeCompoundExpMatch(Match^ match) {
	 

	 if (!match->Success) {

		 this->errorMsg = gcnew Message(Message::State::ERROR, "Wrong arithmetic syntax");
		 return nullptr;
	 }

	GroupCollection^ groups = match->Groups;
	if (!ArithmeticEngine::isParentheseBalanced(groups)) {
		this->errorMsg = Message::PARENTHESE_NOT_BALANCED_MSG;
		return nullptr;
	}

	LinkedList<Expression^>^ opnds;
	LinkedList<String^>^ optors;
	if (!loadTokens(groups, opnds, optors)) {
		return nullptr;
	}

	return buildArithmeticTree(opnds, optors);
}

bool ArithmeticEngine::loadTokens(GroupCollection^ groups, LinkedList<Expression^>^% opnds, LinkedList<String^>^% optors) {
	
	CaptureCollection^ opndB = groups[3]->Captures;
	CaptureCollection^ optorsC = groups[2]->Captures;

	int opndCount = 1 + opndB->Count;
	int optorsCount = optorsC->Count;
	opnds = gcnew LinkedList<Expression^>();
	optors = gcnew LinkedList<String^>();

	opnds->AddLast(convertToExpression(groups[1]->Value));
	if (opnds->Last->Value == nullptr) {
		return false;
	}

	for (int i = 1; i < opndCount; i++) {
		opnds->AddLast(convertToExpression(opndB[i - 1]->Value));
		if (opnds->Last->Value == nullptr) {
			return false;
		}
	}

	for (int i = 0; i < optorsCount; i++) {
		optors->AddLast(optorsC[i]->Value);
	}

	return true;
}

Expression^ ArithmeticEngine::buildArithmeticTree(LinkedList<Expression^>^ opnds, LinkedList<String^>^ optors) {
	String^ lowPriorityOptor = "+-";
	LinkedListNode<Expression^>^ rndNode = opnds->First;
	LinkedListNode<Expression^>^ preRndNode;
	LinkedListNode<String^>^ torNode = optors->First;
	LinkedListNode<String^>^ preTorNode;

	for (; torNode != nullptr;) {
		if (!lowPriorityOptor->Contains(torNode->Value)) {
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

void ArithmeticEngine::CombineNodes(LinkedList<Expression^>^% opnds, LinkedList<String^>^% optors,
									LinkedListNode<Expression^>^% rndNode, LinkedListNode<String^>^% torNode,
									LinkedListNode<Expression^>^% preRndNode, LinkedListNode<String^>^% preTorNode) {

	BinaryOperator^ optor = OperatorFactory::createOperatorInstance(torNode->Value, rndNode->Value, rndNode->Next->Value);

	preRndNode = rndNode;
	preTorNode = torNode;
	rndNode = rndNode->Next;
	torNode = torNode->Next;
	opnds->Remove(preRndNode);
	optors->Remove(preTorNode);

	rndNode->Value = optor;

}

Expression^ ArithmeticEngine::convertToExpression(String^ s) {
	s = s->Trim();
	if (String::IsNullOrWhiteSpace(s)) {
		errorMsg = gcnew Message(Message::State::ERROR, "Empty operand or argument");
		return nullptr;
	}
	
	Match^ match;
	for (int i = 0; i < regexList->Length; i++) {
		match = regexList[i]->Match(s);
		
		if (match->Success) {
			return constrctorList[i](match, this);
		}
	}
	
	errorMsg = gcnew Message(Message::State::ERROR, "Cannot match any arithmetic syntax");
	return nullptr;

}

array<Expression^>^ ArithmeticEngine::convertToExps(GroupCollection^ groups, int firstIndex) {

	CaptureCollection^ argL = groups[firstIndex + 1]->Captures;
	array<Expression^>^ args = gcnew array<Expression^>(1 + argL->Count);

	args[0] = this->convertToExpression(groups[firstIndex]->Value);
	if (args[0] == nullptr) {
		return nullptr;
	}

	for (int i = 1; i < args->Length; i++) {
		args[i] = this->convertToExpression(argL[i - 1]->Value);

		if (args[i] == nullptr) {
			return nullptr;
		}
	}

	return args;
}

bool ArithmeticEngine::isParentheseBalanced(GroupCollection^ groups) {
	return !((groups[parentheseTag]->Success) || (groups[innerParentheseTag]->Success));
}

array<Expression^>^ ArithmeticEngine::vmAssistDelimiter(String^ literalWithCommas) {
	Match^ m = VM_ASSIST_REGEX->Match(literalWithCommas);

	array<Expression^>^ exps;
	if (!m->Success || (exps = this->convertToExps(m->Groups, 1)) == nullptr) {
		this->errorMsg = gcnew Message(Message::State::ERROR, "Empty operand or argument");
		return nullptr;
	}
	
	return exps;
}

Expression^ ArithmeticEngine::ExpressionFactory::concreteScalarExp(Match^ m, ArithmeticEngine^ engine) {
	return gcnew MathObjExp(false ,gcnew Scalar(System::Convert::ToDouble(m->Value)));
}

Expression^ ArithmeticEngine::ExpressionFactory::concreteVarExp(Match^ m, ArithmeticEngine^ engine) {
	MathObject^ mo;
	if (!engine->vTable->checkGet(m->Groups[2]->Value, mo)) {
		engine->errorMsg = Message::varNotFoundMsg(m->Groups[2]->Value);
		return nullptr;
	}

	return gcnew MathObjExp(m->Groups[1]->Success, mo);
}

Expression^ ArithmeticEngine::ExpressionFactory::concreteVMExp(Match^ m, ArithmeticEngine^ engine) {
	GroupCollection^ groups = m->Groups;
	CaptureCollection^ argL = groups[3]->Captures;
	array<Expression^>^ row1;
	

	row1 = engine->vmAssistDelimiter(groups[2]->Value);
	if (row1 == nullptr) {
		return nullptr;
	}

	array<array<Expression^>^>^ rows = gcnew array<array<Expression^>^>(1 + argL->Count);
	rows[0] = row1;
	for (int i = 1; i < rows->Length; i++) {
		rows[i] = engine->vmAssistDelimiter(argL[i - 1]->Value);

		if (rows[i] == nullptr || rows[i]->Length != row1->Length) {
			return nullptr;
		}
	}

	return gcnew VMConstructExp(groups[1]->Success, rows);
}

Expression^ ArithmeticEngine::ExpressionFactory::concreteSetExp(Match^ m, ArithmeticEngine^ engine) {
	GroupCollection^ groups = m->Groups;
	array<Expression^>^ exps = engine->convertToExps(groups, 2);

	if (exps == nullptr) {
		return nullptr;
	}

	return gcnew MathObjSetExp(groups[1]->Success, exps);
}

Expression^ ArithmeticEngine::ExpressionFactory::concreteFunction(Match^ m, ArithmeticEngine^ engine) {

	GroupCollection^ groups = m->Groups;
	String^ funName = groups[2]->Value;
	if (!FunctionFactory::hasFunction(funName)) {
		engine->errorMsg = gcnew Message(Message::State::ERROR, "Cannot find funtion \"" + funName + "\"");
		return nullptr;
	}

	array<Expression^>^ exps;
	if (groups[4]->Captures->Count == 0 && String::IsNullOrWhiteSpace(groups[3]->Value)) {
		exps = gcnew array<Expression^>(0);
	} else {
		exps = engine->convertToExps(groups, 3);
		if (exps == nullptr) {
			return nullptr;
		}
		
	}

	Function^ function = FunctionFactory::createFunctionInstance(funName, groups[1]->Success, exps);

	return function;
}

Expression^ ArithmeticEngine::ExpressionFactory::concreteCompoundExp(Match^ m, ArithmeticEngine^ engine) {
	return engine->anaylzeCompoundExpMatch(m);
}

Expression^ ArithmeticEngine::ExpressionFactory::concreteParentheseUnitExp(Match^ m, ArithmeticEngine^ engine) {
	return engine->anaylzeCompoundExpMatch(INPUT_COMPOUND_EXP_REGEX->Match(m->Groups[1]->Value));
}

String^ ArithmeticEngine::arithmeticContentPattern(String^ tag) {
	return arithmeticContentPattern2(tag, true);
}

String^ ArithmeticEngine::arithmeticContentPattern2(String^ tag, bool atLeastOne) {
	String^ s = "(?:(?<" + tag + ">[(\\[{])|(?<-" + tag + ">[)\\]}])|[-+*/A-Za-z0-9._,|]|\\s)" + (atLeastOne ? "+" : "*");
	return s;
}
String^ ArithmeticEngine::buildCompundExpPattern(bool atLeastOne) {
	StringBuilder^ full = gcnew StringBuilder();
	StringBuilder^ duplicate = gcnew StringBuilder();

	duplicate->AppendFormat("(?:{0}\\s*", OPEN_PARENTHESE_PATTERN);
	duplicate->AppendFormat("(-?(?({0}){1}|(?:{2}|{3}|{4}|{5})))",
		parentheseTag,
		arithmeticContentPattern(innerParentheseTag),
		UNSIGNED_DOUBLE_PATTERN,
		NAME_OR_FUNCTION_PATTERN,
		VM_PREVIEW_PATTERN,
		SET_PREVIEW_PATTERN);

	duplicate->AppendFormat("\\s*{0})", CLOSE_PARENTHESE_PATTERN);

	full->AppendFormat("^\\s*(?:{0}(?:\\s*{1}\\s*{2}){3})\\s*$", duplicate, OPERATOR_PATTERN, duplicate, atLeastOne ? "+" : "*");
	return full->ToString();
}
