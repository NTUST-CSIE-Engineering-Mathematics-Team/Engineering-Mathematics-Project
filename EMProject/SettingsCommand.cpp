#include "SettingsCommand.h"
#include "KeywordCollection.h"
#include "MathObject.h"
#include "CommentPatternAnalyzer.h"

using namespace em::intrprt::cmd;
using em::intrprt::pattern::CommentPatternAnalyzer;
using em::math::MathObject;

SettingsCommand::SettingsCommand() : Command(KeywordCollection::SETTINGS_CMD, "CI") {
}

SettingsCommand::~SettingsCommand() {
}

Message^ SettingsCommand::performCommand(array<String^>^ args, int typeIndex, Interpreter^ iptr) {

	wchar_t flag = System::Convert::ToChar(args[0]);
	int value = System::Convert::ToInt32(args[1]);
	
	flag = System::Char::ToUpper(flag);

	switch (flag) {
	case L'W':
		MathObject::numWidth = value;
		return gcnew Message(Message::State::PASS, Message::SETTING_COLOR, "Set numeral width to " + value);

	case L'F':
		MathObject::numPrecision = value;
		return gcnew Message(Message::State::PASS, Message::SETTING_COLOR, "Set floating precision to " + value);
	case L'C':
		CommentPatternAnalyzer::displayComment = value >= 0 ? true : false;
		return gcnew Message(Message::State::PASS, Message::SETTING_COLOR, "Comments will" + (CommentPatternAnalyzer::displayComment ? " " : " not ") + "be display");
	}

	return gcnew Message(Message::State::ERROR, "cannot find the flag \"" + flag + "\"");
}