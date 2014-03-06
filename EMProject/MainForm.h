#pragma once
#include "CommandInterpreter.h"
#include "Message.h"

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
			this->interpreter = gcnew CommandInterpreter();
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
	private: System::Windows::Forms::Button^  runButton;
	private: System::Windows::Forms::Panel^  bottomPanel;
	private: System::Windows::Forms::RichTextBox^  outputTextBox;
	private: System::Windows::Forms::RichTextBox^  inputTextBox;
	private: System::ComponentModel::IContainer^  components;
	private: System::Windows::Forms::Label^  intprtMsgLabel;
	private: System::Windows::Forms::SaveFileDialog^  saveFileDialog;
	private: System::Windows::Forms::ToolStripMenuItem^  saveAsToolStripMenuItem;

	protected:


	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		CommandInterpreter^ interpreter;

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
			this->saveFileToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->saveAsToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->runButton = (gcnew System::Windows::Forms::Button());
			this->bottomPanel = (gcnew System::Windows::Forms::Panel());
			this->intprtMsgLabel = (gcnew System::Windows::Forms::Label());
			this->saveFileDialog = (gcnew System::Windows::Forms::SaveFileDialog());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->splitContainer))->BeginInit();
			this->splitContainer->Panel1->SuspendLayout();
			this->splitContainer->Panel2->SuspendLayout();
			this->splitContainer->SuspendLayout();
			this->menu->SuspendLayout();
			this->bottomPanel->SuspendLayout();
			this->SuspendLayout();
			// 
			// openFileDialog
			// 
			this->openFileDialog->FileName = L"vector_or_matrix";
			this->openFileDialog->Filter = L"Text files (*.txt)|*.txt";
			this->openFileDialog->FileOk += gcnew System::ComponentModel::CancelEventHandler(this, &MainForm::openVecDialog_FileOk);
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
			this->splitContainer->Size = System::Drawing::Size(426, 242);
			this->splitContainer->SplitterDistance = 207;
			this->splitContainer->TabIndex = 1;
			// 
			// outputTextBox
			// 
			this->outputTextBox->BackColor = System::Drawing::Color::White;
			this->outputTextBox->Dock = System::Windows::Forms::DockStyle::Fill;
			this->outputTextBox->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(136)));
			this->outputTextBox->ForeColor = System::Drawing::SystemColors::WindowText;
			this->outputTextBox->Location = System::Drawing::Point(0, 0);
			this->outputTextBox->Name = L"outputTextBox";
			this->outputTextBox->ReadOnly = true;
			this->outputTextBox->Size = System::Drawing::Size(207, 242);
			this->outputTextBox->TabIndex = 1;
			this->outputTextBox->TabStop = false;
			this->outputTextBox->Text = L"";
			// 
			// inputTextBox
			// 
			this->inputTextBox->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(64)), static_cast<System::Int32>(static_cast<System::Byte>(64)),
				static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->inputTextBox->Dock = System::Windows::Forms::DockStyle::Fill;
			this->inputTextBox->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->inputTextBox->ForeColor = System::Drawing::Color::White;
			this->inputTextBox->Location = System::Drawing::Point(0, 0);
			this->inputTextBox->Name = L"inputTextBox";
			this->inputTextBox->Size = System::Drawing::Size(215, 242);
			this->inputTextBox->TabIndex = 0;
			this->inputTextBox->Text = L"";
			// 
			// menu
			// 
			this->menu->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->fileToolStripMenuItem });
			this->menu->Location = System::Drawing::Point(0, 0);
			this->menu->Name = L"menu";
			this->menu->Size = System::Drawing::Size(426, 24);
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
			this->openVectorFileToolStripMenuItem->Name = L"openVectorFileToolStripMenuItem";
			this->openVectorFileToolStripMenuItem->Size = System::Drawing::Size(133, 22);
			this->openVectorFileToolStripMenuItem->Text = L"Open File...";
			this->openVectorFileToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::openVectorFileToolStripMenuItem_Click);
			// 
			// saveFileToolStripMenuItem
			// 
			this->saveFileToolStripMenuItem->Enabled = false;
			this->saveFileToolStripMenuItem->Name = L"saveFileToolStripMenuItem";
			this->saveFileToolStripMenuItem->Size = System::Drawing::Size(133, 22);
			this->saveFileToolStripMenuItem->Text = L"Save";
			this->saveFileToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::saveFileToolStripMenuItem_Click);
			// 
			// saveAsToolStripMenuItem
			// 
			this->saveAsToolStripMenuItem->Name = L"saveAsToolStripMenuItem";
			this->saveAsToolStripMenuItem->Size = System::Drawing::Size(133, 22);
			this->saveAsToolStripMenuItem->Text = L"Save As...";
			this->saveAsToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::saveAsToolStripMenuItem_Click);
			// 
			// runButton
			// 
			this->runButton->Dock = System::Windows::Forms::DockStyle::Right;
			this->runButton->Location = System::Drawing::Point(351, 0);
			this->runButton->Name = L"runButton";
			this->runButton->Size = System::Drawing::Size(75, 33);
			this->runButton->TabIndex = 0;
			this->runButton->Text = L"Run";
			this->runButton->UseVisualStyleBackColor = true;
			this->runButton->Click += gcnew System::EventHandler(this, &MainForm::runButton_Click);
			// 
			// bottomPanel
			// 
			this->bottomPanel->Controls->Add(this->intprtMsgLabel);
			this->bottomPanel->Controls->Add(this->runButton);
			this->bottomPanel->Dock = System::Windows::Forms::DockStyle::Bottom;
			this->bottomPanel->Location = System::Drawing::Point(0, 266);
			this->bottomPanel->Name = L"bottomPanel";
			this->bottomPanel->Size = System::Drawing::Size(426, 33);
			this->bottomPanel->TabIndex = 3;
			// 
			// intprtMsgLabel
			// 
			this->intprtMsgLabel->Dock = System::Windows::Forms::DockStyle::Fill;
			this->intprtMsgLabel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9));
			this->intprtMsgLabel->ForeColor = System::Drawing::Color::Red;
			this->intprtMsgLabel->Location = System::Drawing::Point(0, 0);
			this->intprtMsgLabel->Name = L"intprtMsgLabel";
			this->intprtMsgLabel->Size = System::Drawing::Size(351, 33);
			this->intprtMsgLabel->TabIndex = 1;
			this->intprtMsgLabel->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// saveFileDialog
			// 
			this->saveFileDialog->FileName = L"sample";
			this->saveFileDialog->Filter = L"txt files (*.txt)|*.txt";
			this->saveFileDialog->FilterIndex = 2;
			this->saveFileDialog->FileOk += gcnew System::ComponentModel::CancelEventHandler(this, &MainForm::saveFileDialog_FileOk);
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(426, 299);
			this->Controls->Add(this->splitContainer);
			this->Controls->Add(this->bottomPanel);
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
			this->bottomPanel->ResumeLayout(false);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

		private: System::Void openVecDialog_FileOk(System::Object^  sender, System::ComponentModel::CancelEventArgs^  e) {

			StreamReader^ reader = gcnew StreamReader(this->openFileDialog->OpenFile());
			this->inputTextBox->Clear();
			for (; !reader->EndOfStream;) {
				this->inputTextBox->AppendText(reader->ReadLine() + "\n");
			}

			reader->Close();
			this->saveFileToolStripMenuItem->Enabled = true;
			/*for (;!reader->EndOfStream;) {
				array<String^>^ header = reader->ReadLine()->Split(' ');

				if (header->Length != 3) {
					continue;
				}

				wchar_t type = Convert::ToChar(header[0]);
				String^ name = header[2];

				this->outputTextBox->AppendText(name + " = \n");
				if (type == L'V') {

					int dim = Convert::ToInt32(header[1]);
					array<String^>^ vecS = reader->ReadLine()->Split(' ');
					array<double>^ vec = gcnew array<double>(dim);
				
					for (int i = 0; i < dim; i++) {
						vec[i] = Convert::ToDouble(vecS[i]);
						this->outputTextBox->AppendText(vec[i] + " ");
					}
					this->outputTextBox->AppendText(L"\n");

				} else if (type == L'M') {

					array<String^>^ dimS = header[1]->Split('x');
					int dim1 = Convert::ToInt32(dimS[0]);
					int dim2 = Convert::ToInt32(dimS[1]);
					array<String^>^ matRowS;
					array<double, 2>^ mat = gcnew array<double, 2>(dim1, dim2);

					for (int i = 0; i < dim1; i++) {
						matRowS = reader->ReadLine()->Split(' ');
						for (int j = 0; j < dim2; j++) {
							mat[i, j] = Convert::ToDouble(matRowS[j]);
							this->outputTextBox->AppendText(mat[i, j] + " ");
						}
						this->outputTextBox->AppendText(L"\n");
					}
				}
				this->outputTextBox->AppendText(L"\n");
			}
			reader->Close();
			*/

		}
		
		private: System::Void openVectorFileToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
				 this->openFileDialog->ShowDialog();
		}
		private: System::Void runButton_Click(System::Object^  sender, System::EventArgs^  e) {
					 TextReader^ reader = gcnew StringReader(this->inputTextBox->Text);
					 
					 for (String^ line = reader->ReadLine(); line != nullptr; line = reader->ReadLine()) {
						
						 Message^ result = interpreter->inetrpret(line);
						 String^ msg = result->msgContent;
						 if (result->msgType == Message::Type::Pass) {
							 if (!String::IsNullOrEmpty(msg)) {
								 this->outputTextBox->AppendText(msg + "\n");
							 }
						 } else if (result->msgType == Message::Type::Error) {
							 this->intprtMsgLabel->Text = msg;
							 break;
						 }
					 }

					 reader->Close();
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
		private: void writeFile(StreamWriter^ writer) {
			TextReader^ reader = gcnew StringReader(this->inputTextBox->Text);
			for (String^ line = reader->ReadLine(); line != nullptr; line = reader->ReadLine()) {
				writer->WriteLine(line);
			}
			writer->Flush();
			writer->Close();
			reader->Close();
		}
	};
}
