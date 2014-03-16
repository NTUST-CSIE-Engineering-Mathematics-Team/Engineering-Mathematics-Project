#include "InterpreterFactory.h"

using namespace em::intrprt;

InterpreterFactory::InterpreterFactory() {
}


InterpreterFactory::~InterpreterFactory() {
}

Interpreter^ InterpreterFactory::createInterpreter(InterpreterType type) {

	switch (type) {
		case InterpreterType::OBJECT_FILE :
			return gcnew ObjectFileInterpreter();
		case InterpreterType::RUNTIME :
			return gcnew RuntimeInterpreter();
	}

	return nullptr;
}
InterpreterFactory::RuntimeInterpreter::RuntimeInterpreter() : Interpreter(analyzers) {
	
}

InterpreterFactory::RuntimeInterpreter::~RuntimeInterpreter() {
}

void InterpreterFactory::RuntimeInterpreter::finishInterpret() {
	this->releaseNextLine();
	this->variableTable->unload(nullptr);

}

InterpreterFactory::ObjectFileInterpreter::ObjectFileInterpreter() : Interpreter(analyzers) {
}

InterpreterFactory::ObjectFileInterpreter::~ObjectFileInterpreter() {
}

void InterpreterFactory::ObjectFileInterpreter::finishInterpret() {
	this->releaseNextLine();
	this->variableTable->clear();
}
