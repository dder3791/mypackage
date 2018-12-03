// DLLTestDoc.cpp : implementation of the CDLLTestDoc class
//

#include "stdafx.h"
#include "DLLTest.h"

#include "DLLTestDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDLLTestDoc

IMPLEMENT_DYNCREATE(CDLLTestDoc, CDocument)

BEGIN_MESSAGE_MAP(CDLLTestDoc, CDocument)
	//{{AFX_MSG_MAP(CDLLTestDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDLLTestDoc construction/destruction

CDLLTestDoc::CDLLTestDoc()
{
	// TODO: add one-time construction code here

}

CDLLTestDoc::~CDLLTestDoc()
{
}

BOOL CDLLTestDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CDLLTestDoc serialization

void CDLLTestDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CDLLTestDoc diagnostics

#ifdef _DEBUG
void CDLLTestDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CDLLTestDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDLLTestDoc commands
