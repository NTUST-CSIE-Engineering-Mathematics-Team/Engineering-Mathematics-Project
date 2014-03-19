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
	keywordsSet->Add(CREATE_MATRIX_CMD);
	keywordsSet->Add(CREATE_VECTOR_CMD);
	keywordsSet->Add(CREATE_SCALAR_CMD);
	keywordsSet->Add(SETTINGS_CMD);
	keywordsSet->Add(PRINT_CMD);
	keywordsSet->Add(DELETE_CMD);
	keywordsSet->Add(STORAGE_CMD);
	keywordsSet->Add(JUDGE_CMD);

}

