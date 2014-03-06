#pragma once

namespace em {
	namespace intrprt {
		using System::Collections::Generic::Dictionary;

		generic <typename K, typename V>
		public ref class MappingTable abstract {
		private:
			Dictionary<K, V> map;
		public:
			virtual property const V default[K] {
				const V get(K key) {
					return map[key];
				}
			}

			MappingTable();
			virtual ~MappingTable();
		};
	}
}
