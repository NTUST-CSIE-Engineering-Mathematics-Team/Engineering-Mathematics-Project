#include "ShowStorageCommand.h"
#include "PrintCommand.h"
#include "KeywordCollection.h"
#include "Interpreter.h"
#include "Matrix.h"
#include "Vector.h"
#include "Scalar.h"

using namespace em::intrprt::cmd;
using namespace em::math;
ShowStorageCommand::ShowStorageCommand() : Command(KeywordCollection::STORAGE_CMD, 'K') {
	this->map = gcnew Dictionary<String^, String^>(3);
	this->map->Add(KeywordCollection::MATRIX, Matrix::TAG);
	this->map->Add(KeywordCollection::VECTOR, Vector::TAG);
	this->map->Add(KeywordCollection::SCALAR, Scalar::TAG);
}


ShowStorageCommand::~ShowStorageCommand() {
}

Message^ ShowStorageCommand::performCommand(String^ arg, Interpreter^ iptr) {

	Dictionary<String^, MathObject^>::Enumerator e = iptr->variableTable->getEnumerator();

	bool isAll = arg->Equals(KeywordCollection::ALL);
	StringBuilder^ sb = gcnew StringBuilder();
	KeyValuePair<String^, MathObject^> pair;
	int count = 0;
	if (isAll) {
		for (; e.MoveNext(); count++) {
			pair = e.Current;
			sb->AppendFormat("{0}\n", PrintCommand::buildHeader(pair.Value, pair.Key));
		}
	} else {
		
		arg = this->map[arg];

		for (; e.MoveNext(); ) {
			pair = e.Current;
			if (arg->Equals(pair.Value->mathType)) {
				sb->AppendFormat("{0}\n", PrintCommand::buildHeader(pair.Value, pair.Key));
				count++;
			}
		}
	}

	if (count == 0) {
		sb->Append("There is no ");
		
		if (!isAll) {
			sb->AppendFormat("{0} ", arg);
		}

		sb->Append("variable");
	} else {
		sb->Insert(0, (isAll ? "All" : this->map[arg->ToLower()])->ToLower() + " variables in the storage:\n");
	}

	return gcnew Message(Message::State::PASS, Message::STORAGE_COLOR, sb->ToString());
}