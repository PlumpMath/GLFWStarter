#ifndef _GAME_H_
#define _GAME_H_
#include "Application.h"

class Game : public Application
{
public:
	Game();
	virtual ~Game();

	virtual void Load();
	virtual void Unload();

	virtual void Update();
	virtual void Draw();

protected:
	unsigned int m_uiVao; /*Vertex Array Object*/
	unsigned int m_uiVbo; /*Vertex Buffer Object*/
	unsigned int m_uiIbo; /*Index Buffer Object*/

	unsigned int m_uiShader; /*Shader Handle*/

private:
};

#endif
