#include "MappingTable.h"

using em::intrprt::MappingTable;
using System::Collections::Generic::Dictionary;

generic <typename K, typename V>
MappingTable<K, V>::MappingTable() {
	this->map = gcnew Dictionary<K, V>(10);
}


generic <typename K, typename V>
MappingTable<K, V>::~MappingTable() {
	delete this->map;
}
