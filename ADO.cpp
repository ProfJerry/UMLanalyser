// ADO.cpp: implementation of the ADO class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ADO.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ADO::ADO()

{
}

ADO::~ADO()
{
}

//**************************************************//
//函数功能：连接数据库								//
//**************************************************//
void ADO::OnInitADOConn (CString dbPath)
{
	CString temp = "DRIVER={Microsoft Access Driver (*.mdb)};\
		uid=;pwd=;DBQ=";
	temp+= dbPath;
	::CoInitialize(NULL);
	try
	{
       m_pConnection.CreateInstance("ADODB.Connection");	//创建连接对象实例
	   //_bstr_t strConnect="DRIVER={Microsoft Access Driver (*.mdb)};\
		//	uid=;pwd=;DBQ=AirConditioner.mdb;";				//连接语句
	   _bstr_t strConnect = _bstr_t (temp);					//连接语句
	   m_pConnection->Open(strConnect,"","",adModeUnknown); //打开数据库
	}
	catch(_com_error e)
	{
		AfxMessageBox(e.Description()); //弹出错误处理
	}
}

//**************************************************//
//函数功能：打开记录集								//
//**************************************************//
_RecordsetPtr& ADO::OpenRecordset(CString sql)
{
	ASSERT(!sql.IsEmpty());									//SQL语句不能为空
	try
	{
		m_pRecordset.CreateInstance(__uuidof(Recordset));	//创建记录集对象实例
		m_pRecordset->Open(_bstr_t(sql), m_pConnection.GetInterfacePtr(),
			adOpenDynamic, adLockOptimistic, adCmdText); 	//执行SQL得到记录集
	}
	catch(_com_error e)										//捕获可能的异常
	{
		AfxMessageBox(e.Description());
	}
	return m_pRecordset;
}

//**************************************************//
//函数功能：打开记录集组							//
//**************************************************//
_RecordsetPtr& ADO::OpenRecordsets(CString sql, int i)
{
	ASSERT(!sql.IsEmpty());									//SQL语句不能为空
	try
	{
		m_pRecordsets [i].CreateInstance(__uuidof(Recordset));	//创建记录集对象实例
		m_pRecordsets [i]->Open(_bstr_t(sql), m_pConnection.GetInterfacePtr(),
			adOpenDynamic, adLockOptimistic, adCmdText); 	//执行SQL得到记录集
	}
	catch(_com_error e)										//捕获可能的异常
	{
		AfxMessageBox(e.Description());
	}
	return m_pRecordsets [i];
}

//**************************************************//
//函数功能：关闭记录集								//
//**************************************************//
void ADO::CloseRecordset()
{
	if(m_pRecordset->GetState() == adStateOpen)				//判断当前的记录集状态
		m_pRecordset->Close();								//关闭记录集
}

//**************************************************//
//函数功能：关闭记录集组							//
//**************************************************//
void ADO::CloseRecordsets(int i)
{
	if(m_pRecordsets [i]->GetState() == adStateOpen)			//判断当前的记录集状态
		m_pRecordsets [i]->Close();								//关闭记录集
}

//**************************************************//
//函数功能：关闭数据库连接							//
//**************************************************//
void ADO::CloseConn()
{
	m_pConnection->Close();									//关闭数据库连接
	::CoUninitialize();										//释放COM环境
}
