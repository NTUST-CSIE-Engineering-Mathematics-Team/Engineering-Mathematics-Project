#pragma once
#include "PatternAnalyzer.h"
#include "CommandTable.h"

namespace em {
	namespace intrprt {
		namespace pattern {
			using cmd::CommandTable;
			using namespace em::intrprt;

			ref class CommentPatternAnalyzer : public PatternAnalyzer {

			public:
				static property bool displayComment{
					bool get() {
						return display;
					}

					void set(bool f) {
						display = f;
					}
				}

			private:
				static bool display = false;

			public:
				CommentPatternAnalyzer();
				virtual ~CommentPatternAnalyzer();

				virtual Message^ analyze(Match^ validateLine, Interpreter^ iptr) override;
				
			protected:
				virtual String^ buildInitPattern() override;
			};
		}
	}
}