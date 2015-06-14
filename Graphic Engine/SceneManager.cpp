#include "SceneManager.h"

SceneManager::SceneManager()
{
	m_oCurrentScene = nullptr;
}

SceneManager::~SceneManager()
{

}

void SceneManager::Start()
{
	m_oCurrentScene = m_mSceneMap.begin()->second;
}

Scene* SceneManager::GetCurrentScene() const
{
	return m_oCurrentScene;
}

void SceneManager::ChangeScene(char* _name, DXRenderer* _renderer)
{
	if (m_oCurrentScene != nullptr) m_oCurrentScene->CleanResources();
	m_oCurrentScene = m_mSceneMap.find(_name)->second;
	if (m_oCurrentScene != nullptr) m_oCurrentScene->SetupScene(_renderer);
}

void SceneManager::AddSceneToList(Scene* _newScene, char* _name)
{
	//_newScene->SetSceneManager(this);
	std::pair<char*, Scene*> _entry(_name, _newScene);
	m_mSceneMap.insert(_entry);
}