#include "ShowStorageCommand.h"
#include "PrintCommand.h"
#include "KeywordCollection.h"
#include "Interpreter.h"
#include "Matrix.h"
#include "Vector.h"
#include "Scalar.h"

using namespace em::intrprt::cmd;
using namespace em::math;
ShowStorageCommand::ShowStorageCommand() : Command(KeywordCollection::STORAGE_CMD, "", "C") {
	this->map = gcnew Dictionary<String^, String^>(3);
	this->map->Add("M", Matrix::tag);
	this->map->Add("V", Vector::tag);
	this->map->Add("S", Scalar::tag);
}


ShowStorageCommand::~ShowStorageCommand() {
}

Message^ ShowStorageCommand::performCommand(array<String^>^ args, int typeIndex, Interpreter^ iptr) {

	Dictionary<String^, MathObject^>::Enumerator e = iptr->variableTable->getEnumerator();

	
	StringBuilder^ sb = gcnew StringBuilder();
	KeyValuePair<String^, MathObject^> pair;
	int count = 0;
	if (typeIndex == 0) {
		for (; e.MoveNext(); count++) {
			pair = e.Current;
			sb->AppendFormat("{0}\n", PrintCommand::buildHeader(pair.Value, pair.Key));
		}
	} else {
		String^ t = args[0]->ToUpper();
		if (!this->map->ContainsKey(t)) {
			return gcnew Message(Message::State::ERROR, "cannot find the type flag \"" + t + "\"");
		}
		t = this->map[t];

		for (; e.MoveNext(); ) {
			pair = e.Current;
			if (t->Equals(pair.Value->mathType)) {
				sb->AppendFormat("{0}\n", PrintCommand::buildHeader(pair.Value, pair.Key));
				count++;
			}
		}
	}

	if (count == 0) {
		sb->Append("There is no ");
		
		if (typeIndex == 1) {
			sb->AppendFormat("{0} ", this->map[args[0]->ToUpper()]->ToLower());
		}

		sb->Append("variable");
	} else {
		sb->Insert(0, (typeIndex == 0 ? "All" : this->map[args[0]->ToUpper()]) + " variables in the storage:\n");
	}

	return gcnew Message(Message::State::PASS, sb->ToString(), Message::STORAGE_COLOR);
}