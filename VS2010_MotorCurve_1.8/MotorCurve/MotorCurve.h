
// MotorCurve.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CMotorCurveApp:
// �йش����ʵ�֣������ MotorCurve.cpp
//

class CMotorCurveApp : public CWinApp
{
public:
	CMotorCurveApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CMotorCurveApp theApp;