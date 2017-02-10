#include "Game.h"
#include "gl_core_4_4.h"
#include "lodepng.h"

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
		"in vec4 vc;"
		"in vec2 vuv;"
		"out vec2 fuv;"
		"out vec4 fc;"
		"uniform mat4 projection;"
		"void main ()"
		"{"
		"	fc = vc;"
		"	fuv = vuv;"
		"	gl_Position = projection * vec4 (vp, 1.0);"
		"}";

	static const char* fragment_shader =
		"#version 400\n"
		"in vec4 fc;"
		"in vec2 fuv;"
		"uniform sampler2D texture;"
		"out vec4 frag_colour;"
		"void main ()"
		"{"
		"	frag_colour = texture2D(texture, fuv) * fc;"
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

	/**/
	glBindAttribLocation(m_uiShader, 0, "vp");
	glBindAttribLocation(m_uiShader, 1, "vc");
	glBindAttribLocation(m_uiShader, 2, "vuv");

	/*Links shaders to the handle*/
	glLinkProgram(m_uiShader);

	/*Delete the compiled shaders*/
	glDeleteShader(vs);
	glDeleteShader(fs);

	float x = 10;
	float y = 10;
	float w = 100;
	float h = 100;
	
	float verts[] = 
	{
	  /*x		y		z     r     g     b     a	  u   	v*/	
		x,		y + h,	0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0,	1,
		x + w,	y + h,	0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1,	1,
		x + w,	y,		0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1,	0,
		x,		y,		0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0,	0
	};

	unsigned char indices[] =
	{
		0, 1, 2,
		0, 2, 3
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
		0,					/*Attribute 0 (which we linked to "vp" above)*/
		3,					/*size - how many floats make up the item*/
		GL_FLOAT,			/*type of data*/
		GL_FALSE,			/*normalised?*/
		sizeof(float) * 9,	/*stride - size of the entire vertex*/
		(void*)0			/*Gives the amount before the beginning of the vertex*/
	);

	/*Read the colour information from the vertex buffer*/
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(
		1,							/*Attribute 1 (which we linked to "vc" above*/
		4,							/*size - how many floats make up the item*/
		GL_FLOAT,					/*type of data*/
		GL_FALSE,					/*normalised?*/
		sizeof(float) * 9,			/*stride - size of the entire vertex*/
		(void*)(sizeof(float) * 3)	/*Gives the amount before the beginning of the vertex*/
	);

	/*Read the uv information from the vertex buffer*/
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(
		2,							/*Attribute 1 (which we linked to "vc" above*/
		2,							/*size - how many floats make up the item*/
		GL_FLOAT,					/*type of data*/
		GL_FALSE,					/*normalised?*/
		sizeof(float) * 9,			/*stride - size of the entire vertex*/
		(void*)(sizeof(float) * 7)	/*Gives the amount before the beginning of the vertex*/
	);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	/*Begin Texture Loading*/
	std::vector<unsigned char> image;
	unsigned texWidth, texHeight;
	unsigned error = lodepng::decode(image, texWidth, texHeight, "box.png");

	/*Generate a texture handle*/
	glGenTextures(1, &m_uiTexture);

	/*Bind the texture for use*/
	glBindTexture(GL_TEXTURE_2D, m_uiTexture);

	/*Fill the texture with the loaded pixels (pixels sent to the graphics card)*/
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 
		texWidth, texHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, &image[0]);

	/*Set some standard texture parameters*/
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	/*Unbind the texture*/
	glBindTexture(GL_TEXTURE_2D, 0);
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
	DrawTexturedQuad(10, 10, 100, 100);
	DrawTexturedQuad(150, 10, 100, 100);
}

void Game::DrawTexturedQuad(float a_x, float a_y, float a_w, float a_h)
{

	float verts[] =
	{
		//  x,       y,			 z,    r,    g,    b,    a,    u,    v
		a_x,         a_y + a_h,  0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0,    1,// bottom left
		a_x + a_w,   a_y + a_h,  0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1,    1,// bottom right
		a_x + a_w,   a_y,		 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1,    0,// top right
		a_x,         a_y,		 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0,    0// top left
	};

	unsigned char indices[] =
	{
		0, 1, 2,
		0, 2, 3
	};

	glBindVertexArray(m_uiVao);
	glBindBuffer(GL_ARRAY_BUFFER, m_uiVbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_uiIbo);

	glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	float l = 0;					/*Left side of window*/
	float r = GetWindowWidth();		/*Right side of window*/
	float t = 0;					/*Top side of window*/
	float b = GetWindowHeight();	/*Bottom side of window*/
	float n = 0.0f;					/*Closest side of window*/
	float f = 1000.0f;				/*Furthest side of window*/

									/*Create an orthographic projection matrix
									on the shader, our verts will be multiplied by this matrix*/
	static float projection[] =
	{
		2.0f / (r - l),         0,                      0,                      0,
		0,                      2.0f / (t - b),         0,                      0,
		0,                      0,                      2.0f / (f - n),         0,
		-(r + l) / (r - l),     -(t + b) / (t - b),     -(f + n) / (f - n),     1
	};

	/*Tell OpenGL to use our shader program*/
	glUseProgram(m_uiShader);
	glUniformMatrix4fv(glGetUniformLocation(m_uiShader, "projection"), 1, false, projection);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_uiTexture);

	glUniform1i(glGetUniformLocation(m_uiShader, "texture"), 0);

	/*Bind our VAO, remember, its grouped our VBO and IBO*/
	glBindVertexArray(m_uiVao);

	/*Draw our buffers. We've hard coded 3, referring to the number of verts*/
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, 0);

	/*Unbind our VAO so nothing else accidental changes it*/
	glBindVertexArray(0);
}


