#pragma once

#include <string>

#include "GameNumberKnot.h"

namespace NumberKnot_WithGUI {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Graphical representation of Puzzle and game.
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//my code --------------------------------------------------------------------- begin

			LoadNewPuzzle();

			//my code --------------------------------------------------------------------- end
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
				delete puzzle;
				delete game;
			}
		}
	private: System::Windows::Forms::Button^  buttonNextLevel;
	protected:
	private: System::Windows::Forms::Button^  buttonReset;
	private: System::Windows::Forms::Button^  buttonStepBack;
	private: System::Windows::Forms::Label^  labelMaxNum;
	private: System::Windows::Forms::Label^  labelNextNum;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Panel^  panel;
	private:
		/// <summary>
		/// Required designer variable.
		// my variables----------------------------------------------------------------------------------- begin

		GameNumberKnot * game = new GameNumberKnot();
		Puzzle * puzzle;
		
		int height, width; /*Dimension of puzzle (Puzzle*)*/
		int deltaX, deltaY; /*Offset for accurate drawing location in window.*/
		bool won = false;

		void AdjustDeltas();
		System::String^ IntToSysStr(int i);

		void LoadNewPuzzle();
		void EraseOldPuzzle();
		void Update();
		void ButtonClicked(Object^ sender, EventArgs^ e);
		void ShowWonMessage();

		// my variables----------------------------------------------------------------------------------- end
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(MyForm::typeid));
			this->buttonNextLevel = (gcnew System::Windows::Forms::Button());
			this->buttonReset = (gcnew System::Windows::Forms::Button());
			this->buttonStepBack = (gcnew System::Windows::Forms::Button());
			this->labelMaxNum = (gcnew System::Windows::Forms::Label());
			this->labelNextNum = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->panel = (gcnew System::Windows::Forms::Panel());
			this->SuspendLayout();
			// 
			// buttonNextLevel
			// 
			this->buttonNextLevel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->buttonNextLevel->Location = System::Drawing::Point(402, 287);
			this->buttonNextLevel->Name = L"buttonNextLevel";
			this->buttonNextLevel->Size = System::Drawing::Size(116, 30);
			this->buttonNextLevel->TabIndex = 111;
			this->buttonNextLevel->Text = L"Next Level";
			this->buttonNextLevel->UseVisualStyleBackColor = true;
			this->buttonNextLevel->Click += gcnew System::EventHandler(this, &MyForm::buttonNextLevel_Click);
			// 
			// buttonReset
			// 
			this->buttonReset->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->buttonReset->Location = System::Drawing::Point(402, 241);
			this->buttonReset->Name = L"buttonReset";
			this->buttonReset->Size = System::Drawing::Size(116, 30);
			this->buttonReset->TabIndex = 110;
			this->buttonReset->Text = L"Reset";
			this->buttonReset->UseVisualStyleBackColor = true;
			this->buttonReset->Click += gcnew System::EventHandler(this, &MyForm::buttonReset_Click);
			// 
			// buttonStepBack
			// 
			this->buttonStepBack->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->buttonStepBack->Location = System::Drawing::Point(402, 195);
			this->buttonStepBack->Name = L"buttonStepBack";
			this->buttonStepBack->Size = System::Drawing::Size(116, 30);
			this->buttonStepBack->TabIndex = 109;
			this->buttonStepBack->Text = L"Step Back";
			this->buttonStepBack->UseVisualStyleBackColor = true;
			this->buttonStepBack->Click += gcnew System::EventHandler(this, &MyForm::buttonStepBack_Click);
			// 
			// labelMaxNum
			// 
			this->labelMaxNum->AutoSize = true;
			this->labelMaxNum->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->labelMaxNum->Location = System::Drawing::Point(520, 132);
			this->labelMaxNum->Name = L"labelMaxNum";
			this->labelMaxNum->Size = System::Drawing::Size(25, 26);
			this->labelMaxNum->TabIndex = 108;
			this->labelMaxNum->Text = L"0";
			// 
			// labelNextNum
			// 
			this->labelNextNum->AutoSize = true;
			this->labelNextNum->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->labelNextNum->Location = System::Drawing::Point(520, 78);
			this->labelNextNum->Name = L"labelNextNum";
			this->labelNextNum->Size = System::Drawing::Size(25, 26);
			this->labelNextNum->TabIndex = 107;
			this->labelNextNum->Text = L"0";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->label2->Location = System::Drawing::Point(374, 132);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(140, 24);
			this->label2->TabIndex = 106;
			this->label2->Text = L"MAX number:";
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->label1->Location = System::Drawing::Point(374, 78);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(137, 24);
			this->label1->TabIndex = 105;
			this->label1->Text = L"Next number:";
			// 
			// panel
			// 
			this->panel->Location = System::Drawing::Point(0, 0);
			this->panel->Name = L"panel";
			this->panel->Size = System::Drawing::Size(370, 360);
			this->panel->TabIndex = 112;
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(584, 362);
			this->Controls->Add(this->panel);
			this->Controls->Add(this->buttonNextLevel);
			this->Controls->Add(this->buttonReset);
			this->Controls->Add(this->buttonStepBack);
			this->Controls->Add(this->labelMaxNum);
			this->Controls->Add(this->labelNextNum);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->MaximizeBox = false;
			this->Name = L"MyForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Number Knot";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

	private: System::Void buttonStepBack_Click(System::Object^  sender, System::EventArgs^  e) {
		puzzle->StepBack();
		won = false;
		Update();
	}

	private: System::Void buttonReset_Click(System::Object^  sender, System::EventArgs^  e) {
		puzzle->Reset();
		won = false;
		Update();
	}

	private: System::Void buttonNextLevel_Click(System::Object^  sender, System::EventArgs^  e) {
		if (won)
		{
			EraseOldPuzzle();
			LoadNewPuzzle();
			won = false;
		}
	}


	};
}
