#pragma once

namespace em {
	namespace intrprt {
		using System::Collections::Generic::Dictionary;

		generic <typename K, typename V>
		ref class MappingTable abstract {

		public:
			virtual property V default[K] {
				virtual V get(K key) {
					return table[key];
				}

			}

		protected:
			Dictionary<K, V>^ table;

		public:
			virtual ~MappingTable();

			virtual bool contains(K key);
			virtual bool checkGet(K key, V% v);
		protected:
			MappingTable();
		};
	}
}
