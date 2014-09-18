/*
Coded by Robel Sharma
Date: 20-08-2013
If you use in any product please
make sure to write my credits

*/
#pragma once

#include "string.h"
#include "string"
#include<winsock2.h>
#include <iostream>
using namespace std;
class ClientDlg;

class ClientCon
{
public:
	ClientCon(void);
	ClientCon(ClientDlg *dlg);
	~ClientCon(void);
	void StartConnect(string sAddress, int iPort, string sUsername);
	void SendData(string sMessage);

	WSADATA wsa;
	SOCKET s;
	ClientDlg *m_pClient;
	string m_pUser = "testU";
	bool failure = false;

};

