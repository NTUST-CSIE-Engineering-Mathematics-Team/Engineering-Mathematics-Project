#pragma once
#include "Interpreter.h"
#include "All_Commands.h"
#include "All_Patterns.h"
namespace em {
	namespace intrprt {
		using namespace cmd;

		ref class InterpreterFactory {

		public:
			enum class InterpreterType { OBJECT_FILE, RUNTIME };

		private:
			InterpreterFactory();

		public:
			virtual ~InterpreterFactory();

			static Interpreter^ createInterpreter(InterpreterType type);

		private:
			ref class RuntimeInterpreter : public Interpreter {

			private:
				static array<Command^>^ commands = {
					gcnew PrintCommand(),
					gcnew CreateMatrixCommand(),
					gcnew CreateVectorCommand(),
					gcnew CreateScalarCommand(),
					gcnew SettingsCommand(),
					gcnew DeleteCommand(),
					gcnew ShowStorageCommand()
				};

				static array<PatternAnalyzer^>^ analyzers = {
					gcnew CommentPatternAnalyzer(), 
					gcnew CommandPatternAnalyzer(commands) 
				};

			public:
				RuntimeInterpreter();
				virtual ~RuntimeInterpreter();

				virtual void finishInterpret() override;

			};

			ref class ObjectFileInterpreter : public Interpreter {

			private:
				static array<Command^>^ commands = {
					CreateFileMathObjectCommand::createFileMatrixCommand,
					CreateFileMathObjectCommand::createFileVectorCommand
				};

				static array<PatternAnalyzer^>^ analyzers = {
					gcnew FileCommandPatternAnalyzer(commands)
				};

			public:
				ObjectFileInterpreter();
				virtual ~ObjectFileInterpreter();

				virtual void finishInterpret() override;
			};
		};
	}
}