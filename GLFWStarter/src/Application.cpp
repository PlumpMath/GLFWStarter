#include "gl_core_4_4.h"
#include "Application.h"

#include <GLFW\glfw3.h>

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

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);

	/* Create a windowed mode window and its OpenGL context */
	m_gWindow = glfwCreateWindow(m_iWindowWidth, m_iWindowHeight, "Hello World", NULL, NULL);

	if (!m_gWindow)
	{
		glfwTerminate();
		return false;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(m_gWindow);

	/*OpenGL 4.4 setup*/
	if (ogl_LoadFunctions() == ogl_LOAD_FAILED)
	{
		/*We didn't load properly, gracefully exit*/
		glfwDestroyWindow(m_gWindow);
		glfwTerminate();
		return false;
	}

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
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		Update();
		Draw();

		/* Swap front and back buffers */
		glfwSwapBuffers(m_gWindow);

		/* Poll for and process events */
		glfwPollEvents();
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
