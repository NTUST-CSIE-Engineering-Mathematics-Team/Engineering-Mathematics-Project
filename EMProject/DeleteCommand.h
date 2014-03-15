#pragma once
#include "Command.h"

namespace em {
	namespace intrprt {
		namespace cmd {

			ref class DeleteCommand : public Command {
			

			public:
				DeleteCommand();
				virtual ~DeleteCommand();

				virtual Message^ performCommand(array<String^>^ args, int typeIndex, Interpreter^ iptr) override;

			};
		}
	}
}
