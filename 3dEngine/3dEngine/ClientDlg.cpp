#include "stdafx.h"
#include "ClientDlg.h"


ClientDlg::ClientDlg()
{
}


ClientDlg::~ClientDlg()
{
}
UINT ClientDlg::ThreadFunc()
{
	// Do your thing, this thread now has access to all the classes member variables

	//text,port,username
	//m_pClient = new ClientCon();
	m_pClient->StartConnect("text", 85, "testI");
	return 0;
}


void ClientDlg::Logout()
{
	// TODO: Add your control notification handler code here

	//ShowServerInfo(m_pClient->m_pUser + " is logged out\n");
	delete m_pClient;
}
void ClientDlg::retrieveDlg(std::string text)
{
	std::cout << text;
}