// MFCLibrary1.cpp : 해당 DLL의 초기화 루틴을 정의합니다.
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
//TODO: 이 DLL이 MFC DLL에 대해 동적으로 링크되어 있는 경우
//		MFC로 호출되는 이 DLL에서 내보내지는 모든 함수의
//		시작 부분에 AFX_MANAGE_STATE 매크로가
//		들어 있어야 합니다.
//
//		예:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// 일반적인 함수 본문은 여기에 옵니다.
//		}
//
//		이 매크로는 MFC로 호출하기 전에
//		각 함수에 반드시 들어 있어야 합니다.
//		즉, 매크로는 함수의 첫 번째 문이어야 하며 
//		개체 변수의 생성자가 MFC DLL로
//		호출할 수 있으므로 개체 변수가 선언되기 전에
//		나와야 합니다.
//
//		자세한 내용은
//		MFC Technical Note 33 및 58을 참조하십시오.
//

// CMFCLibrary1App

BEGIN_MESSAGE_MAP(CMFCLibrary1App, CWinApp)
END_MESSAGE_MAP()


// CMFCLibrary1App 생성

CMFCLibrary1App::CMFCLibrary1App()
{
	// TODO: 여기에 생성 코드를 추가합니다.
	// InitInstance에 모든 중요한 초기화 작업을 배치합니다.
	m_nCheck = 0;
	
}

// 유일한 CMFCLibrary1App 개체입니다.

CMFCLibrary1App theApp;

// CMFCLibrary1App 초기화

BOOL CMFCLibrary1App::InitInstance()
{
	CWinApp::InitInstance();
	m_bDllRun = TRUE;
	return TRUE;
}


int CMFCLibrary1App::Run()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
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
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	m_bDllRun = FALSE;
	m_evExit.SetEvent();
	return CWinApp::ExitInstance();
}
