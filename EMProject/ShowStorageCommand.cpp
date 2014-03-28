#include "ShowStorageCommand.h"
#include "PrintCommand.h"
#include "KeywordCollection.h"
#include "Interpreter.h"
#include "All_Math.h"

using namespace em::intrprt::cmd;
using namespace em::math;

static ShowStorageCommand::ShowStorageCommand() {
	map->Add(KeywordCollection::MATRICES, Matrix::TAG);
	map->Add(KeywordCollection::VECTORS, Vector::TAG);
	map->Add(KeywordCollection::SCALARS, Scalar::TAG);
	map->Add(KeywordCollection::SETS, MathObjSet::TAG);
	map->Add(KeywordCollection::ANGLES, Angle::TAG);
}
ShowStorageCommand::ShowStorageCommand() : Command(KeywordCollection::STORAGE_CMD, 'K') {
	
}


ShowStorageCommand::~ShowStorageCommand() {
}

Message^ ShowStorageCommand::performCommand(String^ arg, Interpreter^ iptr) {

	bool isAll = arg->Equals(KeywordCollection::ALL);
	StringBuilder^ sb = gcnew StringBuilder();

	int count = 0;
	if (isAll) {
		for each(KeyValuePair<String^, MathObject^> pair in iptr->variableTable) {
			sb->AppendFormat("{0} = {1}\n", pair.Key, pair.Value->getHeader());
			count++;
		}
	} else {
		for each(KeyValuePair<String^, MathObject^> pair in iptr->variableTable) {
			if (map[arg]->Equals(pair.Value->mathType)) {
				sb->AppendFormat("{0} = {1}\n", pair.Key, pair.Value->getHeader());
				count++;
			}
		}
	}

	if (count == 0) {
		sb->Append("There is no ");
		
		if (!isAll) {
			sb->AppendFormat("{0} ", arg);
		}

		sb->Append("variable in the storage");
	} else {
		sb->Insert(0, (isAll ? "All" : this->map[arg->ToLower()])->ToLower() + " variables in the storage:\n");
	}

	return gcnew Message(Message::State::PASS, Message::STORAGE_COLOR, sb->ToString());
}