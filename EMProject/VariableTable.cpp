#include "VariableTable.h"

using namespace em::intrprt;


VariableTable::VariableTable() {
	this->lastGeneratedName = gcnew StringBuilder(System::Convert::ToString((wchar_t)(L'a' - 1)));
}


VariableTable::~VariableTable() {
	delete this->lastGeneratedName;
}

bool VariableTable::addVariable(String^ name, MathObject^ mo) {
	if (this->table->ContainsKey(name)) {
		return false;
	}

	this->table->Add(name, mo);
	return true;
}

String^ VariableTable::addVariable(MathObject^ mo) {
	String^ newName = generateNewVariableName();
	this->addVariable(newName, mo);
	return newName;
}

String^ VariableTable::generateNewVariableName() {
	int i;
	String^ result;

	do {
		for (i = 0; i < this->lastGeneratedName->Length; i++) {
			if (L'z' - this->lastGeneratedName[i] > 0) {
				this->lastGeneratedName[i] = this->lastGeneratedName[i] + 1;
				break;
			} else {
				this->lastGeneratedName[i] = L'a';
			}
		}
		
		if (i == this->lastGeneratedName->Length) {
			this->lastGeneratedName->Append(L'a');
		}
		result = this->lastGeneratedName->ToString();
	} while (this->table->ContainsKey(this->lastGeneratedName->ToString()));

	return result;
}