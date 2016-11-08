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
	_ConnectionPtr m_pConnection;						//���Ӷ���ָ��
	_RecordsetPtr m_pRecordset;							//��¼������ָ��	
	_RecordsetPtr m_pRecordsets [4];					//��¼������ָ����
	_CommandPtr m_pCommand;								//�������ָ��

public:
	ADO();
	virtual ~ADO();
	void OnInitADOConn(CString dbPath);					//�������ݿ�
	_RecordsetPtr&  OpenRecordset(CString sql);			//�򿪼�¼��
	_RecordsetPtr&  OpenRecordsets(CString sql, int i);	//�򿪼�¼��
	void CloseRecordset();								//�رռ�¼��
	void CloseRecordsets(int i);						//�رռ�¼��
	void CloseConn();									//�ر����ݿ�����
};

#endif // !defined(AFX_ADO_H__EF02B4FA_E2AC_4CCC_908E_B42F5EA19898__INCLUDED_)
