#pragma once

#include "Scene.h"
#include <unordered_map>

//template<class T, class V>
//class gfxHashMap : public std::unordered_map<T, V, std::hash_compare<T, stdext::less<T>>, std::allocator<std::pair<const T, V>> > { };

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