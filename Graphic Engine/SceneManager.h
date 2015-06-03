#pragma once

#include <unordered_map>
#include "Scene.h"

typedef std::unordered_map<char*, Scene*> gfxHashMap;

class SceneManager
{
public:
	SceneManager();
	~SceneManager();

	Scene* GetCurrentScene() const;
	void ChangeScene(char* _name);
	void AddSceneToList(Scene* _newScene, char* _name);

private:
	Scene* m_oCurrentScene;
	gfxHashMap m_mSceneMap;
};