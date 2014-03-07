#include "VariableTable.h"
#include "MathObject.h"

using namespace em::intrprt;


VariableTable::VariableTable() {
	this->lastGeneratedName = gcnew StringBuilder("a");
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

void VariableTable::addVariable(MathObject^ mo) {
	this->addVariable(generateNewVariableName(), mo);
}

String^ VariableTable::generateNewVariableName() {
	int i;
	do {
		
		for (i = 0; i < this->lastGeneratedName->Length; i++) {
			if (L'z' - this->lastGeneratedName[i] < 0) {
				this->lastGeneratedName[i] = this->lastGeneratedName[i] + 1;
				break;
			} else {
				this->lastGeneratedName[i] = L'a';
			}
		}

		if (i == this->lastGeneratedName->Length) {
			this->lastGeneratedName->Append(L'a');
		}
	} while (this->table->ContainsKey(this->lastGeneratedName->ToString()));

	return this->lastGeneratedName->ToString();
}