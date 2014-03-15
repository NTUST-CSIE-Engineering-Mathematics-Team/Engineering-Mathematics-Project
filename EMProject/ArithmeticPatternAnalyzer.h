#pragma once
#include "PatternAnalyzer.h"
#include "ArithmeticEngine.h"

namespace em {
	namespace intrprt {
		namespace pattern{

			using em::math::engine::ArithmeticEngine;

			ref class ArithmeticPatternAnalyzer : public PatternAnalyzer {
			private:
				ArithmeticEngine^ engine;

				
			public:
				ArithmeticPatternAnalyzer();
				virtual ~ArithmeticPatternAnalyzer();

				virtual Message^ analyze(Match^ result, Interpreter^ iptr) override;

			protected:
				virtual String^ buildInitPattern() override;

			};
		}
	}
}