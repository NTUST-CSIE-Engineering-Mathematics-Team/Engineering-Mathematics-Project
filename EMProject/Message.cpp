#include "Message.h"

using namespace em::intrprt;

Message::Message(State t, String^ s) : state(t), content(s) {
	
}

Message::~Message() {
	delete content;
	
}
