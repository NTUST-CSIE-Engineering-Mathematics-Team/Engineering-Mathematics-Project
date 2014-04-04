#pragma once
#include "PatternAnalyzer.h"
#include "ArithmeticEngine.h"

namespace em {
	namespace intrprt {
		namespace pattern{

			using em::math::engine::ArithmeticEngine;

			ref class AssignmentPatternAnalyzer : public PatternAnalyzer {
			private:
				Regex^ parseAssignment;
			public:
				AssignmentPatternAnalyzer();
				virtual ~AssignmentPatternAnalyzer();

				virtual Message^ analyze(Match^ result, Interpreter^ iptr) override;

			protected:
				virtual String^ buildInitPattern() override;

			};
		}
	}
}