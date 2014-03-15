#pragma once
#include "CreateMathObjectCommand.h"
#include "Matrix.h"
#include "PatternAnalyzer.h"

namespace em {
	namespace intrprt {
		namespace cmd {

			ref class CreateMatrixCommand : public CreateMathObjectCommand {
						
			public:
				CreateMatrixCommand();
				virtual ~CreateMatrixCommand();

			protected:
				virtual Message^ createMathObject(int typeIndex, String^ varName, array<String^>^ rawArgs, Interpreter^ iptr) override;

			private:
				ref class MatrixConstructionAnalyzer : public PatternAnalyzer {

				private:
					Matrix^ tmpMat;
					String^ matName;
					int rowIndex;
					
				public:
					MatrixConstructionAnalyzer(Matrix^ mat, String^ mName);
					virtual ~MatrixConstructionAnalyzer();

					virtual Message^ analyze(Match^ result, Interpreter^ iptr) override;

				protected:
					virtual String^ buildInitPattern() override;

				private:
					Message^ tryFinish(Interpreter^ iptr);
				};
			};
		}
	}
}