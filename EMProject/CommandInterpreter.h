#pragma once
#include "Message.h"
namespace em {
	using System::String;
	ref class CommandInterpreter {
	public:
		CommandInterpreter();
		Message^ inetrpret(String^ line);
		virtual ~CommandInterpreter();
	};
}
