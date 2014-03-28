#pragma once
#include "Command.h"
#include "PatternAnalyzer.h"

namespace em {
	namespace intrprt {
		namespace cmd {
			using em::intrprt::pattern::PatternAnalyzer;

			ref class SettingsCommand : public Command {
			

			public:
				SettingsCommand();
				virtual ~SettingsCommand();

				virtual Message^ performCommand(String^ args, Interpreter^ iptr) override;
			};
		}
	}
}