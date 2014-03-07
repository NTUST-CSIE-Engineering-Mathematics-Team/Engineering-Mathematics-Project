#pragma once
#include "MappingTable.h"
#include "MathObject.h"

namespace em {
	namespace intrprt {

		using em::math::MathObject;
		using System::String;
		using System::Text::StringBuilder;

		public ref class VariableTable : public MappingTable<String^, MathObject^> {

		private:
			StringBuilder^ lastGeneratedName;
			String^ generateNewVariableName();

		public:
			VariableTable();
			virtual ~VariableTable();

			bool addVariable(String^ name, MathObject^ mo);
			void addVariable(MathObject^ mo);
		};
	}
}
