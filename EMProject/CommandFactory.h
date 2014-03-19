#pragma once
#include "Command.h"

namespace em {
	namespace intrprt{
		namespace cmd{
			using System::Collections::Generic::List;

			ref class CommandFactory abstract {
				
			private:

				static List<Command^>^ const cmdList = gcnew List<Command^> ();
			public:
				generic<typename C> where C : Command
				static void addCommand();

				static array<Command^>^ getCommandArray();
				virtual ~CommandFactory();

			private:
				CommandFactory();

			};
		}
	}
}



