#pragma once
#include "AboutDlg.h"

namespace WindowsFormsApplication1 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::IO;
	using namespace System::Runtime::InteropServices;
	[DllImport("user32.dll", EntryPoint = "GetKeyState")]
	int GetKeyState(int vVirtKey);
	/// <summary>
	/// Form1 ժҪ
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public: 
		String ^strFileName;
		bool DoModified()
		{
			if(this->richTextBox1->Modified == false)
				return true;
			System::Windows::Forms::DialogResult dlg;
			dlg = MessageBox::Show(L"��ǰ�ļ��е��������޸ģ���Ҫ������",
				"���±�", MessageBoxButtons::YesNoCancel);
			if(dlg == System::Windows::Forms::DialogResult::Yes)
			{
				OnSaveFile(nullptr, nullptr);
				return true;
			}
			if(dlg == System::Windows::Forms::DialogResult::No)
				return true;
			if(dlg == System::Windows::Forms::DialogResult::Cancel)
				return false;
			return false;
		}
	public:
		Form1(void)
		{
			InitializeComponent();
			//
			//TODO: �ڴ˴���ӹ��캯������
			//
		}

	protected:
		/// <summary>
		/// ������������ʹ�õ���Դ��
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::MenuStrip^  menuStrip1;
	private: System::Windows::Forms::ToolStripMenuItem^  �ļ�ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  �½�ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  ��ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator1;
	private: System::Windows::Forms::ToolStripMenuItem^  ����ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  ���ΪToolStripMenuItem;
	private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator2;
	private: System::Windows::Forms::ToolStripMenuItem^  �˳�ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  �༭ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  ����ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  �ظ�ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator3;
	private: System::Windows::Forms::ToolStripMenuItem^  ����ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  ����ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  ճ��ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator4;
	private: System::Windows::Forms::ToolStripMenuItem^  ȫѡToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  ��ʽToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  ����ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  ��ɫToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  �鿴ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  ������ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  ״̬��ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  ����ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  ���ڼ��±�ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripTextBox^  toolStripTextBox1;
	private: System::Windows::Forms::ToolStrip^  toolStrip1;
	private: System::Windows::Forms::ToolStripButton^  �½�NToolStripButton;
	private: System::Windows::Forms::ToolStripButton^  ��OToolStripButton;
	private: System::Windows::Forms::ToolStripButton^  ����SToolStripButton;
	private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator;
	private: System::Windows::Forms::ToolStripButton^  ����UToolStripButton;
	private: System::Windows::Forms::ToolStripButton^  ����CToolStripButton;
	private: System::Windows::Forms::ToolStripButton^  ճ��PToolStripButton;
	private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator5;
	private: System::Windows::Forms::ToolStripButton^  ����LToolStripButton;
	private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator6;
	private: System::Windows::Forms::ToolStripButton^  toolStripButton1;
	private: System::Windows::Forms::ToolStripButton^  toolStripButton2;
	private: System::Windows::Forms::StatusStrip^  statusStrip1;
	private: System::Windows::Forms::ToolStripStatusLabel^  toolStripStatusLabel1;
	private: System::Windows::Forms::RichTextBox^  richTextBox1;
	private: System::Windows::Forms::ToolStripSplitButton^  toolStripSplitButton1;
	private: System::Windows::Forms::ToolStripMenuItem^  toolStripMenuItem3;
	private: System::Windows::Forms::ToolStripMenuItem^  toolStripMenuItem2;
	private: System::Windows::Forms::ToolStripProgressBar^  toolStripProgressBar1;
	private: System::Windows::Forms::OpenFileDialog^  openFileDialog1;
	private: System::Windows::Forms::SaveFileDialog^  saveFileDialog1;
	private: System::Windows::Forms::FontDialog^  fontDialog1;
	private: System::Windows::Forms::ColorDialog^  colorDialog1;
	private: System::Windows::Forms::ContextMenuStrip^  contextMenuStrip1;
	private: System::Windows::Forms::ToolStripMenuItem^  ����ToolStripMenuItem1;
	private: System::Windows::Forms::ToolStripMenuItem^  ����ToolStripMenuItem1;
	private: System::Windows::Forms::ToolStripMenuItem^  ճ��ToolStripMenuItem1;
	private: System::Windows::Forms::ToolStripMenuItem^  ����ToolStripMenuItem1;
	private: System::Windows::Forms::ToolStripMenuItem^  ��ɫToolStripMenuItem1;
	private: System::Windows::Forms::ToolStripStatusLabel^  toolStripStatusLabel4;
	private: System::Windows::Forms::ToolStripStatusLabel^  toolStripStatusLabel3;
	private: System::Windows::Forms::ToolStripStatusLabel^  toolStripStatusLabel2;
	protected: 

	






	private: System::ComponentModel::IContainer^  components;

	private:
		/// <summary>
		/// ����������������
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// �����֧������ķ��� - ��Ҫ
		/// ʹ�ô���༭���޸Ĵ˷��������ݡ�
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(Form1::typeid));
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->�ļ�ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->�½�ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->��ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripSeparator1 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->����ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->���ΪToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripSeparator2 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->�˳�ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->�༭ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->����ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->�ظ�ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripSeparator3 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->����ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->����ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ճ��ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripSeparator4 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->ȫѡToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->��ʽToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripTextBox1 = (gcnew System::Windows::Forms::ToolStripTextBox());
			this->����ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->��ɫToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->�鿴ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->������ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->״̬��ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->����ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->���ڼ��±�ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStrip1 = (gcnew System::Windows::Forms::ToolStrip());
			this->�½�NToolStripButton = (gcnew System::Windows::Forms::ToolStripButton());
			this->��OToolStripButton = (gcnew System::Windows::Forms::ToolStripButton());
			this->����SToolStripButton = (gcnew System::Windows::Forms::ToolStripButton());
			this->toolStripSeparator = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->����UToolStripButton = (gcnew System::Windows::Forms::ToolStripButton());
			this->����CToolStripButton = (gcnew System::Windows::Forms::ToolStripButton());
			this->ճ��PToolStripButton = (gcnew System::Windows::Forms::ToolStripButton());
			this->toolStripSeparator5 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->����LToolStripButton = (gcnew System::Windows::Forms::ToolStripButton());
			this->toolStripSeparator6 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->toolStripButton1 = (gcnew System::Windows::Forms::ToolStripButton());
			this->toolStripButton2 = (gcnew System::Windows::Forms::ToolStripButton());
			this->statusStrip1 = (gcnew System::Windows::Forms::StatusStrip());
			this->toolStripStatusLabel1 = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->toolStripStatusLabel4 = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->toolStripStatusLabel3 = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->toolStripStatusLabel2 = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->toolStripSplitButton1 = (gcnew System::Windows::Forms::ToolStripSplitButton());
			this->toolStripMenuItem3 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripMenuItem2 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripProgressBar1 = (gcnew System::Windows::Forms::ToolStripProgressBar());
			this->richTextBox1 = (gcnew System::Windows::Forms::RichTextBox());
			this->contextMenuStrip1 = (gcnew System::Windows::Forms::ContextMenuStrip(this->components));
			this->����ToolStripMenuItem1 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->����ToolStripMenuItem1 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ճ��ToolStripMenuItem1 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->����ToolStripMenuItem1 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->��ɫToolStripMenuItem1 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->saveFileDialog1 = (gcnew System::Windows::Forms::SaveFileDialog());
			this->fontDialog1 = (gcnew System::Windows::Forms::FontDialog());
			this->colorDialog1 = (gcnew System::Windows::Forms::ColorDialog());
			this->menuStrip1->SuspendLayout();
			this->toolStrip1->SuspendLayout();
			this->statusStrip1->SuspendLayout();
			this->contextMenuStrip1->SuspendLayout();
			this->SuspendLayout();
			// 
			// menuStrip1
			// 
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(5) {this->�ļ�ToolStripMenuItem, 
				this->�༭ToolStripMenuItem, this->��ʽToolStripMenuItem, this->�鿴ToolStripMenuItem, this->����ToolStripMenuItem});
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(366, 25);
			this->menuStrip1->TabIndex = 0;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// �ļ�ToolStripMenuItem
			// 
			this->�ļ�ToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(7) {this->�½�ToolStripMenuItem, 
				this->��ToolStripMenuItem, this->toolStripSeparator1, this->����ToolStripMenuItem, this->���ΪToolStripMenuItem, this->toolStripSeparator2, 
				this->�˳�ToolStripMenuItem});
			this->�ļ�ToolStripMenuItem->Name = L"�ļ�ToolStripMenuItem";
			this->�ļ�ToolStripMenuItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Alt | System::Windows::Forms::Keys::F));
			this->�ļ�ToolStripMenuItem->Size = System::Drawing::Size(44, 21);
			this->�ļ�ToolStripMenuItem->Text = L"�ļ�";
			// 
			// �½�ToolStripMenuItem
			// 
			this->�½�ToolStripMenuItem->Name = L"�½�ToolStripMenuItem";
			this->�½�ToolStripMenuItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::N));
			this->�½�ToolStripMenuItem->Size = System::Drawing::Size(147, 22);
			this->�½�ToolStripMenuItem->Text = L"�½�";
			this->�½�ToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::OnNewFile);
			// 
			// ��ToolStripMenuItem
			// 
			this->��ToolStripMenuItem->Name = L"��ToolStripMenuItem";
			this->��ToolStripMenuItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::O));
			this->��ToolStripMenuItem->Size = System::Drawing::Size(147, 22);
			this->��ToolStripMenuItem->Text = L"��";
			this->��ToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::OnOpenFile);
			// 
			// toolStripSeparator1
			// 
			this->toolStripSeparator1->Name = L"toolStripSeparator1";
			this->toolStripSeparator1->Size = System::Drawing::Size(144, 6);
			// 
			// ����ToolStripMenuItem
			// 
			this->����ToolStripMenuItem->Name = L"����ToolStripMenuItem";
			this->����ToolStripMenuItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::S));
			this->����ToolStripMenuItem->Size = System::Drawing::Size(147, 22);
			this->����ToolStripMenuItem->Text = L"����";
			this->����ToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::OnSaveFile);
			// 
			// ���ΪToolStripMenuItem
			// 
			this->���ΪToolStripMenuItem->Name = L"���ΪToolStripMenuItem";
			this->���ΪToolStripMenuItem->Size = System::Drawing::Size(147, 22);
			this->���ΪToolStripMenuItem->Text = L"���Ϊ";
			this->���ΪToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::OnSaveAsFile);
			// 
			// toolStripSeparator2
			// 
			this->toolStripSeparator2->Name = L"toolStripSeparator2";
			this->toolStripSeparator2->Size = System::Drawing::Size(144, 6);
			// 
			// �˳�ToolStripMenuItem
			// 
			this->�˳�ToolStripMenuItem->Name = L"�˳�ToolStripMenuItem";
			this->�˳�ToolStripMenuItem->Size = System::Drawing::Size(147, 22);
			this->�˳�ToolStripMenuItem->Text = L"�˳�";
			this->�˳�ToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::OnExit);
			// 
			// �༭ToolStripMenuItem
			// 
			this->�༭ToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(8) {this->����ToolStripMenuItem, 
				this->�ظ�ToolStripMenuItem, this->toolStripSeparator3, this->����ToolStripMenuItem, this->����ToolStripMenuItem, this->ճ��ToolStripMenuItem, 
				this->toolStripSeparator4, this->ȫѡToolStripMenuItem});
			this->�༭ToolStripMenuItem->Name = L"�༭ToolStripMenuItem";
			this->�༭ToolStripMenuItem->Size = System::Drawing::Size(44, 21);
			this->�༭ToolStripMenuItem->Text = L"�༭";
			// 
			// ����ToolStripMenuItem
			// 
			this->����ToolStripMenuItem->Name = L"����ToolStripMenuItem";
			this->����ToolStripMenuItem->Size = System::Drawing::Size(100, 22);
			this->����ToolStripMenuItem->Text = L"����";
			this->����ToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::OnUndo);
			// 
			// �ظ�ToolStripMenuItem
			// 
			this->�ظ�ToolStripMenuItem->Name = L"�ظ�ToolStripMenuItem";
			this->�ظ�ToolStripMenuItem->Size = System::Drawing::Size(100, 22);
			this->�ظ�ToolStripMenuItem->Text = L"�ظ�";
			this->�ظ�ToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::OnRedo);
			// 
			// toolStripSeparator3
			// 
			this->toolStripSeparator3->Name = L"toolStripSeparator3";
			this->toolStripSeparator3->Size = System::Drawing::Size(97, 6);
			// 
			// ����ToolStripMenuItem
			// 
			this->����ToolStripMenuItem->Name = L"����ToolStripMenuItem";
			this->����ToolStripMenuItem->Size = System::Drawing::Size(100, 22);
			this->����ToolStripMenuItem->Text = L"����";
			this->����ToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::OnCut);
			// 
			// ����ToolStripMenuItem
			// 
			this->����ToolStripMenuItem->Name = L"����ToolStripMenuItem";
			this->����ToolStripMenuItem->Size = System::Drawing::Size(100, 22);
			this->����ToolStripMenuItem->Text = L"����";
			this->����ToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::OnCopy);
			// 
			// ճ��ToolStripMenuItem
			// 
			this->ճ��ToolStripMenuItem->Name = L"ճ��ToolStripMenuItem";
			this->ճ��ToolStripMenuItem->Size = System::Drawing::Size(100, 22);
			this->ճ��ToolStripMenuItem->Text = L"ճ��";
			this->ճ��ToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::OnPaste);
			// 
			// toolStripSeparator4
			// 
			this->toolStripSeparator4->Name = L"toolStripSeparator4";
			this->toolStripSeparator4->Size = System::Drawing::Size(97, 6);
			// 
			// ȫѡToolStripMenuItem
			// 
			this->ȫѡToolStripMenuItem->Name = L"ȫѡToolStripMenuItem";
			this->ȫѡToolStripMenuItem->Size = System::Drawing::Size(100, 22);
			this->ȫѡToolStripMenuItem->Text = L"ȫѡ";
			this->ȫѡToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::OnSelectAll);
			// 
			// ��ʽToolStripMenuItem
			// 
			this->��ʽToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {this->toolStripTextBox1, 
				this->����ToolStripMenuItem, this->��ɫToolStripMenuItem});
			this->��ʽToolStripMenuItem->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"��ʽToolStripMenuItem.Image")));
			this->��ʽToolStripMenuItem->Name = L"��ʽToolStripMenuItem";
			this->��ʽToolStripMenuItem->Size = System::Drawing::Size(60, 21);
			this->��ʽToolStripMenuItem->Text = L"��ʽ";
			// 
			// toolStripTextBox1
			// 
			this->toolStripTextBox1->Name = L"toolStripTextBox1";
			this->toolStripTextBox1->Size = System::Drawing::Size(100, 23);
			this->toolStripTextBox1->Click += gcnew System::EventHandler(this, &Form1::toolStripTextBox1_Click);
			// 
			// ����ToolStripMenuItem
			// 
			this->����ToolStripMenuItem->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"����ToolStripMenuItem.Image")));
			this->����ToolStripMenuItem->Name = L"����ToolStripMenuItem";
			this->����ToolStripMenuItem->Size = System::Drawing::Size(160, 22);
			this->����ToolStripMenuItem->Text = L"����";
			this->����ToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::OnFont);
			// 
			// ��ɫToolStripMenuItem
			// 
			this->��ɫToolStripMenuItem->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"��ɫToolStripMenuItem.Image")));
			this->��ɫToolStripMenuItem->Name = L"��ɫToolStripMenuItem";
			this->��ɫToolStripMenuItem->Size = System::Drawing::Size(160, 22);
			this->��ɫToolStripMenuItem->Text = L"��ɫ";
			this->��ɫToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::OnColor);
			// 
			// �鿴ToolStripMenuItem
			// 
			this->�鿴ToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {this->������ToolStripMenuItem, 
				this->״̬��ToolStripMenuItem});
			this->�鿴ToolStripMenuItem->Name = L"�鿴ToolStripMenuItem";
			this->�鿴ToolStripMenuItem->Size = System::Drawing::Size(44, 21);
			this->�鿴ToolStripMenuItem->Text = L"�鿴";
			// 
			// ������ToolStripMenuItem
			// 
			this->������ToolStripMenuItem->Checked = true;
			this->������ToolStripMenuItem->CheckState = System::Windows::Forms::CheckState::Checked;
			this->������ToolStripMenuItem->Name = L"������ToolStripMenuItem";
			this->������ToolStripMenuItem->Size = System::Drawing::Size(112, 22);
			this->������ToolStripMenuItem->Text = L"������";
			this->������ToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::OnTool);
			// 
			// ״̬��ToolStripMenuItem
			// 
			this->״̬��ToolStripMenuItem->Checked = true;
			this->״̬��ToolStripMenuItem->CheckState = System::Windows::Forms::CheckState::Checked;
			this->״̬��ToolStripMenuItem->Name = L"״̬��ToolStripMenuItem";
			this->״̬��ToolStripMenuItem->Size = System::Drawing::Size(112, 22);
			this->״̬��ToolStripMenuItem->Text = L"״̬��";
			this->״̬��ToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::OnStatus);
			// 
			// ����ToolStripMenuItem
			// 
			this->����ToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) {this->���ڼ��±�ToolStripMenuItem});
			this->����ToolStripMenuItem->Name = L"����ToolStripMenuItem";
			this->����ToolStripMenuItem->Size = System::Drawing::Size(44, 21);
			this->����ToolStripMenuItem->Text = L"����";
			// 
			// ���ڼ��±�ToolStripMenuItem
			// 
			this->���ڼ��±�ToolStripMenuItem->Name = L"���ڼ��±�ToolStripMenuItem";
			this->���ڼ��±�ToolStripMenuItem->Size = System::Drawing::Size(136, 22);
			this->���ڼ��±�ToolStripMenuItem->Text = L"���ڼ��±�";
			this->���ڼ��±�ToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::OnAbout);
			// 
			// toolStrip1
			// 
			this->toolStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(12) {this->�½�NToolStripButton, 
				this->��OToolStripButton, this->����SToolStripButton, this->toolStripSeparator, this->����UToolStripButton, this->����CToolStripButton, 
				this->ճ��PToolStripButton, this->toolStripSeparator5, this->����LToolStripButton, this->toolStripSeparator6, this->toolStripButton1, 
				this->toolStripButton2});
			this->toolStrip1->Location = System::Drawing::Point(0, 25);
			this->toolStrip1->Name = L"toolStrip1";
			this->toolStrip1->Size = System::Drawing::Size(366, 25);
			this->toolStrip1->TabIndex = 1;
			this->toolStrip1->Text = L"toolStrip1";
			//this->toolStrip1->ItemClicked += gcnew System::Windows::Forms::ToolStripItemClickedEventHandler(this, &Form1::toolStrip1_ItemClicked);
			// 
			// �½�NToolStripButton
			// 
			this->�½�NToolStripButton->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->�½�NToolStripButton->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"�½�NToolStripButton.Image")));
			this->�½�NToolStripButton->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->�½�NToolStripButton->Name = L"�½�NToolStripButton";
			this->�½�NToolStripButton->Size = System::Drawing::Size(23, 22);
			this->�½�NToolStripButton->Text = L"�½�(&N)";
			this->�½�NToolStripButton->Click += gcnew System::EventHandler(this, &Form1::OnNewFile);
			// 
			// ��OToolStripButton
			// 
			this->��OToolStripButton->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->��OToolStripButton->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"��OToolStripButton.Image")));
			this->��OToolStripButton->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->��OToolStripButton->Name = L"��OToolStripButton";
			this->��OToolStripButton->Size = System::Drawing::Size(23, 22);
			this->��OToolStripButton->Text = L"��(&O)";
			this->��OToolStripButton->Click += gcnew System::EventHandler(this, &Form1::OnOpenFile);
			// 
			// ����SToolStripButton
			// 
			this->����SToolStripButton->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->����SToolStripButton->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"����SToolStripButton.Image")));
			this->����SToolStripButton->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->����SToolStripButton->Name = L"����SToolStripButton";
			this->����SToolStripButton->Size = System::Drawing::Size(23, 22);
			this->����SToolStripButton->Text = L"����(&S)";
			this->����SToolStripButton->Click += gcnew System::EventHandler(this, &Form1::OnSaveFile);
			// 
			// toolStripSeparator
			// 
			this->toolStripSeparator->Name = L"toolStripSeparator";
			this->toolStripSeparator->Size = System::Drawing::Size(6, 25);
			// 
			// ����UToolStripButton
			// 
			this->����UToolStripButton->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->����UToolStripButton->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"����UToolStripButton.Image")));
			this->����UToolStripButton->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->����UToolStripButton->Name = L"����UToolStripButton";
			this->����UToolStripButton->Size = System::Drawing::Size(23, 22);
			this->����UToolStripButton->Text = L"����(&U)";
			this->����UToolStripButton->Click += gcnew System::EventHandler(this, &Form1::OnCut);
			// 
			// ����CToolStripButton
			// 
			this->����CToolStripButton->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->����CToolStripButton->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"����CToolStripButton.Image")));
			this->����CToolStripButton->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->����CToolStripButton->Name = L"����CToolStripButton";
			this->����CToolStripButton->Size = System::Drawing::Size(23, 22);
			this->����CToolStripButton->Text = L"����(&C)";
			this->����CToolStripButton->Click += gcnew System::EventHandler(this, &Form1::OnCopy);
			// 
			// ճ��PToolStripButton
			// 
			this->ճ��PToolStripButton->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->ճ��PToolStripButton->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"ճ��PToolStripButton.Image")));
			this->ճ��PToolStripButton->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->ճ��PToolStripButton->Name = L"ճ��PToolStripButton";
			this->ճ��PToolStripButton->Size = System::Drawing::Size(23, 22);
			this->ճ��PToolStripButton->Text = L"ճ��(&P)";
			this->ճ��PToolStripButton->Click += gcnew System::EventHandler(this, &Form1::OnPaste);
			// 
			// toolStripSeparator5
			// 
			this->toolStripSeparator5->Name = L"toolStripSeparator5";
			this->toolStripSeparator5->Size = System::Drawing::Size(6, 25);
			// 
			// ����LToolStripButton
			// 
			this->����LToolStripButton->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->����LToolStripButton->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"����LToolStripButton.Image")));
			this->����LToolStripButton->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->����LToolStripButton->Name = L"����LToolStripButton";
			this->����LToolStripButton->Size = System::Drawing::Size(23, 22);
			this->����LToolStripButton->Text = L"����(&L)";
			this->����LToolStripButton->Click += gcnew System::EventHandler(this, &Form1::OnAbout);
			// 
			// toolStripSeparator6
			// 
			this->toolStripSeparator6->Name = L"toolStripSeparator6";
			this->toolStripSeparator6->Size = System::Drawing::Size(6, 25);
			// 
			// toolStripButton1
			// 
			this->toolStripButton1->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->toolStripButton1->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"toolStripButton1.Image")));
			this->toolStripButton1->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->toolStripButton1->Name = L"toolStripButton1";
			this->toolStripButton1->Size = System::Drawing::Size(23, 22);
			this->toolStripButton1->Text = L"toolStripButton1";
			this->toolStripButton1->Click += gcnew System::EventHandler(this, &Form1::OnFont);
			// 
			// toolStripButton2
			// 
			this->toolStripButton2->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->toolStripButton2->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"toolStripButton2.Image")));
			this->toolStripButton2->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->toolStripButton2->Name = L"toolStripButton2";
			this->toolStripButton2->Size = System::Drawing::Size(23, 22);
			this->toolStripButton2->Text = L"toolStripButton2";
			this->toolStripButton2->Click += gcnew System::EventHandler(this, &Form1::OnColor);
			// 
			// statusStrip1
			// 
			this->statusStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(6) {this->toolStripStatusLabel1, 
				this->toolStripStatusLabel4, this->toolStripStatusLabel3, this->toolStripStatusLabel2, this->toolStripSplitButton1, this->toolStripProgressBar1});
			this->statusStrip1->Location = System::Drawing::Point(0, 374);
			this->statusStrip1->Name = L"statusStrip1";
			this->statusStrip1->Size = System::Drawing::Size(366, 23);
			this->statusStrip1->TabIndex = 2;
			this->statusStrip1->Text = L"��д";
			// 
			// toolStripStatusLabel1
			// 
			this->toolStripStatusLabel1->AutoSize = false;
			this->toolStripStatusLabel1->Name = L"toolStripStatusLabel1";
			this->toolStripStatusLabel1->Size = System::Drawing::Size(255, 18);
			this->toolStripStatusLabel1->Spring = true;
			this->toolStripStatusLabel1->Text = L"����";
			this->toolStripStatusLabel1->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->toolStripStatusLabel1->Click += gcnew System::EventHandler(this, &Form1::toolStripStatusLabel1_Click);
			this->toolStripStatusLabel1->MouseEnter += gcnew System::EventHandler(this, &Form1::OnSelMenu);
			// 
			// toolStripStatusLabel4
			// 
			this->toolStripStatusLabel4->BorderStyle = System::Windows::Forms::Border3DStyle::Sunken;
			this->toolStripStatusLabel4->Name = L"toolStripStatusLabel4";
			this->toolStripStatusLabel4->Size = System::Drawing::Size(32, 18);
			this->toolStripStatusLabel4->Text = L"��д";
			// 
			// toolStripStatusLabel3
			// 
			this->toolStripStatusLabel3->BorderStyle = System::Windows::Forms::Border3DStyle::Sunken;
			this->toolStripStatusLabel3->Name = L"toolStripStatusLabel3";
			this->toolStripStatusLabel3->Size = System::Drawing::Size(32, 18);
			this->toolStripStatusLabel3->Text = L"����";
			// 
			// toolStripStatusLabel2
			// 
			this->toolStripStatusLabel2->BorderStyle = System::Windows::Forms::Border3DStyle::Sunken;
			this->toolStripStatusLabel2->Name = L"toolStripStatusLabel2";
			this->toolStripStatusLabel2->Size = System::Drawing::Size(32, 18);
			this->toolStripStatusLabel2->Text = L"����";
			// 
			// toolStripSplitButton1
			// 
			this->toolStripSplitButton1->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {this->toolStripMenuItem3, 
				this->toolStripMenuItem2});
			this->toolStripSplitButton1->Name = L"toolStripSplitButton1";
			this->toolStripSplitButton1->Size = System::Drawing::Size(48, 21);
			this->toolStripSplitButton1->Text = L"ʵ��";
			// 
			// toolStripMenuItem3
			// 
			this->toolStripMenuItem3->Name = L"toolStripMenuItem3";
			this->toolStripMenuItem3->Size = System::Drawing::Size(97, 22);
			this->toolStripMenuItem3->Text = L"456";
			// 
			// toolStripMenuItem2
			// 
			this->toolStripMenuItem2->Name = L"toolStripMenuItem2";
			this->toolStripMenuItem2->Size = System::Drawing::Size(97, 22);
			this->toolStripMenuItem2->Text = L"123";
			// 
			// toolStripProgressBar1
			// 
			this->toolStripProgressBar1->Name = L"toolStripProgressBar1";
			this->toolStripProgressBar1->Size = System::Drawing::Size(100, 17);
			// 
			// richTextBox1
			// 
			this->richTextBox1->ContextMenuStrip = this->contextMenuStrip1;
			this->richTextBox1->HideSelection = false;
			this->richTextBox1->Location = System::Drawing::Point(6, 53);
			this->richTextBox1->Name = L"richTextBox1";
			this->richTextBox1->Size = System::Drawing::Size(354, 318);
			this->richTextBox1->TabIndex = 3;
			this->richTextBox1->Text = L"";
			this->richTextBox1->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &Form1::OnKey);
			// 
			// contextMenuStrip1
			// 
			this->contextMenuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(5) {this->����ToolStripMenuItem1, 
				this->����ToolStripMenuItem1, this->ճ��ToolStripMenuItem1, this->����ToolStripMenuItem1, this->��ɫToolStripMenuItem1});
			this->contextMenuStrip1->Name = L"contextMenuStrip1";
			this->contextMenuStrip1->Size = System::Drawing::Size(146, 114);
			// 
			// ����ToolStripMenuItem1
			// 
			this->����ToolStripMenuItem1->Name = L"����ToolStripMenuItem1";
			this->����ToolStripMenuItem1->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::X));
			this->����ToolStripMenuItem1->Size = System::Drawing::Size(145, 22);
			this->����ToolStripMenuItem1->Text = L"����";
			this->����ToolStripMenuItem1->Click += gcnew System::EventHandler(this, &Form1::OnCut);
			// 
			// ����ToolStripMenuItem1
			// 
			this->����ToolStripMenuItem1->Name = L"����ToolStripMenuItem1";
			this->����ToolStripMenuItem1->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::C));
			this->����ToolStripMenuItem1->Size = System::Drawing::Size(145, 22);
			this->����ToolStripMenuItem1->Text = L"����";
			this->����ToolStripMenuItem1->Click += gcnew System::EventHandler(this, &Form1::OnCopy);
			// 
			// ճ��ToolStripMenuItem1
			// 
			this->ճ��ToolStripMenuItem1->Name = L"ճ��ToolStripMenuItem1";
			this->ճ��ToolStripMenuItem1->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::V));
			this->ճ��ToolStripMenuItem1->Size = System::Drawing::Size(145, 22);
			this->ճ��ToolStripMenuItem1->Text = L"ճ��";
			this->ճ��ToolStripMenuItem1->Click += gcnew System::EventHandler(this, &Form1::OnPaste);
			// 
			// ����ToolStripMenuItem1
			// 
			this->����ToolStripMenuItem1->Name = L"����ToolStripMenuItem1";
			this->����ToolStripMenuItem1->Size = System::Drawing::Size(145, 22);
			this->����ToolStripMenuItem1->Text = L"����";
			this->����ToolStripMenuItem1->Click += gcnew System::EventHandler(this, &Form1::OnFont);
			// 
			// ��ɫToolStripMenuItem1
			// 
			this->��ɫToolStripMenuItem1->Name = L"��ɫToolStripMenuItem1";
			this->��ɫToolStripMenuItem1->Size = System::Drawing::Size(145, 22);
			this->��ɫToolStripMenuItem1->Text = L"��ɫ";
			this->��ɫToolStripMenuItem1->Click += gcnew System::EventHandler(this, &Form1::OnColor);
			// 
			// openFileDialog1
			// 
			this->openFileDialog1->FileName = L"openFileDialog1";
			// 
			// fontDialog1
			// 
			this->fontDialog1->Color = System::Drawing::SystemColors::ControlText;
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(366, 397);
			this->Controls->Add(this->richTextBox1);
			this->Controls->Add(this->statusStrip1);
			this->Controls->Add(this->toolStrip1);
			this->Controls->Add(this->menuStrip1);
			this->KeyPreview = true;
			this->MainMenuStrip = this->menuStrip1;
			this->Name = L"Form1";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"���±�";
			this->FormClosed += gcnew System::Windows::Forms::FormClosedEventHandler(this, &Form1::OnClose);
			this->Load += gcnew System::EventHandler(this, &Form1::OnLoad);
			this->Resize += gcnew System::EventHandler(this, &Form1::Form1_Resize);
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			this->toolStrip1->ResumeLayout(false);
			this->toolStrip1->PerformLayout();
			this->statusStrip1->ResumeLayout(false);
			this->statusStrip1->PerformLayout();
			this->contextMenuStrip1->ResumeLayout(false);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void toolStripTextBox1_Click(System::Object^  sender, System::EventArgs^  e) {
			 }
private: System::Void toolStripStatusLabel1_Click(System::Object^  sender, System::EventArgs^  e) {
		 }

private: System::Void OnNewFile(System::Object^  sender, System::EventArgs^  e) {
			if(!DoModified())return;
			this->Text = "�ޱ���--���±�";
			this->richTextBox1->Text = "";//�����ı��༭�ؼ�richTextBox1����
			this->richTextBox1->Select(0, 0);//�����ı��༭�ؼ�richTextBox1ѡ���ı�Ϊ��
			this->richTextBox1->Modified = false;//�����ĵ��ı��ʶΪ��
			this->strFileName = "";//�������ڱ༭���ĵ���Ϊ��
		 }


private: System::Void OnOpenFile(System::Object^  sender, System::EventArgs^  e) {
			 if(!DoModified())return;
			 System::Windows::Forms::DialogResult dlg;//dlg���ڻ�ȡͨ�öԻ��������
			 openFileDialog1->InitialDirectory = "c:\\";//����ͨ�öԻ���ĳ�ʼ·����
			 openFileDialog1->Filter = "Rtf files(*.rtf)|*.rtf|�ı��ļ�(*.txt)|*.txt";//�����ļ��򿪶Ի�����ļ���������ֻ�ܴ���չ��Ϊ*.rtf��*.txt���ļ�
			 openFileDialog1->FileName = "";
			 dlg = openFileDialog1->ShowDialog();
			 try{
				if(dlg == System::Windows::Forms::DialogResult::OK)
					if(Path::GetExtension(openFileDialog1->FileName) == ".rtf")
					{
						//ʹ��Path��ľ�̬��������ļ�����չ��
						strFileName = openFileDialog1->FileName;
						this->richTextBox1->LoadFile(strFileName, RichTextBoxStreamType::RichText);//�������ʽ�ı�
						this->Text = Path::GetFileName(strFileName)+"--���±�";
							//ʹ��Path��ľ�̬��������ļ��������޸Ĵ������
					}
					else
						if(Path::GetExtension(openFileDialog1->FileName) == ".txt")
						{
							strFileName = openFileDialog1->FileName;
							this->richTextBox1->LoadFile(strFileName,
								RichTextBoxStreamType::PlainText);//�����޸�ʽ�ı�
							this->Text = Path::GetFileName(strFileName)+"--���±�";
						}
						else 
							MessageBox::Show(L"ѡ��Ĳ���RTF��TXT��ʽ���ļ��� ��Ч", "����",MessageBoxButtons::OK);

			 }
			 catch(System::ArgumentException ^e)
			 {
				MessageBox::Show(L"ѡ��Ĳ���RTF��TXT��ʽ���ļ��� ��Ч", "����",MessageBoxButtons::OK);
			 }
		 }


private: System::Void OnSaveFile(System::Object^  sender, System::EventArgs^  e) {
			 if(strFileName->Length == 0)//���ļ���
			 {
				System::Windows::Forms::DialogResult dlg;
				saveFileDialog1->Filter = "Rtf files(*.rtf)|*.rtf|�ı��ļ�(*.txt)|*.txt";//�����ļ��򿪶Ի�����ļ���������ֻ�ܴ���չ��Ϊ*.rtf��*.txt���ļ�
				dlg = saveFileDialog1->ShowDialog();
				if(dlg == System::Windows::Forms::DialogResult::OK)
					strFileName = saveFileDialog1->FileName;
				else
					return;
			 }
			 if(Path::GetExtension(strFileName) == ".rtf")
			 {
				this->richTextBox1->SaveFile(strFileName,
					RichTextBoxStreamType::RichText);//д�����ʽ�ı�
				this->Text = Path::GetFileName(strFileName)+"--���±�";
				richTextBox1->Modified = false;
			 }
			 else
				 if(Path::GetExtension(strFileName) == ".txt")
				 {
					this->richTextBox1->SaveFile(strFileName,
						RichTextBoxStreamType::PlainText);//д���޸�ʽ�ı�
					this->Text = Path::GetFileName(strFileName)+"--���±�";
					richTextBox1->Modified = false;
				 }
				 else
				 {
					MessageBox::Show(L"ѡ��Ĳ���RTF��TXT��ʽ���ļ��� ��Ч", "����",MessageBoxButtons::OK);
					strFileName = "";
				 }
		 }

private: System::Void OnSaveAsFile(System::Object^  sender, System::EventArgs^  e) {
			  System::Windows::Forms::DialogResult dlg;//dlg���ڻ�ȡͨ�öԻ��������
			  saveFileDialog1->Filter = "Rtf files(*.rtf)|*.rtf|�ı��ļ�(*.txt)|*.txt";//�����ļ��򿪶Ի�����ļ���������ֻ�ܴ���չ��Ϊ*.rtf��*.txt���ļ�
			  dlg = saveFileDialog1->ShowDialog();
			  if(dlg != System::Windows::Forms::DialogResult::OK)return;
			  if(Path::GetExtension(saveFileDialog1->FileName) == ".rtf")
			 {
				 strFileName = saveFileDialog1->FileName;
				this->richTextBox1->SaveFile(strFileName,
					RichTextBoxStreamType::RichText);//д�����ʽ�ı�
				this->Text = Path::GetFileName(strFileName)+"--���±�";
				richTextBox1->Modified = false;
			 }
			 else
				 if(Path::GetExtension(strFileName) == ".txt")
				 {
					this->richTextBox1->SaveFile(strFileName,
						RichTextBoxStreamType::PlainText);//д���޸�ʽ�ı�
					this->Text = Path::GetFileName(strFileName)+"--���±�";
					richTextBox1->Modified = false;
				 }
				 else
				 {
					MessageBox::Show(L"ѡ��Ĳ���RTF��TXT��ʽ���ļ��� ��Ч", "����",MessageBoxButtons::OK);
					strFileName = "";
				 }

		 }


private: System::Void OnExit(System::Object^  sender, System::EventArgs^  e) {
			 this->Close();//�رմ���
		 }

private: System::Void OnClose(System::Object^  sender, System::Windows::Forms::FormClosedEventArgs^  e) {
			 //e->Cancel = !DoModified();

		 }


private: System::Void OnUndo(System::Object^  sender, System::EventArgs^  e) {
			 this->richTextBox1->Undo();//�������ı���Ĳ���
		 }
private: System::Void OnRedo(System::Object^  sender, System::EventArgs^  e) {
			 this->richTextBox1->Redo();//�ָ����ı���Ĳ���
		 }
private: System::Void OnCut(System::Object^  sender, System::EventArgs^  e) {
			 if(this->richTextBox1->SelectedText != "")
			 {
				Clipboard::SetDataObject(richTextBox1->SelectedText);
				richTextBox1->SelectedText = "";
			 }
		 }

private: System::Void OnCopy(System::Object^  sender, System::EventArgs^  e) {
			 if(this->richTextBox1->SelectedText != "")
			 {
				Clipboard::SetDataObject(richTextBox1->SelectedText);
			 }
		 }
private: System::Void OnPaste(System::Object^  sender, System::EventArgs^  e) {
			 IDataObject^ iData = Clipboard::GetDataObject();
			 if(iData->GetDataPresent(DataFormats::Text))
				 richTextBox1->SelectedText = (String^)(iData->GetData(DataFormats::Text));
				//�ü������ϵ������滻�ı���ѡ��������
		 }

private: System::Void OnSelectAll(System::Object^  sender, System::EventArgs^  e) {
			 this->richTextBox1->SelectAll();
		 }
private: System::Void OnFont(System::Object^  sender, System::EventArgs^  e) {
			 System::Windows::Forms::DialogResult dlg;
			 dlg = fontDialog1->ShowDialog();
			 if(dlg == System::Windows::Forms::DialogResult::OK)
				 this->richTextBox1->SelectionFont = fontDialog1->Font;
		 }
private: System::Void OnColor(System::Object^  sender, System::EventArgs^  e) {
			 System::Windows::Forms::DialogResult dlg;
			 dlg = colorDialog1->ShowDialog();
			 if(dlg == System::Windows::Forms::DialogResult::OK)
				 this->richTextBox1->SelectionColor = colorDialog1->Color;
		 }
private: System::Void OnTool(System::Object^  sender, System::EventArgs^  e) {
			 this->toolStrip1->Visible = ! this->toolStrip1->Visible;//ʹ��������ʾ������
			 this->������ToolStripMenuItem->Checked =! this->������ToolStripMenuItem->Checked;
		 }

private: System::Void OnStatus(System::Object^  sender, System::EventArgs^  e) {
			 this->statusStrip1->Visible =! this->statusStrip1->Visible;
			 this->״̬��ToolStripMenuItem->Checked =! this ->״̬��ToolStripMenuItem->Checked;
		 }
private: System::Void OnAbout(System::Object^  sender, System::EventArgs^  e) {
			 AboutDlg^ dlg = gcnew AboutDlg;//�������ڶԻ���ʵ��
			 dlg->ShowDialog();				//��ʾ���ڶԻ���
		 }
private: System::Void OnSelMenu(System::Object^  sender, System::EventArgs^  e) {
			 if(sender == this->�ļ�ToolStripMenuItem)
				 this->toolStripStatusLabel1->Text = "�ļ�";
			 if((sender == this->�½�ToolStripMenuItem) ||(sender == this->�½�NToolStripButton))
				 this->toolStripStatusLabel1->Text = "�½��ļ�";
			 if((sender == this->��ToolStripMenuItem) || (sender == this->��OToolStripButton ))
				 this->toolStripStatusLabel1->Text = "���ļ�";
			 if((sender == this->����SToolStripButton) || (sender == this->����ToolStripMenuItem ))
				 this->toolStripStatusLabel1->Text = "�����ļ�";
			 if((sender == this->���ΪToolStripMenuItem) )
				 this->toolStripStatusLabel1->Text = "���Ϊ�ļ�";
			 if(sender == this->�˳�ToolStripMenuItem )
				 this->toolStripStatusLabel1->Text = "�˳�";
		 }
		 
	void UpdateKeyPanel()
	{
		if(GetKeyState(20))//��ȡ����д������״̬
			this->toolStripStatusLabel2->Text = "��д";
		else
			this->toolStripStatusLabel2->Text = "Сд";
		if(GetKeyState(144))
			this->toolStripStatusLabel2->Text = "����";
		else
			this->toolStripStatusLabel2->Text = "";
		if(GetKeyState(145))
			this->toolStripStatusLabel2->Text = "����";
		else
			this->toolStripStatusLabel2->Text = "";

	}
private: System::Void OnKey(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
			 UpdateKeyPanel();
		 }
private: System::Void OnLoad(System::Object^  sender, System::EventArgs^  e) {
			 this->richTextBox1->Size = System::Drawing::Size(this->ClientSize.Width,
				 this->ClientSize.Height - this->statusStrip1->Height -52);
			 //�����ı��༭�ؼ�richTextBox1�Ĵ�С
			 UpdateKeyPanel();
			 OnNewFile(sender, e);
		 }
private: System::Void Form1_Resize(System::Object^  sender, System::EventArgs^  e) {
			 this->richTextBox1->Size = System::Drawing::Size(this->ClientSize.Width,
				 this->ClientSize.Height - this->statusStrip1->Height -52);
		 }
};
}

