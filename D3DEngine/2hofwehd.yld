#pragma once
#include "Core.h"
#include "vector"
class Scene;

class Director
{
	SINGLETON_CLASS(Director)
public:
	bool Init();
	void Cleanup();

	void Update();
	void Render();

	void PushScene(Scene*);
	void PopScene();
	void ReplaceScene(Scene*);
	void RunWithScene(Scene*);

	void Pause();
	void Resume();

	int GetWidth();
	int GetHeight();
private:
	bool m_run;
	std::vector<Scene*> m_scenes;
};