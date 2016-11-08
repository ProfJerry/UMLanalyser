// UMLanalyserDlg.h : header file
//
#include <msxml2.h>
#include "ADO.h"
#include "BmpEdit.h"
#include "DrawButton.h"

#if !defined(AFX_UMLANALYSERDLG_H__63844F22_B6E2_4A17_A3B6_FD042097DC93__INCLUDED_)
#define AFX_UMLANALYSERDLG_H__63844F22_B6E2_4A17_A3B6_FD042097DC93__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define NOTSUCC		 0		 //���ؽ��״̬��ʧ��
#define IGNORED		 1		 //���ؽ��״̬���ɹ�
#define SUCCEED		 2		 //���ؽ��״̬���������Եĳɹ�
typedef unsigned int RESULT;

/////////////////////////////////////////////////////////////////////////////
// CUMLanalyserDlg dialog

class CUMLanalyserDlg : public CDialog
{
// Construction
public:
	BOOL ExportDatabase (CString dbPath);
	BOOL SetTxtPath (CString dbPath);
	BOOL FindClassThroughAssociation (CString classID, CString & endName);
	CString FindOS (IXMLDOMNodeList * brothers, CString osID);
	CString FindLifeline (IXMLDOMNodeList * brothers, CString lifelineID);
	unsigned int InteractionSiInvariantAnalyse(IXMLDOMNode *pNode, CString interactionSiID);
	unsigned int InteractionSIAnalyse(IXMLDOMNode *pNode, CString interactionName, CString interactionID);
	unsigned int MessageArgumentAnalyse(IXMLDOMNode *pNode, CString messageName, CString messageID);
	unsigned int CFoperandGuardAnalyse(IXMLDOMNode *pNode, CString cfopID);
	unsigned int CFOperandAnalyse(IXMLDOMNode *pNode, CString cfName, CString cfID);
	unsigned int ActorAnalyse(IXMLDOMNode *pNode, CString parentName, CString parentID);
	unsigned int CollaborationAttributeAnalyse(IXMLDOMNode *pNode, CString collaborationName, CString collaborationID);
	unsigned int InteractionCFAnalyse(IXMLDOMNode *pNode, CString interactionName, CString interactionID);
	unsigned int InteractionGateAnalyse(IXMLDOMNode *pNode, CString interactionName, CString interactionID);
	unsigned int InteractionMessageAnalyse(IXMLDOMNode *pNode, CString interactionName, CString interactionID, IXMLDOMNodeList * brothers);
	unsigned int InteractionLifelineAnalyse(IXMLDOMNode *pNode, CString interactionName, CString interactionID);
	unsigned int InteractionOSAnalyse(IXMLDOMNode *pNode, CString interactionName, CString interactionID, unsigned int number, IXMLDOMNodeList * brothers);
	unsigned int ClassGeneralizationAnalyse(IXMLDOMNode *pNode, CString className, CString classID);
	unsigned int ClassOperationAnalyse(IXMLDOMNode *pNode, CString className, CString classID);
	unsigned int ClassAttributeAnalyse (IXMLDOMNode *pNode, CString className, CString classID);
	unsigned int InteractionAnalyse(IXMLDOMNode *pNode, CString collaborationName, CString collaborationID);
	unsigned int AssociationClassAnalyse(IXMLDOMNode *pNode, CString parentName, CString parentID);
	unsigned int CollaborationAnalyse (IXMLDOMNode *pNode, CString parentName, CString parentID);
	unsigned int AssociationAnalyse (IXMLDOMNode * pNode, CString parentName, CString parentID);
	unsigned int ClassAnalyse (IXMLDOMNode * pNode, CString parentName, CString parentID);
	unsigned int NodeAnalyse (IXMLDOMNode *pNode, CString parentName, CString parentID);
	BOOL CreateDatabaseFile ();
	BOOL SetNameSpaces (CString strPath);
	void Clean();

	BOOL isSelected;					//��ʶ�Ƿ�ѡ���˴��ļ��ı���

	ADO m_Ado;							//���ݿ�ADO����
	IXMLDOMDocument2 * pXMLDoc;			//XML�ļ��ĵ�����
	IXMLDOMParseError * pObjError;		//MSXML������Ϣ
	IXMLDOMNode * rootNode;				//XML�ĵ�����ĸ��ڵ�
	VARIANT vSrc;
	BSTR bstr;

	CString content;					//xml�ļ�����
	CString logContent;					//��־����
	CString txtContent;					//�������
	CString strPath;					//���������ļ�·��
	CString databasePath;				//�洢��������ݿ��ļ�·��
	CString logPath;					//��־�ļ�·��
	CString txtPath;					//����xml�ļ�·��
	CString xsdPath;					//����xsd�ļ�·��
	CString xml4RelaPath;               //������ϵ�ļ���xml�ļ�·��
	CFile logFile;						//��־�ļ�


	CUMLanalyserDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CUMLanalyserDlg)
	enum { IDD = IDD_UMLANALYSER_DIALOG };
	CDrawButton	m_txtReturn;
	CDrawButton	m_logReturn;
	CDrawButton	m_Close;
	CDrawButton m_bTxt;
	CDrawButton	m_bLog;
	CDrawButton	m_Analyse;
	CDrawButton	m_Open;
	CBmpEdit	m_Edit;
	CBmpEdit	m_Txt;
	CBmpEdit	m_Log;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUMLanalyserDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CUMLanalyserDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButtonOpen();
	afx_msg void OnDestroy();
	afx_msg void OnButtonAnalyse();
	afx_msg void OnButtonLog();
	afx_msg void OnButtonTxt();
	afx_msg void OnButtonTxtcancel();
	afx_msg void OnButtonLogcancel();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_UMLANALYSERDLG_H__63844F22_B6E2_4A17_A3B6_FD042097DC93__INCLUDED_)
