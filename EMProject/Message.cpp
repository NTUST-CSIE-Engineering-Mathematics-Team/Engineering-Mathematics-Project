#include "Message.h"

using em::intrprt::Message;
using System::String;
Message::Message(State t, String^ s) : state(t), content(s) {
	
}

Message::~Message() {
	delete content;
	
}
