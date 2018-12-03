// DLLTestView.cpp : implementation of the CDLLTestView class
//

#include "stdafx.h"
#include "DLLTest.h"

#include "DLLTestDoc.h"
#include "DLLTestView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDLLTestView

IMPLEMENT_DYNCREATE(CDLLTestView, CView)

BEGIN_MESSAGE_MAP(CDLLTestView, CView)
	//{{AFX_MSG_MAP(CDLLTestView)
	ON_WM_DESTROY()
	ON_COMMAND(ID_START, OnStart)
	ON_COMMAND(ID_STOP, OnStop)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDLLTestView construction/destruction

// �߳�״̬�ص�����
static void CALLBACK UpdateDownloadMessage(DownloadMessage emDLM, int nPercent)
{
	TRACE(_T("\n %d "), (int)emDLM);
	switch(emDLM)
	{
	case CASEDOWNLOAD:
		// 0  �������²�������ʱ����·�����������µ�XML�ļ�
		break;
	case ERROR_OPEN:
		// 1  �˿ڴ�ʧ�ܣ���ȷ�ϴ��ں��Ƿ���ȷ�������豸�����Ƿ���ȷ��Ȼ�������߳�
		break;
	case ERROR_VSN:
		// 2  ��ȡ�豸�汾��ʧ�ܣ���ȷ���豸�����Ƿ�������Ȼ�������߳�
		break;
	case ERROR_DEV:
		// 3  ��ȡ�豸��ʶʧ�ܣ���ȷ���豸�����Ƿ�������Ȼ�������߳�
		break;
	case ERROR_CASES:
		// 4  ��ȡ������ʧ�ܣ���ȷ���豸�����Ƿ�������Ȼ�������߳�
		break;
	case ERROR_NOCASE:
		// 5  δ��⵽�²���
		break;
	case ERROR_INFO:
		// 6  ��ȡ������Ϣʧ�ܣ���ȷ���豸�����Ƿ�������Ȼ�������߳�
		break;
	case ERROR_DATA:
		// 7  ��ȡ��������ʧ�ܣ���ȷ���豸�����Ƿ�������Ȼ�������߳�
		break;
	case ERROR_DELETE:
		// 8  ɾ������ʧ�ܣ���ȷ���豸�����Ƿ�������Ȼ�������߳�
		break;
	case ERROR_SPACE:
		// 9  ���̿ռ䲻�㣬����Ĳ�������·����������̺������߳�
		break;
	case ERROR_END:
		// 10 ��ֹ����
		break;
	case DOWNLOADING:
		TRACE(_T("\n Downloading: %d"), nPercent);
		break;
	default:
		break;
	}
}

CDLLTestView::CDLLTestView()
{
	// ��Ա������ֵ
	m_hDLL = NULL;
	m_strExePath = _T("");
	memset(m_pCasePath, 0, sizeof(m_pCasePath));
}

CDLLTestView::~CDLLTestView()
{
}

/////////////////////////////////////////////////////////////////////////////
// CDLLTestView drawing

void CDLLTestView::OnDraw(CDC* pDC)
{
	CDLLTestDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
}

/////////////////////////////////////////////////////////////////////////////
// CDLLTestView diagnostics

#ifdef _DEBUG
void CDLLTestView::AssertValid() const
{
	CView::AssertValid();
}

void CDLLTestView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CDLLTestDoc* CDLLTestView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDLLTestDoc)));
	return (CDLLTestDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDLLTestView message handlers
BOOL CDLLTestView::LoadECGLibrary(CString& strFile)
{
	if (m_hDLL != NULL)
	{
		FreeLibrary(m_hDLL);
		m_hDLL = NULL;
	}

	m_hDLL = LoadLibrary(strFile);
	if (m_hDLL == NULL)
	{
		return FALSE;
	}

	return TRUE;
}

void CDLLTestView::OnInitialUpdate() 
{
	CView::OnInitialUpdate();

	// ��ȡexe�ļ�·��
	TCHAR exeFullPath[MAX_PATH];
	GetModuleFileName(NULL,exeFullPath,MAX_PATH);
	m_strExePath.Format(_T("%s"), exeFullPath);
	int nIndex = m_strExePath.ReverseFind(_T('\\'));
	if(nIndex == -1)
	{
		return;
	}
	m_strExePath = m_strExePath.Left(nIndex);
	m_strExePath += _T("\\");

	// ��̬���ļ�·��
	CString strDLL = m_strExePath + _T("Sync_CaseDownload.dll");

	// ����·���������Գ��򽫲�������·�������ڱ���·����Archive�ļ����У���ʵ��ʹ��ʱ���û����������ô�·����
	CString strCasePath = m_strExePath + _T("Archive\\");
	memset(m_pCasePath, 0, sizeof(m_pCasePath));
	int nLength = min(strCasePath.GetLength(), MAX_PATH);

	strcpy(m_pCasePath, strCasePath.GetBuffer(nLength + 1));
	strCasePath.ReleaseBuffer();

	m_pCasePath[MAX_PATH] = '\0';

	if(!LoadECGLibrary(strDLL))
	{
		return;
	}
}

void CDLLTestView::OnDestroy() 
{
	CView::OnDestroy();

	if (m_hDLL != NULL)
	{
		StopDownloadCase();
		FreeLibrary(m_hDLL);
		m_hDLL = NULL;
	}
}

void CDLLTestView::OnStart() 
{
	if(m_hDLL == NULL)
	{
		return;
	}

	if(CheckPort(13))
	{
		StartDownloadCase(13, 100, m_pCasePath, UpdateDownloadMessage);
	}
}

void CDLLTestView::OnStop() 
{
	if(m_hDLL == NULL)
	{
		return;
	}

	StopDownloadCase();
}
