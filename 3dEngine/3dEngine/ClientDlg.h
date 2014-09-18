#pragma once
#include "ClientCon.h"
#define _WINSOCKAPI_    // stops windows.h including winsock.h
#include <Windows.h>
class ClientDlg
{
public:
	ClientDlg();
	~ClientDlg();
	UINT ThreadFunc();
	void Logout();
	void retrieveDlg(std::string text);
	ClientCon *m_pClient;
};

