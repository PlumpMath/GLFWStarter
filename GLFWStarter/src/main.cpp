#include "Game.h"

int main(int argc, char **argv)
{
	Application *pApp = new Game();

	if (pApp->Setup(1360, 768))
	{
		pApp->Run();
		pApp->Shutdown();
	}

	delete pApp;

	return 0;
}