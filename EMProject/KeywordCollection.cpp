#include "KeywordCollection.h"

using namespace em::intrprt;

KeywordCollection::KeywordCollection() {
}

KeywordCollection::~KeywordCollection() {
}

bool KeywordCollection::contains(String^ keywords) {
	return keywordsSet->Contains(keywords);
}

static KeywordCollection::KeywordCollection() {
	keywordsSet->Add(MATRICES);
	keywordsSet->Add(VECTORS);
	keywordsSet->Add(SCALARS);
	keywordsSet->Add(ANGLES);
	keywordsSet->Add(ALL);
	keywordsSet->Add(SETTINGS_CMD);
	keywordsSet->Add(PRINT_CMD);
	keywordsSet->Add(DELETE_CMD);
	keywordsSet->Add(STORAGE_CMD);

}

