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
	return this->root != nullptr;
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
	LinkedList<wchar_t>^ optors;
	if (!loadTokens(groups, opnds, optors)) {
		return nullptr;
	}

	return buildArithmeticTree(opnds, optors);
}

bool ArithmeticEngine::loadTokens(GroupCollection^ groups, LinkedList<Expression^>^% opnds, LinkedList<wchar_t>^% optors) {
	
	CaptureCollection^ opndsC = groups[operandTag]->Captures;
	CaptureCollection^ optorsC = groups[1]->Captures;

	opnds = gcnew LinkedList<Expression^>();
	optors = gcnew LinkedList<wchar_t>();


	for (int i = 0; i < opndsC->Count; i++) {
		opnds->AddLast(convertToExpression(opndsC[i]->Value));
		if (opnds->Last->Value == nullptr) {
			return false;
		}
	}

	for (int i = 0; i < optorsC->Count; i++) {
		optors->AddLast(optorsC[i]->Value[0]);
	}

	return true;
}

Expression^ ArithmeticEngine::buildArithmeticTree(LinkedList<Expression^>^ opnds, LinkedList<wchar_t>^ optors) {
	String^ lowPriorityOptor = "+-";
	LinkedListNode<Expression^>^ rndNode = opnds->First;
	LinkedListNode<Expression^>^ preRndNode;
	LinkedListNode<wchar_t>^ torNode = optors->First;
	LinkedListNode<wchar_t>^ preTorNode;

	for (; torNode != nullptr;) {
		if (lowPriorityOptor->IndexOf(torNode->Value) < 0) {
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

void ArithmeticEngine::CombineNodes(LinkedList<Expression^>^% opnds, LinkedList<wchar_t>^% optors,
									LinkedListNode<Expression^>^% rndNode, LinkedListNode<wchar_t>^% torNode,
									LinkedListNode<Expression^>^% preRndNode, LinkedListNode<wchar_t>^% preTorNode) {

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

array<Expression^>^ ArithmeticEngine::convertToExps(GroupCollection^ groups) {

	CaptureCollection^ argL = groups[operandTag]->Captures;
	array<Expression^>^ args = gcnew array<Expression^>(argL->Count);

	for (int i = 0; i < args->Length; i++) {
		args[i] = this->convertToExpression(argL[i]->Value);

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
	if (!m->Success || (exps = this->convertToExps(m->Groups)) == nullptr) {
		this->errorMsg = gcnew Message(Message::State::ERROR, "Empty operand or argument");
		return nullptr;
	}
	
	return exps;
}

Expression^ ArithmeticEngine::ExpressionFactory::concreteDecimalExp(Match^ m, ArithmeticEngine^ engine) {
	int vLast = m->Value->Length - 1;
	wchar_t unit = m->Value[vLast];
	
	if (System::Char::IsLetter(unit) || System::Char::IsPunctuation(unit)) {
		double value = System::Convert::ToDouble(m->Value->Substring(0, vLast));
		
		switch (unit) {
		case L'a':
			return gcnew SimpleMathObjExp(false, gcnew Angle(value, true));

		case L'p':
			return gcnew SimpleMathObjExp(false, gcnew Scalar(value * System::Math::PI));

		case L'e':
			return gcnew SimpleMathObjExp(false, gcnew Scalar(value * System::Math::E));

		case L'!':
			if (System::Math::Truncate(value) == value) {
				return gcnew SimpleMathObjExp(false, MathHelper::factorial(static_cast<int>(value)));
			}
		default:
			return nullptr;
		}
	}
	return gcnew SimpleMathObjExp(false, gcnew Scalar(System::Convert::ToDouble(m->Value)));
}

Expression^ ArithmeticEngine::ExpressionFactory::concreteVarExp(Match^ m, ArithmeticEngine^ engine) {
	MathObject^ mo;
	if (!engine->vTable->checkGet(m->Groups[2]->Value, mo)) {
		engine->errorMsg = Message::varNotDefinedMsg(m->Groups[2]->Value);
		return nullptr;
	}

	return gcnew SimpleMathObjExp(m->Groups[1]->Success, mo);
}

Expression^ ArithmeticEngine::ExpressionFactory::concreteVMExp(Match^ m, ArithmeticEngine^ engine) {
	GroupCollection^ groups = m->Groups;
	CaptureCollection^ argL = groups[operandTag]->Captures;
	
	array<array<Expression^>^>^ rows = gcnew array<array<Expression^>^>(argL->Count);
	for (int i = 0; i < rows->Length; i++) {
		rows[i] = engine->vmAssistDelimiter(argL[i]->Value);

		if (rows[i] == nullptr) {
			return nullptr;
		}
	}

	return gcnew VMConstructExp(groups[1]->Success, rows);
}

Expression^ ArithmeticEngine::ExpressionFactory::concreteSetExp(Match^ m, ArithmeticEngine^ engine) {
	GroupCollection^ groups = m->Groups;
	array<Expression^>^ exps = engine->convertToExps(groups);

	if (exps == nullptr) {
		return nullptr;
	}

	return gcnew MathObjSetExp(groups[1]->Success, exps);
}

Expression^ ArithmeticEngine::ExpressionFactory::concreteFunction(Match^ m, ArithmeticEngine^ engine) {

	GroupCollection^ groups = m->Groups;
	String^ funName = groups[2]->Value;
	if (!FunctionFactory::hasFunction(funName)) {
		engine->errorMsg = gcnew Message(Message::State::ERROR, "Funtion \"" + funName + "\" is not defined");
		return nullptr;
	}

	array<Expression^>^ exps;
	exps = engine->convertToExps(groups);
	if (exps == nullptr) {
		return nullptr;
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
	StringBuilder^ result = gcnew StringBuilder();
	result->AppendFormat("(?:(?<{0}>[(\\[{{])|(?<-{1}>[)\\]}}])|{2}|\\s){3}", tag, tag, CHARACTERS_SET, (atLeastOne ? "+" : "*"));
	
	return result->ToString();
}

String^ ArithmeticEngine::multiArithmeticContentPattern(String^ tag) {
	StringBuilder^ result = gcnew StringBuilder();
	StringBuilder^ duplicate = gcnew StringBuilder();
	duplicate->AppendFormat("(?:{0}\\s*", OPEN_PARENTHESE_PATTERN);

	duplicate->AppendFormat("(?<{0}>(?:(?<{1}>[(\\[{{])|(?<-{2}>[)\\]}}])|\\s|(?({3}){4}|{5}))+)", operandTag, tag, tag, tag, CHARACTERS_SET, CHARACTERS_SET_WHITOUT_DELIMITERS);
	duplicate->AppendFormat("\\s*{0})", CLOSE_PARENTHESE_PATTERN);
	result->AppendFormat("(?:{0}(?:,\\s*{1})*)", duplicate, duplicate);

	return result->ToString();
}

String^ ArithmeticEngine::buildCompundExpPattern(bool atLeastOne) {
	StringBuilder^ full = gcnew StringBuilder();
	StringBuilder^ duplicate = gcnew StringBuilder();

	duplicate->AppendFormat("(?:{0}\\s*", OPEN_PARENTHESE_PATTERN);
	duplicate->AppendFormat("(?<{0}>-?(?({1}){2}|(?:{3}|{4}|{5}|{6})))",
		operandTag,
		parentheseTag,
		arithmeticContentPattern(innerParentheseTag),
		UNSIGNED_DOUBLE_PATTERN,
		NAME_OR_FUNCTION_PATTERN,
		VM_PREVIEW_PATTERN,
		SET_PREVIEW_PATTERN);

	duplicate->AppendFormat("\\s*{0})", CLOSE_PARENTHESE_PATTERN);

	full->AppendFormat("^\\s*(?:{0}(?:\\s*({1})\\s*{2}){3})\\s*$", duplicate, OPERATOR_PATTERN, duplicate, atLeastOne ? "+" : "*");
	return full->ToString();
}
