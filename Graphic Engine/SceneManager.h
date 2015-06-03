#pragma once

#include "Scene.h"

class SceneManager
{
public:
	SceneManager();
	~SceneManager();

	Scene* GetCurrentScene() const;
	void ChangeScene(/*id della scena*/);
	void AddSceneToList(Scene* _newScene, char* _name);

private:
	//hashmap di scene
	Scene* m_oCurrentScene;

};