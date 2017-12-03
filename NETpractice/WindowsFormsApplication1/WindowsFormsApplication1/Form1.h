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
	/// Form1 摘要
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
			dlg = MessageBox::Show(L"当前文件中的内容有修改，需要保存吗？",
				"记事本", MessageBoxButtons::YesNoCancel);
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
			//TODO: 在此处添加构造函数代码
			//
		}

	protected:
		/// <summary>
		/// 清理所有正在使用的资源。
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::MenuStrip^  menuStrip1;
	private: System::Windows::Forms::ToolStripMenuItem^  文件ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  新建ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  打开ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator1;
	private: System::Windows::Forms::ToolStripMenuItem^  保存ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  另存为ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator2;
	private: System::Windows::Forms::ToolStripMenuItem^  退出ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  编辑ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  撤销ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  重复ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator3;
	private: System::Windows::Forms::ToolStripMenuItem^  剪切ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  复制ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  粘贴ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator4;
	private: System::Windows::Forms::ToolStripMenuItem^  全选ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  格式ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  字体ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  颜色ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  查看ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  工具栏ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  状态栏ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  帮助ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  关于记事本ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripTextBox^  toolStripTextBox1;
	private: System::Windows::Forms::ToolStrip^  toolStrip1;
	private: System::Windows::Forms::ToolStripButton^  新建NToolStripButton;
	private: System::Windows::Forms::ToolStripButton^  打开OToolStripButton;
	private: System::Windows::Forms::ToolStripButton^  保存SToolStripButton;
	private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator;
	private: System::Windows::Forms::ToolStripButton^  剪切UToolStripButton;
	private: System::Windows::Forms::ToolStripButton^  复制CToolStripButton;
	private: System::Windows::Forms::ToolStripButton^  粘贴PToolStripButton;
	private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator5;
	private: System::Windows::Forms::ToolStripButton^  帮助LToolStripButton;
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
	private: System::Windows::Forms::ToolStripMenuItem^  剪切ToolStripMenuItem1;
	private: System::Windows::Forms::ToolStripMenuItem^  复制ToolStripMenuItem1;
	private: System::Windows::Forms::ToolStripMenuItem^  粘贴ToolStripMenuItem1;
	private: System::Windows::Forms::ToolStripMenuItem^  字体ToolStripMenuItem1;
	private: System::Windows::Forms::ToolStripMenuItem^  颜色ToolStripMenuItem1;
	private: System::Windows::Forms::ToolStripStatusLabel^  toolStripStatusLabel4;
	private: System::Windows::Forms::ToolStripStatusLabel^  toolStripStatusLabel3;
	private: System::Windows::Forms::ToolStripStatusLabel^  toolStripStatusLabel2;
	protected: 

	






	private: System::ComponentModel::IContainer^  components;

	private:
		/// <summary>
		/// 必需的设计器变量。
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// 设计器支持所需的方法 - 不要
		/// 使用代码编辑器修改此方法的内容。
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(Form1::typeid));
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->文件ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->新建ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->打开ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripSeparator1 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->保存ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->另存为ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripSeparator2 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->退出ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->编辑ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->撤销ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->重复ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripSeparator3 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->剪切ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->复制ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->粘贴ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripSeparator4 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->全选ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->格式ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripTextBox1 = (gcnew System::Windows::Forms::ToolStripTextBox());
			this->字体ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->颜色ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->查看ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->工具栏ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->状态栏ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->帮助ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->关于记事本ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStrip1 = (gcnew System::Windows::Forms::ToolStrip());
			this->新建NToolStripButton = (gcnew System::Windows::Forms::ToolStripButton());
			this->打开OToolStripButton = (gcnew System::Windows::Forms::ToolStripButton());
			this->保存SToolStripButton = (gcnew System::Windows::Forms::ToolStripButton());
			this->toolStripSeparator = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->剪切UToolStripButton = (gcnew System::Windows::Forms::ToolStripButton());
			this->复制CToolStripButton = (gcnew System::Windows::Forms::ToolStripButton());
			this->粘贴PToolStripButton = (gcnew System::Windows::Forms::ToolStripButton());
			this->toolStripSeparator5 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->帮助LToolStripButton = (gcnew System::Windows::Forms::ToolStripButton());
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
			this->剪切ToolStripMenuItem1 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->复制ToolStripMenuItem1 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->粘贴ToolStripMenuItem1 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->字体ToolStripMenuItem1 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->颜色ToolStripMenuItem1 = (gcnew System::Windows::Forms::ToolStripMenuItem());
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
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(5) {this->文件ToolStripMenuItem, 
				this->编辑ToolStripMenuItem, this->格式ToolStripMenuItem, this->查看ToolStripMenuItem, this->帮助ToolStripMenuItem});
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(366, 25);
			this->menuStrip1->TabIndex = 0;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// 文件ToolStripMenuItem
			// 
			this->文件ToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(7) {this->新建ToolStripMenuItem, 
				this->打开ToolStripMenuItem, this->toolStripSeparator1, this->保存ToolStripMenuItem, this->另存为ToolStripMenuItem, this->toolStripSeparator2, 
				this->退出ToolStripMenuItem});
			this->文件ToolStripMenuItem->Name = L"文件ToolStripMenuItem";
			this->文件ToolStripMenuItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Alt | System::Windows::Forms::Keys::F));
			this->文件ToolStripMenuItem->Size = System::Drawing::Size(44, 21);
			this->文件ToolStripMenuItem->Text = L"文件";
			// 
			// 新建ToolStripMenuItem
			// 
			this->新建ToolStripMenuItem->Name = L"新建ToolStripMenuItem";
			this->新建ToolStripMenuItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::N));
			this->新建ToolStripMenuItem->Size = System::Drawing::Size(147, 22);
			this->新建ToolStripMenuItem->Text = L"新建";
			this->新建ToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::OnNewFile);
			// 
			// 打开ToolStripMenuItem
			// 
			this->打开ToolStripMenuItem->Name = L"打开ToolStripMenuItem";
			this->打开ToolStripMenuItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::O));
			this->打开ToolStripMenuItem->Size = System::Drawing::Size(147, 22);
			this->打开ToolStripMenuItem->Text = L"打开";
			this->打开ToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::OnOpenFile);
			// 
			// toolStripSeparator1
			// 
			this->toolStripSeparator1->Name = L"toolStripSeparator1";
			this->toolStripSeparator1->Size = System::Drawing::Size(144, 6);
			// 
			// 保存ToolStripMenuItem
			// 
			this->保存ToolStripMenuItem->Name = L"保存ToolStripMenuItem";
			this->保存ToolStripMenuItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::S));
			this->保存ToolStripMenuItem->Size = System::Drawing::Size(147, 22);
			this->保存ToolStripMenuItem->Text = L"保存";
			this->保存ToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::OnSaveFile);
			// 
			// 另存为ToolStripMenuItem
			// 
			this->另存为ToolStripMenuItem->Name = L"另存为ToolStripMenuItem";
			this->另存为ToolStripMenuItem->Size = System::Drawing::Size(147, 22);
			this->另存为ToolStripMenuItem->Text = L"另存为";
			this->另存为ToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::OnSaveAsFile);
			// 
			// toolStripSeparator2
			// 
			this->toolStripSeparator2->Name = L"toolStripSeparator2";
			this->toolStripSeparator2->Size = System::Drawing::Size(144, 6);
			// 
			// 退出ToolStripMenuItem
			// 
			this->退出ToolStripMenuItem->Name = L"退出ToolStripMenuItem";
			this->退出ToolStripMenuItem->Size = System::Drawing::Size(147, 22);
			this->退出ToolStripMenuItem->Text = L"退出";
			this->退出ToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::OnExit);
			// 
			// 编辑ToolStripMenuItem
			// 
			this->编辑ToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(8) {this->撤销ToolStripMenuItem, 
				this->重复ToolStripMenuItem, this->toolStripSeparator3, this->剪切ToolStripMenuItem, this->复制ToolStripMenuItem, this->粘贴ToolStripMenuItem, 
				this->toolStripSeparator4, this->全选ToolStripMenuItem});
			this->编辑ToolStripMenuItem->Name = L"编辑ToolStripMenuItem";
			this->编辑ToolStripMenuItem->Size = System::Drawing::Size(44, 21);
			this->编辑ToolStripMenuItem->Text = L"编辑";
			// 
			// 撤销ToolStripMenuItem
			// 
			this->撤销ToolStripMenuItem->Name = L"撤销ToolStripMenuItem";
			this->撤销ToolStripMenuItem->Size = System::Drawing::Size(100, 22);
			this->撤销ToolStripMenuItem->Text = L"撤销";
			this->撤销ToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::OnUndo);
			// 
			// 重复ToolStripMenuItem
			// 
			this->重复ToolStripMenuItem->Name = L"重复ToolStripMenuItem";
			this->重复ToolStripMenuItem->Size = System::Drawing::Size(100, 22);
			this->重复ToolStripMenuItem->Text = L"重复";
			this->重复ToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::OnRedo);
			// 
			// toolStripSeparator3
			// 
			this->toolStripSeparator3->Name = L"toolStripSeparator3";
			this->toolStripSeparator3->Size = System::Drawing::Size(97, 6);
			// 
			// 剪切ToolStripMenuItem
			// 
			this->剪切ToolStripMenuItem->Name = L"剪切ToolStripMenuItem";
			this->剪切ToolStripMenuItem->Size = System::Drawing::Size(100, 22);
			this->剪切ToolStripMenuItem->Text = L"剪切";
			this->剪切ToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::OnCut);
			// 
			// 复制ToolStripMenuItem
			// 
			this->复制ToolStripMenuItem->Name = L"复制ToolStripMenuItem";
			this->复制ToolStripMenuItem->Size = System::Drawing::Size(100, 22);
			this->复制ToolStripMenuItem->Text = L"复制";
			this->复制ToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::OnCopy);
			// 
			// 粘贴ToolStripMenuItem
			// 
			this->粘贴ToolStripMenuItem->Name = L"粘贴ToolStripMenuItem";
			this->粘贴ToolStripMenuItem->Size = System::Drawing::Size(100, 22);
			this->粘贴ToolStripMenuItem->Text = L"粘贴";
			this->粘贴ToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::OnPaste);
			// 
			// toolStripSeparator4
			// 
			this->toolStripSeparator4->Name = L"toolStripSeparator4";
			this->toolStripSeparator4->Size = System::Drawing::Size(97, 6);
			// 
			// 全选ToolStripMenuItem
			// 
			this->全选ToolStripMenuItem->Name = L"全选ToolStripMenuItem";
			this->全选ToolStripMenuItem->Size = System::Drawing::Size(100, 22);
			this->全选ToolStripMenuItem->Text = L"全选";
			this->全选ToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::OnSelectAll);
			// 
			// 格式ToolStripMenuItem
			// 
			this->格式ToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {this->toolStripTextBox1, 
				this->字体ToolStripMenuItem, this->颜色ToolStripMenuItem});
			this->格式ToolStripMenuItem->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"格式ToolStripMenuItem.Image")));
			this->格式ToolStripMenuItem->Name = L"格式ToolStripMenuItem";
			this->格式ToolStripMenuItem->Size = System::Drawing::Size(60, 21);
			this->格式ToolStripMenuItem->Text = L"格式";
			// 
			// toolStripTextBox1
			// 
			this->toolStripTextBox1->Name = L"toolStripTextBox1";
			this->toolStripTextBox1->Size = System::Drawing::Size(100, 23);
			this->toolStripTextBox1->Click += gcnew System::EventHandler(this, &Form1::toolStripTextBox1_Click);
			// 
			// 字体ToolStripMenuItem
			// 
			this->字体ToolStripMenuItem->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"字体ToolStripMenuItem.Image")));
			this->字体ToolStripMenuItem->Name = L"字体ToolStripMenuItem";
			this->字体ToolStripMenuItem->Size = System::Drawing::Size(160, 22);
			this->字体ToolStripMenuItem->Text = L"字体";
			this->字体ToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::OnFont);
			// 
			// 颜色ToolStripMenuItem
			// 
			this->颜色ToolStripMenuItem->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"颜色ToolStripMenuItem.Image")));
			this->颜色ToolStripMenuItem->Name = L"颜色ToolStripMenuItem";
			this->颜色ToolStripMenuItem->Size = System::Drawing::Size(160, 22);
			this->颜色ToolStripMenuItem->Text = L"颜色";
			this->颜色ToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::OnColor);
			// 
			// 查看ToolStripMenuItem
			// 
			this->查看ToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {this->工具栏ToolStripMenuItem, 
				this->状态栏ToolStripMenuItem});
			this->查看ToolStripMenuItem->Name = L"查看ToolStripMenuItem";
			this->查看ToolStripMenuItem->Size = System::Drawing::Size(44, 21);
			this->查看ToolStripMenuItem->Text = L"查看";
			// 
			// 工具栏ToolStripMenuItem
			// 
			this->工具栏ToolStripMenuItem->Checked = true;
			this->工具栏ToolStripMenuItem->CheckState = System::Windows::Forms::CheckState::Checked;
			this->工具栏ToolStripMenuItem->Name = L"工具栏ToolStripMenuItem";
			this->工具栏ToolStripMenuItem->Size = System::Drawing::Size(112, 22);
			this->工具栏ToolStripMenuItem->Text = L"工具栏";
			this->工具栏ToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::OnTool);
			// 
			// 状态栏ToolStripMenuItem
			// 
			this->状态栏ToolStripMenuItem->Checked = true;
			this->状态栏ToolStripMenuItem->CheckState = System::Windows::Forms::CheckState::Checked;
			this->状态栏ToolStripMenuItem->Name = L"状态栏ToolStripMenuItem";
			this->状态栏ToolStripMenuItem->Size = System::Drawing::Size(112, 22);
			this->状态栏ToolStripMenuItem->Text = L"状态栏";
			this->状态栏ToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::OnStatus);
			// 
			// 帮助ToolStripMenuItem
			// 
			this->帮助ToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) {this->关于记事本ToolStripMenuItem});
			this->帮助ToolStripMenuItem->Name = L"帮助ToolStripMenuItem";
			this->帮助ToolStripMenuItem->Size = System::Drawing::Size(44, 21);
			this->帮助ToolStripMenuItem->Text = L"帮助";
			// 
			// 关于记事本ToolStripMenuItem
			// 
			this->关于记事本ToolStripMenuItem->Name = L"关于记事本ToolStripMenuItem";
			this->关于记事本ToolStripMenuItem->Size = System::Drawing::Size(136, 22);
			this->关于记事本ToolStripMenuItem->Text = L"关于记事本";
			this->关于记事本ToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::OnAbout);
			// 
			// toolStrip1
			// 
			this->toolStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(12) {this->新建NToolStripButton, 
				this->打开OToolStripButton, this->保存SToolStripButton, this->toolStripSeparator, this->剪切UToolStripButton, this->复制CToolStripButton, 
				this->粘贴PToolStripButton, this->toolStripSeparator5, this->帮助LToolStripButton, this->toolStripSeparator6, this->toolStripButton1, 
				this->toolStripButton2});
			this->toolStrip1->Location = System::Drawing::Point(0, 25);
			this->toolStrip1->Name = L"toolStrip1";
			this->toolStrip1->Size = System::Drawing::Size(366, 25);
			this->toolStrip1->TabIndex = 1;
			this->toolStrip1->Text = L"toolStrip1";
			//this->toolStrip1->ItemClicked += gcnew System::Windows::Forms::ToolStripItemClickedEventHandler(this, &Form1::toolStrip1_ItemClicked);
			// 
			// 新建NToolStripButton
			// 
			this->新建NToolStripButton->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->新建NToolStripButton->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"新建NToolStripButton.Image")));
			this->新建NToolStripButton->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->新建NToolStripButton->Name = L"新建NToolStripButton";
			this->新建NToolStripButton->Size = System::Drawing::Size(23, 22);
			this->新建NToolStripButton->Text = L"新建(&N)";
			this->新建NToolStripButton->Click += gcnew System::EventHandler(this, &Form1::OnNewFile);
			// 
			// 打开OToolStripButton
			// 
			this->打开OToolStripButton->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->打开OToolStripButton->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"打开OToolStripButton.Image")));
			this->打开OToolStripButton->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->打开OToolStripButton->Name = L"打开OToolStripButton";
			this->打开OToolStripButton->Size = System::Drawing::Size(23, 22);
			this->打开OToolStripButton->Text = L"打开(&O)";
			this->打开OToolStripButton->Click += gcnew System::EventHandler(this, &Form1::OnOpenFile);
			// 
			// 保存SToolStripButton
			// 
			this->保存SToolStripButton->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->保存SToolStripButton->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"保存SToolStripButton.Image")));
			this->保存SToolStripButton->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->保存SToolStripButton->Name = L"保存SToolStripButton";
			this->保存SToolStripButton->Size = System::Drawing::Size(23, 22);
			this->保存SToolStripButton->Text = L"保存(&S)";
			this->保存SToolStripButton->Click += gcnew System::EventHandler(this, &Form1::OnSaveFile);
			// 
			// toolStripSeparator
			// 
			this->toolStripSeparator->Name = L"toolStripSeparator";
			this->toolStripSeparator->Size = System::Drawing::Size(6, 25);
			// 
			// 剪切UToolStripButton
			// 
			this->剪切UToolStripButton->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->剪切UToolStripButton->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"剪切UToolStripButton.Image")));
			this->剪切UToolStripButton->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->剪切UToolStripButton->Name = L"剪切UToolStripButton";
			this->剪切UToolStripButton->Size = System::Drawing::Size(23, 22);
			this->剪切UToolStripButton->Text = L"剪切(&U)";
			this->剪切UToolStripButton->Click += gcnew System::EventHandler(this, &Form1::OnCut);
			// 
			// 复制CToolStripButton
			// 
			this->复制CToolStripButton->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->复制CToolStripButton->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"复制CToolStripButton.Image")));
			this->复制CToolStripButton->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->复制CToolStripButton->Name = L"复制CToolStripButton";
			this->复制CToolStripButton->Size = System::Drawing::Size(23, 22);
			this->复制CToolStripButton->Text = L"复制(&C)";
			this->复制CToolStripButton->Click += gcnew System::EventHandler(this, &Form1::OnCopy);
			// 
			// 粘贴PToolStripButton
			// 
			this->粘贴PToolStripButton->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->粘贴PToolStripButton->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"粘贴PToolStripButton.Image")));
			this->粘贴PToolStripButton->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->粘贴PToolStripButton->Name = L"粘贴PToolStripButton";
			this->粘贴PToolStripButton->Size = System::Drawing::Size(23, 22);
			this->粘贴PToolStripButton->Text = L"粘贴(&P)";
			this->粘贴PToolStripButton->Click += gcnew System::EventHandler(this, &Form1::OnPaste);
			// 
			// toolStripSeparator5
			// 
			this->toolStripSeparator5->Name = L"toolStripSeparator5";
			this->toolStripSeparator5->Size = System::Drawing::Size(6, 25);
			// 
			// 帮助LToolStripButton
			// 
			this->帮助LToolStripButton->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->帮助LToolStripButton->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"帮助LToolStripButton.Image")));
			this->帮助LToolStripButton->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->帮助LToolStripButton->Name = L"帮助LToolStripButton";
			this->帮助LToolStripButton->Size = System::Drawing::Size(23, 22);
			this->帮助LToolStripButton->Text = L"帮助(&L)";
			this->帮助LToolStripButton->Click += gcnew System::EventHandler(this, &Form1::OnAbout);
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
			this->statusStrip1->Text = L"大写";
			// 
			// toolStripStatusLabel1
			// 
			this->toolStripStatusLabel1->AutoSize = false;
			this->toolStripStatusLabel1->Name = L"toolStripStatusLabel1";
			this->toolStripStatusLabel1->Size = System::Drawing::Size(255, 18);
			this->toolStripStatusLabel1->Spring = true;
			this->toolStripStatusLabel1->Text = L"就绪";
			this->toolStripStatusLabel1->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->toolStripStatusLabel1->Click += gcnew System::EventHandler(this, &Form1::toolStripStatusLabel1_Click);
			this->toolStripStatusLabel1->MouseEnter += gcnew System::EventHandler(this, &Form1::OnSelMenu);
			// 
			// toolStripStatusLabel4
			// 
			this->toolStripStatusLabel4->BorderStyle = System::Windows::Forms::Border3DStyle::Sunken;
			this->toolStripStatusLabel4->Name = L"toolStripStatusLabel4";
			this->toolStripStatusLabel4->Size = System::Drawing::Size(32, 18);
			this->toolStripStatusLabel4->Text = L"大写";
			// 
			// toolStripStatusLabel3
			// 
			this->toolStripStatusLabel3->BorderStyle = System::Windows::Forms::Border3DStyle::Sunken;
			this->toolStripStatusLabel3->Name = L"toolStripStatusLabel3";
			this->toolStripStatusLabel3->Size = System::Drawing::Size(32, 18);
			this->toolStripStatusLabel3->Text = L"数字";
			// 
			// toolStripStatusLabel2
			// 
			this->toolStripStatusLabel2->BorderStyle = System::Windows::Forms::Border3DStyle::Sunken;
			this->toolStripStatusLabel2->Name = L"toolStripStatusLabel2";
			this->toolStripStatusLabel2->Size = System::Drawing::Size(32, 18);
			this->toolStripStatusLabel2->Text = L"滚动";
			// 
			// toolStripSplitButton1
			// 
			this->toolStripSplitButton1->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {this->toolStripMenuItem3, 
				this->toolStripMenuItem2});
			this->toolStripSplitButton1->Name = L"toolStripSplitButton1";
			this->toolStripSplitButton1->Size = System::Drawing::Size(48, 21);
			this->toolStripSplitButton1->Text = L"实验";
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
			this->contextMenuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(5) {this->剪切ToolStripMenuItem1, 
				this->复制ToolStripMenuItem1, this->粘贴ToolStripMenuItem1, this->字体ToolStripMenuItem1, this->颜色ToolStripMenuItem1});
			this->contextMenuStrip1->Name = L"contextMenuStrip1";
			this->contextMenuStrip1->Size = System::Drawing::Size(146, 114);
			// 
			// 剪切ToolStripMenuItem1
			// 
			this->剪切ToolStripMenuItem1->Name = L"剪切ToolStripMenuItem1";
			this->剪切ToolStripMenuItem1->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::X));
			this->剪切ToolStripMenuItem1->Size = System::Drawing::Size(145, 22);
			this->剪切ToolStripMenuItem1->Text = L"剪切";
			this->剪切ToolStripMenuItem1->Click += gcnew System::EventHandler(this, &Form1::OnCut);
			// 
			// 复制ToolStripMenuItem1
			// 
			this->复制ToolStripMenuItem1->Name = L"复制ToolStripMenuItem1";
			this->复制ToolStripMenuItem1->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::C));
			this->复制ToolStripMenuItem1->Size = System::Drawing::Size(145, 22);
			this->复制ToolStripMenuItem1->Text = L"复制";
			this->复制ToolStripMenuItem1->Click += gcnew System::EventHandler(this, &Form1::OnCopy);
			// 
			// 粘贴ToolStripMenuItem1
			// 
			this->粘贴ToolStripMenuItem1->Name = L"粘贴ToolStripMenuItem1";
			this->粘贴ToolStripMenuItem1->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::V));
			this->粘贴ToolStripMenuItem1->Size = System::Drawing::Size(145, 22);
			this->粘贴ToolStripMenuItem1->Text = L"粘贴";
			this->粘贴ToolStripMenuItem1->Click += gcnew System::EventHandler(this, &Form1::OnPaste);
			// 
			// 字体ToolStripMenuItem1
			// 
			this->字体ToolStripMenuItem1->Name = L"字体ToolStripMenuItem1";
			this->字体ToolStripMenuItem1->Size = System::Drawing::Size(145, 22);
			this->字体ToolStripMenuItem1->Text = L"字体";
			this->字体ToolStripMenuItem1->Click += gcnew System::EventHandler(this, &Form1::OnFont);
			// 
			// 颜色ToolStripMenuItem1
			// 
			this->颜色ToolStripMenuItem1->Name = L"颜色ToolStripMenuItem1";
			this->颜色ToolStripMenuItem1->Size = System::Drawing::Size(145, 22);
			this->颜色ToolStripMenuItem1->Text = L"颜色";
			this->颜色ToolStripMenuItem1->Click += gcnew System::EventHandler(this, &Form1::OnColor);
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
			this->Text = L"记事本";
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
			this->Text = "无标题--记事本";
			this->richTextBox1->Text = "";//设置文本编辑控件richTextBox1标题
			this->richTextBox1->Select(0, 0);//设置文本编辑控件richTextBox1选中文本为空
			this->richTextBox1->Modified = false;//设置文档改变标识为假
			this->strFileName = "";//设置正在编辑的文档名为空
		 }


private: System::Void OnOpenFile(System::Object^  sender, System::EventArgs^  e) {
			 if(!DoModified())return;
			 System::Windows::Forms::DialogResult dlg;//dlg用于获取通用对话框的输入
			 openFileDialog1->InitialDirectory = "c:\\";//设置通用对话框的初始路径；
			 openFileDialog1->Filter = "Rtf files(*.rtf)|*.rtf|文本文件(*.txt)|*.txt";//设置文件打开对话框的文件过滤器，只能打开扩展名为*.rtf与*.txt的文件
			 openFileDialog1->FileName = "";
			 dlg = openFileDialog1->ShowDialog();
			 try{
				if(dlg == System::Windows::Forms::DialogResult::OK)
					if(Path::GetExtension(openFileDialog1->FileName) == ".rtf")
					{
						//使用Path类的静态函数获得文件的扩展名
						strFileName = openFileDialog1->FileName;
						this->richTextBox1->LoadFile(strFileName, RichTextBoxStreamType::RichText);//读入带格式文本
						this->Text = Path::GetFileName(strFileName)+"--记事本";
							//使用Path类的静态方法获得文件名，并修改窗体标题
					}
					else
						if(Path::GetExtension(openFileDialog1->FileName) == ".txt")
						{
							strFileName = openFileDialog1->FileName;
							this->richTextBox1->LoadFile(strFileName,
								RichTextBoxStreamType::PlainText);//读入无格式文本
							this->Text = Path::GetFileName(strFileName)+"--记事本";
						}
						else 
							MessageBox::Show(L"选择的不是RTF或TXT格式的文件！ 无效", "错误",MessageBoxButtons::OK);

			 }
			 catch(System::ArgumentException ^e)
			 {
				MessageBox::Show(L"选择的不是RTF或TXT格式的文件！ 无效", "错误",MessageBoxButtons::OK);
			 }
		 }


private: System::Void OnSaveFile(System::Object^  sender, System::EventArgs^  e) {
			 if(strFileName->Length == 0)//无文件名
			 {
				System::Windows::Forms::DialogResult dlg;
				saveFileDialog1->Filter = "Rtf files(*.rtf)|*.rtf|文本文件(*.txt)|*.txt";//设置文件打开对话框的文件过滤器，只能打开扩展名为*.rtf与*.txt的文件
				dlg = saveFileDialog1->ShowDialog();
				if(dlg == System::Windows::Forms::DialogResult::OK)
					strFileName = saveFileDialog1->FileName;
				else
					return;
			 }
			 if(Path::GetExtension(strFileName) == ".rtf")
			 {
				this->richTextBox1->SaveFile(strFileName,
					RichTextBoxStreamType::RichText);//写入带格式文本
				this->Text = Path::GetFileName(strFileName)+"--记事本";
				richTextBox1->Modified = false;
			 }
			 else
				 if(Path::GetExtension(strFileName) == ".txt")
				 {
					this->richTextBox1->SaveFile(strFileName,
						RichTextBoxStreamType::PlainText);//写入无格式文本
					this->Text = Path::GetFileName(strFileName)+"--记事本";
					richTextBox1->Modified = false;
				 }
				 else
				 {
					MessageBox::Show(L"选择的不是RTF或TXT格式的文件！ 无效", "错误",MessageBoxButtons::OK);
					strFileName = "";
				 }
		 }

private: System::Void OnSaveAsFile(System::Object^  sender, System::EventArgs^  e) {
			  System::Windows::Forms::DialogResult dlg;//dlg用于获取通用对话框的输入
			  saveFileDialog1->Filter = "Rtf files(*.rtf)|*.rtf|文本文件(*.txt)|*.txt";//设置文件打开对话框的文件过滤器，只能打开扩展名为*.rtf与*.txt的文件
			  dlg = saveFileDialog1->ShowDialog();
			  if(dlg != System::Windows::Forms::DialogResult::OK)return;
			  if(Path::GetExtension(saveFileDialog1->FileName) == ".rtf")
			 {
				 strFileName = saveFileDialog1->FileName;
				this->richTextBox1->SaveFile(strFileName,
					RichTextBoxStreamType::RichText);//写入带格式文本
				this->Text = Path::GetFileName(strFileName)+"--记事本";
				richTextBox1->Modified = false;
			 }
			 else
				 if(Path::GetExtension(strFileName) == ".txt")
				 {
					this->richTextBox1->SaveFile(strFileName,
						RichTextBoxStreamType::PlainText);//写入无格式文本
					this->Text = Path::GetFileName(strFileName)+"--记事本";
					richTextBox1->Modified = false;
				 }
				 else
				 {
					MessageBox::Show(L"选择的不是RTF或TXT格式的文件！ 无效", "错误",MessageBoxButtons::OK);
					strFileName = "";
				 }

		 }


private: System::Void OnExit(System::Object^  sender, System::EventArgs^  e) {
			 this->Close();//关闭窗体
		 }

private: System::Void OnClose(System::Object^  sender, System::Windows::Forms::FormClosedEventArgs^  e) {
			 //e->Cancel = !DoModified();

		 }


private: System::Void OnUndo(System::Object^  sender, System::EventArgs^  e) {
			 this->richTextBox1->Undo();//撤销对文本框的操纵
		 }
private: System::Void OnRedo(System::Object^  sender, System::EventArgs^  e) {
			 this->richTextBox1->Redo();//恢复对文本框的操纵
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
				//用剪贴板上的内容替换文本框选定的内容
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
			 this->toolStrip1->Visible = ! this->toolStrip1->Visible;//使工具栏显示或隐藏
			 this->工具栏ToolStripMenuItem->Checked =! this->工具栏ToolStripMenuItem->Checked;
		 }

private: System::Void OnStatus(System::Object^  sender, System::EventArgs^  e) {
			 this->statusStrip1->Visible =! this->statusStrip1->Visible;
			 this->状态栏ToolStripMenuItem->Checked =! this ->状态栏ToolStripMenuItem->Checked;
		 }
private: System::Void OnAbout(System::Object^  sender, System::EventArgs^  e) {
			 AboutDlg^ dlg = gcnew AboutDlg;//创建关于对话框实例
			 dlg->ShowDialog();				//显示关于对话框
		 }
private: System::Void OnSelMenu(System::Object^  sender, System::EventArgs^  e) {
			 if(sender == this->文件ToolStripMenuItem)
				 this->toolStripStatusLabel1->Text = "文件";
			 if((sender == this->新建ToolStripMenuItem) ||(sender == this->新建NToolStripButton))
				 this->toolStripStatusLabel1->Text = "新建文件";
			 if((sender == this->打开ToolStripMenuItem) || (sender == this->打开OToolStripButton ))
				 this->toolStripStatusLabel1->Text = "打开文件";
			 if((sender == this->保存SToolStripButton) || (sender == this->保存ToolStripMenuItem ))
				 this->toolStripStatusLabel1->Text = "保存文件";
			 if((sender == this->另存为ToolStripMenuItem) )
				 this->toolStripStatusLabel1->Text = "另存为文件";
			 if(sender == this->退出ToolStripMenuItem )
				 this->toolStripStatusLabel1->Text = "退出";
		 }
		 
	void UpdateKeyPanel()
	{
		if(GetKeyState(20))//获取【大写】键的状态
			this->toolStripStatusLabel2->Text = "大写";
		else
			this->toolStripStatusLabel2->Text = "小写";
		if(GetKeyState(144))
			this->toolStripStatusLabel2->Text = "数字";
		else
			this->toolStripStatusLabel2->Text = "";
		if(GetKeyState(145))
			this->toolStripStatusLabel2->Text = "滚动";
		else
			this->toolStripStatusLabel2->Text = "";

	}
private: System::Void OnKey(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
			 UpdateKeyPanel();
		 }
private: System::Void OnLoad(System::Object^  sender, System::EventArgs^  e) {
			 this->richTextBox1->Size = System::Drawing::Size(this->ClientSize.Width,
				 this->ClientSize.Height - this->statusStrip1->Height -52);
			 //设置文本编辑控件richTextBox1的大小
			 UpdateKeyPanel();
			 OnNewFile(sender, e);
		 }
private: System::Void Form1_Resize(System::Object^  sender, System::EventArgs^  e) {
			 this->richTextBox1->Size = System::Drawing::Size(this->ClientSize.Width,
				 this->ClientSize.Height - this->statusStrip1->Height -52);
		 }
};
}

