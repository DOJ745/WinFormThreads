#pragma once
#include "MyController.h"
namespace WinFormThreads 
{

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for Form1
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	private:
		MyController^ myController;

	public:
		Form1(void): myController(gcnew MyController())
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//

			// Подписываемся на событие завершения потока
			myController->GetThreadManager()->m_ThreadCompleted += gcnew EventHandler(this, &Form1::OnThreadCompleted);
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  UI_BTN_START_THREAD;
	protected: 
	private: System::Windows::Forms::GroupBox^  groupBox1;
	private: System::Windows::Forms::Button^  UI_BTN_STOP_THREAD;
	private: System::Windows::Forms::Label^  statusLabel;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->UI_BTN_START_THREAD = (gcnew System::Windows::Forms::Button());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->UI_BTN_STOP_THREAD = (gcnew System::Windows::Forms::Button());
			this->statusLabel = (gcnew System::Windows::Forms::Label());
			this->groupBox1->SuspendLayout();
			this->SuspendLayout();
			// 
			// UI_BTN_START_THREAD
			// 
			this->UI_BTN_START_THREAD->Location = System::Drawing::Point(43, 115);
			this->UI_BTN_START_THREAD->Name = L"UI_BTN_START_THREAD";
			this->UI_BTN_START_THREAD->Size = System::Drawing::Size(112, 54);
			this->UI_BTN_START_THREAD->TabIndex = 0;
			this->UI_BTN_START_THREAD->Text = L"START";
			this->UI_BTN_START_THREAD->UseVisualStyleBackColor = true;
			this->UI_BTN_START_THREAD->Click += gcnew System::EventHandler(this, &Form1::UI_BTN_START_THREAD_Click);
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->statusLabel);
			this->groupBox1->Controls->Add(this->UI_BTN_STOP_THREAD);
			this->groupBox1->Controls->Add(this->UI_BTN_START_THREAD);
			this->groupBox1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(204)));
			this->groupBox1->Location = System::Drawing::Point(128, 12);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(327, 189);
			this->groupBox1->TabIndex = 1;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"THREAD OPERATIONS";
			// 
			// UI_BTN_STOP_THREAD
			// 
			this->UI_BTN_STOP_THREAD->Location = System::Drawing::Point(175, 115);
			this->UI_BTN_STOP_THREAD->Name = L"UI_BTN_STOP_THREAD";
			this->UI_BTN_STOP_THREAD->Size = System::Drawing::Size(112, 54);
			this->UI_BTN_STOP_THREAD->TabIndex = 1;
			this->UI_BTN_STOP_THREAD->Text = L"STOP";
			this->UI_BTN_STOP_THREAD->UseVisualStyleBackColor = true;
			this->UI_BTN_STOP_THREAD->Click += gcnew System::EventHandler(this, &Form1::UI_BTN_STOP_THREAD_Click);
			// 
			// statusLabel
			// 
			this->statusLabel->AutoSize = true;
			this->statusLabel->Location = System::Drawing::Point(110, 53);
			this->statusLabel->Name = L"statusLabel";
			this->statusLabel->Size = System::Drawing::Size(108, 20);
			this->statusLabel->TabIndex = 2;
			this->statusLabel->Text = L"...STATUS...";
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(572, 292);
			this->Controls->Add(this->groupBox1);
			this->Name = L"Form1";
			this->Text = L"Form1";
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void UI_BTN_START_THREAD_Click(System::Object^  sender, System::EventArgs^  e) 
			 {
				 myController->SetNumber(42);
				 myController->StartThread(gcnew Action<Object^>(myController, &MyController::ThreadFunction));
			 }
	private: System::Void UI_BTN_STOP_THREAD_Click(System::Object^  sender, System::EventArgs^  e) 
			 {
				 myController->StopThread();
			 }

			 void OnThreadCompleted(Object^ sender, EventArgs^ e) 
			 {
				 // Обновляем статус потока в UI
				 if (this->InvokeRequired) 
				 {
					 this->BeginInvoke(gcnew Action<String^>(this, &Form1::UpdateStatus), "Completed");
				 } 
				 else 
				 {
					 UpdateStatus("FAILED!");
				 }
			 }

			 void UpdateStatus(String^ status) 
			 {
				 statusLabel->Text = "Status: " + status;
			 }
	};
}