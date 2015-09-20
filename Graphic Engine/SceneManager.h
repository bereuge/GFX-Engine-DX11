#pragma once

#include <unordered_map>
#include "AbstractScene.h"

typedef std::unordered_map<char*, AbstractScene*> gfxHashMap;

class SceneManager
{
public:
	SceneManager();
	~SceneManager();

	void Start();
	AbstractScene* GetCurrentScene() const;
	void ChangeScene(char* _name);
	void AddSceneToList(AbstractScene* _newScene, char* _name);

private:
	AbstractScene* m_oCurrentScene;
	gfxHashMap m_mSceneMap;
};