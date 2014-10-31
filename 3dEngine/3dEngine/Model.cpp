#include "stdafx.h"
#include "Model.h"


Model::Model()
{
}


Model::~Model()
{
}
char *textFileRead(char *fn) {


	FILE *fp;
	char *content = NULL;

	int count = 0;

	if (fn != NULL) {
		fp = fopen(fn, "rt");

		if (fp != NULL) {

			fseek(fp, 0, SEEK_END);
			count = ftell(fp);
			rewind(fp);

			if (count > 0) {
				content = (char *)malloc(sizeof(char) * (count + 1));
				count = fread(content, sizeof(char), count, fp);
				content[count] = '\0';
			}
			fclose(fp);
		}
	}
	return content;
}

int textFileWrite(char *fn, char *s) {

	FILE *fp;
	int status = 0;

	if (fn != NULL) {
		fp = fopen(fn, "w");

		if (fp != NULL) {

			if (fwrite(s, sizeof(char), strlen(s), fp) == strlen(s))
				status = 1;
			fclose(fp);
		}
	}
	return(status);
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
	shader.init("shader.vert", "shader.frag");
	//setShaders();
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
	shader.bind();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture);
	glBegin(GL_TRIANGLES);
	glPushMatrix();
	glLoadIdentity();
	//glClearColor(0.0, 0.0, 0.0, 0.0);
	//glColor3f(1, 1, 1);
	for (int l_index = 0; l_index < vertices.size(); l_index++)
	{
		glTexCoord2f(uvs[l_index].x, uvs[l_index].y);
		glVertex3f(vertices[l_index].x * 5, vertices[l_index].y * 5, vertices[l_index].z * 5);
	}
	glDisable(GL_TEXTURE_2D);
	glEnd();
	glPopMatrix();
	shader.unbind();
}
/*void Model::setShaders() {

	char *vs = NULL, *fs = NULL, *fs2 = NULL;

	v = glCreateShader(GL_VERTEX_SHADER);
	f = glCreateShader(GL_FRAGMENT_SHADER);
	f2 = glCreateShader(GL_FRAGMENT_SHADER);


	vs = textFileRead("toon.vert");
	fs = textFileRead("toon.frag");
	fs2 = textFileRead("toon2.frag");

	const char * ff = fs;
	const char * ff2 = fs2;
	const char * vv = vs;

	glShaderSource(v, 1, &vv, NULL);
	glShaderSource(f, 1, &ff, NULL);
	glShaderSource(f2, 1, &ff2, NULL);

	free(vs); free(fs);

	glCompileShader(v);
	glCompileShader(f);
	glCompileShader(f2);

	p = glCreateProgram();

	glLinkProgram(p);
	glUseProgram(p);
}*/

