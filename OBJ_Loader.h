/*
	Author:Hanning Chen
	Class:ECE6122
	Last Date Modified:2019.11.21
	Description:This is the .h file for ECE6122 which includes definition of vertices structure
	,loadOBJ function to load obj file and enhanceDraw function to draw the enhance piece
	I reference the method :http://www.opengl-tutorial.org/beginners-tutorials/tutorial-7-model-loading/
*/

#include<GL/glut.h>
#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<vector>
#include<fstream>
#include<sstream>

using namespace std;

//vec3 is the structure for vertex including x, y, z position
struct vec3
{
	GLfloat x;
	GLfloat y;
	GLfloat z;
};
//vec2 is the structure for material vertex including x, y position
struct vec2
{
	GLfloat x;
	GLfloat y;
};

using namespace std;

//loadOBJ is the function to load vertice parameter into the function
//the input parameter includes the path of the file,the vector that stores vertices and 
//the vector stores matrial vectices and vecter that stores normal vertices.
bool loadOBJ(const char* path, vector<vec3>& out_vertices,
	vector<vec2>& out_uvs, vector<vec3>& out_normals);
//enhanceDraw is the function to draw enhance piece object
void enhanceDraw(const char* name);
