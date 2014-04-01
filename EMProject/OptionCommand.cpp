#include "OptionCommand.h"
#include "KeywordCollection.h"
#include "MathObject.h"
#include "CommentPatternAnalyzer.h"

using namespace em::intrprt::cmd;
using em::intrprt::pattern::CommentPatternAnalyzer;
using em::math::MathObject;

OptionCommand::OptionCommand() : Command(KeywordCollection::SETTINGS_CMD, 'P') {
}

OptionCommand::~OptionCommand() {
}

Message^ OptionCommand::performCommand(String^ arg, Interpreter^ iptr) {
	String^ key;
	int value;
	PatternAnalyzer::isPair(arg, key, value);

	if (key->Length > 1) {
		return gcnew Message(Message::State::ERROR, "cannot find the flag \"" + key + "\"");
	}

	wchar_t flag = System::Char::ToLower(key[0]);

	switch (flag) {
	case L'w':
		MathObject::numWidth = value;
		return gcnew Message(Message::State::PASS, Message::SETTING_COLOR, "Set numeral width to " + value);

	case L'f':
		MathObject::formatSpecifier = flag;
		MathObject::numPrecision = value;
		return gcnew Message(Message::State::PASS, Message::SETTING_COLOR, "Set to fixed-point format, floating precision is " + value);

	case L'e':
		MathObject::formatSpecifier = flag;
		MathObject::numPrecision = value;
		return gcnew Message(Message::State::PASS, Message::SETTING_COLOR, "Set to exponential format, precision is " + value);

	case L'c':
		CommentPatternAnalyzer::displayComment = value >= 0 ? true : false;
		return gcnew Message(Message::State::PASS, Message::SETTING_COLOR, "Comments will" + (CommentPatternAnalyzer::displayComment ? " " : " not ") + "be display");
	}

	return gcnew Message(Message::State::ERROR, "cannot find the flag \"" + flag + "\"");
}