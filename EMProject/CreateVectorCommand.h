#pragma once
#include "CreateMathObjectCommand.h"
#include "MathObject.h"
#include "Matrix.h"
#include "Vector.h"
#include "Scalar.h"

namespace em {
	namespace intrprt {
		namespace cmd {
			
			ref class CreateVectorCommand : public CreateMathObjectCommand {
		
			public:
				CreateVectorCommand();
				virtual ~CreateVectorCommand();

			protected:
				virtual Message^ createMathObject(int typeIndex, String^ varName, array<String^>^ args, Interpreter^ iptr) override;

			private:
				ref class VectorConstructionAnalyzer : public PatternAnalyzer {

				private:
					Vector^ tmpVec;
					String^ vecName;

				public:
					VectorConstructionAnalyzer(Vector^ vec, String^ vName);
					virtual ~VectorConstructionAnalyzer();

					virtual Message^ analyze(Match^ result, Interpreter^ iptr) override;

				protected:
					virtual String^ buildInitPattern() override;

				};
			};
		}
	}
}
