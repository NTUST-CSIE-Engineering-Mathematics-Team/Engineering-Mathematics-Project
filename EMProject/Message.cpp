#include "Message.h"

using em::Message;
using System::String;
Message::Message(Type t, String^ s) : type(t), content(s) {
	
}

Message::~Message() {
	delete content;
	
}
