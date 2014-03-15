#pragma once
#include "PatternAnalyzer.h"
#include "CommandTable.h"


namespace em {
	namespace intrprt {
		namespace pattern {
			using namespace cmd;
			using namespace em::intrprt;
			using System::String;
			
			ref class CommandPatternAnalyzer : public PatternAnalyzer {

			protected:
				CommandTable^ commandTable;

			public:
				CommandPatternAnalyzer(array<Command^>^ commands);
				virtual ~CommandPatternAnalyzer();

				virtual Message^ analyze(Match^ validateLine, Interpreter^ iptr) override;

			protected:
				virtual String^ buildInitPattern() override;
			
			};

			ref class FileCommandPatternAnalyzer : public CommandPatternAnalyzer {
			
			public:
				FileCommandPatternAnalyzer(array<Command^>^ commands);
				virtual ~FileCommandPatternAnalyzer();

				virtual Message^ analyze(Match^ validateLine, Interpreter^ iptr) override;
				
			protected:
				virtual String^ buildInitPattern() override;

			};
		}
	}
}