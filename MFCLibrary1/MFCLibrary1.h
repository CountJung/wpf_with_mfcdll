// MFCLibrary1.h : MFCLibrary1 DLL의 기본 헤더 파일입니다.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH에 대해 이 파일을 포함하기 전에 'stdafx.h'를 포함합니다."
#endif

#include "resource.h"		// 주 기호입니다.
#include <afxmt.h>

// CMFCLibrary1App
// 이 클래스의 구현을 보려면 MFCLibrary1.cpp를 참조하십시오.
//

#define MSG_CALL_DATA WM_USER+0x01

class CMFCLibrary1App : public CWinApp
{
public:
	CMFCLibrary1App();

	BOOL m_bDllRun;
	CEvent m_evExit;
	int m_nCheck;

// 재정의입니다.

public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
	virtual int Run();
	virtual int ExitInstance();
};

class CMainClassDLL
{
public:
	CMainClassDLL();
	~CMainClassDLL();

	void addValue(int a, int b, int *c);
private:
	
};

class CLASS_DLL CMFCClassDll
{
public:
	CMFCClassDll();
	~CMFCClassDll();

	int a;
	CMainClassDLL *getMainClassDll();
	void addValue(int a, int b, int *c);

private:
	CMainClassDLL *m_pMain;
	
};
