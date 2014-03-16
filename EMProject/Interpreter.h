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
			PatternAnalyzer^ const commentPattern = gcnew CommentPatternAnalyzer();
			PatternTable^ pTable;
			VariableTable^ proxyVTable;
			ArithmeticEngine^ engine;

		public:
			virtual ~Interpreter();

			Message^ interpret(String^ line);
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

					virtual void set(String^ key, MathObject^ value) override {

						allVTable[key] = value;
						if (this->VariableTable::contains(key)) {
							this->table[key] = value;
						}
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
				virtual Dictionary<String^, MathObject^>::Enumerator getEnumerator() override;
			};
		};
	}
}