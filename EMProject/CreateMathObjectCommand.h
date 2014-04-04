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
			private:
				ref class FilePatternAnalyzer abstract : public PatternAnalyzer {

				protected:
					Regex^ initRegex;

				public:
					FilePatternAnalyzer();
					virtual ~FilePatternAnalyzer();
					virtual void reset(Interpreter^ iptr) abstract;

				protected:
					Message^ wrongFormatMsg(Interpreter^ iptr);
				};

				ref class FileMatrixConstructionAnalyzer : public FilePatternAnalyzer {

				private:
					Matrix^ tmpMat;
					int rowIndex;

					
				public:
					FileMatrixConstructionAnalyzer();
					virtual ~FileMatrixConstructionAnalyzer();

					virtual Message^ analyze(Match^ result, Interpreter^ iptr) override;
					virtual void reset(Interpreter^ iptr) override;
				protected:
					virtual String^ buildInitPattern() override;


				};

				ref class FileVectorConstructionAnalyzer : public FilePatternAnalyzer {

				private:
					Vector^ tmpVec;

				public:
					FileVectorConstructionAnalyzer();
					virtual ~FileVectorConstructionAnalyzer();

					virtual Message^ analyze(Match^ result, Interpreter^ iptr) override;
					virtual void reset(Interpreter^ iptr) override;
				protected:
					virtual String^ buildInitPattern() override;

				};

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
				static FilePatternAnalyzer^ fmcAnalyzer = gcnew FileMatrixConstructionAnalyzer();
				static FilePatternAnalyzer^ fvcAnalyzer = gcnew FileVectorConstructionAnalyzer();
				
				FilePatternAnalyzer^ analyzer;

			public:
				virtual ~CreateFileMathObjectCommand();

				virtual Message^ performCommand(String^ arg, Interpreter^ iptr) override;

			private:
				CreateFileMathObjectCommand(String^ cl, FilePatternAnalyzer^ storedAnalyzer);

			
			};
		}
	}
}
