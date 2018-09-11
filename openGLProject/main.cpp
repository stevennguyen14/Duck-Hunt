#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include <iostream>
#include <string>
#include <sstream>//string stream
#include "Shader.h"
#include "Menu.h"


using namespace std;

//just testing if this works with github

bool wireFrame = false;

int selectedColour = 1;


//window resize call back function prototype
void windowResizeCallBack(GLFWwindow* window, int width, int height);

//user inputs
void processInputs(GLFWwindow* window);

//Frames Per Second prototype
void showFPS(GLFWwindow* window); 

//Vertex Shader Program Source Code
const char* vertexShaderSource =
"#version 330 core\n"
"layout(location = 0) in vec3 aPos;\n" //variable location[0], read value in of type vec3
"\n"
"void main()\n"
"{\n"
"    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\n\0";//need \0 to tell it its the end of the character string

//Fragment Shader Program Source Code
const char* fragmentShaderSource =
"#version 330 core\n"
"out vec4 FragColor;\n" //value passed on to next shader when done
"\n"
"void main()\n"
"{\n"
"FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\n\0";



void main()
{
	glfwInit();
	//tell glfw that we want to work with openGL 3.3 core profile
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //the first 3 of 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); //the .3 of 3.3
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //core profile

	//build window
	GLFWwindow *window = glfwCreateWindow(800, 600, "My first OpenGL thing", NULL, NULL);
	//if it fails
	if (window == NULL){
		//try report error
		cout << "failed to create window" << endl;
		glfwTerminate(); //cleanup glfw stuff
		system("pause");
		return;
	}
	//make this window the current one
	glfwMakeContextCurrent(window);

	//initialise GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
		//if this fails, then
		cout << "GLAD failed to initialise" << endl;
		glfwTerminate(); //cleanup glfw stuff
		system("pause");
		return;
	}

	//set up openGL viewport x,y,w,h
	glViewport(0, 0, 800, 600);//you dont have to use the full window for openGL but we will

	//add window resize callback, params: window to check events on, function to call
		//when it resizes
	glfwSetFramebufferSizeCallback(window, windowResizeCallBack);


	//========================================================
	/*
	Shader shaderProgram1("vertexShader1.txt", "fragmentShader1.txt");
	Shader shaderProgram2("vertexShader2.txt", "fragmentShader2.txt");
	Shader shaderProgram3("vertexShader3.txt", "fragmentShader3.txt");
	

	//Compile Shader Source into shader programs
	//vertex shader first
	int vertexShaderID = glCreateShader(GL_VERTEX_SHADER);//gives id for a vertex shader
	//give it the source code
	//params:
	//		shader id
	//		number of source strings
	//		source strings (1 or array)
	//		length of string or NULL if it ends in a \0
	glShaderSource(vertexShaderID, 1, &vertexShaderSource, NULL);
	//compile the code on the gpu
	glCompileShader(vertexShaderID);

	//check for errors
	int success;
	char infoLog[512];
	//check compile status for our program, store result in success
	glGetShaderiv(vertexShaderID, GL_COMPILE_STATUS, &success);
	//failed?
	if (!success){
		//get error for the log and store in infoLog
		glGetShaderInfoLog(vertexShaderID, 512, NULL, infoLog);
		cout << "Vertex shader error!: " << infoLog << endl;
		system("pause");
	}
	//Fragment shader
	int fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShaderID, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShaderID);

	glGetShaderiv(fragmentShaderID, GL_COMPILE_STATUS, &success);
	//failed?
	if (!success){
		//get error for the log and store in infoLog
		glGetShaderInfoLog(fragmentShaderID, 512, NULL, infoLog);
		cout << "Fragment shader error!: " << infoLog << endl;
		system("pause");
	}
	//Create a Shader Program which links a bunch of shaders together for a full pipeline
	int shaderProgramID = glCreateProgram();
	//attach our shaders to this program
	glAttachShader(shaderProgramID, vertexShaderID);
	glAttachShader(shaderProgramID, fragmentShaderID);
	//link the attached shaders
	glLinkProgram(shaderProgramID);
	//check for linking errors
	glGetProgramiv(shaderProgramID, GL_LINK_STATUS, &success);
	if (!success){
		glGetProgramInfoLog(shaderProgramID, 512, NULL, infoLog);
		cout << "Shader Program Linking Error!: " << infoLog << endl;
		system("pause");
	}
	//our shaders were used to help make the full shader program, we dont need them individually anymore
	glDeleteShader(vertexShaderID);
	glDeleteShader(fragmentShaderID);

	//3 points in X,Y,Z
	float vertices[] = {
		0.5f, -0.5f, 0, //bottom right point
		-0.5f, -0.5f, 0, //bottom left
		0, 0.5f, 0 // top
	};

	float rectVertices[] = {
		//first triangle
		0.5f, 0.5f, 0.0f,//top right  0
		0.5f, -0.5f, 0.0f, //bottom right   1
		//-0.5f, 0.5f, 0.0f, //top left
		//second triangle
		//0.5f, -0.5f, 0.0f, //bottom right
		-0.5f, -0.5f, 0.0f, //bottom left  2
		-0.5f, 0.5f, 0.0f //top left  3
		
	};

	//the vertices order, treating each xyz as an index
	unsigned int indices[] = {
		0, 1, 3, //first triangle
		1, 2, 3 // second triangle
	};

	float rainbowTriangleVertices[] = {
		//x    y      z       //r    g    b
		0.5f, -0.5f, 0.0f,   1.0f, 0.0f, 0.0f,
		-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,
		0.0f, 0.5f, 0.0f,    0.0f, 0.0f, 1.0f
	};

	//generate vertex buffer objects in our GPU to store our vertices
	//if we only need 1
	unsigned int VBO; //we're gonna store the id of a vertex buffer object in this var
	glGenBuffers(1, &VBO); //params: how many vertex buffer objects to build and where to store their id's
	//if we need to generate multiple VBO's
	//unsigned int VBOs[2];
	//glGenBuffers(2, VBOs);

	//vbo for rect
	unsigned int VBO2;
	glGenBuffers(1, &VBO2);

	//vbo for rainbow triangle
	unsigned int VBO3;
	glGenBuffers(1, &VBO3);

	//Elemental Buffer Object
	//we're going to use this thing to hold the indices values to help describe
	//in which order to construct stuff out of a set of indices
	unsigned int EBO; //id of EBO we want to build in GPU
	glGenBuffers(1, &EBO); //generate buffer, return 1 id, store id in our EBO variable


	//generate Vertex Array Object, we bind vbo data to this thing aswell as a few specific function calls
	unsigned int VAO; //we'll store an id in this variable
	glGenVertexArrays(1, &VAO); //how many arrays to build, where to store ids(we just want 1, store id in VAO)

	//VAO2 was for rect
	unsigned int VAO2;
	glGenVertexArrays(1, &VAO2);

	//VAO3 for rainbow triangle VBO3
	unsigned int VAO3;
	glGenVertexArrays(1, &VAO3);

	//to start binding data to our VAO, we have to make our VAO active by binding it first
	glBindVertexArray(VAO);
		
		//bind the VBO we want to the current working array
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		//describe the VBO data and bind the vertices
		//params:
			//which buffer to bind to? (the current binded array buffer)
			//size of the data
			//the data
			//type of data: static, dynamic, stream
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		//tell it how to feed this vertex data into the vertex shader
		//params:
			//0 = variable location in our vertex shader program(aPos)
			//3 = how many values make up a vertex in our data (1-4)
			//GL_FLOAT = what datatype to map to in the shader
			//GL_FALSE = 
			//3*sizeof(float) = Stride(how to find the next vertex), after current, the next is 3 floats up
			//(void*)0 = must be (void*) type..., but the zero is 'what is the starting index of your data'
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		//enable this variable location slot in our vertex shader
		glEnableVertexAttribArray(0); //vec3 aPos

	//finished binding information to current VAO, set binding to nothing for safety
	glBindVertexArray(0);

	//VAO2 binding
	glBindVertexArray(VAO2);
		glBindBuffer(GL_ARRAY_BUFFER, VBO2);
		glBufferData(GL_ARRAY_BUFFER, sizeof(rectVertices), rectVertices, GL_STATIC_DRAW);
		//bind our EBO buffer for use
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		//bind our indices to this buffer
		//param:	bufferType,              size of data,      data to store, draw type
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
	glBindVertexArray(0);

	//bind VAO
	glBindVertexArray(VAO3);
	//things to do with buffer and vertex attributes will be binded to VAO3 now
		//bind buffer
		glBindBuffer(GL_ARRAY_BUFFER, VBO3);
		//give buffer the array of data
		glBufferData(GL_ARRAY_BUFFER, sizeof(rainbowTriangleVertices), rainbowTriangleVertices, GL_STATIC_DRAW);

		//tell it which parts of our rainbowTriangleVertices array are associated with vertex shaders
		//location = 0 variable aPos
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		//next, we want to tell it which parts of our array are the colour values to go into location = 1 variable aColour
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3*sizeof(float)));
		glEnableVertexAttribArray(1);
	glBindVertexArray(0); //unbind the VAO so we dont accidentally mess with our currently binded options

	*/
	//================================================================================
	
	Menu menu;
	bool showMenu;

	//GAME LOOP
	while (!glfwWindowShouldClose(window))
	{
		//user inputs
		processInputs(window);
		//GROWTH
		//MINDSET!

		//RENDER STUFF
		//set openGL clear colour
		glClearColor(0,0,1,1);//r,g,b,a as floats, 0 to 1
		//clear screen
		glClear(GL_COLOR_BUFFER_BIT);

		//displays menu
		if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
			showMenu = false;
		if (showMenu)
			menu.displayMenu();


		//======================================
		/*
		//LETS DRAW THE DAMN TRIANGLE!!!
		//1.tell it which shader program to use
		//glUseProgram(shaderProgramID);
		//shaderProgram1.use();
		shaderProgram2.use();
		//lets set that uniform value
		//find the uniform variables location
		//NOTE: gets location of uniform variable of currently in use shader program
		int ourColourUniformLocation = glGetUniformLocation(shaderProgram2.ID, "ourColour");
		//then set its value
		//params:
		// uniform variable location,    R        G    B     A   
		if (selectedColour == 1)
			glUniform4f(ourColourUniformLocation, 0.0f, 1.0f, 0.0f, 1.0f);
		if (selectedColour == 2)
			glUniform4f(ourColourUniformLocation, 0.0f, 1.0f, 1.0f, 1.0f);
		if (selectedColour == 3)
			glUniform4f(ourColourUniformLocation, 1.0f, 0.5f, 0.0f, 1.0f);
		//NOTE: uniforms are global variables. It will hold this green colour
		//until we decide to change it to something else

		//2.bind a VAO to work with (can only bind 1 at a time)
		glBindVertexArray(VAO2);
		//3.draw array
		//param:
		//	primitive type(GL_POINTS, GL_TRIANGLES and GL_LINE_STRIP)
		//	starting index in the array
		//  number of vertices in the array
		//glDrawArrays(GL_TRIANGLES, 0, 6);

		//3.draw elements
		//param:
		//	primitive type
		//	how many elements in our indices array (or how many we want to use at least)
		//	data type of our indices
		//	starting index in our indices to start building from
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		//LOAD UP VAO3 to draw the sick ass rainbow triangle!!!!!!!.......
		shaderProgram3.use();
		glBindVertexArray(VAO3);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		*/
		//==========================================


		//Input for window
		glfwPollEvents();

		//swap render buffers with this loops rendered scene
		glfwSwapBuffers(window);

		showFPS(window);
	}

	/*
	//optional: de-allocate all resources
	glDeleteVertexArrays(1, &VAO);//params: how many, thing with ids(unsigned int, or array of)
	glDeleteVertexArrays(1, &VAO2);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &VBO2);
	glDeleteBuffers(1, &EBO);
	//glDeleteBuffers(2, VBOs); //example of deleting 2 VBO ids from the VBOs array
	*/

	glfwTerminate();
}

//window resize call back function prototype
void windowResizeCallBack(GLFWwindow* window, int width, int height){
	glViewport(0, 0, width, height);
}

//user inputs
void processInputs(GLFWwindow* window){
	//if esc pressed, set window to 'should close'
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_W) ==GLFW_PRESS ){
		//flip wiremode value
		wireFrame = !wireFrame;
		if (wireFrame) //if(wireframe == true)
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		else
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
	if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
		selectedColour = 1;
	if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
		selectedColour = 2;
	if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
		selectedColour = 3;
}

void showFPS(GLFWwindow* window){
	//static function variables are declared 
	//once per project run, so these 2 lines of 
	//code run once and then the variables persist
	//until the end of the program
	static double previousSeconds = 0.0;
	static int frameCount = 0;
	double elapsedSeconds;
	double currentSeconds = glfwGetTime();
		//getTime returns seconds since startup

	elapsedSeconds = currentSeconds - previousSeconds;
	if (elapsedSeconds > 0.25){
		previousSeconds = currentSeconds;
		double fps = frameCount / elapsedSeconds;
		double msPerFrame = 1000.0 / fps;

		stringstream ss;
		ss.precision(3);//3 decimal places
		ss << fixed << "Game1 FPS: " << fps << " Frame Time: " << msPerFrame << "(ms)";

		glfwSetWindowTitle(window, ss.str().c_str());
		frameCount = 0;
	}
	frameCount++;
}
