#pragma once
#include "Command.h"
#include "PatternAnalyzer.h"

namespace em {
	namespace intrprt {
		namespace cmd {
			using em::intrprt::pattern::PatternAnalyzer;

			ref class SettingsCommand : public Command {
			private:
				static array<String^>^ argTypes = { "CI" };

			public:
				SettingsCommand();
				virtual ~SettingsCommand();

				virtual Message^ performCommand(array<String^>^ args, int typeIndex, Interpreter^ iptr) override;
			};
		}
	}
}