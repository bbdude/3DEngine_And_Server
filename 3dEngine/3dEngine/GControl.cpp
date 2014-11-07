#include "stdafx.h"
#include "GControl.h"


GControl::GControl(){}
GControl::~GControl(){}
void GControl::draw()
{
	//tree.draw();
	for (auto & element : cubes)
		element.draw();
	for (auto & element : bullets)
		element.draw();
	//test.draw();
	floor.draw();
	effectTest.draw();
	//testHead.draw();
	//testBody.draw();
	if (testEntity.health > 0)
		testEntity.draw();

	drawGui();
	if (showTree)
		tree.draw();
	abar.draw();

	//abar.draw();
}
void GControl::drawGui()
{
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0.0, screen.x, screen.y, 0.0, -1.0, 10.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glDisable(GL_CULL_FACE);

	glClear(GL_DEPTH_BUFFER_BIT);
	//glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	glBegin(GL_QUADS);
	if (player.invTimer == 0)
		glColor3f(1.0f, 1.0f, 1.0);
	else
		glColor3f(1.0f, 0.0f, 1.0);

	/*glVertex2f((screen.x / 2 - (screen.x / 6)) - 2.6*(100 - player.health), screen.y - (screen.y / 35));
	glVertex2f((screen.x / 2 - (screen.x / 6)) - 2.6*(100 - player.health), screen.y - (screen.y / 15));
	glVertex2f((screen.x / 35), screen.y - (screen.y / 15));
	glVertex2f((screen.x / 35), screen.y - (screen.y / 35));*/
	glVertex2f((screen.x / 2 - (screen.x / 6)) - 2.6*(100 - player.health), 0 + (screen.y / 35));
	glVertex2f((screen.x / 2 - (screen.x / 6)) - 2.6*(100 - player.health), 0 + (screen.y / 15));
	glVertex2f((screen.x / 35), 0 + (screen.y / 15));
	glVertex2f((screen.x / 35), 0 + (screen.y / 35));
	glEnd();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
}
void GControl::update(ClientDlg * dlg)
{
	//dlg->retrieveDlg();
	updateTimer++;
	if (updateTimer == 49)
	{
		if (!dlg->m_pClient->failure){
			string transferPos = "";
			std::ostringstream buff;
			int hitop = 0;
			if (hitOP)
				hitop = 1;
			buff << player.position.x << "," << player.position.z << "," << hitop << ",";
			hitOP = false;
			transferPos += buff.str();
			dlg->m_pClient->SendData(transferPos);
		}
	}
	else if (updateTimer >= 50)
	{
		if (!dlg->m_pClient->failure)
		{
			char server_reply[2000];
			int recv_size = 0;
			if ((recv_size = recv(dlg->m_pClient->s, server_reply, 2000, 0)) != 0)
			{

				string retMsg = "";
				bool read = false;
				for (int i = 0; i < 5; i++)
					if (server_reply[i] != username[i])
					{
					read = true;
					}
				if (read && server_reply[7] != ' ')
				{
					server_reply[recv_size] = '\0';
					puts(server_reply);
					for (int i = 7; i <= 20; i++)
					{
						if (server_reply[i] == ' ' || server_reply[i] == '\n')
							break;
						retMsg += server_reply[i];
					}
				}
				if (retMsg != "")
				{
					size_t pos = 0;
					std::string delimiter = ",";
					std::string token;
					int pas = 0;
					while ((pos = retMsg.find(delimiter)) != std::string::npos) {
						token = retMsg.substr(0, pos);
						switch (pas)
						{
						case 0:
							//test.position.x = stof(token);
							testEntity.position.x = stof(token);
							break;
						case 1:
							//test.position.z = stof(token);
							testEntity.position.z = stof(token);
							break;
						case 2:
							//test.position.z = stof(token);
							if (stof(token) == 1)
								player.health -= 20;
							break;
						default:
							break;
						}
						//std::cout << token << std::endl;
						pas++;
						retMsg.erase(0, pos + delimiter.length());
					}
					int bob = 5;
				}

			}
		}
		updateTimer = 0;
	}
	

	for (auto & element : cubes){
		vector3 newPos = vector3(player.position);
		newPos.z += 10;
		newPos.x += player.speed.x;
		if (element.testColl(newPos, player.size))
		{
			newPos.x -= player.speed.x;
			player.speed.x = 0;
		}
		else if (testEntity.testColl(newPos, player.size))
		{
			newPos.x -= player.speed.x;
			player.speed.x = 0;
		}


		newPos.x -= player.speed.x;
		newPos.z += player.speed.z;
		if (element.testColl(newPos, player.size))
		{
			newPos.z -= player.speed.z;
			player.speed.z = 0;
		}
		//newPos.z -= 50;
		//player.size = vector3(4,0, 4);
		/*if (testEntity.testColl(newPos, player.size))
		{
			newPos.z -= player.speed.z;
			player.speed.z = 0;
		}*/


		for (auto & elemb : bullets)
		{
			if (element.testColl(elemb.position, vector3(elemb.size.x, elemb.size.y, elemb.size.x)))
			{
				elemb.killOff = true;
			}
			if (testEntity.testColl(elemb.position, vector3(elemb.size.x, elemb.size.y, elemb.size.x)))
			{
				testEntity.health -= 5;
				elemb.killOff = true;
				std::cout << "HIT";// +testEntity.health;
			}
		}

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

			effectTest = ParticleEffect();
			effectTest.pushOutMovement(player.position, vector3(50, 50, 50), vector4(1, 0, 1, 1), 20);
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
	//test.update(0, vector3(0, 0, 0));
	//if (testEntity.health 
	testEntity.update();
	for (auto & element : cubes)
		element.update(0, player.position);
	auto i = std::begin(bullets);

	while (i != std::end(bullets)) {
		// do some stuff
		if (i->killOff)
			i = bullets.erase(i);
		else
		{
			i->update(0, player.position);
			i->updateSpeed();
			//if (test.testColl(i->position, vector3(i->size.x, i->size.y, i->size.x))){
			//	i->killOff = true; hitOP = true;
			//}
			++i;
		}
	}
	/*for (auto & element : bullets)
	{
	}*/
	floor.update(0, vector3(0, 0, 0));
	player.update(true);

}
void GControl::fireBullet(vector3 & playerPos, float angle, float lx, float ly, float lz)
{
	//if (whatBullet < 10)
	//{
		//whatBullet++;
		Bullet newBullet(masterBullet);
		newBullet.angle = angle;
		newBullet.position = playerPos;
		newBullet.size.x = 3;
		newBullet.size.y = 2;
		newBullet.speed.x = lx * 0.5f;
		newBullet.speed.z = lz * 0.5f;
		newBullet.speed.y = ly * 0.5f;
		newBullet.position.y = playerPos.y;
		newBullet.color.fill(0.5f, 0.5f, 0.5f);
		bullets.push_back(newBullet);
		//effectTest = ParticleEffect();
		//effectTest.createSpawnPoint(newBullet.position, vector3(5, 5, 5), vector4(1, 0, 1, 1), 20);
	//}
	//else
	//	reloadGun = true;
}
void GControl::init()
{
	//test.LoadGLTextures(1);
	//testHead.init("head");
	//testBody.init("body");
	testEntity.init();
	curr = GAME;
	vector3 position(500, -20, -500);
	vector3 color(0.4, 0.3, 0);
	vector2 size(-1000, 1);
	floor.fill(position, size, color, 0);
	floor.init("floor.png");
	/*position.fill(100, -15, -100);
		size << vector2(25, 50);
		test.fill(position, size, color, 0);
		test.init("wood.png");*/
	position.fill(0, 5, -0);
	size << vector2(25, 50);
	//test.fill(position, size, color, 0);
	//test.init("person.png");
	int offset = 0;
	for (auto & element : cubes){
		position.fill(100 - offset, 5, -100);
		element.fill(position, size, color, 0);
		element.init("wood.png");
		offset += size.x;
	}
	player.size.x = 5;

	masterBullet.setColor(1, 0, 0);

	masterBullet.loadGLTextures("icon2.png");// .filename = "bullet.png";
	masterBullet.init();
	
	abar.loadGLTextures("actionBar.png");
	abar.loadGLTexturesIco("icon1.png", "icon1");
	abar.loadGLTexturesIco("icon2.png", "icon2");

	tree.loadGLTextures("template.png");
	tree.loadData();

	effectTest = ParticleEffect();
}