// DLLTestDoc.h : interface of the CDLLTestDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_DLLTESTDOC_H__C1CB77D1_3F4B_42E9_A037_F345D247AE00__INCLUDED_)
#define AFX_DLLTESTDOC_H__C1CB77D1_3F4B_42E9_A037_F345D247AE00__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CDLLTestDoc : public CDocument
{
protected: // create from serialization only
	CDLLTestDoc();
	DECLARE_DYNCREATE(CDLLTestDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDLLTestDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDLLTestDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CDLLTestDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLLTESTDOC_H__C1CB77D1_3F4B_42E9_A037_F345D247AE00__INCLUDED_)
