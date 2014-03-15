#pragma once

#include "Message.h"

namespace em {
	namespace intrprt {

		ref class Interpreter;
		namespace cmd {
			using namespace em::intrprt;
			using System::String;
			using namespace System::Text::RegularExpressions;
			
			ref class Command abstract {
			public:
				property String^ commandLiteral {
					String^ get() {
						return this->cmdLiteral;
					}
				}

				property array<String^>^ argTypes {
					array<String^>^  get() {
						return this->argTs;
					}
				}

			private:
				String^ cmdLiteral;
				array<String^>^ argTs;
		
			public:
				virtual ~Command();

				virtual Message^ performCommand(array<String^>^ args, int typeIndex, Interpreter^ iptr) abstract;
				
			protected:
				Command(String^ cl, ...array<String^>^  argsTypes);

			};
		}
	}
}