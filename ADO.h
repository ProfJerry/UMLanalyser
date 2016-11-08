// ADO.h: interface for the ADO class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ADO_H__EF02B4FA_E2AC_4CCC_908E_B42F5EA19898__INCLUDED_)
#define AFX_ADO_H__EF02B4FA_E2AC_4CCC_908E_B42F5EA19898__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class ADO  
{
public:
	_ConnectionPtr m_pConnection;						//连接对象指针
	_RecordsetPtr m_pRecordset;							//记录集对象指针	
	_RecordsetPtr m_pRecordsets [4];					//记录集对象指针组
	_CommandPtr m_pCommand;								//命令对象指针

public:
	ADO();
	virtual ~ADO();
	void OnInitADOConn(CString dbPath);					//连接数据库
	_RecordsetPtr&  OpenRecordset(CString sql);			//打开记录集
	_RecordsetPtr&  OpenRecordsets(CString sql, int i);	//打开记录集
	void CloseRecordset();								//关闭记录集
	void CloseRecordsets(int i);						//关闭记录集
	void CloseConn();									//关闭数据库连接
};

#endif // !defined(AFX_ADO_H__EF02B4FA_E2AC_4CCC_908E_B42F5EA19898__INCLUDED_)
