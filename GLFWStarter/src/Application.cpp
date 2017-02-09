#include <GLFW\glfw3.h>

#include "Application.h"

Application::Application()
{
}

Application::~Application()
{
}

bool Application::Setup(int a_iWindowWidth, int a_iWindowHeight)
{
	/*Take input screen size and save it in member variables*/	
	m_iWindowWidth = a_iWindowWidth;
	m_iWindowHeight = a_iWindowHeight;

	/* Initialize the library */
	if (!glfwInit())
		return false;

	/* Create a windowed mode window and its OpenGL context */
	m_gWindow = glfwCreateWindow(m_iWindowWidth, m_iWindowHeight, "Hello World", NULL, NULL);

	if (!m_gWindow)
	{
		glfwTerminate();
		return false;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(m_gWindow);

	return true;
}

void Application::Shutdown()
{
	glfwTerminate();
}

void Application::Run()
{
	Load();

	while (!glfwWindowShouldClose(m_gWindow))
	{
		Update();
		Draw();
	}

	Unload();
}

void Application::Load()
{
}

void Application::Update()
{
}

void Application::Draw()
{
	/* Render here */
	glClear(GL_COLOR_BUFFER_BIT);

	/* Swap front and back buffers */
	glfwSwapBuffers(m_gWindow);

	/* Poll for and process events */
	glfwPollEvents();
}

void Application::Unload()
{
}

int Application::GetWindowHeight() const
{
	return m_iWindowHeight;
}

int Application::GetWindowWidth() const
{
	return m_iWindowWidth;
}

GLFWwindow * Application::GetWindow()
{
	return m_gWindow;
}
