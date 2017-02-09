#ifndef _APPLICATION_H_
#define _APPLICATION_H_

class GLFWwindow;

class Application
{
public:
	Application();
	virtual ~Application();

	bool Setup(int a_iWindowWidth, int a_iWindowHeight);
	void Shutdown();

	void Run();

	/*Load will be called within Run before the game loop begins
	  Assets load here.*/
	virtual void Load();

	/*Called every frame by the Run function*/
	virtual void Update();
	virtual void Draw();

	/*Called when Run stops looping. Remove whichever assets you still
	  have from Load or other game actions*/
	virtual void Unload();

	int GetWindowHeight() const;
	int GetWindowWidth() const;
	
	GLFWwindow *GetWindow();

protected:

	GLFWwindow *m_gWindow;

	int m_iWindowHeight;
	int m_iWindowWidth;

private:

};
#endif


