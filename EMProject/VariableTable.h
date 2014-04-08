#pragma once
#include "MappingTable.h"
#include "All_Math.h"
#include "KeywordCollection.h"

namespace em {
	namespace intrprt {

		using namespace em::math;
		using System::String;
		using System::Text::StringBuilder;
		using System::Collections::Generic::KeyValuePair;

		ref class VariableTable : public MappingTable<String^, MathObject^>, System::Collections::Generic::IEnumerable<KeyValuePair<String^, MathObject^>> {
		public:
			virtual property MathObject^ default[String^] {
				virtual MathObject^ get(String^ key) override {
					if (stgSetCreators->ContainsKey(key)) {
						return stgSetCreators[key](this);
					}

					return MappingTable::default[key];
				}
			}

			static property Dictionary<String^, String^>^ typeSetNameMap {
				Dictionary<String^, String^>^ get() {
					return tnMap;
				}
			}

		private:
			delegate MathObjSet^ CreateStorageSet(VariableTable^ vTable);

			static StringBuilder^ lastGeneratedName;
			static Dictionary<String^, CreateStorageSet^>^ const stgSetCreators = gcnew Dictionary<String^, CreateStorageSet^>(5);
			static Dictionary<String^, String^>^ const tnMap = gcnew Dictionary<String^, String^>(5);
		public:
			VariableTable();
			virtual ~VariableTable();

			virtual bool addVariable(String^ name, MathObject^ mo);
			virtual String^ addVariable(MathObject^ mo) sealed;
			virtual bool deleteVariable(String^ name);
			virtual bool contains(String^ name) override;

			virtual void load(VariableTable^ vTable);
			virtual void unload(VariableTable^ vTable);
			virtual void clear();
		
			virtual System::Collections::Generic::IEnumerator<KeyValuePair<String^, MathObject^>>^ GetEnumerator();

		private:
			static VariableTable();
			String^ generateNewVariableName();

			generic<typename M> where M : MathObject
			static MathObjSet^ createStgSet(VariableTable^ vTable);

			virtual System::Collections::IEnumerator^ GetNGEnumerator() sealed = System::Collections::IEnumerable::GetEnumerator;
		};
	}
}
