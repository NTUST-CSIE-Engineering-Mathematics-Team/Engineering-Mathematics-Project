#include "VariableTable.h"

using namespace em::intrprt;
using System::Collections::Generic::KeyValuePair;

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

bool VariableTable::deleteVariable(String^ name) {
	return this->table->Remove(name);
}

void VariableTable::load(VariableTable^ vTable) {

	for each(KeyValuePair<String^, MathObject^> pair in vTable->table) {
		this->addVariable(pair.Key, pair.Value);
	}
	
}

void VariableTable::unload(VariableTable^ vTable) {

	for each(String^ key in vTable->table->Keys) {
		this->deleteVariable(key);
	}

}

void VariableTable::clear() {
	this->table->Clear();
}

Dictionary<String^, MathObject^>::Enumerator VariableTable::getEnumerator() {
	return table->GetEnumerator();
}

String^ VariableTable::generateNewVariableName() {

	int i;
	String^ result;

	do {
		for (i = 0; i < lastGeneratedName->Length; i++) {
			if (L'z' - lastGeneratedName[i] > 0) {
				lastGeneratedName[i] = lastGeneratedName[i] + 1;
				break;
			} else {
				lastGeneratedName[i] = L'a';
			}
		}
		
		if (i == lastGeneratedName->Length) {
			lastGeneratedName->Append(L'a');
		}

		result = lastGeneratedName->ToString();
	} while (this->table->ContainsKey(lastGeneratedName->ToString()));

	return result;
}
