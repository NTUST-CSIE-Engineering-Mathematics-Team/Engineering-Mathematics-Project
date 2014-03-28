#pragma once
#include "Command.h"
#include "MathObject.h"
#include "Matrix.h"
#include "Vector.h"
#include "PatternAnalyzer.h"

namespace em {
	namespace intrprt {
		namespace cmd {
			using namespace em::math; 
			using em::intrprt::pattern::PatternAnalyzer;

			ref class CreateFileMathObjectCommand : public Command {

			public:
				static property CreateFileMathObjectCommand^ createFileMatrixCommand{
					CreateFileMathObjectCommand^ get() {
						return gcnew CreateFileMathObjectCommand("M", fmcAnalyzer);
					}
				}

				static property CreateFileMathObjectCommand^ createFileVectorCommand{
					CreateFileMathObjectCommand^ get() {
						return gcnew CreateFileMathObjectCommand("V", fvcAnalyzer);
					}
				}

			private:
				static PatternAnalyzer^ fmcAnalyzer = gcnew FileMatrixConstructionAnalyzer();
				static PatternAnalyzer^ fvcAnalyzer = gcnew FileVectorConstructionAnalyzer();
				
				PatternAnalyzer^ analyzer;

			public:
				virtual ~CreateFileMathObjectCommand();

				virtual Message^ performCommand(String^ arg, Interpreter^ iptr) override;

			private:
				CreateFileMathObjectCommand(String^ cl, PatternAnalyzer^ storedAnalyzer);

			private:
				ref class FileMatrixConstructionAnalyzer : public PatternAnalyzer {

				private:
					Matrix^ tmpMat;
					Regex^ initRegex;
					int rowIndex;

				public:
					FileMatrixConstructionAnalyzer();
					virtual ~FileMatrixConstructionAnalyzer();

					virtual Message^ analyze(Match^ result, Interpreter^ iptr) override;

				protected:
					virtual String^ buildInitPattern() override;
				};

				ref class FileVectorConstructionAnalyzer : public PatternAnalyzer {

				private:
					Vector^ tmpVec;
					Regex^ initRegex;

				public:
					FileVectorConstructionAnalyzer();
					virtual ~FileVectorConstructionAnalyzer();

					virtual Message^ analyze(Match^ result, Interpreter^ iptr) override;

				protected:
					virtual String^ buildInitPattern() override;
				};
			};
		}
	}
}
