// MFCLibrary1.h : MFCLibrary1 DLL�� �⺻ ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.
#include <afxmt.h>

// CMFCLibrary1App
// �� Ŭ������ ������ ������ MFCLibrary1.cpp�� �����Ͻʽÿ�.
//

#define MSG_CALL_DATA WM_USER+0x01

class CMFCLibrary1App : public CWinApp
{
public:
	CMFCLibrary1App();

	BOOL m_bDllRun;
	CEvent m_evExit;
	int m_nCheck;

// �������Դϴ�.

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
