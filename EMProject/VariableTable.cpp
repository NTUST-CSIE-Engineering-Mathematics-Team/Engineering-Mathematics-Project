#include "VariableTable.h"
#include "ShowStorageCommand.h"

using namespace em::intrprt;
using namespace em::intrprt::cmd;

using System::Collections::Generic::KeyValuePair;

using System::Collections::Generic::IEnumerator;

VariableTable::VariableTable() {
	this->lastGeneratedName = gcnew StringBuilder(System::Convert::ToString((wchar_t)(L'a' - 1)));
}

static VariableTable::VariableTable() {
	stgSetCreators->Add(KeywordCollection::SCALARS, gcnew CreateStorageSet(&createStgSet<Scalar^>));
	stgSetCreators->Add(KeywordCollection::VECTORS, gcnew CreateStorageSet(&createStgSet<Vector^>));
	stgSetCreators->Add(KeywordCollection::MATRICES, gcnew CreateStorageSet(&createStgSet<Matrix^>));
	stgSetCreators->Add(KeywordCollection::SETS, gcnew CreateStorageSet(&createStgSet<MathObjSet^>));
	stgSetCreators->Add(KeywordCollection::ANGLES, gcnew CreateStorageSet(&createStgSet<Angle^>));
	
	tnMap->Add(KeywordCollection::SCALARS, Scalar::TAG);
	tnMap->Add(KeywordCollection::VECTORS, Vector::TAG);
	tnMap->Add(KeywordCollection::MATRICES, Matrix::TAG);
	tnMap->Add(KeywordCollection::SETS, MathObjSet::TAG);
	tnMap->Add(KeywordCollection::ANGLES, Angle::TAG);
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

bool VariableTable::contains(String^ name) {

	return MappingTable<String^, MathObject^>::contains(name) || typeSetNameMap->ContainsKey(name);
}

bool VariableTable::deleteVariable(String^ name) {
	if (typeSetNameMap->ContainsKey(name)) {
		LinkedList<String^>^ varNameList = gcnew LinkedList<String^>();
		String^ typeName = this->typeSetNameMap[name];
		for each(KeyValuePair<String^, MathObject^> pair in this->table) {
			if (pair.Value->mathType->Equals(typeName)) {
				varNameList->AddLast(pair.Key);
			}
		}

		for each(String^ varName in varNameList) {
			this->table->Remove(varName);
		}
	}

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

System::Collections::Generic::IEnumerator<KeyValuePair<String^, MathObject^>>^ VariableTable::GetEnumerator() {
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


System::Collections::IEnumerator^ VariableTable::GetNGEnumerator() {
	return this->GetEnumerator();
}

generic<typename M> where M : MathObject
MathObjSet^ VariableTable::createStgSet(VariableTable^ vTable) {
	MathObjSet^ set = gcnew MathObjGenericSet<M>();
	for each(KeyValuePair<String^, MathObject^> pair in vTable) {
		set->add(pair.Value);
	}

	return set;
}
