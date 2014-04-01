#pragma once
#include "Command.h"
#include "PatternAnalyzer.h"

namespace em {
	namespace intrprt {
		namespace cmd {
			using em::intrprt::pattern::PatternAnalyzer;

			ref class OptionCommand : public Command {
			

			public:
				OptionCommand();
				virtual ~OptionCommand();

				virtual Message^ performCommand(String^ args, Interpreter^ iptr) override;
			};
		}
	}
}