/*
	Author:Hanning Chen
	Class:ECE6122
	Last Date Modified:2019.11.21
	Description:This is the .cpp file for ECE6122 which includes the implementation of
	objLoader function to load obj parameter and enhanced draw function
*/
#include"OBJ_Loader.h"

//loadOBJ is the function to load vertice parameter into the function
//the input parameter includes the path of the file,the vector that stores vertices and 
//the vector stores matrial vectices and vecter that stores normal vertices.
bool loadOBJ(const char* path, vector<vec3>& out_vertices,
	vector<vec2>& out_uvs, vector<vec3>& out_normals)
{
	//vertexIndices, uvIndices, normalIndices are used to 
	//store the index of points for each surface
	vector<int> vertexIndices, uvIndices, normalIndices;
	//temp_vertices is a vector used to store each vertices parameter
	vector<vec3> temp_vertices;
	//temp_uvs is a vector used to store each material vertices parameter
	vector<vec2> temp_uvs;
	//temp_normals is a vector used to store each normal vertices parameter
	vector<vec3> temp_normals;	
	//file is the input file stream
	ifstream file(path);
	//we sue line to hold each line's parameter
	string line;
	while (getline(file,line))
	{
		//if the first 2 alpabet is vt then we store the following parameter into
		//vertice texture vector
		if (line.substr(0,2) == "vt")
		{
			istringstream s(line.substr(3));
			vec2* uv;
			uv = new vec2;
			s >> uv->x;
			s >> uv->y;
			temp_uvs.push_back(*uv);
		}
		else if (line.substr(0, 2) == "vn")
		{
			//if the first 2 alpabet is vn then we store the following parameter into
			//vertice noral vector
			istringstream s(line.substr(3));
			vec3* normal;
			normal = new vec3;
			s >> normal->x;
			s >> normal->y;
			s >> normal->z;
			temp_normals.push_back(*normal);
		}
		else if (line.substr(0, 1) == "v")
		{
			//if the first alpabet is v then we store the following parameter into
			//vertice vector
			istringstream s(line.substr(2));
			vec3* vertex;
			vertex = new vec3;
			s >> vertex->x;
			s >> vertex->y;
			s >> vertex->z;
			temp_vertices.push_back(*vertex);
		}
		else if (line.substr(0, 1) == "f")
		{
			//if the first alpabet is f then we should use the index of points to get the
			//parameter of each points in the square
			istringstream s(line.substr(2));
			//Here we use 4 array to store the parameter of 4 vertices
			unsigned int vertexIndex[4], uvIndex[4], normalIndex[4];
			s >> vertexIndex[0];
			s >> uvIndex[0];
			s >> normalIndex[0];

			s >> vertexIndex[1];
			s >> uvIndex[1];
			s >> normalIndex[1];

			s >> vertexIndex[2];
			s >> uvIndex[2];
			s >> normalIndex[2];
			
			s >> vertexIndex[3];
			s >> uvIndex[3];
			s >> normalIndex[3];
			//Then we push them into vector
			vertexIndices.push_back(vertexIndex[0]);
			vertexIndices.push_back(vertexIndex[1]);
			vertexIndices.push_back(vertexIndex[2]);
			vertexIndices.push_back(vertexIndex[3]);
			uvIndices.push_back(uvIndex[0]);
			uvIndices.push_back(uvIndex[1]);
			uvIndices.push_back(uvIndex[2]);
			uvIndices.push_back(uvIndex[3]);
			normalIndices.push_back(normalIndex[0]);
			normalIndices.push_back(normalIndex[1]);
			normalIndices.push_back(normalIndex[2]);
			normalIndices.push_back(normalIndex[3]);
		}
		else if (line.substr(0, 1) == "#")
		{

		}
		else
		{

		}
	}
	//Since in Obj file the start number is 1 and in C++ the start is 0
	//So we should minus 1 to each cordinate fo these parametr when we return them
	for (unsigned int i = 0; i < vertexIndices.size(); i++)
	{
		//We get the index of each vertices in a face first
		unsigned int vertexIndex = vertexIndices[i];
		//Then we get the vertex we have to minus 1 since the Obj file start 1 and c++ start 0
		vec3 vertex = temp_vertices[vertexIndex - 1];
		out_vertices.push_back(vertex);
	}
	//Here we load the texture parameter in to out_uvs vector
	for (unsigned int i = 0; i < uvIndices.size(); i++)
	{
		unsigned int uvIndex = uvIndices[i];
		vec2 vertex = temp_uvs[uvIndex - 1];
		out_uvs.push_back(vertex);
	}
	//Here we load the normal parameter in to out_normals vector
	for (unsigned int i = 0; i < normalIndices.size(); i++)
	{
		unsigned int normalndex = normalIndices[i];
		vec3 vertex = temp_normals[normalndex - 1];
		out_normals.push_back(vertex);
	}
	return true;
}
//enhanceDraw function is used to draw the enhanced mode piece and we should input the 
//name that we want to draw
void enhanceDraw(const char* name)
{
	//Here we initiate vector to store the parameter including vertice coordination
	//normal coordiantion and textire coordination
	vector<vec3> out_vertices;
	vector<vec2> out_uvs;
	vector<vec3> out_normals;
	//we use loadOBJ to get the parameter and put them into vector
	loadOBJ(name, out_vertices, out_uvs, out_normals);
	//We have to draw the vertice and normal vertice and each 4 points belong to a face
	for (int i = 0; i < out_vertices.size(); i = i + 4)
	{
		glBegin(GL_POLYGON);
		glNormal3d(out_normals.at(i + 3).x, out_vertices.at(i + 3).y, out_vertices.at(i + 3).z);
		glNormal3d(out_normals.at(i + 1).x, out_vertices.at(i + 1).y, out_vertices.at(i + 1).z);
		glNormal3d(out_normals.at(i + 1).x, out_vertices.at(i + 1).y, out_vertices.at(i + 1).z);
		glNormal3d(out_normals.at(i).x, out_vertices.at(i).y, out_vertices.at(i).z);

		glVertex3d(out_vertices.at(i + 3).x, out_vertices.at(i + 3).y, out_vertices.at(i + 3).z);
		glVertex3d(out_vertices.at(i + 2).x, out_vertices.at(i + 2).y, out_vertices.at(i + 2).z);
		glVertex3d(out_vertices.at(i + 1).x, out_vertices.at(i + 1).y, out_vertices.at(i + 1).z);
		glVertex3d(out_vertices.at(i).x, out_vertices.at(i).y, out_vertices.at(i).z);
		glEnd();
	}
}
