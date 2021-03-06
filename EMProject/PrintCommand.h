#pragma once
#include "Command.h"
#include "All_Math.h"

namespace em {
	namespace intrprt {
		namespace cmd {
			using namespace em::intrprt;
			using System::String;
			using System::Text::StringBuilder;
			using System::Collections::Generic::Dictionary;
			using namespace em::math;

			ref class PrintCommand : public Command {

			public:
				PrintCommand();
				virtual ~PrintCommand();

				virtual Message^ performCommand(String^ arg, Interpreter^ iptr) override;

			private:
				static PrintCommand();
			};
		}
	}
}