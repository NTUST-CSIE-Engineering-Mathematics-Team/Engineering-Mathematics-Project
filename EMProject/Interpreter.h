#pragma once
#include "All_Patterns.h"
#include "PatternTable.h"
#include "CommandTable.h"
#include "VariableTable.h"
#include "Message.h"


namespace em {
	namespace intrprt {
		using namespace pattern;
		using System::String;

		ref class Interpreter abstract{

		public:
			property VariableTable^ variableTable{
				VariableTable^ get() {
					return proxyVTable;
				}
			}

			property ArithmeticEngine^ arithmeticEngine{
				ArithmeticEngine^ get() {
					return engine;
				}
			}
		private:
			PatternAnalyzer^ needNext;
			StringBuilder^ fullLine;
			PatternTable^ pTable;
			VariableTable^ proxyVTable;
			ArithmeticEngine^ engine;
			int beenIntrprtedLineCount;
			Regex^ const commentPattern = gcnew Regex("^([^#]*)\\#(.*)$", RegexOptions::Compiled);
		public:
			virtual ~Interpreter();

			Message^ interpret(String^ line, int% beenIntrprtedLineCount);
			void releaseNextLine();
			void needNextLine(PatternAnalyzer^ analyzer);

			virtual void finishInterpret() abstract;

			
		protected:
			Interpreter(array<PatternAnalyzer^>^ patternList);

		private:
			ref class VariableTableProxy : public VariableTable {
			public:
				property MathObject^ default[String^] {
					virtual MathObject^ get(String^ key) override {
						return allVTable[key];
					}

				}

			private:
				static VariableTable^ const allVTable = gcnew VariableTable();
				
			public:
				VariableTableProxy();
				virtual ~VariableTableProxy();

				virtual bool contains(String^ name) override;
				virtual bool addVariable(String^ name, MathObject^ mo) override;
				virtual bool deleteVariable(String^ name) override;

				virtual void load(VariableTable^ vTable) override;
				virtual void unload(VariableTable^ vTable) override;
				virtual bool checkGet(String^ name, MathObject^% mo) override;
				virtual System::Collections::Generic::IEnumerator<KeyValuePair<String^, MathObject^>>^ GetEnumerator() override;

			};
		};
	}
}