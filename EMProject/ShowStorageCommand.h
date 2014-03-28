#pragma once
#include "Command.h"

namespace em {
	namespace intrprt {
		namespace cmd {
			using namespace System::Collections::Generic;

			ref class ShowStorageCommand : public Command {
			private:
				static Dictionary<String^, String^>^ const map = gcnew Dictionary<String^, String^>(4);

			public:
				ShowStorageCommand();
				virtual ~ShowStorageCommand();

				virtual Message^ performCommand(String^ arg, Interpreter^ iptr) override;

			private:
				static ShowStorageCommand();
			};
		}
	}
}