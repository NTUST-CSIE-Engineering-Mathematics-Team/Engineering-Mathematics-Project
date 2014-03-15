#include "ConstantTable.h"

using namespace em::intrprt;

generic <typename K, typename V>
	ConstantTable<K, V>::ConstantTable(array<K>^ keyList, array<V>^ valueList) {
	this->initTable(keyList, valueList);
}

generic <typename K, typename V>
ConstantTable<K, V>::~ConstantTable() {
}

generic <typename K, typename V>
void ConstantTable<K, V>::initTable(array<K>^ keyList, array<V>^ valueList) {

	int len = keyList->Length > valueList->Length ? valueList->Length : keyList->Length;

	for (int i = 0; i < len; i++) {
		this->table->Add(keyList[i], valueList[i]);
	}
	
}