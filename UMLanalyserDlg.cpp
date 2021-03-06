// UMLanalyserDlg.cpp : implementation file
//

#include "stdafx.h"
#include "UMLanalyser.h"
#include "UMLanalyserDlg.h"
#include "ADO.h"

#include <vector> 
using std::vector;

#include <string> 
#include <iostream>
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUMLanalyserDlg dialog
//:后面是初始化列表，调用CUMLanalyserDlg::CUMLanalyserDlg(CWnd* pParent /*=NULL*/)构造函数之前先调用CDialog(CUMLanalyserDlg::IDD, pParent)
CUMLanalyserDlg::CUMLanalyserDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CUMLanalyserDlg::IDD, pParent)
{

	//{{AFX_DATA_INIT(CUMLanalyserDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

//函数DoDataExchange(CDataExchange* pDX)未在CUMLanalyserDlg类中声明,"::"表示
void CUMLanalyserDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CUMLanalyserDlg)
	DDX_Control(pDX, IDC_BUTTON_TXTCANCEL, m_txtReturn);
	DDX_Control(pDX, IDC_BUTTON_LOGCANCEL, m_logReturn);
	DDX_Control(pDX, IDCANCEL, m_Close);
	DDX_Control(pDX, IDC_BUTTON_TXT, m_bTxt);
	DDX_Control(pDX, IDC_BUTTON_LOG, m_bLog);
	DDX_Control(pDX, IDC_BUTTON_ANALYSE, m_Analyse);
	DDX_Control(pDX, IDC_BUTTON_OPEN, m_Open);
	DDX_Control(pDX, IDC_EDIT, m_Edit);
	DDX_Control(pDX, IDC_TXT, m_Txt);
	DDX_Control(pDX, IDC_LOG, m_Log);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CUMLanalyserDlg, CDialog)
	//{{AFX_MSG_MAP(CUMLanalyserDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_OPEN, OnButtonOpen)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTON_ANALYSE, OnButtonAnalyse)
	ON_BN_CLICKED(IDC_BUTTON_LOG, OnButtonLog)
	ON_BN_CLICKED(IDC_BUTTON_TXT, OnButtonTxt)
	ON_BN_CLICKED(IDC_BUTTON_TXTCANCEL, OnButtonTxtcancel)
	ON_BN_CLICKED(IDC_BUTTON_LOGCANCEL, OnButtonLogcancel)
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUMLanalyserDlg message handlers

BOOL CUMLanalyserDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	////***********************************************************************
	////ZR 2016-11-4
	//#ifdef _DEBUG
	//if (AllocConsole())//弹出控制台窗口
	//{//AfxMessageBox("Failed to create the console!", MB_ICONEXCLAMATION);
	////控制台输出过程
	//HANDLE hdlWrite = GetStdHandle(STD_OUTPUT_HANDLE); //这里也可以使用STD_ERROR_HANDLE

	//TCHAR c[] = {"Hello world!"};
	//WriteConsole(hdlWrite, c, sizeof(c), NULL, NULL);

	//////控制台输入过程
	//TCHAR Buffer[100]; //开缓存
	//memset(Buffer, 0, 100);

	//DWORD dwCount = 0;//已输入数

	//HANDLE hdlRead = GetStdHandle(STD_INPUT_HANDLE);
	//ReadConsole(hdlRead, Buffer, 100, &dwCount, NULL);

	//////释放过程
	////CloseHandle(hdlRead);
	////CloseHandle(hdlWrite);
	//}
	//#endif 

	//
	////***********************************************************************
	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here

	isSelected = FALSE;
	m_Log.ShowWindow (FALSE);
	m_Txt.ShowWindow (FALSE);
	m_Edit.ShowWindow (TRUE);
	GetDlgItem(IDC_BUTTON_LOGCANCEL)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BUTTON_TXTCANCEL)->ShowWindow(SW_HIDE);
	GetDlgItem (IDC_BUTTON_ANALYSE)->EnableWindow(FALSE);	//使分析按钮无效化
	GetDlgItem (IDC_BUTTON_LOG)->EnableWindow(FALSE);		//使查看日志按钮无效化
	HRESULT hr;
	pXMLDoc = NULL;
	pObjError = NULL;
	rootNode = NULL;
	bstr = NULL;
	hr = CoInitialize (NULL);			//初始化COM
	if (FAILED(hr))						//COM初始化失败
	{
		AfxMessageBox ("Failed to CoInitialize the DOM library.Error code: %x\n", hr);
		Clean ();
	}

	//创建DOM的文档对象
	hr = CoCreateInstance(CLSID_DOMDocument2,NULL,CLSCTX_INPROC_SERVER,IID_IXMLDOMDocument2,(void**)&pXMLDoc);	
	if (FAILED(hr))
	{
		AfxMessageBox ("Failed to CoCreate an instance of an XML DOM.Error code: %x\n", hr);
		Clean ();
	}
	hr = pXMLDoc->put_async(VARIANT_FALSE);						// 设置异步属性为假（即同步）
	if (FAILED(hr)) 
	{
		AfxMessageBox ("Failed to set async property");
		Clean ();
	}
	hr = pXMLDoc->put_validateOnParse(VARIANT_TRUE);			// 设置分析时有效性验证为真
	if (FAILED(hr))
	{
		AfxMessageBox ("Failed to set validateOnParse");		
		Clean ();
	}
	hr = pXMLDoc->put_resolveExternals(VARIANT_TRUE);			// 设置解析外部实体为真
	if (FAILED(hr))
	{
		AfxMessageBox ("Failed to disable resolving externals.");
		Clean ();
	}
	//ZR 2016/11/4 销毁Dialog
	return TRUE;  // return TRUE  unless you set the focus to a control
}
//函数主要是截获控制命令的
void CUMLanalyserDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	//oxFFF0 对应的二进制：1111 1111 1111 0000
	//所以这里nID & 0xFFF0  就是把nID的最后4位置为0
	//然后判断得到的数据是否和 IDM_ABOUTBOX相等
	//nID参数的低四位被Windows内部使用。当应用程序测试nID的值时，它必须用位与操作符AND将值0xFFF0与nID的值组合在一起以获得正确的结果
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CUMLanalyserDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CPaintDC dc (this);													//定义设备上下文指针   
        CDC BmpDC;   
        CBitmap Mybmp;														//位图变量   
        CBitmap * OldBmp;   
        CRect rect;   
        Mybmp.LoadBitmap(IDB_BITMAP_BACKGROUND);											//从资源中装入位图   
        GetClientRect(rect);												//得到客户区域   
        BmpDC.CreateCompatibleDC(& dc);   
        OldBmp = BmpDC.SelectObject(& Mybmp);   
		BITMAP bm;
		memset( &bm, 0, sizeof(bm) );
		Mybmp.GetBitmap(&bm);
        dc.StretchBlt(0,0,rect.Width(),rect.Height(),& BmpDC,0,0,bm.bmWidth,bm.bmHeight,SRCCOPY);     //在显示器上粘贴位图   
        BmpDC.SelectObject(OldBmp); 
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CUMLanalyserDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CUMLanalyserDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	
	/*#ifdef _DEBUG
	if (!FreeConsole())
	AfxMessageBox("Could not free the console!");
	#endif */
	// TODO: Add your message handler code here
	Clean();				//清理
	CoUninitialize();		//释放COM
}

//********************************************************************//
//函数功能：在DOM出错或查询运行结束时清理相关信息                     //
//********************************************************************//
void CUMLanalyserDlg::Clean()
{
	if (bstr) SysFreeString (bstr);			//释放bstr
	if (&vSrc) VariantClear (& vSrc);		//清空vSrc
	if (pObjError) pObjError->Release ();	//释放DOM错误信息对象
	if (pXMLDoc) pXMLDoc->Release ();		//释放DOM文档对象
}

//********************************************************************//
//函数功能：处理“打开”按钮的操作，打开选定的XML文件并显示在编辑框   //
//********************************************************************//
void CUMLanalyserDlg::OnButtonOpen() 
{
	// TODO: Add your control notification handler code here
	HRESULT hr;//使用方式类似bool
	VARIANT_BOOL status;
	BSTR t_bstr;
	CString temp;

	CFileDialog dlg(TRUE,NULL,NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,
		"All Files(*.xml,*.xmi)|*.xml;*.xmi||",AfxGetMainWnd());//构造“文件打开”对话框
	if(dlg.DoModal() == IDOK)									//判断按下“打开”
	{
		//打开
		strPath = "";												//清空文件路径
		m_Edit.SetWindowText("");									//清空编辑框
		strPath = dlg.GetPathName();								//获取文件打开路径
		if (SetNameSpaces (strPath))
		{
			VariantInit (&vSrc);								// 设置VARIANT结构变量vSrc为XML文档文件名的Unicode字符串
			V_BSTR (&vSrc) = strPath.AllocSysString();			// 将文件名转换为Unicode字符串后赋值给vSrc结构的变量的bstrVal联合域
			V_VT (&vSrc) = VT_BSTR;								// 设置vSrc结构的变量类型vt域为VT_BSTR

			hr = pXMLDoc->load(vSrc, &status);					// 装入并验证XML文档，获取结果状态

			if(status!=VARIANT_TRUE)							// 装入失败
			{
				hr = pXMLDoc->get_parseError(&pObjError);
				hr = pObjError->get_reason(&bstr);
				temp.Format ("Failed to load DOM from selected file.%S", bstr);
				AfxMessageBox (temp);
				Clean ();
			}

			hr = pXMLDoc->get_xml (&t_bstr);					//获取xml文件内容 分析起点
			if (FAILED (hr))
			{
				printf("Failed to get XML document\n"); 
				return;
			}
		
			CString context (t_bstr);							//设置xml文件内容变量的内容
			content = context;
			m_Edit.SetWindowText (content);						//在编辑框中显示文件内容
			//m_Edit.SetModify (FALSE);
			isSelected = TRUE;
			//m_Log.ShowWindow (FALSE);
			//m_Txt.ShowWindow (FALSE);
			//m_Edit.ShowWindow (TRUE);
			//GetDlgItem(IDC_BUTTON_LOGCANCEL)->ShowWindow(SW_HIDE);
			//GetDlgItem(IDC_BUTTON_TXTCANCEL)->ShowWindow(SW_HIDE);
			GetDlgItem (IDC_BUTTON_ANALYSE)->EnableWindow(TRUE);//使分析按钮有效化
			GetDlgItem (IDC_BUTTON_LOG)->EnableWindow(FALSE);	//使查看日志按钮无效效化
		}
	}
	return;	
}

//********************************************************************//
//函数功能：根据xml文件内容设置分析xml的MSXML对象的命名空间           //？？？？？？？？
//********************************************************************//
BOOL CUMLanalyserDlg::SetNameSpaces(CString strPath)
{
	CFile file (strPath, CFile::modeRead);					//以读方式打开文件

	char buff [5000];
	CString fileText = "", nameSpace = "";
	int nBegin = 0, nEnd = 0, temp = 0;
	VARIANT t_vSrc;
	HRESULT hr;

	file.Read (buff, 5000);									//读取前5000字节内容
	file.Close ();

	for(int i=0; i < 5000; i++)
	{
		fileText += buff[i];
	}
	
	nBegin = fileText.Find ("xmlns:", 0);					//寻找第一个命名空间起始点
	if (nBegin == -1)
	{
		AfxMessageBox ("No namespaces for the xml/xmi file selected!");
		return TRUE;
	}
	nEnd = nBegin;
	for (int i = nBegin + 1; nEnd != -1 && i < 5000;)
	{
		nEnd = fileText.Find ("xmlns:", nEnd + 1);			//寻找最后一个命名空间起始点
		if (nEnd != -1)
		{
			temp = nEnd;
		}
	}
	if (!temp) temp = nBegin;
	nEnd = fileText.Find ("\"", temp + 1);
	nEnd = fileText.Find ("\"", nEnd + 1);					//寻找最后一个命名空间结束点

	nameSpace = fileText.Mid (nBegin, nEnd - nBegin + 1);	//获取命名空间内容

	VariantInit (&t_vSrc);									// 设置VARIANT结构变量t_vSrc为XML文档文件名的Unicode字符串
	V_BSTR (&t_vSrc) = nameSpace.AllocSysString();			// 将文件名转换为Unicode字符串后赋值给t_vSrc结构的变量的bstrVal联合域
	V_VT (&t_vSrc) = VT_BSTR;								// 设置t_vSrc结构的变量类型vt域为VT_BSTR

	hr = pXMLDoc->setProperty (L"SelectionNamespaces", t_vSrc);	// 设置解析命名空间
	if (FAILED (hr))
	{
		AfxMessageBox ("Failed to set namespaces.");
		Clean ();
		return FALSE;
	}
	return TRUE;
}

//********************************************************************//
//函数功能：1.为选定的xml文件创建对应的存储分析结果的数据库文件       //
//          2.设置日志文件的路径                                    //
//********************************************************************//
BOOL CUMLanalyserDlg::CreateDatabaseFile()
{
	HINSTANCE hInst = AfxGetInstanceHandle (); 

	//获取资源中原始数据库文件 
	HRSRC hExeFile = ::FindResource(hInst, MAKEINTRESOURCE(IDR_ACCESSDATABASE), TEXT("AccessDatabase")); 
	HGLOBAL hRes = ::LoadResource(hInst, hExeFile); 
	DWORD dwSize = ::SizeofResource(hInst, hExeFile); 

	//动态生成新的数据库文件路径和日志文件路径
	TCHAR exeFullPath [MAX_PATH];
	GetModuleFileName (NULL,exeFullPath,MAX_PATH);
	CString temp;
	databasePath.Format ("%s", exeFullPath);
	int i = databasePath.ReverseFind ('\\');
	int len = databasePath.GetLength();
	databasePath.Delete (i, len - i);
	i = strPath.ReverseFind ('\\');
	len = strPath.GetLength ();
	temp = strPath.Right (len - i);
	i = temp.ReverseFind ('.');
	len = temp.GetLength ();
	temp.Delete (i, len - i);
	databasePath += temp;
	CTime curTime = CTime::GetCurrentTime();
	temp = curTime.Format ("-%Y%m%d%H%M%S");
	databasePath += temp;
	logPath = databasePath;
	databasePath += ".mdb";
	logPath += ".log";

	//创建日志文件
	logFile.Open (logPath, CFile::modeCreate | CFile::modeWrite);

	//生成新的数据库文件
	if (hRes != NULL) 
	{
		UINT FAR * lpnRes = (UINT FAR *)::LockResource (hRes); 
		TRY
		{ 
			//构造文件
			CFile file(databasePath, CFile::modeCreate | CFile::modeWrite);
			//写入文件 
			file.Write(lpnRes, dwSize); 
			file.Flush (); 
		}
		CATCH (CFileException, e) 
		{
			return FALSE;
		}
		END_CATCH
		::FreeResource (hRes); 
		return TRUE; 
	}
	else
		return FALSE;
}

//********************************************************************//
//函数功能：开始从根节点分析UML的xml标准文件                          //
//********************************************************************//
void CUMLanalyserDlg::OnButtonAnalyse() 
{
	// TODO: Add your control notification handler code her
	HRESULT hr;
	unsigned int result;
	CString temp = "";

	if (CreateDatabaseFile ())
	{
		m_Ado.OnInitADOConn (databasePath);							//连接数据库
		/////////////////////////////////hr = pXMLDoc->selectSingleNode (L"//xmi:XMI", &rootNode);//added
		hr = pXMLDoc->selectSingleNode (L"//uml:Model", &rootNode);	//获取根节点
		if (FAILED (hr))
		{
			AfxMessageBox ("Fail to analyse the xml file because of a failure in getting root node.");
			Clean ();
			return;
		}
		result = NodeAnalyse (rootNode, "", "");					//从根节点开始分析
		if (result == SUCCEED)										//分析XML | XMI文件成功
		{
			temp = "";
			temp = "分析成功！\r\n结果存于数据库文件：" + databasePath + "\r\n";
			AfxMessageBox (temp, MB_ICONINFORMATION | MB_OK, 0);
			GetDlgItem (IDC_BUTTON_LOG)->EnableWindow(TRUE);		//使查看日志按钮有效化
			GetDlgItem (IDC_BUTTON_ANALYSE)->EnableWindow(FALSE);	//使分析按钮无效化
		}
		else if (result == IGNORED)									//分析XML | XMI文件存在忽略的成功
		{
			temp = "";
			temp = "分析成功, 部分信息被忽略\r\n结果存于数据库文件：" + databasePath + "\r\n";
			AfxMessageBox (temp, MB_ICONINFORMATION  | MB_OK, 0);
			GetDlgItem (IDC_BUTTON_LOG)->EnableWindow(TRUE);		//使查看日志按钮有效化			
			GetDlgItem (IDC_BUTTON_ANALYSE)->EnableWindow(FALSE);	//使分析按钮无效化
		}
		else														//分析XML | XMI文件失败
		{
			AfxMessageBox ("Analyse fail, some mistakes or errors occurs!", MB_ICONEXCLAMATION  | MB_OK, 0);
		}
		logFile.Close ();											//关闭日志文件
		m_Ado.CloseConn ();											//断开数据库
	}
	else															//创建数据库文件失败
	{
		AfxMessageBox ("Analyse fail, error occurs in creating database file!", MB_ICONEXCLAMATION  | MB_OK, 0);
		logFile.Close ();											//关闭日志文件
	}
}

//********************************************************************//
//函数功能：对一个节点进行判断分析，并调用相应的函数进行处理          //
//参数说明：pNode为此节点的指针，parentName为此节点的父节点名称，     //
//          parentID为父节点ID ，返回值为处理结果                     //
//********************************************************************//
unsigned int CUMLanalyserDlg::NodeAnalyse(IXMLDOMNode *pNode, CString parentName, CString parentID)
{
	HRESULT hr;
	VARIANT_BOOL b;
	BSTR text = NULL;
	DOMNodeType type;													//节点类型
	IXMLDOMNode *aNode = NULL;											//临时节点
	IXMLDOMNamedNodeMap *pAtts = NULL;									//属性列表
	IXMLDOMNodeList *pNodes = NULL;										//子节点列表
	CString temp = "", stype = "", name = "", ID = "", visibility = "";	//临时变量，节点信息类型，名称，ID，可见性
	long i = 0, childNum = 0, n =0;										//循环变量、子节点数量、属性节点数量
	unsigned int result = SUCCEED, tempResult = SUCCEED;				//子函数调用返回结果、临时结果
	CString resInfo = "";

	hr = pNode->get_nodeName(&bstr);									// 获取节点的名称
	if (FAILED (hr))
	{
		//log file
		AfxMessageBox ("Fail to get node name!");
		resInfo = "ERROR:Fail to get node name! Ignore the node and its child nodes.\r\nINFO:parentName:" + parentName + "    parentID:" + parentID + "\r\n\r\n"; 
		logFile.Write (resInfo, resInfo.GetLength ());
		return IGNORED;
	}
	stype.Format ("%S", bstr);
	if ( stype.Compare ("uml:Model") &&  stype.Compare ("packagedElement"))
	{
		//log file
		resInfo = "IGNORE:Ignore a node of node name \"" + stype + "\" and its child nodes!\r\nINFO:parentName:" + parentName + "    parentID:" + parentID + "\r\n\r\n"; 
		logFile.Write (resInfo, resInfo.GetLength ());
		return IGNORED;
	}

	hr = pNode->get_nodeTypeString(&text);		// 获得节点类型的字符串
	if (FAILED (hr))
	{
		AfxMessageBox ("Fail to get the name of node type!");
		//log file
		resInfo = "ERROR:Fail to get name of node type! Ignore the node and its child nodes.\r\nINFO:node name:" + stype + "parentName:" + parentName + "    parentID:" + parentID + "\r\n\r\n"; 
		logFile.Write (resInfo, resInfo.GetLength ());
		return IGNORED;
	}
	hr = pNode->get_nodeType(&type);			// 获取节点的类型
	if (FAILED (hr))
	{
		AfxMessageBox ("Fail to get node type!");
		//log file
		resInfo = "ERROR:Fail to get node type! Ignore the node andits child nodes.\r\nINFO:node name:" + stype + "    parentName:" + parentName + "    parentID:" + parentID + "\r\n\r\n"; 
		logFile.Write (resInfo, resInfo.GetLength ());
		return IGNORED;
	}
	hr = pNode->hasChildNodes (&b);				//判断节点是否有孩子
	if (FAILED (hr))
	{
		AfxMessageBox ("Fail to find whether the node has child!");
		//log file
		resInfo = "ERROR:Fail to find whether the node has child! Ignore child nodes of the node.\r\nINFO:node name:" + stype + "    parentName:" + parentName + "    parentID:" + parentID + "\r\n\r\n"; 
		logFile.Write (resInfo, resInfo.GetLength ());
		return IGNORED;
	}

	if (type == NODE_ELEMENT)
	{
		hr = pNode->get_attributes (&pAtts);
		if (FAILED (hr))
		{
			AfxMessageBox ("Fail to get attributes of the node!");
			//log file
			resInfo = "ERROR:Fail to get attributes of the node! Ignore all attributes of the node.\r\nINFO:node name:" + stype + "    parentName:" + parentName + "    parentID:" + parentID + "\r\n\r\n"; 
			logFile.Write (resInfo, resInfo.GetLength ());
			return IGNORED;
		}
		hr = pAtts->getNamedItem(L"xmi:type",& aNode);
		if (FAILED (hr))
		{
			AfxMessageBox ("Fail to get wanted attribute!");
			//log file
			resInfo = "ERROR:Fail to get \"xmi:type\" of the node! Ignore all attributes of the node.\r\nINFO:node name:" + stype + "    parentName:" + parentName + "    parentID:" + parentID + "\r\n\r\n"; 
			logFile.Write (resInfo, resInfo.GetLength ());
			return IGNORED;
		}
		hr = aNode->get_text(&text); 
		if (FAILED (hr))
		{
			AfxMessageBox ("Fail to get wanted attribute!");
			//log file
			resInfo = "ERROR:Fail to get \"xmi:type\" of the node! Ignore all attributes of the node.\r\nINFO:node name:" + stype + "    parentName:" + parentName + "    parentID:" + parentID + "\r\n\r\n"; 
			logFile.Write (resInfo, resInfo.GetLength ());
			return IGNORED;
		}

		if (text != NULL)
		{
			stype.Format ("%S", text);								//显示节点的文本内容
			if (!stype.Compare ("uml:Class"))						//类节点
			{
				tempResult = ClassAnalyse (pNode, parentName, parentID);
				if (tempResult < result) result = tempResult;
			}
			else if (!stype.Compare ("uml:Association"))			//关联节点
			{
				tempResult = AssociationAnalyse (pNode, parentName, parentID);
				if (tempResult < result) result = tempResult;
			}
			else if (!stype.Compare ("uml:Collaboration"))			//合作节点
			{
				tempResult = CollaborationAnalyse (pNode, parentName, parentID);
				if (tempResult < result) result = tempResult;
			}
			else if (!stype.Compare ("uml:AssociationClass"))		//关联类节点
			{
				tempResult = AssociationClassAnalyse (pNode, parentName, parentID);
				if (tempResult < result) result = tempResult;
			}
			else if (!stype.Compare ("uml:Actor"))					//角色节点
			{
				tempResult = ActorAnalyse (pNode, parentName, parentID);
				if (tempResult < result) result = tempResult;
			}
			else if (!stype.Compare ("uml:Package"))				//包节点
			{
				hr = pAtts->get_length (&n);						// 获取节点个数
				if (FAILED (hr))
				{
					AfxMessageBox ("Fail to get number of attributes!");
					//log file
					resInfo = "IGNORE:Fail to get attributes of a \"uml:Packet\" node! Ignore all attributes of the node.\r\nINFO:node name:" + stype + "    parentName:" + parentName + "    parentID:" + parentID + "\r\n\r\n"; 
					logFile.Write (resInfo, resInfo.GetLength ());
					return IGNORED;
				}
				name = "";
				ID = "";
				visibility = "";
				for (i = 0; i < n; i ++)
				{
					hr = pAtts->get_item (i, &aNode);
					if (FAILED (hr))
					{
						AfxMessageBox ("Fail to get wanted attributes!");
						//log file
						temp.Format ("%d", i);
						resInfo = "ERROR:Fail to get the ith attribute of the \"uml:Packet\" node! Ignore this attribute.\r\nINFO:node name:" + stype + "    parentName:" + parentName + "    parentID:" + parentID + "    i:" + temp + "\r\n\r\n"; 
						logFile.Write (resInfo, resInfo.GetLength ());
						if (result == SUCCEED) result = IGNORED;
						continue;
					}
					hr = aNode->get_nodeName (&bstr);			// 获取节点的名称
					if (FAILED (hr))
					{
						AfxMessageBox ("Fail to get name of wanted attributes!");
						//log file
						temp.Format ("%d", i);
						resInfo = "ERROR:Fail to get the ith attribute of the \"uml:Packet\" node! Ignore this attribute.\r\nINFO:node name:" + stype + "    parentName:" + parentName + "    parentID:" + parentID + "    i:" + temp + "\r\n\r\n"; 
						logFile.Write (resInfo, resInfo.GetLength ());
						if (result == SUCCEED) result = IGNORED;
						continue;
					}
					hr = aNode->get_text (&text); 
					if (FAILED (hr) || text == NULL)
					{
						AfxMessageBox ("Fail to get the value of wanted attributes!");
						temp.Format ("%d", i);
						resInfo = "ERROR:Fail to get the ith attribute of the \"uml:Packet\" node! Ignore this attribute.\r\nINFO:node name:" + stype + "    parentName:" + parentName + "    parentID:" + parentID + "    i:" + temp + "\r\n\r\n"; 
						logFile.Write (resInfo, resInfo.GetLength ());
						if (result == SUCCEED) result = IGNORED;
						continue;
					}
					temp.Format ("%S",bstr);
					if (! temp.Compare ("xmi:id"))
					{
						ID.Format ("%S", text);
					}
					else if (! temp.Compare ("name"))
					{
						name.Format ("%S", text);
					}
					else if (! temp.Compare ("visibility"))
					{
						visibility.Format ("%S", text);
					}
					else if (temp.Compare ("xmi:type"))
					{
						resInfo = "IGNORE:Ignore the ith attribute of the \"uml:Packet\" node! Attribute type is \"" + temp + "\".\r\nINFO:node name:" + stype + "    parentName:" + parentName + "    parentID:" + parentID + "    i:";
						temp.Format ("%d\r\n\r\n", i);
						resInfo += temp; 
						logFile.Write (resInfo, resInfo.GetLength ());
					}
				}
				try
				{
					CString sql = "select * from package";								//设置查询字符串
					m_Ado.m_pRecordset = m_Ado.OpenRecordset(sql);						//打开记录集
					m_Ado.m_pRecordset->AddNew();										//添加新行
					m_Ado.m_pRecordset->PutCollect("名称", (_bstr_t)name);				//设置名称字段内容
					m_Ado.m_pRecordset->PutCollect("ID", (_bstr_t)ID);					//设置ID字段内容
					m_Ado.m_pRecordset->PutCollect("可见性", (_bstr_t)visibility);		//设置可见性字段内容
					m_Ado.m_pRecordset->PutCollect("所属包", (_bstr_t)parentName);		//设置所属包字段内容
					m_Ado.m_pRecordset->PutCollect("所属包ID", (_bstr_t)parentID);		//设置所属包ID字段内容
					m_Ado.m_pRecordset->Update();										//更新记录集
					m_Ado.CloseRecordset();												//关闭记录集
				}
				catch(_com_error e)
				{
					AfxMessageBox(e.Description());										//弹出错误处理
					//log file
					resInfo = "ERROR:Fail to put packet data into database! Ignore this database write.\r\nINFO:packet name:" + name + "    packetID:" + ID + "\r\n\r\n"; 
					logFile.Write (resInfo, resInfo.GetLength ());
				}
				if (b)
				{
					hr = pNode->get_childNodes (&pNodes);
					if (FAILED (hr))
					{
						AfxMessageBox ("Fail to get children of the node!");
						//log file
						resInfo = "ERROR:Fail to get child nodes of the packet node! Ignore all child nodes of the packet.\r\nINFO:packet name:" + name + "    packetID:" + ID + "\r\n\r\n"; 
						logFile.Write (resInfo, resInfo.GetLength ());
						return IGNORED;
					}
					hr = pNodes->get_length (&childNum);				// 获取节点个数
					if (FAILED (hr))
					{
						AfxMessageBox ("Fail to get the number of the children of the node!");
						//log file
						resInfo = "ERROR:Fail to get number of child nodes! Ignore all child nodes of the packet.\r\nINFO:packet name:" + name + "    packetID:" + ID + "\r\n\r\n"; 
						logFile.Write (resInfo, resInfo.GetLength ());
						return IGNORED;
					}
					for (i = 0; i < childNum; i ++)
					{
						hr = pNodes->get_item (i, &aNode);
						if (FAILED (hr))
						{
							AfxMessageBox ("Fail to get the selected children of the node!");
							//log file
							temp.Format ("%d", i);
							resInfo = "ERROR:Fail to get ith child nodes of the packet node! Ignore the ith child node.\r\nINFO:packet name:" + name + "    packetID:" + ID + "    i:" + temp + "\r\n\r\n"; 
							logFile.Write (resInfo, resInfo.GetLength ());
							if (result == SUCCEED) result = IGNORED;
							continue;
						}
						tempResult = NodeAnalyse (aNode, name, ID);		//递归分析子节点
						if (tempResult < result) result = tempResult;
					}
				}
			}
			else if (!stype.Compare ("uml:Model"))					//模型节点
			{

				if (b)
				{
					hr = pNode->get_childNodes (&pNodes);
					if (FAILED (hr))
					{
						AfxMessageBox ("Fail to get children of the node!");
						//log file
						resInfo = "ERROR:Fail to get child nodes of a \"uml:Model\" node! Ignore all child nodes of the node.\r\nINFO:node name:" + stype + "    parentName:" + parentName + "    parentID:" + parentID + "\r\n\r\n"; 
						logFile.Write (resInfo, resInfo.GetLength ());
						return IGNORED;
					}
					hr = pNodes->get_length (&childNum);			// 获取节点个数
					if (FAILED (hr))
					{
						AfxMessageBox ("Fail to get the number of the children of the node!");
						//log file
						resInfo = "ERROR:Fail to get number of child nodes of the \"uml:Model\" node! Ignore all child nodes of the node.\r\nINFO:node name:" + stype + "    parentName:" + parentName + "    parentID:" + parentID + "\r\n\r\n"; 
						logFile.Write (resInfo, resInfo.GetLength ());
						return IGNORED;
					}
					for (i = 0; i < childNum; i ++)
					{
						hr = pNodes->get_item (i, &aNode);
						if (FAILED (hr))
						{
							AfxMessageBox ("Fail to get the selected children of the node!");
							//log file
							temp.Format ("%d", i);
							resInfo = "ERROR:Fail to get ith child node of a \"uml:Model\" node! Ignore the ith child node.\r\nINFO:node name:" + stype + "    parentName:" + parentName + "    parentID:" + parentID + "    i:" + temp + "\r\n\r\n"; 
							logFile.Write (resInfo, resInfo.GetLength ());
							if (result == SUCCEED) result = IGNORED;
							continue;
						}
						tempResult = NodeAnalyse (aNode, "", "");	//递归分析子节点
						if (tempResult < result) result = tempResult;
					}
				}
			}
			else
			{
				//log file
				resInfo = "IGNORE:A node of node name \"" + stype + "\" and its child nodes!\r\nINFO:parentName:" + parentName + "    parentID:" + parentID + "\r\n\r\n"; 
				logFile.Write (resInfo, resInfo.GetLength ());
				return IGNORED;
			}
			return result;
		}
	}
	return result;
}

//********************************************************************//
//函数功能：对一个类节点进行判断分析，处理其属性及方法                //
//参数说明：pNode为此节点的指针，parentName为此节点的父节点名称，     //
//          parentID为父节点ID ，返回值为处理结果                     //
//********************************************************************//
unsigned int CUMLanalyserDlg::ClassAnalyse(IXMLDOMNode *pNode, CString parentName, CString parentID)
{
	long int n = -1, i = 0;
	unsigned int result = SUCCEED, tempResult = SUCCEED;//处理结果
	CString nodeName = "", pname = "", pID = "", pvisibility = "", sql = "";
	HRESULT hr;
	VARIANT_BOOL b;
	BSTR text = NULL;									//节点值
	IXMLDOMNamedNodeMap *pAtts = NULL;					//属性节点列表
	IXMLDOMNode *aNode = NULL;
	IXMLDOMNodeList *pNodes = NULL;						//子节点列表
	CString resInfo = "", temp = "";
	
	//类的属性分析
	hr = pNode->get_attributes (&pAtts);
	if (FAILED (hr))
	{
		AfxMessageBox ("Fail to get attributes of the node!");
		//log file
		resInfo = "ERROR:Fail to get attributes of the class node! Ignore all attributes of the node.\r\nINFO:parentName:" + parentName + "    parentID:" + parentID + "\r\n\r\n"; 
		logFile.Write (resInfo, resInfo.GetLength ());
		return IGNORED;
	}
	hr = pAtts->get_length (&n);						// 获取属性节点个数
	//cout<<"*************************************************************************N: "<<n<<endl;
	if (FAILED (hr))
	{
		AfxMessageBox ("Fail to get number of the attributes of the node!");
		//log file
		resInfo = "ERROR:Fail to get number of attributes of the class node! Ignore all attributes of the node.\r\nINFO:parentName:" + parentName + "    parentID:" + parentID + "\r\n\r\n"; 
		logFile.Write (resInfo, resInfo.GetLength ());
		return IGNORED;
	}
	for (i = 0; i < n; i ++)
	{
		hr = pAtts->get_item (i, &aNode);
		if (FAILED (hr))
		{
			AfxMessageBox ("Fail to get the wanted attribute of the node!");
			//log file
			temp.Format ("%d", i);
			resInfo = "ERROR:Fail to get ith attribute node of the class node! Ignore the ith attribute node.\r\nINFO:INFO:parentName:" + parentName + "    parentID:" + parentID + "    i:" + temp + "\r\n\r\n"; 
			logFile.Write (resInfo, resInfo.GetLength ());
			if (result == SUCCEED) result = IGNORED;
			continue;
		}
		hr = aNode->get_nodeName (&bstr);			// 获取属性节点的名称
		if (FAILED (hr))
		{
			AfxMessageBox ("Fail to get name of the wanted attribute!");
			//log file
			temp.Format ("%d", i);
			resInfo = "ERROR:Fail to get ith attribute node of the class node! Ignore the ith attribute node.\r\nINFO:INFO:parentName:" + parentName + "    parentID:" + parentID + "    i:" + temp + "\r\n\r\n"; 
			logFile.Write (resInfo, resInfo.GetLength ());
			if (result == SUCCEED) result = IGNORED;
			continue;
		}
		nodeName.Format ("%S",bstr);
		text = NULL;
		hr = aNode->get_text (&text);				//获取属性节点的值
		if (FAILED (hr) || text == NULL)
		{
			AfxMessageBox ("Fail to get the value of wanted attribute's name!");
			//log file
			temp.Format ("%d", i);
			resInfo = "ERROR:Fail to get ith attribute node of the class node! Ignore the ith attribute node.\r\nINFO:INFO:parentName:" + parentName + "    parentID:" + parentID + "    i:" + temp + "\r\n\r\n"; 
			logFile.Write (resInfo, resInfo.GetLength ());
			if (result == SUCCEED) result = IGNORED;
			continue;
		}
		if (!nodeName.Compare ("xmi:id"))
		{
			pID.Format ("%S", text);
		}
		else if (!nodeName.Compare ("name"))
		{
			pname.Format ("%S", text);
		}
		else if (!nodeName.Compare ("visibility"))
		{
			pvisibility.Format ("可见性:%S", text);
		}
		else if (temp.Compare ("xmi:type"))
		{
			//log file
			resInfo = "IGNORE:Ignore the ith attribute of the \"uml:Class\" node! Attribute type is \"" + temp + "\".\r\nINFO:parentName:" + parentName + "    parentID:" + parentID + "    i:";
			temp.Format ("%d\r\n\r\n", i);
			resInfo += temp; 
			logFile.Write (resInfo, resInfo.GetLength ());
		}
	}
	try
	{
		sql = "select * from class";										//设置查询字符串
		m_Ado.m_pRecordset = m_Ado.OpenRecordset(sql);						//打开记录集
		m_Ado.m_pRecordset->AddNew();										//添加新行
		m_Ado.m_pRecordset->PutCollect("名称", (_bstr_t)pname);				//设置名称字段内容
		m_Ado.m_pRecordset->PutCollect("ID", (_bstr_t)pID);					//设置ID字段内容
		m_Ado.m_pRecordset->PutCollect("备注", (_bstr_t)pvisibility);		//设置备注字段内容
		m_Ado.m_pRecordset->PutCollect("所属包", (_bstr_t)parentName);		//设置所属包字段内容
		m_Ado.m_pRecordset->PutCollect("所属包ID", (_bstr_t)parentID);		//设置所属包ID字段内容
		m_Ado.m_pRecordset->Update();										//更新记录集
		m_Ado.CloseRecordset();												//关闭记录集
	}
	catch(_com_error e)
	{
		AfxMessageBox(e.Description());										//弹出错误处理
		//log file
		resInfo = "ERROR:Fail to put class data into database! Ignore this database write.\r\nINFO:class name:" + pname + "    class ID:" + pID + "\r\n\r\n"; 
		logFile.Write (resInfo, resInfo.GetLength ());
		if (result == SUCCEED) result = IGNORED;
	}

	//类的成员属性和方法分析
	hr = pNode->hasChildNodes (&b);											//判断节点是否有孩子
	if (FAILED (hr))
	{
		AfxMessageBox ("Fail to find whether the node has child!");
		//log file
		resInfo = "ERROR:Fail to find whether the node has child! Ignore child nodes of the node.\r\nINFO:class name:" + pname  + "    class ID:" + pID + "\r\n\r\n"; 
		logFile.Write (resInfo, resInfo.GetLength ());
		return IGNORED;
	}
	if (!b)											//没有子节点(即没有成员属性和方法)
	{
		return result;
	}

	hr = pNode->get_childNodes (&pNodes);			//获取子节点
	if (FAILED (hr))
	{
		AfxMessageBox ("Fail to get attributes of the node!");
		//log file
		resInfo = "ERROR:Fail to get child nodes of the class node! Ignore all child nodes of the class.\r\nINFO:class name:" + pname + "    class ID:" + pID + "\r\n\r\n"; 
		logFile.Write (resInfo, resInfo.GetLength ());
		return IGNORED;
	}
	hr = pNodes->get_length (&n);					// 获取子节点个数
	if (FAILED (hr))
	{
		AfxMessageBox ("Fail to get number of the attributes of the node!");
		//log file
		resInfo = "ERROR:Fail to get number of child nodes of the class node! Ignore all child nodes of the class.\r\nINFO:class name:" + pname + "    class ID:" + pID + "\r\n\r\n"; 
		logFile.Write (resInfo, resInfo.GetLength ());
		return IGNORED;
	}
	for (i = 0; i < n; i ++)
	{
		hr = pNodes->get_item (i, &aNode);
		if (FAILED (hr))
		{
			AfxMessageBox ("Fail to get the wanted child node!");
			//log file
			temp.Format ("%d", i);
			resInfo = "ERROR:Fail to get ith child nodes of the class node! Ignore the ith child node.\r\nINFO:class name:" + pname + "    class ID:" + pID + "    i:" + temp + "\r\n\r\n"; 
			logFile.Write (resInfo, resInfo.GetLength ());
			if (result == SUCCEED) result = IGNORED;
			continue;
		}
		hr = aNode->get_nodeName (&bstr);			// 获取子节点的名称
		if (FAILED (hr))
		{
			AfxMessageBox ("Fail to get name of the wanted chile node!");
			//log file
			temp.Format ("%d", i);
			resInfo = "ERROR:Fail to get ith child nodes of the class node! Ignore the ith child node.\r\nINFO:class name:" + pname + "    class ID:" + pID + "    i:" + temp + "\r\n\r\n"; 
			logFile.Write (resInfo, resInfo.GetLength ());
			if (result == SUCCEED) result = IGNORED;
			continue;
		}
		nodeName.Format ("%S",bstr);
		text = NULL;
		hr = aNode->get_text (&text);						//获取属性节点的值
		if (FAILED (hr) || text == NULL)
		{
			AfxMessageBox ("Fail to get the value of wanted child's name!");
			//log file
			temp.Format ("%d", i);
			resInfo = "ERROR:Fail to get ith child nodes of the class node! Ignore the ith child node.\r\nINFO:class name:" + pname + "    class ID:" + pID + "    i:" + temp + "\r\n\r\n"; 
			logFile.Write (resInfo, resInfo.GetLength ());
			if (result == SUCCEED) result = IGNORED;
			continue;
		}
		if (!nodeName.Compare ("ownedAttribute"))			//成员属性分析
		{
			tempResult = ClassAttributeAnalyse (aNode, pname, pID);
			if (tempResult <= result) result = tempResult;
		}
		else if (!nodeName.Compare ("ownedOperation"))		//成员方法分析
		{
			tempResult = ClassOperationAnalyse (aNode, pname, pID);
			if (tempResult <= result) result = tempResult;
		}
		else if (!nodeName.Compare ("generalization"))		//继承信息分析
		{
			tempResult = ClassGeneralizationAnalyse (aNode, pname, pID);
			if (tempResult <= result) result = tempResult;
		}
		else if (temp.Compare ("xmi:type"))					//其它
		{
			//log file	
			resInfo = "IGNORE:Ignore the  ith child node of the class node!.\r\nINFO:class name:" + pname + "    class ID:" + pID + "    child node type:" + temp; 
			temp.Format ("%d\r\n\r\n", i);
			resInfo += temp;
			logFile.Write (resInfo, resInfo.GetLength ());
			if (result == SUCCEED) result = IGNORED;
			continue;
		}
	}
	return result;
}

//********************************************************************//
//函数功能：对一个关联节点进行判断分析，并处理其信息及端点信息        //
//参数说明：pNode为此节点的指针，parentName为此节点的父节点名称，     //
//          parentID为父节点ID ，返回值为处理结果                     //
//********************************************************************//
unsigned int CUMLanalyserDlg::AssociationAnalyse(IXMLDOMNode *pNode, CString parentName, CString parentID)
{
	long int n = -1, i = 0, j = 0, m = -1, k = 0, l = -1, n1= -1, i1 = 0, count = 0;
	BOOL isFound = FALSE;
	unsigned int result = SUCCEED, tempResult = SUCCEED;						//处理结果
	CString nodeName = "", endID = "", pname = "", pID = "", pvisibility = "", pdirection = "", paggregation = "", sql = "", temp = "", resInfo = "";
	HRESULT hr;
	VARIANT_BOOL b;
	BSTR text = NULL;															//节点值
	IXMLDOMNamedNodeMap *pAtts = NULL, *qAtts = NULL, *propertyAtts = NULL;		//属性节点列表
	IXMLDOMNode *endNode = NULL, *endPNode = NULL, *aNode = NULL, *bNode = NULL, *cNode = NULL;
	IXMLDOMNode *classNode = NULL, *attributeNode = NULL, *propertyNode = NULL;
	IXMLDOMNodeList *pNodes = NULL, *qNodes = NULL, *rNodes = NULL;				//子节点列表
	CString end1 = "", end1name = "", end1ID = "", end1role = "", end1visibility = "", end1multiplicity = "";
	CString end2 = "", end2name = "", end2ID = "", end2role = "", end2visibility = "", end2multiplicity = "";
	CString valueType = "", value = "", lowerValue = "", upperValue = "";

	//关联的属性分析
	hr = pNode->get_attributes (&pAtts);
	if (FAILED (hr))
	{
		AfxMessageBox ("Fail to get attributes of the node!");
		//log file
		resInfo = "ERROR:Fail to get attributes of the association node! Ignore all attributes of the node.\r\nINFO:parentName:" + parentName + "    parentID:" + parentID + "\r\n\r\n"; 
		logFile.Write (resInfo, resInfo.GetLength ());
		return IGNORED;
	}
	hr = pAtts->get_length (&n);					// 获取属性节点个数
	if (FAILED (hr))
	{
		AfxMessageBox ("Fail to get number of the attributes of the node!");
		//log file
		resInfo = "ERROR:Fail to get number of attributes of the association node! Ignore all attributes of the node.\r\nINFO:parentName:" + parentName + "    parentID:" + parentID + "\r\n\r\n"; 
		logFile.Write (resInfo, resInfo.GetLength ());
		return IGNORED;
	}
	for (i = 0; i < n; i ++)
	{
		hr = pAtts->get_item (i, &aNode);
		if (FAILED (hr))
		{
			AfxMessageBox ("Fail to get the wanted attribute of the node!");
			//log file
			temp.Format ("%d", i);
			resInfo = "ERROR:Fail to get ith attribute node of the association node! Ignore the ith attribute node.\r\nINFO:INFO:parentName:" + parentName + "    parentID:" + parentID + "    i:" + temp + "\r\n\r\n"; 
			logFile.Write (resInfo, resInfo.GetLength ());
			if (result == SUCCEED) result = IGNORED;
			continue;
		}
		hr = aNode->get_nodeName (&bstr);			// 获取属性节点的名称
		if (FAILED (hr))
		{
			AfxMessageBox ("Fail to get name of the wanted attribute!");
			//log file
			temp.Format ("%d", i);
			resInfo = "ERROR:Fail to get ith attribute node of the association node! Ignore the ith attribute node.\r\nINFO:INFO:parentName:" + parentName + "    parentID:" + parentID + "    i:" + temp + "\r\n\r\n"; 
			logFile.Write (resInfo, resInfo.GetLength ());
			if (result == SUCCEED) result = IGNORED;
			continue;
		}
		nodeName.Format ("%S",bstr);
		text = NULL;
		hr = aNode->get_text (&text);				//获取属性节点的值
		if (FAILED (hr) || text == NULL)
		{
			AfxMessageBox ("Fail to get the value of wanted attribute's name!");
			//log file
			temp.Format ("%d", i);
			resInfo = "ERROR:Fail to get ith attribute node of the association node! Ignore the ith attribute node.\r\nINFO:INFO:parentName:" + parentName + "    parentID:" + parentID + "    i:" + temp + "\r\n\r\n"; 
			logFile.Write (resInfo, resInfo.GetLength ());
			if (result == SUCCEED) result = IGNORED;
			continue;
		}
		if (!nodeName.Compare ("xmi:id"))
		{
			pID.Format ("%S", text);
		}
		else if (!nodeName.Compare ("name"))
		{
			pname.Format ("%S", text);
		}
		else if (!nodeName.Compare ("visibility"))
		{
			pvisibility.Format ("%S", text);
		}
		else  if (temp.Compare ("xmi:type"))
		{
			//log file
			resInfo = "IGNORE:Ignore the ith attribute of the \"uml:Association\" node! Attribute type is \"" + temp + "\".\r\nINFO:parentName:" + parentName + "    parentID:" + parentID + "    i:";
			temp.Format ("%d\r\n\r\n", i);
			resInfo += temp; 
			logFile.Write (resInfo, resInfo.GetLength ());
		}
	}
	try
	{
		sql = "select * from association";									//设置查询字符串
		m_Ado.m_pRecordset = m_Ado.OpenRecordset(sql);						//打开记录集
		m_Ado.m_pRecordset->AddNew();										//添加新行
		m_Ado.m_pRecordset->PutCollect("名称", (_bstr_t)pname);				//设置名称字段内容
		m_Ado.m_pRecordset->PutCollect("ID", (_bstr_t)pID);					//设置ID字段内容
		m_Ado.m_pRecordset->PutCollect("可见性", (_bstr_t)pvisibility);		//设置备注字段内容
		m_Ado.m_pRecordset->PutCollect("所属包", (_bstr_t)parentName);		//设置所属包字段内容
		m_Ado.m_pRecordset->PutCollect("所属包ID", (_bstr_t)parentID);		//设置所属包ID字段内容
	}
	catch(_com_error e)
	{
		AfxMessageBox(e.Description());										//弹出错误处理
		//log file
		resInfo = "ERROR:Fail to put association data into database! Ignore this database write.\r\nINFO:association name:" + pname + "    association ID:" + pID + "\r\n\r\n"; 
		logFile.Write (resInfo, resInfo.GetLength ());
		if (result == SUCCEED) result = IGNORED;
	}

	//关联的参与实例分析
	hr = pNode->hasChildNodes (&b);											//判断节点是否有孩子
	if (FAILED (hr))
	{
		AfxMessageBox ("Fail to find whether the node has child!");
		//log file
		resInfo = "ERROR:Fail to find whether the node has child! Ignore child nodes of the node.\r\nINFO:association name:" + pname  + "    association ID:" + pID + "\r\n\r\n"; 
		logFile.Write (resInfo, resInfo.GetLength ());
		return IGNORED;
	}
	if (!b)											//没有子节点(即没有成员属性和方法)
	{
		try
		{
			m_Ado.m_pRecordset->Update();										//更新记录集
			m_Ado.CloseRecordset();												//关闭记录集
		}
		catch(_com_error e)
		{
			AfxMessageBox(e.Description()); //弹出错误处理
			resInfo = "ERROR:Fail to find whether the node has child! Ignore child nodes of the node.\r\nINFO:association name:" + pname  + "    association ID:" + pID + "\r\n\r\n"; 
			logFile.Write (resInfo, resInfo.GetLength ());
			return IGNORED;
		}
		return result;
	}

	hr = pNode->get_childNodes (&pNodes);			//获取子节点
	if (FAILED (hr))
	{
		AfxMessageBox ("Fail to get attributes of the node!");
		//log file
		resInfo = "ERROR:Fail to get child nodes of the association node! Ignore all child nodes of the association.\r\nINFO:association name:" + pname + "    association ID:" + pID + "\r\n\r\n"; 
		logFile.Write (resInfo, resInfo.GetLength ());
		return IGNORED;
	}
	hr = pNodes->get_length (&n);					// 获取子节点个数
	if (FAILED (hr))
	{
		AfxMessageBox ("Fail to get number of the attributes of the node!");
		//log file
		resInfo = "ERROR:Fail to get number of child nodes of the association node! Ignore all child nodes of the association.\r\nINFO:association name:" + pname + "    association ID:" + pID + "\r\n\r\n"; 
		logFile.Write (resInfo, resInfo.GetLength ());
		return IGNORED;
	}
	
	end1name = "";
	end1ID = "";
	end1role = "";
	end1visibility = "";
	end1multiplicity = "";
	end2name = "";
	end2ID = "";
	end2role = "";
	end2visibility = "";
	end2multiplicity = "";
	for (i = 0; i < n && count < 2 ; i ++)
	{
		hr = pNodes->get_item (i, &aNode);
		if (FAILED (hr))
		{
			AfxMessageBox ("Fail to get the wanted child node!");
			//log file
			temp.Format ("%d", i);
			resInfo = "ERROR:Fail to get ith child nodes of the association node! Ignore the ith child node.\r\nINFO:association name:" + pname + "    association ID:" + pID + "    i:" + temp + "\r\n\r\n"; 
			logFile.Write (resInfo, resInfo.GetLength ());
			if (result == SUCCEED) result = IGNORED;
			continue;
		}
		hr = aNode->get_nodeName (&bstr);			// 获取子节点的名称
		if (FAILED (hr))
		{
			AfxMessageBox ("Fail to get name of the wanted chile node!");
			//log file
			temp.Format ("%d", i);
			resInfo = "ERROR:Fail to get ith child nodes of the association node! Ignore the ith child node.\r\nINFO:association name:" + pname + "    association ID:" + pID + "    i:" + temp + "\r\n\r\n"; 
			logFile.Write (resInfo, resInfo.GetLength ());
			if (result == SUCCEED) result = IGNORED;
			continue;
		}
		nodeName.Format ("%S",bstr);
		text = NULL;
		hr = aNode->get_text (&text);						//获取属性节点的值
		if (FAILED (hr) || text == NULL)
		{
			AfxMessageBox ("Fail to get the value of wanted child's name!");
			//log file
			temp.Format ("%d", i);
			resInfo = "ERROR:Fail to get ith child nodes of the association node! Ignore the ith child node.\r\nINFO:association name:" + pname + "    association ID:" + pID + "    i:" + temp + "\r\n\r\n"; 
			logFile.Write (resInfo, resInfo.GetLength ());
			if (result == SUCCEED) result = IGNORED;
			continue;
		}
		if (!nodeName.Compare ("memberEnd"))			//关联实例分析
		{
			count ++;
			hr = aNode->get_attributes (&pAtts);
			if (FAILED (hr))
			{
				AfxMessageBox ("Fail to get attributes of the node!");
				//log file
				temp.Format ("%d", i);
				resInfo = "ERROR:Fail to get attributes of the association end node! Ignore all attributes of the node.\r\nINFO:association name:" + pname + "    association ID:" + pID + "    i:" + temp + "\r\n\r\n"; 
				logFile.Write (resInfo, resInfo.GetLength ());
				return IGNORED;
			}
			hr = pAtts->getNamedItem(L"xmi:idref",& bNode);
			if (FAILED (hr))
			{
				AfxMessageBox ("Failed to get wanted attribute of the node.");
				//logfile
				resInfo = "ERROR:Fail to get \"xmi:idref\" of the node! Ignore all attributes of the node.\r\nINFO:association name:" + pname + "    association ID:" + pID + "\r\n\r\n"; 
				logFile.Write (resInfo, resInfo.GetLength ());
				return IGNORED;
			}
			hr = bNode->get_text(&text);
			if (text != NULL)
			{
				endID.Format ("%S", text);
			}
			
			isFound = FALSE;
			//isFound = FindInAssociation (pNodes, endNode, endID);
			hr = pNodes->get_length (&m);								// 获取子节点个数
			if (FAILED (hr))
			{
				AfxMessageBox ("Fail to get number of the attributes of the node!");
				//log file
				temp.Format ("%d", i);
				resInfo = "ERROR:Fail to get the ith association end iformation! Abort this association analyse.\r\nINFO:association name:" + pname + "    association ID:" + pID + "    i:" + temp + "\r\n\r\n"; 
				logFile.Write (resInfo, resInfo.GetLength ());
				return IGNORED;
			}
			for (j = 0; j < m; j ++)
			{
				hr = pNodes->get_item (j, &bNode);
				if (FAILED (hr))
				{
					AfxMessageBox ("Fail to get the wanted child node!");
					//log file
					temp.Format ("%d", i);
					resInfo = "ERROR:Fail to get the ith association end iformation! Abort this association analyse.\r\nINFO:association name:" + pname + "    association ID:" + pID + "    i:" + temp + "\r\n\r\n"; 
					logFile.Write (resInfo, resInfo.GetLength ());
					return IGNORED;
				}
				hr = bNode->get_nodeName (&bstr);			// 获取子节点的名称
				if (FAILED (hr))
				{
					AfxMessageBox ("Fail to get name of the wanted chile node!");
					//log file
					temp.Format ("%d", i);
					resInfo = "ERROR:Fail to get the ith association end iformation! Abort this association analyse.\r\nINFO:association name:" + pname + "    association ID:" + pID + "    i:" + temp + "\r\n\r\n"; 
					logFile.Write (resInfo, resInfo.GetLength ());
					return IGNORED;
				}
				nodeName.Format ("%S",bstr);
				text = NULL;
				hr = bNode->get_text (&text);						//获取属性节点的值
				if (FAILED (hr) || text == NULL)
				{
					AfxMessageBox ("Fail to get the value of wanted child's name!");
					//log file
					temp.Format ("%d", i);
					resInfo = "ERROR:Fail to get the ith association end iformation! Abort this association analyse.\r\nINFO:association name:" + pname + "    association ID:" + pID + "    i:" + temp + "\r\n\r\n"; 
					logFile.Write (resInfo, resInfo.GetLength ());
					return IGNORED;
				}
				if (!nodeName.Compare ("ownedEnd"))			//关联实例分析
				{
					hr = bNode->get_attributes (&qAtts);
					if (FAILED (hr))
					{
						AfxMessageBox ("Fail to get attributes of the node!");
						//log file
						temp.Format ("%d", i);
						resInfo = "ERROR:Fail to get the ith association end iformation! Abort this association analyse.\r\nINFO:association name:" + pname + "    association ID:" + pID + "    i:" + temp + "\r\n\r\n"; 
						logFile.Write (resInfo, resInfo.GetLength ());
						return IGNORED;
					}
					hr = qAtts->getNamedItem(L"xmi:type",& cNode);
					if (FAILED (hr))
					{
						AfxMessageBox ("Failed to get wanted attribute of the node.");
						//logfile
						temp.Format ("%d", i);
						resInfo = "ERROR:Fail to get the ith association end iformation! Abort this association analyse.\r\nINFO:association name:" + pname + "    association ID:" + pID + "    i:" + temp + "\r\n\r\n"; 
						logFile.Write (resInfo, resInfo.GetLength ());
						return IGNORED;
					}
					hr = cNode->get_text(&text);
					if (FAILED (hr) || text == NULL)
					{
						AfxMessageBox ("Failed to get value of wanted attribute.");
						//logfile
						temp.Format ("%d", i);
						resInfo = "ERROR:Fail to get the ith association end iformation! Abort this association analyse.\r\nINFO:association name:" + pname + "    association ID:" + pID + "    i:" + temp + "\r\n\r\n"; 
						logFile.Write (resInfo, resInfo.GetLength ());
						return IGNORED;	
					}
					temp.Format ("%S", text);
					if (temp.Compare ("uml:Property"))
						return IGNORED;
					hr = qAtts->getNamedItem(L"xmi:id",& cNode);
					if (FAILED (hr))
					{
						AfxMessageBox ("Failed to get wanted attribute of the node.");
						//logfile
						temp.Format ("%d", i);
						resInfo = "ERROR:Fail to get the ith association end iformation! Abort this association analyse.\r\nINFO:association name:" + pname + "    association ID:" + pID + "    i:" + temp + "\r\n\r\n"; 
						logFile.Write (resInfo, resInfo.GetLength ());
						return IGNORED;
					}
					hr = cNode->get_text(&text);
					if (FAILED (hr) || text == NULL)
					{
						AfxMessageBox ("Failed to get value of wanted attribute.");
						//logfile
						temp.Format ("%d", i);
						resInfo = "ERROR:Fail to get the ith association end iformation! Abort this association analyse.\r\nINFO:association name:" + pname + "    association ID:" + pID + "    i:" + temp + "\r\n\r\n"; 
						logFile.Write (resInfo, resInfo.GetLength ());
						return IGNORED;
					}
					temp.Format ("%S", text);
					if (!temp.Compare (endID))
					{
						endNode = bNode;
						isFound = TRUE;
						break;
					}
				}
			}




			if (isFound)					//在关联内部
			{
				hr = endNode->get_attributes (&qAtts);
				if (FAILED (hr))
				{
					AfxMessageBox ("Fail to get attributes of the node!");
					//log file
					temp.Format ("%d", i);
					resInfo = "ERROR:Fail to get the ith association end iformation! Abort this association analyse.\r\nINFO:association name:" + pname + "    association ID:" + pID + "    i:" + temp + "\r\n\r\n"; 
					logFile.Write (resInfo, resInfo.GetLength ());
					return IGNORED;
				}
				hr = qAtts->get_length (&m);					// 获取属性节点个数
				if (FAILED (hr))
				{
					AfxMessageBox ("Fail to get number of the attributes of the node!");
					//log file
					temp.Format ("%d", i);
					resInfo = "ERROR:Fail to get the ith association end iformation! Abort this association analyse.\r\nINFO:association name:" + pname + "    association ID:" + pID + "    i:" + temp + "\r\n\r\n"; 
					logFile.Write (resInfo, resInfo.GetLength ());
					return IGNORED;
				}
				for (j = 0; j < m; j ++)
				{
					hr = qAtts->get_item (j, &cNode);
					if (FAILED (hr))
					{
						AfxMessageBox ("Fail to get the wanted attribute of the node!");
						//log file
						temp.Format ("%d", i);
						resInfo = "ERROR:Fail to get the ith association end iformation! Abort this association analyse.\r\nINFO:association name:" + pname + "    association ID:" + pID + "    i:" + temp + "\r\n\r\n"; 
						logFile.Write (resInfo, resInfo.GetLength ());
						return IGNORED;
					}
					hr = cNode->get_nodeName (&bstr);			// 获取属性节点的名称
					if (FAILED (hr))
					{
						AfxMessageBox ("Fail to get name of the wanted attribute!");
						//log file
						temp.Format ("%d", i);
						resInfo = "ERROR:Fail to get the ith association end iformation! Abort this association analyse.\r\nINFO:association name:" + pname + "    association ID:" + pID + "    i:" + temp + "\r\n\r\n"; 
						logFile.Write (resInfo, resInfo.GetLength ());
						return IGNORED;
					}
					nodeName.Format ("%S",bstr);
					text = NULL;
					hr = cNode->get_text (&text);				//获取属性节点的值
					if (FAILED (hr) || text == NULL)
					{
						AfxMessageBox ("Fail to get the value of wanted attribute's name!");
						//log file
						temp.Format ("%d", i);
						resInfo = "ERROR:Fail to get the ith association end iformation! Abort this association analyse.\r\nINFO:association name:" + pname + "    association ID:" + pID + "    i:" + temp + "\r\n\r\n"; 
						logFile.Write (resInfo, resInfo.GetLength ());
						return IGNORED;
					}
					if (count == 1)
					{
						if (!nodeName.Compare ("xmi:id"))
						{
							end1.Format ("%S", text);
						}
						else if (!nodeName.Compare ("name"))
						{
							end1role.Format ("%S", text);
						}
						else if (!nodeName.Compare ("visibility"))
						{
							end1visibility.Format ("%S", text);
						}
						else if (!nodeName.Compare ("aggregation"))
						{
							if (!paggregation.Compare ("") || !paggregation.Compare ("none"))
							{
								paggregation.Format ("%S", text);
								//AfxMessageBox ("11111111111111"+paggregation+"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
								if (paggregation.Compare (""))
									pdirection.Format("%d", count);
							}
						}
						else
						{
						}
					}
					else
					{
						if (!nodeName.Compare ("xmi:id"))
						{
							end2.Format ("%S", text);
						}
						else if (!nodeName.Compare ("name"))
						{
							end2role.Format ("%S", text);
						}
						else if (!nodeName.Compare ("visibility"))
						{
							end2visibility.Format ("%S", text);
						}
						else if (!nodeName.Compare ("aggregation"))
						{
							if (!paggregation.Compare ("") || !paggregation.Compare ("none"))
							{
								paggregation.Format ("%S", text);
								//AfxMessageBox ("2222222222222222222211111111111111"+paggregation+"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
								if (paggregation.Compare (""))
									pdirection.Format("%d", count);
							}
						}
						else
						{
						}
					}
				}
				//type,lowervalue,uppervalue
				hr = endNode->hasChildNodes (&b);											//判断节点是否有孩子
				if (FAILED (hr))
				{
					AfxMessageBox ("Fail to find whether the node has child!");
					//log file
					temp.Format ("%d", i);
					resInfo = "ERROR:Fail to get the ith association end iformation! Abort this association analyse.\r\nINFO:association name:" + pname + "    association ID:" + pID + "    i:" + temp + "\r\n\r\n"; 
					logFile.Write (resInfo, resInfo.GetLength ());
					return IGNORED;
				}
				if (b)											//没有子节点(即没有成员属性和方法)
				{
					hr = endNode->get_childNodes (&qNodes);			//获取子节点
					if (FAILED (hr))
					{
						AfxMessageBox ("Fail to get attributes of the node!");
						//log file
						temp.Format ("%d", i);
						resInfo = "ERROR:Fail to get the ith association end iformation! Abort this association analyse.\r\nINFO:association name:" + pname + "    association ID:" + pID + "    i:" + temp + "\r\n\r\n"; 
						logFile.Write (resInfo, resInfo.GetLength ());
						return IGNORED;
					}
					hr = qNodes->get_length (&m);					// 获取子节点个数
					if (FAILED (hr))
					{
						AfxMessageBox ("Fail to get number of the attributes of the node!");
						//log file
						temp.Format ("%d", i);
						resInfo = "ERROR:Fail to get the ith association end iformation! Abort this association analyse.\r\nINFO:association name:" + pname + "    association ID:" + pID + "    i:" + temp + "\r\n\r\n"; 
						logFile.Write (resInfo, resInfo.GetLength ());
						return IGNORED;
					}
					lowerValue = "";
					upperValue = "";
					for (j = 0; j < m; j ++)
					{
						hr = qNodes->get_item (j, &bNode);
						if (FAILED (hr))
						{
							AfxMessageBox ("Fail to get the wanted child node!");
							//log file
							temp.Format ("%d", i);
							resInfo = "ERROR:Fail to get the ith association end iformation! Abort this association analyse.\r\nINFO:association name:" + pname + "    association ID:" + pID + "    i:" + temp + "\r\n\r\n"; 
							logFile.Write (resInfo, resInfo.GetLength ());
							return IGNORED;
						}
						hr = bNode->get_nodeName (&bstr);			// 获取子节点的名称
						if (FAILED (hr))
						{
							AfxMessageBox ("Fail to get name of the wanted chile node!");
							//log file
							temp.Format ("%d", i);
							resInfo = "ERROR:Fail to get the ith association end iformation! Abort this association analyse.\r\nINFO:association name:" + pname + "    association ID:" + pID + "    i:" + temp + "\r\n\r\n"; 
							logFile.Write (resInfo, resInfo.GetLength ());
							return IGNORED;
						}
						nodeName.Format ("%S",bstr);
						text = NULL;
						hr = bNode->get_text (&text);						//获取属性节点的值
						if (FAILED (hr) || text == NULL)
						{
							AfxMessageBox ("Fail to get the value of wanted child's name!");
							//log file
							temp.Format ("%d", i);
							resInfo = "ERROR:Fail to get the ith association end iformation! Abort this association analyse.\r\nINFO:association name:" + pname + "    association ID:" + pID + "    i:" + temp + "\r\n\r\n"; 
							logFile.Write (resInfo, resInfo.GetLength ());
							return IGNORED;
						}
						if (!nodeName.Compare ("type"))			//成员属性类型分析
						{
							hr = bNode->get_attributes (&pAtts);
							if (FAILED (hr))
							{
								AfxMessageBox ("Fail to get attributes of the node!");
								//log file
								temp.Format ("%d", i);
								resInfo = "ERROR:Fail to get the ith association end iformation! Abort this association analyse.\r\nINFO:association name:" + pname + "    association ID:" + pID + "    i:" + temp + "\r\n\r\n"; 
								logFile.Write (resInfo, resInfo.GetLength ());
								return IGNORED;
							}
							hr = pAtts->getNamedItem(L"xmi:idref",& cNode);
							if (FAILED (hr))
							{
								AfxMessageBox ("Fail to get type of the attributes of the class!");
								//log file
								temp.Format ("%d", i);
								resInfo = "ERROR:Fail to get the ith association end iformation! Abort this association analyse.\r\nINFO:association name:" + pname + "    association ID:" + pID + "    i:" + temp + "\r\n\r\n"; 
								logFile.Write (resInfo, resInfo.GetLength ());
								return IGNORED;
							}
							hr = cNode->get_text(&text);
							if (count == 1)
							{
								end1ID.Format ("%S",text);
								if (! FindClassThroughAssociation (end1ID, end1name))
								{
									end1name = "";
								}
							}
							else
							{
								end2ID.Format ("%S",text);
								if (! FindClassThroughAssociation (end2ID, end2name))
								{
									end2name = "";
								}
							}
						}
						else if (!nodeName.Compare ("lowerValue"))
						{
							hr = bNode->get_attributes (&pAtts);
							if (FAILED (hr))
							{
								AfxMessageBox ("Fail to get attributes of the node!");
								//log file
								temp.Format ("%d", i);
								resInfo = "ERROR:Fail to get the ith association end iformation! Abort this association analyse.\r\nINFO:association name:" + pname + "    association ID:" + pID + "    i:" + temp + "\r\n\r\n"; 
								logFile.Write (resInfo, resInfo.GetLength ());
								return IGNORED;
							}
							hr = pAtts->getNamedItem(L"xmi:type",& cNode);
							if (FAILED (hr))
							{
								AfxMessageBox ("Fail to get type of the attributes of the class!");
								//log file
								temp.Format ("%d", i);
								resInfo = "ERROR:Fail to get the ith association end iformation! Abort this association analyse.\r\nINFO:association name:" + pname + "    association ID:" + pID + "    i:" + temp + "\r\n\r\n"; 
								logFile.Write (resInfo, resInfo.GetLength ());
								return IGNORED;
							}
							hr = cNode->get_text(&text);
							valueType.Format ("%S",text);
							hr = pAtts->getNamedItem(L"value",& cNode);
							if (FAILED (hr))
							{
								AfxMessageBox ("Fail to get type of the attributes of the class!");
								//log file
								temp.Format ("%d", i);
								resInfo = "ERROR:Fail to get the ith association end iformation! Abort this association analyse.\r\nINFO:association name:" + pname + "    association ID:" + pID + "    i:" + temp + "\r\n\r\n"; 
								logFile.Write (resInfo, resInfo.GetLength ());
								return IGNORED;
							}
							hr = cNode->get_text(&text);
							value.Format ("%S",text);
							if (!valueType.Compare ("uml:LiteralUnlimitedNatural") && !value.Compare ("-1"))
								lowerValue = "*";
							else if (!valueType.Compare ("uml:LiteralUnlimitedNatural") || !valueType.Compare ("uml:LiteralInteger"))
								lowerValue = value;
							else
							{
							}
						}
						else if (!nodeName.Compare ("upperValue"))
						{
							hr = bNode->get_attributes (&pAtts);
							if (FAILED (hr))
							{
								AfxMessageBox ("Fail to get attributes of the node!");
								//log file
								temp.Format ("%d", i);
								resInfo = "ERROR:Fail to get the ith association end iformation! Abort this association analyse.\r\nINFO:association name:" + pname + "    association ID:" + pID + "    i:" + temp + "\r\n\r\n"; 
								logFile.Write (resInfo, resInfo.GetLength ());
								return IGNORED;
							}
							hr = pAtts->getNamedItem(L"xmi:type",& cNode);
							if (FAILED (hr))
							{
								AfxMessageBox ("Fail to get type of the attributes of the class!");
								//log file
								temp.Format ("%d", i);
								resInfo = "ERROR:Fail to get the ith association end iformation! Abort this association analyse.\r\nINFO:association name:" + pname + "    association ID:" + pID + "    i:" + temp + "\r\n\r\n"; 
								logFile.Write (resInfo, resInfo.GetLength ());
								return IGNORED;
							}
							hr = cNode->get_text(&text);
							valueType.Format ("%S",text);
							hr = pAtts->getNamedItem(L"value",& cNode);
							if (FAILED (hr))
							{
								AfxMessageBox ("Fail to get type of the attributes of the class!");
								//log file
								temp.Format ("%d", i);
								resInfo = "ERROR:Fail to get the ith association end iformation! Abort this association analyse.\r\nINFO:association name:" + pname + "    association ID:" + pID + "    i:" + temp + "\r\n\r\n"; 
								logFile.Write (resInfo, resInfo.GetLength ());
								return IGNORED;
							}
							hr = cNode->get_text(&text);
							value.Format ("%S",text);
							if (!valueType.Compare ("uml:LiteralUnlimitedNatural") && !value.Compare ("-1"))
								upperValue = "*";
							else if (!valueType.Compare ("uml:LiteralUnlimitedNatural") || !valueType.Compare ("uml:LiteralInteger"))
								upperValue = value;
							else
							{
							}
						}
						else
						{
						}
					}
					if (count == 1)
					{
						if (!lowerValue.Compare (upperValue))
								end1multiplicity = lowerValue;
						else
							end1multiplicity = lowerValue + ".." + upperValue;
					}
					else
					{
						if (!lowerValue.Compare (upperValue))
								end2multiplicity = lowerValue;
						else
							end2multiplicity = lowerValue + ".." + upperValue;
					}
				}
			}
			else
			{
				//isFound = FindInClass (endNode, endPNode, endID);		//直接关联类

				hr = pXMLDoc->selectNodes(L"//packagedElement", &qNodes);
				if (FAILED (hr))
				{
					AfxMessageBox ("Fail to start finding parent class!");
					//log file
					temp.Format ("%d", i);
					resInfo = "ERROR:Fail to get the ith association end iformation! Abort this association analyse.\r\nINFO:association name:" + pname + "    association ID:" + pID + "    i:" + temp + "\r\n\r\n"; 
					logFile.Write (resInfo, resInfo.GetLength ());
					return IGNORED;
				}
				hr = qNodes->get_length (&m);//获得该节点对象集合的长度（即节点个数）
				if (FAILED (hr))
				{
					AfxMessageBox ("Failure occurs in the progress of finding parent class!");
					//log file
					temp.Format ("%d", i);
					resInfo = "ERROR:Fail to get the ith association end iformation! Abort this association analyse.\r\nINFO:association name:" + pname + "    association ID:" + pID + "    i:" + temp + "\r\n\r\n"; 
					logFile.Write (resInfo, resInfo.GetLength ());
					return IGNORED;
				}
				for (j = 0; j < m && ! isFound; j ++)
				{
					hr = qNodes->get_item (j, &classNode);//获取该节点对象集合中指定位置的节点
					if (FAILED (hr))
					{
						AfxMessageBox ("Fail to get wanted item!");
						//log file
						temp.Format ("%d", i);
						resInfo = "ERROR:Fail to get the ith association end iformation! Abort this association analyse.\r\nINFO:association name:" + pname + "    association ID:" + pID + "    i:" + temp + "\r\n\r\n"; 
						logFile.Write (resInfo, resInfo.GetLength ());
						return IGNORED;
					}
					hr = classNode->get_attributes (&qAtts);
					if (FAILED (hr))
					{
						AfxMessageBox ("Fail to get attributes of wanted item!");
						//log file
						temp.Format ("%d", i);
						resInfo = "ERROR:Fail to get the ith association end iformation! Abort this association analyse.\r\nINFO:association name:" + pname + "    association ID:" + pID + "    i:" + temp + "\r\n\r\n"; 
						logFile.Write (resInfo, resInfo.GetLength ());
						return IGNORED;
					}
					hr = qAtts->getNamedItem(L"xmi:type",& attributeNode);
					if (FAILED (hr))
					{
						AfxMessageBox ("Fail to get type of wanted item!");
						//log file
						temp.Format ("%d", i);
						resInfo = "ERROR:Fail to get the ith association end iformation! Abort this association analyse.\r\nINFO:association name:" + pname + "    association ID:" + pID + "    i:" + temp + "\r\n\r\n"; 
						logFile.Write (resInfo, resInfo.GetLength ());
						return IGNORED;
					}
					hr = attributeNode->get_text(&text);
					if (FAILED (hr))
					{
						AfxMessageBox ("Fail to get ID information of wanted item!");
						//log file
						temp.Format ("%d", i);
						resInfo = "ERROR:Fail to get the ith association end iformation! Abort this association analyse.\r\nINFO:association name:" + pname + "    association ID:" + pID + "    i:" + temp + "\r\n\r\n"; 
						logFile.Write (resInfo, resInfo.GetLength ());
						return IGNORED;
					}
					temp.Format ("%S",text);
					if (!temp.Compare ("uml:Class"))
					{
						hr = classNode->hasChildNodes (&b);											//判断节点是否有孩子
						if (FAILED (hr))
						{
							AfxMessageBox ("Fail to find whether the node has child!");
							//log file
							temp.Format ("%d", i);
							resInfo = "ERROR:Fail to get the ith association end iformation! Abort this association analyse.\r\nINFO:association name:" + pname + "    association ID:" + pID + "    i:" + temp + "\r\n\r\n"; 
							logFile.Write (resInfo, resInfo.GetLength ());
							return IGNORED;
						}
						if (!b)											//没有子节点
							return IGNORED;

						hr = classNode->get_childNodes (&rNodes);			//获取子节点
						if (FAILED (hr))
						{
							AfxMessageBox ("Fail to get attributes of the node!");
							//log file
							temp.Format ("%d", i);
							resInfo = "ERROR:Fail to get the ith association end iformation! Abort this association analyse.\r\nINFO:association name:" + pname + "    association ID:" + pID + "    i:" + temp + "\r\n\r\n"; 
							logFile.Write (resInfo, resInfo.GetLength ());
							return IGNORED;
						}
						hr = rNodes->get_length (&n1);					// 获取子节点个数
						if (FAILED (hr))
						{
							AfxMessageBox ("Fail to get number of the attributes of the node!");
							//log file
							temp.Format ("%d", i);
							resInfo = "ERROR:Fail to get the ith association end iformation! Abort this association analyse.\r\nINFO:association name:" + pname + "    association ID:" + pID + "    i:" + temp + "\r\n\r\n"; 
							logFile.Write (resInfo, resInfo.GetLength ());
							return IGNORED;
						}
						for (i1 = 0; i1 < n1 && ! isFound; i1 ++)
						{

							hr = rNodes->get_item (i1, &propertyNode);//获取该节点对象集合中指定位置的节点
							if (FAILED (hr))
							{
								AfxMessageBox ("Fail to get the wanted child node!");
								//log file
								temp.Format ("%d", i);
								resInfo = "ERROR:Fail to get the ith association end iformation! Abort this association analyse.\r\nINFO:association name:" + pname + "    association ID:" + pID + "    i:" + temp + "\r\n\r\n"; 
								logFile.Write (resInfo, resInfo.GetLength ());
								return IGNORED;
							}
							hr = propertyNode->get_nodeName (&bstr);			// 获取子节点的名称
							if (FAILED (hr))
							{
								AfxMessageBox ("Fail to get name of the wanted chile node!");
								//log file
								temp.Format ("%d", i);
								resInfo = "ERROR:Fail to get the ith association end iformation! Abort this association analyse.\r\nINFO:association name:" + pname + "    association ID:" + pID + "    i:" + temp + "\r\n\r\n"; 
								logFile.Write (resInfo, resInfo.GetLength ());
								return IGNORED;
							}
							nodeName.Format ("%S",bstr);
							text = NULL;
							hr = propertyNode->get_text (&text);						//获取属性节点的值
							if (FAILED (hr) || text == NULL)
							{
								AfxMessageBox ("Fail to get the value of wanted child's name!");
								//log file
								temp.Format ("%d", i);
								resInfo = "ERROR:Fail to get the ith association end iformation! Abort this association analyse.\r\nINFO:association name:" + pname + "    association ID:" + pID + "    i:" + temp + "\r\n\r\n"; 
								logFile.Write (resInfo, resInfo.GetLength ());
								return IGNORED;
							}
							if (!nodeName.Compare ("ownedAttribute"))			//成员属性类型分析
							{
								hr = propertyNode->get_attributes (&propertyAtts);
								if (FAILED (hr))
								{
									AfxMessageBox ("Fail to get attributes of wanted item!");
									//log file
									temp.Format ("%d", i);
									resInfo = "ERROR:Fail to get the ith association end iformation! Abort this association analyse.\r\nINFO:association name:" + pname + "    association ID:" + pID + "    i:" + temp + "\r\n\r\n"; 
									logFile.Write (resInfo, resInfo.GetLength ());
									return IGNORED;
								}
								hr = propertyAtts->get_length (&l);					// 获取属性节点个数
								if (FAILED (hr))
								{
									AfxMessageBox ("Fail to get number of the attributes of the node!");
									//log file
									temp.Format ("%d", i);
									resInfo = "ERROR:Fail to get the ith association end iformation! Abort this association analyse.\r\nINFO:association name:" + pname + "    association ID:" + pID + "    i:" + temp + "\r\n\r\n"; 
									logFile.Write (resInfo, resInfo.GetLength ());
									return IGNORED;
								}
								for (k = 0; k < l && ! isFound; k ++)
								{
									hr = propertyAtts->get_item (k, &attributeNode);//获取该节点对象集合中指定位置的节点
									if (FAILED (hr))
									{
										AfxMessageBox ("Fail to get the wanted attribute of the node!");
										//log file
										temp.Format ("%d", i);
										resInfo = "ERROR:Fail to get the ith association end iformation! Abort this association analyse.\r\nINFO:association name:" + pname + "    association ID:" + pID + "    i:" + temp + "\r\n\r\n"; 
										logFile.Write (resInfo, resInfo.GetLength ());
										return IGNORED;
									}
									hr = attributeNode->get_nodeName (&bstr);			// 获取属性节点的名称
									if (FAILED (hr))
									{
										AfxMessageBox ("Fail to get name of the wanted attribute!");
										//log file
										temp.Format ("%d", i);
										resInfo = "ERROR:Fail to get the ith association end iformation! Abort this association analyse.\r\nINFO:association name:" + pname + "    association ID:" + pID + "    i:" + temp + "\r\n\r\n"; 
										logFile.Write (resInfo, resInfo.GetLength ());
										return IGNORED;
									}
									nodeName.Format ("%S",bstr);
									text = NULL;
									hr = attributeNode->get_text (&text);				//获取属性节点的值
									if (FAILED (hr) || text == NULL)
									{
										AfxMessageBox ("Fail to get the value of wanted attribute's name!");
										//log file
										temp.Format ("%d", i);
										resInfo = "ERROR:Fail to get the ith association end iformation! Abort this association analyse.\r\nINFO:association name:" + pname + "    association ID:" + pID + "    i:" + temp + "\r\n\r\n"; 
										logFile.Write (resInfo, resInfo.GetLength ());
										return IGNORED;
									}
									if (!nodeName.Compare ("xmi:id"))
									{
										temp.Format ("%S", text);
										if (! temp.Compare (endID))
										{
											isFound = TRUE;
											endNode = classNode;
											endPNode = propertyNode;
											break;
										}
										else
											break;
									}
								}
							}
						}
					}
				}



				if (count == 1) end1 = endID;
				else end2 = endID;
				if (isFound)
				{
					hr = endPNode->get_attributes (&qAtts);
					if (FAILED (hr))
					{
						AfxMessageBox ("Fail to get attributes of the node!");
						//log file
						temp.Format ("%d", i);
						resInfo = "ERROR:Fail to get the ith association end iformation! Abort this association analyse.\r\nINFO:association name:" + pname + "    association ID:" + pID + "    i:" + temp + "\r\n\r\n"; 
						logFile.Write (resInfo, resInfo.GetLength ());
						return IGNORED;
					}
					hr = qAtts->get_length (&m);					// 获取属性节点个数
					if (FAILED (hr))
					{
						AfxMessageBox ("Fail to get number of the attributes of the node!");
						//log file
						temp.Format ("%d", i);
						resInfo = "ERROR:Fail to get the ith association end iformation! Abort this association analyse.\r\nINFO:association name:" + pname + "    association ID:" + pID + "    i:" + temp + "\r\n\r\n"; 
						logFile.Write (resInfo, resInfo.GetLength ());
						return IGNORED;
					}
					for (j = 0; j < m; j ++)
					{
						hr = qAtts->get_item (j, &cNode);//获取该节点对象集合中指定位置的节点
						if (FAILED (hr))
						{
							AfxMessageBox ("Fail to get the wanted attribute of the node!");
							//log file
							temp.Format ("%d", i);
							resInfo = "ERROR:Fail to get the ith association end iformation! Abort this association analyse.\r\nINFO:association name:" + pname + "    association ID:" + pID + "    i:" + temp + "\r\n\r\n"; 
							logFile.Write (resInfo, resInfo.GetLength ());
							return IGNORED;
						}
						hr = cNode->get_nodeName (&bstr);			// 获取属性节点的名称
						if (FAILED (hr))
						{
							AfxMessageBox ("Fail to get name of the wanted attribute!");
							//log file
							temp.Format ("%d", i);
							resInfo = "ERROR:Fail to get the ith association end iformation! Abort this association analyse.\r\nINFO:association name:" + pname + "    association ID:" + pID + "    i:" + temp + "\r\n\r\n"; 
							logFile.Write (resInfo, resInfo.GetLength ());
							return IGNORED;
						}
						nodeName.Format ("%S",bstr);
						text = NULL;
						hr = cNode->get_text (&text);				//获取属性节点的值
						if (FAILED (hr) || text == NULL)
						{
							AfxMessageBox ("Fail to get the value of wanted attribute's name!");
							//log file
							temp.Format ("%d", i);
							resInfo = "ERROR:Fail to get the ith association end iformation! Abort this association analyse.\r\nINFO:association name:" + pname + "    association ID:" + pID + "    i:" + temp + "\r\n\r\n"; 
							logFile.Write (resInfo, resInfo.GetLength ());
							return IGNORED;
						}
						if (count == 1)
						{
							if (!nodeName.Compare ("name"))
							{
								end1role.Format ("%S", text);
							}
							else if (!nodeName.Compare ("visibility"))
							{
								end1visibility.Format ("%S", text);
							}
							else if (!nodeName.Compare ("aggregation"))
							{
								if (!paggregation.Compare ("") || !paggregation.Compare ("none"))
								{
									paggregation.Format ("%S", text);
									//AfxMessageBox ("33333333333333333333222222222222222211111111111111"+paggregation+"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
									
									if (paggregation.Compare (""))
										pdirection.Format("%d", count + 1);
								}
							}
							else
							{
							}
						}
						else
						{
							if (!nodeName.Compare ("name"))
							{
								end2role.Format ("%S", text);
							}
							else if (!nodeName.Compare ("visibility"))
							{
								end2visibility.Format ("%S", text);
							}
							else if (!nodeName.Compare ("aggregation"))
							{
								if (!paggregation.Compare ("") || !paggregation.Compare ("none"))
								{
									paggregation.Format ("%S", text);
									//AfxMessageBox ("4444444444444444444444444333333333333333311111111111"+paggregation+"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
									
									if (paggregation.Compare (""))
										pdirection.Format("%d", count + 1);
								}
							}
							else
							{
							}
						}
					}

					//type,lowervalue,uppervalue
					hr = endPNode->hasChildNodes (&b);											//判断节点是否有孩子
					if (FAILED (hr))
					{
						AfxMessageBox ("Fail to find whether the node has child!");
						//log file
						temp.Format ("%d", i);
						resInfo = "ERROR:Fail to get the ith association end iformation! Abort this association analyse.\r\nINFO:association name:" + pname + "    association ID:" + pID + "    i:" + temp + "\r\n\r\n"; 
						logFile.Write (resInfo, resInfo.GetLength ());
						return IGNORED;
					}
					if (b)											//没有子节点(即没有成员属性和方法)
					{
						hr = endPNode->get_childNodes (&qNodes);			//获取子节点
						if (FAILED (hr))
						{
							AfxMessageBox ("Fail to get attributes of the node!");
							//log file
							temp.Format ("%d", i);
							resInfo = "ERROR:Fail to get the ith association end iformation! Abort this association analyse.\r\nINFO:association name:" + pname + "    association ID:" + pID + "    i:" + temp + "\r\n\r\n"; 
							logFile.Write (resInfo, resInfo.GetLength ());
							return IGNORED;
						}
						hr = qNodes->get_length (&m);					// 获取子节点个数
						if (FAILED (hr))
						{
							AfxMessageBox ("Fail to get number of the attributes of the node!");
							//log file
							temp.Format ("%d", i);
							resInfo = "ERROR:Fail to get the ith association end iformation! Abort this association analyse.\r\nINFO:association name:" + pname + "    association ID:" + pID + "    i:" + temp + "\r\n\r\n"; 
							logFile.Write (resInfo, resInfo.GetLength ());
							return IGNORED;
						}
						lowerValue = "";
						upperValue = "";
						for (j = 0; j < m; j ++)
						{
							hr = qNodes->get_item (j, &bNode);//获取该节点对象集合中指定位置的节点
							if (FAILED (hr))
							{
								AfxMessageBox ("Fail to get the wanted child node!");
								//log file
								temp.Format ("%d", i);
								resInfo = "ERROR:Fail to get the ith association end iformation! Abort this association analyse.\r\nINFO:association name:" + pname + "    association ID:" + pID + "    i:" + temp + "\r\n\r\n"; 
								logFile.Write (resInfo, resInfo.GetLength ());
								return IGNORED;
							}
							hr = bNode->get_nodeName (&bstr);			// 获取子节点的名称
							if (FAILED (hr))
							{
								AfxMessageBox ("Fail to get name of the wanted chile node!");
								//log file
								temp.Format ("%d", i);
								resInfo = "ERROR:Fail to get the ith association end iformation! Abort this association analyse.\r\nINFO:association name:" + pname + "    association ID:" + pID + "    i:" + temp + "\r\n\r\n"; 
								logFile.Write (resInfo, resInfo.GetLength ());
								return IGNORED;
							}
							nodeName.Format ("%S",bstr);
							text = NULL;
							hr = bNode->get_text (&text);						//获取属性节点的值
							if (FAILED (hr) || text == NULL)
							{
								AfxMessageBox ("Fail to get the value of wanted child's name!");
								//log file
								temp.Format ("%d", i);
								resInfo = "ERROR:Fail to get the ith association end iformation! Abort this association analyse.\r\nINFO:association name:" + pname + "    association ID:" + pID + "    i:" + temp + "\r\n\r\n"; 
								logFile.Write (resInfo, resInfo.GetLength ());
								return IGNORED;
							}
							if (!nodeName.Compare ("type"))
							{
								hr = bNode->get_attributes (&pAtts);
								if (FAILED (hr))
								{
									AfxMessageBox ("Fail to get attributes of the node!");
									//log file
									temp.Format ("%d", i);
									resInfo = "ERROR:Fail to get the ith association end iformation! Abort this association analyse.\r\nINFO:association name:" + pname + "    association ID:" + pID + "    i:" + temp + "\r\n\r\n"; 
									logFile.Write (resInfo, resInfo.GetLength ());
									return IGNORED;
								}
								hr = pAtts->getNamedItem(L"xmi:idref",& cNode);
								if (FAILED (hr))
								{
									AfxMessageBox ("Fail to get type of the attributes of the class!");
									//log file
									temp.Format ("%d", i);
									resInfo = "ERROR:Fail to get the ith association end iformation! Abort this association analyse.\r\nINFO:association name:" + pname + "    association ID:" + pID + "    i:" + temp + "\r\n\r\n"; 
									logFile.Write (resInfo, resInfo.GetLength ());
									return IGNORED;
								}
								hr = cNode->get_text(&text);
								if (count == 1)
								{
									end1ID.Format ("%S",text);
									if (! FindClassThroughAssociation (end1ID, end1name))
									{
										end1name = "";
									}
								}
								else
								{
									end2ID.Format ("%S",text);
									if (! FindClassThroughAssociation (end2ID, end2name))
									{
										end2name = "";
									}
								}		
							}
							else if (!nodeName.Compare ("lowerValue"))
							{
								hr = bNode->get_attributes (&pAtts);
								if (FAILED (hr))
								{
									AfxMessageBox ("Fail to get attributes of the node!");
									//log file
									temp.Format ("%d", i);
									resInfo = "ERROR:Fail to get the ith association end iformation! Abort this association analyse.\r\nINFO:association name:" + pname + "    association ID:" + pID + "    i:" + temp + "\r\n\r\n"; 
									logFile.Write (resInfo, resInfo.GetLength ());
									return IGNORED;
								}
								hr = pAtts->getNamedItem(L"xmi:type",& cNode);
								if (FAILED (hr))
								{
									AfxMessageBox ("Fail to get type of the attributes of the class!");
									//log file
									temp.Format ("%d", i);
									resInfo = "ERROR:Fail to get the ith association end iformation! Abort this association analyse.\r\nINFO:association name:" + pname + "    association ID:" + pID + "    i:" + temp + "\r\n\r\n"; 
									logFile.Write (resInfo, resInfo.GetLength ());
									return IGNORED;
								}
								hr = cNode->get_text(&text);
								valueType.Format ("%S",text);
								hr = pAtts->getNamedItem(L"value",& cNode);
								if (FAILED (hr))
								{
									AfxMessageBox ("Fail to get type of the attributes of the class!");
									//log file
									temp.Format ("%d", i);
									resInfo = "ERROR:Fail to get the ith association end iformation! Abort this association analyse.\r\nINFO:association name:" + pname + "    association ID:" + pID + "    i:" + temp + "\r\n\r\n"; 
									logFile.Write (resInfo, resInfo.GetLength ());
									return IGNORED;
								}
								hr = cNode->get_text(&text);
								value.Format ("%S",text);
								if (!valueType.Compare ("uml:LiteralUnlimitedNatural") && !value.Compare ("-1"))
									lowerValue = "*";
								else if (!valueType.Compare ("uml:LiteralUnlimitedNatural") || !valueType.Compare ("uml:LiteralInteger"))
									lowerValue = value;
								else
								{
								}
							}
							else if (!nodeName.Compare ("upperValue"))
							{
								hr = bNode->get_attributes (&pAtts);
								if (FAILED (hr))
								{
									AfxMessageBox ("Fail to get attributes of the node!");
									//log file
									temp.Format ("%d", i);
									resInfo = "ERROR:Fail to get the ith association end iformation! Abort this association analyse.\r\nINFO:association name:" + pname + "    association ID:" + pID + "    i:" + temp + "\r\n\r\n"; 
									logFile.Write (resInfo, resInfo.GetLength ());
									return IGNORED;
								}
								hr = pAtts->getNamedItem(L"xmi:type",& cNode);
								if (FAILED (hr))
								{
									AfxMessageBox ("Fail to get type of the attributes of the class!");
									//log file
									temp.Format ("%d", i);
									resInfo = "ERROR:Fail to get the ith association end iformation! Abort this association analyse.\r\nINFO:association name:" + pname + "    association ID:" + pID + "    i:" + temp + "\r\n\r\n"; 
									logFile.Write (resInfo, resInfo.GetLength ());
									return IGNORED;
								}
								hr = cNode->get_text(&text);
								valueType.Format ("%S",text);
								hr = pAtts->getNamedItem(L"value",& cNode);
								if (FAILED (hr))
								{
									AfxMessageBox ("Fail to get type of the attributes of the class!");
									//log file
									temp.Format ("%d", i);
									resInfo = "ERROR:Fail to get the ith association end iformation! Abort this association analyse.\r\nINFO:association name:" + pname + "    association ID:" + pID + "    i:" + temp + "\r\n\r\n"; 
									logFile.Write (resInfo, resInfo.GetLength ());
									return IGNORED;
								}
								hr = cNode->get_text(&text);
								value.Format ("%S",text);
								if (!valueType.Compare ("uml:LiteralUnlimitedNatural") && !value.Compare ("-1"))
									upperValue = "*";
								else if (!valueType.Compare ("uml:LiteralUnlimitedNatural") || !valueType.Compare ("uml:LiteralInteger"))
									upperValue = value;
								else
								{
								}
							}
							else
							{
							}
						}
						if (count == 1)
						{
							if (!lowerValue.Compare (upperValue))
								end1multiplicity = lowerValue;
							else
								end1multiplicity = lowerValue +  ".." + upperValue;
						}
						else
						{
							if (!lowerValue.Compare (upperValue))
								end2multiplicity = lowerValue;
							else
								end2multiplicity = lowerValue + ".." + upperValue;
						}
					}
				}
			}
		}
	}
	//if (!paggregation.Compare ("") || !paggregation.Compare ("none"))
	//{
	//	pdirection = "0"; 
	//}
	try
	{
		m_Ado.m_pRecordset->PutCollect("端点一ID", (_bstr_t)end1);				//设置端点一ID字段内容
		m_Ado.m_pRecordset->PutCollect("类一", (_bstr_t)end1name);				//设置类一字段内容
		m_Ado.m_pRecordset->PutCollect("类一ID", (_bstr_t)end1ID);				//设置类一ID字段内容
		m_Ado.m_pRecordset->PutCollect("类一可见性", (_bstr_t)end1visibility);	//设置类一可见性字段内容
		m_Ado.m_pRecordset->PutCollect("类一角色名", (_bstr_t)end1role);		//设置类一角色名字段内容
		m_Ado.m_pRecordset->PutCollect("类一重数", (_bstr_t)end1multiplicity);	//设置类一重数字段内容
		m_Ado.m_pRecordset->PutCollect("端点二ID", (_bstr_t)end2);				//设置端点二ID字段内容
		m_Ado.m_pRecordset->PutCollect("类二", (_bstr_t)end2name);				//设置类二字段内容
		m_Ado.m_pRecordset->PutCollect("类二ID", (_bstr_t)end2ID);				//设置类二ID字段内容
		m_Ado.m_pRecordset->PutCollect("类二可见性", (_bstr_t)end2visibility);	//设置类二可见性字段内容
		m_Ado.m_pRecordset->PutCollect("类二角色名", (_bstr_t)end2role);		//设置类二角色名字段内容
		m_Ado.m_pRecordset->PutCollect("类型", (_bstr_t)paggregation);			//设置类型字段内容
		m_Ado.m_pRecordset->PutCollect("方向", (_bstr_t)pdirection);			//设置方向字段内容
		m_Ado.m_pRecordset->PutCollect("类二重数", (_bstr_t)end2multiplicity);	//设置类二重数字段内容
		m_Ado.m_pRecordset->Update();											//更新记录集
		m_Ado.CloseRecordset();													//关闭记录集
	}
	catch(_com_error e)
	{
		AfxMessageBox(e.Description()); //弹出错误处理
		resInfo = "ERROR:Fail to put association database! Ignore this database write.\r\nINFO:association name:" + pname + "    association ID:" + pID + "\r\n\r\n"; 
		logFile.Write (resInfo, resInfo.GetLength ());
	}	return IGNORED;
	return result;
}

//********************************************************************//
//函数功能：对一个合作节点进行判断分析，处理其属性及包含的交互        //
//参数说明：pNode为此节点的指针，parentName为此节点的父节点名称，     //
//          parentID为父节点ID ，返回值为处理结果                     //
//********************************************************************//
unsigned int CUMLanalyserDlg::CollaborationAnalyse(IXMLDOMNode *pNode, CString parentName, CString parentID)
{
	long i = 0, n = -1;
	unsigned int result = SUCCEED, tempResult = SUCCEED;
	CString temp = "", resInfo = "";

	HRESULT hr;
	VARIANT_BOOL b;
	BSTR text = NULL;
	IXMLDOMNamedNodeMap *pAtts = NULL;
	IXMLDOMNodeList *pNodes = NULL;
	IXMLDOMNode *aNode = NULL, *bNode = NULL;
	CString type = "", name = "", ID = "", visibility = "";

	//合作的属性分析
	hr = pNode->get_attributes (&pAtts);
	if (FAILED (hr))
	{
		AfxMessageBox ("Fail to get attributes of the node!");
		//log file
		resInfo = "ERROR:Fail to get attributes of the collaboration node! Ignore all attributes of the node.\r\nINFO:parentName:" + parentName + "    parentID:" + parentID + "\r\n\r\n"; 
		logFile.Write (resInfo, resInfo.GetLength ());
		return IGNORED;
	}
	hr = pAtts->get_length (&n);					// 获取属性节点个数
	if (FAILED (hr))
	{
		AfxMessageBox ("Fail to get number of the attributes of the node!");
		//log file
		resInfo = "ERROR:Fail to get number of attributes of the collaboration node! Ignore all attributes of the node.\r\nINFO:parentName:" + parentName + "    parentID:" + parentID + "\r\n\r\n"; 
		logFile.Write (resInfo, resInfo.GetLength ());
		return IGNORED;
	}
	for (i = 0; i < n; i ++)
	{
		hr = pAtts->get_item (i, &aNode);//获取该节点对象集合中指定位置的节点
		if (FAILED (hr))
		{
			AfxMessageBox ("Fail to get the wanted attribute of the node!");
			//log file
			temp.Format ("%d", i);
			resInfo = "ERROR:Fail to get ith attribute node of the collaboration node! Ignore the ith attribute node.\r\nINFO:INFO:parentName:" + parentName + "    parentID:" + parentID + "    i:" + temp + "\r\n\r\n"; 
			logFile.Write (resInfo, resInfo.GetLength ());
			if (result == SUCCEED) result = IGNORED;
			continue;
		}
		hr = aNode->get_nodeName (&bstr);			// 获取属性节点的名称
		if (FAILED (hr))
		{
			AfxMessageBox ("Fail to get name of the wanted attribute!");
			//log file
			temp.Format ("%d", i);
			resInfo = "ERROR:Fail to get ith attribute node of the collaboration node! Ignore the ith attribute node.\r\nINFO:INFO:parentName:" + parentName + "    parentID:" + parentID + "    i:" + temp + "\r\n\r\n"; 
			logFile.Write (resInfo, resInfo.GetLength ());
			if (result == SUCCEED) result = IGNORED;
			continue;
		}
		type.Format ("%S",bstr);
		text = NULL;
		hr = aNode->get_text (&text);				//获取属性节点的值
		if (FAILED (hr) || text == NULL)
		{
			AfxMessageBox ("Fail to get the value of wanted attribute's name!");
			//log file
			temp.Format ("%d", i);
			resInfo = "ERROR:Fail to get ith attribute node of the collaboration node! Ignore the ith attribute node.\r\nINFO:INFO:parentName:" + parentName + "    parentID:" + parentID + "    i:" + temp + "\r\n\r\n"; 
			logFile.Write (resInfo, resInfo.GetLength ());
			if (result == SUCCEED) result = IGNORED;
			continue;
		}
		if (! type.Compare ("xmi:id"))
		{
			ID.Format ("%S", text);
		}
		else if (! type.Compare ("name"))
		{
			name.Format ("%S", text);
		}
		else if (! type.Compare ("visibility"))
		{
			visibility.Format ("%S", text);
		}
		else if (temp.Compare ("xmi:type"))
		{
			//log file
			resInfo = "IGNORE:Ignore the ith attribute of the \"uml:Collaboration\" node! Attribute type is \"" + temp + "\".\r\nINFO:parentName:" + parentName + "    parentID:" + parentID + "    i:";
			temp.Format ("%d\r\n\r\n", i);
			resInfo += temp; 
			logFile.Write (resInfo, resInfo.GetLength ());
		}
	}
	try
	{
		CString sql = "select * from collaboration";										//设置查询字符串
		m_Ado.m_pRecordset = m_Ado.OpenRecordset(sql);						//打开记录集
		m_Ado.m_pRecordset->AddNew();										//添加新行
		m_Ado.m_pRecordset->PutCollect("名称", (_bstr_t)name);				//设置名称字段内容
		m_Ado.m_pRecordset->PutCollect("ID", (_bstr_t)ID);					//设置ID字段内容
		m_Ado.m_pRecordset->PutCollect("可见性", (_bstr_t)visibility);		//设置备注字段内容
		m_Ado.m_pRecordset->PutCollect("所属包", (_bstr_t)parentName);		//设置所属包字段内容
		m_Ado.m_pRecordset->PutCollect("所属包ID", (_bstr_t)parentID);		//设置所属包ID字段内容
		m_Ado.m_pRecordset->Update();										//更新记录集
		m_Ado.CloseRecordset();												//关闭记录集
	}
	catch(_com_error e)
	{
		AfxMessageBox(e.Description());										//弹出错误处理
		//log file
		resInfo = "ERROR:Fail to put collaboration data into database! Ignore this database write.\r\nINFO:collabortaion name:" + name + "    collabortaion ID:" + ID + "\r\n\r\n"; 
		logFile.Write (resInfo, resInfo.GetLength ());
		if (result == SUCCEED) result = IGNORED;
	}

	hr = pNode->hasChildNodes (&b);
	if (FAILED (hr))
	{
		AfxMessageBox ("Fail to find whether the node has child!");
		//log file
		resInfo = "ERROR:Fail to find whether the node has child! Ignore child nodes of the node.\r\nINFO:collabortaion name:" + name + "    collabortaion ID:" + ID + "\r\n\r\n";
		logFile.Write (resInfo, resInfo.GetLength ());
		return IGNORED;
	}
	if (!b)											//没有子节点(即没有成员属性和方法)
	{
		return result;
	}

	hr = pNode->get_childNodes (&pNodes);
	if (FAILED (hr))
	{
		AfxMessageBox ("Fail to get children of the node!");
		//log file
		resInfo = "ERROR:Fail to get child nodes of the collabortaion node! Ignore all child nodes of the packet.\r\nINFO:collabortaion name:" + name + "    collabortaion ID:" + ID + "\r\n\r\n"; 
		logFile.Write (resInfo, resInfo.GetLength ());
		return IGNORED;
	}
	hr = pNodes->get_length (&n);				// 获取节点个数
	if (FAILED (hr))
	{
		AfxMessageBox ("Fail to get number of children of the node!");
		//log file
		resInfo = "ERROR:Fail to get number of child nodes of the collabortaion node! Ignore all child nodes of the collabortaion.\r\nINFO:collabortaion name:" + name + "    collabortaion ID:" + ID + "\r\n\r\n"; 
		logFile.Write (resInfo, resInfo.GetLength ());
		return IGNORED;
	}
	for (i = 0; i < n; i ++)
	{
		hr = pNodes->get_item (i, &aNode);//获取该节点对象集合中指定位置的节点
		if (FAILED (hr))
		{
			AfxMessageBox ("Fail to get the wanted child node!");
			//log file
			temp.Format ("%d", i);
			resInfo = "ERROR:Fail to get ith child nodes of the collaboration node! Ignore the ith child node.\r\nINFO:collaboration name:" + name + "    collaboration ID:" + ID + "    i:" + temp + "\r\n\r\n"; 
			logFile.Write (resInfo, resInfo.GetLength ());
			if (result == SUCCEED) result = IGNORED;
			continue;
		}
		hr = aNode->get_nodeName (&bstr);			// 获取节点的名称
		if (FAILED (hr))
		{
			AfxMessageBox ("Fail to get name of the wanted chile node!");
			//log file
			temp.Format ("%d", i);
			resInfo = "ERROR:Fail to get ith child nodes of the collaboration node! Ignore the ith child node.\r\nINFO:collaboration name:" + name + "    collaboration ID:" + ID + "    i:" + temp + "\r\n\r\n"; 
			logFile.Write (resInfo, resInfo.GetLength ());
			if (result == SUCCEED) result = IGNORED;
			continue;
		}
		type.Format ("%S", bstr);
		if (! type.Compare ("ownedBehavior"))					//行为分析
		{
			hr = aNode->get_attributes (&pAtts);
			if (FAILED (hr))
			{
				AfxMessageBox ("Fail to get the attributes of the node!");
				//log file
				resInfo = "ERROR:Fail to get attributes of the child node! Ignore all attributes of the child node.\r\nINFO:node name:" + type + "    collaboration name:" + name + "    collaboration ID:" + ID + "    i:" + temp + "\r\n\r\n"; 
				logFile.Write (resInfo, resInfo.GetLength ());
				return IGNORED;
			}
			hr = pAtts->getNamedItem(L"xmi:type",& bNode);
			if (FAILED (hr))
			{
				AfxMessageBox ("Fail to get the wanted attribute of the node!");
				//log file
				resInfo = "ERROR:Fail to get \"xmi:type\" of the child node! Ignore all attributes of the child node.\r\nINFO:node name:" + type + "    collaboration name:" + name + "    collaboration ID:" + ID + "    i:" + temp + "\r\n\r\n"; 
				logFile.Write (resInfo, resInfo.GetLength ());
				return IGNORED;
			}
			hr = bNode->get_text(&text);
			if (FAILED (hr) || text == NULL)
			{
				AfxMessageBox ("Fail to get value of the wanted attribute!");
				//log file
				resInfo = "ERROR:Fail to get \"xmi:type\" of the child node! Ignore all attributes of the child node.\r\nINFO:node name:" + type + "    collaboration name:" + name + "    collaboration ID:" + ID + "\r\n\r\n"; 
				logFile.Write (resInfo, resInfo.GetLength ());
				return IGNORED;
			}
			type.Format ("%S", text);
			if (! type.Compare ("uml:Interaction"))						//交互分析
			{
				tempResult = InteractionAnalyse (aNode, name, ID);
				if (tempResult <= result) result = tempResult;		
			}
			else
			{
				resInfo = "IGNORE:Ignore a node of node name \"" + type + "\" and its child nodes!\r\nINFO:collaboration name:" + name + "    collaboration ID:" + ID + "\r\n\r\n";  
				logFile.Write (resInfo, resInfo.GetLength ());
				return IGNORED;
			}
		}
		else if (! type.Compare ("ownedAttribute"))						//属性分析
		{
			tempResult = CollaborationAttributeAnalyse (aNode, name, ID);
			if (tempResult <= result) result = tempResult;
		}
		else
		{
			//logfile
			resInfo = "IGNORE:Ignore a node of node name \"" + type + "\" and its child nodes!\r\nINFO:collaboration name:" + name + "    collaboration ID:" + ID + "\r\n\r\n";  
			logFile.Write (resInfo, resInfo.GetLength ());
			return IGNORED;
		}
	}
	return result;
}

//********************************************************************//
//函数功能：对一个关联类节点进行判断分析，处理其属性、方法及关联信息  //
//参数说明：pNode为此节点的指针，parentName为此节点的父节点名称，     //
//          parentID为父节点ID ，返回值为处理结果                     //
//********************************************************************//
unsigned int CUMLanalyserDlg::AssociationClassAnalyse(IXMLDOMNode *pNode, CString parentName, CString parentID)
{
	unsigned int result = SUCCEED, tempResult = SUCCEED;
	tempResult = ClassAnalyse (pNode, parentName, parentID);		//关联类中的类分析
	if (tempResult <= result) result = tempResult;
	tempResult = AssociationAnalyse (pNode, parentName, parentID);	//关联类中的关联分析
	if (tempResult <= result) result = tempResult;
	return result;
}

//************************************************************************//
//函数功能：对一个交互图节点进行判断分析，处理其信息及包含的生命线、消息等//
//参数说明：pNode为此节点的指针，collaborationName为此交互所在合作的名称  //
//          collaborationID为此交互所在合作的ID ，返回值为处理结果        //
//************************************************************************//
unsigned int CUMLanalyserDlg::InteractionAnalyse(IXMLDOMNode *pNode, CString collaborationName, CString collaborationID)
{
	long i = 0, n = -1;
	unsigned int result = SUCCEED, tempResult = SUCCEED, number = 0;

	HRESULT hr;
	VARIANT_BOOL b;
	BSTR text = NULL;
	IXMLDOMNamedNodeMap *pAtts = NULL;
	IXMLDOMNodeList *pNodes = NULL;
	IXMLDOMNode *aNode = NULL, *bNode = NULL;
	CString nodeName = "", type = "", name = "", ID = "", visibility = "", temp = "", resInfo = "";

	//交互的属性分析
	hr = pNode->get_attributes (&pAtts);
	if (FAILED (hr))
	{
		AfxMessageBox ("Fail to get attributes of the node!");
		//log file
		resInfo = "ERROR:Fail to get attributes of the interaction node! Ignore all attributes of the node.\r\nINFO:parent collaboration Name:" + collaborationName + "    parent collaboration ID:" + collaborationID + "\r\n\r\n"; 
		logFile.Write (resInfo, resInfo.GetLength ());
		return IGNORED;
	}
	hr = pAtts->get_length (&n);					// 获取属性节点个数
	if (FAILED (hr))
	{
		AfxMessageBox ("Fail to get number of the attributes of the node!");
		//log file
		resInfo = "ERROR:Fail to get number of attributes of the interaction node! Ignore all attributes of the node.\r\nINFO:parent collaboration Name:" + collaborationName + "    parent collaboration ID:" + collaborationID + "\r\n\r\n"; 
		logFile.Write (resInfo, resInfo.GetLength ());
		return IGNORED;
	}
	for (i = 0; i < n; i ++)
	{
		hr = pAtts->get_item (i, &aNode);//获取该节点对象集合中指定位置的节点
		if (FAILED (hr))
		{
			AfxMessageBox ("Fail to get the wanted attribute of the node!");
			//log file
			temp.Format ("%d", i);
			resInfo = "ERROR:Fail to get ith attribute node of the interaction node! Ignore the ith attribute node.\r\nINFO:INFO:parent collaboration Name:" + collaborationName + "    parent collaboration ID:" + collaborationID + "    i:" + temp + "\r\n\r\n"; 
			logFile.Write (resInfo, resInfo.GetLength ());
			if (result == SUCCEED) result = IGNORED;
			continue;
		}
		hr = aNode->get_nodeName (&bstr);			// 获取属性节点的名称
		if (FAILED (hr))
		{
			AfxMessageBox ("Fail to get name of the wanted attribute!");
			//log file
			temp.Format ("%d", i);
			resInfo = "ERROR:Fail to get ith attribute node of the interaction node! Ignore the ith attribute node.\r\nINFO:INFO:parent collaboration Name:" + collaborationName + "    parent collaboration ID:" + collaborationID + "    i:" + temp + "\r\n\r\n"; 
			logFile.Write (resInfo, resInfo.GetLength ());
			if (result == SUCCEED) result = IGNORED;
			continue;
		}
		type.Format ("%S",bstr);
		text = NULL;
		hr = aNode->get_text (&text);				//获取属性节点的值
		if (FAILED (hr) || text == NULL)
		{
			AfxMessageBox ("Fail to get the value of wanted attribute's name!");
			//log file
			temp.Format ("%d", i);
			resInfo = "ERROR:Fail to get ith attribute node of the interaction node! Ignore the ith attribute node.\r\nINFO:INFO:parent collaboration Name:" + collaborationName + "    parent collaboration ID:" + collaborationID + "    i:" + temp + "\r\n\r\n"; 
			logFile.Write (resInfo, resInfo.GetLength ());
			if (result == SUCCEED) result = IGNORED;
			continue;
		}
		if (! type.Compare ("xmi:id"))
		{
			ID.Format ("%S", text);
		}
		else if (! type.Compare ("name"))
		{
			name.Format ("%S", text);
		}
		else if (! type.Compare ("visibility"))
		{
			visibility.Format ("%S", text);
		}
		else if (temp.Compare ("xmi:type"))
		{
			//log file
			resInfo = "IGNORE:Ignore the ith attribute of the \"uml:Interaction\" node! Attribute type is \"" + temp + "\".\r\nINFO:parent collaboration Name:" + collaborationName + "    parent collaboration ID:" + collaborationID + "    i:";
			temp.Format ("%d\r\n\r\n", i);
			resInfo += temp; 
			logFile.Write (resInfo, resInfo.GetLength ());
		}
	}
	try
	{
		CString sql = "select * from interaction";								//设置查询字符串
		m_Ado.m_pRecordset = m_Ado.OpenRecordset(sql);							//打开记录集
		m_Ado.m_pRecordset->AddNew();											//添加新行
		m_Ado.m_pRecordset->PutCollect("名称", (_bstr_t)name);					//设置名称字段内容
		m_Ado.m_pRecordset->PutCollect("ID", (_bstr_t)ID);						//设置ID字段内容
		m_Ado.m_pRecordset->PutCollect("可见性", (_bstr_t)visibility);			//设置备注字段内容
		m_Ado.m_pRecordset->PutCollect("所属合作", (_bstr_t)collaborationName);	//设置所属合作字段内容
		m_Ado.m_pRecordset->PutCollect("所属合作ID", (_bstr_t)collaborationID);	//设置所属合作ID字段内容
		m_Ado.m_pRecordset->Update();											//更新记录集
		m_Ado.CloseRecordset();													//关闭记录集
	}
	catch(_com_error e)
	{
		AfxMessageBox(e.Description());										//弹出错误处理
		//log file
		resInfo = "ERROR:Fail to put class data into database! Ignore this database write.\r\nINFO:interaction Name:" + name + "    interaction ID:" + ID + "\r\n\r\n"; 
		logFile.Write (resInfo, resInfo.GetLength ());
		return IGNORED;
	}

	hr = pNode->hasChildNodes (&b);
	if (FAILED (hr))
	{
		AfxMessageBox ("Fail to find whether the node has child!");
		//log file
		resInfo = "ERROR:Fail to find whether the node has child! Ignore child nodes of the node.\r\nINFO:interaction Name:" + name + "    interaction ID:" + ID + "\r\n\r\n"; 
		logFile.Write (resInfo, resInfo.GetLength ());
		return IGNORED;	
	}
	if (!b)											//没有子节点(即没有成员属性和方法)
	{
		return result;
	}

	hr = pNode->get_childNodes (&pNodes);
	if (FAILED (hr))
	{
		AfxMessageBox ("Fail to get children of the node!");
		//log file
		resInfo = "ERROR:Fail to get child nodes of the interaction node! Ignore all child nodes of the intercation.\r\nINFO:interaction Name:" + name + "    interaction ID:" + ID + "\r\n\r\n"; 
		logFile.Write (resInfo, resInfo.GetLength ());
		return IGNORED;	
	}
	hr = pNodes->get_length (&n);				// 获取节点个数
	if (FAILED (hr))
	{
		AfxMessageBox ("Fail to get number of children of the node!");
		//log file
		resInfo = "ERRORFail to get child nodes of the interaction node! Ignore all child nodes of the intercation.\r\nINFO:interaction Name:" + name + "    interaction ID:" + ID + "\r\n\r\n"; 
		logFile.Write (resInfo, resInfo.GetLength ());
		return IGNORED;	
	}
	for (i = 0, number = 0; i < n; i ++)
	{
		hr = pNodes->get_item (i, &aNode);
		if (FAILED (hr))
		{
			AfxMessageBox ("Fail to get the wanted child node!");
			//log file
			temp.Format ("%d", i);
			resInfo = "ERROR:Fail to get child nodes of the interaction node! Ignore all child nodes of the intercation.\r\nINFO:interaction Name:" + name + "    interaction ID:" + ID + "    i:" + temp + "\r\n\r\n"; 
			logFile.Write (resInfo, resInfo.GetLength ());
			if (result == SUCCEED) result = IGNORED;
			continue;
		}
		hr = aNode->get_nodeName (&bstr);			// 获取节点的名称
		if (FAILED (hr))
		{
			AfxMessageBox ("Fail to get name of the wanted chile node!");
			//log file
			temp.Format ("%d", i);
			resInfo = "ERROR:Fail to get child nodes of the interaction node! Ignore all child nodes of the intercation.\r\nINFO:interaction Name:" + name + "    interaction ID:" + ID + "    i:" + temp + "\r\n\r\n"; 
			logFile.Write (resInfo, resInfo.GetLength ());
			if (result == SUCCEED) result = IGNORED;
			continue;
		}
		nodeName.Format ("%S", bstr);
		hr = aNode->get_attributes (&pAtts);
		if (FAILED (hr))
		{
			AfxMessageBox ("Fail to get the attributes of the node!");
			//log file
			temp.Format ("%d", i);
			resInfo = "ERROR:Fail to get attributes of the ith child node of interaction! Ignore all these attributes.\r\nINFO:interaction Name:" + name + "    interaction ID:" + ID + "    i:" + temp + "\r\n\r\n"; 
			logFile.Write (resInfo, resInfo.GetLength ());
			if (result == SUCCEED) result = IGNORED;
			continue;
		}
		hr = pAtts->getNamedItem(L"xmi:type",& bNode);
		if (FAILED (hr))
		{
			AfxMessageBox ("Fail to get the wanted attribute of the node!");
			//log file
			temp.Format ("%d", i);
			resInfo = "ERROR:Fail to get \"xmi:type\" attribute of the ith child node of interaction! Ignore all these attributes.\r\nINFO:interaction Name:" + name + "    interaction ID:" + ID + "    i:" + temp + "\r\n\r\n"; 
			logFile.Write (resInfo, resInfo.GetLength ());
			if (result == SUCCEED) result = IGNORED;
			continue;
		}
		hr = bNode->get_text(&text);
		if (FAILED (hr) || text == NULL)
		{
			AfxMessageBox ("Fail to get value of the wanted attribute!");
			//log file
			temp.Format ("%d", i);
			resInfo = "ERROR:Fail to get \"xmi:type\" attribute of the ith child node of interaction! Ignore all these attributes.\r\nINFO:interaction Name:" + name + "    interaction ID:" + ID + "    i:" + temp + "\r\n\r\n"; 
			logFile.Write (resInfo, resInfo.GetLength ());
			if (result == SUCCEED) result = IGNORED;
			continue;
		}
		type.Format ("%S", text);

		if (! nodeName.Compare ("fragment"))						//片段分析
		{
			if (! type.Compare ("uml:OccurrenceSpecification"))		//时间点分析
			{
				number ++;
				tempResult = InteractionOSAnalyse (aNode, name, ID, number, pNodes);
				if (tempResult <= result) result = tempResult;
			}
			else if (! type.Compare ("uml:CombinedFragment"))		//组合片段分析
			{
				tempResult = InteractionCFAnalyse (aNode, name, ID);
				if (tempResult <= result) result = tempResult;
			}
			else if (! type.Compare ("uml:StateInvariant"))			//恒等式声明分析
			{
				tempResult = InteractionSIAnalyse (aNode, name, ID);
				if (tempResult <= result) result = tempResult;
			}
			else
			{
				//logfile
				temp.Format ("%d", i);
				resInfo = "IGNORE:Ignore a node of uml type \"" + type + "\" ith child node and its child nodes of interaction!\r\nINFO:interaction Name:" + name + "    interaction ID:" + ID + "    i:" + temp + "\r\n\r\n"; 
				logFile.Write (resInfo, resInfo.GetLength ());
				if (result == SUCCEED) result = IGNORED;
			}
		}
		else if (! nodeName.Compare ("lifeline") && ! type.Compare ("uml:Lifeline"))	//生命线分析
		{
			tempResult = InteractionLifelineAnalyse (aNode, name, ID);
			if (tempResult <= result) result = tempResult;
		}
		else if (! nodeName.Compare ("message") && ! type.Compare ("uml:Message"))		//消息分析
		{
			tempResult = InteractionMessageAnalyse (aNode, name, ID, pNodes);
			if (tempResult <= result) result = tempResult;
		}
		else if (! nodeName.Compare ("formalGate"))										//门分析
		{
			tempResult = InteractionGateAnalyse (aNode, name, ID);
			if (tempResult <= result) result = tempResult;
		}
		else
		{
			//logfile
			temp.Format ("%d", i);
			resInfo = "IGNORE:Ignore a node of type \"" + type + "\" ith child node and its child nodes of interaction!\r\nINFO:interaction Name:" + name + "    interaction ID:" + ID + "    i:" + temp + "\r\n\r\n"; 
			logFile.Write (resInfo, resInfo.GetLength ());
			if (result == SUCCEED) result = IGNORED;
		}
	}
	return result;
}

//********************************************************************//
//函数功能：对类属性节点进行判断分析，分析属性类型、初始值等          //
//参数说明：pNode为此节点的指针，className为此属性所在类的名称，      //
//          classID为此属性所在类的ID ，返回值为处理结果              //
//********************************************************************//
unsigned int CUMLanalyserDlg::ClassAttributeAnalyse(IXMLDOMNode *pNode, CString className, CString classID)
{
	long int n = -1, i = 0;
	unsigned int result = SUCCEED;					//处理结果
	BOOL isAssociated = FALSE;
	CString resInfo = "", temp = "", nodeName = "", pname = "", pID = "", pvisibility = "", sql = "", pdefault = "", pinfo = "";
	HRESULT hr;
	VARIANT_BOOL b;
	BSTR text = NULL;								//节点值
	IXMLDOMNamedNodeMap *pAtts = NULL;				//属性节点列表
	IXMLDOMNode *aNode = NULL, *bNode = NULL;
	IXMLDOMNodeList *pNodes = NULL;					//子节点列表
	
	//成员属性的属性分析
	hr = pNode->get_attributes (&pAtts);
	if (FAILED (hr))
	{
		AfxMessageBox ("Fail to get attributes of the node!");
		//log file		
		resInfo = "ERROR:Fail to get attributes of the attribute node! Ignore all attributes of the node.\r\nINFO:class name:" + className + "    class ID:" + classID + "\r\n\r\n"; 
		logFile.Write (resInfo, resInfo.GetLength ());
		return IGNORED;
	}
	hr = pAtts->getNamedItem(L"xmi:type",& aNode);
	if (FAILED (hr))
	{
		AfxMessageBox ("Fail to get type of the attributes of the class!");
		//log file		
		resInfo = "ERROR:Fail to get \"xmi:type\" of the node! Ignore all attributes of the node.\r\nINFO:class name:" + className + "    class ID:" + classID + "\r\n\r\n"; 
		logFile.Write (resInfo, resInfo.GetLength ());
		return IGNORED;
	}
	hr = aNode->get_text(&text);
	temp.Format ("%S",text);
	if (temp.Compare ("uml:Property"))
	{
		//log file
		resInfo = "IGNORE:Ignore a class attribute of uml type \"" + temp + "\"! Ignore this class attribute.\r\nINFO:class name:" + className + "    class ID:" + classID + "\r\n\r\n"; 
		logFile.Write (resInfo, resInfo.GetLength ());
		return IGNORED;
	}
	hr = pAtts->get_length (&n);					// 获取属性节点个数
	if (FAILED (hr))
	{
		AfxMessageBox ("Fail to get number of the attributes of the node!");
		//log file
		resInfo = "ERROR:Fail to get number of attributes of the class attribute node! Ignore this class attribute.\r\nINFO:class name:" + className + "    class ID:" + classID + "\r\n\r\n"; 
		logFile.Write (resInfo, resInfo.GetLength ());
		return IGNORED;
	}
	for (i = 0; i < n; i ++)
	{
		hr = pAtts->get_item (i, &aNode);
		if (FAILED (hr))
		{
			AfxMessageBox ("Fail to get the wanted attribute of the node!");
			//log file
			temp.Format ("%d", i);
			resInfo = "ERROR:Fail to get the ith attribute of the class attribute node! Ignore this class attribute.\r\nINFO:class name:" + className + "    class ID:" + classID + "    i:" + temp + "\r\n\r\n"; 
			logFile.Write (resInfo, resInfo.GetLength ());
			if (result == SUCCEED) result = IGNORED;
			continue;
		}
		hr = aNode->get_nodeName (&bstr);			// 获取属性节点的名称
		if (FAILED (hr))
		{
			AfxMessageBox ("Fail to get name of the wanted attribute!");
			//log file
			temp.Format ("%d", i);
			resInfo = "ERROR:Fail to get the ith attribute of the class attribute node! Ignore this class attribute.\r\nINFO:class name:" + className + "    class ID:" + classID + "    i:" + temp + "\r\n\r\n"; 
			logFile.Write (resInfo, resInfo.GetLength ());
			if (result == SUCCEED) result = IGNORED;
			continue;
		}
		nodeName.Format ("%S",bstr);
		text = NULL;
		hr = aNode->get_text (&text);				//获取属性节点的值
		if (FAILED (hr) || text == NULL)
		{
			AfxMessageBox ("Fail to get the value of wanted attribute's name!");
			//log file
			temp.Format ("%d", i);
			resInfo = "ERROR:Fail to get the ith attribute of the class attribute node! Ignore this class attribute.\r\nINFO:class name:" + className + "    class ID:" + classID + "    i:" + temp + "\r\n\r\n"; 
			logFile.Write (resInfo, resInfo.GetLength ());
			if (result == SUCCEED) result = IGNORED;
			continue;
		}
		if (!nodeName.Compare ("xmi:id"))
		{
			pID.Format ("%S", text);
		}
		else if (!nodeName.Compare ("name"))
		{
			pname.Format ("%S", text);
		}
		else if (!nodeName.Compare ("visibility"))
		{
			pvisibility.Format ("%S", text);
		}
		else if (!nodeName.Compare ("association"))
		{
			isAssociated = TRUE;
		}
		else if (nodeName.Compare ("xmi:type"))
		{
			temp.Format ("%s:%S  ", nodeName, text);
			pinfo += temp;
			//log file
			temp.Format ("%d", i);
			resInfo = "IGNORE:Ignore the  ith attribute of type \"" + nodeName + "\" of the class attribute node! Ignore this class attribute.\r\nINFO:class name:" + className + "    class ID:" + classID + "    i:" + temp + "\r\n\r\n"; 
			logFile.Write (resInfo, resInfo.GetLength ());
			if (result == SUCCEED) result = IGNORED;
			continue;
		}
	}
	if (isAssociated)
		return SUCCEED;
	try
	{
		sql = "select * from attribute";									//设置查询字符串
		m_Ado.m_pRecordset = m_Ado.OpenRecordset(sql);						//打开记录集
		m_Ado.m_pRecordset->AddNew();										//添加新行
		m_Ado.m_pRecordset->PutCollect("名称", (_bstr_t)pname);				//设置名称字段内容
		m_Ado.m_pRecordset->PutCollect("ID", (_bstr_t)pID);					//设置ID字段内容
		m_Ado.m_pRecordset->PutCollect("可见性", (_bstr_t)pvisibility);		//设置可见性字段内容
		m_Ado.m_pRecordset->PutCollect("初始值", (_bstr_t)pdefault);		//设置初始值字段内容
		m_Ado.m_pRecordset->PutCollect("备注", (_bstr_t)pinfo);				//设置备注字段内容
		m_Ado.m_pRecordset->PutCollect("所属类", (_bstr_t)className);		//设置所属类字段内容
		m_Ado.m_pRecordset->PutCollect("所属类ID", (_bstr_t)classID);		//设置所属类字段内容
		//m_Ado.m_pRecordset->Update();										//更新记录集
		//m_Ado.CloseRecordset();												//关闭记录集
	}
	catch(_com_error e)
	{
		AfxMessageBox(e.Description());										//弹出错误处理
		//log file
		resInfo = "ERROR:Fail to put class attribute data into database! Ignore this database write.\r\nINFO:attribute name:" + pname + "    attribute ID" + pID + "    class name:" + className + "    class ID:" + classID + "\r\n\r\n"; 
		logFile.Write (resInfo, resInfo.GetLength ());
		if (result == SUCCEED) result = IGNORED;
	}

	//类的成员属性的类型分析
	hr = pNode->hasChildNodes (&b);											//判断节点是否有孩子
	if (FAILED (hr))
	{
		AfxMessageBox ("Fail to find whether the node has child!");
		//log file	
		resInfo = "ERROR:Fail to find whether the node has child! !Ignore all these child nodes.\r\nINFO:attribute name:" + pname + "    attribute ID" + pID + "    class name:" + className + "    class ID:" + classID + "\r\n\r\n"; 
		logFile.Write (resInfo, resInfo.GetLength ());
		return IGNORED;
	}
	if (!b)											//没有子节点(即没有成员属性和方法)
	{
		try
		{
			m_Ado.m_pRecordset->Update();										//更新记录集
			m_Ado.CloseRecordset();												//关闭记录集
		}
		catch(_com_error e)
		{
			AfxMessageBox(e.Description()); //弹出错误处理
		}
		return result;
	}

	hr = pNode->get_childNodes (&pNodes);			//获取子节点
	if (FAILED (hr))
	{
		AfxMessageBox ("Fail to get child nodes of the node!");
		//log file
		resInfo = "ERROR:Fail to get child nodes of the class attribute!Ignore all these child nodes.\r\nINFO:attribute name:" + pname + "    attribute ID" + pID + "    class name:" + className + "    class ID:" + classID + "\r\n\r\n"; 
		logFile.Write (resInfo, resInfo.GetLength ());
		return IGNORED;
	}
	hr = pNodes->get_length (&n);					// 获取子节点个数
	if (FAILED (hr))
	{
		AfxMessageBox ("Fail to get number of the child nodes of the node!");
		//log file
		resInfo = "ERROR:Fail to get number of child nodes of the class attribute!Ignore all these child nodes.\r\nINFO:attribute name:" + pname + "    attribute ID" + pID + "    class name:" + className + "    class ID:" + classID + "\r\n\r\n"; 
		logFile.Write (resInfo, resInfo.GetLength ());
		return IGNORED;
	}
	for (i = 0; i < n; i ++)
	{

		hr = pNodes->get_item (i, &aNode);
		if (FAILED (hr))
		{
			AfxMessageBox ("Fail to get the wanted child node!");
			//log file
			temp.Format ("%d", i);
			resInfo = "ERROR:Fail to get the ith child node of the class attribute!Ignore this child node.\r\nINFO:attribute name:" + pname + "    attribute ID" + pID + "    class name:" + className + "    class ID:" + classID + "    i:" + temp + "\r\n\r\n"; 
			logFile.Write (resInfo, resInfo.GetLength ());
			if (result == SUCCEED) result = IGNORED;
			continue;
		}
		hr = aNode->get_nodeName (&bstr);			// 获取子节点的名称
		if (FAILED (hr))
		{
			AfxMessageBox ("Fail to get name of the wanted chile node!");
			//log file
			temp.Format ("%d", i);
			resInfo = "ERROR:Fail to get the ith child node of the class attribute!Ignore this child node.\r\nINFO:attribute name:" + pname + "    attribute ID" + pID + "    class name:" + className + "    class ID:" + classID + "    i:" + temp + "\r\n\r\n"; 
			logFile.Write (resInfo, resInfo.GetLength ());
			if (result == SUCCEED) result = IGNORED;
			continue;
		}
		nodeName.Format ("%S",bstr);
		text = NULL;
		hr = aNode->get_text (&text);						//获取属性节点的值
		if (FAILED (hr) || text == NULL)
		{
			AfxMessageBox ("Fail to get the value of wanted child's name!");
			//log file
			temp.Format ("%d", i);
			resInfo = "ERROR:Fail to get the ith child node of the class attribute!Ignore this child node.\r\nINFO:attribute name:" + pname + "    attribute ID" + pID + "    class name:" + className + "    class ID:" + classID + "    i:" + temp + "\r\n\r\n"; 
			logFile.Write (resInfo, resInfo.GetLength ());
			if (result == SUCCEED) result = IGNORED;
			continue;
		}
		if (!nodeName.Compare ("type"))			//成员属性类型分析
		{
			hr = aNode->get_attributes (&pAtts);
			if (FAILED (hr))
			{
				AfxMessageBox ("Failed to get attributes of the node.");
				//logfile
				resInfo = "ERROR:Fail to get type of the class attribute!Abort analyse the attibute type.\r\nINFO:attribute name:" + pname + "    attribute ID" + pID + "    class name:" + className + "    class ID:" + classID + "\r\n\r\n"; 
				logFile.Write (resInfo, resInfo.GetLength ());
				return IGNORED;
			}
			hr = pAtts->getNamedItem(L"xmi:idref",& bNode);
			if (FAILED (hr))
			{
				AfxMessageBox ("Failed to get wanted attribute of the node.");
				//logfile
				resInfo = "ERROR:Fail to get type of the class attribute!Abort analyse the attibute type.\r\nINFO:attribute name:" + pname + "    attribute ID" + pID + "    class name:" + className + "    class ID:" + classID + "\r\n\r\n"; 
				logFile.Write (resInfo, resInfo.GetLength ());
				return IGNORED;
			}
			hr = bNode->get_text(&text);
			if (text != NULL)
			{
				temp.Format ("%S", text);
			}
			try
			{
				m_Ado.m_pRecordset->PutCollect("类型", (_bstr_t)temp);		//添加新记录
				//m_Ado.m_pRecordset->Update();								//更新记录集
				//m_Ado.CloseRecordset();										//关闭记录集
			}
			catch(_com_error e)
			{
				AfxMessageBox(e.Description()); //弹出错误处理
				resInfo = "ERROR:Fail to put information of the class attribute into database file! Ignore this database write.\r\nINFO:attribute name:" + pname + "    attribute ID" + pID + "    class name:" + className + "    class ID:" + classID + "\r\n\r\n"; 
				logFile.Write (resInfo, resInfo.GetLength ());
				return IGNORED;
			}
		}
		else if (!nodeName.Compare ("defaultValue"))			//成员属性初始值分析
		{
			hr = aNode->get_attributes (&pAtts);
			hr = pAtts->getNamedItem(L"xmi:type",& bNode);
			hr = bNode->get_text(&text);
			if (text != NULL)
			{
				pdefault.Format ("%S -- ", text);
			}
			hr = pAtts->getNamedItem(L"value",& bNode);
			hr = bNode->get_text(&text);
			if (text != NULL)
			{
				temp.Format ("%S", text);
				pdefault += temp;
			}
			try
			{
				m_Ado.m_pRecordset->PutCollect("初始值", (_bstr_t)pdefault);//添加新记录
				//m_Ado.m_pRecordset->Update();								//更新记录集
				//m_Ado.CloseRecordset();										//关闭记录集
			}
			catch(_com_error e)
			{
				AfxMessageBox(e.Description()); //弹出错误处理
				resInfo = "ERROR:Fail to put information of the class attribute into database file! Ignore this database write.\r\nINFO:attribute name:" + pname + "    attribute ID" + pID + "    class name:" + className + "    class ID:" + classID + "\r\n\r\n"; 
				logFile.Write (resInfo, resInfo.GetLength ());
				return IGNORED;
			}		
		}
		else
		{
			//logfile
			resInfo = "IGNORE:Ignore a child node of type \"" + nodeName + "\" of the class attribute!\r\nINFO:attribute name:" + pname + "    attribute ID" + pID + "    class name:" + className + "    class ID:" + classID + "\r\n\r\n"; 
			logFile.Write (resInfo, resInfo.GetLength ());
		}
	}
	try
	{
		m_Ado.m_pRecordset->Update();										//更新记录集
		m_Ado.CloseRecordset();												//关闭记录集
	}
	catch(_com_error e)
	{
		AfxMessageBox(e.Description()); //弹出错误处理
		resInfo = "ERROR:Fail to put information of the class attribute into database file! Ignore this database write.\r\nINFO:attribute name:" + pname + "    attribute ID" + pID + "    class name:" + className + "    class ID:" + classID + "\r\n\r\n"; 
		logFile.Write (resInfo, resInfo.GetLength ());
		return IGNORED;
	}
	return result;
}

//********************************************************************//
//函数功能：对类继承信息节点进行判断分析，分析继承的父节点信息等      //
//参数说明：pNode为此节点的指针，className为此继承所在类的名称，      //
//          classID为此继承所在类的ID ，返回值为处理结果              //
//********************************************************************//
unsigned int CUMLanalyserDlg::ClassGeneralizationAnalyse(IXMLDOMNode *pNode, CString className, CString classID)
{
	HRESULT hr;
	BSTR text = NULL;
	IXMLDOMNode *aNode = NULL, *bNode = NULL;
	IXMLDOMNamedNodeMap *pAtts = NULL;
	IXMLDOMNodeList *pNodes = NULL;

	long i = 0, n = -1;
	CString temp = "", generalID = "", gID = "", gname = "", resInfo = "";

	//获取继承信息
	hr = pNode->get_attributes (&pAtts);
	if (FAILED (hr))
	{
		AfxMessageBox ("Fail to get generalization infomation!");
		//log file
		resInfo = "ERROR:Fail to get attributes of the attribute node! Ignore all attributes of the node.\r\nINFO:class name:" + className + "    class ID:" + classID + "\r\n\r\n"; 
		logFile.Write (resInfo, resInfo.GetLength ());
		return IGNORED;
	}
	hr = pAtts->getNamedItem(L"xmi:type",& aNode);
	if (FAILED (hr))
	{
		AfxMessageBox ("Fail to get generalization type!");
		//log file
		resInfo = "ERROR:Fail to get \"xmi:type\" of the node! Ignore all attributes of the node.\r\nINFO:class name:" + className + "    class ID:" + classID + "\r\n\r\n"; 
		logFile.Write (resInfo, resInfo.GetLength ());
		return IGNORED;
	}
	hr = aNode->get_text(&text);
	if (FAILED (hr))
	{
		AfxMessageBox ("Fail to get generalization infomation!");
		//log file		
		resInfo = "ERROR:Fail to get \"xmi:type\" of the node! Ignore all attributes of the node.\r\nINFO:class name:" + className + "    class ID:" + classID + "\r\n\r\n"; 
		logFile.Write (resInfo, resInfo.GetLength ());
		return IGNORED;
	}
	if (text != NULL)
	{
		temp.Format ("%S", text);
	}
	if (!temp.Compare ("uml:Generalization"))				//继承分析
	{
		hr = pAtts->getNamedItem(L"xmi:id",& aNode);
		if (FAILED (hr))
		{
			AfxMessageBox ("Fail to get generalization ID!");
			//log file
			resInfo = "ERROR:Fail to get generalization ID! Abort this generalization analyse.\r\nINFO:class name:" + className + "    class ID:" + classID + "\r\n\r\n"; 
			logFile.Write (resInfo, resInfo.GetLength ());
			return IGNORED;
		}
		hr = aNode->get_text(&text);
		if (FAILED (hr))
		{
			AfxMessageBox ("Fail to get generalization ID infomation!");
			//log file
			resInfo = "ERROR:Fail to get generalization ID! Abort this generalization analyse.\r\nINFO:class name:" + className + "    class ID:" + classID + "\r\n\r\n"; 
			logFile.Write (resInfo, resInfo.GetLength ());
			return IGNORED;
		}
		if (text != NULL)
			generalID.Format ("%S", text);

		hr = pAtts->getNamedItem(L"general",& aNode);
		if (FAILED (hr))
		{
			AfxMessageBox ("Fail to get parent class infomation!");
			//log file
			resInfo = "ERROR:Fail to get parent class ID! Abort this generalization analyse.\r\nINFO:generalization ID:" + generalID + "    class name:" + className + "    class ID:" + classID + "\r\n\r\n"; 
			logFile.Write (resInfo, resInfo.GetLength ());
			return IGNORED;
		}
		hr = aNode->get_text(&text);
		if (FAILED (hr))
		{
			AfxMessageBox ("Fail to get parent class ID!");
			//log file
		}
		if (text != NULL)
		{
			//寻找父类信息
			gID.Format ("%S", text);
			hr = pXMLDoc->selectNodes(L"//packagedElement", &pNodes);
			if (FAILED (hr))
			{
				AfxMessageBox ("Fail to start finding parent class!");
				//log file
				resInfo = "ERROR:Fail to get information of the parent! Abort this generalization analyse.\r\nINFO:generalization ID:" + generalID + "    class name:" + className + "    class ID:" + classID + "    parent class ID:" + gID + "\r\n\r\n"; 
				logFile.Write (resInfo, resInfo.GetLength ());
				return IGNORED;
			}
			hr = pNodes->get_length (&n);
			if (FAILED (hr))
			{
				AfxMessageBox ("Failure occurs in the progress of finding parent class!");
				//log file
				resInfo = "ERROR:Fail to get information of the parent! Abort this generalization analyse.\r\nINFO:generalization ID:" + generalID + "    class name:" + className + "    class ID:" + classID + "\r\n\r\n"; 
				logFile.Write (resInfo, resInfo.GetLength ());
				return IGNORED;
			}
			for (i = 0; i < n; i ++)
			{
				hr = pNodes->get_item (i, &aNode);//获取该节点对象集合中指定位置的节点
				if (FAILED (hr))
				{
					AfxMessageBox ("Fail to get wanted item!");
					//log file
					resInfo = "ERROR:Fail to get information of the parent! Abort this generalization analyse.\r\nINFO:generalization ID:" + generalID + "    class name:" + className + "    class ID:" + classID + "\r\n\r\n"; 
					logFile.Write (resInfo, resInfo.GetLength ());
					return IGNORED;
				}
				hr = aNode->get_attributes (&pAtts);
				if (FAILED (hr))
				{
					AfxMessageBox ("Fail to get attributes of wanted item!");
					//log file
					resInfo = "ERROR:Fail to get information of the parent! Abort this generalization analyse.\r\nINFO:generalization ID:" + generalID + "    class name:" + className + "    class ID:" + classID + "\r\n\r\n"; 
					logFile.Write (resInfo, resInfo.GetLength ());
					return IGNORED;
				}
				hr = pAtts->getNamedItem(L"xmi:id",& bNode);
				if (FAILED (hr))
				{
					AfxMessageBox ("Fail to get ID of wanted item!");
					//log file
					resInfo = "ERROR:Fail to get information of the parent! Abort this generalization analyse.\r\nINFO:generalization ID:" + generalID + "    class name:" + className + "    class ID:" + classID + "\r\n\r\n"; 
					logFile.Write (resInfo, resInfo.GetLength ());
					return IGNORED;
				}
				hr = bNode->get_text(&text);
				if (FAILED (hr))
				{
					AfxMessageBox ("Fail to get ID information of wanted item!");
					//log file
					resInfo = "ERROR:Fail to get information of the parent! Abort this generalization analyse.\r\nINFO:generalization ID:" + generalID + "    class name:" + className + "    class ID:" + classID + "\r\n\r\n"; 
					logFile.Write (resInfo, resInfo.GetLength ());
					return IGNORED;
				}
				temp.Format ("%S",text);
				if (!temp.Compare (gID))
				{
					hr = pAtts->getNamedItem(L"name",& bNode);
					if (FAILED (hr))
					{
						AfxMessageBox ("Fail to get name of parent class!");
						//log file
						resInfo = "ERROR:Fail to get information of the parent! Abort this generalization analyse.\r\nINFO:generalization ID:" + generalID + "    class name:" + className + "    class ID:" + classID + "\r\n\r\n"; 
						logFile.Write (resInfo, resInfo.GetLength ());
						return IGNORED;
					}
					hr = bNode->get_text(&text);
					if (FAILED (hr))
					{
						AfxMessageBox ("Fail to get name information of parent class!");
						//log file
						resInfo = "ERROR:Fail to get information of the parent! Abort this generalization analyse.\r\nINFO:generalization ID:" + generalID + "    class name:" + className + "    class ID:" + classID + "\r\n\r\n"; 
						logFile.Write (resInfo, resInfo.GetLength ());
						return IGNORED;
					}
					gname.Format ("%S",text);
					break;
				}
			}
			try
			{
				CString sql = "select * from generalization";					//设置查询字符串
				m_Ado.m_pRecordset = m_Ado.OpenRecordset(sql);					//打开记录集
				m_Ado.m_pRecordset->AddNew();
				m_Ado.m_pRecordset->PutCollect("ID", (_bstr_t)generalID);		//添加新记录
				m_Ado.m_pRecordset->PutCollect("类", (_bstr_t)className);		//添加新记录
				m_Ado.m_pRecordset->PutCollect("类ID", (_bstr_t)classID);		//添加新记录
				m_Ado.m_pRecordset->PutCollect("继承类", (_bstr_t)gname);		//添加新记录
				m_Ado.m_pRecordset->PutCollect("继承类ID", (_bstr_t)gID);		//添加新记录
				m_Ado.m_pRecordset->Update();									//更新记录集
				m_Ado.CloseRecordset();	
			}
			catch(_com_error e)
			{
				AfxMessageBox(e.Description()); //弹出错误处理
				resInfo = "ERROR:Fail to put information of the parent class into database file! Abort this database write.\r\nINFO:generalization ID:" + generalID + "    class name:" + className + "    class ID:" + classID + "    parent class name" + gname + "    parent class ID" + gID + "\r\n\r\n"; 
				logFile.Write (resInfo, resInfo.GetLength ());
				return IGNORED;
			}
		}
	}
	else					//忽略其它信息
	{
		//logfile		
		resInfo = "IGNORE:Ignore this uml generalization type \"" + temp + "\" node of the class.\r\nINFO:generalization ID:" + generalID + "    class name:" + className + "    class ID:" + classID + "\r\n\r\n"; 
		logFile.Write (resInfo, resInfo.GetLength ());
		return IGNORED;
	}
	return SUCCEED;
}

//********************************************************************//
//函数功能：对类方法节点进行判断分析，分析方法的名称、参数等          //
//参数说明：pNode为此节点的指针，className为此方法所在类的名称，      //
//          classID为此方法所在类的ID ，返回值为处理结果              //
//********************************************************************//
unsigned int CUMLanalyserDlg::ClassOperationAnalyse(IXMLDOMNode *pNode, CString className, CString classID)
{
	long int n = -1, i = 0, m = -1, j = 0;
	unsigned int result = SUCCEED;					//处理结果
	CString temp = "", nodeName = "", pname = "", pID = "", pvisibility = "", sql = "", qname = "", qID = "", qdirection = "", qtype = "";
	HRESULT hr;
	VARIANT_BOOL b;
	BSTR text = NULL;								//节点值
	IXMLDOMNamedNodeMap *pAtts = NULL;				//属性节点列表
	IXMLDOMNode *aNode = NULL, *bNode = NULL;
	IXMLDOMNodeList *pNodes = NULL;					//子节点列表
	CString resInfo = "";
	
	//成员方法的属性分析
	hr = pNode->get_attributes (&pAtts);
	if (FAILED (hr))
	{
		AfxMessageBox ("Fail to get attributes of the node!");
		//log file		
		resInfo = "ERROR:Fail to get attributes of the operation node! Ignore all attributes of the node.\r\nINFO:class name:" + className + "    class ID:" + classID + "\r\n\r\n"; 
		logFile.Write (resInfo, resInfo.GetLength ());
		return IGNORED;
	}
	hr = pAtts->get_length (&n);					// 获取属性节点个数
	if (FAILED (hr))
	{
		AfxMessageBox ("Fail to get number of the attributes of the node!");
		//log file
		resInfo = "ERROR:Fail to get number of attributes of the class operation node! Ignore this class operation.\r\nINFO:class name:" + className + "    class ID:" + classID + "\r\n\r\n"; 
		logFile.Write (resInfo, resInfo.GetLength ());
		return IGNORED;
	}
	for (i = 0; i < n; i ++)
	{
		hr = pAtts->get_item (i, &aNode);
		if (FAILED (hr))
		{
			AfxMessageBox ("Fail to get the wanted attribute of the node!");
			//log file
			temp.Format ("%d", i);
			resInfo = "ERROR:Fail to get the ith attribute of the class operation node! Ignore this operation attribute.\r\nINFO:class name:" + className + "    class ID:" + classID + "    i:" + temp + "\r\n\r\n"; 
			logFile.Write (resInfo, resInfo.GetLength ());
			if (result == SUCCEED) result = IGNORED;
			continue;
		}
		hr = aNode->get_nodeName (&bstr);			// 获取属性节点的名称
		if (FAILED (hr))
		{
			AfxMessageBox ("Fail to get name of the wanted attribute!");
			//log file
			temp.Format ("%d", i);
			resInfo = "ERROR:Fail to get the ith attribute of the class operation node! Ignore this operation attribute.\r\nINFO:class name:" + className + "    class ID:" + classID + "    i:" + temp + "\r\n\r\n"; 
			logFile.Write (resInfo, resInfo.GetLength ());
			if (result == SUCCEED) result = IGNORED;
			continue;
		}
		nodeName.Format ("%S",bstr);
		text = NULL;
		hr = aNode->get_text (&text);				//获取属性节点的值
		if (FAILED (hr) || text == NULL)
		{
			AfxMessageBox ("Fail to get the value of wanted attribute's name!");
			//log file
			temp.Format ("%d", i);
			resInfo = "ERROR:Fail to get the ith attribute of the class operation node! Ignore this operation attribute.\r\nINFO:class name:" + className + "    class ID:" + classID + "    i:" + temp + "\r\n\r\n"; 
			logFile.Write (resInfo, resInfo.GetLength ());
			if (result == SUCCEED) result = IGNORED;
			continue;
		}
		if (!nodeName.Compare ("xmi:id"))
		{
			pID.Format ("%S", text);
		}
		else if (!nodeName.Compare ("name"))
		{
			pname.Format ("%S", text);
		}
		else if (!nodeName.Compare ("visibility"))
		{
			pvisibility.Format ("%S", text);
		}
		else
		{
			//log file
			temp.Format ("%d", i);
			resInfo = "IGNORE:Ignore the  ith attribute of type \"" + nodeName + "\" of the class operation node! Ignore this class operation attribute.\r\nINFO:class name:" + className + "    class ID:" + classID + "    i:" + temp + "\r\n\r\n"; 
			logFile.Write (resInfo, resInfo.GetLength ());
			if (result == SUCCEED) result = IGNORED;
			continue;
		}
	}
	try
	{
		sql = "select * from operation";									//设置查询字符串
		m_Ado.m_pRecordset = m_Ado.OpenRecordset(sql);						//打开记录集
		m_Ado.m_pRecordset->AddNew();										//添加新行
		m_Ado.m_pRecordset->PutCollect("名称", (_bstr_t)pname);				//设置名称字段内容
		m_Ado.m_pRecordset->PutCollect("ID", (_bstr_t)pID);					//设置ID字段内容
		m_Ado.m_pRecordset->PutCollect("可见性", (_bstr_t)pvisibility);		//设置可见性字段内容
		m_Ado.m_pRecordset->PutCollect("所属类", (_bstr_t)className);		//设置所属类字段内容
		m_Ado.m_pRecordset->PutCollect("所属类ID", (_bstr_t)classID);		//设置所属类字段内容
		m_Ado.m_pRecordset->Update();										//更新记录集
		m_Ado.CloseRecordset();												//关闭记录集
	}
	catch(_com_error e)
	{
		AfxMessageBox(e.Description());										//弹出错误处理
		//log file
		resInfo = "ERROR:Fail to put class operation data into database! Ignore this database write.\r\nINFO:operation name:" + pname + "    operation ID" + pID + "    class name:" + className + "    class ID:" + classID + "\r\n\r\n"; 
		logFile.Write (resInfo, resInfo.GetLength ());
		if (result == SUCCEED) result = IGNORED;
	}

	//类的成员方法的参数分析
	hr = pNode->hasChildNodes (&b);											//判断节点是否有孩子
	if (FAILED (hr))
	{
		AfxMessageBox ("Fail to find whether the node has child!");
		//log file	
		resInfo = "ERROR:Fail to find whether the node has child! !Ignore all these child nodes.\r\nINFO:operation name:" + pname + "    operation ID" + pID + "    class name:" + className + "    class ID:" + classID + "\r\n\r\n"; 
		logFile.Write (resInfo, resInfo.GetLength ());
		return IGNORED;
	}
	if (!b)											//没有子节点(即没有成员属性和方法)
	{
		return result;
	}

	hr = pNode->get_childNodes (&pNodes);			//获取子节点
	if (FAILED (hr))
	{
		AfxMessageBox ("Fail to get child nodes of the node!");
		//log file
		resInfo = "ERROR:Fail to get child nodes of the class operation!Ignore all these child nodes.\r\nINFO:operation name:" + pname + "    operation ID" + pID + "    class name:" + className + "    class ID:" + classID + "\r\n\r\n"; 
		logFile.Write (resInfo, resInfo.GetLength ());
		return IGNORED;
	}
	hr = pNodes->get_length (&n);					// 获取子节点个数
	if (FAILED (hr))
	{
		AfxMessageBox ("Fail to get number of the child nodes of the node!");
		//log file
		resInfo = "ERROR:Fail to get number of child nodes of the class operation!Ignore all these child nodes.\r\nINFO:operation name:" + pname + "    operation ID" + pID + "    class name:" + className + "    class ID:" + classID + "\r\n\r\n"; 
		logFile.Write (resInfo, resInfo.GetLength ());
		return IGNORED;
	}
	for (i = 0; i < n; i ++)
	{

		hr = pNodes->get_item (i, &aNode);
		if (FAILED (hr))
		{
			AfxMessageBox ("Fail to get the wanted child node!");
			//log file
			temp.Format ("%d", i);
			resInfo = "ERROR:Fail to get the ith child node of the class operation!Ignore all these child nodes.\r\nINFO:operation name:" + pname + "    operation ID" + pID + "    class name:" + className + "    class ID:" + classID + "    i:" + temp + "\r\n\r\n"; 
			logFile.Write (resInfo, resInfo.GetLength ());
			if (result == SUCCEED) result = IGNORED;
			continue;
		}
		hr = aNode->get_nodeName (&bstr);			// 获取子节点的名称
		if (FAILED (hr))
		{
			AfxMessageBox ("Fail to get name of the wanted chile node!");
			//log file
			temp.Format ("%d", i);
			resInfo = "ERROR:Fail to get the ith child node of the class operation!Ignore all these child nodes.\r\nINFO:operation name:" + pname + "    operation ID" + pID + "    class name:" + className + "    class ID:" + classID + "    i:" + temp + "\r\n\r\n"; 
			logFile.Write (resInfo, resInfo.GetLength ());
			if (result == SUCCEED) result = IGNORED;
			continue;
		}
		nodeName.Format ("%S",bstr);
		text = NULL;
		hr = aNode->get_text (&text);						//获取属性节点的值
		if (FAILED (hr) || text == NULL)
		{
			AfxMessageBox ("Fail to get the value of wanted child's name!");
			//log file
			temp.Format ("%d", i);
			resInfo = "ERROR:Fail to get the ith child node of the class operation!Ignore all these child nodes.\r\nINFO:operation name:" + pname + "    operation ID" + pID + "    class name:" + className + "    class ID:" + classID + "    i:" + temp + "\r\n\r\n"; 
			logFile.Write (resInfo, resInfo.GetLength ());
			if (result == SUCCEED) result = IGNORED;
			continue;
		}
		if (!nodeName.Compare ("ownedParameter"))			//成员属性类型分析
		{
			hr = aNode->get_attributes (&pAtts);
			if (FAILED (hr))
			{
				AfxMessageBox ("Fail to get attributes of the node!");
				//log file
				resInfo = "ERROR:Fail to get parameters of the class operation!Ignore all this parameter.\r\nINFO:operation name:" + pname + "    operation ID" + pID + "    class name:" + className + "    class ID:" + classID + "\r\n\r\n"; 
				logFile.Write (resInfo, resInfo.GetLength ());
				if (result == SUCCEED) result = IGNORED;
				continue;
			}
			hr = pAtts->get_length (&m);					// 获取属性节点个数
			if (FAILED (hr))
			{
				AfxMessageBox ("Fail to get number of the attributes of the node!");
				//log file
				resInfo = "ERROR:Fail to get number of parameters of the class operation!Ignore all this parameter.\r\nINFO:operation name:" + pname + "    operation ID" + pID + "    class name:" + className + "    class ID:" + classID + "\r\n\r\n"; 
				logFile.Write (resInfo, resInfo.GetLength ());
				if (result == SUCCEED) result = IGNORED;
				continue;
			}
			qname = "";
			qID = "";
			qdirection = "";
			qtype = "";
			for (j = 0; j < m; j ++)
			{
				hr = pAtts->get_item (j, &bNode);
				if (FAILED (hr))
				{
					AfxMessageBox ("Fail to get the wanted attribute of the node!");
					//log file
					resInfo = "ERROR:Fail to get parameter information of the class operation!Ignore all this parameter.\r\nINFO:operation name:" + pname + "    operation ID" + pID + "    class name:" + className + "    class ID:" + classID + "\r\n\r\n"; 
					logFile.Write (resInfo, resInfo.GetLength ());
					if (result == SUCCEED) result = IGNORED;
					break;
				}
				hr = bNode->get_nodeName (&bstr);			// 获取属性节点的名称
				if (FAILED (hr))
				{
					AfxMessageBox ("Fail to get name of the wanted attribute!");
					//log file
					resInfo = "ERROR:Fail to get parameter information of the class operation!Ignore all this parameter.\r\nINFO:operation name:" + pname + "    operation ID" + pID + "    class name:" + className + "    class ID:" + classID + "\r\n\r\n"; 
					logFile.Write (resInfo, resInfo.GetLength ());
					if (result == SUCCEED) result = IGNORED;
					break;
				}
				nodeName.Format ("%S",bstr);
				text = NULL;
				hr = bNode->get_text (&text);				//获取属性节点的值
				if (FAILED (hr) || text == NULL)
				{
					AfxMessageBox ("Fail to get the value of wanted attribute's name!");
					//log file
					resInfo = "ERROR:Fail to get parameter information of the class operation!Ignore all this parameter.\r\nINFO:operation name:" + pname + "    operation ID" + pID + "    class name:" + className + "    class ID:" + classID + "\r\n\r\n"; 
					logFile.Write (resInfo, resInfo.GetLength ());
					if (result == SUCCEED) result = IGNORED;
					break;
				}
				if (!nodeName.Compare ("xmi:id"))
				{
					qID.Format ("%S", text);
				}
				else if (!nodeName.Compare ("name"))
				{
					qname.Format ("%S", text);
				}
				else if (!nodeName.Compare ("direction"))
				{
					qdirection.Format ("%S", text);
				}
				else if (!nodeName.Compare ("type"))
				{
					qtype.Format ("%S", text);
				}
				else
				{
					//log file	
					resInfo = "IGNORE:Ignore a information node of type \"" + nodeName + "\" of the parameter!.\r\nINFO:operation name:" + pname + "    operation ID" + pID + "    class name:" + className + "    class ID:" + classID + "\r\n\r\n"; 
					logFile.Write (resInfo, resInfo.GetLength ());
					if (result == SUCCEED) result = IGNORED;
				}
			}
			if (j != m)
				continue;
			try
			{
				sql = "select * from parameter";									//设置查询字符串
				m_Ado.m_pRecordset = m_Ado.OpenRecordset(sql);						//打开记录集
				m_Ado.m_pRecordset->AddNew();										//添加新行
				m_Ado.m_pRecordset->PutCollect("名称", (_bstr_t)qname);				//设置名称字段内容
				m_Ado.m_pRecordset->PutCollect("ID", (_bstr_t)qID);					//设置ID字段内容
				m_Ado.m_pRecordset->PutCollect("类型", (_bstr_t)qtype);				//设置类型字段内容
				m_Ado.m_pRecordset->PutCollect("方向", (_bstr_t)qdirection);		//设置方向字段内容
				m_Ado.m_pRecordset->PutCollect("所属方法", (_bstr_t)pname);			//设置所属方法字段内容
				m_Ado.m_pRecordset->PutCollect("所属方法ID", (_bstr_t)pID);			//设置所属方法字段内容
				m_Ado.m_pRecordset->Update();										//更新记录集
				m_Ado.CloseRecordset();												//关闭记录集
			}
			catch(_com_error e)
			{
				AfxMessageBox(e.Description());										//弹出错误处理
				//log file
				resInfo = "ERROR:Fail to put operation parameter data into database! Ignore this database write.\r\nINFO:parameter name:" + qname + "    parameter ID" + qID +"    operation name:" + pname + "    operation ID" + pID + "    class name:" + className + "    class ID:" + classID + "\r\n\r\n"; 
				logFile.Write (resInfo, resInfo.GetLength ());
				if (result == SUCCEED) result = IGNORED;
			}
		}
		else
		{
			//logfile
			resInfo = "IGNORE:Ignore a information node of type \"" + nodeName + "\" of the operation!.\r\nINFO:operation name:" + pname + "    operation ID" + pID + "    class name:" + className + "    class ID:" + classID + "\r\n\r\n"; 
			logFile.Write (resInfo, resInfo.GetLength ());
			if (result == SUCCEED) result = IGNORED;
			break;
		}
	}
	return SUCCEED;
}

//********************************************************************//
//函数功能：对时间点节点进行判断分析，分析时间点的ID及覆盖生命线等信息//
//参数说明：pNode为此节点的指针                                       //
//          interactionName为此时间点所在交互的名称                   //
//          interactionID为此时间点所在交互的ID                       //
//          number为此时间点所在交互的内的序号                        //
//          brothers为此时间点所在交互内的兄弟节点                    //
//          返回值为处理结果                                          //
//********************************************************************//
unsigned int CUMLanalyserDlg::InteractionOSAnalyse(IXMLDOMNode *pNode, CString interactionName, CString interactionID, unsigned int number, IXMLDOMNodeList * brothers)
{
	long int n = -1, i = 0;
	CString nodeName = "", pID = "", pcovered = "", sql = "", temp = "", resInfo = "";
	HRESULT hr;
	BSTR text = NULL;								//节点值
	IXMLDOMNamedNodeMap *pAtts = NULL;				//属性节点列表
	IXMLDOMNode *aNode = NULL;
	unsigned int result = SUCCEED;
	
	//OS的属性分析
	hr = pNode->get_attributes (&pAtts);
	if (FAILED (hr))
	{
		AfxMessageBox ("Fail to get attributes of the node!");
		//log file		
		resInfo = "ERROR:Fail to get attributes of the OS node! Ignore all attributes of the node.\r\nINFO:interaction name:" + interactionName + "    interaction ID:" + interactionID + "\r\n\r\n"; 
		logFile.Write (resInfo, resInfo.GetLength ());
		return IGNORED;
	}
	hr = pAtts->getNamedItem(L"xmi:type",& aNode);
	if (FAILED (hr))
	{
		AfxMessageBox ("Fail to get type of the attributes of the class!");
		//log file		
		resInfo = "ERROR:Fail to get \"xmi:type\" of the node! Ignore all attributes of the node.\r\nINFO:interaction name:" + interactionName + "    interaction ID:" + interactionID + "\r\n\r\n"; 
		logFile.Write (resInfo, resInfo.GetLength ());
		return IGNORED;
	}
	hr = aNode->get_text(&text);
	if (FAILED (hr))
	{
		AfxMessageBox ("Fail to get the value of the attribute!");
		//log file		
		resInfo = "ERROR:Fail to get \"xmi:type\" of the node! Ignore all attributes of the node.\r\nINFO:interaction name:" + interactionName + "    interaction ID:" + interactionID + "\r\n\r\n"; 
		logFile.Write (resInfo, resInfo.GetLength ());
		return IGNORED;
	}
	nodeName.Format ("%S",text);
	if (nodeName.Compare ("uml:OccurrenceSpecification"))
	{
		//log file		
		resInfo = "IGNORE:Ignore a node of uml type \"" + nodeName +"\"  and its child nodes!\r\nINFO:interaction name:" + interactionName + "    interaction ID:" + interactionID + "\r\n\r\n"; 
		logFile.Write (resInfo, resInfo.GetLength ());
		return IGNORED;
	}
	hr = pAtts->get_length (&n);					// 获取属性节点个数
	if (FAILED (hr))
	{
		AfxMessageBox ("Fail to get number of the attributes of the node!");
		//log file		
		resInfo = "ERROR:Fail to get number of attributes of the OS node! Ignore this interaction OS.\r\nINFO:interaction name:" + interactionName + "    interaction ID:" + interactionID + "\r\n\r\n"; 
		logFile.Write (resInfo, resInfo.GetLength ());
		return IGNORED;
	}
	for (i = 0; i < n; i ++)
	{
		hr = pAtts->get_item (i, &aNode);//获取该节点对象集合中指定位置的节点
		if (FAILED (hr))
		{
			AfxMessageBox ("Fail to get the wanted attribute of the node!");
			//log file			
			temp.Format ("%d", i);
			resInfo = "ERROR:Fail to get the ith attribute of the OS node! Ignore this OS attribute.\r\nINFO:interaction name:" + interactionName + "    interaction ID:" + interactionID + "    i:" + temp + "\r\n\r\n"; 
			logFile.Write (resInfo, resInfo.GetLength ());
			if (result == SUCCEED) result = IGNORED;
			continue;
		}
		hr = aNode->get_nodeName (&bstr);			// 获取属性节点的名称
		if (FAILED (hr))
		{
			AfxMessageBox ("Fail to get name of the wanted attribute!");
			//log file			
			temp.Format ("%d", i);
			resInfo = "ERROR:Fail to get the ith attribute of the OS node! Ignore this OS attribute.\r\nINFO:interaction name:" + interactionName + "    interaction ID:" + interactionID + "    i:" + temp + "\r\n\r\n"; 
			logFile.Write (resInfo, resInfo.GetLength ());
			if (result == SUCCEED) result = IGNORED;
			continue;
		}
		nodeName.Format ("%S",bstr);
		text = NULL;
		hr = aNode->get_text (&text);				//获取属性节点的值
		if (FAILED (hr) || text == NULL)
		{
			AfxMessageBox ("Fail to get the value of wanted attribute's name!");
			//log file			
			temp.Format ("%d", i);
			resInfo = "ERROR:Fail to get the ith attribute of the OS node! Ignore this OS attribute.\r\nINFO:interaction name:" + interactionName + "    interaction ID:" + interactionID + "    i:" + temp + "\r\n\r\n"; 
			logFile.Write (resInfo, resInfo.GetLength ());
			if (result == SUCCEED) result = IGNORED;
			continue;
		}
		if (!nodeName.Compare ("xmi:id"))
		{
			pID.Format ("%S", text);
		}
		else if (!nodeName.Compare ("covered"))
		{
			pcovered.Format ("%S", text);
		}
		else if (nodeName.Compare ("xmi:type"))
		{
			//log file
			temp.Format ("%d", i);
			resInfo = "IGNORE:Ignore the  ith attribute of type \"" + nodeName + "\" of the OS node! Ignore this OS attribute.\r\nINFO:interaction name:" + interactionName + "    interaction ID:" + interactionID + "    i:" + temp + "\r\n\r\n"; 
			logFile.Write (resInfo, resInfo.GetLength ());
			if (result == SUCCEED) result = IGNORED;
		}
	}
	CString plifeline = FindLifeline (brothers, pcovered);
	CString pnumber = "";
	pnumber.Format ("%d", number);
	try
	{
		sql = "select * from occurrenceSpecification";							//设置查询字符串
		m_Ado.m_pRecordset = m_Ado.OpenRecordset(sql);							//打开记录集
		m_Ado.m_pRecordset->AddNew();											//添加新行
		m_Ado.m_pRecordset->PutCollect("ID", (_bstr_t)pID);						//设置ID字段内容
		m_Ado.m_pRecordset->PutCollect("覆盖生命线ID", (_bstr_t)pcovered);		//设置覆盖生命线ID字段内容
		m_Ado.m_pRecordset->PutCollect("覆盖生命线", (_bstr_t)plifeline);		//设置覆盖生命线字段内容
		m_Ado.m_pRecordset->PutCollect("所属交互", (_bstr_t)interactionName);	//设置所属交互字段内容
		m_Ado.m_pRecordset->PutCollect("所属交互ID", (_bstr_t)interactionID);	//设置所属交互ID字段内容
		m_Ado.m_pRecordset->PutCollect("所属交互内序号", (_bstr_t)pnumber);		//设置所属交互内序号字段内容
		m_Ado.m_pRecordset->Update();											//更新记录集
		m_Ado.CloseRecordset();													//关闭记录集
	}
	catch(_com_error e)
	{
		AfxMessageBox(e.Description());										//弹出错误处理
		//log file
		resInfo = "ERROR:Fail to put OS data into database! Ignore this database write.\r\nINFO:OS ID:" + pID + "    interaction name:" + interactionName + "    interaction ID:" + interactionID + "\r\n\r\n"; 
		logFile.Write (resInfo, resInfo.GetLength ());
		return IGNORED;
	}
	return result;
}

//********************************************************************//
//函数功能：对生命线节点进行判断分析，分析生命线的ID及其表示属性等信息//
//参数说明：pNode为此节点的指针                                       //
//          interactionName为此生命线所在交互的名称                   //
//          interactionID为此生命线所在交互的ID                       //
//          返回值为处理结果                                          //
//********************************************************************//
unsigned int CUMLanalyserDlg::InteractionLifelineAnalyse(IXMLDOMNode *pNode, CString interactionName, CString interactionID)
{
	long int n = -1, i = 0;
	CString nodeName = "", pname = "", pID = "", pvisibility = "", prepresent = "", sql = "", temp = "", resInfo = "";
	HRESULT hr;
	BSTR text = NULL;								//节点值
	IXMLDOMNamedNodeMap *pAtts = NULL;				//属性节点列表
	IXMLDOMNode *aNode = NULL;
	unsigned int result = SUCCEED;
	
	//生命线的属性分析
	hr = pNode->get_attributes (&pAtts);
	if (FAILED (hr))
	{
		AfxMessageBox ("Fail to get attributes of the node!");
		//log file
		resInfo = "ERROR:Fail to get attributes of the lifeline node! Ignore all attributes of the node.\r\nINFO:interaction name:" + interactionName + "    interaction ID:" + interactionID + "\r\n\r\n"; 
		logFile.Write (resInfo, resInfo.GetLength ());
		return IGNORED;
	}
	hr = pAtts->getNamedItem(L"xmi:type",& aNode);
	if (FAILED (hr))
	{
		AfxMessageBox ("Fail to get type of the attributes of the class!");
		//log file
		resInfo = "ERROR:Fail to get \"xmi:type\" of the node! Ignore all attributes of the node.\r\nINFO:interaction name:" + interactionName + "    interaction ID:" + interactionID + "\r\n\r\n"; 
		logFile.Write (resInfo, resInfo.GetLength ());
		return IGNORED;
	}
	hr = aNode->get_text(&text);
	if (FAILED (hr))
	{
		AfxMessageBox ("Fail to get the value of the attribute!");
		//log file
		resInfo = "ERROR:Fail to get \"xmi:type\" of the node! Ignore all attributes of the node.\r\nINFO:interaction name:" + interactionName + "    interaction ID:" + interactionID + "\r\n\r\n"; 
		logFile.Write (resInfo, resInfo.GetLength ());
		return IGNORED;
	}
	nodeName.Format ("%S",text);
	if (nodeName.Compare ("uml:Lifeline"))
	{
		//log file
		resInfo = "IGNORE:Ignore a node of uml type \"" + nodeName +"\"  and its child nodes!\r\nINFO:interaction name:" + interactionName + "    interaction ID:" + interactionID + "\r\n\r\n"; 
		logFile.Write (resInfo, resInfo.GetLength ());
		return IGNORED;
	}
	hr = pAtts->get_length (&n);					// 获取属性节点个数
	if (FAILED (hr))
	{
		AfxMessageBox ("Fail to get number of the attributes of the node!");
		//log file
		resInfo = "ERROR:Fail to get number of attributes of the lifeline node! Ignore this interaction lifeline.\r\nINFO:interaction name:" + interactionName + "    interaction ID:" + interactionID + "\r\n\r\n"; 
		logFile.Write (resInfo, resInfo.GetLength ());
		return IGNORED;
	}
	for (i = 0; i < n; i ++)
	{
		hr = pAtts->get_item (i, &aNode);
		if (FAILED (hr))
		{
			AfxMessageBox ("Fail to get the wanted attribute of the node!");
			//log file
			temp.Format ("%d", i);
			resInfo = "ERROR:Fail to get the ith attribute of the lifeline node! Ignore this lifeline attribute.\r\nINFO:interaction name:" + interactionName + "    interaction ID:" + interactionID + "    i:" + temp + "\r\n\r\n"; 
			logFile.Write (resInfo, resInfo.GetLength ());
			if (result == SUCCEED) result = IGNORED;
			continue;
		}
		hr = aNode->get_nodeName (&bstr);			// 获取属性节点的名称
		if (FAILED (hr))
		{
			AfxMessageBox ("Fail to get name of the wanted attribute!");
			//log file
			temp.Format ("%d", i);
			resInfo = "ERROR:Fail to get the ith attribute of the lifeline node! Ignore this lifeline attribute.\r\nINFO:interaction name:" + interactionName + "    interaction ID:" + interactionID + "    i:" + temp + "\r\n\r\n"; 
			logFile.Write (resInfo, resInfo.GetLength ());
			if (result == SUCCEED) result = IGNORED;
			continue;
		}
		nodeName.Format ("%S",bstr);
		text = NULL;
		hr = aNode->get_text (&text);				//获取属性节点的值
		if (FAILED (hr) || text == NULL)
		{
			AfxMessageBox ("Fail to get the value of wanted attribute's name!");
			//log file
			temp.Format ("%d", i);
			resInfo = "ERROR:Fail to get the ith attribute of the lifeline node! Ignore this lifeline attribute.\r\nINFO:interaction name:" + interactionName + "    interaction ID:" + interactionID + "    i:" + temp + "\r\n\r\n"; 
			logFile.Write (resInfo, resInfo.GetLength ());
			if (result == SUCCEED) result = IGNORED;
			continue;
		}
		if (!nodeName.Compare ("xmi:id"))
		{
			pID.Format ("%S", text);
		}
		else if (!nodeName.Compare ("name"))
		{
			pname.Format ("%S", text);
		}
		else if (!nodeName.Compare ("visibility"))
		{
			pvisibility.Format ("%S", text);
		}
			else if (!nodeName.Compare ("represents"))
		{
			prepresent.Format ("%S", text);
		}
		else if (nodeName.Compare ("xmi:type"))
		{
			//log file
			temp.Format ("%d", i);
			resInfo = "IGNORE:Ignore the  ith attribute of type \"" + nodeName + "\" of the lifeline node! Ignore this lifeline attribute.\r\nINFO:interaction name:" + interactionName + "    interaction ID:" + interactionID + "    i:" + temp + "\r\n\r\n"; 
			logFile.Write (resInfo, resInfo.GetLength ());
			if (result == SUCCEED) result = IGNORED;
		}
	}
	try
	{
		sql = "select * from lifeline";											//设置查询字符串
		m_Ado.m_pRecordset = m_Ado.OpenRecordset(sql);							//打开记录集
		m_Ado.m_pRecordset->AddNew();											//添加新行
		m_Ado.m_pRecordset->PutCollect("名称", (_bstr_t)pname);					//设置名称字段内容
		m_Ado.m_pRecordset->PutCollect("ID", (_bstr_t)pID);						//设置ID字段内容
		m_Ado.m_pRecordset->PutCollect("可见性", (_bstr_t)pvisibility);			//设置备注字段内容
		m_Ado.m_pRecordset->PutCollect("表示属性ID", (_bstr_t)prepresent);		//设置表示属性ID字段内容
		m_Ado.m_pRecordset->PutCollect("所属交互", (_bstr_t)interactionName);	//设置所属交互字段内容
		m_Ado.m_pRecordset->PutCollect("所属交互ID", (_bstr_t)interactionID);	//设置所属交互ID字段内容
		m_Ado.m_pRecordset->Update();											//更新记录集
		m_Ado.CloseRecordset();													//关闭记录集
	}
	catch(_com_error e)
	{
		AfxMessageBox(e.Description());										//弹出错误处理
		//log file
		resInfo = "ERROR:Fail to put lifeline data into database! Ignore this database write.\r\nINFO:lifeline name:" + pname + "    lifeline ID:" + pID + "    interaction name:" + interactionName + "    interaction ID:" + interactionID + "\r\n\r\n"; 
		logFile.Write (resInfo, resInfo.GetLength ());
		return IGNORED;
	}
	return result;
}

//********************************************************************//
//函数功能：对消息节点进行判断分析，分析消息的ID及收发事件等信息      //
//参数说明：pNode为此节点的指针                                       //
//          interactionName为此消息所在交互的名称                     //
//          interactionID为此消息所在交互的ID                         //
//          brothers为此时间点所在交互内的兄弟节点                    //
//          返回值为处理结果                                          //
//********************************************************************//
unsigned int CUMLanalyserDlg::InteractionMessageAnalyse(IXMLDOMNode *pNode, CString interactionName, CString interactionID, IXMLDOMNodeList * brothers)
{
	long int n = -1, i = 0;
	unsigned int result = SUCCEED, tempResult = SUCCEED;		//处理结果
	CString nodeName = "", pname = "", pID = "", pkind = "", psort = "", sql = "", temp = "", resInfo = "";
	CString psend = "", preceive = "", psendLifeline = "", preceiveLifeline = "", psendlID = "", preceivelID = "";
	HRESULT hr;
	VARIANT_BOOL b;
	BSTR text = NULL;								//节点值
	IXMLDOMNamedNodeMap *pAtts = NULL;				//属性节点列表
	IXMLDOMNode *aNode = NULL;
	IXMLDOMNodeList *pNodes = NULL;					//子节点列表
	
	//消息的属性分析
	hr = pNode->get_attributes (&pAtts);
	if (FAILED (hr))
	{
		AfxMessageBox ("Fail to get attributes of the node!");
		//log file
		resInfo = "ERROR:Fail to get attributes of the message node! Ignore all attributes of the node.\r\nINFO:interaction name:" + interactionName + "    interaction ID:" + interactionID + "\r\n\r\n"; 
		logFile.Write (resInfo, resInfo.GetLength ());
		return IGNORED;
	}
	hr = pAtts->get_length (&n);					// 获取属性节点个数
	if (FAILED (hr))
	{
		AfxMessageBox ("Fail to get number of the attributes of the node!");
		//log file
		resInfo = "ERROR:Fail to get number of attributes of the message node! Ignore this interaction message.\r\nINFO:interaction name:" + interactionName + "    interaction ID:" + interactionID + "\r\n\r\n"; 
		logFile.Write (resInfo, resInfo.GetLength ());
		return IGNORED;
	}
	for (i = 0; i < n; i ++)
	{
		hr = pAtts->get_item (i, &aNode);
		if (FAILED (hr))
		{
			AfxMessageBox ("Fail to get the wanted attribute of the node!");
			//log file
			temp.Format ("%d", i);
			resInfo = "ERROR:Fail to get the ith attribute of the message node! Ignore this message attribute.\r\nINFO:interaction name:" + interactionName + "    interaction ID:" + interactionID + "    i:" + temp + "\r\n\r\n"; 
			logFile.Write (resInfo, resInfo.GetLength ());
			if (result == SUCCEED) result = IGNORED;
			continue;
		}
		hr = aNode->get_nodeName (&bstr);			// 获取属性节点的名称
		if (FAILED (hr))
		{
			AfxMessageBox ("Fail to get name of the wanted attribute!");
			//log file
			temp.Format ("%d", i);
			resInfo = "ERROR:Fail to get the ith attribute of the message node! Ignore this message attribute.\r\nINFO:interaction name:" + interactionName + "    interaction ID:" + interactionID + "    i:" + temp + "\r\n\r\n"; 
			logFile.Write (resInfo, resInfo.GetLength ());
			if (result == SUCCEED) result = IGNORED;
			continue;
		}
		nodeName.Format ("%S",bstr);
		text = NULL;
		hr = aNode->get_text (&text);				//获取属性节点的值
		if (FAILED (hr) || text == NULL)
		{
			AfxMessageBox ("Fail to get the value of wanted attribute's name!");
			//log file
			temp.Format ("%d", i);
			resInfo = "ERROR:Fail to get the ith attribute of the message node! Ignore this message attribute.\r\nINFO:interaction name:" + interactionName + "    interaction ID:" + interactionID + "    i:" + temp + "\r\n\r\n"; 
			logFile.Write (resInfo, resInfo.GetLength ());
			if (result == SUCCEED) result = IGNORED;
			continue;
		}
		if (!nodeName.Compare ("xmi:id"))
		{
			pID.Format ("%S", text);
		}
		else if (!nodeName.Compare ("name"))
		{
			pname.Format ("%S", text);
		}
		else if (!nodeName.Compare ("messageKind"))
		{
			pkind.Format ("%S", text);
		}
		else if (!nodeName.Compare ("messageSort"))
		{
			psort.Format ("%S", text);
		}
		else if (!nodeName.Compare ("sendEvent"))
		{
			psend.Format ("%S", text);
		}
		else if (!nodeName.Compare ("receiveEvent"))
		{
			preceive.Format ("%S", text);
		}
		else if (nodeName.Compare ("xmi:type"))
		{
			//log file
			temp.Format ("%d", i);
			resInfo = "IGNORE:Ignore the  ith attribute of type \"" + nodeName + "\" of the message node! Ignore this message attribute.\r\nINFO:interaction name:" + interactionName + "    interaction ID:" + interactionID + "    i:" + temp + "\r\n\r\n"; 
			logFile.Write (resInfo, resInfo.GetLength ());
			if (result == SUCCEED) result = IGNORED;
			continue;
		}
	}
	psendLifeline = "";
	preceiveLifeline = "";
	psendlID = "";
	preceivelID = "";
	psendlID = FindOS (brothers, psend);
	if (psendlID.Compare (""))
		psendLifeline = FindLifeline (brothers, psendlID);
	preceivelID = FindOS (brothers, preceive);
	if (preceivelID.Compare (""))
		preceiveLifeline = FindLifeline (brothers, preceivelID);
	try
	{
		sql = "select * from message";											//设置查询字符串
		m_Ado.m_pRecordset = m_Ado.OpenRecordset(sql);							//打开记录集
		m_Ado.m_pRecordset->AddNew();											//添加新行
		m_Ado.m_pRecordset->PutCollect("名称", (_bstr_t)pname);					//设置名称字段内容
		m_Ado.m_pRecordset->PutCollect("ID", (_bstr_t)pID);						//设置ID字段内容
		m_Ado.m_pRecordset->PutCollect("种类", (_bstr_t)pkind);					//设置种类字段内容
		m_Ado.m_pRecordset->PutCollect("时序", (_bstr_t)psort);					//设置时序字段内容
		m_Ado.m_pRecordset->PutCollect("发送事件ID", (_bstr_t)psend);			//设置发送事件ID字段内容
		m_Ado.m_pRecordset->PutCollect("发送生命线", (_bstr_t)psendLifeline);	//设置发送生命线字段内容
		m_Ado.m_pRecordset->PutCollect("发送生命线ID", (_bstr_t)psendlID);		//设置发送生命线ID字段内容
		m_Ado.m_pRecordset->PutCollect("接收事件ID", (_bstr_t)preceive);		//设置接收事件ID字段内容
		m_Ado.m_pRecordset->PutCollect("接收生命线", (_bstr_t)preceiveLifeline);//设置接收生命线字段内容
		m_Ado.m_pRecordset->PutCollect("接收生命线ID", (_bstr_t)preceivelID);	//设置接收生命线ID字段内容
		m_Ado.m_pRecordset->PutCollect("所属交互", (_bstr_t)interactionName);	//设置所属交互字段内容
		m_Ado.m_pRecordset->PutCollect("所属交互ID", (_bstr_t)interactionID);	//设置所属交互ID字段内容
		m_Ado.m_pRecordset->Update();											//更新记录集
		m_Ado.CloseRecordset();													//关闭记录集
	}
	catch(_com_error e)
	{
		AfxMessageBox(e.Description());										//弹出错误处理
		//log file
		resInfo = "ERROR:Fail to put message data into database! Ignore this database write.\r\nINFO:message name:" + pname + "    message ID:" + pID + "    interaction name:" + interactionName + "    interaction ID:" + interactionID + "\r\n\r\n"; 
		logFile.Write (resInfo, resInfo.GetLength ());
		return IGNORED;
	}

	//消息的参数分析
	hr = pNode->hasChildNodes (&b);											//判断节点是否有孩子
	if (FAILED (hr))
	{
		AfxMessageBox ("Fail to find whether the node has child!");
		//log file
		resInfo = "ERROR:Fail to find whether the node has child! Ignore all these child nodes.\r\nINFO:message name:" + pname + "    message ID:" + pID + "    interaction name:" + interactionName + "    interaction ID:" + interactionID + "\r\n\r\n"; 
		logFile.Write (resInfo, resInfo.GetLength ());
		return IGNORED;
	}
	if (!b)											//没有子节点(即没有消息参数)
	{
		return result;
	}

	hr = pNode->get_childNodes (&pNodes);			//获取子节点
	if (FAILED (hr))
	{
		AfxMessageBox ("Fail to get child nodes of the node!");
		//log file		
		resInfo = "ERROR:Fail to get child nodes of the message!Ignore all these child nodes.\r\nINFO:message name:" + pname + "    message ID:" + pID + "    interaction name:" + interactionName + "    interaction ID:" + interactionID + "\r\n\r\n"; 
		logFile.Write (resInfo, resInfo.GetLength ());
		return IGNORED;
	}
	hr = pNodes->get_length (&n);					// 获取子节点个数
	if (FAILED (hr))
	{
		AfxMessageBox ("Fail to get number of the child nodes of the node!");
		//log file
		resInfo = "ERROR:Fail to get number of the child nodes of the message! Ignore all these child nodes.\r\nINFO:message name:" + pname + "    message ID:" + pID + "    interaction name:" + interactionName + "    interaction ID:" + interactionID + "\r\n\r\n"; 
		logFile.Write (resInfo, resInfo.GetLength ());
		return IGNORED;
	}
	for (i = 0; i < n; i ++)
	{
		hr = pNodes->get_item (i, &aNode);
		if (FAILED (hr))
		{
			AfxMessageBox ("Fail to get the wanted child node!");
			//log file
			temp.Format ("%d", i);
			resInfo = "ERROR:Fail to get the ith child node of the message! Ignore this child node.\r\nINFO:message name:" + pname + "    message ID:" + pID + "    interaction name:" + interactionName + "    interaction ID:" + interactionID + "    i:" + temp + "\r\n\r\n"; 
			logFile.Write (resInfo, resInfo.GetLength ());
			if (result == SUCCEED) result = IGNORED;
			continue;
		}
		hr = aNode->get_nodeName (&bstr);			// 获取子节点的名称
		if (FAILED (hr))
		{
			AfxMessageBox ("Fail to get name of the wanted chile node!");
			//log file
			temp.Format ("%d", i);
			resInfo = "ERROR:Fail to get the ith child node of the message! Ignore this child node.\r\nINFO:message name:" + pname + "    message ID:" + pID + "    interaction name:" + interactionName + "    interaction ID:" + interactionID + "    i:" + temp + "\r\n\r\n"; 
			logFile.Write (resInfo, resInfo.GetLength ());
			if (result == SUCCEED) result = IGNORED;
			continue;
		}
		nodeName.Format ("%S",bstr);
		text = NULL;
		hr = aNode->get_text (&text);						//获取节点的值
		if (FAILED (hr) || text == NULL)
		{
			AfxMessageBox ("Fail to get the value of wanted child's name!");
			//log file
			temp.Format ("%d", i);
			resInfo = "ERROR:Fail to get the ith child node of the message! Ignore this child node.\r\nINFO:message name:" + pname + "    message ID:" + pID + "    interaction name:" + interactionName + "    interaction ID:" + interactionID + "    i:" + temp + "\r\n\r\n"; 
			logFile.Write (resInfo, resInfo.GetLength ());
			if (result == SUCCEED) result = IGNORED;
			continue;
		}
		if (!nodeName.Compare ("argument"))			//消息参数分析
		{
			tempResult = MessageArgumentAnalyse (aNode, pname, pID);
			if (tempResult <= result) result = tempResult;
		}
		else
		{
			//log file
			temp.Format ("%d", i);
			resInfo = "IGNORE:Ignore the  ith child node of type \"" + nodeName + "\" of the message node! Ignore this child node.\r\nINFO:message name:" + pname + "    message ID:" + pID + "    interaction name:" + interactionName + "    interaction ID:" + interactionID + "    i:" + temp + "\r\n\r\n"; 
			logFile.Write (resInfo, resInfo.GetLength ());
			if (result == SUCCEED) result = IGNORED;
		}
	}
	return result;
}

//********************************************************************//
//函数功能：对门节点进行判断分析，分析门的ID及名称等信息              //
//参数说明：pNode为此节点的指针                                       //
//          interactionName为此门所在交互的名称                       //
//          interactionID为此门所在交互的ID                           //
//          返回值为处理结果                                          //
//********************************************************************//
unsigned int CUMLanalyserDlg::InteractionGateAnalyse(IXMLDOMNode *pNode, CString interactionName, CString interactionID)
{
	long int n = -1, i = 0;
	CString nodeName = "", pname = "", pID = "", pvisibility = "", sql = "", temp = "", resInfo = "";
	HRESULT hr;
	BSTR text = NULL;								//节点值
	IXMLDOMNamedNodeMap *pAtts = NULL;				//属性节点列表
	IXMLDOMNode *aNode = NULL;
	unsigned int result = SUCCEED;
	
	//门的属性分析
	hr = pNode->get_attributes (&pAtts);
	if (FAILED (hr))
	{
		AfxMessageBox ("Fail to get attributes of the node!");
		//log file
		resInfo = "ERROR:Fail to get attributes of the gate node! Ignore all attributes of the node.\r\nINFO:interaction name:" + interactionName + "    interaction ID:" + interactionID + "\r\n\r\n"; 
		logFile.Write (resInfo, resInfo.GetLength ());
		return IGNORED;
	}
	hr = pAtts->getNamedItem(L"xmi:type",& aNode);
	if (FAILED (hr))
	{
		AfxMessageBox ("Fail to get type of the attributes of the gate!");
		//log file
		resInfo = "ERROR:Fail to get \"xmi:type\" of the node! Ignore all attributes of the node.\r\nINFO:interaction name:" + interactionName + "    interaction ID:" + interactionID + "\r\n\r\n"; 
		logFile.Write (resInfo, resInfo.GetLength ());
		return IGNORED;
	}
	hr = aNode->get_text(&text);
	nodeName.Format ("%S",text);
	if (nodeName.Compare ("uml:Gate"))
	{
		//log file		
		resInfo = "IGNORE:Ignore a node of uml type \"" + nodeName +"\" and its child nodes.\r\nINFO:interaction name:" + interactionName + "    interaction ID:" + interactionID + "\r\n\r\n"; 
		logFile.Write (resInfo, resInfo.GetLength ());
		return IGNORED;
	}
	hr = pAtts->get_length (&n);					// 获取属性节点个数
	if (FAILED (hr))
	{
		AfxMessageBox ("Fail to get number of the attributes of the node!");
		//log file
		resInfo = "ERROR:Fail to get number of attributes of the gate node! Ignore this interaction gate.\r\nINFO:interaction name:" + interactionName + "    interaction ID:" + interactionID + "\r\n\r\n"; 
		logFile.Write (resInfo, resInfo.GetLength ());
		return IGNORED;
	}
	for (i = 0; i < n; i ++)
	{
		hr = pAtts->get_item (i, &aNode);
		if (FAILED (hr))
		{
			AfxMessageBox ("Fail to get the wanted attribute of the node!");
			//log file
			temp.Format ("%d", i);
			resInfo = "ERROR:Fail to get the ith attribute of the gate node! Ignore this attribute.\r\nINFO:interaction name:" + interactionName + "    interaction ID:" + interactionID + "    i:" + temp + "\r\n\r\n"; 
			logFile.Write (resInfo, resInfo.GetLength ());
			return IGNORED;
		}
		hr = aNode->get_nodeName (&bstr);			// 获取属性节点的名称
		if (FAILED (hr))
		{
			AfxMessageBox ("Fail to get name of the wanted attribute!");
			//log file
			temp.Format ("%d", i);
			resInfo = "ERROR:Fail to get the ith attribute of the gate node! Ignore this attribute.\r\nINFO:interaction name:" + interactionName + "    interaction ID:" + interactionID + "    i:" + temp + "\r\n\r\n"; 
			logFile.Write (resInfo, resInfo.GetLength ());
			return IGNORED;
		}
		nodeName.Format ("%S",bstr);
		text = NULL;
		hr = aNode->get_text (&text);				//获取属性节点的值
		if (FAILED (hr) || text == NULL)
		{
			AfxMessageBox ("Fail to get the value of wanted attribute's name!");
			//log file
			temp.Format ("%d", i);
			resInfo = "ERROR:Fail to get the ith attribute of the gate node! Ignore this attribute.\r\nINFO:interaction name:" + interactionName + "    interaction ID:" + interactionID + "    i:" + temp + "\r\n\r\n"; 
			logFile.Write (resInfo, resInfo.GetLength ());
			return IGNORED;
		}
		if (!nodeName.Compare ("xmi:id"))
		{
			pID.Format ("%S", text);
		}
		else if (!nodeName.Compare ("name"))
		{
			pname.Format ("%S", text);
		}
		else if (!nodeName.Compare ("visibility"))
		{
			pvisibility.Format ("%S", text);
		}
		else if (nodeName.Compare ("xmi:type"))
		{
			//log file
			temp.Format ("%d", i);
			resInfo = "IGNORE:Ignore the ith attribute of type \"" + nodeName + "\" of the gate node! Ignore this gate attribute.\r\nINFO:interaction name:" + interactionName + "    interaction ID:" + interactionID + "    i:" + temp + "\r\n\r\n"; 
			logFile.Write (resInfo, resInfo.GetLength ());
			if (result == SUCCEED) result = IGNORED;
			continue;
		}
	}
	try
	{
		sql = "select * from gate";											//设置查询字符串
		m_Ado.m_pRecordset = m_Ado.OpenRecordset(sql);						//打开记录集
		m_Ado.m_pRecordset->AddNew();										//添加新行
		m_Ado.m_pRecordset->PutCollect("名称", (_bstr_t)pname);				//设置名称字段内容
		m_Ado.m_pRecordset->PutCollect("ID", (_bstr_t)pID);					//设置ID字段内容
		m_Ado.m_pRecordset->PutCollect("可见性", (_bstr_t)pvisibility);		//设置备注字段内容
		m_Ado.m_pRecordset->PutCollect("所属交互", (_bstr_t)interactionName);		//设置所属交互字段内容
		m_Ado.m_pRecordset->PutCollect("所属交互ID", (_bstr_t)interactionID);		//设置所属交互ID字段内容
		m_Ado.m_pRecordset->Update();										//更新记录集
		m_Ado.CloseRecordset();												//关闭记录集
	}
	catch(_com_error e)
	{
		AfxMessageBox(e.Description());										//弹出错误处理
		//log file
		resInfo = "ERROR:Fail to put gate data into database! Ignore this database write.\r\nINFO:gate name:" + pname + "    gate ID:" + pID + "    interaction name:" + interactionName + "    interaction ID:" + interactionID + "\r\n\r\n"; 
		logFile.Write (resInfo, resInfo.GetLength ());
		return IGNORED;
	}
	return SUCCEED;
}

//********************************************************************//
//函数功能：对组合片段节点进行判断分析，分析组合片段的ID、类型等信息  //
//参数说明：pNode为此节点的指针                                       //
//          interactionName为此片段所在交互的名称                     //
//          interactionID为此片段所在交互的ID                         //
//          返回值为处理结果                                          //
//********************************************************************//
unsigned int CUMLanalyserDlg::InteractionCFAnalyse(IXMLDOMNode *pNode, CString interactionName, CString interactionID)
{
	long int n = -1, i = 0;
	unsigned int result = SUCCEED;					//处理结果
	BOOL isUpdated = FALSE;
	CString resInfo = "", temp = "", nodeName = "", pID = "", pname = "", pcovered = "", pvisibility = "", ptype = "", sql = "";
	HRESULT hr;
	VARIANT_BOOL b;
	BSTR text = NULL;								//节点值
	IXMLDOMNamedNodeMap *pAtts = NULL;				//属性节点列表
	IXMLDOMNode *aNode = NULL, *bNode = NULL;
	IXMLDOMNodeList *pNodes = NULL;					//子节点列表
	
	//组合片段属性的属性分析
	hr = pNode->get_attributes (&pAtts);
	if (FAILED (hr))
	{
		AfxMessageBox ("Fail to get attributes of the node!");
		//log file
		resInfo = "ERROR:Fail to get attributes of the combined fragment node! Ignore all attributes of the node.\r\nINFO:interaction name:" + interactionName + "    interaction ID:" + interactionID + "\r\n\r\n"; 
		logFile.Write (resInfo, resInfo.GetLength ());
		return IGNORED;
	}
	hr = pAtts->getNamedItem(L"xmi:type",& aNode);
	if (FAILED (hr))
	{
		AfxMessageBox ("Fail to get type of the attributes of the class!");
		//log file
		resInfo = "ERROR:Fail to get \"xmi:type\" of the node! Ignore all attributes of the node.\r\nINFO:interaction name:" + interactionName + "    interaction ID:" + interactionID + "\r\n\r\n"; 
		logFile.Write (resInfo, resInfo.GetLength ());
		return IGNORED;
	}
	hr = aNode->get_text(&text);
	temp.Format ("%S",text);
	hr = pAtts->get_length (&n);					// 获取属性节点个数
	if (FAILED (hr))
	{
		AfxMessageBox ("Fail to get number of the attributes of the node!");
		//log file
		resInfo = "ERROR:Fail to get number of attributes of the combined fragment node! Ignore this combined fragment.\r\nINFO:interaction name:" + interactionName + "    interaction ID:" + interactionID + "\r\n\r\n"; 
		logFile.Write (resInfo, resInfo.GetLength ());
		return IGNORED;
	}
	for (i = 0; i < n; i ++)
	{
		hr = pAtts->get_item (i, &aNode);
		if (FAILED (hr))
		{
			AfxMessageBox ("Fail to get the wanted attribute of the node!");
			//log file
			temp.Format ("%d", i);
			resInfo = "ERROR:Fail to get the ith attribute of the combined fragment node! Ignore this combined fragment attribute.\r\nINFO:interaction name:" + interactionName + "    interaction ID:" + interactionID + "    i:" + temp + "\r\n\r\n"; 
			logFile.Write (resInfo, resInfo.GetLength ());
			if (result == SUCCEED) result = IGNORED;
			continue;
		}
		hr = aNode->get_nodeName (&bstr);			// 获取属性节点的名称
		if (FAILED (hr))
		{
			AfxMessageBox ("Fail to get name of the wanted attribute!");
			//log file
			temp.Format ("%d", i);
			resInfo = "ERROR:Fail to get the ith attribute of the combined fragment node! Ignore this combined fragment attribute.\r\nINFO:interaction name:" + interactionName + "    interaction ID:" + interactionID + "    i:" + temp + "\r\n\r\n"; 
			logFile.Write (resInfo, resInfo.GetLength ());
			if (result == SUCCEED) result = IGNORED;
			continue;
		}
		nodeName.Format ("%S",bstr);
		text = NULL;
		hr = aNode->get_text (&text);				//获取属性节点的值
		if (FAILED (hr) || text == NULL)
		{
			AfxMessageBox ("Fail to get the value of wanted attribute's name!");
			//log file
			temp.Format ("%d", i);
			resInfo = "ERROR:Fail to get the ith attribute of the combined fragment node! Ignore this combined fragment attribute.\r\nINFO:interaction name:" + interactionName + "    interaction ID:" + interactionID + "    i:" + temp + "\r\n\r\n"; 
			logFile.Write (resInfo, resInfo.GetLength ());
			if (result == SUCCEED) result = IGNORED;
			continue;
		}
		if (!nodeName.Compare ("xmi:id"))
		{
			pID.Format ("%S", text);
		}		
		else if (! nodeName.Compare ("name"))
		{
			pname.Format ("%S", text);
		}
		else if (! nodeName.Compare ("visibility"))
		{
			pvisibility.Format ("%S", text);
		}
		else if (! nodeName.Compare ("interactionOperator"))
		{
			ptype.Format ("%S", text);
		}
		else if (nodeName.Compare ("xmi:type"))
		{
			//log file
			temp.Format ("%d", i);
			resInfo = "IGNORE:Ignore the ith attribute of type \"" + nodeName + "\" of the combined fragment node! Ignore this combined fragment attribute.\r\nINFO:interaction name:" + interactionName + "    interaction ID:" + interactionID + "    i:" + temp + "\r\n\r\n"; 
			logFile.Write (resInfo, resInfo.GetLength ());
			if (result == SUCCEED) result = IGNORED;
		}
	}
	try
	{
		sql = "select * from combinedFragment";									//设置查询字符串
		m_Ado.m_pRecordset = m_Ado.OpenRecordset(sql);							//打开记录集
		m_Ado.m_pRecordset->AddNew();											//添加新行
		m_Ado.m_pRecordset->PutCollect("ID", (_bstr_t)pID);						//设置ID字段内容
		m_Ado.m_pRecordset->PutCollect("名称", (_bstr_t)pname);					//设置名称字段内容
		m_Ado.m_pRecordset->PutCollect("可见性", (_bstr_t)pvisibility);			//设置可见性字段内容
		m_Ado.m_pRecordset->PutCollect("类型", (_bstr_t)ptype);					//设置类型字段内容
		m_Ado.m_pRecordset->PutCollect("所属交互", (_bstr_t)interactionName);	//设置所属交互字段内容
		m_Ado.m_pRecordset->PutCollect("所属交互ID", (_bstr_t)interactionID);	//设置所属交互字段内容
		//m_Ado.m_pRecordset->Update();											//更新记录集
		//m_Ado.CloseRecordset();												//关闭记录集
	}
	catch(_com_error e)
	{
		AfxMessageBox(e.Description());										//弹出错误处理
		//log file
		resInfo = "ERROR:Fail to put combined fragment data into database! Ignore this database write.\r\nINFO:combined fragment name:" + pname + "    combined fragment ID:" + pID + "    interaction name:" + interactionName + "    interaction ID:" + interactionID + "\r\n\r\n"; 
		logFile.Write (resInfo, resInfo.GetLength ());
		return IGNORED;
	}

	//组合片段的覆盖生命线及约束条件的分析
	hr = pNode->hasChildNodes (&b);											//判断节点是否有孩子
	if (FAILED (hr))
	{
		AfxMessageBox ("Fail to find whether the node has child!");
		//log file
	}
	if (!b)											//没有子节点(即没有成员属性和方法)
	{
		try
		{
			m_Ado.m_pRecordset->Update();										//更新记录集
			m_Ado.CloseRecordset();												//关闭记录集
		}
		catch(_com_error e)
		{
			AfxMessageBox(e.Description()); //弹出错误处理	
			resInfo = "ERROR:Fail to put combined fragment data into database! Ignore this database write.\r\nINFO:combined fragment name:" + pname + "    combined fragment ID:" + pID + "    interaction name:" + interactionName + "    interaction ID:" + interactionID + "\r\n\r\n"; 
			logFile.Write (resInfo, resInfo.GetLength ());
			return IGNORED;
		}
		return result;
	}

	hr = pNode->get_childNodes (&pNodes);			//获取子节点
	if (FAILED (hr))
	{
		AfxMessageBox ("Fail to get attributes of the node!");
		//log file
		resInfo = "ERROR:Fail to get child nodes of the combined fragment! Ignore all these child nodes.\r\nINFO:combined fragment name:" + pname + "    combined fragment ID:" + pID + "    interaction name:" + interactionName + "    interaction ID:" + interactionID + "\r\n\r\n"; 
		logFile.Write (resInfo, resInfo.GetLength ());
		return IGNORED;
	}
	hr = pNodes->get_length (&n);					// 获取子节点个数
	if (FAILED (hr))
	{
		AfxMessageBox ("Fail to get number of the attributes of the node!");
		//log file
		resInfo = "ERROR:Fail to get number of the child nodes of combined fragment! Ignore all these child nodes.\r\nINFO:combined fragment name:" + pname + "    combined fragment ID:" + pID + "    interaction name:" + interactionName + "    interaction ID:" + interactionID + "\r\n\r\n"; 
		logFile.Write (resInfo, resInfo.GetLength ());
		return IGNORED;
	}
	for (i = 0; i < n; i ++)
	{

		hr = pNodes->get_item (i, &aNode);
		if (FAILED (hr))
		{
			AfxMessageBox ("Fail to get the wanted child node!");
			//log file
			temp.Format ("%d", i);
			resInfo = "ERROR:Fail to get the ith child node of the combined fragment! Ignore this child node.\r\nINFO:combined fragment name:" + pname + "    combined fragment ID:" + pID + "    interaction name:" + interactionName + "    interaction ID:" + interactionID + "    i:" + temp + "\r\n\r\n"; 
			logFile.Write (resInfo, resInfo.GetLength ());
			if (result == SUCCEED) result = IGNORED;
			continue;
		}
		hr = aNode->get_nodeName (&bstr);			// 获取子节点的名称
		if (FAILED (hr))
		{
			AfxMessageBox ("Fail to get name of the wanted chile node!");
			//log file
			temp.Format ("%d", i);
			resInfo = "ERROR:Fail to get the ith child node of the combined fragment! Ignore this child node.\r\nINFO:combined fragment name:" + pname + "    combined fragment ID:" + pID + "    interaction name:" + interactionName + "    interaction ID:" + interactionID + "    i:" + temp + "\r\n\r\n"; 
			logFile.Write (resInfo, resInfo.GetLength ());
			if (result == SUCCEED) result = IGNORED;
			continue;
		}
		nodeName.Format ("%S",bstr);
		text = NULL;
		hr = aNode->get_text (&text);						//获取属性节点的值
		if (FAILED (hr) || text == NULL)
		{
			AfxMessageBox ("Fail to get the value of wanted child's name!");
			//log file
			temp.Format ("%d", i);
			resInfo = "ERROR:Fail to get the ith child node of the combined fragment! Ignore this child node.\r\nINFO:combined fragment name:" + pname + "    combined fragment ID:" + pID + "    interaction name:" + interactionName + "    interaction ID:" + interactionID + "    i:" + temp + "\r\n\r\n"; 
			logFile.Write (resInfo, resInfo.GetLength ());
			if (result == SUCCEED) result = IGNORED;
			continue;
		}
		if (!nodeName.Compare ("covered"))			//成员属性类型分析
		{
			hr = aNode->get_attributes (&pAtts);
			if (FAILED (hr))
			{
				AfxMessageBox ("Failed to get attributes of the node.");
				//logfile
				resInfo = "ERROR:Fail to get the \"covered\" lifeline information of the combined fragment! Ignore this information.\r\nINFO:combined fragment name:" + pname + "    combined fragment ID:" + pID + "    interaction name:" + interactionName + "    interaction ID:" + interactionID + "\r\n\r\n"; 
				logFile.Write (resInfo, resInfo.GetLength ());
				if (result == SUCCEED) result = IGNORED;
				continue;
			}
			hr = pAtts->getNamedItem(L"xmi:idref",& bNode);
			if (FAILED (hr))
			{
				AfxMessageBox ("Failed to get wanted attribute of the node.");
				//logfile
				resInfo = "ERROR:Fail to get the \"covered\" lifeline information of the combined fragment! Ignore this information.\r\nINFO:combined fragment name:" + pname + "    combined fragment ID:" + pID + "    interaction name:" + interactionName + "    interaction ID:" + interactionID + "\r\n\r\n"; 
				logFile.Write (resInfo, resInfo.GetLength ());
				if (result == SUCCEED) result = IGNORED;
				continue;
			}
			hr = bNode->get_text(&text);
			if (text != NULL)
			{
				temp.Format ("%S", text);
			}
			try
			{
				m_Ado.m_pRecordset->PutCollect("覆盖生命线ID", (_bstr_t)temp);	//添加新记录
				m_Ado.m_pRecordset->Update();									//更新记录集
				m_Ado.CloseRecordset();											//关闭记录集
				isUpdated = TRUE;
			}
			catch(_com_error e)
			{
				AfxMessageBox(e.Description()); //弹出错误处理
				resInfo = "ERROR:Fail to the covered lifeline data of the combined fragment into database! Ignore this database write.\r\nINFO:covered lifeline ID:" + temp + "    combined fragment name:" + pname + "    combined fragment ID:" + pID + "    interaction name:" + interactionName + "    interaction ID:" + interactionID + "\r\n\r\n"; 
				logFile.Write (resInfo, resInfo.GetLength ());
				return IGNORED;
			}
		}
		else if (! nodeName.Compare ("operand"))
		{
			if (! isUpdated)
			{
				try
				{
					m_Ado.m_pRecordset->Update();										//更新记录集
					m_Ado.CloseRecordset();												//关闭记录集
					isUpdated = TRUE;
				}
				catch(_com_error e)
				{
					AfxMessageBox(e.Description()); //弹出错误处理
					resInfo = "ERROR:Fail to the covered lifeline data of the combined fragment into database! Ignore this database write.\r\nINFO:covered lifeline ID:" + temp + "    combined fragment name:" + pname + "    combined fragment ID:" + pID + "    interaction name:" + interactionName + "    interaction ID:" + interactionID + "\r\n\r\n"; 
					logFile.Write (resInfo, resInfo.GetLength ());
					return IGNORED;
				}
			}
			CFOperandAnalyse (aNode, pname, pID);		//操作对象分析
		}
		else
		{
			//logfile
			resInfo = "IGNORE:Ignore the  ith child of type \"" + nodeName + "\" of the combined fragment node and its child nodes.\r\nINFO:combined fragment name:" + pname + "    combined fragment ID:" + pID + "    interaction name:" + interactionName + "    interaction ID:" + interactionID + "\r\n\r\n"; 
			logFile.Write (resInfo, resInfo.GetLength ());
			if (result == SUCCEED) result = IGNORED;
		}
	}
	return SUCCEED;
}

//********************************************************************//
//函数功能：对角色节点进行判断分析，分析角色的ID及名称等信息          //
//参数说明：pNode为此节点的指针                                       //
//          parentName为此角色所在父节点的名称                        //
//          parentID为此角色所在父节点的ID                            //
//          返回值为处理结果                                          //
//********************************************************************//
unsigned int CUMLanalyserDlg::ActorAnalyse(IXMLDOMNode *pNode, CString parentName, CString parentID)
{
	long int n = -1, i = 0;
	CString nodeName = "", pname = "", pID = "", pvisibility = "", sql = "", temp = "", resInfo = "";
	HRESULT hr;
	BSTR text = NULL;								//节点值
	IXMLDOMNamedNodeMap *pAtts = NULL;				//属性节点列表
	IXMLDOMNode *aNode = NULL;
	RESULT result = SUCCEED;
	
	//角色的属性分析
	hr = pNode->get_attributes (&pAtts);
	if (FAILED (hr))
	{
		AfxMessageBox ("Fail to get attributes of the node!");
		//log file
		resInfo = "ERROR:Fail to get attributes of the actor node! Ignore all attributes of the node.\r\nINFO:parent name:" + parentName + "    parent ID:" + parentID + "\r\n\r\n"; 
		logFile.Write (resInfo, resInfo.GetLength ());
		return IGNORED;
	}
	hr = pAtts->get_length (&n);					// 获取属性节点个数
	if (FAILED (hr))
	{
		AfxMessageBox ("Fail to get number of the attributes of the node!");
		//log file
		resInfo = "ERROR:Fail to get number of attributes of the actor node! Ignore this actor.\r\nINFO:parent name:" + parentName + "    parent ID:" + parentID + "\r\n\r\n"; 
		logFile.Write (resInfo, resInfo.GetLength ());
		return IGNORED;
	}
	for (i = 0; i < n; i ++)
	{
		hr = pAtts->get_item (i, &aNode);//获取该节点对象集合中指定位置的节点
		if (FAILED (hr))
		{
			AfxMessageBox ("Fail to get the wanted attribute of the node!");
			//log file
			temp.Format ("%d", i);
			resInfo = "ERROR:Fail to get the ith attribute of the actor node! Ignore this actor attribute.\r\nINFO:parent name:" + parentName + "    parent ID:" + parentID + "    i:" + temp + "\r\n\r\n"; 
			logFile.Write (resInfo, resInfo.GetLength ());
			return IGNORED;
		}
		hr = aNode->get_nodeName (&bstr);			// 获取属性节点的名称
		if (FAILED (hr))
		{
			AfxMessageBox ("Fail to get name of the wanted attribute!");
			//log file
		}
		nodeName.Format ("%S",bstr);
		text = NULL;
		hr = aNode->get_text (&text);				//获取属性节点的值
		if (FAILED (hr) || text == NULL)
		{
			AfxMessageBox ("Fail to get the value of wanted attribute's name!");
			//log file
		}
		if (!nodeName.Compare ("xmi:id"))
		{
			pID.Format ("%S", text);
		}
		else if (!nodeName.Compare ("name"))
		{
			pname.Format ("%S", text);
		}
		else if (!nodeName.Compare ("visibility"))
		{
			pvisibility.Format ("%S", text);
		}
		else if (nodeName.Compare ("xmi:type"))
		{
			//log file
			temp.Format ("%d", i);
			resInfo = "IGNORE:Ignore the  ith attribute of type \"" + nodeName + "\" of the actor node! Ignore this actor attribute.\r\nINFO:parent name:" + parentName + "    parent ID:" + parentID + "    i:" + temp + "\r\n\r\n"; 
			logFile.Write (resInfo, resInfo.GetLength ());
			if (result == SUCCEED) result = IGNORED;
		}
	}
	try
	{
		sql = "select * from actor";										//设置查询字符串
		m_Ado.m_pRecordset = m_Ado.OpenRecordset(sql);						//打开记录集
		m_Ado.m_pRecordset->AddNew();										//添加新行
		m_Ado.m_pRecordset->PutCollect("名称", (_bstr_t)pname);				//设置名称字段内容
		m_Ado.m_pRecordset->PutCollect("ID", (_bstr_t)pID);					//设置ID字段内容
		m_Ado.m_pRecordset->PutCollect("可见性", (_bstr_t)pvisibility);		//设置备注字段内容
		m_Ado.m_pRecordset->PutCollect("所属包", (_bstr_t)parentName);		//设置所属包字段内容
		m_Ado.m_pRecordset->PutCollect("所属包ID", (_bstr_t)parentID);		//设置所属包ID字段内容
		m_Ado.m_pRecordset->Update();										//更新记录集
		m_Ado.CloseRecordset();												//关闭记录集
	}
	catch(_com_error e)
	{
		AfxMessageBox(e.Description());										//弹出错误处理
		//log file
		resInfo = "IGNORE:Fail to put actor data into database! Ignore this database write.\r\nINFO:actor name:" + pname + "    actor ID:" + pID + "    parent name:" + parentName + "    parent ID:" + parentID + "    i:" + temp + "\r\n\r\n"; 
		logFile.Write (resInfo, resInfo.GetLength ());
		if (result == SUCCEED) result = IGNORED;
	}
	return SUCCEED;
}

//********************************************************************//
//函数功能：对合作属性节点进行判断分析，分析合作属性的ID及类型等信息  //
//参数说明：pNode为此节点的指针                                       //
//          collaborationName为此合作属性所在合作的名称               //
//          collaborationID为此合作属性所在合作的ID                   //
//          返回值为处理结果                                          //
//********************************************************************//
unsigned int CUMLanalyserDlg::CollaborationAttributeAnalyse(IXMLDOMNode *pNode, CString collaborationName, CString collaborationID)
{
	long int n = -1, i = 0;
	unsigned int result = SUCCEED;					//处理结果
	BOOL isAssociated = FALSE;
	CString temp = "", nodeName = "", pID = "", sql = "", pdefault = "", resInfo = "";
	HRESULT hr;
	VARIANT_BOOL b;
	BSTR text = NULL;								//节点值
	IXMLDOMNamedNodeMap *pAtts = NULL;				//属性节点列表
	IXMLDOMNode *aNode = NULL, *bNode = NULL;
	IXMLDOMNodeList *pNodes = NULL;					//子节点列表
	
	//合作属性的属性分析
	hr = pNode->get_attributes (&pAtts);
	if (FAILED (hr))
	{
		AfxMessageBox ("Fail to get attributes of the node!");
		//log file
		resInfo = "ERROR:Fail to get attributes of the collaboration attribute node! Ignore all attributes of the node.\r\nINFO:collaboration name:" + collaborationName + "    collaboration ID:" + collaborationID + "\r\n\r\n"; 
		logFile.Write (resInfo, resInfo.GetLength ());
		return IGNORED;
	}
	hr = pAtts->getNamedItem(L"xmi:type",& aNode);
	if (FAILED (hr))
	{
		AfxMessageBox ("Fail to get type of the attributes of the class!");
		//log file
		resInfo = "ERROR:Fail to get \"xmi:type\" of the collaboration attribute node! Ignore all attributes of the node.\r\nINFO:collaboration name:" + collaborationName + "    collaboration ID:" + collaborationID + "\r\n\r\n"; 
		logFile.Write (resInfo, resInfo.GetLength ());
		return IGNORED;
	}
	hr = aNode->get_text(&text);
	temp.Format ("%S",text);
	if (temp.Compare ("uml:Property"))
	{
		//log file
		resInfo = "IGNORE:Ignore a node of uml type \"" + nodeName +"\"  and its child nodes!\r\nINFO:collaboration name:" + collaborationName + "    collaboration ID:" + collaborationID + "\r\n\r\n"; 
		logFile.Write (resInfo, resInfo.GetLength ());
		return IGNORED;
	}
	hr = pAtts->get_length (&n);					// 获取属性节点个数
	if (FAILED (hr))
	{
		AfxMessageBox ("Fail to get number of the attributes of the node!");
		//log file
		resInfo = "ERROR:Fail to get number of attributes of the collaboration attribute node! Ignore all attributes of the node.\r\nINFO:collaboration name:" + collaborationName + "    collaboration ID:" + collaborationID + "\r\n\r\n"; 
		logFile.Write (resInfo, resInfo.GetLength ());
		return IGNORED;
	}
	for (i = 0; i < n; i ++)
	{
		hr = pAtts->get_item (i, &aNode);
		if (FAILED (hr))
		{
			AfxMessageBox ("Fail to get the wanted attribute of the node!");
			//log file
			temp.Format ("%d", i);
			resInfo = "ERROR:Fail to get the ith attribute of the collaboration attribute node! Ignore this attribute.\r\nINFO:collaboration name:" + collaborationName + "    collaboration ID:" + collaborationID + "    i:" + temp + "\r\n\r\n"; 
			logFile.Write (resInfo, resInfo.GetLength ());
			if (result == SUCCEED) result = IGNORED;
			continue;
		}
		hr = aNode->get_nodeName (&bstr);			// 获取属性节点的名称
		if (FAILED (hr))
		{
			AfxMessageBox ("Fail to get name of the wanted attribute!");
			//log file
			temp.Format ("%d", i);
			resInfo = "ERROR:Fail to get the ith attribute of the collaboration attribute node! Ignore this attribute.\r\nINFO:collaboration name:" + collaborationName + "    collaboration ID:" + collaborationID + "    i:" + temp + "\r\n\r\n"; 
			logFile.Write (resInfo, resInfo.GetLength ());
			if (result == SUCCEED) result = IGNORED;
			continue;
		}
		nodeName.Format ("%S",bstr);
		text = NULL;
		hr = aNode->get_text (&text);				//获取属性节点的值
		if (FAILED (hr) || text == NULL)
		{
			AfxMessageBox ("Fail to get the value of wanted attribute's name!");
			//log file
			temp.Format ("%d", i);
			resInfo = "ERROR:Fail to get the ith attribute of the collaboration attribute node! Ignore this attribute.\r\nINFO:collaboration name:" + collaborationName + "    collaboration ID:" + collaborationID + "    i:" + temp + "\r\n\r\n"; 
			logFile.Write (resInfo, resInfo.GetLength ());
			if (result == SUCCEED) result = IGNORED;
			continue;
		}
		if (!nodeName.Compare ("xmi:id"))
		{
			pID.Format ("%S", text);
		}
		else if (nodeName.Compare ("xmi:type"))
		{
			//log file			
			temp.Format ("%d", i);
			resInfo = "IGNORE:Ignore the ith attribute of type \"" + nodeName + "\" of the collaboration attribute node!\r\nINFO:collaboration name:" + collaborationName + "    collaboration ID:" + collaborationID + "    i:" + temp + "\r\n\r\n"; 
			logFile.Write (resInfo, resInfo.GetLength ());
			if (result == SUCCEED) result = IGNORED;
		}
	}
	try
	{
		sql = "select * from collaborationAttribute";						//设置查询字符串
		m_Ado.m_pRecordset = m_Ado.OpenRecordset(sql);						//打开记录集
		m_Ado.m_pRecordset->AddNew();										//添加新行
		m_Ado.m_pRecordset->PutCollect("ID", (_bstr_t)pID);					//设置ID字段内容
		m_Ado.m_pRecordset->PutCollect("所属合作", (_bstr_t)collaborationName);		//设置所属类字段内容
		m_Ado.m_pRecordset->PutCollect("所属合作ID", (_bstr_t)collaborationID);		//设置所属类字段内容
		//m_Ado.m_pRecordset->Update();										//更新记录集
		//m_Ado.CloseRecordset();												//关闭记录集
	}
	catch(_com_error e)
	{
		AfxMessageBox(e.Description());										//弹出错误处理
		//log file
		resInfo = "ERROR:Fail to put collaboration attribute data into database! Ignore this database write.\r\nINFO:collaboration attribute ID:" + pID + "    collaboration name:" + collaborationName + "    collaboration ID:" + collaborationID + "\r\n\r\n"; 
		logFile.Write (resInfo, resInfo.GetLength ());
		return IGNORED;
	}

	//类的成员属性的类型分析
	hr = pNode->hasChildNodes (&b);											//判断节点是否有孩子
	if (FAILED (hr))
	{
		AfxMessageBox ("Fail to find whether the node has child!");
		//log file
		resInfo = "ERROR:Fail to find whether the node has child! Ignore all these child nodes.\r\nINFO:collaboration attribute ID:" + pID + "    collaboration name:" + collaborationName + "    collaboration ID:" + collaborationID + "\r\n\r\n"; 
		logFile.Write (resInfo, resInfo.GetLength ());
		return IGNORED;
	}
	if (!b)											//没有子节点
	{
		try
		{
			m_Ado.m_pRecordset->Update();										//更新记录集
			m_Ado.CloseRecordset();												//关闭记录集
		}
		catch(_com_error e)
		{
			AfxMessageBox(e.Description()); //弹出错误处理
			resInfo = "ERROR:Fail to put collaboration attribute data into database! Ignore this database write.\r\nINFO:collaboration attribute ID:" + pID + "    collaboration name:" + collaborationName + "    collaboration ID:" + collaborationID + "\r\n\r\n"; 
			logFile.Write (resInfo, resInfo.GetLength ());
			return IGNORED;
		}
		return result;
	}

	hr = pNode->get_childNodes (&pNodes);			//获取子节点
	if (FAILED (hr))
	{
		AfxMessageBox ("Fail to get attributes of the node!");
		//log file
		resInfo = "ERROR:Fail to get child nodes of the collaboration attribute!Ignore all these child nodes.\r\nINFO:collaboration attribute ID:" + pID + "    collaboration name:" + collaborationName + "    collaboration ID:" + collaborationID + "\r\n\r\n"; 
		logFile.Write (resInfo, resInfo.GetLength ());
		return IGNORED;
	}
	hr = pNodes->get_length (&n);					// 获取子节点个数
	if (FAILED (hr))
	{
		AfxMessageBox ("Fail to get number of the attributes of the node!");
		//log file
		resInfo = "ERROR:Fail to get number of child nodes of the collaboration attribute!Ignore all these child nodes.\r\nINFO:collaboration attribute ID:" + pID + "    collaboration name:" + collaborationName + "    collaboration ID:" + collaborationID + "\r\n\r\n"; 
		logFile.Write (resInfo, resInfo.GetLength ());
		return IGNORED;
	}
	for (i = 0; i < n; i ++)
	{

		hr = pNodes->get_item (i, &aNode);
		if (FAILED (hr))
		{
			AfxMessageBox ("Fail to get the wanted child node!");
			//log file
			temp.Format ("%d", i);
			resInfo = "ERROR:Fail to get the ith child node of the collaboration attribute! Ignore this child node.\r\nINFO:collaboration attribute ID:" + pID + "    collaboration name:" + collaborationName + "    collaboration ID:" + collaborationID + "    i:" + temp + "\r\n\r\n"; 
			logFile.Write (resInfo, resInfo.GetLength ());
			if (result == SUCCEED) result = IGNORED;
			continue;
		}
		hr = aNode->get_nodeName (&bstr);			// 获取子节点的名称
		if (FAILED (hr))
		{
			AfxMessageBox ("Fail to get name of the wanted chile node!");
			//log file
			temp.Format ("%d", i);
			resInfo = "ERROR:Fail to get the ith child node of the collaboration attribute! Ignore this child node.\r\nINFO:collaboration attribute ID:" + pID + "    collaboration name:" + collaborationName + "    collaboration ID:" + collaborationID + "    i:" + temp + "\r\n\r\n"; 
			logFile.Write (resInfo, resInfo.GetLength ());
			if (result == SUCCEED) result = IGNORED;
			continue;
		}
		nodeName.Format ("%S",bstr);
		text = NULL;
		hr = aNode->get_text (&text);						//获取属性节点的值
		if (FAILED (hr) || text == NULL)
		{
			AfxMessageBox ("Fail to get the value of wanted child's name!");
			//log file
			temp.Format ("%d", i);
			resInfo = "ERROR:Fail to get the ith child node of the collaboration attribute! Ignore this child node.\r\nINFO:collaboration attribute ID:" + pID + "    collaboration name:" + collaborationName + "    collaboration ID:" + collaborationID + "    i:" + temp + "\r\n\r\n"; 
			logFile.Write (resInfo, resInfo.GetLength ());
			if (result == SUCCEED) result = IGNORED;
			continue;
		}
		if (!nodeName.Compare ("type"))			//成员属性类型分析
		{
			hr = aNode->get_attributes (&pAtts);
			if (FAILED (hr))
			{
				AfxMessageBox ("Failed to get attributes of the node.");
				//logfile
				temp.Format ("%d", i);
				resInfo = "ERROR:Fail to get the ith child node information of the collaboration attribute! Ignore this child node information.\r\nINFO:collaboration attribute ID:" + pID + "    collaboration name:" + collaborationName + "    collaboration ID:" + collaborationID + "    i:" + temp + "\r\n\r\n"; 
				logFile.Write (resInfo, resInfo.GetLength ());
				if (result == SUCCEED) result = IGNORED;
				continue;
			}
			hr = pAtts->getNamedItem(L"xmi:idref",& bNode);
			if (FAILED (hr))
			{
				AfxMessageBox ("Failed to get wanted attribute of the node.");
				//logfile
				temp.Format ("%d", i);
				resInfo = "ERROR:Fail to get the ith child node information of the collaboration attribute! Ignore this child node information.\r\nINFO:collaboration attribute ID:" + pID + "    collaboration name:" + collaborationName + "    collaboration ID:" + collaborationID + "    i:" + temp + "\r\n\r\n"; 
				logFile.Write (resInfo, resInfo.GetLength ());
				if (result == SUCCEED) result = IGNORED;
				continue;
			}
			hr = bNode->get_text(&text);
			if (text != NULL)
			{
				temp.Format ("%S", text);
			}
			try
			{
				m_Ado.m_pRecordset->PutCollect("类型", (_bstr_t)temp);		//添加新记录
			}
			catch(_com_error e)
			{
				AfxMessageBox(e.Description()); //弹出错误处理				
				resInfo = "ERROR:Fail to put collaboration attribute type information into database! Ignore this database write.\r\nINFO:collaboration attribute ID:" + pID + "    collaboration name:" + collaborationName + "    collaboration ID:" + collaborationID + "\r\n\r\n"; 
				logFile.Write (resInfo, resInfo.GetLength ());
				return IGNORED;
			}
		}
		else
		{
			//logfile
			temp.Format ("%d", i);
			resInfo = "IGNORE:Ignore ith child node information of type \"" + nodeName + "\"the collaboration attribute! Ignore this child node information.\r\nINFO:collaboration attribute ID:" + pID + "    collaboration name:" + collaborationName + "    collaboration ID:" + collaborationID + "    i:" + temp + "\r\n\r\n"; 
			logFile.Write (resInfo, resInfo.GetLength ());
			if (result == SUCCEED) result = IGNORED;
		}
	}
	try
	{
		m_Ado.m_pRecordset->Update();										//更新记录集
		m_Ado.CloseRecordset();												//关闭记录集
	}
	catch(_com_error e)
	{
		AfxMessageBox(e.Description()); //弹出错误处理
		resInfo = "ERROR:Fail to put collaboration attribute data into database! Ignore this database write.\r\nINFO:collaboration attribute ID:" + pID + "    collaboration name:" + collaborationName + "    collaboration ID:" + collaborationID + "\r\n\r\n"; 
		logFile.Write (resInfo, resInfo.GetLength ());
		return IGNORED;
	}
	return result;
}

//********************************************************************//
//函数功能：对CF操作对象节点进行判断分析，分析其ID及类型等信息        //
//参数说明：pNode为此节点的指针                                       //
//          cfName为此CF操作对象所在组合片段的名称                    //
//          cfID为此CF操作对象所在组合片段的ID                        //
//          返回值为处理结果                                          //
//********************************************************************//
unsigned int CUMLanalyserDlg::CFOperandAnalyse(IXMLDOMNode *pNode, CString cfName, CString cfID)
{
	long int n = -1, i = 0;
	unsigned int result = SUCCEED;					//处理结果
	BOOL isAssociated = FALSE;
	CString temp = "", nodeName = "", pID = "", sql = "", resInfo = "";
	HRESULT hr;
	VARIANT_BOOL b;
	BSTR text = NULL;								//节点值
	IXMLDOMNamedNodeMap *pAtts = NULL;				//属性节点列表
	IXMLDOMNode *aNode = NULL;
	IXMLDOMNodeList *pNodes = NULL;					//子节点列表
	
	//CF操作对象的属性分析
	hr = pNode->get_attributes (&pAtts);
	if (FAILED (hr))
	{
		AfxMessageBox ("Fail to get attributes of the node!");
		//log file
		resInfo = "ERROR:Fail to get attributes of the CF operand node! Ignore all attributes of the node.\r\nINFO:parent CF name:" + cfName + "    parent CF ID:" + cfID + "\r\n\r\n"; 
		logFile.Write (resInfo, resInfo.GetLength ());
		return IGNORED;
	}
	hr = pAtts->getNamedItem(L"xmi:type",& aNode);
	if (FAILED (hr))
	{
		AfxMessageBox ("Fail to get type of the attributes of the class!");
		//log file
		resInfo = "ERROR:Fail to get \"xmi:type\" of the CF operand node! Ignore all attributes of the node.\r\nINFO:parent CF name:" + cfName + "    parent CF ID:" + cfID + "\r\n\r\n"; 
		logFile.Write (resInfo, resInfo.GetLength ());
		return IGNORED;
	}
	hr = aNode->get_text(&text);
	if (FAILED (hr) || text == NULL)
	{
		AfxMessageBox ("Fail to get the value of wanted attribute's name!");
		//log file
		resInfo = "ERROR:Fail to get \"xmi:itype\" of the CF operand node! Ignore all attributes of the node.\r\nINFO:parent CF name:" + cfName + "    parent CF ID:" + cfID + "\r\n\r\n"; 
		logFile.Write (resInfo, resInfo.GetLength ());
		return IGNORED;
	}
	temp.Format ("%S",text);
	if (temp.Compare ("uml:InteractionOperand"))
	{
		//log file
		resInfo = "IGNORE:Ignore a node of uml type \"" + nodeName +"\"  and its child nodes!\r\nINFO:parent CF name:" + cfName + "    parent CF ID:" + cfID + "\r\n\r\n"; 
		logFile.Write (resInfo, resInfo.GetLength ());
		return IGNORED;
	}
	hr = pAtts->getNamedItem(L"xmi:id",& aNode);
	if (FAILED (hr))
	{
		AfxMessageBox ("Fail to get the wanted attribute of the node!");
		//log file
		resInfo = "ERROR:Fail to get \"xmi:id\" of the CF operand node! Ignore all attributes of the node.\r\nINFO:parent CF name:" + cfName + "    parent CF ID:" + cfID + "\r\n\r\n"; 
		logFile.Write (resInfo, resInfo.GetLength ());
		return IGNORED;
	}
	text = NULL;
	hr = aNode->get_text (&text);				//获取属性节点的值
	if (FAILED (hr) || text == NULL)
	{
		AfxMessageBox ("Fail to get the value of wanted attribute's name!");
		//log file
		resInfo = "ERROR:Fail to get \"xmi:id\" of the CF operand node! Ignore all attributes of the node.\r\nINFO:parent CF name:" + cfName + "    parent CF ID:" + cfID + "\r\n\r\n"; 
		logFile.Write (resInfo, resInfo.GetLength ());
		return IGNORED;
	}
	pID.Format ("%S", text);
	try
	{
		sql = "select * from operand";										//设置查询字符串
		m_Ado.m_pRecordset = m_Ado.OpenRecordset(sql);						//打开记录集
		m_Ado.m_pRecordset->AddNew();										//添加新行
		m_Ado.m_pRecordset->PutCollect("ID", (_bstr_t)pID);					//设置ID字段内容
		m_Ado.m_pRecordset->PutCollect("所属片段", (_bstr_t)cfName);		//设置所属片段字段内容
		m_Ado.m_pRecordset->PutCollect("所属片段ID", (_bstr_t)cfID);		//设置所属片段字段内容
		m_Ado.m_pRecordset->Update();										//更新记录集
		m_Ado.CloseRecordset();												//关闭记录集
	}
	catch(_com_error e)
	{
		AfxMessageBox(e.Description());										//弹出错误处理
		//log file
		resInfo = "ERROR:Fail to put CF operand data into database! Ignore this database write.\r\nINFO:operand ID:" + pID + "    parent CF name:" + cfName + "    parent CF ID:" + cfID + "\r\n\r\n"; 
		logFile.Write (resInfo, resInfo.GetLength ());
		return IGNORED;
	}

	//CF操作对象的成员属性的类型分析
	hr = pNode->hasChildNodes (&b);											//判断节点是否有孩子
	if (FAILED (hr))
	{
		AfxMessageBox ("Fail to find whether the node has child!");
		//log file
		resInfo = "ERROR:Fail to find whether the node has child! Ignore all these child nodes.\r\nINFO:operand ID:" + pID + "    parent CF name:" + cfName + "    parent CF ID:" + cfID + "\r\n\r\n"; 
		logFile.Write (resInfo, resInfo.GetLength ());
		return IGNORED;
	}
	if (!b)											//没有子节点
	{
		return result;
	}

	hr = pNode->get_childNodes (&pNodes);			//获取子节点
	if (FAILED (hr))
	{
		AfxMessageBox ("Fail to get attributes of the node!");
		//log file
		resInfo = "ERROR:Fail to get child nodes of the CF operand node! Ignore all these child nodes.\r\nINFO:operand ID:" + pID + "    parent CF name:" + cfName + "    parent CF ID:" + cfID + "\r\n\r\n"; 
		logFile.Write (resInfo, resInfo.GetLength ());
		return IGNORED;
	}
	hr = pNodes->get_length (&n);					// 获取子节点个数
	if (FAILED (hr))
	{
		AfxMessageBox ("Fail to get number of the attributes of the node!");
		//log file
		resInfo = "ERROR:Fail to get number of child nodes of the CF operand node! Ignore all these child nodes.\r\nINFO:operand ID:" + pID + "    parent CF name:" + cfName + "    parent CF ID:" + cfID + "\r\n\r\n"; 
		logFile.Write (resInfo, resInfo.GetLength ());
		return IGNORED;
	}
	for (i = 0; i < n; i ++)
	{

		hr = pNodes->get_item (i, &aNode);
		if (FAILED (hr))
		{
			AfxMessageBox ("Fail to get the wanted child node!");
			//log file
			temp.Format ("%d", i);
			resInfo = "ERROR:Fail to get the ith child node of the CF operand node! Ignore all this child node.\r\nINFO:operand ID:" + pID + "    parent CF name:" + cfName + "    parent CF ID:" + cfID + "    i:" + temp + "\r\n\r\n"; 
			logFile.Write (resInfo, resInfo.GetLength ());
			if (result == SUCCEED) result = IGNORED;
			continue;
		}
		hr = aNode->get_nodeName (&bstr);			// 获取子节点的名称
		if (FAILED (hr))
		{
			AfxMessageBox ("Fail to get name of the wanted chile node!");
			//log file
			temp.Format ("%d", i);
			resInfo = "ERROR:Fail to get the ith child node of the CF operand node! Ignore all this child node.\r\nINFO:operand ID:" + pID + "    parent CF name:" + cfName + "    parent CF ID:" + cfID + "    i:" + temp + "\r\n\r\n"; 
			logFile.Write (resInfo, resInfo.GetLength ());
			if (result == SUCCEED) result = IGNORED;
			continue;
		}
		nodeName.Format ("%S",bstr);
		text = NULL;
		hr = aNode->get_text (&text);						//获取属性节点的值
		if (FAILED (hr) || text == NULL)
		{
			AfxMessageBox ("Fail to get the value of wanted child's name!");
			//log file
			temp.Format ("%d", i);
			resInfo = "ERROR:Fail to get the ith child node of the CF operand node! Ignore all this child node.\r\nINFO:operand ID:" + pID + "    parent CF name:" + cfName + "    parent CF ID:" + cfID + "    i:" + temp + "\r\n\r\n"; 
			logFile.Write (resInfo, resInfo.GetLength ());
			if (result == SUCCEED) result = IGNORED;
			continue;
		}
		if (!nodeName.Compare ("guard"))			//成员属性类型分析
		{
			CFoperandGuardAnalyse (aNode, pID);
		}
		else
		{
			//logfile
			temp.Format ("%d", i);
			resInfo = "IGNORE:Ignore the ith child node of type \"" + nodeName + "\" of the CF operand node! Ignore all this child node.\r\nINFO:operand ID:" + pID + "    parent CF name:" + cfName + "    parent CF ID:" + cfID + "    i:" + temp + "\r\n\r\n"; 
			logFile.Write (resInfo, resInfo.GetLength ());
			if (result == SUCCEED) result = IGNORED;
		}
	}
	return result;
}

//********************************************************************//
//函数功能：对操作对象约束节点进行判断分析，分析其ID及约束条件等信息  //
//参数说明：pNode为此节点的指针                                       //
//          cfopID为此操作对象约束所在操作对象的ID                    //
//          返回值为处理结果                                          //
//********************************************************************//
unsigned int CUMLanalyserDlg::CFoperandGuardAnalyse(IXMLDOMNode *pNode, CString cfopID)
{
	long int n = -1, i = 0, m = -1, j = 0;
	unsigned int result = SUCCEED;					//处理结果
	CString resInfo = "", temp = "", nodeName = "", pID = "", pspecificationID = "", ptype = "", pconstraint = "", sql = "";
	HRESULT hr;
	VARIANT_BOOL b;
	BSTR text = NULL;								//节点值
	IXMLDOMNamedNodeMap *pAtts = NULL;				//属性节点列表
	IXMLDOMNode *aNode = NULL, *bNode = NULL;
	IXMLDOMNodeList *pNodes = NULL, *qNodes = NULL;	//子节点列表
	
	//操作对象约束的属性分析
	hr = pNode->get_attributes (&pAtts);
	if (FAILED (hr))
	{
		AfxMessageBox ("Fail to get attributes of the node!");
		//log file
		resInfo = "ERROR:Fail to get attributes of the operand guard node! Ignore all attributes of the node.\r\nINFO:parent operand name:" + cfopID + "\r\n\r\n"; 
		logFile.Write (resInfo, resInfo.GetLength ());
		return IGNORED;
	}
	hr = pAtts->getNamedItem(L"xmi:type",& aNode);
	if (FAILED (hr))
	{
		AfxMessageBox ("Fail to get type of the attributes of the class!");
		//log file
		resInfo = "ERROR:Fail to get \"xmi:type\" of the operand guard node! Ignore all attributes of the node.\r\nINFO:parent operand name:" + cfopID + "\r\n\r\n"; 
		logFile.Write (resInfo, resInfo.GetLength ());
		return IGNORED;
	}
	hr = aNode->get_text(&text);
	temp.Format ("%S",text);
	if (temp.Compare ("uml:InteractionConstraint"))
	{
		//log file
		resInfo = "IGNORE:Ignore a node of uml type \"" + temp +"\"  and its child nodes!\r\nINFO:parent operand name:" + cfopID + "\r\n\r\n"; 
		logFile.Write (resInfo, resInfo.GetLength ());
		return IGNORED;
	}

	hr = pAtts->getNamedItem(L"xmi:id",& aNode);
	if (FAILED (hr))
	{
		AfxMessageBox ("Fail to get type of the attributes of the class!");
		//log file
		resInfo = "ERROR:Fail to get \"xmi:id\" of the operand guard node! Ignore all attributes of the node.\r\nINFO:parent operand name:" + cfopID + "\r\n\r\n"; 
		logFile.Write (resInfo, resInfo.GetLength ());
		return IGNORED;
	}
	hr = aNode->get_text(&text);
	pID.Format ("%S", text);

	//操作对象约束的详细约束分析
	hr = pNode->hasChildNodes (&b);											//判断节点是否有孩子
	if (FAILED (hr))
	{
		AfxMessageBox ("Fail to find whether the node has child!");
		//log file
		resInfo = "ERROR:Fail to find whether the node has child! Ignore all these child nodes.\r\nINFO:parent operand name:" + cfopID + "\r\n\r\n"; 
		logFile.Write (resInfo, resInfo.GetLength ());
		return IGNORED;
	}
	if (!b)											//没有子节点(即没有详细约束条件)
	{
		return IGNORED;
	}

	hr = pNode->get_childNodes (&pNodes);			//获取子节点
	if (FAILED (hr))
	{
		AfxMessageBox ("Fail to get attributes of the node!");
		//log file
		resInfo = "ERROR:Fail to get child nodes of the operand guard node! Ignore all these child nodes.\r\nINFO:parent operand name:" + cfopID + "\r\n\r\n"; 
		logFile.Write (resInfo, resInfo.GetLength ());
		return IGNORED;
	}
	hr = pNodes->get_length (&n);					// 获取子节点个数
	if (FAILED (hr))
	{
		AfxMessageBox ("Fail to get number of the attributes of the node!");
		//log file
		resInfo = "ERROR:Fail to get number of child nodes of the operand guard node! Ignore all these child nodes.\r\nINFO:parent operand name:" + cfopID + "\r\n\r\n"; 
		logFile.Write (resInfo, resInfo.GetLength ());
		return IGNORED;
	}
	for (i = 0; i < n; i ++)
	{

		hr = pNodes->get_item (i, &aNode);
		if (FAILED (hr))
		{
			AfxMessageBox ("Fail to get the wanted child node!");
			//log file
			resInfo = "ERROR:Fail to get specific guard condition of the operand guard node! Ignore all these child nodes.\r\nINFO:parent operand name:" + cfopID + "\r\n\r\n"; 
			logFile.Write (resInfo, resInfo.GetLength ());
			return IGNORED;
		}
		hr = aNode->get_nodeName (&bstr);			// 获取子节点的名称
		if (FAILED (hr))
		{
			AfxMessageBox ("Fail to get name of the wanted chile node!");
			//log file
			resInfo = "ERROR:Fail to get specific guard condition of the operand guard node! Ignore all these child nodes.\r\nINFO:parent operand name:" + cfopID + "\r\n\r\n"; 
			logFile.Write (resInfo, resInfo.GetLength ());
			return IGNORED;
		}
		nodeName.Format ("%S",bstr);
		text = NULL;
		hr = aNode->get_text (&text);						//获取属性节点的值
		if (FAILED (hr) || text == NULL)
		{
			AfxMessageBox ("Fail to get the value of wanted child's name!");
			//log file
			resInfo = "ERROR:Fail to get specific guard condition of the operand guard node! Ignore all these child nodes.\r\nINFO:parent operand name:" + cfopID + "\r\n\r\n"; 
			logFile.Write (resInfo, resInfo.GetLength ());
			return IGNORED;
		}
		if (!nodeName.Compare ("specification"))			//成员属性类型分析
		{
			hr = aNode->get_attributes (&pAtts);
			if (FAILED (hr))
			{
				AfxMessageBox ("Failed to get attributes of the node.");
				//logfile
				resInfo = "ERROR:Fail to get specific guard condition of the operand guard node! Ignore all these child nodes.\r\nINFO:parent operand name:" + cfopID + "\r\n\r\n"; 
				logFile.Write (resInfo, resInfo.GetLength ());
				return IGNORED;
			}
			hr = pAtts->get_length (&m);					// 获取节点个数
			if (FAILED (hr))
			{
				AfxMessageBox ("Failed to get the number of attributes of the node.");
				//logfile
				resInfo = "ERROR:Fail to get specific guard condition of the operand guard node! Ignore all these child nodes.\r\nINFO:parent operand name:" + cfopID + "\r\n\r\n"; 
				logFile.Write (resInfo, resInfo.GetLength ());
				return IGNORED;
			}
			for (j = 0; j < m; j ++)
			{
				hr = pAtts->get_item (j, &bNode);
				if (FAILED (hr))
				{
					AfxMessageBox ("Failed to get wanted attribute of the node.");
					//logfile
					resInfo = "ERROR:Fail to get specific guard condition of the operand guard node! Ignore all these child nodes.\r\nINFO:parent operand name:" + cfopID + "\r\n\r\n"; 
					logFile.Write (resInfo, resInfo.GetLength ());
					return IGNORED;
				}
				hr = bNode->get_nodeName (&bstr);			// 获取属性节点的名称
				if (FAILED (hr))
				{
					AfxMessageBox ("Fail to get name of the wanted attribute!");
					//log file
					resInfo = "ERROR:Fail to get specific guard condition of the operand guard node! Ignore all these child nodes.\r\nINFO:parent operand name:" + cfopID + "\r\n\r\n"; 
					logFile.Write (resInfo, resInfo.GetLength ());
					return IGNORED;
				}
				nodeName.Format ("%S",bstr);
				text = NULL;
				hr = bNode->get_text (&text);				//获取属性节点的值
				if (FAILED (hr) || text == NULL)
				{
					AfxMessageBox ("Fail to get the value of wanted attribute's name!");
					//log file
					resInfo = "ERROR:Fail to get specific guard condition of the operand guard node! Ignore all these child nodes.\r\nINFO:parent operand name:" + cfopID + "\r\n\r\n"; 
					logFile.Write (resInfo, resInfo.GetLength ());
					return IGNORED;
				}
				if (!nodeName.Compare ("xmi:id"))
				{
					pspecificationID.Format ("%S", text);
				}
				else if (!nodeName.Compare ("xmi:type"))
				{
					ptype.Format ("%S", text);
				}
				else
				{
				}
			}

			//child
			//操作对象约束的详细约束分析
			hr = aNode->hasChildNodes (&b);											//判断节点是否有孩子
			if (FAILED (hr))
			{
				AfxMessageBox ("Fail to find whether the node has child!");
				//log file
			}
			if (!b)											//没有子节点(即没有成员属性和方法)
			{
				try
				{
					sql = "select * from guard";											//设置查询字符串
					m_Ado.m_pRecordset = m_Ado.OpenRecordset(sql);							//打开记录集
					m_Ado.m_pRecordset->AddNew();											//添加新行
					m_Ado.m_pRecordset->PutCollect("ID", (_bstr_t)pID);						//设置ID字段内容
					m_Ado.m_pRecordset->PutCollect("详细条件ID", (_bstr_t)pspecificationID);//设置详细条件ID字段内容
					m_Ado.m_pRecordset->PutCollect("类型", (_bstr_t)ptype);					//设置类型字段内容
					m_Ado.m_pRecordset->PutCollect("所属操作对象ID", (_bstr_t)cfopID);		//设置所属操作对象ID字段内容
					m_Ado.m_pRecordset->Update();											//更新记录集
					m_Ado.CloseRecordset();													//关闭记录集
				}
				catch(_com_error e)
				{
					AfxMessageBox(e.Description());										//弹出错误处理
					//log file
					resInfo = "ERROR:Fail to put operand guard data into database! Ignore this database write.\r\nINFO:parent operand name:" + cfopID + "\r\n\r\n"; 
					logFile.Write (resInfo, resInfo.GetLength ());
					return IGNORED;
				}
				return SUCCEED;
			}

			hr = aNode->get_childNodes (&qNodes);			//获取子节点
			if (FAILED (hr))
			{
				AfxMessageBox ("Fail to get attributes of the node!");
				//log file
				resInfo = "ERROR:Fail to get specific guard condition of the operand guard node! Ignore all these child nodes.\r\nINFO:parent operand name:" + cfopID + "\r\n\r\n"; 
				logFile.Write (resInfo, resInfo.GetLength ());
				return IGNORED;
			}
			hr = qNodes->get_length (&m);					// 获取子节点个数
			if (FAILED (hr))
			{
				AfxMessageBox ("Fail to get number of the attributes of the node!");
				//log file
				resInfo = "ERROR:Fail to get specific guard condition of the operand guard node! Ignore all these child nodes.\r\nINFO:parent operand name:" + cfopID + "\r\n\r\n"; 
				logFile.Write (resInfo, resInfo.GetLength ());
				return IGNORED;
			}
			for (j = 0; j < m; j ++)
			{
				hr = qNodes->get_item (i, &bNode);
				if (FAILED (hr))
				{
					AfxMessageBox ("Fail to get the wanted child node!");
					//log file
					resInfo = "ERROR:Fail to get specific guard condition of the operand guard node! Ignore all these child nodes.\r\nINFO:parent operand name:" + cfopID + "\r\n\r\n"; 
					logFile.Write (resInfo, resInfo.GetLength ());
					return IGNORED;
				}
				hr = bNode->get_nodeName (&bstr);			// 获取子节点的名称
				if (FAILED (hr))
				{
					AfxMessageBox ("Fail to get name of the wanted chile node!");
					//log file
					resInfo = "ERROR:Fail to get specific guard condition of the operand guard node! Ignore all these child nodes.\r\nINFO:parent operand name:" + cfopID + "\r\n\r\n"; 
					logFile.Write (resInfo, resInfo.GetLength ());
					return IGNORED;
				}
				nodeName.Format ("%S",bstr);
				text = NULL;
				hr = bNode->get_text (&text);						//获取属性节点的值
				if (FAILED (hr) || text == NULL)
				{
					AfxMessageBox ("Fail to get the value of wanted child's name!");
					//log file
					resInfo = "ERROR:Fail to get specific guard condition of the operand guard node! Ignore all these child nodes.\r\nINFO:parent operand name:" + cfopID + "\r\n\r\n"; 
					logFile.Write (resInfo, resInfo.GetLength ());
					return IGNORED;
				}
				if (!nodeName.Compare ("body"))			//成员属性类型分析
				{
					pconstraint.Format ("%S", text);
				}
			}
			try
			{
				sql = "select * from guard";											//设置查询字符串
				m_Ado.m_pRecordset = m_Ado.OpenRecordset(sql);							//打开记录集
				m_Ado.m_pRecordset->AddNew();											//添加新行
				m_Ado.m_pRecordset->PutCollect("ID", (_bstr_t)pID);						//设置ID字段内容
				m_Ado.m_pRecordset->PutCollect("详细条件ID", (_bstr_t)pspecificationID);//设置详细条件ID字段内容
				m_Ado.m_pRecordset->PutCollect("类型", (_bstr_t)ptype);					//设置类型字段内容
				m_Ado.m_pRecordset->PutCollect("约束条件", (_bstr_t)pconstraint);		//设置约束条件字段内容
				m_Ado.m_pRecordset->PutCollect("所属操作对象ID", (_bstr_t)cfopID);		//设置所属操作对象ID字段内容
				m_Ado.m_pRecordset->Update();											//更新记录集
				m_Ado.CloseRecordset();													//关闭记录集
			}
			catch(_com_error e)
			{
				AfxMessageBox(e.Description());										//弹出错误处理
				//log file
				resInfo = "ERROR:Fail to put specific operand guard condition data into database! Ignore this database write.\r\nINFO:parent operand name:" + cfopID + "\r\n\r\n"; 
				logFile.Write (resInfo, resInfo.GetLength ());
				return IGNORED;
			}
		}
		else
		{
		}
	}
	return SUCCEED;
}

//********************************************************************//
//函数功能：对消息参数节点进行判断分析，分析其名称及类型等信息        //
//参数说明：pNode为此节点的指针                                       //
//          messageName为此消息参数所在消息的名称                     //
//          messageID为此消息参数所在消息的ID                         //
//          返回值为处理结果                                          //
//********************************************************************//
unsigned int CUMLanalyserDlg::MessageArgumentAnalyse(IXMLDOMNode *pNode, CString messageName, CString messageID)
{
	long int n = -1, i = 0;
	CString nodeName = "", pname = "", pID = "", ptype = "", sql = "", temp = "", resInfo = "";
	HRESULT hr;
	BSTR text = NULL;								//节点值
	IXMLDOMNamedNodeMap *pAtts = NULL;				//属性节点列表
	IXMLDOMNode *aNode = NULL;
	unsigned int result = SUCCEED;
	
	//消息参数的属性分析
	hr = pNode->get_attributes (&pAtts);
	if (FAILED (hr))
	{
		AfxMessageBox ("Fail to get attributes of the node!");
		//log file
		resInfo = "ERROR:Fail to get attributes of the message argument node! Ignore all attributes of the node.\r\nINFO:parent message name:" + messageName + "    parent message ID:" + messageID + "\r\n\r\n"; 
		logFile.Write (resInfo, resInfo.GetLength ());
		return IGNORED;
	}
	hr = pAtts->get_length (&n);					// 获取属性节点个数
	if (FAILED (hr))
	{
		AfxMessageBox ("Fail to get number of the attributes of the node!");
		//log file
		resInfo = "ERROR:Fail to get number of attributes of the message argument node! Ignore all attributes of the node.\r\nINFO:parent message name:" + messageName + "    parent message ID:" + messageID + "\r\n\r\n"; 
		logFile.Write (resInfo, resInfo.GetLength ());
		return IGNORED;
	}
	for (i = 0; i < n; i ++)
	{
		hr = pAtts->get_item (i, &aNode);
		if (FAILED (hr))
		{
			AfxMessageBox ("Fail to get the wanted attribute of the node!");
			//log file
			temp.Format ("%d", i);
			resInfo = "ERROR:Fail to get the ith attribute of the message argument node! Ignore this attribute of the node.\r\nINFO:parent message name:" + messageName + "    parent message ID:" + messageID + "    i:" + temp + "\r\n\r\n"; 
			logFile.Write (resInfo, resInfo.GetLength ());
			if (result == SUCCEED) result = IGNORED;
			continue;
		}
		hr = aNode->get_nodeName (&bstr);			// 获取属性节点的名称
		if (FAILED (hr))
		{
			AfxMessageBox ("Fail to get name of the wanted attribute!");
			//log file
			temp.Format ("%d", i);
			resInfo = "ERROR:Fail to get the ith attribute of the message argument node! Ignore this attribute of the node.\r\nINFO:parent message name:" + messageName + "    parent message ID:" + messageID + "    i:" + temp + "\r\n\r\n"; 
			logFile.Write (resInfo, resInfo.GetLength ());
			if (result == SUCCEED) result = IGNORED;
			continue;
		}
		nodeName.Format ("%S",bstr);
		text = NULL;
		hr = aNode->get_text (&text);				//获取属性节点的值
		if (FAILED (hr) || text == NULL)
		{
			AfxMessageBox ("Fail to get the value of wanted attribute's name!");
			//log file
			temp.Format ("%d", i);
			resInfo = "ERROR:Fail to get the ith attribute of the message argument node! Ignore this attribute of the node.\r\nINFO:parent message name:" + messageName + "    parent message ID:" + messageID + "    i:" + temp + "\r\n\r\n"; 
			logFile.Write (resInfo, resInfo.GetLength ());
			if (result == SUCCEED) result = IGNORED;
			continue;
		}
		if (!nodeName.Compare ("xmi:id"))
		{
			pID.Format ("%S", text);
		}
		else if (!nodeName.Compare ("name"))
		{
			pname.Format ("%S", text);
		}
		else if (!nodeName.Compare ("xmi:type"))
		{
			ptype.Format ("%S", text);
		}
		else
		{
		}
	}
	try
	{
		sql = "select * from argument";										//设置查询字符串
		m_Ado.m_pRecordset = m_Ado.OpenRecordset(sql);						//打开记录集
		m_Ado.m_pRecordset->AddNew();										//添加新行
		m_Ado.m_pRecordset->PutCollect("名称", (_bstr_t)pname);				//设置名称字段内容
		m_Ado.m_pRecordset->PutCollect("ID", (_bstr_t)pID);					//设置ID字段内容
		m_Ado.m_pRecordset->PutCollect("类型", (_bstr_t)ptype);				//设置类型字段内容
		m_Ado.m_pRecordset->PutCollect("所属消息", (_bstr_t)messageName);	//设置所属消息字段内容
		m_Ado.m_pRecordset->PutCollect("所属消息ID", (_bstr_t)messageID);	//设置所属消息ID字段内容
		m_Ado.m_pRecordset->Update();										//更新记录集
		m_Ado.CloseRecordset();												//关闭记录集
	}
	catch(_com_error e)
	{
		AfxMessageBox(e.Description());										//弹出错误处理
		//log file
		resInfo = "ERROR:Fail to put message argument data into database! Ignore this database write.\r\nINFO:argument name:" + pname + "    argument ID:" + pID + "    parent message name:" + messageName + "    parent message ID:" + messageID + "\r\n\r\n"; 
		logFile.Write (resInfo, resInfo.GetLength ());
		return IGNORED;
	}
	return result;
}

//********************************************************************//
//函数功能：根据生命线ID找到生命线，获取其名称等相关信息              //
//参数说明：brothers为查找范围                                        //
//          lifelineID为此待查生命线的ID                              //
//          返回值为待查生命线的名称                                  //
//********************************************************************//
CString CUMLanalyserDlg::FindLifeline(IXMLDOMNodeList *brothers, CString lifelineID)
{
	long int n = -1, i = 0, m = -1, j = 0;
	unsigned int result = SUCCEED;					//处理结果
	CString temp = "", nodeName = "", lifelineName = "", resInfo = "";
	HRESULT hr;
	BSTR text = NULL;								//节点值
	IXMLDOMNamedNodeMap *pAtts = NULL;				//属性节点列表
	IXMLDOMNode *aNode = NULL, *bNode = NULL;
	IXMLDOMNodeList *pNodes = NULL;					//子节点列表
	
	hr = brothers->get_length (&n);					// 获取子节点个数
	if (FAILED (hr))
	{
		AfxMessageBox ("Fail to get number of the attributes of the node!");
		//log file
		resInfo = "ERROR:Fail to find the name of lifeline whose ID is \"" + lifelineID + "\"\r\n\r\n"; 
		logFile.Write (resInfo, resInfo.GetLength ());
		return "";	
	}
	for (i = 0; i < n; i ++)
	{
		hr = brothers->get_item (i, &aNode);
		if (FAILED (hr))
		{
			AfxMessageBox ("Fail to get the wanted child node!");
			//log file
			resInfo = "ERROR:Fail to find the name of lifeline whose ID is \"" + lifelineID + "\"\r\n\r\n"; 
			logFile.Write (resInfo, resInfo.GetLength ());
			continue;
		}
		hr = aNode->get_nodeName (&bstr);			// 获取子节点的名称
		if (FAILED (hr))
		{
			AfxMessageBox ("Fail to get name of the wanted chile node!");
			//log file
			resInfo = "ERROR:Fail to find the name of lifeline whose ID is \"" + lifelineID + "\"\r\n\r\n"; 
			logFile.Write (resInfo, resInfo.GetLength ());
			continue;
		}
		nodeName.Format ("%S",bstr);
		if (!nodeName.Compare ("lifeline") || !nodeName.Compare ("fragment"))	//成员属性类型分析
		{
			hr = aNode->get_attributes (&pAtts);
			if (FAILED (hr))
			{
				AfxMessageBox ("Failed to get attributes of the node.");
				//logfile
				resInfo = "ERROR:Fail to find the name of lifeline whose ID is \"" + lifelineID + "\"\r\n\r\n"; 
				logFile.Write (resInfo, resInfo.GetLength ());
				continue;
			}
			hr = pAtts->getNamedItem(L"xmi:type",& bNode);
			if (FAILED (hr))
			{
				AfxMessageBox ("Fail to get type of the attributes of the class!");
				//log file
				resInfo = "ERROR:Fail to find the name of lifeline whose ID is \"" + lifelineID + "\"\r\n\r\n"; 
				logFile.Write (resInfo, resInfo.GetLength ());
				continue;
			}
			hr = bNode->get_text(&text);
			temp.Format ("%S", text);
			if (temp.Compare ("uml:Lifeline") && temp.Compare ("uml:CombinedFragment"))
				continue;
			hr = pAtts->getNamedItem(L"xmi:id",& bNode);
			if (FAILED (hr))
			{
				AfxMessageBox ("Fail to get type of the attributes of the class!");
				//log file
				resInfo = "ERROR:Fail to find the name of lifeline whose ID is \"" + lifelineID + "\"\r\n\r\n"; 
				logFile.Write (resInfo, resInfo.GetLength ());
				continue;
			}
			hr = bNode->get_text(&text);
			temp.Format ("%S", text);
			if (! temp.Compare (lifelineID))
			{
				hr = pAtts->get_length (&m);					// 获取节点个数
				if (FAILED (hr))
				{
					AfxMessageBox ("Failed to get the number of attributes of the node.");
					//logfile
					resInfo = "ERROR:Fail to find the name of lifeline whose ID is \"" + lifelineID + "\"\r\n\r\n"; 
					logFile.Write (resInfo, resInfo.GetLength ());
					continue;
				}
				lifelineName = "";
				for (j = 0; j < m; j ++)
				{
					hr = pAtts->get_item (j, &bNode);
					if (FAILED (hr))
					{
						AfxMessageBox ("Failed to get wanted attribute of the node.");
						//logfile
						resInfo = "ERROR:Fail to find the name of lifeline whose ID is \"" + lifelineID + "\"\r\n\r\n"; 
						logFile.Write (resInfo, resInfo.GetLength ());
						continue;
					}
					hr = bNode->get_nodeName (&bstr);			// 获取属性节点的名称
					if (FAILED (hr))
					{
						AfxMessageBox ("Fail to get name of the wanted attribute!");
						//log file
						resInfo = "ERROR:Fail to find the name of lifeline whose ID is \"" + lifelineID + "\"\r\n\r\n"; 
						logFile.Write (resInfo, resInfo.GetLength ());
						continue;
					}
					nodeName.Format ("%S",bstr);
					text = NULL;
					hr = bNode->get_text (&text);				//获取属性节点的值
					if (FAILED (hr) || text == NULL)
					{
						AfxMessageBox ("Fail to get the value of wanted attribute's name!");
						//log file
						resInfo = "ERROR:Fail to find the name of lifeline whose ID is \"" + lifelineID + "\"\r\n\r\n"; 
						logFile.Write (resInfo, resInfo.GetLength ());
						continue;
					}
					if (!nodeName.Compare ("name"))
					{
						lifelineName.Format ("%S", text);
						break;
					}
					else
					{
					}
				}
				break;
			}
		}
	}
	return lifelineName;
}

//********************************************************************//
//函数功能：根据时间点ID找到时间点，获取其名称等相关信息              //
//参数说明：brothers为查找范围                                        //
//          osID为此待查时间点的ID                                    //
//          返回值为待查生命线的名称                                  //
//********************************************************************//
CString CUMLanalyserDlg::FindOS(IXMLDOMNodeList *brothers, CString osID)
{
	long int n = -1, i = 0, m = -1, j = 0;
	unsigned int result = SUCCEED;					//处理结果
	CString resInfo = "",temp = "", nodeName = "", lifelineID = "";
	HRESULT hr;
	BSTR text = NULL;								//节点值
	IXMLDOMNamedNodeMap *pAtts = NULL;				//属性节点列表
	IXMLDOMNode *aNode = NULL, *bNode = NULL;
	IXMLDOMNodeList *pNodes = NULL;					//子节点列表
	
	hr = brothers->get_length (&n);					// 获取子节点个数
	if (FAILED (hr))
	{
		AfxMessageBox ("Fail to get number of the attributes of the node!");
		//log file
		resInfo = "ERROR:Fail to find the name of occurence specification whose ID is \"" + osID + "\"\r\n\r\n"; 
		logFile.Write (resInfo, resInfo.GetLength ());
		return "";
	}
	for (i = 0; i < n; i ++)
	{
		hr = brothers->get_item (i, &aNode);
		if (FAILED (hr))
		{
			AfxMessageBox ("Fail to get the wanted child node!");
			//log file
			resInfo = "ERROR:Fail to find the name of occurence specification whose ID is \"" + osID + "\"\r\n\r\n"; 
			logFile.Write (resInfo, resInfo.GetLength ());
			continue;
		}
		hr = aNode->get_nodeName (&bstr);			// 获取子节点的名称
		if (FAILED (hr))
		{
			AfxMessageBox ("Fail to get name of the wanted chile node!");
			//log file
			resInfo = "ERROR:Fail to find the name of occurence specification whose ID is \"" + osID + "\"\r\n\r\n"; 
			logFile.Write (resInfo, resInfo.GetLength ());
			continue;
		}
		nodeName.Format ("%S",bstr);
		if (!nodeName.Compare ("fragment") || !nodeName.Compare ("formalGate"))	//成员属性类型分析
		{
			hr = aNode->get_attributes (&pAtts);
			if (FAILED (hr))
			{
				AfxMessageBox ("Failed to get attributes of the node.");
				//logfile
				resInfo = "ERROR:Fail to find the name of occurence specification whose ID is \"" + osID + "\"\r\n\r\n"; 
				logFile.Write (resInfo, resInfo.GetLength ());
				continue;
			}
			hr = pAtts->getNamedItem(L"xmi:type",& bNode);
			if (FAILED (hr))
			{
				AfxMessageBox ("Fail to get type of the attributes of the class!");
				//log file
				resInfo = "ERROR:Fail to find the name of occurence specification whose ID is \"" + osID + "\"\r\n\r\n"; 
				logFile.Write (resInfo, resInfo.GetLength ());
				continue;
			}
			hr = bNode->get_text(&text);
			temp.Format ("%S", text);
			if (temp.Compare ("uml:OccurrenceSpecification") && temp.Compare ("uml:Gate"))
				continue;
			hr = pAtts->getNamedItem(L"xmi:id",& bNode);
			if (FAILED (hr))
			{
				AfxMessageBox ("Fail to get type of the attributes of the class!");
				//log file
				resInfo = "ERROR:Fail to find the name of occurence specification whose ID is \"" + osID + "\"\r\n\r\n"; 
				logFile.Write (resInfo, resInfo.GetLength ());
				continue;
			}
			hr = bNode->get_text(&text);
			temp.Format ("%S", text);
			if (! temp.Compare (osID))
			{
				hr = pAtts->get_length (&m);					// 获取节点个数
				if (FAILED (hr))
				{
					AfxMessageBox ("Failed to get the number of attributes of the node.");
					//logfile
					resInfo = "ERROR:Fail to find the name of occurence specification whose ID is \"" + osID + "\"\r\n\r\n"; 
					logFile.Write (resInfo, resInfo.GetLength ());
					continue;
				}
				lifelineID = "";
				for (j = 0; j < m; j ++)
				{
					hr = pAtts->get_item (j, &bNode);
					if (FAILED (hr))
					{
						AfxMessageBox ("Failed to get wanted attribute of the node.");
						//logfile
						resInfo = "ERROR:Fail to find the name of occurence specification whose ID is \"" + osID + "\"\r\n\r\n"; 
						logFile.Write (resInfo, resInfo.GetLength ());
						continue;
					}
					hr = bNode->get_nodeName (&bstr);			// 获取属性节点的名称
					if (FAILED (hr))
					{
						AfxMessageBox ("Fail to get name of the wanted attribute!");
						//log file
						resInfo = "ERROR:Fail to find the name of occurence specification whose ID is \"" + osID + "\"\r\n\r\n"; 
						logFile.Write (resInfo, resInfo.GetLength ());
						continue;
					}
					nodeName.Format ("%S",bstr);
					text = NULL;
					hr = bNode->get_text (&text);				//获取属性节点的值
					if (FAILED (hr) || text == NULL)
					{
						AfxMessageBox ("Fail to get the value of wanted attribute's name!");
						//log file
						resInfo = "ERROR:Fail to find the name of occurence specification whose ID is \"" + osID + "\"\r\n\r\n"; 
						logFile.Write (resInfo, resInfo.GetLength ());
						continue;
					}
					if (!nodeName.Compare ("covered"))
					{
						lifelineID.Format ("%S", text);
						break;
					}
					else
					{
					}
				}
				break;
			}
		}
	}
	return lifelineID;
}

//********************************************************************//
//函数功能：根据关系的端点类ID找到获取其端点相关信息                  //
//参数说明：classID为待查关系的端点类ID                               //
//          endName为关系的端点名称                                   //
//          返回值为查找结果                                          //
//********************************************************************//
BOOL CUMLanalyserDlg::FindClassThroughAssociation(CString classID, CString &endName)
{
	long int i = 0, n = -1, j = 0, m = -1;
	HRESULT hr;
	BSTR text = NULL;												//节点值
	IXMLDOMNamedNodeMap *pAtts = NULL, *propertyAtts = NULL;								//属性节点列表
	IXMLDOMNode *classNode = NULL, *attributeNode = NULL, *propertyNode = NULL;;
	IXMLDOMNodeList *pNodes = NULL, *qNodes = NULL;									//子节点列表
	CString nodeName = "", temp = "", resInfo = "";

	hr = pXMLDoc->selectNodes(L"//packagedElement", &pNodes);
	if (FAILED (hr))
	{
		AfxMessageBox ("Fail to start finding parent class!");
		//log file
		resInfo = "ERROR:Fail to find the end name of associated class whose ID is \"" + classID + "\"\r\n\r\n"; 
		logFile.Write (resInfo, resInfo.GetLength ());
		return FALSE;
	}
	hr = pNodes->get_length (&n);
	if (FAILED (hr))
	{
		AfxMessageBox ("Failure occurs in the progress of finding parent class!");
		//log file
		resInfo = "ERROR:Fail to find the end name of associated class whose ID is \"" + classID + "\"\r\n\r\n"; 
		logFile.Write (resInfo, resInfo.GetLength ());
		return FALSE;
	}
	for (i = 0; i < n; i ++)
	{
		hr = pNodes->get_item (i, &classNode);
		if (FAILED (hr))
		{
			AfxMessageBox ("Fail to get wanted item!");
			//log file
			resInfo = "ERROR:Fail to find the end name of associated class whose ID is \"" + classID + "\"\r\n\r\n"; 
			logFile.Write (resInfo, resInfo.GetLength ());
			continue;
		}
		hr = classNode->get_attributes (&pAtts);
		if (FAILED (hr))
		{
			AfxMessageBox ("Fail to get attributes of wanted item!");
			//log file
			resInfo = "ERROR:Fail to find the end name of associated class whose ID is \"" + classID + "\"\r\n\r\n"; 
			logFile.Write (resInfo, resInfo.GetLength ());
			continue;
		}
		hr = pAtts->getNamedItem(L"xmi:id",& attributeNode);
		if (FAILED (hr))
		{
			AfxMessageBox ("Fail to get type of wanted item!");
			//log file
			resInfo = "ERROR:Fail to find the end name of associated class whose ID is \"" + classID + "\"\r\n\r\n"; 
			logFile.Write (resInfo, resInfo.GetLength ());
			continue;
		}
		hr = attributeNode->get_text(&text);
		if (FAILED (hr))
		{
			AfxMessageBox ("Fail to get ID information of wanted item!");
			//log file
			resInfo = "ERROR:Fail to find the end name of associated class whose ID is \"" + classID + "\"\r\n\r\n"; 
			logFile.Write (resInfo, resInfo.GetLength ());
			continue;
		}
		temp.Format ("%S",text);
		if (!temp.Compare (classID))
		{
			hr = pAtts->getNamedItem(L"name",& attributeNode);
			if (FAILED (hr))
			{
				AfxMessageBox ("Fail to get type of wanted item!");
				//log file
				resInfo = "ERROR:Fail to find the end name of associated class whose ID is \"" + classID + "\"\r\n\r\n"; 
				logFile.Write (resInfo, resInfo.GetLength ());
				continue;
			}
			hr = attributeNode->get_text(&text);
			if (FAILED (hr))
			{
				AfxMessageBox ("Fail to get ID information of wanted item!");
				//log file
				resInfo = "ERROR:Fail to find the end name of associated class whose ID is \"" + classID + "\"\r\n\r\n"; 
				logFile.Write (resInfo, resInfo.GetLength ());
				continue;
			}
			if (text == NULL) endName = "";
			else endName.Format ("%S", text);
			return TRUE;
		}
	}
	return FALSE;
}

//********************************************************************//
//函数功能：对恒等式声明节点进行判断分析                              //
//参数说明：pNode为此节点的指针                                       //
//          interactionName为此恒等式声明所在交互的名称               //
//          interactionID为此此恒等式声明所在交互的ID                 //
//          返回值为处理结果                                          //
//********************************************************************//
unsigned int CUMLanalyserDlg::InteractionSIAnalyse(IXMLDOMNode *pNode, CString interactionName, CString interactionID)
{
	long int n = -1, i = 0;
	unsigned int result = SUCCEED;					//处理结果
	CString temp = "", nodeName = "", pID = "", sql = "", resInfo = "";
	HRESULT hr;
	VARIANT_BOOL b;
	BSTR text = NULL;								//节点值
	IXMLDOMNamedNodeMap *pAtts = NULL;				//属性节点列表
	IXMLDOMNode *aNode = NULL;
	IXMLDOMNodeList *pNodes = NULL;					//子节点列表
	
	//恒等式声明属性的属性分析
	hr = pNode->get_attributes (&pAtts);
	if (FAILED (hr))
	{
		AfxMessageBox ("Fail to get attributes of the node!");
		//log file
		resInfo = "ERROR:Fail to get attributes of the state invariant node! Ignore all attributes of the node.\r\nINFO:parent interaction name:" + interactionName + "    parent interaction ID:" + interactionID + "\r\n\r\n"; 
		logFile.Write (resInfo, resInfo.GetLength ());
		return IGNORED;
	}
	hr = pAtts->getNamedItem(L"xmi:id",& aNode);
	if (FAILED (hr))
	{
		AfxMessageBox ("Fail to get the wanted attribute of the node!");
		//log file
		resInfo = "ERROR:Fail to get \"xmi:type\" of the  state invariant node! Ignore all attributes of the node.\r\nINFO:parent interaction name:" + interactionName + "    parent interaction ID:" + interactionID + "\r\n\r\n"; 
		logFile.Write (resInfo, resInfo.GetLength ());
		return IGNORED;
	}
	text = NULL;
	hr = aNode->get_text (&text);				//获取属性节点的值
	if (FAILED (hr) || text == NULL)
	{
		AfxMessageBox ("Fail to get the value of wanted attribute's name!");
		//log file
		resInfo = "ERROR:Fail to get \"xmi:type\" of the  state invariant node! Ignore all attributes of the node.\r\nINFO:parent interaction name:" + interactionName + "    parent interaction ID:" + interactionID + "\r\n\r\n"; 
		logFile.Write (resInfo, resInfo.GetLength ());
		return IGNORED;
	}
	pID.Format ("%S", text);
	try
	{
		sql = "select * from stateInvariant";									//设置查询字符串
		m_Ado.m_pRecordset = m_Ado.OpenRecordset(sql);							//打开记录集
		m_Ado.m_pRecordset->AddNew();											//添加新行
		m_Ado.m_pRecordset->PutCollect("ID", (_bstr_t)pID);						//设置ID字段内容
		m_Ado.m_pRecordset->PutCollect("所属交互", (_bstr_t)interactionName);	//设置所属交互字段内容
		m_Ado.m_pRecordset->PutCollect("所属交互ID", (_bstr_t)interactionID);	//设置所属交互字段内容
		m_Ado.m_pRecordset->Update();											//更新记录集
		m_Ado.CloseRecordset();													//关闭记录集
	}
	catch(_com_error e)
	{
		AfxMessageBox(e.Description());										//弹出错误处理
		//log file
		resInfo = "ERROR:Fail to put state invariant data into database! Ignore this database write.\r\nINFO:state invariant ID:" + pID + "    parent interaction name:" + interactionName + "    parent interaction ID:" + interactionID + "\r\n\r\n"; 
		logFile.Write (resInfo, resInfo.GetLength ());
		return IGNORED;
	}

	//类的成员属性的类型分析
	hr = pNode->hasChildNodes (&b);											//判断节点是否有孩子
	if (FAILED (hr))
	{
		AfxMessageBox ("Fail to find whether the node has child!");
		//log file
		resInfo = "ERROR:Fail to find whether the node has child! Ignore all these child nodes.\r\nINFO:state invariant ID:" + pID+ "    parent interaction name:" + interactionName + "    parent interaction ID:" + interactionID + "\r\n\r\n"; 
		logFile.Write (resInfo, resInfo.GetLength ());
		return IGNORED;
	}
	if (!b)											//没有子节点(即没有成员属性和方法)
	{
		return result;
	}

	hr = pNode->get_childNodes (&pNodes);			//获取子节点
	if (FAILED (hr))
	{
		AfxMessageBox ("Fail to get child nodes of the node!");
		//log file
		resInfo = "ERROR:Fail to get child nodes of the state invariant! Ignore all these child nodes.\r\nINFO:state invariant ID:" +  pID+ "    parent interaction name:" + interactionName + "    parent interaction ID:" + interactionID + "\r\n\r\n"; 
		logFile.Write (resInfo, resInfo.GetLength ());
		return IGNORED;
	}
	hr = pNodes->get_length (&n);					// 获取子节点个数
	if (FAILED (hr))
	{
		AfxMessageBox ("Fail to get number of the attributes of the node!");
		//log file
		resInfo = "ERROR:Fail to get number child nodes of the state invariant! Ignore all these child nodes.\r\nINFO:state invariant ID:" +  pID+ "    parent interaction name:" + interactionName + "    parent interaction ID:" + interactionID + "\r\n\r\n"; 
		logFile.Write (resInfo, resInfo.GetLength ());
		return IGNORED;
	}
	for (i = 0; i < n; i ++)
	{

		hr = pNodes->get_item (i, &aNode);
		if (FAILED (hr))
		{
			AfxMessageBox ("Fail to get the wanted child node!");
			//log file
			temp.Format ("%d", i);
			resInfo = "ERROR:Fail to get ith child node of the state invariant! Ignore thise child node.\r\nINFO:state invariant ID:" +  pID+ "    parent interaction name:" + interactionName + "    parent interaction ID:" + interactionID + "    i:" + temp + "\r\n\r\n"; 
			logFile.Write (resInfo, resInfo.GetLength ());
			if (result == SUCCEED) result = IGNORED;
			continue;
		}
		hr = aNode->get_nodeName (&bstr);			// 获取子节点的名称
		if (FAILED (hr))
		{
			AfxMessageBox ("Fail to get name of the wanted chile node!");
			//log file
			temp.Format ("%d", i);
			resInfo = "ERROR:Fail to get ith child node of the state invariant! Ignore thise child node.\r\nINFO:state invariant ID:" +  pID+ "    parent interaction name:" + interactionName + "    parent interaction ID:" + interactionID + "    i:" + temp + "\r\n\r\n"; 
			logFile.Write (resInfo, resInfo.GetLength ());
			if (result == SUCCEED) result = IGNORED;
			continue;
		}
		nodeName.Format ("%S",bstr);
		text = NULL;
		hr = aNode->get_text (&text);						//获取属性节点的值
		if (FAILED (hr) || text == NULL)
		{
			AfxMessageBox ("Fail to get the value of wanted child's name!");
			//log file
			temp.Format ("%d", i);
			resInfo = "ERROR:Fail to get the ith child node of the state invariant! Ignore thise child node.\r\nINFO:state invariant ID:" +  pID+ "    parent interaction name:" + interactionName + "    parent interaction ID:" + interactionID + "    i:" + temp + "\r\n\r\n"; 
			logFile.Write (resInfo, resInfo.GetLength ());
			if (result == SUCCEED) result = IGNORED;
			continue;
		}
		if (!nodeName.Compare ("invariant"))			//成员属性类型分析
		{
			InteractionSiInvariantAnalyse (aNode, pID);
		}
		else
		{
			//logfile
			temp.Format ("%d", i);
			resInfo = "IGNORE:Ignore the ith child node of type \"" + nodeName + "\" of the state invariant! Ignore thise child node.\r\nINFO:state invariant ID:" +  pID+ "    parent interaction name:" + interactionName + "    parent interaction ID:" + interactionID + "    i:" + temp + "\r\n\r\n"; 
			logFile.Write (resInfo, resInfo.GetLength ());
			if (result == SUCCEED) result = IGNORED;
			continue;
		}
	}
	return SUCCEED;
}

//********************************************************************//
//函数功能：对恒等式声明约束条件节点进行分析                          //
//参数说明：pNode为此节点的指针                                       //
//          interactionSiName为此约束条件所在恒等式声明的名称         //
//          interactionSiID为此此约束条件所在恒等式声明的ID           //
//          返回值为处理结果                                          //
//********************************************************************//
unsigned int CUMLanalyserDlg::InteractionSiInvariantAnalyse(IXMLDOMNode *pNode, CString interactionSiID)
{
	long int n = -1, i = 0, m = -1, j = 0;
	unsigned int result = SUCCEED;					//处理结果
	CString resInfo = "", temp = "", nodeName = "", pID = "", pspecificationID = "", ptype = "", pconstraint = "", sql = "";
	HRESULT hr;
	VARIANT_BOOL b;
	BSTR text = NULL;								//节点值
	IXMLDOMNamedNodeMap *pAtts = NULL;				//属性节点列表
	IXMLDOMNode *aNode = NULL, *bNode = NULL;
	IXMLDOMNodeList *pNodes = NULL, *qNodes = NULL;	//子节点列表
	
	//恒等式声明约束条件的属性分析
	hr = pNode->get_attributes (&pAtts);
	if (FAILED (hr))
	{
		AfxMessageBox ("Fail to get attributes of the node!");
		//log file
		resInfo = "ERROR:Fail to get attributes of the SI invariant node! Ignore all attributes of the node.\r\nINFO:parent state invariant ID:" + interactionSiID + "\r\n\r\n"; 
		logFile.Write (resInfo, resInfo.GetLength ());
		return IGNORED;
	}
	hr = pAtts->getNamedItem(L"xmi:type",& aNode);
	if (FAILED (hr))
	{
		AfxMessageBox ("Fail to get type of the attributes of the class!");
		//log file
		resInfo = "ERROR:Fail to get \"xmi:type\" of the SI invariant node! Ignore all attributes of the node.\r\nINFO:parent state invariant ID:" + interactionSiID + "\r\n\r\n"; 
		logFile.Write (resInfo, resInfo.GetLength ());
		return IGNORED;
	}
	hr = aNode->get_text(&text);
	temp.Format ("%S",text);
	if (temp.Compare ("uml:Constraint"))
	{
		//log file
		resInfo = "IGNORE:Ignore a node of uml type \"" + temp + "\" of the SI invariant node! Ignore all attributes of the node.\r\nINFO:parent state invariant ID:" + interactionSiID + "\r\n\r\n"; 
		logFile.Write (resInfo, resInfo.GetLength ());
		return IGNORED;
	}

	hr = pAtts->getNamedItem(L"xmi:id",& aNode);
	if (FAILED (hr))
	{
		AfxMessageBox ("Fail to get type of the attributes of the class!");
		//log file
		resInfo = "ERROR:Fail to get \"xmi:id\" of the SI invariant node! Ignore all attributes of the node.\r\nINFO:parent state invariant ID:" + interactionSiID + "\r\n\r\n"; 
		logFile.Write (resInfo, resInfo.GetLength ());
		return IGNORED;
	}
	hr = aNode->get_text(&text);
	if (FAILED (hr))
	{
		AfxMessageBox ("Fail to get value of type of the attributes of the class!");
		//log file
		resInfo = "ERROR:Fail to get \"xmi:id\" of the SI invariant node! Ignore all attributes of the node.\r\nINFO:parent state invariant ID:" + interactionSiID + "\r\n\r\n"; 
		logFile.Write (resInfo, resInfo.GetLength ());
		return IGNORED;
	}
	pID.Format ("%S", text);

	//约束的具体条分析
	hr = pNode->hasChildNodes (&b);											//判断节点是否有孩子
	if (FAILED (hr))
	{
		AfxMessageBox ("Fail to find whether the node has child!");
		//log file
		resInfo = "ERROR:Fail to find whether the node has child! Ignore all these child nodes.\r\nINFO:parent state invariant ID:" + interactionSiID + "\r\n\r\n"; 
		logFile.Write (resInfo, resInfo.GetLength ());
		return IGNORED;
	}
	if (!b)											//没有子节点
	{
		return IGNORED;
	}

	hr = pNode->get_childNodes (&pNodes);			//获取子节点
	if (FAILED (hr))
	{
		AfxMessageBox ("Fail to get attributes of the node!");
		//log file
		resInfo = "ERROR:Fail to get child nodes of the SI invariant node! Ignore all these child nodes.\r\nINFO:parent state invariant ID:" + interactionSiID + "\r\n\r\n"; 
		logFile.Write (resInfo, resInfo.GetLength ());
		return IGNORED;
	}
	hr = pNodes->get_length (&n);					// 获取子节点个数
	if (FAILED (hr))
	{
		AfxMessageBox ("Fail to get number of the attributes of the node!");
		//log file
		resInfo = "ERROR:Fail to get number of child nodes of the SI invariant node! Ignore all these child nodes.\r\nINFO:parent state invariant ID:" + interactionSiID + "\r\n\r\n"; 
		logFile.Write (resInfo, resInfo.GetLength ());
		return IGNORED;
	}
	for (i = 0; i < n; i ++)
	{

		hr = pNodes->get_item (i, &aNode);
		if (FAILED (hr))
		{
			AfxMessageBox ("Fail to get the wanted child node!");
			//log file
			temp.Format ("%d", i);
			resInfo = "ERROR:Fail to get the ith child node of the SI invariant node! Ignore this child node.\r\nINFO:parent state invariant ID:" + interactionSiID + "    i:" + temp + "\r\n\r\n"; 
			logFile.Write (resInfo, resInfo.GetLength ());
			if (result == SUCCEED) result = IGNORED;
			continue;
		}
		hr = aNode->get_nodeName (&bstr);			// 获取子节点的名称
		if (FAILED (hr))
		{
			AfxMessageBox ("Fail to get name of the wanted chile node!");
			//log file
			temp.Format ("%d", i);
			resInfo = "ERROR:Fail to get the ith child node of the SI invariant node! Ignore this child node.\r\nINFO:parent state invariant ID:" + interactionSiID + "    i:" + temp + "\r\n\r\n"; 
			logFile.Write (resInfo, resInfo.GetLength ());
			if (result == SUCCEED) result = IGNORED;
			continue;
		}
		nodeName.Format ("%S",bstr);
		text = NULL;
		hr = aNode->get_text (&text);						//获取属性节点的值
		if (FAILED (hr) || text == NULL)
		{
			AfxMessageBox ("Fail to get the value of wanted child's name!");
			//log file
			temp.Format ("%d", i);
			resInfo = "ERROR:Fail to get the ith child node of the SI invariant node! Ignore this child node.\r\nINFO:parent state invariant ID:" + interactionSiID + "    i:" + temp + "\r\n\r\n"; 
			logFile.Write (resInfo, resInfo.GetLength ());
			if (result == SUCCEED) result = IGNORED;
			continue;
		}
		if (!nodeName.Compare ("specification"))			//成员属性类型分析
		{
			hr = aNode->get_attributes (&pAtts);
			if (FAILED (hr))
			{
				AfxMessageBox ("Failed to get attributes of the node.");
				//logfile
				resInfo = "ERROR:Fail to get the specific invariant condition of the SI invariant node! Ignore this child node.\r\nINFO:parent state invariant ID:" + interactionSiID + "\r\n\r\n"; 
				logFile.Write (resInfo, resInfo.GetLength ());
				if (result == SUCCEED) result = IGNORED;
				continue;
			}
			hr = pAtts->get_length (&m);					// 获取节点个数
			if (FAILED (hr))
			{
				AfxMessageBox ("Failed to get the number of attributes of the node.");
				//logfile
				resInfo = "ERROR:Fail to get the specific invariant condition of the SI invariant node! Ignore this child node.\r\nINFO:parent state invariant ID:" + interactionSiID + "\r\n\r\n"; 
				logFile.Write (resInfo, resInfo.GetLength ());
				if (result == SUCCEED) result = IGNORED;
				continue;
			}
			for (j = 0; j < m; j ++)
			{
				hr = pAtts->get_item (j, &bNode);
				if (FAILED (hr))
				{
					AfxMessageBox ("Failed to get wanted attribute of the node.");
					//logfile
					resInfo = "ERROR:Fail to get the specific invariant condition of the SI invariant node! Ignore this child node.\r\nINFO:parent state invariant ID:" + interactionSiID + "\r\n\r\n"; 
					logFile.Write (resInfo, resInfo.GetLength ());
					if (result == SUCCEED) result = IGNORED;
					continue;
				}
				hr = bNode->get_nodeName (&bstr);			// 获取属性节点的名称
				if (FAILED (hr))
				{
					AfxMessageBox ("Fail to get name of the wanted attribute!");
					//log file
					resInfo = "ERROR:Fail to get the specific invariant condition of the SI invariant node! Ignore this child node.\r\nINFO:parent state invariant ID:" + interactionSiID + "\r\n\r\n"; 
					logFile.Write (resInfo, resInfo.GetLength ());
					if (result == SUCCEED) result = IGNORED;
					continue;
				}
				nodeName.Format ("%S",bstr);
				text = NULL;
				hr = bNode->get_text (&text);				//获取属性节点的值
				if (FAILED (hr) || text == NULL)
				{
					AfxMessageBox ("Fail to get the value of wanted attribute's name!");
					//log file
					resInfo = "ERROR:Fail to get the specific invariant condition of the SI invariant node! Ignore this child node.\r\nINFO:parent state invariant ID:" + interactionSiID + "\r\n\r\n"; 
					logFile.Write (resInfo, resInfo.GetLength ());
					if (result == SUCCEED) result = IGNORED;
					continue;
				}
				if (!nodeName.Compare ("xmi:id"))
				{
					pspecificationID.Format ("%S", text);
				}
				else if (!nodeName.Compare ("xmi:type"))
				{
					ptype.Format ("%S", text);
				}
				else
				{
				}
			}

			//child
			//类的成员属性的类型分析
			hr = aNode->hasChildNodes (&b);											//判断节点是否有孩子
			if (FAILED (hr))
			{
				AfxMessageBox ("Fail to find whether the node has child!");
				//log file
				resInfo = "ERROR:Fail to get the specific invariant condition of the SI invariant node! Ignore this child node.\r\nINFO:parent state invariant ID:" + interactionSiID + "\r\n\r\n"; 
				logFile.Write (resInfo, resInfo.GetLength ());
				if (result == SUCCEED) result = IGNORED;
				continue;
			}
			if (!b)											//没有子节点(即没有成员属性和方法)
			{
				try
				{
					sql = "select * from invariant";													//设置查询字符串
					m_Ado.m_pRecordset = m_Ado.OpenRecordset(sql);									//打开记录集
					m_Ado.m_pRecordset->AddNew();													//添加新行
					m_Ado.m_pRecordset->PutCollect("ID", (_bstr_t)pID);								//设置ID字段内容
					m_Ado.m_pRecordset->PutCollect("详细条件ID", (_bstr_t)pspecificationID);		//设置详细条件ID字段内容
					m_Ado.m_pRecordset->PutCollect("类型", (_bstr_t)ptype);							//设置类型字段内容
					m_Ado.m_pRecordset->PutCollect("所属恒等式声明ID", (_bstr_t)interactionSiID);	//设置所属恒等式声明ID字段内容
					m_Ado.m_pRecordset->Update();													//更新记录集
					m_Ado.CloseRecordset();															//关闭记录集
				}
				catch(_com_error e)
				{
					AfxMessageBox(e.Description());										//弹出错误处理
					//log file
					resInfo = "ERROR:Fail to get the specific invariant condition of the SI invariant node! Ignore this child node.\r\nINFO:ID:" + pID + "    specific condition ID" + pspecificationID + "    parent state invariant ID:" + interactionSiID + "\r\n\r\n"; 
					logFile.Write (resInfo, resInfo.GetLength ());
					return IGNORED;
				}
				return SUCCEED;
			}

			hr = aNode->get_childNodes (&qNodes);			//获取子节点
			if (FAILED (hr))
			{
				AfxMessageBox ("Fail to get attributes of the node!");
				//log file
				resInfo = "ERROR:Fail to get the specific invariant condition of the SI invariant node! Ignore this child node.\r\nINFO:parent state invariant ID:" + interactionSiID + "\r\n\r\n"; 
				logFile.Write (resInfo, resInfo.GetLength ());
				if (result == SUCCEED) result = IGNORED;
				continue;
			}
			hr = qNodes->get_length (&m);					// 获取子节点个数
			if (FAILED (hr))
			{
				AfxMessageBox ("Fail to get number of the attributes of the node!");
				//log file
				resInfo = "ERROR:Fail to get the specific invariant condition of the SI invariant node! Ignore this child node.\r\nINFO:parent state invariant ID:" + interactionSiID + "\r\n\r\n"; 
				logFile.Write (resInfo, resInfo.GetLength ());
				if (result == SUCCEED) result = IGNORED;
				continue;
			}
			for (j = 0; j < m; j ++)
			{
				hr = qNodes->get_item (i, &bNode);
				if (FAILED (hr))
				{
					AfxMessageBox ("Fail to get the wanted child node!");
					//log file
					resInfo = "ERROR:Fail to get the specific invariant condition of the SI invariant node! Ignore this child node.\r\nINFO:parent state invariant ID:" + interactionSiID + "\r\n\r\n"; 
					logFile.Write (resInfo, resInfo.GetLength ());
					if (result == SUCCEED) result = IGNORED;
					continue;
				}
				hr = bNode->get_nodeName (&bstr);			// 获取子节点的名称
				if (FAILED (hr))
				{
					AfxMessageBox ("Fail to get name of the wanted chile node!");
					//log file
					resInfo = "ERROR:Fail to get the specific invariant condition of the SI invariant node! Ignore this child node.\r\nINFO:parent state invariant ID:" + interactionSiID + "\r\n\r\n"; 
					logFile.Write (resInfo, resInfo.GetLength ());
					if (result == SUCCEED) result = IGNORED;
					continue;
				}
				nodeName.Format ("%S",bstr);
				text = NULL;
				hr = bNode->get_text (&text);						//获取属性节点的值
				if (FAILED (hr) || text == NULL)
				{
					AfxMessageBox ("Fail to get the value of wanted child's name!");
					//log file
					resInfo = "ERROR:Fail to get the specific invariant condition of the SI invariant node! Ignore this child node.\r\nINFO:parent state invariant ID:" + interactionSiID + "\r\n\r\n"; 
					logFile.Write (resInfo, resInfo.GetLength ());
					if (result == SUCCEED) result = IGNORED;
					continue;
				}
				if (!nodeName.Compare ("body"))			//成员属性类型分析
				{
					pconstraint.Format ("%S", text);
				}
			}
			try
			{
				sql = "select * from invariant";													//设置查询字符串
				m_Ado.m_pRecordset = m_Ado.OpenRecordset(sql);									//打开记录集
				m_Ado.m_pRecordset->AddNew();													//添加新行
				m_Ado.m_pRecordset->PutCollect("ID", (_bstr_t)pID);								//设置ID字段内容
				m_Ado.m_pRecordset->PutCollect("详细条件ID", (_bstr_t)pspecificationID);		//设置详细条件ID字段内容
				m_Ado.m_pRecordset->PutCollect("类型", (_bstr_t)ptype);							//设置类型字段内容
				m_Ado.m_pRecordset->PutCollect("约束条件", (_bstr_t)pconstraint);				//设置约束条件字段内容
				m_Ado.m_pRecordset->PutCollect("所属恒等式声明ID", (_bstr_t)interactionSiID);	//设置所属恒等式声明ID字段内容
				m_Ado.m_pRecordset->Update();													//更新记录集
				m_Ado.CloseRecordset();															//关闭记录集
			}
			catch(_com_error e)
			{
				AfxMessageBox(e.Description());										//弹出错误处理
				//log file
				resInfo = "ERROR:Fail to get the specific invariant condition of the SI invariant node! Ignore this child node.\r\nINFO:ID:" + pID + "    specific condition ID" + pspecificationID + "    parent state invariant ID:" + interactionSiID + "\r\n\r\n"; 
				logFile.Write (resInfo, resInfo.GetLength ());
				return IGNORED;
			}
		}
		else
		{
			//logfile			
			resInfo = "IGNORE:Ignore a node of \"" + nodeName + "\" and its child nodes.\r\nINFO:parent state invariant ID:" + interactionSiID + "\r\n\r\n"; 
			logFile.Write (resInfo, resInfo.GetLength ());
			if (result == SUCCEED) result = IGNORED;
		}
	}
	return SUCCEED;
}

//********************************************************************//
//函数功能：处理“日志”按钮的操作，打开对应的日志文件并显示在编辑框  //
//********************************************************************//
void CUMLanalyserDlg::OnButtonLog() 
{
	// TODO: Add your control notification handler code here
	GetDlgItem (IDC_BUTTON_OPEN)->EnableWindow(FALSE);		//使打开按钮无效化
	m_Edit.ShowWindow (FALSE);								//隐藏xml内容
	m_Txt.ShowWindow (FALSE);								//隐藏导出结果
	m_Log.ShowWindow (TRUE);								//显示日志内容
	GetDlgItem(IDC_BUTTON_TXTCANCEL)->ShowWindow(SW_HIDE);	//隐藏退出导出结果按钮
	GetDlgItem(IDC_BUTTON_LOGCANCEL)->ShowWindow(SW_SHOW);	//显示退出查看日志按钮

	logFile.Open (logPath, CFile::modeRead);
	char * pBuf;
	int iLen = logFile.GetLength ();
	pBuf =new char [iLen+1];
	logFile.Read (pBuf, iLen);
	pBuf [iLen]=0;
	logContent.Format ("%s", pBuf);
	m_Log.SetWindowText (logContent);
	logFile.Close();
}

//********************************************************************//
//函数功能：处理“退出”按钮的操作，退出查看日志界面                  //
//********************************************************************//
void CUMLanalyserDlg::OnButtonLogcancel() 
{
	// TODO: Add your control notification handler code herem_Edit.ShowWindow (TRUE);
	m_Log.ShowWindow (FALSE);								//隐藏日志内容
	m_Edit.ShowWindow (TRUE);								//显示xml内容
	GetDlgItem(IDC_BUTTON_LOGCANCEL)->ShowWindow(SW_HIDE);	//隐藏退出查看日志按钮
	GetDlgItem (IDC_BUTTON_OPEN)->EnableWindow(TRUE);		//使打开按钮有效化
}

//********************************************************************//
//函数功能：处理“导出”按钮的操作，将选定的数据库内容导出为xml文件   //
//********************************************************************//
void CUMLanalyserDlg::OnButtonTxt() 
{
	// TODO: Add your control notification handler code here

	CString dbPath = "", temp = "";

	CFileDialog dlg(TRUE,NULL,NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,
		"All Files(*.mdb)|*.mdb||",AfxGetMainWnd());			//构造“文件打开”对话框
	if(dlg.DoModal() == IDOK)									//判断按下“打开”
	{
		GetDlgItem (IDC_BUTTON_OPEN)->EnableWindow(FALSE);		//使打开按钮无效化
		m_Edit.ShowWindow (FALSE);								//隐藏xml内容
		m_Log.ShowWindow (FALSE);								//隐藏日志内容
		m_Txt.ShowWindow (TRUE);								//显示导出结果
		GetDlgItem(IDC_BUTTON_LOGCANCEL)->ShowWindow(SW_HIDE);	//隐藏退出查看日志按钮
		GetDlgItem(IDC_BUTTON_TXTCANCEL)->ShowWindow(SW_SHOW);	//显示退出导出结果按钮
		//打开
		
		m_Txt.SetWindowText ("");
		dbPath = dlg.GetPathName ();
		if (SetTxtPath (dbPath))
		{
			if (ExportDatabase (dbPath))
			{
				//temp = "导出成功! 结果已被导入 " + txtPath;
				temp = "导出成功! 类模型已被导入 " + xsdPath + "\r\n" + "类关系模型已被导入" +  xml4RelaPath;
				AfxMessageBox (temp, MB_ICONINFORMATION | MB_OK, 0);

				CFile txtFile;
				txtFile.Open (txtPath, CFile::modeRead);
				char * pBuf;
				int iLen = txtFile.GetLength ();
				pBuf =new char [iLen+1];
				txtFile.Read (pBuf, iLen);
				pBuf [iLen]=0;
				txtContent.Format ("%s", pBuf);
				m_Txt.SetWindowText (txtContent);
				txtFile.Close();
				return;
			}
			else
			{
				AfxMessageBox ("Error occurs during exporting mdb file into file!");
				return;
			}
		}
		else
		{
			AfxMessageBox ("Error occurs during generating the file path of result file!");
			return;
		}
	}
	return;	
}

//********************************************************************//
//函数功能：处理“退出”按钮的操作，退出导出结果界面                  //
//********************************************************************//
void CUMLanalyserDlg::OnButtonTxtcancel() 
{
	// TODO: Add your control notification handler code here
	m_Edit.ShowWindow (TRUE);								//显示xml内容
	m_Txt.ShowWindow (FALSE);								//隐藏导出结果
	GetDlgItem(IDC_BUTTON_TXTCANCEL)->ShowWindow(SW_HIDE);	//隐藏退出导出结果按钮
	GetDlgItem (IDC_BUTTON_OPEN)->EnableWindow(TRUE);		//使打开按钮有效化
}

//********************************************************************//
//函数功能：设置存储导出结果的xml文件以及xsd文件的路径及名称                     //
//********************************************************************//
BOOL CUMLanalyserDlg::SetTxtPath(CString dbPath)
{
	TCHAR exeFullPath [MAX_PATH];
	GetModuleFileName (NULL,exeFullPath,MAX_PATH);
	CString temp;
	txtPath.Format ("%s", exeFullPath);
	int i = txtPath.ReverseFind ('\\');
	int len = txtPath.GetLength();
	txtPath.Delete (i, len - i);
	i = dbPath.ReverseFind ('\\');
	len = dbPath.GetLength ();
	temp = dbPath.Right (len - i);
	i = temp.ReverseFind ('.');
	len = temp.GetLength ();
	temp.Delete (i, len - i);
	txtPath += temp;
	xsdPath = txtPath +"-model-class"+ ".xsd";
	xml4RelaPath=txtPath +"-TSmodel-relationship"+ ".xml";
	txtPath += ".xml";
	return TRUE;
}

//********************************************************************//
//函数功能：将string数据按照指定的分隔符割开  split(sss,"__",Array1); 将sss按照“__”分隔后放到Array1 //
//********************************************************************//
int split(string &str1_31,string c_31,vector<string> &Array_31)//字符分割函数
{
	int cleng_31=c_31.size();//分割符号长度
	int weii_31=0;//分割符号位置
	int readi_31=0;//读数据开始位置
	do{   
	   weii_31=str1_31.find(c_31.c_str(),readi_31);   
	   Array_31.push_back(str1_31.substr(readi_31,weii_31-readi_31));
	   readi_31=weii_31+cleng_31;//读数据位置前移     
	   }while(weii_31!=string::npos);
	return 0; 
}
//********************************************************************//
//函数功能：从数据库导出类信息结果的到xml文件,xsd文件                         //gyy add 2015
//********************************************************************//
BOOL CUMLanalyserDlg::ExportDatabase(CString dbPath)
{
	//从数据库导出类信息结果的到xml文件
	CFile txtFile;
	ADO dbAdo;
	BOOL hasReturn = FALSE;
	CString sql[4], temp = "", parameterTemp = "";
	CString packageName = "", packageID = "", className ="", classID = "";
	CString attributeName = "", attributeType = "", attributeDefault = "";
	CString operationName = "", operationID = "";
	CString parameterName = "", parameterType = "", parameterDirection = "";
	CString associationName = "", associationType = "", associationDirection = "";
	CString end1Name = "", end1Role = "", end1Multi = "";

	CString tempAss="\t\t<associationList>\r\n";	
		//txtFile.Write (tempAss, tempAss.GetLength ());
		CString tempAgg="\t\t<aggregationList>\r\n";
		//txtFile.Write (tempAgg, tempAgg.GetLength ());
		CString tempCom="\t\t<compositionList>\r\n";
		//txtFile.Write (tempCom, tempCom.GetLength ());
		CString tempGen="";
		//txtFile.Write (tempGen, tempGen.GetLength ());

	if(true){
		dbAdo.OnInitADOConn (dbPath);										//连接数据库	

	//创建并打开xml文件
	if (! txtFile.Open (txtPath, CFile::modeCreate | CFile::modeWrite))	//打开失败
	{
		AfxMessageBox ("Failed to create an open xml file!");
		return FALSE;
	}

	//获取包信息
	sql [0]= "select 名称, ID from package";
	dbAdo.m_pRecordsets [0] = dbAdo.OpenRecordsets (sql[0], 0);
	dbAdo.m_pRecordsets [0] -> Requery (0);
	//while (!dbAdo.m_pRecordsets [0] -> adoEOF)
	//{
		packageName = (char *)(_bstr_t) dbAdo.m_pRecordsets [0] -> GetCollect ("名称");
		packageID = (char *)(_bstr_t) dbAdo.m_pRecordsets [0] -> GetCollect ("ID");
		////////////////////////////////////////////temp = "[包名]" + packageName + "\r\n\r\n";
		//xml头部编写
		temp = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\r\n";
		temp += "<containmentSetInfo xmlns=\"http://www.bupt.edu.cn/xml-namespace/UMLModelOutput\" ";
		temp += "xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xsi:schemaLocation=\"http://www.bupt.edu.cn/xml-namespace/UMLModelOutput\r\n";           
	    temp +="D:\\Backup\\UMLanalyser\\UMLModelOutpu.xsd\">\r\n";
		temp += "\t<classSet>\r\n";
		txtFile.Write (temp, temp.GetLength ());

		//获取类信息
		sql [1] = "select 名称, ID from class where 所属包ID = '" + packageID + "'";
		dbAdo.m_pRecordsets [1] = dbAdo.OpenRecordsets (sql[1], 1);
		dbAdo.m_pRecordsets [1] -> Requery (0);
		while (!dbAdo.m_pRecordsets [1] -> adoEOF)
		{
			className = (char *)(_bstr_t) dbAdo.m_pRecordsets [1] -> GetCollect ("名称");

			//测试程序
			//string a=className.GetBuffer(0); 
			//CString className1="";
			//className1.Format( "%s",a.data()); 

			classID = (char *)(_bstr_t) dbAdo.m_pRecordsets [1] -> GetCollect ("ID");
			/////////////////////////temp = "------[类名]" + className + "\r\n";
			temp="\t\t<class>\r\n";
			temp+="\t\t\t<className>"+ className+"</className>\r\n";
			txtFile.Write (temp, temp.GetLength ());

			//获取类属性信息
			sql [2] = "select 名称, 类型, 初始值 from attribute where 所属类ID = '" + classID + "'";
			dbAdo.m_pRecordsets [2] = dbAdo.OpenRecordsets (sql[2], 2);
			dbAdo.m_pRecordsets [2] -> Requery (0);
			temp="\t\t\t<attributeSet>\r\n";
			txtFile.Write (temp, temp.GetLength ());
			while (!dbAdo.m_pRecordsets [2] -> adoEOF)
			{
				attributeName = (char *)(_bstr_t) dbAdo.m_pRecordsets [2] -> GetCollect ("名称");
				attributeType = (char *)(_bstr_t) dbAdo.m_pRecordsets [2] -> GetCollect ("类型");
				temp="\t\t\t\t<item>\r\n";
				temp+="\t\t\t\t\t<name>"+ attributeName+"</name>\r\n";

				string attributeT=attributeType.GetBuffer(0); 
				vector<string> Array1;
				split(attributeT,"__",Array1);
				if(Array1.size()==2)
				{
					CString attributeTy="";
					attributeTy.Format( "%s",Array1[1].data()); 
					temp+="\t\t\t\t\t<type>"+ attributeTy+"</type>\r\n";
				}
				else
				{
					CString attributeTy="";
					attributeTy.Format( "%s",Array1[2].data()); 
					temp+="\t\t\t\t\t<type>"+ attributeTy+"</type>\r\n";
				}
			    //CString className1="";
			     //className1.Format( "%s",a.data()); 

				
				///////////////////////////temp+="\t\t\t\t\t<type>"+ attributeType+"</type>\r\n";
				temp+="\t\t\t\t</item>\r\n";
				txtFile.Write (temp, temp.GetLength ());

				dbAdo.m_pRecordsets [2] -> MoveNext ();
			}
			temp="\t\t\t</attributeSet>\r\n";
			txtFile.Write (temp, temp.GetLength ());

			//获取类方法信息
			sql [2] = "select 名称, ID from operation where 所属类ID = '" + classID + "'";
			dbAdo.m_pRecordsets [2] = dbAdo.OpenRecordsets (sql[2], 2);
			dbAdo.m_pRecordsets [2] -> Requery (0);
			temp="\t\t\t<operationSet>\r\n";
			txtFile.Write (temp, temp.GetLength ());
			while (!dbAdo.m_pRecordsets [2] -> adoEOF)
			{
				operationName = (char *)(_bstr_t) dbAdo.m_pRecordsets [2] -> GetCollect ("名称");
				operationID = (char *)(_bstr_t) dbAdo.m_pRecordsets [2] -> GetCollect ("ID");
				/////////////////////////////////temp = "------------[方法]";
				temp="\t\t\t\t<operation>\r\n";
				txtFile.Write (temp, temp.GetLength ());
				//获取方法参数信息
				parameterTemp = "";
				hasReturn = FALSE;
				sql [3] = "select 名称, 类型, 方向 from parameter where 所属方法ID = '" + operationID + "'";
				dbAdo.m_pRecordsets [3] = dbAdo.OpenRecordsets (sql[3], 3);
				dbAdo.m_pRecordsets [3] -> Requery (0);
				while (!dbAdo.m_pRecordsets [3] -> adoEOF)
				{
					parameterName = (char *)(_bstr_t) dbAdo.m_pRecordsets [3] -> GetCollect ("名称");
					parameterType = (char *)(_bstr_t) dbAdo.m_pRecordsets [3] -> GetCollect ("类型");
					parameterDirection = (char *)(_bstr_t) dbAdo.m_pRecordsets [3] -> GetCollect ("方向");
					
					if (! parameterName.Compare ("return") && ! parameterDirection.Compare ("return"))
					{
						hasReturn = TRUE;
						/////////////////////////////////temp += parameterType;
						/////////////////////////////////temp += " ";
						/////////////////////////////////temp += operationName;
						/////////////////////////////////temp += " ( ";
						temp="\t\t\t\t\t<name>"+operationName+"</name>\r\n";

						string attributeT=parameterType.GetBuffer(0); 
						vector<string> Array1;
						split(attributeT,"__",Array1);
						if(Array1.size()==2)
						{
							CString attributeTy="";
							attributeTy.Format( "%s",Array1[1].data()); 
							temp+="\t\t\t\t\t<returnType>"+attributeTy+"</returnType>\r\n";
						}
						else
						{
							CString attributeTy="";
							attributeTy.Format( "%s",Array1[2].data()); 
							temp+="\t\t\t\t\t<returnType>"+attributeTy+"</returnType>\r\n";
						}

						///////////////////////////temp+="\t\t\t\t\t<returnType>"+parameterType+"</returnType>\r\n";
		
					}
					else
					{
						/////////////////////////////////parameterTemp += "[";
						/////////////////////////////////parameterTemp += parameterType;
						/////////////////////////////////parameterTemp += "]";
						/////////////////////////////////parameterTemp += parameterName;
						/////////////////////////////////parameterTemp += " ";
						parameterTemp+="\t\t\t\t\t\t<item>\r\n";
						parameterTemp+="\t\t\t\t\t\t\t<name>"+parameterName+"</name>\r\n";

						string attributeT=parameterType.GetBuffer(0); 
						vector<string> Array1;
						split(attributeT,"__",Array1);
						if(Array1.size()==2)
						{
							CString attributeTy="";
							attributeTy.Format( "%s",Array1[1].data()); 
							parameterTemp+="\t\t\t\t\t\t\t<type>"+ attributeTy+"</type>\r\n";
						}
						else
						{
							CString attributeTy="";
							attributeTy.Format( "%s",Array1[2].data()); 
							parameterTemp+="\t\t\t\t\t\t\t<type>"+ attributeTy+"</type>\r\n";
						}

						//////////////////////////////parameterTemp+="\t\t\t\t\t\t\t<type>"+parameterType+"</type>\r\n";
						parameterTemp+="\t\t\t\t\t\t</item>\r\n";
					}

					dbAdo.m_pRecordsets [3] -> MoveNext ();
				}
				if (! hasReturn)
				{
					temp += operationName;
					temp += " ( ";
				}
				temp+="\t\t\t\t\t<parameterList>\r\n";
				temp+=parameterTemp;
				temp+="\t\t\t\t\t</parameterList>\r\n";
				temp+="\t\t\t\t</operation>\r\n";
				
				////////////////////////////////////////////////temp += parameterTemp;
				////////////////////////////////////////////////temp += ")\r\n";
				txtFile.Write (temp, temp.GetLength ());
				dbAdo.m_pRecordsets [2] -> MoveNext ();
			}
			temp="\t\t\t</operationSet>\r\n";
			//////////////////////////////////////////txtFile.Write ("\r\n\r\n", 2);
			temp+="\t\t</class>\r\n";
			txtFile.Write (temp, temp.GetLength ());
			dbAdo.m_pRecordsets [1]-> MoveNext ();
		}
		temp="\t</classSet>\r\n";
		txtFile.Write (temp, temp.GetLength ());
		//获取关系信息
		temp ="\t<relationshipSet>\r\n";	
		txtFile.Write (temp, temp.GetLength ());

		sql [1] = "select 名称, 类一, 类一角色名, 类一重数, 类二, 类二角色名, 类二重数, 类型 , 方向 from association where 所属包ID = '" + packageID + "'";
		dbAdo.m_pRecordsets [1] = dbAdo.OpenRecordsets (sql[1], 1);
		dbAdo.m_pRecordsets [1] -> Requery (0);
		while (!dbAdo.m_pRecordsets [1] -> adoEOF)
		{
			parameterTemp = (char *)(_bstr_t) dbAdo.m_pRecordsets [1] -> GetCollect ("类型");
			if (! parameterTemp.Compare ("none"))
			{
				///////////////////temp = "------[关联]";
				tempAss += "\t\t\t<associationInfo>\r\n";
				parameterTemp = (char *)(_bstr_t) dbAdo.m_pRecordsets [1] -> GetCollect ("名称");
				if (! parameterTemp.Compare (""))
				{
					////////////////temp += "none";
					tempAss += "\t\t\t\t<associationRelationshipName>NULL</associationRelationshipName>\r\n";
				}
				else
				{
					/////////////////temp += parameterTemp;
					tempAss +="\t\t\t\t<associationRelationshipName>"+parameterTemp+"</associationRelationshipName>\r\n";

				}
				parameterTemp = (char *)(_bstr_t) dbAdo.m_pRecordsets [1] -> GetCollect ("方向");
				if (!parameterTemp.Compare ("0"))
				{
					////////////////////temp += "    方向：双向\r\n------------[端一]";
					tempAss +="\t\t\t\t<associationDirection>bidirectional</associationDirection>\r\n";
					parameterTemp = (char *)(_bstr_t) dbAdo.m_pRecordsets [1] -> GetCollect ("类一");
					////////////////////temp+= parameterTemp;
					tempAss +="\t\t\t\t<fromClass>"+parameterTemp+"</fromClass>\r\n";
					parameterTemp = (char *)(_bstr_t) dbAdo.m_pRecordsets [1] -> GetCollect ("类一角色名");
					if (! parameterTemp.Compare (""))
					{
						////////////////////////temp += "    角色：无";
						tempAss +="\t\t\t\t<fromAssociationAttribute>NULL</fromAssociationAttribute>\r\n";
					}
					else
					{
						////////////////////////temp += "    角色：";
						////////////////////////temp += parameterTemp;
						tempAss +="\t\t\t\t<fromAssociationAttribute>"+parameterTemp+"</fromAssociationAttribute>\r\n";
					}
					parameterTemp = (char *)(_bstr_t) dbAdo.m_pRecordsets [1] -> GetCollect ("类一重数");
					if (! parameterTemp.Compare (""))
					{
						////////////////////////temp += "    重数：未限定\r\n------------[端二]";
						tempAss +="\t\t\t\t<fromMultiplicity>NULL</fromMultiplicity>\r\n";
					}
					else
					{
						////////////////////////////temp += "    重数：";
						////////////////////////////temp += parameterTemp;
						////////////////////////////temp += "\r\n------------[端二]";
						tempAss +="\t\t\t\t<fromMultiplicity>"+parameterTemp+"</fromMultiplicity>\r\n";
					}
					parameterTemp = (char *)(_bstr_t) dbAdo.m_pRecordsets [1] -> GetCollect ("类二");
					///////////////////////temp+= parameterTemp;
					tempAss +="\t\t\t\t<toClass>"+parameterTemp+"</toClass>\r\n";
					parameterTemp = (char *)(_bstr_t) dbAdo.m_pRecordsets [1] -> GetCollect ("类二角色名");
					if (! parameterTemp.Compare (""))
					{
						///////////////////////temp += "    角色：无";
						tempAss +="\t\t\t\t<toAssociationAttribute>NULL</toAssociationAttribute>\r\n";
					}
					else
					{
						//////////////////////////temp += "    角色：";
						//////////////////////////temp += parameterTemp;
						tempAss +="\t\t\t\t<toAssociationAttribute>"+parameterTemp+"</toAssociationAttribute>\r\n";
					}
					parameterTemp = (char *)(_bstr_t) dbAdo.m_pRecordsets [1] -> GetCollect ("类二重数");
					if (! parameterTemp.Compare (""))
					{
						///////////////////////////temp += "    重数：未限定\r\n\r\n";
						tempAss +="\t\t\t\t<toMultiplicity>NULL</toMultiplicity>\r\n";
					}
					else
					{
						///////////////////////////////////////////temp += "    重数：";
						/////////////////////////////////////////temp += parameterTemp;
						//////////////////////////////////////////temp += "\r\n\r\n";
						tempAss +="\t\t\t\t<toMultiplicity>"+parameterTemp+"</toMultiplicity>\r\n";
					}	
				}
				else if (!parameterTemp.Compare ("1"))
				{
					//////////////////////////////temp += "    方向：端点1->端点2\r\n------------[端一]";
					tempAss +="\t\t\t\t<associationDirection>unidirectional</associationDirection>\r\n";
					parameterTemp = (char *)(_bstr_t) dbAdo.m_pRecordsets [1] -> GetCollect ("类一");
					////////////////////temp+= parameterTemp;
					tempAss +="\t\t\t\t<fromClass>"+parameterTemp+"</fromClass>\r\n";
					parameterTemp = (char *)(_bstr_t) dbAdo.m_pRecordsets [1] -> GetCollect ("类一角色名");
					if (! parameterTemp.Compare (""))
					{
						////////////////////////temp += "    角色：无";
						tempAss +="\t\t\t\t<fromAssociationAttribute>NULL</fromAssociationAttribute>\r\n";
					}
					else
					{
						////////////////////////temp += "    角色：";
						////////////////////////temp += parameterTemp;
						tempAss +="\t\t\t\t<fromAssociationAttribute>"+parameterTemp+"</fromAssociationAttribute>\r\n";
					}
					parameterTemp = (char *)(_bstr_t) dbAdo.m_pRecordsets [1] -> GetCollect ("类一重数");
					if (! parameterTemp.Compare (""))
					{
						////////////////////////temp += "    重数：未限定\r\n------------[端二]";
						tempAss +="\t\t\t\t<fromMultiplicity>NULL</fromMultiplicity>\r\n";
					}
					else
					{
						////////////////////////////temp += "    重数：";
						////////////////////////////temp += parameterTemp;
						////////////////////////////temp += "\r\n------------[端二]";
						tempAss +="\t\t\t\t<fromMultiplicity>"+parameterTemp+"</fromMultiplicity>\r\n";
					}
					parameterTemp = (char *)(_bstr_t) dbAdo.m_pRecordsets [1] -> GetCollect ("类二");
					///////////////////////temp+= parameterTemp;
					tempAss +="\t\t\t\t<toClass>"+parameterTemp+"</toClass>\r\n";
					parameterTemp = (char *)(_bstr_t) dbAdo.m_pRecordsets [1] -> GetCollect ("类二角色名");
					if (! parameterTemp.Compare (""))
					{
						///////////////////////temp += "    角色：无";
						tempAss +="\t\t\t\t<toAssociationAttribute>NULL</toAssociationAttribute>\r\n";
					}
					else
					{
						//////////////////////////temp += "    角色：";
						//////////////////////////temp += parameterTemp;
						tempAss +="\t\t\t\t<toAssociationAttribute>"+parameterTemp+"</toAssociationAttribute>\r\n";
					}
					parameterTemp = (char *)(_bstr_t) dbAdo.m_pRecordsets [1] -> GetCollect ("类二重数");
					if (! parameterTemp.Compare (""))
					{
						///////////////////////////temp += "    重数：未限定\r\n\r\n";
						tempAss +="\t\t\t\t<toMultiplicity>NULL</toMultiplicity>\r\n";
					}
					else
					{
						///////////////////////////////////////////temp += "    重数：";
						/////////////////////////////////////////temp += parameterTemp;
						//////////////////////////////////////////temp += "\r\n\r\n";
						tempAss +="\t\t\t\t<toMultiplicity>"+parameterTemp+"</toMultiplicity>\r\n";
					}	
				}
				else if (!parameterTemp.Compare ("2"))
				{
					//temp += "    方向：端点2->端点1\r\n------------[端一]";
					tempAss +="\t\t\t\t<associationDirection>unidirectional</associationDirection>\r\n";
					parameterTemp = (char *)(_bstr_t) dbAdo.m_pRecordsets [1] -> GetCollect ("类二");
					////////////////////temp+= parameterTemp;
					tempAss +="\t\t\t\t<fromClass>"+parameterTemp+"</fromClass>\r\n";
					parameterTemp = (char *)(_bstr_t) dbAdo.m_pRecordsets [1] -> GetCollect ("类二角色名");
					if (! parameterTemp.Compare (""))
					{
						////////////////////////temp += "    角色：无";
						tempAss +="\t\t\t\t<fromAssociationAttribute>NULL</fromAssociationAttribute>\r\n";
					}
					else
					{
						////////////////////////temp += "    角色：";
						////////////////////////temp += parameterTemp;
						tempAss +="\t\t\t\t<fromAssociationAttribute>"+parameterTemp+"</fromAssociationAttribute>\r\n";
					}
					parameterTemp = (char *)(_bstr_t) dbAdo.m_pRecordsets [1] -> GetCollect ("类二重数");
					if (! parameterTemp.Compare (""))
					{
						////////////////////////temp += "    重数：未限定\r\n------------[端二]";
						tempAss +="\t\t\t\t<fromMultiplicity>NULL</fromMultiplicity>\r\n";
					}
					else
					{
						////////////////////////////temp += "    重数：";
						////////////////////////////temp += parameterTemp;
						////////////////////////////temp += "\r\n------------[端二]";
						tempAss +="\t\t\t\t<fromMultiplicity>"+parameterTemp+"</fromMultiplicity>\r\n";
					}
					parameterTemp = (char *)(_bstr_t) dbAdo.m_pRecordsets [1] -> GetCollect ("类一");
					///////////////////////temp+= parameterTemp;
					tempAss +="\t\t\t\t<toClass>"+parameterTemp+"</toClass>\r\n";
					parameterTemp = (char *)(_bstr_t) dbAdo.m_pRecordsets [1] -> GetCollect ("类一角色名");
					if (! parameterTemp.Compare (""))
					{
						///////////////////////temp += "    角色：无";
						tempAss +="\t\t\t\t<toAssociationAttribute>NULL</toAssociationAttribute>\r\n";
					}
					else
					{
						//////////////////////////temp += "    角色：";
						//////////////////////////temp += parameterTemp;
						tempAss +="\t\t\t\t<toAssociationAttribute>"+parameterTemp+"</toAssociationAttribute>\r\n";
					}
					parameterTemp = (char *)(_bstr_t) dbAdo.m_pRecordsets [1] -> GetCollect ("类一重数");
					if (! parameterTemp.Compare (""))
					{
						///////////////////////////temp += "    重数：未限定\r\n\r\n";
						tempAss +="\t\t\t\t<toMultiplicity>NULL</toMultiplicity>\r\n";
					}
					else
					{
						///////////////////////////////////////////temp += "    重数：";
						/////////////////////////////////////////temp += parameterTemp;
						//////////////////////////////////////////temp += "\r\n\r\n";
						tempAss +="\t\t\t\t<toMultiplicity>"+parameterTemp+"</toMultiplicity>\r\n";
					}	
				}
				tempAss += "\t\t\t</associationInfo>\r\n";				
			}
			else if (! parameterTemp.Compare ("shared"))
			{
				///////////////////temp = "------[聚合]";
				tempAgg +="\t\t\t<containmentInfo>\r\n";
				parameterTemp = (char *)(_bstr_t) dbAdo.m_pRecordsets [1] -> GetCollect ("名称");
				if (! parameterTemp.Compare (""))
				{
					////////////////////////////////////tempAgg += "none";
					tempAgg +="\t\t\t\t<containmentRelationshipName>NULL</containmentRelationshipName>\r\n";
				}
				else
				{
					//////////////////////////////////temp += parameterTemp;
					tempAgg +="\t\t\t\t<containmentRelationshipName>"+parameterTemp+"</containmentRelationshipName>\r\n";
				}
				parameterTemp = (char *)(_bstr_t) dbAdo.m_pRecordsets [1] -> GetCollect ("类一");
				//////////////////////////////temp+= parameterTemp;
				tempAgg +="\t\t\t\t<superiorClass>"+parameterTemp+"</superiorClass>\r\n";
				parameterTemp = (char *)(_bstr_t) dbAdo.m_pRecordsets [1] -> GetCollect ("类一重数");
				if (! parameterTemp.Compare (""))
				{
					///////////////////////////temp += "    重数：未限定\r\n------------[端二]";
					tempAgg +="\t\t\t\t<superiorClassMultiplicity>NULL</superiorClassMultiplicity>\r\n";
				}
				else
				{
					////////////////////////////temp += "    重数：";
					/////////////////////////////temp += parameterTemp;
					/////////////////////////temp += "\r\n------------[端二]";
					tempAgg +="\t\t\t\t<superiorClassMultiplicity>"+parameterTemp+"</superiorClassMultiplicity>\r\n";
				}
				parameterTemp = (char *)(_bstr_t) dbAdo.m_pRecordsets [1] -> GetCollect ("类二");
				////////////////////////////////temp+= parameterTemp;
				tempAgg +="\t\t\t\t<subordinateClass>"+parameterTemp+"</subordinateClass>\r\n";
				parameterTemp = (char *)(_bstr_t) dbAdo.m_pRecordsets [1] -> GetCollect ("类二重数");
				if (! parameterTemp.Compare (""))
				{
					////////////////////////////////////////temp += "    重数：未限定\r\n\r\n";
					tempAgg +="\t\t\t\t<subordinateClassMultiplicity>NULL</subordinateClassMultiplicity>\r\n";
				}
				else
				{
					tempAgg +="\t\t\t\t<subordinateClassMultiplicity>"+parameterTemp+"</subordinateClassMultiplicity>\r\n";
				}
				tempAgg +="\t\t\t</containmentInfo>\r\n";
			}
			else if (! parameterTemp.Compare ("composite"))
			{
				///////////////////temp = "------[组合]";
				tempCom +="\t\t\t<containmentInfo>\n";
				parameterTemp = (char *)(_bstr_t) dbAdo.m_pRecordsets [1] -> GetCollect ("名称");
				if (! parameterTemp.Compare (""))
				{
					////////////////////////////////////tempAgg += "none";
					tempCom +="\t\t\t\t<containmentRelationshipName>NULL</containmentRelationshipName>\r\n";
				}
				else
				{
					//////////////////////////////////temp += parameterTemp;
					tempCom +="\t\t\t\t<containmentRelationshipName>"+parameterTemp+"</containmentRelationshipName>\r\n";
				}
				parameterTemp = (char *)(_bstr_t) dbAdo.m_pRecordsets [1] -> GetCollect ("类一");
				//////////////////////////////temp+= parameterTemp;
				tempCom +="\t\t\t\t<superiorClass>"+parameterTemp+"</superiorClass>\r\n";
				parameterTemp = (char *)(_bstr_t) dbAdo.m_pRecordsets [1] -> GetCollect ("类一重数");
				if (! parameterTemp.Compare (""))
				{
					///////////////////////////temp += "    重数：未限定\r\n------------[端二]";
					tempCom +="\t\t\t\t<superiorClassMultiplicity>NULL</superiorClassMultiplicity>\r\n";
				}
				else
				{
					////////////////////////////temp += "    重数：";
					/////////////////////////////temp += parameterTemp;
					/////////////////////////temp += "\r\n------------[端二]";
					tempCom +="\t\t\t\t<superiorClassMultiplicity>"+parameterTemp+"</superiorClassMultiplicity>\r\n";
				}
				parameterTemp = (char *)(_bstr_t) dbAdo.m_pRecordsets [1] -> GetCollect ("类二");
				////////////////////////////////temp+= parameterTemp;
				tempCom +="\t\t\t\t<subordinateClass>"+parameterTemp+"</subordinateClass>\r\n";
				parameterTemp = (char *)(_bstr_t) dbAdo.m_pRecordsets [1] -> GetCollect ("类二重数");
				if (! parameterTemp.Compare (""))
				{
					////////////////////////////////////////temp += "    重数：未限定\r\n\r\n";
					tempCom +="\t\t\t\t<subordinateClassMultiplicity>NULL</subordinateClassMultiplicity>\r\n";
				}
				else
				{
					/////////////////////////temp += "    重数：";
					/////////////////////////////temp += parameterTemp;
					//////////////////////////////////////temp += "\r\n\r\n";
					tempCom +="\t\t\t\t<subordinateClassMultiplicity>"+parameterTemp+"</subordinateClassMultiplicity>\r\n";
				}	
				tempCom +="\t\t\t</containmentInfo>\r\n";
			}
			///////////////////////////////txtFile.Write (temp, temp.GetLength ());
			dbAdo.m_pRecordsets [1]-> MoveNext ();
		}
		
		//数据读取完毕写入文件
		tempAss +="\t\t</associationList>\r\n";	
		txtFile.Write (tempAss, tempAss.GetLength ());

		tempAgg +="\t\t</aggregationList>\r\n";
		txtFile.Write (tempAgg, tempAgg.GetLength ());

		tempCom +="\t\t</compositionList>\r\n";
		txtFile.Write (tempCom, tempCom.GetLength ());

		//tempGen +="\t\t</generalizationList>\r\n";
		//txtFile.Write (tempGen, tempGen.GetLength ());
		
		//////////////////////////////////////////////////////////////////////////////////////
		//以下为尚未看懂部分
		/*
		//获取角色信息
		sql [1] = "select 名称 from actor where 所属包ID = '" + packageID + "'";
		dbAdo.m_pRecordsets [1] = dbAdo.OpenRecordsets (sql[1], 1);
		dbAdo.m_pRecordsets [1] -> Requery (0);
		while (!dbAdo.m_pRecordsets [1] -> adoEOF)
		{
			className = (char *)(_bstr_t) dbAdo.m_pRecordsets [1] -> GetCollect ("名称");
			temp = "------[角色]" + className + "\r\n\r\n";
			txtFile.Write (temp, temp.GetLength ());
			dbAdo.m_pRecordsets [1]-> MoveNext ();
		}

		txtFile.Write ("\r\n\r\n\r\n\r\n", 4);
		dbAdo.m_pRecordsets [0] -> MoveNext ();
		*/
		////////////////////////////////////////////////////////////////////////////////////////////
	//}
	//获取继承信息
	tempGen="";
	tempGen="\t\t<generalizationList>\r\n";
	txtFile.Write (tempGen, tempGen.GetLength ());
	sql [1] = "select 类, 继承类 from generalization";
	dbAdo.m_pRecordsets [1] = dbAdo.OpenRecordsets (sql[1],1);
	dbAdo.m_pRecordsets [1] -> Requery (0);
	//dbAdo.m_pRecordsets [0]-> MoveNext ();
	while (!dbAdo.m_pRecordsets [1] -> adoEOF)
	{			
		/////////////////temp = "------[继承]\r\n";
		tempGen ="\t\t\t<generalizationInfo>\r\n";
		parameterTemp = (char *)(_bstr_t) dbAdo.m_pRecordsets [1] -> GetCollect ("继承类");
		if (! parameterTemp.Compare (""))
			{
				///////////////////////////////temp += "父类：无名称\r\n";
				tempGen +="\t\t\t\t<parentClass>NULL</parentClass>\r\n";
			}
		else
			{
				//////////////////////////temp += "父类："+parameterTemp+"\r\n";
				tempGen +="\t\t\t\t<parentClass>"+parameterTemp+"</parentClass>\r\n";
			}
		parameterTemp = (char *)(_bstr_t) dbAdo.m_pRecordsets [1] -> GetCollect ("类");
		if (! parameterTemp.Compare (""))
			{
				//////////////////////////temp += "子类：无名称\r\n\r\n";
				tempGen +="\t\t\t\t<childClass>NULL</childClass>\r\n";
			}
		else
			{
				/////////////////////temp += "子类："+parameterTemp+"\r\n\r\n";
				tempGen +="\t\t\t\t<childClass>"+parameterTemp+"</childClass>\r\n";
			}
		tempGen +="\t\t\t</generalizationInfo>\r\n";
		txtFile.Write (tempGen, tempGen.GetLength ());
		dbAdo.m_pRecordsets [1]-> MoveNext ();
	}
	temp ="\t\t</generalizationList>\r\n";
	temp +="\t</relationshipSet>\r\n";
	temp +="</containmentSetInfo>\r\n";
	txtFile.Write (temp, temp.GetLength ());
	txtFile.Close ();													//关闭xml文件
	dbAdo.CloseConn ();													//断开数据库

	}

	//从数据库导出类信息结果的到xsd文件
	CFile xsdFile;
	ADO dbAdox;
	hasReturn = FALSE;
	CString sqlx[4], tempx = "", parameterTempx = "";
	CString packageNamex = "", packageIDx = "", classNamex ="", classIDx = "";
	CString attributeNamex = "", attributeTypex = "", attributeDefaultx = "";
	CString operationNamex = "", operationIDx = "";
	CString parameterNamex = "", parameterTypex = "", parameterDirectionx = "";
	CString associationNamex = "", associationTypex = "", associationDirectionx = "";
	CString end1Namex = "", end1Rolex = "", end1Multix = "";
	CString tempAdd= "";
	vector <CString> v;
	vector <vector <CString>> generaList; //将有继承关系的类放入一个列表
	vector <CString> v2;
	vector <vector <CString>> containmentList; //将有继承关系的类放入一个列表
	vector <CString> v3;    //用来记录已经存过的root-某一类的包含关系
	int flag=0;//flag为是否有继承关系的标志，0为没有，1为有
	
	dbAdox.OnInitADOConn (dbPath);										//连接数据库	

	//创建并打开xsd文件
	if (! xsdFile.Open (xsdPath, CFile::modeCreate | CFile::modeWrite))	//打开失败
	{
		AfxMessageBox ("Failed to create an open xsd file!");
		return FALSE;
	}
	//将有继承关系的类放入一个二维列表generaList
	sqlx [0] = "select 类, 继承类 from generalization";
	dbAdox.m_pRecordsets [0] = dbAdox.OpenRecordsets (sqlx[0],0);
	dbAdox.m_pRecordsets [0] -> Requery (0);
	while (!dbAdox.m_pRecordsets [0] -> adoEOF)
	{			
		parameterTemp = (char *)(_bstr_t) dbAdox.m_pRecordsets [0] -> GetCollect ("类");
		if (! parameterTemp.Compare (""))
			{
			}
		else
			{			 
				v.push_back(parameterTemp); 			
			}
		parameterTemp = (char *)(_bstr_t) dbAdox.m_pRecordsets [0] -> GetCollect ("继承类");
		if (! parameterTemp.Compare (""))
			{
			}
		else
			{
				v.push_back(parameterTemp);
				generaList.push_back(v); 
				v.clear();
			}
		dbAdox.m_pRecordsets [0]-> MoveNext ();
	}
	
	//将有包含关系的类放入一个二维列表containmentList
	sqlx [3] = "select 类一, 类二 from association where 类型='shared' union select 类一, 类二 from association where 类型='composite'";
	dbAdox.m_pRecordsets [3] = dbAdox.OpenRecordsets (sqlx[3],3);
	dbAdox.m_pRecordsets [3] -> Requery (0);
	while (!dbAdox.m_pRecordsets [3] -> adoEOF)
	{			
		parameterTemp = (char *)(_bstr_t) dbAdox.m_pRecordsets [3] -> GetCollect ("类一");
		if (! parameterTemp.Compare (""))
			{
			}
		else
			{			 
				v2.push_back(parameterTemp); 			
			}
		parameterTemp = (char *)(_bstr_t) dbAdox.m_pRecordsets [3] -> GetCollect ("类二");
		if (! parameterTemp.Compare (""))
			{
			}
		else
			{
				v2.push_back(parameterTemp);
				containmentList.push_back(v2); 
				v2.clear();
			}
		dbAdox.m_pRecordsets [3]-> MoveNext ();
	}
	
	//以下为测试代码
	//for(int i=0;i<generaList.size();i++)
	//{
	//	for(int j=0;j<generaList[i].size();j++)
	//	{
	//		temp =generaList[i][j];
	//		xsdFile.Write (temp, temp.GetLength ());
	//	}
	//}
	//开始写xsd文件
	//xml头部编写
	temp = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\r\n";
	temp +="<xsd:schema xmlns:xsd=\"http://www.w3.org/2001/XMLSchema\" xmlns:uml=\"http://www.ws.zc/xml-namespace/informationModel/UMLModelGenericModel\" targetNamespace=\"http://www.ws.zc/xml-namespace/informationModel/UMLModelGenericModel\" elementFormDefault=\"qualified\" attributeFormDefault=\"unqualified\" version=\"1.0\">\r\n";
	xsdFile.Write (temp, temp.GetLength ());	
	temp ="\t<xsd:simpleType name=\"DNType\">\r\n";
	temp +="\t\t<xsd:restriction base=\"xsd:string\"/>\r\n";
	temp +="\t</xsd:simpleType>\r\n";
	temp +="\t<xsd:complexType name=\"DNSetType\">\r\n";
	temp +="\t\t<xsd:sequence>\r\n";
	temp +="\t\t\t<xsd:element name=\"dn\" type=\"uml:DNType\" minOccurs=\"0\" maxOccurs=\"unbounded\"/>\r\n";
	temp +="\t\t</xsd:sequence>\r\n";
	temp +="\t</xsd:complexType>\r\n";
	xsdFile.Write (temp, temp.GetLength ());
	//获取类及继承信息	
	sqlx [1] = "select 名称, ID from class where 所属包ID = '" + packageID + "'";
	dbAdox.m_pRecordsets [1] = dbAdox.OpenRecordsets (sqlx[1], 1);
	dbAdox.m_pRecordsets [1] -> Requery (0);
	while (!dbAdox.m_pRecordsets [1] -> adoEOF)
	{
		className = (char *)(_bstr_t) dbAdox.m_pRecordsets [1] -> GetCollect ("名称");
		classID = (char *)(_bstr_t) dbAdox.m_pRecordsets [1] -> GetCollect ("ID");
		temp="\t<xsd:complexType name=\""+className+"_T\">\r\n";
		//temp+="\t\t\t<className>"+ className+"</className>\r\n";
		if(!className.Compare ("ManagedObject"))
			{
				temp+="\t\t<xsd:sequence>\r\n";
				flag=1;
			}
		for(int i=0;i<generaList.size();i++)
		{
			if(!className.Compare (generaList[i][0]))
			{
				temp+="\t\t<xsd:complexContent>\r\n";
				temp+="\t\t\t<xsd:extension base=\"uml:"+generaList[i][1]+"_T\">\r\n";
				temp+="\t\t\t\t<xsd:sequence>\r\n";
				flag=1;
			}

		}
		if(flag==0)
		{
			temp+="\t\t<xsd:complexContent>\r\n";
			temp+="\t\t\t<xsd:extension base=\"uml:ManagedObject_T\">\r\n";
			temp+="\t\t\t\t<xsd:sequence>\r\n";
		}
		xsdFile.Write (temp, temp.GetLength ());
		//获取类属性信息
		sqlx [2] = "select 名称, 类型, 初始值 from attribute where 所属类ID = '" + classID + "'";
		dbAdox.m_pRecordsets [2] = dbAdox.OpenRecordsets (sqlx[2], 2);
		dbAdox.m_pRecordsets [2] -> Requery (0);	
		//xsdFile.Write (temp, temp.GetLength ());
		while (!dbAdox.m_pRecordsets [2] -> adoEOF)
		{
			attributeName = (char *)(_bstr_t) dbAdox.m_pRecordsets [2] -> GetCollect ("名称");
			attributeType = (char *)(_bstr_t) dbAdox.m_pRecordsets [2] -> GetCollect ("类型");	
			//if(flag==1)
			//	temp="\t\t\t\t\t<xsd:element name=\""+attributeName+"\" type=\"xsd:"+attributeType+"\"/>\r\n";	
			//if(flag==0)
			//	temp="\t\t\t\t\t<xsd:element name=\""+attributeName+"\" type=\"xsd:"+attributeType+"\"/>\r\n";

			string attributeT=attributeType.GetBuffer(0); 
			vector<string> Array1;
			split(attributeT,"__",Array1);
			if(Array1.size()==2)
			{
				CString attributeTy="";
				attributeTy.Format( "%s",Array1[1].data()); 
				temp="\t\t\t\t\t<xsd:element name=\""+attributeName+"\" type=\"xsd:"+attributeTy+"\"/>\r\n";
			}
			else
			{
				CString attributeTy="";
				attributeTy.Format( "%s",Array1[2].data()); 
				temp="\t\t\t\t\t<xsd:element name=\""+attributeName+"\" type=\"uml:"+attributeTy+"\"/>\r\n";
			}

			xsdFile.Write (temp, temp.GetLength ());
			dbAdox.m_pRecordsets [2] -> MoveNext ();
		}		
		if((flag==1)&&(className.Compare ("ManagedObject")))
		{
			temp="\t\t\t\t</xsd:sequence>\r\n";
			temp+="\t\t\t</xsd:extension>\r\n";
			temp+="\t\t</xsd:complexContent>\r\n";
			temp+="\t</xsd:complexType>\r\n";
			//temp+="</xsd:schema>";
			xsdFile.Write (temp, temp.GetLength ());
			int fflag=0;//fflag是是否有孩子的类的标志，0为没孩子
			for(int i=0;i<generaList.size();i++)
			{
				if(!className.Compare (generaList[i][1]))
				{
					fflag=1;
				}

			}
			if(fflag==0)
			{
				//在这里为生成的类模板文件中的类加上后缀_C ZR
				temp="\t<xsd:element name=\""+className+"_C\" type=\"uml:"+className+"_T\"/>\r\n";
				xsdFile.Write (temp, temp.GetLength ());
				tempAdd+="\t\t\t<xsd:element ref=\"uml:"+className+"_C\" minOccurs=\"0\" maxOccurs=\"unbounded\"/>\r\n";
			}

		}
		if((flag==1)&&(!className.Compare ("ManagedObject")))
		{
			temp="\t\t</xsd:sequence>\r\n";
			temp+="\t</xsd:complexType>\r\n";
			//temp+="</xsd:schema>";
			xsdFile.Write (temp, temp.GetLength ());			
		}
		if(flag==0)
		{
			temp="\t\t\t\t</xsd:sequence>\r\n";
			temp+="\t\t\t</xsd:extension>\r\n";
			temp+="\t\t</xsd:complexContent>\r\n";
			temp+="\t</xsd:complexType>\r\n";
			xsdFile.Write (temp, temp.GetLength ());
		}
		dbAdox.m_pRecordsets [1]-> MoveNext ();
	}	
	temp="\t<xsd:complexType name=\"InstanceOutputType\">\r\n";
	temp+="\t\t<xsd:sequence>\r\n";
	temp+=tempAdd;
	temp+="\t\t</xsd:sequence>\r\n";
	temp+="\t</xsd:complexType>\r\n";
	temp+="\t<xsd:element name=\"outputInstanceList\" type=\"uml:InstanceOutputType\"/>\r\n";
	temp+="</xsd:schema>";
	xsdFile.Write (temp, temp.GetLength ());
	xsdFile.Close ();	//关闭xsd文件				
	//temp="</xsd:schema>";
	//xsdFile.Write (temp, temp.GetLength ());

	//获取关系信息并将结果导入xml文件
	CFile xmlFile;
	if (! xmlFile.Open (xml4RelaPath, CFile::modeCreate | CFile::modeWrite))	//打开失败
	{
		AfxMessageBox ("Failed to create an open xsd file!");
		return FALSE;
	}
	//文件头部编写 
	temp ="<?xml version=\"1.0\" encoding=\"UTF-8\"?>\r\n";
    temp+="<relationshipSet xmlns=\"http://www.ws.zc/xml-namespace/informationModel/zcGenericModelRelationship\" xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xsi:schemaLocation=\"http://www.ws.zc/xml-namespace/informationModel/zcGenericModelRelationship\r\n";
	temp+="D:\\Backup\\UMLanalyser\\Debug\\zcGenericModelRelationship.xsd\">\r\n";
	temp+="\t<containmentList>\r\n";
	xmlFile.Write (temp, temp.GetLength ());
	int flag4con=0;//是否有被包含关系的标志，0为没有，1为有，1则不需要添加root到此类的包含关系
	for(int i=0;i<containmentList.size();i++)
	{
		flag4con=0;
		for(int j=0;j<containmentList.size();j++)
		{
			if(!containmentList[i][0].Compare(containmentList[j][1]))
				flag4con=1;
		}
		if(flag4con==0)
		{
			int temp4ConClass=0;//是否需要添加root到此类的包含关系，0为需要，1为不需要
			for(int z=0;z<v3.size();z++)
			{
				if(!containmentList[i][0].Compare(v3[z]))
					temp4ConClass=1;

			}
			if(temp4ConClass==0)
			{
				
				v3.push_back(containmentList[i][0]);
				temp ="\t\t<containmentInfo>\r\n";
				temp +="\t\t\t<containmentRelationshipName>Root-"+containmentList[i][0]+"</containmentRelationshipName>\r\n";
				temp +="\t\t\t<superiorClass>Root</superiorClass>\r\n";
				temp +="\t\t\t<superiorClassMultiplicity>1</superiorClassMultiplicity>\r\n";
				temp +="\t\t\t<subordinateClass>"+containmentList[i][0]+"</subordinateClass>\r\n";
				temp +="\t\t\t<subordinateClassMultiplicity>0..*</subordinateClassMultiplicity>\r\n";
				if(!containmentList[i][0].Compare ("Student"))
				{
					//ZR modified StudentNo to studentNo
					temp+="\t\t\t<namingAttribute>studentNo</namingAttribute>\r\n";
				}
				else
					//ZR modified 把containmentList[][] 全部改成小写的，为了和类属性保持一致
					temp+="\t\t\t<namingAttribute>"+containmentList[i][0].MakeLower()+"ID</namingAttribute>\r\n";
				//temp +="\t\t\t<namingAttribute>StudentNo</namingAttribute>
				temp +="\t\t</containmentInfo>\r\n";
				xmlFile.Write (temp, temp.GetLength ());
			}
		}
		
	}

	tempAss="\t<associationList>\r\n";	
	
	tempAgg="";
	
	tempCom="";

	sqlx [1] = "select 名称, 类一, 类一角色名, 类一重数, 类二, 类二角色名, 类二重数, 类型 , 方向 from association where 所属包ID = '" + packageID + "'";
	dbAdox.m_pRecordsets [1] = dbAdox.OpenRecordsets (sqlx[1], 1);
	dbAdox.m_pRecordsets [1] -> Requery (0);
	while (!dbAdox.m_pRecordsets [1] -> adoEOF)
	{
		parameterTemp = (char *)(_bstr_t) dbAdox.m_pRecordsets [1] -> GetCollect ("类型");
		if (! parameterTemp.Compare ("none"))
		{
			//"------[关联]";
			tempAss += "\t\t<associationInfo>\r\n";
			parameterTemp = (char *)(_bstr_t) dbAdox.m_pRecordsets [1] -> GetCollect ("名称");
			if (! parameterTemp.Compare (""))
			{
				tempAss += "\t\t\t<associationRelationshipName>NULL</associationRelationshipName>\r\n";
			}
			else
			{
				tempAss +="\t\t\t<associationRelationshipName>"+parameterTemp+"</associationRelationshipName>\r\n";
			}
			parameterTemp = (char *)(_bstr_t) dbAdox.m_pRecordsets [1] -> GetCollect ("方向");
			if (!parameterTemp.Compare ("0"))
			{
				////////////////////temp += "方向：双向";
				tempAss +="\t\t\t<associationDirection>bidirectional</associationDirection>\r\n";
				parameterTemp = (char *)(_bstr_t) dbAdox.m_pRecordsets [1] -> GetCollect ("类一");
				tempAss +="\t\t\t<fromClass>"+parameterTemp+"</fromClass>\r\n";
				parameterTemp = (char *)(_bstr_t) dbAdox.m_pRecordsets [1] -> GetCollect ("类一角色名");
				if (! parameterTemp.Compare (""))
				{
					// "角色：无";
					tempAss +="\t\t\t<fromAssociationAttribute>NULL</fromAssociationAttribute>\r\n";
				}
				else
				{
					tempAss +="\t\t\t<fromAssociationAttribute>"+parameterTemp+"</fromAssociationAttribute>\r\n";
				}
				parameterTemp = (char *)(_bstr_t) dbAdox.m_pRecordsets [1] -> GetCollect ("类一重数");
				if (! parameterTemp.Compare (""))
				{
					// " 重数：未限定";
					tempAss +="\t\t\t<fromMultiplicity>NULL</fromMultiplicity>\r\n";
				}
				else
				{
					tempAss +="\t\t\t<fromMultiplicity>"+parameterTemp+"</fromMultiplicity>\r\n";
				}
				parameterTemp = (char *)(_bstr_t) dbAdox.m_pRecordsets [1] -> GetCollect ("类二");
				tempAss +="\t\t\t<toClass>"+parameterTemp+"</toClass>\r\n";
				parameterTemp = (char *)(_bstr_t) dbAdox.m_pRecordsets [1] -> GetCollect ("类二角色名");
				if (! parameterTemp.Compare (""))
				{
					//"角色：无";
					tempAss +="\t\t\t<toAssociationAttribute>NULL</toAssociationAttribute>\r\n";
				}
				else
				{
					//"角色：";
					tempAss +="\t\t\t<toAssociationAttribute>"+parameterTemp+"</toAssociationAttribute>\r\n";
				}
				parameterTemp = (char *)(_bstr_t) dbAdox.m_pRecordsets [1] -> GetCollect ("类二重数");
				if (! parameterTemp.Compare (""))
				{
					//"重数：未限定";
					tempAss +="\t\t\t<toMultiplicity>NULL</toMultiplicity>\r\n";
				}
				else
				{
					tempAss +="\t\t\t<toMultiplicity>"+parameterTemp+"</toMultiplicity>\r\n";
				}	
			}
			else if (!parameterTemp.Compare ("1"))
			{
				//"方向：端点1->端点2";
				tempAss +="\t\t\t<associationDirection>unidirectional</associationDirection>\r\n";
				parameterTemp = (char *)(_bstr_t) dbAdox.m_pRecordsets [1] -> GetCollect ("类一");
				tempAss +="\t\t\t<fromClass>"+parameterTemp+"</fromClass>\r\n";
				parameterTemp = (char *)(_bstr_t) dbAdox.m_pRecordsets [1] -> GetCollect ("类一角色名");
				if (! parameterTemp.Compare (""))
				{
					//temp += "    角色：无";
					tempAss +="\t\t\t<fromAssociationAttribute>NULL</fromAssociationAttribute>\r\n";
				}
				else
				{
					tempAss +="\t\t\t<fromAssociationAttribute>"+parameterTemp+"</fromAssociationAttribute>\r\n";
				}
				parameterTemp = (char *)(_bstr_t) dbAdox.m_pRecordsets [1] -> GetCollect ("类一重数");
				if (! parameterTemp.Compare (""))
				{
					//"重数：未限定";
					tempAss +="\t\t\t<fromMultiplicity>NULL</fromMultiplicity>\r\n";
				}
				else
				{
					tempAss +="\t\t\t<fromMultiplicity>"+parameterTemp+"</fromMultiplicity>\r\n";
				}
				parameterTemp = (char *)(_bstr_t) dbAdox.m_pRecordsets [1] -> GetCollect ("类二");
				tempAss +="\t\t\t<toClass>"+parameterTemp+"</toClass>\r\n";
				parameterTemp = (char *)(_bstr_t) dbAdox.m_pRecordsets [1] -> GetCollect ("类二角色名");
				if (! parameterTemp.Compare (""))
				{
					//"角色：无";
					tempAss +="\t\t\t<toAssociationAttribute>NULL</toAssociationAttribute>\r\n";
				}
				else
				{
					//"角色：";
					tempAss +="\t\t\t<toAssociationAttribute>"+parameterTemp+"</toAssociationAttribute>\r\n";
				}
				parameterTemp = (char *)(_bstr_t) dbAdox.m_pRecordsets [1] -> GetCollect ("类二重数");
				if (! parameterTemp.Compare (""))
				{
					//"重数：未限定";
					tempAss +="\t\t\t<toMultiplicity>NULL</toMultiplicity>\r\n";
				}
				else
				{
					tempAss +="\t\t\t<toMultiplicity>"+parameterTemp+"</toMultiplicity>\r\n";
				}	
			}
			else if (!parameterTemp.Compare ("2"))
			{
				// "方向：端点2->端点1";
				tempAss +="\t\t\t<associationDirection>unidirectional</associationDirection>\r\n";
				parameterTemp = (char *)(_bstr_t) dbAdox.m_pRecordsets [1] -> GetCollect ("类二");
				tempAss +="\t\t\t<fromClass>"+parameterTemp+"</fromClass>\r\n";
				parameterTemp = (char *)(_bstr_t) dbAdox.m_pRecordsets [1] -> GetCollect ("类二角色名");
				if (! parameterTemp.Compare (""))
				{
					//"角色：无";
					tempAss +="\t\t\t<fromAssociationAttribute>NULL</fromAssociationAttribute>\r\n";
				}
				else
				{
					//"角色：";
					tempAss +="\t\t\t<fromAssociationAttribute>"+parameterTemp+"</fromAssociationAttribute>\r\n";
				}
				parameterTemp = (char *)(_bstr_t) dbAdox.m_pRecordsets [1] -> GetCollect ("类二重数");
				if (! parameterTemp.Compare (""))
				{
					//"重数：未限定";
					tempAss +="\t\t\t<fromMultiplicity>NULL</fromMultiplicity>\r\n";
				}
				else
				{
					tempAss +="\t\t\t<fromMultiplicity>"+parameterTemp+"</fromMultiplicity>\r\n";
				}
				parameterTemp = (char *)(_bstr_t) dbAdox.m_pRecordsets [1] -> GetCollect ("类一");
				tempAss +="\t\t\t\t<toClass>"+parameterTemp+"</toClass>\r\n";
				parameterTemp = (char *)(_bstr_t) dbAdox.m_pRecordsets [1] -> GetCollect ("类一角色名");
				if (! parameterTemp.Compare (""))
				{
					// "角色：无";
					tempAss +="\t\t\t<toAssociationAttribute>NULL</toAssociationAttribute>\r\n";
				}
				else
				{
					tempAss +="\t\t\t<toAssociationAttribute>"+parameterTemp+"</toAssociationAttribute>\r\n";
				}
				parameterTemp = (char *)(_bstr_t) dbAdox.m_pRecordsets [1] -> GetCollect ("类一重数");
				if (! parameterTemp.Compare (""))
				{
					//"重数：未限定";
					tempAss +="\t\t\t<toMultiplicity>NULL</toMultiplicity>\r\n";
				}
				else
				{
					//"重数：";
					tempAss +="\t\t\t<toMultiplicity>"+parameterTemp+"</toMultiplicity>\r\n";
				}	
			}
			tempAss += "\t\t</associationInfo>\r\n";				
		}
		else if (! parameterTemp.Compare ("shared"))
		{
			//"------[聚合]";注意名称的获取
			CString parameterTemp1;
			CString tempAgg1;
			CString parameterTemp2;
			CString tempAgg2;
			CString parameterTemp3;
			CString tempAgg3;
			CString parameterTemp4;
			CString tempAgg4;
			tempAgg +="\t\t<containmentInfo>\r\n";
			parameterTemp1 = (char *)(_bstr_t) dbAdox.m_pRecordsets [1] -> GetCollect ("类一");
			tempAgg1 +="\t\t\t<superiorClass>"+parameterTemp1+"</superiorClass>\r\n";
			parameterTemp2 = (char *)(_bstr_t) dbAdox.m_pRecordsets [1] -> GetCollect ("类一重数");
			if (! parameterTemp2.Compare (""))
			{
				///////////////////////////temp += "    重数：未限定\r\n------------[端二]";
				tempAgg2 +="\t\t\t<superiorClassMultiplicity>NULL</superiorClassMultiplicity>\r\n";
			}
			else
			{
				tempAgg2 +="\t\t\t<superiorClassMultiplicity>"+parameterTemp2+"</superiorClassMultiplicity>\r\n";
			}
			parameterTemp3 = (char *)(_bstr_t) dbAdox.m_pRecordsets [1] -> GetCollect ("类二");
			tempAgg3 +="\t\t\t<subordinateClass>"+parameterTemp3+"</subordinateClass>\r\n";
			parameterTemp4 = (char *)(_bstr_t) dbAdox.m_pRecordsets [1] -> GetCollect ("类二重数");
			if (! parameterTemp4.Compare (""))
			{
				//"重数：未限定";
				tempAgg4 +="\t\t\t<subordinateClassMultiplicity>NULL</subordinateClassMultiplicity>\r\n";
			}
			else
			{
				tempAgg4 +="\t\t\t<subordinateClassMultiplicity>"+parameterTemp4+"</subordinateClassMultiplicity>\r\n";
			}
			tempAgg +="\t\t\t<containmentRelationshipName>"+parameterTemp1+"-"+parameterTemp3+"</containmentRelationshipName>\r\n";
			tempAgg += tempAgg1;
			tempAgg += tempAgg2;
			tempAgg += tempAgg3;
			tempAgg += tempAgg4;
			//查询数据库获取类的唯一标识,此处限定标识的格式，如果是student就是studentNo，其他的均为name加上ID
			if(! parameterTemp3.Compare ("Student"))
			{
				tempAgg+="\t\t\t<namingAttribute>StudentNo</namingAttribute>\r\n";
			}
			else
				tempAgg+="\t\t\t<namingAttribute>"+parameterTemp3+"ID</namingAttribute>\r\n";
			tempAgg +="\t\t</containmentInfo>\r\n";
		}
		else if (! parameterTemp.Compare ("composite"))
		{
			//"------[组合]";注意名称的获取
			CString parameterTemp1;
			CString tempCom1;
			CString parameterTemp2;
			CString tempCom2;
			CString parameterTemp3;
			CString tempCom3;
			CString parameterTemp4;
			CString tempCom4;
			tempCom +="\t\t<containmentInfo>\r\n";
			parameterTemp1 = (char *)(_bstr_t) dbAdox.m_pRecordsets [1] -> GetCollect ("类一");
			tempCom1 +="\t\t\t<superiorClass>"+parameterTemp1+"</superiorClass>\r\n";
			parameterTemp2 = (char *)(_bstr_t) dbAdox.m_pRecordsets [1] -> GetCollect ("类一重数");
			if (! parameterTemp2.Compare (""))
			{
				///////////////////////////temp += "    重数：未限定\r\n------------[端二]";
				tempCom2 +="\t\t\t<superiorClassMultiplicity>NULL</superiorClassMultiplicity>\r\n";
			}
			else
			{
				tempCom2 +="\t\t\t<superiorClassMultiplicity>"+parameterTemp2+"</superiorClassMultiplicity>\r\n";
			}
			parameterTemp3 = (char *)(_bstr_t) dbAdox.m_pRecordsets [1] -> GetCollect ("类二");
			tempCom3 +="\t\t\t<subordinateClass>"+parameterTemp3+"</subordinateClass>\r\n";
			parameterTemp4 = (char *)(_bstr_t) dbAdox.m_pRecordsets [1] -> GetCollect ("类二重数");
			if (! parameterTemp4.Compare (""))
			{
				//"重数：未限定";
				tempCom4 +="\t\t\t<subordinateClassMultiplicity>NULL</subordinateClassMultiplicity>\r\n";
			}
			else
			{
				tempCom4 +="\t\t\t<subordinateClassMultiplicity>"+parameterTemp4+"</subordinateClassMultiplicity>\r\n";
			}
			tempCom +="\t\t\t<containmentRelationshipName>"+parameterTemp1+"-"+parameterTemp3+"</containmentRelationshipName>\r\n";
			tempCom += tempCom1;
			tempCom += tempCom2;
			tempCom += tempCom3;
			tempCom += tempCom4;
			//查询数据库获取类的唯一标识,此处限定标识的格式，如果是student就是studentNo，其他的均为name加上ID
			if(! parameterTemp3.Compare ("Student"))
			{
				tempCom+="\t\t\t<namingAttribute>StudentNo</namingAttribute>\r\n";
			}
			else
				tempCom+="\t\t\t<namingAttribute>"+parameterTemp3+"ID</namingAttribute>\r\n";
			tempCom +="\t\t</containmentInfo>\r\n";
			
		}
			///////////////////////////////txtFile.Write (temp, temp.GetLength ());
			dbAdox.m_pRecordsets [1]-> MoveNext ();
	}
		
	//数据读取完毕写入文件
	xmlFile.Write (tempAgg, tempAgg.GetLength ());
	xmlFile.Write (tempCom, tempCom.GetLength ());
	temp="\t</containmentList>\r\n";
	xmlFile.Write (temp, temp.GetLength ());
	tempAss +="\t</associationList>\r\n";	
	xmlFile.Write (tempAss, tempAss.GetLength ());
	temp="</relationshipSet>\r\n";	
	xmlFile.Write (temp, temp.GetLength ());
	dbAdox.CloseConn ();			
	return TRUE;
}

HBRUSH CUMLanalyserDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO: Return a different brush if the default is not desired
	//设置各个控件背景透明
	hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	switch  (nCtlColor)    
	{    
//		case CTLCOLOR_MSGBOX:
//		case CTLCOLOR_BTN:
//		case CTLCOLOR_SCROLLBAR:
		case CTLCOLOR_STATIC:
			hbr  =  (HBRUSH)::GetStockObject(NULL_BRUSH);  //创建一个空画刷，使控件背景透明
		case CTLCOLOR_EDIT:
//		case CTLCOLOR_LISTBOX:
//		case CTLCOLOR_MAX:
			pDC->SetBkMode(TRANSPARENT); 
			break;
		default:
			break;
	}
	return hbr;
}