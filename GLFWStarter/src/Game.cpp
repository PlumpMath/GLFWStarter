#include "Game.h"
#include "gl_core_4_4.h"

Game::Game()
{
}

Game::~Game()
{
}

void Game::Load()
{
	static const char* vertex_shader =
		"#version 400\n"
		"in vec3 vp;"
		"void main ()"
		"{"
		"	gl_Position = vec4 (vp, 1.0);"
		"}";

	static const char* fragment_shader =
		"#version 400\n"
		"out vec4 frag_colour;"
		"void main ()"
		"{"
		"	frag_colour = vec4 (1.0, 1.0, 1.0, 1.0);"
		"}";

	/*Compile Vertex Shader*/
	GLuint vs = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vs, 1, &vertex_shader, NULL);
	glCompileShader(vs);

	/*Compile Fragment Shader*/
	GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs, 1, &fragment_shader, NULL);
	glCompileShader(fs);

	/*Create shader program (we now have a value for m_uiShader so we can access it)*/
	m_uiShader = glCreateProgram();

	/*Attach teh compiled shader to the program*/
	glAttachShader(m_uiShader, fs);
	glAttachShader(m_uiShader, vs);

	/*Links shaders to the handle*/
	glLinkProgram(m_uiShader);

	/*Delete the compiled shaders*/
	glDeleteShader(vs);
	glDeleteShader(fs);


	float verts[] = 
	{
	   -1.0f, -1.0f, 0.0f,	/*0*/
		1.0f, -1.0f, 0.0f,	/*1*/
		0.0f,  1.0f, 0.0f,	/*2*/
	};

	unsigned char indices[] =
	{
		0, 1, 2
	};

	/*Generate our VAO and bind it
	  Our VBO and IBO will be "group" with the VAO*/
	glGenVertexArrays(1, &m_uiVao);
	glBindVertexArray(m_uiVao);

	/*Create our VBO and IBO*/
	glGenBuffers(1, &m_uiVbo);
	glGenBuffers(1, &m_uiIbo);

	/*Bind these Buffers as well*/
	glBindBuffer(GL_ARRAY_BUFFER, m_uiVbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_uiIbo);

	/*Fill the buffers with data*/
	glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	/*Here we are describing the format of our vertices to OpenGL
	  This will describe to OpenGL the size, location & offset in memory for each vertex*/
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(
		0,				/*Position of First item*/
		3,				/*size - how many floats make up the item*/
		GL_FLOAT,		/*type of data*/
		GL_FALSE,		/*normalised?*/
		0,				/*stride - how far into the data you read*/
		(void*)0		/*array buffer offset*/
	);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Game::Unload()
{
	glDeleteBuffers(1, &m_uiVbo);
	glDeleteBuffers(1, &m_uiIbo);
	glDeleteVertexArrays(1, &m_uiVao);
	glDeleteProgram(m_uiShader );
}

void Game::Update()
{
}

void Game::Draw()
{
	/*Tell OpenGL to use our shader program*/
	glUseProgram(m_uiShader);

	/*Bind our VAO, remember, its grouped our VBO and IBO*/
	glBindVertexArray(m_uiVao);

	/*Draw our buffers. We've hard coded 3, referring to the number of verts*/
	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_BYTE, 0);

	/*Unbind our VAO so nothing else accidental changes it*/
	glBindVertexArray(0);
}
