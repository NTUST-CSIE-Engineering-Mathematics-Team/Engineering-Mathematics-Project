#pragma once
#include "ConstantTable.h"
#include "Command.h"

namespace em {
	namespace intrprt {
		namespace cmd {
			using System::String;

			ref class CommandTable : public ConstantTable<String^, Command^> {

			public:
				CommandTable(array<Command^>^ commands);
				virtual ~CommandTable();

			private:
				static array<String^>^ createKeys(array<Command^>^ commands);
			};
		}
	}
}