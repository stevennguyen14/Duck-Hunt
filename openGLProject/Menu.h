#pragma once
#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include "Shader.h"


class Menu
{
public:
	Menu();
	~Menu();
	//Add all of your attributes here e.g
	unsigned int backgroundVBO, backgroundEBO, backgroundVAO, backgroundID;
	unsigned int logoVBO, logoEBO, logoVAO, logoID;
	unsigned int textVBO, textEBO, textVAO, textID;
	//etc for each thing
	
	
	//Move these into the class definition
	void background();
	void logo();
	void text();
	void displayMenu();
};


