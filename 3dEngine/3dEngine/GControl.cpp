#include "stdafx.h"
#include "GControl.h"


GControl::GControl(){}
GControl::~GControl(){}
void GControl::draw()
{
	//tree.draw();
	//glDisable(GL_TEXTURE_2D);
	//glActiveTexture(GL_TEXTURE1);
	//ffor (auto & element : cubes)
	//f	element.draw();
	for (auto & element : aiCubes)
	{
		if (element.light == 5)
			element.drawC();
		else
			element.draw();
	}
	for (auto & element : bullets)
		element.draw();
	//test.draw();
	//ffloor.draw();
	//effectTest.draw();
	//testHead.draw();
	//testBody.draw();
	if (testEntity.health > 0)
	{
		testEntity.draw();
		int i = 1;
		for (auto element : testEntity.aiHold.nextPath)
		{
			if (!element.equals(testEntity.aiHold.nextPath.back()))
			{
				glClearColor(1, 1, 1, 1);
				glLineWidth(2.5);
				glBegin(GL_LINES);
				glColor3f(0.0f, 0.0f, 1.0f);
				glVertex3f(element.x * 10, -15, element.z * 10);
				glVertex3f(testEntity.aiHold.nextPath[i].x * 10, -15, testEntity.aiHold.nextPath[i].z * 10);
				glEnd();
			}
			else
			{
				break;
			}
			i++;
		}
		if (testEntity.aiHold.nextPath.empty())
		{
			testEntity.addPoint(followtestEntity.position);
		}
	}if (followtestEntity.health > 0)
	{
		followtestEntity.draw();
		int i = 1;
		for (auto element : followtestEntity.aiHold.nextPath)
		{
			if (!element.equals(followtestEntity.aiHold.nextPath.back()))
			{
				glClearColor(1, 1, 1, 1);
				glLineWidth(2.5);
				glBegin(GL_LINES);
				glColor3f(0.0f, 0.0f, 1.0f);
				glVertex3f(element.x * 10, -15, element.z * 10);
				glVertex3f(followtestEntity.aiHold.nextPath[i].x * 10, -15, followtestEntity.aiHold.nextPath[i].z * 10);
				glEnd();
			}
			else
			{
				break;
			}
			i++;
		}
		if (followtestEntity.aiHold.nextPath.empty())
		{
			vector3 tempPos = vector3(290,0,290);
			tempPos -= testEntity.position;
			//tempPos.x = (rand() % 29) * 10;
			followtestEntity.addPoint(tempPos);
		}
		else if (followtestEntity.aiHold.followStepsTaken >= 5)
		{
			followtestEntity.aiHold.nextPath.clear();
			vector3 tempPos = vector3(290, 0, 290);
			tempPos -= testEntity.position;
			//tempPos.x = (rand() % 29) * 10;
			followtestEntity.addPoint(tempPos);
			followtestEntity.aiHold.followStepsTaken = 0;
			
			/*if (testEntity.position.x > followtestEntity.position.x)
				xcoord = 1;
			else if (testEntity.position.x < followtestEntity.position.x)
				xcoord = -1;


			if (testEntity.position.z > followtestEntity.position.z)
				zcoord = 1;
			else if (testEntity.position.z < followtestEntity.position.z)
				zcoord = -1;

			vector3 testCoords = followtestEntity.position - testEntity.position;
			if (testCoords.x < testCoords.z)
				fireBullet(followtestEntity.position, 0, xcoord, 0, 0);
			else
				fireBullet(followtestEntity.position, 0, 0, 0, zcoord);*/

		}
	}
	///drawGui();
	///if (showTree)
	///	tree.draw();
	///abar.draw();

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
		reloaded = true;
		reloadedf = true;
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
			if (testEntity.testColl(elemb.position, vector3(elemb.size.x, elemb.size.y, elemb.size.x)) && elemb.tag != "te")
			{
				testEntity.health -= 5;
				elemb.killOff = true;
				std::cout << "HIT";// +testEntity.health;
			}
			if (followtestEntity.testColl(elemb.position, vector3(elemb.size.x, elemb.size.y, elemb.size.x)) && elemb.tag != "tf")
			{
				followtestEntity.health -= 5;
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
	testEntity.update(player.position);
	followtestEntity.update(player.position);
	if (/*rand() % 100 == 25 && */testEntity.aiHold.nextPath.size() == 2 && followtestEntity.aiHold.nextPath.size() == 1)
	{
		followtestEntity.addPoint(testEntity.position);
	}
	//testEntity.position += AIhold::walkFunction(vector3(100, 0, 100), testEntity.position);

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

	int xcoord = 0;
	int zcoord = 0;

	if (testEntity.position.x > followtestEntity.position.x)
		xcoord = 1;
	else if (testEntity.position.x < followtestEntity.position.x)
		xcoord = -1;
	if (testEntity.position.z > followtestEntity.position.z)
		zcoord = 1;
	else if (testEntity.position.z < followtestEntity.position.z)
		zcoord = -1;

	int convertedCoordx = testEntity.position.x / 4;
	int convertedCoordxf = followtestEntity.position.x / 4;
	int convertedCoordz = testEntity.position.x / 4;
	int convertedCoordzf = followtestEntity.position.x / 4;

	//testEntity.position.closeequals()
	if (convertedCoordx == convertedCoordxf && reloadedf)
	{
		fireBullet(followtestEntity.position, 0, 0, 0, zcoord, "tf");
		reloadedf = false;
	}
	else if (convertedCoordz == convertedCoordzf && reloadedf)
	{
		fireBullet(followtestEntity.position, 0, xcoord, 0, 0,"tf");
		reloadedf = false;
	}

	if (testEntity.aiHold.followStepsTaken == 5)
	{
		testEntity.aiHold.followStepsTaken = 0;
		fireBullet(testEntity.position, 0, 1, 0, 0,"te");
		fireBullet(testEntity.position, 0, -1, 0, 0,"te");
		fireBullet(testEntity.position, 0, 0, 0, 1,"te");
		fireBullet(testEntity.position, 0, 0, 0, -1,"te");

	}

	floor.update(0, vector3(0, 0, 0));
	player.update(true);


}
void GControl::fireBullet(vector3 & playerPos, float angle, float lx, float ly, float lz)
{
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
	newBullet.tag = "";
	bullets.push_back(newBullet);
}
void GControl::fireBullet(vector3 & playerPos, float angle, float lx, float ly, float lz,string tag)
{
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
	newBullet.tag = tag;
	bullets.push_back(newBullet);
}
void GControl::init()
{
	//test.LoadGLTextures(1);
	//testHead.init("head");
	//testBody.init("body");
	testEntity.init();
	testEntity.addPoint(vector3(100, 0, 140));
	followtestEntity.init();
	//followtestEntity.addPoint(vector3(0, 0, 290));
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

	for (int i = 0; i < 30; i++)
	{
		for (int ii = 0; ii < 30; ii++)
		{
			/*
			for (int i = 5; i < 25; i++)
			{
			map[i][m / 2] = 1;
			}for (int i = 5; i < 25; i++)
			{
			map[n / 2][i] = 1;
			}
			*/
			Cube newCube = Cube(i * 10, -15, ii * 10, 1, 1);
			newCube.light = 0;

			if ((i == 16 && ii > 5 && ii < 26))
				newCube.light = 5;
			else if ((ii == 16 && i > 5 && i < 26))
				newCube.light  = 5;
				//newCube.color = vector3(1, 0, 0);
			//newCube.init("icon2.png");
			aiCubes.push_back(newCube);
		}
	}
}