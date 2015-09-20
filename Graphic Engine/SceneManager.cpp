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

AbstractScene* SceneManager::GetCurrentScene() const
{
	return m_oCurrentScene;
}

void SceneManager::ChangeScene(char* _name)
{
	if (m_oCurrentScene != nullptr) m_oCurrentScene->CleanResources();
	m_oCurrentScene = m_mSceneMap.find(_name)->second;
	if (m_oCurrentScene != nullptr) m_oCurrentScene->SetupScene();
}

void SceneManager::AddSceneToList(AbstractScene* _newScene, char* _name)
{
	//_newScene->SetSceneManager(this);
	std::pair<char*, AbstractScene*> _entry(_name, _newScene);
	m_mSceneMap.insert(_entry);
}