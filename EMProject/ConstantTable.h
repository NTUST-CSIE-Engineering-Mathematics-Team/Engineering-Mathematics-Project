#pragma once
#include "MappingTable.h"

namespace em {
	namespace intrprt {

		generic <typename K, typename V>
		ref class ConstantTable abstract: public MappingTable<K, V> {

		public:
			virtual ~ConstantTable();

		protected:
			ConstantTable(array<K>^ keyList, array<V>^ valueList);
			virtual void initTable(array<K>^ keyList, array<V>^ valueList);

		};
	}
}