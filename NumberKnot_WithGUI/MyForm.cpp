#include "MyForm.h"

using namespace System;
using namespace System::Windows::Forms;

/*
	Name: Emanuel Zaymus
	Number of group: 5ZY021
	Number Knot is a game where you are given a grid with just a few numbers filled in. 
	You must then build an ascending sequence of numbers going sideways or diagonally.
*/

[STAThread]
void main(cli::array<String^>^ args)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	NumberKnot_WithGUI::MyForm form;
	Application::Run(%form);
}

/*Adjusts deltas (deltaX, deltaY) depending on attributes widht and height for accurate drawing location in window.*/
void NumberKnot_WithGUI::MyForm::AdjustDeltas()
{
	if (width == 4 && height == 4)
		deltaX = 89, deltaY = 89;
	else if (width == 5 && height == 4)
		deltaX = 72, deltaY = 89;
	else if (width == 5 && height == 5)
		deltaX = 72, deltaY = 72;
	else if (width == 5 && height == 6)
		deltaX = 72, deltaY = 48;
	else if (width == 6 && height == 6)
		deltaX = 48, deltaY = 48;
	else if (width == 7 && height == 6)
		deltaX = 24, deltaY = 48;
	else if (width == 7 && height == 7)
		deltaX = 24, deltaY = 24;
}

/*Converts int to System::String^.*/
System::String^ NumberKnot_WithGUI::MyForm::IntToSysStr(int i)
{
	return gcnew System::String(std::to_string(i).c_str());
}

/*Loads new puzzle, sets attributes height, widht; creates System::Windows::Forms::Button^s according to loaded puzzle.*/
void NumberKnot_WithGUI::MyForm::LoadNewPuzzle()
{
	puzzle = game->GetNext();
	height = puzzle->GetHeight();
	width = puzzle->GetWidth();

	AdjustDeltas();
	for (size_t y = 0; y < height; y++)
	{
		for (size_t x = 0; x < width; x++)
		{
			System::Windows::Forms::Button^  b = (gcnew System::Windows::Forms::Button());
			if (puzzle->Get(y, x) == 0)
			{
				b->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 13.25F, System::Drawing::FontStyle::Regular,
					System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(238)));
				b->Text = "";
			}
			else if (puzzle->Get(y, x) > 0) {
				b->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Bold,
					System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(238)));
				b->Text = IntToSysStr(puzzle->Get(y, x));
				b->ForeColor = SystemColors::Control.MediumBlue;
			}
			else
			{
				b->Hide();
			}
			b->Location = System::Drawing::Point(x * 46 + deltaX, y * 46 + deltaY);
			b->Size = System::Drawing::Size(40, 40);
			b->UseVisualStyleBackColor = true;
			b->Click += gcnew EventHandler(this, &MyForm::ButtonClicked);
			panel->Controls->Add(b);
		}
	}
	labelMaxNum->Text = IntToSysStr(puzzle->GetCountOfFields());
	labelNextNum->Text = IntToSysStr(puzzle->GetNextNumber());
}

/*Hides and clears all buttons; deletes puzzle.*/
void NumberKnot_WithGUI::MyForm::EraseOldPuzzle()
{
	for each (Control^ control in panel->Controls)
		control->Hide();

	panel->Controls->Clear();
	delete puzzle;
}

/*Updates every button in puzzle; sets Text in labelNextNum.*/
void NumberKnot_WithGUI::MyForm::Update()
{
	if (puzzle->GetNextNumber() > puzzle->GetCountOfFields())
		labelNextNum->Text = "--";
	else
		labelNextNum->Text = IntToSysStr(puzzle->GetNextNumber());

	int i = 0;
	for each(Control^ control in panel->Controls) {
		int y = (i / width), x = (i % width);
		if (puzzle->Get(y, x) == 0)
			control->Text = "";
		else if (puzzle->Get(y, x) > 0)
			control->Text = IntToSysStr(puzzle->Get(y, x));
		i++;
	}
}

/*Click method for puzzle buttons; calls PutNumber method in puzzle; sets attribute won.*/
void NumberKnot_WithGUI::MyForm::ButtonClicked(Object ^ sender, EventArgs ^ e)
{
	int i = 0;
	for each(Control^ control in panel->Controls) {
		if (sender == control)
		{
			won = puzzle->PutNumber(i / width, i % width);
			Update();
			if (won)
				ShowWonMessage();
			return;
		}
		i++;
	}
}

/*Shows short won message in MessageBox.*/
void NumberKnot_WithGUI::MyForm::ShowWonMessage()
{
	int option = rand() % 5;
	System::String^ s = gcnew System::String("");
	switch (option)
	{
	case 0:
		s = "GREAT !";
		break;
	case 1:
		s = "PERFECT !";
		break;
	case 2:
		s = "WELL DONE !";
		break;
	case 3:
		s = "NICE !";
		break;
	case 4:
		s = "GOOD JOB !";
		break;
	default:
		break;
	}
	MessageBox::Show(s, "Done");
}
