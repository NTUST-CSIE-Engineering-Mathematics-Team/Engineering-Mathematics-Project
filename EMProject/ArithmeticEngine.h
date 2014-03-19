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
					static Expression^ concreteMathObjExp(Match^ m, ArithmeticEngine^ engine);
					static Expression^ concreteFunction(Match^ m, ArithmeticEngine^ engine);
					static Expression^ concreteCompoundExp(Match^ m, ArithmeticEngine^ engine);

				};

			private:
				VariableTable^ const vTable;
				Expression^ root;
				
				static String^ const innerParentheseTag = "i";
				static String^ const functionArgParentheseTag = "f";
			
				static String^ const NAME_PATTERN = "^(-)?([A-Za-z_]\\w*)$";
				static String^ const DOUBLE_PATTERN = "^-?\\d+(?:\\.\\d+)?$";
				static String^ const UNSIGNED_DOUBLE_PATTERN = "(?:\\d+(?:\\.\\d+)?)";
				
				static String^ const OPERATOR_PATTERN = "([-+*/x])";
				static String^ const NAME_OR_FUNCTION_PATTERN = "(?:[A-Za-z_]\\w*(?:\\s*\\(" + arithmeticContentPattern(functionArgParentheseTag) + "\\))?)";

				static property String^ COMPOUND_EXP_PATTERN {
					String^ get() {
						StringBuilder^ full = gcnew StringBuilder();
						StringBuilder^ duplicate = gcnew StringBuilder();

						duplicate->AppendFormat("(?:{0}\\s*", OPEN_PARENTHESE_PATTERN);
						duplicate->AppendFormat("(-?(?({0}){1}|(?:{2}|{3})))", parentheseTag, arithmeticContentPattern(innerParentheseTag), NAME_OR_FUNCTION_PATTERN, UNSIGNED_DOUBLE_PATTERN);
						duplicate->AppendFormat("\\s*{0})", CLOSE_PARENTHESE_PATTERN);

						full->AppendFormat("^\\s*(?:{0}(?:\\s*{1}\\s*{2})*)\\s*$", duplicate, OPERATOR_PATTERN, duplicate);

						return full->ToString();
					}
				}

				static property String^ FUNCTION_PATTERN {
					String^ get() {
						StringBuilder^ full = gcnew StringBuilder();
						StringBuilder^ duplicate = gcnew StringBuilder();
						duplicate->AppendFormat("(?:{0}\\s*", OPEN_PARENTHESE_PATTERN);

						duplicate->AppendFormat("((?:(?<{0}>\\()|(?<-{1}>\\))|\\s|(?({2})[-+*/A-Za-z0-9._,]|[-+*/A-Za-z0-9._]))+)", innerParentheseTag, innerParentheseTag, innerParentheseTag);
						duplicate->AppendFormat("\\s*{0})", CLOSE_PARENTHESE_PATTERN);

						full->AppendFormat("^(-)?([A-Za-z_]\\w*)\\s*\\(\\s*{0}(?:\\s*,\\s*{1})*\\s*\\)$", duplicate, duplicate);

						return full->ToString();
					}
				}

				static Regex^ const NAME_REGEX = gcnew Regex(NAME_PATTERN, RegexOptions::Compiled);
				static Regex^ const DOUBLE_REGEX = gcnew Regex(DOUBLE_PATTERN, RegexOptions::Compiled);
				static Regex^ const FUNCTION_REGEX = gcnew Regex(FUNCTION_PATTERN, RegexOptions::Compiled);
				static Regex^ const COMPOUND_EXP_REGEX = gcnew Regex(COMPOUND_EXP_PATTERN, RegexOptions::Compiled);

				static array<Regex^>^ regexList = { DOUBLE_REGEX, NAME_REGEX, FUNCTION_REGEX, COMPOUND_EXP_REGEX };
				static array<ExpressionFactory::ConcreteExpression^>^ constrctorList = {
					gcnew ExpressionFactory::ConcreteExpression(ExpressionFactory::concreteScalarExp),
					gcnew ExpressionFactory::ConcreteExpression(ExpressionFactory::concreteMathObjExp),
					gcnew ExpressionFactory::ConcreteExpression(ExpressionFactory::concreteFunction),
					gcnew ExpressionFactory::ConcreteExpression(ExpressionFactory::concreteCompoundExp)
				};

			public:
				ArithmeticEngine(VariableTable^ vTable);
				virtual ~ArithmeticEngine(); 

				Message^ execute(String^ expressionString, MathObject^% mo);

				static String^ arithmeticContentPattern(String^ tag);

			private:
				Expression^ anaylzeCompoundExpression(String^ expression);

				bool analyze(String^ expression, Message^% msg);
				bool compute(MathObject^% mo, Message^% message);

				bool loadTokens(GroupCollection^ groups, LinkedList<Expression^>^% opnds, LinkedList<String^>^% optors);
				Expression^ convertToExpression(String^ s);
				Expression^ buildArithmeticTree(LinkedList<Expression^>^ opnds, LinkedList<String^>^ optors);
				void CombineNodes(LinkedList<Expression^>^% opnds, LinkedList<String^>^% optors,
								  LinkedListNode<Expression^>^% rndNode, LinkedListNode<String^>^% torNode,
								  LinkedListNode<Expression^>^% preRndNode, LinkedListNode<String^>^% preTorNode);
				
				static bool isParentheseBalanced(GroupCollection^ groups);

			};
		}
	}
}