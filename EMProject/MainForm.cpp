#include "MainForm.h"

using namespace System;
using namespace System::Windows::Forms;
using namespace em;

[STAThread]
void Main(array<String^>^ args)
{	
	

	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	System::Drawing::Color s = Color();
	Application::Run(gcnew em::MainForm);
}

