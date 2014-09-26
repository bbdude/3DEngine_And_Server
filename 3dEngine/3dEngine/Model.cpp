#include "stdafx.h"
#include "Model.h"


Model::Model()
{
}


Model::~Model()
{
}

void Model::loadOBJ(const char * path, std::vector < vector3 > & out_vertices, std::vector < vector2 > & out_uvs, std::vector < vector3 > & out_normals)
{
	std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
	std::vector<vector3> temp_vertices;
	std::vector<vector2> temp_uvs;
	std::vector<vector3> temp_normals;

	FILE * file = fopen(path, "r");
	if (file == NULL)
		return;

	while (1)
	{
		char lineHeader[128];
		int res = fscanf(file, "%s", lineHeader);
		if (res == EOF)
			break;

		if (strcmp(lineHeader, "v") == 0)
		{
			vector3 vertex;
			fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
			temp_vertices.push_back(vertex);
		}else if (strcmp(lineHeader, "vt") == 0)
		{
			vector2 uv;
			fscanf(file, "%f %f\n", &uv.x, &uv.y);
			temp_uvs.push_back(uv);
		}
		else if (strcmp(lineHeader, "f") == 0)
		{
			std::string vertex1, vertex2, vertex3;
			unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
			int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
			if (matches != 9){
				//printf("File can't be read by our simple parser : ( Try exporting with other options\n");
				exit(matches);
				return;
			}
			vertexIndices.push_back(vertexIndex[0]);
			vertexIndices.push_back(vertexIndex[1]);
			vertexIndices.push_back(vertexIndex[2]);
			uvIndices.push_back(uvIndex[0]);
			uvIndices.push_back(uvIndex[1]);
			uvIndices.push_back(uvIndex[2]);
			normalIndices.push_back(normalIndex[0]);
			normalIndices.push_back(normalIndex[1]);
			normalIndices.push_back(normalIndex[2]);
		}
	}
	//out_vertices = vertexIndices;
	
	for (unsigned int i = 0; i < vertexIndices.size(); i++){
		unsigned int vertexIndex = vertexIndices[i];
		vector3 vertex = temp_vertices[vertexIndex - 1];
		out_vertices.push_back(vertex);
	}
	for (unsigned int i = 0; i < uvIndices.size(); i++){
		unsigned int uvIndex = uvIndices[i];
		vector2 uv = temp_uvs[uvIndex - 1];
		//vertex.normalise();
		out_uvs.push_back(uv);
	}
}
void Model::loadGLTextures(std::string file)
{
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
void Model::init(std::string part)
{
	if (part == "head")
	{
		loadOBJ("facecolor.obj", vertices, uvs, normals);
		loadGLTextures("facemeshtestcolor.png");
	}
	else if (part == "body")
	{
		loadOBJ("body.obj", vertices, uvs, normals);
		loadGLTextures("bodypaint.png");
	}
}
void Model::draw()
{
	//glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vector3), &vertices[0], GL_STATIC_DRAW);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture);
	glBegin(GL_TRIANGLES);
	glPushMatrix();
	glLoadIdentity();
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glColor3f(1, 1, 1);
	//vector3 color = vector3(0, 1, 0);
	for (int l_index = 0; l_index < vertices.size(); l_index++)
	{
		//glRotatef(angle,1,0,0);
		//glClearColor(0.0, 1.0, 0.0, 0.5);
		//glColor3f(color.x, color.y, color.z);
		//color.x += 0.001f;
		//color.y -= 0.001f;

		//glColor3f((float)(l_index/100), 0, 0);
		//if (angle != 0)
//			glRotatef(-angle * 100, 0.0, 0.0, 1.0);
		glTexCoord2f(uvs[l_index].x, uvs[l_index].y);
		glVertex3f(vertices[l_index].x * 5, vertices[l_index].y * 5, vertices[l_index].z * 5);
		//glVertex3f(vertices[l_index].x * 5, vertices[l_index].y * 5, vertices[l_index].z * 5);
		//glVertex3f(vertices[l_index].x * 5, vertices[l_index].y * 5, vertices[l_index].z * 5);
	}
	glDisable(GL_TEXTURE_2D);
	glEnd();
}