#pragma once
#include "MappingTable.h"
#include "MathObject.h"

namespace em {
	namespace intrprt {

		using em::math::MathObject;
		using System::String;
		using System::Text::StringBuilder;

		ref class VariableTable : public MappingTable<String^, MathObject^> {

		private:
			static StringBuilder^ lastGeneratedName;
			virtual String^ generateNewVariableName() sealed;

		public:

			VariableTable();
			virtual ~VariableTable();

			virtual bool addVariable(String^ name, MathObject^ mo);
			virtual String^  addVariable(MathObject^ mo);
			virtual bool deleteVariable(String^ name);

			virtual void load(VariableTable^ vTable);
			virtual void unload(VariableTable^ vTable);
			virtual void clear();
			
		};
	}
}
