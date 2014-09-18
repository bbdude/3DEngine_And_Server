#include "stdafx.h"
#include "GControl.h"


GControl::GControl(){}
GControl::~GControl(){}
void GControl::draw()
{
	tree.draw();
	//test.draw();
	//floor.draw();
	abar.draw();
}
void GControl::update(ClientDlg * dlg)
{
	//dlg->retrieveDlg();
	updateTimer++;
	if (updateTimer == 99)
	{
		if (!dlg->m_pClient->failure)
			dlg->m_pClient->SendData(/*"," + */player.position.toString() + ",");
	}
	else if (updateTimer >= 100)
	{
		if (!dlg->m_pClient->failure)
		{
			char server_reply[2000];
			int recv_size = 0;
			//if ((recv_size = recv(dlg->m_pClient->s, server_reply, 2000, 0)) != SOCKET_ERROR)
			if ((recv_size = recv(dlg->m_pClient->s, server_reply, 2000, 0)) != 0)
			{
				
				//puts("Reply received\n");

				//Add a NULL terminating character to make it a proper string before printing
				/*server_reply[recv_size] = '\0';
				puts(server_reply);
				player.position << string(server_reply);
				string sTempMsg = "\n" + string(server_reply);
				dlg->retrieveDlg(sTempMsg);*/
				//return;

			}
		}
		updateTimer = 0;
	}

	/*switch (keyState.)
	{
	default:
		break;
	}*/
	if (keyState['1'])
	{
		 //icons;
		std::map<std::string, Icon>::iterator it = abar.icons.find("icon1");
		Icon ico;
		if (it != abar.icons.end())
		{
			//element found;
			ico = it->second;

			abar.icons["icon1"].run();
			//keyState['1'] = false;
		}
	}
	else if (keyState['2'])
	{ //icons;
		std::map<std::string, Icon>::iterator it = abar.icons.find("icon2");
		Icon ico;
		if (it != abar.icons.end())
		{
			//element found;
			ico = it->second;
			abar.icons["icon2"].run();
		}
	}
	else if (keyState['3'])
	{ //icons;
		std::map<std::string, Icon>::iterator it = abar.icons.find("icon3");
		Icon ico;
		if (it != abar.icons.end())
		{
			//element found;
			ico = it->second;
			abar.icons["icon3"].run();
		}
	}
	else if (keyState['4'])
	{ //icons;
		std::map<std::string, Icon>::iterator it = abar.icons.find("icon4");
		Icon ico;
		if (it != abar.icons.end())
		{
			//element found;
			ico = it->second;
			abar.icons["icon4"].run();
		}
	}
	else if (keyState['5'])
	{ //icons;
		std::map<std::string, Icon>::iterator it = abar.icons.find("icon5");
		Icon ico;
		if (it != abar.icons.end())
		{
			//element found;
			ico = it->second;
			abar.icons["icon5"].run();
		}
	}
	else if (keyState['6'])
	{ //icons;
		std::map<std::string, Icon>::iterator it = abar.icons.find("icon6");
		Icon ico;
		if (it != abar.icons.end())
		{
			//element found;
			ico = it->second;
			abar.icons["icon6"].run();
		}
	}
	else if (keyState['7'])
	{ //icons;
		std::map<std::string, Icon>::iterator it = abar.icons.find("icon7");
		Icon ico;
		if (it != abar.icons.end())
		{
			//element found;
			ico = it->second;
			abar.icons["icon7"].run();
		}
	}
	else if (keyState['8'])
	{ //icons;
		std::map<std::string, Icon>::iterator it = abar.icons.find("icon8");
		Icon ico;
		if (it != abar.icons.end())
		{
			//element found;
			ico = it->second;
			abar.icons["icon8"].run();
		}
	}
	else if (keyState['9'])
	{ //icons;
		std::map<std::string, Icon>::iterator it = abar.icons.find("icon9");
		Icon ico;
		if (it != abar.icons.end())
		{
			//element found;
			ico = it->second;
			abar.icons["icon9"].run();
		}
	}
	else if (keyState['0'])
	{ //icons;
		std::map<std::string, Icon>::iterator it = abar.icons.find("icon0");
		Icon ico;
		if (it != abar.icons.end())
		{
			//element found;
			ico = it->second;
			abar.icons["icon0"].run();
		}
	}

	abar.update();
	test.update(0, vector3(0, 0, 0));
	floor.update(0, vector3(0, 0, 0));
	player.update(true);
}
void GControl::init()
{
	//test.LoadGLTextures(1);
	curr = GAME;
	vector3 position(500, -20, -500);
	vector3 color(0.4, 0.3, 0);
	vector2 size(-1000, 1);
	floor.fill(position, size, color, 0);
	floor.init("floor.png");

	position.fill(100, 15, -100);
	size << vector2(10, 10);
	test.fill(position, size, color, 0);
	test.init("wood.png");

	abar.loadGLTextures("actionBar.png");
	abar.loadGLTexturesIco("icon1.png", "icon1");
	abar.loadGLTexturesIco("icon2.png", "icon2");

	tree.loadGLTextures("templateAdvanced.png");

}