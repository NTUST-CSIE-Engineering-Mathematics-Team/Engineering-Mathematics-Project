#pragma once
#include "Command.h"


namespace em {
	namespace intrprt {
		namespace cmd {
			ref class JudgeCommand : public Command {
			public:
				JudgeCommand();
				virtual ~JudgeCommand();

				virtual Message^ performCommand(array<String^>^ args, int typeIndex, Interpreter^ iptr) override;
			};

		}
	}
}

