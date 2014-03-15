#pragma once
#include "CreateMathObjectCommand.h"
#include "Scalar.h"

namespace em {
	namespace intrprt {

		namespace cmd {
			ref class CreateScalarCommand : public CreateMathObjectCommand {
			
			public:
				CreateScalarCommand();
				virtual ~CreateScalarCommand();

			protected:
				virtual Message^ createMathObject(int typeIndex, String^ varName, array<String^>^ args, Interpreter^ iptr) override;
			};
		}
	}
}
