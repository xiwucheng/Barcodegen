// Barcodegen.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CBarcodegenApp:
// �йش����ʵ�֣������ Barcodegen.cpp
//

class CBarcodegenApp : public CWinApp
{
public:
	CBarcodegenApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CBarcodegenApp theApp;