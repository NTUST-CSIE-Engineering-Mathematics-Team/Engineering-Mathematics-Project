#pragma once
#include "MappingTable.h"
#include "MathObject.h"

namespace em {
	namespace intrprt {

		using em::math::MathObject;
		using System::String;
		using System::Text::StringBuilder;

		ref class VariableTable : public MappingTable<String^, MathObject^> {
		public:
			virtual property MathObject^ default[String^] {
				virtual MathObject^ get(String^ key) override {
					return MappingTable::default[key];
				}

				virtual void set(String^ key, MathObject^ value) {
					if (this->contains(key)) {
						this->table[key] = value;
					}
				}
			}

		private:
			static StringBuilder^ lastGeneratedName;

		public:
			VariableTable();
			virtual ~VariableTable();

			virtual bool addVariable(String^ name, MathObject^ mo);
			virtual String^  addVariable(MathObject^ mo) sealed;
			virtual bool deleteVariable(String^ name);

			virtual void load(VariableTable^ vTable);
			virtual void unload(VariableTable^ vTable);
			virtual void clear();
			virtual Dictionary<String^, MathObject^>::Enumerator getEnumerator();
		private:
			String^ generateNewVariableName();
		};
	}
}
