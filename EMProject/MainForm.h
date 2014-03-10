#pragma once

#include "InterpreterFactory.h"
#include "Interpreter.h"
#include "Message.h"
#include "Matrix.h"

namespace em {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Diagnostics;
	using namespace System::IO;
	using namespace intrprt;
	/// <summary>
	/// Summary for MainForm
	/// </summary>
	public ref class MainForm : public System::Windows::Forms::Form {
	public:
		MainForm(void) {
			InitializeComponent();

			this->ofInterpreter = InterpreterFactory::createInterpreter(InterpreterFactory::InterpreterType::OBJECT_FILE);
			this->rInterpreter = InterpreterFactory::createInterpreter(InterpreterFactory::InterpreterType::RUNTIME);
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MainForm()	{
			if (components)	{
				delete components;
			}
		}
	private: System::Windows::Forms::OpenFileDialog^  openFileDialog;
	protected:

	private: System::Windows::Forms::SplitContainer^  splitContainer;
	private: System::Windows::Forms::MenuStrip^  menu;
	private: System::Windows::Forms::ToolStripMenuItem^  fileToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  openVectorFileToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  saveFileToolStripMenuItem;


	private: System::Windows::Forms::RichTextBox^  outputTextBox;

	private: System::ComponentModel::IContainer^  components;

	private: System::Windows::Forms::SaveFileDialog^  saveFileDialog;
	private: System::Windows::Forms::ToolStripMenuItem^  saveAsToolStripMenuItem;

	private: System::Windows::Forms::ToolStripMenuItem^  runToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  setTestToolStripMenuItem;


	protected:


	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		Interpreter^ rInterpreter;
	private: System::Windows::Forms::ToolStripMenuItem^  openFileToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  loadObjectFileToolStripMenuItem;
	private: System::Windows::Forms::OpenFileDialog^  openObjectFileDialog;
	private: System::Windows::Forms::RichTextBox^  inputTextBox;
			 Interpreter^ ofInterpreter;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->openFileDialog = (gcnew System::Windows::Forms::OpenFileDialog());
			this->splitContainer = (gcnew System::Windows::Forms::SplitContainer());
			this->outputTextBox = (gcnew System::Windows::Forms::RichTextBox());
			this->inputTextBox = (gcnew System::Windows::Forms::RichTextBox());
			this->menu = (gcnew System::Windows::Forms::MenuStrip());
			this->fileToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->openVectorFileToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->openFileToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->loadObjectFileToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->saveFileToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->saveAsToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->runToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->setTestToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->saveFileDialog = (gcnew System::Windows::Forms::SaveFileDialog());
			this->openObjectFileDialog = (gcnew System::Windows::Forms::OpenFileDialog());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->splitContainer))->BeginInit();
			this->splitContainer->Panel1->SuspendLayout();
			this->splitContainer->Panel2->SuspendLayout();
			this->splitContainer->SuspendLayout();
			this->menu->SuspendLayout();
			this->SuspendLayout();
			// 
			// openFileDialog
			// 
			this->openFileDialog->FileName = L"vector_or_matrix";
			this->openFileDialog->Filter = L"Text files (*.txt)|*.txt";
			this->openFileDialog->FileOk += gcnew System::ComponentModel::CancelEventHandler(this, &MainForm::openFileDialog_FileOk);
			// 
			// splitContainer
			// 
			this->splitContainer->Dock = System::Windows::Forms::DockStyle::Fill;
			this->splitContainer->Location = System::Drawing::Point(0, 24);
			this->splitContainer->Name = L"splitContainer";
			// 
			// splitContainer.Panel1
			// 
			this->splitContainer->Panel1->Controls->Add(this->outputTextBox);
			// 
			// splitContainer.Panel2
			// 
			this->splitContainer->Panel2->Controls->Add(this->inputTextBox);
			this->splitContainer->Size = System::Drawing::Size(507, 352);
			this->splitContainer->SplitterDistance = 246;
			this->splitContainer->TabIndex = 1;
			// 
			// outputTextBox
			// 
			this->outputTextBox->BackColor = System::Drawing::Color::White;
			this->outputTextBox->Dock = System::Windows::Forms::DockStyle::Fill;
			this->outputTextBox->Font = (gcnew System::Drawing::Font(L"Consolas", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->outputTextBox->ForeColor = System::Drawing::Color::Black;
			this->outputTextBox->Location = System::Drawing::Point(0, 0);
			this->outputTextBox->Name = L"outputTextBox";
			this->outputTextBox->ReadOnly = true;
			this->outputTextBox->Size = System::Drawing::Size(246, 352);
			this->outputTextBox->TabIndex = 1;
			this->outputTextBox->TabStop = false;
			this->outputTextBox->Text = L"";
			// 
			// inputTextBox
			// 
			this->inputTextBox->AcceptsTab = true;
			this->inputTextBox->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(64)), static_cast<System::Int32>(static_cast<System::Byte>(64)),
				static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->inputTextBox->Dock = System::Windows::Forms::DockStyle::Fill;
			this->inputTextBox->Font = (gcnew System::Drawing::Font(L"Consolas", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->inputTextBox->ForeColor = System::Drawing::Color::White;
			this->inputTextBox->Location = System::Drawing::Point(0, 0);
			this->inputTextBox->Name = L"inputTextBox";
			this->inputTextBox->Size = System::Drawing::Size(257, 352);
			this->inputTextBox->TabIndex = 0;
			this->inputTextBox->Text = L"#Write your instructions here";
			// 
			// menu
			// 
			this->menu->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
				this->fileToolStripMenuItem,
					this->runToolStripMenuItem, this->setTestToolStripMenuItem
			});
			this->menu->Location = System::Drawing::Point(0, 0);
			this->menu->Name = L"menu";
			this->menu->Size = System::Drawing::Size(507, 24);
			this->menu->TabIndex = 2;
			this->menu->Text = L"menu";
			// 
			// fileToolStripMenuItem
			// 
			this->fileToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
				this->openVectorFileToolStripMenuItem,
					this->saveFileToolStripMenuItem, this->saveAsToolStripMenuItem
			});
			this->fileToolStripMenuItem->Name = L"fileToolStripMenuItem";
			this->fileToolStripMenuItem->Size = System::Drawing::Size(37, 20);
			this->fileToolStripMenuItem->Text = L"File";
			// 
			// openVectorFileToolStripMenuItem
			// 
			this->openVectorFileToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->openFileToolStripMenuItem,
					this->loadObjectFileToolStripMenuItem
			});
			this->openVectorFileToolStripMenuItem->Name = L"openVectorFileToolStripMenuItem";
			this->openVectorFileToolStripMenuItem->Size = System::Drawing::Size(123, 22);
			this->openVectorFileToolStripMenuItem->Text = L"Open";
			// 
			// openFileToolStripMenuItem
			// 
			this->openFileToolStripMenuItem->Name = L"openFileToolStripMenuItem";
			this->openFileToolStripMenuItem->Size = System::Drawing::Size(168, 22);
			this->openFileToolStripMenuItem->Text = L"Open File...";
			this->openFileToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::openFileToolStripMenuItem_Click);
			// 
			// loadObjectFileToolStripMenuItem
			// 
			this->loadObjectFileToolStripMenuItem->Name = L"loadObjectFileToolStripMenuItem";
			this->loadObjectFileToolStripMenuItem->Size = System::Drawing::Size(168, 22);
			this->loadObjectFileToolStripMenuItem->Text = L"Load Object File...";
			this->loadObjectFileToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::loadObjectFileToolStripMenuItem_Click);
			// 
			// saveFileToolStripMenuItem
			// 
			this->saveFileToolStripMenuItem->Enabled = false;
			this->saveFileToolStripMenuItem->Name = L"saveFileToolStripMenuItem";
			this->saveFileToolStripMenuItem->Size = System::Drawing::Size(123, 22);
			this->saveFileToolStripMenuItem->Text = L"Save";
			this->saveFileToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::saveFileToolStripMenuItem_Click);
			// 
			// saveAsToolStripMenuItem
			// 
			this->saveAsToolStripMenuItem->Name = L"saveAsToolStripMenuItem";
			this->saveAsToolStripMenuItem->Size = System::Drawing::Size(123, 22);
			this->saveAsToolStripMenuItem->Text = L"Save As...";
			this->saveAsToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::saveAsToolStripMenuItem_Click);
			// 
			// runToolStripMenuItem
			// 
			this->runToolStripMenuItem->Name = L"runToolStripMenuItem";
			this->runToolStripMenuItem->Size = System::Drawing::Size(40, 20);
			this->runToolStripMenuItem->Text = L"Run";
			this->runToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::runToolStripMenuItem_Click_1);
			// 
			// setTestToolStripMenuItem
			// 
			this->setTestToolStripMenuItem->Name = L"setTestToolStripMenuItem";
			this->setTestToolStripMenuItem->Size = System::Drawing::Size(60, 20);
			this->setTestToolStripMenuItem->Text = L"Set Test";
			this->setTestToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::setTestToolStripMenuItem_Click);
			// 
			// saveFileDialog
			// 
			this->saveFileDialog->FileName = L"sample";
			this->saveFileDialog->Filter = L"txt files (*.txt)|*.txt";
			this->saveFileDialog->FilterIndex = 2;
			this->saveFileDialog->FileOk += gcnew System::ComponentModel::CancelEventHandler(this, &MainForm::saveFileDialog_FileOk);
			// 
			// openObjectFileDialog
			// 
			this->openObjectFileDialog->FileName = L"vector_or_matrix.txt";
			this->openObjectFileDialog->Filter = L"Text files (*.txt)|*.txt";
			this->openObjectFileDialog->FileOk += gcnew System::ComponentModel::CancelEventHandler(this, &MainForm::openObjectFileDialog_FileOk);
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(507, 376);
			this->Controls->Add(this->splitContainer);
			this->Controls->Add(this->menu);
			this->MainMenuStrip = this->menu;
			this->Name = L"MainForm";
			this->Text = L"Engineering Mathematics Application";
			this->WindowState = System::Windows::Forms::FormWindowState::Maximized;
			this->splitContainer->Panel1->ResumeLayout(false);
			this->splitContainer->Panel2->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->splitContainer))->EndInit();
			this->splitContainer->ResumeLayout(false);
			this->menu->ResumeLayout(false);
			this->menu->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

		private: System::Void openFileDialog_FileOk(System::Object^  sender, System::ComponentModel::CancelEventArgs^  e) {

			StreamReader^ reader = gcnew StreamReader(this->openFileDialog->OpenFile());
			this->inputTextBox->Clear();
			this->outputTextBox->Clear();

			for (; !reader->EndOfStream;) {
				this->inputTextBox->AppendText(reader->ReadLine() + "\n");
			}

			reader->Close();
			this->saveFileToolStripMenuItem->Enabled = true;
			this->outputTextBox->AppendText("Click \"Run\" to execute the instructions.");
		}

		private: System::Void openObjectFileDialog_FileOk(System::Object^  sender, System::ComponentModel::CancelEventArgs^  e) {
			StreamReader^ reader = gcnew StreamReader(this->openObjectFileDialog->OpenFile());
			this->outputTextBox->Clear();
			this->outputTextBox->AppendText("Load object file \"" + this->openObjectFileDialog->FileName + "\"\n");
			startInterpret(ofInterpreter, reader, false);
		}

		private: System::Void openFileToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			this->openFileDialog->ShowDialog();
		}

		private: System::Void loadObjectFileToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			this->openObjectFileDialog->ShowDialog();
		}

		private: System::Void saveFileToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			writeFile(gcnew StreamWriter(this->openFileDialog->FileName));
		}

		private: System::Void saveAsToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			this->saveFileDialog->ShowDialog();
		}

		private: System::Void saveFileDialog_FileOk(System::Object^  sender, System::ComponentModel::CancelEventArgs^  e) {
			writeFile(gcnew StreamWriter(this->saveFileDialog->OpenFile()));

		}

		private: System::Void runToolStripMenuItem_Click_1(System::Object^  sender, System::EventArgs^  e) {
			TextReader^ reader = gcnew StringReader(this->inputTextBox->Text);
			this->outputTextBox->Clear();
			startInterpret(rInterpreter, reader, true);
		}
		private: System::Void setTestToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			Matrix^ m1 = gcnew Matrix(2, 2);

			for (int i = 0; i < 2; i++) {
				for (int j = 0; j < 2; j++) {
					m1[i,j] = i - j;
				}
			}

			Matrix^ m2 = m1;

			m1[0,0] = 90;
			//m2 = m1;
			outputTextBox->AppendText(m2->ToString());

		}

		private: void writeFile(StreamWriter^ writer) {
			TextReader^ reader = gcnew StringReader(this->inputTextBox->Text);
			for (String^ line = reader->ReadLine(); line != nullptr; line = reader->ReadLine()) {
				writer->WriteLine(line);
			}
			writer->Flush();
			writer->Close();
			reader->Close();
		}
		private: void startInterpret(Interpreter^ interpreter, TextReader^ reader, bool selectError) {
			Message^ result;
			int lineIndex = -1;
			

			for (String^ line = reader->ReadLine(); line != nullptr; line = reader->ReadLine()) {
				lineIndex++;
				if (System::String::IsNullOrWhiteSpace(line)) {
					continue;
				}

				result = interpreter->interpret(line);

				if (result->msgState == Message::State::PASS) {
					handlePass(result);
					
				} else if (result->msgState == Message::State::ERROR) {
					handleError(result, lineIndex, selectError);
					break;
				}


			}
			reader->Close();
			interpreter->finishInterpret();
		}
		private: void handlePass(Message^ msg) {

			if (!String::IsNullOrEmpty(msg)) {
				this->outputTextBox->SelectionColor = msg->msgColor;
				this->outputTextBox->AppendText(msg + "\n");
				this->outputTextBox->SelectionColor = Color::Black;
			}

			delete msg;
		}

		private: void handleError(Message^ msg, int lineIndex, bool selectError) {
			this->outputTextBox->SelectionColor = Color::Red;
			this->outputTextBox->AppendText("Error occurs at line " + (lineIndex + 1) + ":\n\t");
			this->outputTextBox->AppendText(msg);
			this->outputTextBox->SelectionColor = Color::Black;
			if (selectError) {
				this->inputTextBox->Select(this->inputTextBox->GetFirstCharIndexFromLine(lineIndex), this->inputTextBox->Lines[lineIndex]->Length);
			}
			delete msg;
		}
		
	
	};

		
}
