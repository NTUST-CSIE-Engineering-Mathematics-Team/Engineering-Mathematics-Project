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

				property wchar_t argType {
					wchar_t  get() {
						return this->argT;
					}
				}

			private:
				String^ cmdLiteral;
				wchar_t argT;
		
			public:
				virtual ~Command();
				virtual Message^ performCommand(String^ arg, Interpreter^ iptr) abstract;
				
			protected:
				Command(String^ cl, wchar_t argType);

			};
		}
	}
}