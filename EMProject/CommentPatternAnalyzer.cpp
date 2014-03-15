#include "CommentPatternAnalyzer.h"

using namespace em::intrprt::pattern;

CommentPatternAnalyzer::CommentPatternAnalyzer() {
}


CommentPatternAnalyzer::~CommentPatternAnalyzer() {
}

Message^ CommentPatternAnalyzer::analyze(Match^ result, Interpreter^ iptr) {
	return displayComment ? gcnew Message(Message::State::PASS, result->Groups[1]->Value, Message::COMMENT_COLOR) : Message::PASS_NO_CONTENT_MSG;
}


String^ CommentPatternAnalyzer::buildInitPattern() {
	return "^#(.*)$";
}