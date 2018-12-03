// DLLTestView.h : interface of the CDLLTestView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_DLLTESTVIEW_H__65EDC230_413B_4857_A63C_04D40722E319__INCLUDED_)
#define AFX_DLLTESTVIEW_H__65EDC230_413B_4857_A63C_04D40722E319__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Sync_CaseDownloadDll.h"

class CDLLTestView : public CView
{
protected: // create from serialization only
	CDLLTestView();
	DECLARE_DYNCREATE(CDLLTestView)

// Attributes
public:
	CDLLTestDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDLLTestView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual void OnInitialUpdate();
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDLLTestView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CDLLTestView)
	afx_msg void OnDestroy();
	afx_msg void OnStart();
	afx_msg void OnStop();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	char	m_pCasePath[MAX_PATH + 1];	// �����ļ�����·��
	HANDLE	m_nThread;					// �߳̾��
	CString	m_strExePath;				// exe�ļ�����·��

	HINSTANCE m_hDLL;					// ���ز�����̬����
	BOOL LoadECGLibrary(CString& strFile);	// ���ض�̬��
};

#ifndef _DEBUG  // debug version in DLLTestView.cpp
inline CDLLTestDoc* CDLLTestView::GetDocument()
   { return (CDLLTestDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLLTESTVIEW_H__65EDC230_413B_4857_A63C_04D40722E319__INCLUDED_)
