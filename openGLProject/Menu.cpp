#include "Menu.h"
#define STB_IMAGE_IMPLEMENTATION//so it wont go looking for the c or cpp files
#include "stb_image.h"


Menu::Menu()
{
	background();
	logo();
	text();
}


Menu::~Menu()
{
}

// load up background image
void Menu::background() {
	float rectVertices[] = {
		//first triangle
		1.0f, 1.0f, 0.0f,//top right
		1.0f, -1.0f, 0.0f, //bottom right
		//-0.5f, 0.5f, 0.0f, //top left
		//second triangle
		// 0.5f, -0.5f, 0.0f, //bottom right
		-1.0f, -1.0f, 0.0f, //bottom left
		-1.0f, 1.0f, 0.0f //top left
	};

	unsigned int indices[] = {
		0, 1, 3, //first triangle
		1, 2, 3 // second triangle
	};

	//MATT:use your attributes from here
	//unsigned int VBO; //we're gonna store the id of a vertex buffer object in this var
	glGenBuffers(1, &backgroundVBO);
	//unsigned int EBO; //id of EBO we want to build in GPU
	glGenBuffers(1, &backgroundEBO);
//	unsigned int VAO; //we'll store an id in this variable
	glGenVertexArrays(1, &backgroundVAO);


	//VAO binding
	glBindVertexArray(backgroundVAO);
	glBindBuffer(GL_ARRAY_BUFFER, backgroundVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(rectVertices), rectVertices, GL_STATIC_DRAW);
	//bind our EBO buffer for use
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, backgroundEBO);
	//bind our indices to this buffer
	//param:	bufferType,              size of data,      data to store, draw type
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);

	
	glGenTextures(1, &backgroundID);
	
	//bind texture to work on
	glBindTexture(GL_TEXTURE_2D, backgroundID);
	//wrapping
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);//horizontal
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);//vertical
	//stretch
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); 

	//load image
	int width, height, channelCount;
	unsigned char *BGImage = stbi_load("background.png", &width, &height, &channelCount, 0);
	if (BGImage) {
		//GIvE THE TEXTURE UN OUR GRAOHICS CARD THE DATA FROM THE PNG FILE
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, BGImage);
		//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, BGImage);
		//generate mipmaps for this texture 
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		cout << "failed to load background.png" << endl;
	}
	//free image data from ram because thers a copy in the texture
	stbi_image_free(BGImage);
}

//=======================================================

//load up logo image
void Menu::logo() {
	float rectVertices[] = {
		//first triangle
		1.0f, 1.0f, 0.0f,//top right
		1.0f, -0.5f, 0.0f, //bottom right
		//-0.5f, 0.5f, 0.0f, //top left
		//second triangle
		// 0.5f, -0.5f, 0.0f, //bottom right
		-1.0f, -0.5f, 0.0f, //bottom left
		-1.0f, 1.0f, 0.0f //top left
	};

	unsigned int indices[] = {
		0, 1, 3, //first triangle
		1, 2, 3 // second triangle
	};


	//unsigned int VBO; //we're gonna store the id of a vertex buffer object in this var
	glGenBuffers(1, &logoVBO);
	//unsigned int logoEBO; //id of EBO we want to build in GPU
	glGenBuffers(1, &logoEBO);
	//unsigned int VAO; //we'll store an id in this variable
	glGenVertexArrays(1, &logoVAO);


	//VAO binding
	glBindVertexArray(logoVAO);
	glBindBuffer(GL_ARRAY_BUFFER, logoVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(rectVertices), rectVertices, GL_STATIC_DRAW);
	//bind our EBO buffer for use
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, logoEBO);
	//bind our indices to this buffer
	//param:	bufferType,              size of data,      data to store, draw type
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);

	//unsigned int logoID;
	glGenTextures(1, &logoID);

	//bind texture to work on
	glBindTexture(GL_TEXTURE_2D, logoID);
	//wrapping
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);//horizontal
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);//vertical
																 //stretch
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	//load image
	int width, height, channelCount;
	unsigned char *logoImage = stbi_load("logo.png", &width, &height, &channelCount, 0);
	if (logoImage) {
		//GIvE THE TEXTURE UN OUR GRAOHICS CARD THE DATA FROM THE PNG FILE
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, logoImage);
		//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, logoImage);
		//generate mipmaps for this texture 
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		cout << "failed to load logo.png" << endl;
	}
	//free image data from ram because thers a copy in the texture
	stbi_image_free(logoImage);
}

//=============================================================

//load up "press to play" image
void Menu::text() {
	float rectVertices[] = {
		//first triangle
		0.5f, 0.5f, 0.0f,//top right
		0.5f, -1.0f, 0.0f, //bottom right
		//-0.5f, 0.5f, 0.0f, //top left
		//second triangle
		// 0.5f, -0.5f, 0.0f, //bottom right
		-0.5f, -1.0f, 0.0f, //bottom left
		-0.5f, 0.5f, 0.0f //top left
	};

	unsigned int indices[] = {
		0, 1, 3, //first triangle
		1, 2, 3 // second triangle
	};


	//unsigned int VBO; //we're gonna store the id of a vertex buffer object in this var
	glGenBuffers(1, &textVBO);
	//unsigned int EBO; //id of EBO we want to build in GPU
	glGenBuffers(1, &textEBO);
	//unsigned int VAO; //we'll store an id in this variable
	glGenVertexArrays(1, &textVAO);


	//VAO binding
	glBindVertexArray(textVAO);
	glBindBuffer(GL_ARRAY_BUFFER, textVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(rectVertices), rectVertices, GL_STATIC_DRAW);
	//bind our EBO buffer for use
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, textEBO);
	//bind our indices to this buffer
	//param:	bufferType,              size of data,      data to store, draw type
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);

	//unsigned int textID;
	glGenTextures(1, &textID);

	//bind texture to work on
	glBindTexture(GL_TEXTURE_2D, textID);
	//wrapping
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);//horizontal
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);//vertical
																 //stretch
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	//load image
	int width, height, channelCount;
	unsigned char *textImage = stbi_load("text.png", &width, &height, &channelCount, 0);
	if (textImage) {
		//GIvE THE TEXTURE UN OUR GRAOHICS CARD THE DATA FROM THE PNG FILE
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, textImage);
		//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, textImage);
		//generate mipmaps for this texture 
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		cout << "failed to load text.png" << endl;
	}
	//free image data from ram because theres a copy in the texture
	stbi_image_free(textImage);
}

//============================================================

//renders menu to screen
void Menu::displayMenu() {

	Shader shaderProgram4("VertexShader4.txt", "FragmentShader4.txt");
	//MATT: heres a battle plan for this part
	//set shader for first thing you want to draw
	shaderProgram4.use();
	//bind VAO
	glBindVertexArray(backgroundVAO);
	//setup uniforms (mostly textures at this stage)
	//set texture uniforms: tell each texture uniform which texture slot to use
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, backgroundID);
	//draw thing
	glUniform1i(glGetUniformLocation(shaderProgram4.ID, "texture"), 0);

	//===========================================

	//MATT: heres a battle plan for this part
	//set shader for first thing you want to draw
	shaderProgram4.use();
	//bind VAO
	glBindVertexArray(backgroundVAO);
	//setup uniforms (mostly textures at this stage)
	//set texture uniforms: tell each texture uniform which texture slot to use
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, backgroundID);
	//draw thing
	glUniform1i(glGetUniformLocation(shaderProgram4.ID, "texture"), 0);

	//=======================================

	//MATT: heres a battle plan for this part
	//set shader for first thing you want to draw
	shaderProgram4.use();
	//bind VAO
	glBindVertexArray(backgroundVAO);
	//setup uniforms (mostly textures at this stage)
	//set texture uniforms: tell each texture uniform which texture slot to use
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, backgroundID);
	//draw thing


	//ERIC: cant remember or find exaclty what the string "TEXTURE" relates too
	glUniform1i(glGetUniformLocation(shaderProgram4.ID, "texture"), 0);
}
