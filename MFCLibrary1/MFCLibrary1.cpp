// MFCLibrary1.cpp : �ش� DLL�� �ʱ�ȭ ��ƾ�� �����մϴ�.
//

#include "stdafx.h"
#include "MFCLibrary1.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CMainClassDLL::CMainClassDLL()
{
}

CMainClassDLL::~CMainClassDLL()
{
}

void CMainClassDLL::addValue(int a, int b, int *c)
{
	*c = a + b;
}

CMFCClassDll::CMFCClassDll()
{
	a = 0;
	m_pMain = new CMainClassDLL;
}

CMFCClassDll::~CMFCClassDll()
{
	delete m_pMain;
}

CMainClassDLL * CMFCClassDll::getMainClassDll()
{
	return m_pMain;
}

void CMFCClassDll::addValue(int a, int b, int *c)
{
	*c = a + b;
}

CMFCClassDll g_dllClass;

namespace mfcLibraryDll
{
	Dll int addValue(int a, int b, int &c)
	{
		CMFCLibrary1App *pApp = dynamic_cast<CMFCLibrary1App *>(AfxGetApp());
		if (NULL != pApp)
		{
			pApp->m_nCheck += 1;
		}
		int n;
		
		c = a + b;
		n = c;
		return n;
	}
	Dll void addValue2(void *p, int a, int b, int *c)
	{
		CMFCClassDll *pMain = (CMFCClassDll *)p;

		pMain->addValue(a, b, c);
		pMain->a += 1;
		*c = a + b;
	}
	Dll CMFCClassDll *initClassDll()
	{
		CMFCClassDll *pClassDll = new CMFCClassDll;

		return pClassDll;
	}
	Dll void endClassDll(CMFCClassDll *pClassDll)
	{
		SAFE_DELETE(pClassDll);
	}
}

//
//TODO: �� DLL�� MFC DLL�� ���� �������� ��ũ�Ǿ� �ִ� ���
//		MFC�� ȣ��Ǵ� �� DLL���� ���������� ��� �Լ���
//		���� �κп� AFX_MANAGE_STATE ��ũ�ΰ�
//		��� �־�� �մϴ�.
//
//		��:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// �Ϲ����� �Լ� ������ ���⿡ �ɴϴ�.
//		}
//
//		�� ��ũ�δ� MFC�� ȣ���ϱ� ����
//		�� �Լ��� �ݵ�� ��� �־�� �մϴ�.
//		��, ��ũ�δ� �Լ��� ù ��° ���̾�� �ϸ� 
//		��ü ������ �����ڰ� MFC DLL��
//		ȣ���� �� �����Ƿ� ��ü ������ ����Ǳ� ����
//		���;� �մϴ�.
//
//		�ڼ��� ������
//		MFC Technical Note 33 �� 58�� �����Ͻʽÿ�.
//

// CMFCLibrary1App

BEGIN_MESSAGE_MAP(CMFCLibrary1App, CWinApp)
END_MESSAGE_MAP()


// CMFCLibrary1App ����

CMFCLibrary1App::CMFCLibrary1App()
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
	// InitInstance�� ��� �߿��� �ʱ�ȭ �۾��� ��ġ�մϴ�.
	m_nCheck = 0;
	
}

// ������ CMFCLibrary1App ��ü�Դϴ�.

CMFCLibrary1App theApp;

// CMFCLibrary1App �ʱ�ȭ

BOOL CMFCLibrary1App::InitInstance()
{
	CWinApp::InitInstance();
	m_bDllRun = TRUE;
	return TRUE;
}


int CMFCLibrary1App::Run()
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	while (m_bDllRun)
	{
		if(WaitForSingleObject((HANDLE)m_evExit,10)==WAIT_OBJECT_0)
			break;

		m_nCheck++;
		if (m_nCheck > 0xFFFF)
			m_nCheck = 0;
	}
	return CWinApp::Run();
}


int CMFCLibrary1App::ExitInstance()
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	m_bDllRun = FALSE;
	m_evExit.SetEvent();
	return CWinApp::ExitInstance();
}
