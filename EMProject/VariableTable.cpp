#include "VariableTable.h"
#include "MathObject.h"

using em::intrprt::VariableTable;
using System::String;
using em::math::MathObject;

VariableTable::VariableTable() {
	this->lastGeneratedName = gcnew StringBuilder("a");
}


VariableTable::~VariableTable() {
	delete this->lastGeneratedName;
}

bool VariableTable::addVariable(String^ name, MathObject^ mo) {
	if (this->map->ContainsKey(name)) {
		return false;
	}

	this->map->Add(name, mo);
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
	} while (this->map->ContainsKey(this->lastGeneratedName->ToString()));

	return this->lastGeneratedName->ToString();
}