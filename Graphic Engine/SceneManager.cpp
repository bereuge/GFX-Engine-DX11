#include "SceneManager.h"

SceneManager::SceneManager()
{
	m_oCurrentScene = nullptr;
}

SceneManager::~SceneManager()
{

}

Scene* SceneManager::GetCurrentScene() const
{
	return m_oCurrentScene;
}

void SceneManager::ChangeScene()
{
	m_oCurrentScene->CleanResources();
	//m_oCurrentScene=//map.get(id);
	m_oCurrentScene->SetupScene();
}

void SceneManager::AddSceneToList(Scene* _newScene, char* _name)
{
	//hashmap.add(newscene, key = _name)
}