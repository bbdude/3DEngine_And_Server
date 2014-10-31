#include "stdafx.h"
#include "TalentTree.h"



void Talent::loadGLTextures()
{
	std::string file = name + ".png";
	texture = SOIL_load_OGL_texture
		(
		(char*)file.c_str(),
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y
		);

	// Typical Texture Generation Using Data From The Bitmap
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}
void init()
{

}

TalentTree::TalentTree()
{
}


TalentTree::~TalentTree()
{
}

void TalentTree::loadGLTextures(std::string file)
{
	texture = SOIL_load_OGL_texture
		(
		(char*)file.c_str(),
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y
		);

	vector2 screen = vector2(800, 600);
	// Typical Texture Generation Using Data From The Bitmap
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}
/*void TalentTree::loadGLTexturesIco(std::string file, std::string choice)
{
	icons[choice].texture = SOIL_load_OGL_texture
		(
		(char*)file.c_str(),
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y
		);
	icons[choice].cooldown = 0;
	// Typical Texture Generation Using Data From The Bitmap
	glBindTexture(GL_TEXTURE_2D, icons[choice].texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	vector2 screen = vector2(800, 600);
	icons[choice].size.x = (((screen.x - (screen.x / 10)) - (screen.x / 10)) / 10);
}*/
void TalentTree::loadGLTextures(int limit)
{
}
void TalentTree::update()
{
	/*for (auto & element : icons)
	{
		//if (element.second.cooldown == 0 && element.second.color == vector3(1, 1, 1))
		if (element.second.cooldown == 0 && element.second.color.x == 0)
		{
			element.second.color = vector3(1, 1, 1);
		}
		else if (element.second.cooldown > 0)
		{
			element.second.cooldown--;
		}
	}*/
}
void TalentTree::draw(void)
{
	vector2 screen = vector2(800, 600);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0.0, screen.x, screen.y, 0.0, -1.0, 10.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_TEXTURE_2D);

	int locationx = (screen.x / 10);
	/*for (auto & element : icons)
	{
		glColor3f(element.second.color.x, element.second.color.y, element.second.color.z);

		glBindTexture(GL_TEXTURE_2D, element.second.texture);
		glBegin(GL_QUADS);

		glTexCoord2f(1, 1); glVertex2f(locationx + element.second.size.x, (screen.y - (screen.y / 6))); //left top
		glTexCoord2f(1, 0); glVertex2f(locationx + element.second.size.x, (screen.y - (screen.y / 18))); //left bottom
		glTexCoord2f(0, 0); glVertex2f(locationx, (screen.y - (screen.y / 18))); //right bottom
		glTexCoord2f(0, 1); glVertex2f(locationx, (screen.y - (screen.y / 6))); //right top

		glEnd();
		locationx += element.second.size.x + 1;
	}/**/


	glBindTexture(GL_TEXTURE_2D, texture);

	glBegin(GL_QUADS);

	glTexCoord2f(1, 1); glVertex2f(0, 0); //left top
	glTexCoord2f(1, 0); glVertex2f(0, (screen.y - (screen.y / 6))); //left bottom
	glTexCoord2f(0, 0); glVertex2f(screen.x, (screen.y - (screen.y / 6))); //right bottom
	glTexCoord2f(0, 1); glVertex2f(screen.x, 0); //right top

	glEnd();

	/*int locationx = (screen.x / 10) + 1;
	for (auto & element : icons)
	{
	glBindTexture(GL_TEXTURE_2D, element.second.texture);

	glBegin(GL_QUADS);

	glTexCoord2f(1, 1); glVertex2f(locationx, (screen.y - (screen.y / 6))); //left top
	glTexCoord2f(1, 0); glVertex2f(locationx, (screen.y - (screen.y / 18))); //left bottom
	glTexCoord2f(0, 0); glVertex2f(locationx + element.second.size.x, (screen.y - (screen.y / 18))); //right bottom
	glTexCoord2f(0, 1); glVertex2f(locationx + element.second.size.x, (screen.y - (screen.y / 6))); //right top



	glEnd();
	}*/


	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
}
void TalentTree::init()
{
}
void TalentTree::loadElement(vector<vector<map<std::string, Talent>>> & tileNodes, TiXmlElement * node, int column, int subcolumn, int row)
{
	std::stringstream nameTemp;
	std::stringstream typeTemp;
	std::stringstream amountTemp;
	std::stringstream lockedTemp;

	Talent newTalent = Talent();

	std::string blocked = "true";
	std::string ucAmount = "0";

	nameTemp << node->Attribute("name");
	nameTemp >> newTalent.name;
	typeTemp << node->Attribute("type");
	typeTemp >> newTalent.type;
	lockedTemp << node->Attribute("type");
	lockedTemp >> blocked;
	if (blocked == "true")
		newTalent.avail = true;
	else
		newTalent.avail = false;


	amountTemp << node->Attribute("amount");
	amountTemp >> ucAmount;

	newTalent.pointsA = stoi(ucAmount);
	newTalent.loadGLTextures();
	tileNodes.at(column).at(subcolumn)[newTalent.name] = newTalent;// [row];

	/*if (type == "Wall")
	{
		Wall * nWall = new Wall;
		nWall->init();
		landNodes.at(y) = (Land*)nWall;
		landNodes.at(y)->load();
	}
	else if (type == "Dirt")
	{
		Dirt * nDirt = new Dirt();
		nDirt->init();
		landNodes.at(y) = (Land*)nDirt;
		landNodes.at(y)->load();
	}
	else if (type == "House")
	{
		sideTemp << node->Attribute("side");
		sideTemp >> side;

		House * nDirt = new House();
		nDirt->init();
		landNodes.at(y) = (Land*)nDirt;
		landNodes.at(y)->load(std::stoi(side));
	}
	else if (type == "Water")
	{
		Water * nWater = new Water();
		nWater->init();
		landNodes.at(y) = (Land*)nWater;
		landNodes.at(y)->load();
	}
	else if (type == "Grass")
	{
		Grass * nGrass = new Grass();
		nGrass->init();
		landNodes.at(y) = (Land*)nGrass;
		landNodes.at(y)->load();
	}
	else if (type == "Tree")
	{
		Tree * nTree = new Tree();
		nTree->init();
		landNodes.at(y) = (Land*)nTree;
		landNodes.at(y)->load();
	}*/
}
void TalentTree::loadData()
{
	TiXmlDocument doc("ttree.xml");

	vector<vector<map<std::string, Talent>>> newTree = vector<vector<map<std::string,Talent>>>(3);
	for (auto & i : newTree)
	{
		i = vector<map<std::string, Talent>>(3);
	}
	//map<string, Talent> talentTree;
	if (doc.LoadFile())
	{
		TiXmlElement *pRoot = doc.RootElement();
		TiXmlElement *column = pRoot->FirstChildElement();
		int i = 0;
		while (column)
		{
			TiXmlElement *subColumn = column->FirstChildElement();
			int ii = 0;
			while (subColumn)
			{
				TiXmlElement *finTalent = subColumn->FirstChildElement();
				int iii = 0;
				while (finTalent)
				{
					loadElement(newTree, finTalent, i, ii, iii);
					finTalent = finTalent->NextSiblingElement();
					iii++;
				}
				subColumn = subColumn->NextSiblingElement();
				ii++;
			}
			column = column->NextSiblingElement();
			i++;
		}
	}
	talents = newTree;
}
void TalentTree::changeSel(int change)
{
	//if (change <= max)
	//{
	//	select = change;
	//}
}
void TalentTree::setCD(int choice, int cd)
{

}