#pragma once
#include "All_Expressions.h"
#include "OperatorFactory.h"
#include "FunctionFactory.h"
#include "VariableTable.h"
#include "Message.h"

namespace em {
	namespace math {
		namespace engine {

			using System::String;
			using namespace System::Collections::Generic;
			using namespace System::Text::RegularExpressions;
			using namespace em::intrprt;
			using namespace expression;
			using namespace expression::operators;
			using namespace expression::functions;

			ref class ArithmeticEngine {
			public:
				static String^ const parentheseTag = "p";
				static String^ const OPEN_PARENTHESE_PATTERN = "(?<" + parentheseTag + ">\\()?";
				static String^ const CLOSE_PARENTHESE_PATTERN = "(?(" + parentheseTag + ")(?<-" + parentheseTag + ">\\)))";
				
			private:
				interface class ExpressionFactory {

				public:
					delegate Expression^ ConcreteExpression(Match^ m, ArithmeticEngine^ engine);
					
					static Expression^ concreteScalarExp(Match^ m, ArithmeticEngine^ engine);
					static Expression^ concreteVarExp(Match^ m, ArithmeticEngine^ engine);
					static Expression^ concreteVMExp(Match^ m, ArithmeticEngine^ engine);
					static Expression^ concreteSetExp(Match^ m, ArithmeticEngine^ engine);
					static Expression^ concreteFunction(Match^ m, ArithmeticEngine^ engine);
					static Expression^ concreteParentheseUnitExp(Match^ m, ArithmeticEngine^ engine);
					static Expression^ concreteCompoundExp(Match^ m, ArithmeticEngine^ engine);

					
				};

			private:
				VariableTable^ const vTable;
				Expression^ root;
				Message^ errorMsg;

				static String^ const innerParentheseTag = "i";
			
				static String^ const NAME_PATTERN = "^(-)?([A-Za-z_]\\w*)$";
				static String^ const DOUBLE_PATTERN = "^-?\\d+(?:\\.\\d+)?$";
				static String^ const UNSIGNED_DOUBLE_PATTERN = "(?:\\d+(?:\\.\\d+)?)";
				static String^ const PARENTHESE_UNIT_PATTERN = "^\\((" + arithmeticContentPattern2(innerParentheseTag, true) + ")\\)$";

				static String^ const OPERATOR_PATTERN = "([-+*/x])";
				static String^ const NAME_OR_FUNCTION_PATTERN = "(?:[A-Za-z_]\\w*(?:\\s*\\(" + arithmeticContentPattern2(innerParentheseTag, false) + "\\))?)";
				static String^ const SET_PREVIEW_PATTERN = "{" + arithmeticContentPattern(innerParentheseTag) + "}";
				static String^ const VM_PREVIEW_PATTERN = "\\[(?:(?<" + innerParentheseTag + ">\\()|(?<-" + innerParentheseTag + ">\\))|[-+*/A-Za-z0-9._,|]|\\s)+\\]";
				static String^ const COMPOUND_EXP_PATTERN = buildCompundExpPattern(true);
				 

				static property String^ FUNCTION_PATTERN {
					String^ get() {
						StringBuilder^ full = gcnew StringBuilder();
						StringBuilder^ duplicate = gcnew StringBuilder();
						duplicate->AppendFormat("(?:{0}\\s*", OPEN_PARENTHESE_PATTERN);

						duplicate->AppendFormat("((?:(?<{0}>[(\\[{{])|(?<-{1}>[)\\]}}])|\\s|(?({2})[-+*/A-Za-z0-9._,|]|[-+*/A-Za-z0-9._]))+)", innerParentheseTag, innerParentheseTag, innerParentheseTag);
						duplicate->AppendFormat("\\s*{0})", CLOSE_PARENTHESE_PATTERN);

						full->AppendFormat("^(-)?([A-Za-z_]\\w*)\\s*\\(\\s*(?:{0}(?:,\\s*{1})*)?\\s*\\)$", duplicate, duplicate);

						return full->ToString();
					}
				}

				static property String^ SET_PATTERN {
					String^ get() {
						StringBuilder^ full = gcnew StringBuilder();
						StringBuilder^ duplicate = gcnew StringBuilder();
						duplicate->AppendFormat("(?:{0}\\s*", OPEN_PARENTHESE_PATTERN);

						duplicate->AppendFormat("((?:(?<{0}>[(\\[{{])|(?<-{1}>[)\\]}}])|\\s|(?({2})[-+*/A-Za-z0-9._,|]|[-+*/A-Za-z0-9._]))+)", innerParentheseTag, innerParentheseTag, innerParentheseTag);
						duplicate->AppendFormat("\\s*{0})", CLOSE_PARENTHESE_PATTERN);

						full->AppendFormat("^(-)?{{\\s*{0}(?:,\\s*{1})*\\s*}}$", duplicate, duplicate);

						return full->ToString();
					}
				}

				static property String^ VM_PATTERN {
					String^ get() {
						StringBuilder^ full = gcnew StringBuilder();
						StringBuilder^ duplicate = gcnew StringBuilder();
						duplicate->AppendFormat("(?:{0}\\s*", OPEN_PARENTHESE_PATTERN);

						duplicate->AppendFormat("((?:(?<{0}>\\()|(?<-{1}>\\))|[-+*/A-Za-z0-9._,]|\\s)+)", innerParentheseTag, innerParentheseTag, innerParentheseTag);
						duplicate->AppendFormat("\\s*{0})", CLOSE_PARENTHESE_PATTERN);

						full->AppendFormat("^(-)?\\[\\s*{0}(?:\\|\\s*{1})*\\s*\\]$", duplicate, duplicate);

						System::Diagnostics::Debug::WriteLine(full->ToString());
						return full->ToString();
					}
				}

				static property String^ VM_ASSIST_PATTERN {
					String^ get() {
						StringBuilder^ full = gcnew StringBuilder();
						StringBuilder^ duplicate = gcnew StringBuilder();
						duplicate->AppendFormat("(?:{0}\\s*", OPEN_PARENTHESE_PATTERN);

						duplicate->AppendFormat("((?:(?<{0}>\\()|(?<-{1}>\\))|\\s|(?({2})[-+*/A-Za-z0-9._,]|[-+*/A-Za-z0-9._]))+)", innerParentheseTag, innerParentheseTag, innerParentheseTag);
						duplicate->AppendFormat("\\s*{0})", CLOSE_PARENTHESE_PATTERN);

						full->AppendFormat("^\\s*{0}(?:,\\s*{1})*\\s*$", duplicate, duplicate);

						System::Diagnostics::Debug::WriteLine(full->ToString());
						return full->ToString();
					}
				}

				static Regex^ const NAME_REGEX = gcnew Regex(NAME_PATTERN, RegexOptions::Compiled);
				static Regex^ const DOUBLE_REGEX = gcnew Regex(DOUBLE_PATTERN, RegexOptions::Compiled);
				static Regex^ const VM_REGEX = gcnew Regex(VM_PATTERN, RegexOptions::Compiled);
				static Regex^ const SET_REGEX = gcnew Regex(SET_PATTERN, RegexOptions::Compiled);
				static Regex^ const FUNCTION_REGEX = gcnew Regex(FUNCTION_PATTERN, RegexOptions::Compiled);
				static Regex^ const PARENTHESE_UNIT_REGEX = gcnew Regex(PARENTHESE_UNIT_PATTERN, RegexOptions::Compiled);
				static Regex^ const COMPOUND_EXP_REGEX = gcnew Regex(COMPOUND_EXP_PATTERN, RegexOptions::Compiled);

				static Regex^ const INPUT_COMPOUND_EXP_REGEX = gcnew Regex(buildCompundExpPattern(false), RegexOptions::Compiled);
				static Regex^ const VM_ASSIST_REGEX = gcnew Regex(VM_ASSIST_PATTERN, RegexOptions::Compiled);

				static array<Regex^>^ regexList = { DOUBLE_REGEX, NAME_REGEX, FUNCTION_REGEX, VM_REGEX, SET_REGEX, COMPOUND_EXP_REGEX, PARENTHESE_UNIT_REGEX};
				static array<ExpressionFactory::ConcreteExpression^>^ constrctorList = {
					gcnew ExpressionFactory::ConcreteExpression(ExpressionFactory::concreteScalarExp),
					gcnew ExpressionFactory::ConcreteExpression(ExpressionFactory::concreteVarExp),
					gcnew ExpressionFactory::ConcreteExpression(ExpressionFactory::concreteFunction),
					gcnew ExpressionFactory::ConcreteExpression(ExpressionFactory::concreteVMExp),
					gcnew ExpressionFactory::ConcreteExpression(ExpressionFactory::concreteSetExp),
					gcnew ExpressionFactory::ConcreteExpression(ExpressionFactory::concreteCompoundExp),
					gcnew ExpressionFactory::ConcreteExpression(ExpressionFactory::concreteParentheseUnitExp)
				};

			public:
				ArithmeticEngine(VariableTable^ vTable);
				virtual ~ArithmeticEngine(); 

				Message^ execute(String^ expressionString, MathObject^% mo);

				static String^ arithmeticContentPattern(String^ tag);

			private:
				Expression^ anaylzeCompoundExpMatch(Match^ match);

				bool analyze(String^ expression);
				bool compute(MathObject^% mo);

				bool loadTokens(GroupCollection^ groups, LinkedList<Expression^>^% opnds, LinkedList<String^>^% optors);
				Expression^ convertToExpression(String^ s);
				array<Expression^>^ vmAssistDelimiter(String^ literalWithCommas);
				array<Expression^>^ convertToExps(GroupCollection^ groups, int firstIndex);
				Expression^ buildArithmeticTree(LinkedList<Expression^>^ opnds, LinkedList<String^>^ optors);
				void CombineNodes(LinkedList<Expression^>^% opnds, LinkedList<String^>^% optors,
								  LinkedListNode<Expression^>^% rndNode, LinkedListNode<String^>^% torNode,
								  LinkedListNode<Expression^>^% preRndNode, LinkedListNode<String^>^% preTorNode);
				
				static bool isParentheseBalanced(GroupCollection^ groups);
				static String^ arithmeticContentPattern2(String^ tag, bool atLeastOne);
				static String^ buildCompundExpPattern(bool atLeastOne);
			};
		}
	}
}