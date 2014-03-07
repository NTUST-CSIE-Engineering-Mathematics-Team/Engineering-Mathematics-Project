#include "MappingTable.h"

using namespace em::intrprt;


generic <typename K, typename V>
MappingTable<K, V>::MappingTable() {
	this->table = gcnew Dictionary<K, V>(10);
}


generic <typename K, typename V>
MappingTable<K, V>::~MappingTable() {
	delete this->table;
}
generic <typename K, typename V>
bool MappingTable<K, V>::contains(K key) {
	return this->table->ContainsKey(key);
}